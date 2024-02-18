package models

import (
	"github.com/tsousa111/probum-auth/db"
	"github.com/tsousa111/probum-auth/forms"
	"golang.org/x/crypto/bcrypt"
	"gorm.io/gorm"
)

type User struct {
	gorm.Model

	UId      string `gorm:"primaryKey" json:"id" binding:"required"`
	Password []byte `gorm:"index"      json:"password" binding:"required"`
}

func (u User) Create(userPayload forms.UserSignup) (*User, error) {
	database := db.GetDB()

	hashedPass, err := bcrypt.GenerateFromPassword([]byte(userPayload.Password), 10)
	if err != nil {
		return nil, err
	}

	user := User{
		UId:      userPayload.UId,
		Password: hashedPass,
	}

	if err := database.Create(&user).Error; err != nil {
		return nil, err
	}

	return &user, nil
}
func (u User) Delete(uId string) error {

	database := db.GetDB()

	if err := database.Delete(&User{}, uId).Error; err != nil {
		return err
	}
	return nil
}

func (u User) Get(id string) (*User, error) {

	database := db.GetDB()

	var user User
	if err := database.First(&user, id).Error; err != nil {
		return nil, err
	}

	return &user, nil
}

func (u User) CheckPassword(userPayload forms.User) (*User, error) {

	stored, err := u.Get(userPayload.UId)
	if err != nil {
		return nil, err
	}

	err = bcrypt.CompareHashAndPassword(stored.Password, []byte(userPayload.Password))
	if err != nil {
		return nil, err
	}

	return stored, nil
}

func (u User) ChangePassword(userPayload forms.User) (*User, error) {

	database := db.GetDB()

	user, err := u.Get(userPayload.UId)
	if err != nil {
		return nil, err
	}

	user.Password, err = bcrypt.GenerateFromPassword([]byte(userPayload.Password), 10)
	if err != nil {
		return nil, err
	}

	database.Save(user)
	return user, nil
}

func (u User) CheckAuth(userPayload forms.User) error {

	// verificar se user existe GetUserById
	stored, err := u.Get(userPayload.UId)
	if err != nil {
		return err
	}
	// verificar a Password
	err = bcrypt.CompareHashAndPassword(stored.Password, []byte(userPayload.Password))
	if err != nil {
		return err
	}
	// todo: get user info pelo servico de user management

	// return do user e hash da pass e erro caso nao exista
	return nil
}
