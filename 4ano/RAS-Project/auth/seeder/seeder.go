package seeder

import (
	"encoding/json"
	"log"
	"os"

	"github.com/tsousa111/probum-auth/db"
	"github.com/tsousa111/probum-auth/models"
	"github.com/tsousa111/probum-auth/utils"
	"golang.org/x/crypto/bcrypt"
	"gorm.io/gorm"
)

type Seeder struct {
	SeedPath string
	Db       *gorm.DB
}

func New(seedPath string) *Seeder {

	db := db.GetDB()

	return &Seeder{
		SeedPath: seedPath,
		Db:       db,
	}
}

func (s *Seeder) Seed() {

	log.Println("seeding database")

	usersJson, err := os.ReadFile(s.SeedPath)
	utils.Check(err, "")

	var users []models.User

	err = json.Unmarshal(usersJson, &users)
	utils.Check(err, "")

	// Print the users' information
	for _, user := range users {
		hashedPassword, err := bcrypt.GenerateFromPassword([]byte(user.Password), 10)
		utils.Check(err, "")
		user.Password = hashedPassword
		s.Db.Create(&user)
	}

	log.Println("finished seeding database")

}
