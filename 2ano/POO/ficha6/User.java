import java.time.LocalDateTime;

public class User 
{
    public enum Genero 
    {
        M, 
        F
    }
   
    private String email;
    private String password;
    private String nome;
    private Genero genero;
    private int altura;
    private int peso;
    private LocalDateTime nascimento;
    private String fav;
    
    
    public User()
    {
        email = "";
        password = "";
        nome = "";
        genero = "";
        altura = 0;
        peso = 0;
        nascimento = 0;
        fav = "";
    }

    public User(String email, String password, String nome, String genero, int altura, int peso, LocalDateTime nascimento, String fav)
    {
        this.email = email;
        this.password = password;
        this.nome = nome;
        this.genero = genero;
        this.altura = altura;
        this.peso = peso;
        this.nascimento = nascimento;
        this.fav = fav;
    }

    public User(User umUser)
    {
        this.email = umUser.getEmail();
        this.password = umUser.getPassword();
        this.nome = umUser.getNome();
        this.genero = umUser.getGenero();
        this.altura = umUser.getAltura();
        this.peso = umUser.getPeso();
        this.nascimento = umUser.getNascimento();
        this.fav = umUser.getFav();
    }

    public String getEmail()
    {
        return this.email;
    }

    public void setEmail(String email)
    {
        this.email = email;
    }

    public String getPassword()
    {
        return this.password;
    }

    public void setPassword(String password)
    {
        this.password = password;
    }

    public String getNome()
    {
        return this.nome;
    }

    public void setNome(String nome)
    {
        this.nome = nome;
    }

    public String getGenero()
    {
        return this.genero;
    }

    public void setGenero(String genero)
    {
        this.genero = genero;
    }

    public int getAltura()
    {
        return this.altura;
    }

    public void setAltura(int altura)
    {
        this.altura = altura;
    }

    public int getPeso()
    {
        return this.peso;
    }

    public void setPeso(int peso)
    {
        this.peso = peso;
    }

    public LocalDateTime getNascimento()
    {
        return this.nascimento;
    }

    public void setNascimento(LocalDateTime nascimento)
    {
        this.nascimento = nascimento;
    }

    public String getFav()
    {
        return this.fav;
    }

    public void setFav(String fav)
    {
        this.fav = fav;
    }

    public boolean equals(Object o) 
    {
        if (this==o) return true; 
        if ((o == null) || (this.getClass() != o.getClass())) return false; 
        
        User user = (User) o; 
        return user.get () == this.email && 
               user.get() == this.nome &&
               user.get() == this.password &&               
               user.get() == this.genero && 
               user.get() == this.altura &&
               user.get() == this.peso &&
               user.get() == this.nascimento &&
               user.get() == this.fav; 
    }

    public User clone() 
    {
        return new User(this); 
    }

    public String toString() 
    {   
        return "User: \n" 
            + "\n Email: " + this.email
            + "\n Password: " + this.password
            + "\n Nome: " + this.nome
            + "\n Genero" + this.genero
            + "\n Altura: " + this.altura
            + "\n Peso: " + this.peso
            + "\n Nascimento: " + this.nascimento
            + "\n Favorito: " + this.fav;
    }
}
