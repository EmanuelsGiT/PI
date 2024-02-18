package controllers

import (
	"net/http"

	"github.com/gin-gonic/gin"

	"github.com/tsousa111/probum-auth/forms"
	"github.com/tsousa111/probum-auth/models"
	"github.com/tsousa111/probum-auth/utils"
)

type UserController struct{}

var userModel = new(models.User)

func (u UserController) Create(c *gin.Context) {

	var newUser forms.UserSignup

	err := c.ShouldBindJSON(&newUser)
	if err != nil {
		utils.HandleAbort(c, http.StatusBadRequest, "could not unmarshal request body into 'forms.UserSignup'", err.Error())
		return
	}

	user, err := userModel.Create(newUser)
	if err != nil {
		utils.HandleAbort(c, http.StatusBadRequest, "could not add user to the database", err.Error())
		return
	}

	c.JSON(
		http.StatusCreated,
		gin.H{"user": user},
	)
	return
}

func (u UserController) Delete(c *gin.Context) {

	storedObj, exists := c.Get("user")
	if !exists {
		utils.HandleAbort(c, http.StatusBadRequest, "user is not authenticated", "")
		return
	}

	stored := storedObj.(*models.User)

	err := userModel.Delete(stored.UId)
	if err != nil {
		utils.HandleAbort(c, http.StatusInternalServerError, "cannot delete user", err.Error())
		return
	}

	c.Status(http.StatusOK)
	return

}

func (u UserController) Update(c *gin.Context) {

	var userPayload forms.User

	err := c.ShouldBindJSON(&userPayload)
	if err != nil {
		utils.HandleAbort(c, http.StatusBadRequest, "could not unmarshal request body into 'models.User'", err.Error())
		return
	}

	user, err := userModel.ChangePassword(userPayload)
	if err != nil {
		utils.HandleAbort(c, http.StatusInternalServerError, "could not change password", err.Error())
		return
	}

	c.JSON(
		http.StatusOK,
		gin.H{"user": user},
	)
}

func (u UserController) Validate(c *gin.Context) {

	token := c.Param("jwt")
	if token == "" {
		utils.HandleAbort(c, http.StatusBadRequest, "jwt not specified as uri param", "")
		return
	}

	user, err := utils.CheckToken(token)
	if err != nil {
		utils.HandleAbort(c, http.StatusInternalServerError, "could not decode jwt token", err.Error())
	}

	c.JSON(
		http.StatusOK,
		gin.H{"user": user},
	)
}

func (u UserController) Login(c *gin.Context) {

	var user forms.User

	err := c.ShouldBindJSON(&user)
	if err != nil {
		utils.HandleAbort(c, http.StatusBadRequest, "could not unmarshal request body into 'models.User'", err.Error())
		return
	}

	_, err = userModel.CheckPassword(user)
	if err != nil {
		utils.HandleAbort(c, http.StatusUnauthorized, "invalid credentials", err.Error())
		return
	}

	tokenString, err := utils.CreateToken(user.UId)
	if err != nil {
		utils.HandleAbort(c, http.StatusInternalServerError, "could not generate jwt", err.Error())
		return
	}

	c.JSON(
		http.StatusOK,
		gin.H{"token": tokenString},
	)
}
