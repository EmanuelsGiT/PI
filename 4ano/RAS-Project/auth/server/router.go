package server

import (
	"github.com/gin-gonic/gin"
	"github.com/tsousa111/probum-auth/controllers"
)

func NewRouter() *gin.Engine {

	router := gin.New()

	router.Use(gin.Logger())
	router.Use(gin.Recovery())

	v1 := router.Group("api/v1")
	{
		userGroup := v1.Group("user")
		{
			user := new(controllers.UserController)

			userGroup.POST("/login", user.Login)
			userGroup.POST("/", user.Create)

			userGroup.GET("/verify/:jwt", user.Validate)

			userGroup.PUT("/", user.Update)

			userGroup.DELETE("/", user.Delete)

		}

	}
	return router
}
