package db

import (
	"github.com/tsousa111/probum-auth/utils"
	"gorm.io/driver/sqlite"
	"gorm.io/gorm"
)

var db *gorm.DB

func ConnectDatabase() {
	var err error

	db, err = gorm.Open(sqlite.Open("db/auth.db"), &gorm.Config{})
	utils.Check(err, "")
}

func GetDB() *gorm.DB {
	return db
}
