package main

import (
	"errors"
	"flag"
	"fmt"
	"os"

	"github.com/tsousa111/probum-auth/config"
	"github.com/tsousa111/probum-auth/db"
	"github.com/tsousa111/probum-auth/models"
	"github.com/tsousa111/probum-auth/seeder"
	"github.com/tsousa111/probum-auth/server"
	"gorm.io/gorm"
)

func main() {

	environment := flag.String("e", "development", "")
	flag.Usage = func() {
		fmt.Println("Usage: server -e {mode}")
		os.Exit(1)
	}

	flag.Parse()

	config.Init(*environment)

	db.ConnectDatabase()

	database := db.GetDB()
	if err := database.AutoMigrate(&models.User{}); err == nil && database.Migrator().HasTable(&models.User{}) {
		if err := database.First(&models.User{}).Error; errors.Is(err, gorm.ErrRecordNotFound) {
			s := seeder.New("seeder/seed_data/users.json")
			s.Seed()
		}
	}

	server.Init()
}
