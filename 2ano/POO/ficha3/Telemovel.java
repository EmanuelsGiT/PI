import java.util.Arrays;

public class Telemovel
{
    private String marca;
    private String modelo;
    private int displayx;
    private int displayy;
    private long armsg; //armazenamento utilizado para msg
    private long armtotal; //armazenamento utilizado para fotos e apps
    private long armfot; //armazenamento utilizado para fotos
    private long armapp; //armazenamento utilizado para apps
    private int espacocup; //armazenamento utilizado no total
    private int nfot;
    private int napp;
    //private ArrayList<String> nomeapps;

    public Telemovel()
    {
        this.marca = "Samsung";
        this.modelo = "A6";
        this.espacocup = 23;
        this.armsg = 2;
        this.armapp = 18;
        this.armtotal = 64;
        this.armfot = 3;
        this.displayx = 50;
        this.displayy = 100;
        this.napp = 20;
        this.nfot = 52;
    }

    public boolean existeEspaco(int numeroBytes)
    {
        if (this.espacocup + numeroBytes < this.armtotal)
            return true;

        return false;
    }

    public void instalaApp(String nome, int tamanho)
    {
        if (this.armapp + tamanho > this.espacocup)
            System.out.println("Nao ha espaço para a app.");
        else
        {
            this.armapp += tamanho;
            this.espacocup += tamanho;
            this.napp++;
            //this.nomeapps.add(nome);
        }
    }

    public void recebeMsg(String msg)
    {
        if (this.armsg+1>this.espacocup)
            System.out.println("Não há espaço para MSG.");
        else
        {
            this.armsg++;
        }
    }

    public void tamMedioApps()
    {
        System.out.println("O tamanho médio de cada app é "+(this.armapp)/(this.napp)+".");
    }

    public String maiorMsg()
    {
        return marca;
    }

    public void removeApp(String nome, int tamanho)
    {
        this.napp--;
        this.armapp-=tamanho;
        this.espacocup-=tamanho;
    }

}