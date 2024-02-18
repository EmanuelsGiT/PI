package utils

import (
	"bytes"
	"encoding/json"
	"errors"
	"github.com/gin-gonic/gin"
	"log"
	"net/http"
	"time"

	"github.com/golang-jwt/jwt/v4"
	"github.com/tsousa111/probum-auth/config"
	"github.com/tsousa111/probum-auth/forms"
)

func Check(err error, format string, args ...interface{}) {
	if err != nil {
		if format != "" {
			log.Fatalf(format, args...)
		} else {
			log.Println(err.Error())
		}
	}
}

func CheckToken(cookie string) (*forms.UserSignup, error) {
	conf := config.GetConfig()
	// Decode and validate the cookie.
	token, _ := jwt.Parse(cookie, func(token *jwt.Token) (interface{}, error) {

		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, errors.New("unexpected jwt signing method: " + token.Method.Alg())
		}
		return []byte(conf.GetString("app.jwt-secret")), nil

	})

	claims, ok := token.Claims.(jwt.MapClaims)
	if !(ok && token.Valid) {
		return nil, errors.New("token is not valid")
	}

	// Check the expiration.
	if float64(time.Now().Unix()) > claims["exp"].(float64) {
		return nil, errors.New("token is expired")
	}

	url := conf.GetString("endpoints.users.base") + conf.GetString("endpoints.users.get.uri") + claims["sub"].(string)
	header := map[string]string{}
	payload := []string{}
	resp, err := SendHTTPRequest(conf.GetString("endpoints.users.get.method"), url, header, payload)
	if err != nil {
		return nil, err
	}

	var buffer []byte = make([]byte, 1024)
	n, err := resp.Body.Read(buffer)
	if err != nil {
		return nil, err
	}

	var user forms.UserSignup
	err = json.Unmarshal(buffer[:n], &user)

	return &user, nil
}

func CreateToken(uId string) (string, error) {
	conf := config.GetConfig()

	token := jwt.NewWithClaims(jwt.SigningMethodPS256.SigningMethodRSA, jwt.MapClaims{
		"sub": uId,
		"exp": time.Now().Add(time.Hour * 24 * 7).Unix(),
	})

	jwtSecret := conf.GetString("app.jwt-secret")
	tokenString, err := token.SignedString(jwtSecret)
	if err != nil {
		return "", err
	}

	return tokenString, nil
}

func SendHTTPRequest(method, url string, headers map[string]string, payload interface{}) (*http.Response, error) {

	jsonPayload, err := json.Marshal(payload)
	if err != nil {
		return nil, err
	}

	req, err := http.NewRequest(method, url, bytes.NewBuffer(jsonPayload))
	if err != nil {
		return nil, err
	}

	req.Header.Set("Content-Type", "application/json")

	for key, value := range headers {
		req.Header.Set(key, value)
	}

	client := &http.Client{}
	return client.Do(req)
}

func HandleAbort(c *gin.Context, status int, message string, error string) {
	c.JSON(status, gin.H{"message": message, "error": error})
	c.Abort()
}
