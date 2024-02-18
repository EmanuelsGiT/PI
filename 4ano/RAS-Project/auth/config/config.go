package config

import (
	"github.com/spf13/viper"
)

var config *viper.Viper

func Init(env string) {

    config = viper.New()

    config.SetConfigType("yaml")
    config.SetConfigName(env)
    config.AddConfigPath("../config/")
    config.AddConfigPath("config/")

    err := config.ReadInConfig()
    if err != nil {
        panic(err.Error())
    }

}

func GetConfig() *viper.Viper {
    return config
}
