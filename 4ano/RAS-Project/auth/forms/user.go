package forms

type User struct {
	UId      string `json:"id" binding:"required"`
	Password string `json:"password" binding:"required"`
}

type UserSignup struct {
	Name     string `json:"name" binding:"required"`
	Email    string `json:"email" binding:"required"`
	UId      string `json:"id" binding:"required"`
	Password string `json:"password" binding:"required"`
	Role     string `json:"role" binding:"required"`
}
