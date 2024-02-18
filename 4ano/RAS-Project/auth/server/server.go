package server

import (
	"github.com/tsousa111/probum-auth/config"
	"github.com/tsousa111/probum-auth/utils"
)

func Init() {
	conf := config.GetConfig()
	router := NewRouter()

	err := router.Run(conf.GetString("app.listen"))
	utils.Check(err, "")
}
