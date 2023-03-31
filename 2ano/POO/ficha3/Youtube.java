import java.time.LocalDate;

public class Youtube
{
    private String nome;
    private int cont;
    private LocalDate data;
    private int resol;
    private int duracao;
    private String comentario;
    private int likes;
    private int dislikes;

    public Youtube(String nome, int cont, LocalDate data, int resol, int duracao, String comentario, int likes, int dislikes)
    {
        this.nome = nome;
        this.cont = cont;
        this.data = data;
        this.resol = resol;
        this.duracao = duracao;
        this.comentario = comentario;
        this.likes = likes;
        this.dislikes = dislikes;
    }

    public Youtube(Youtube youtube)
    {
        this.nome = youtube.getNome();
        this.cont = youtube.getCont();
        //this.data = youtube.getData(());
        this.resol = youtube.getResol();
        this.duracao = youtube.getDuracao();
        this.comentario = youtube.getComentario();
        this.likes = youtube.getLikes();
        this.dislikes = youtube.getDislikes();
    }

    public String getNome()
    {
        return this.nome;
    }

    public int getCont()
    {
        return this.cont;
    }

    public LocalDate getData()
    {
        return this.data;
    }

    public int getResol()
    {
        return this.resol;
    }

    public int getDuracao()
    {
        return this.duracao;
    }

    public String getComentario() {
        return comentario;
    }

    public int getLikes()
    {
        return this.likes;
    }

    public int getDislikes()
    {
        return this.dislikes;
    }

    public void setCont(int cont) {
        this.cont = cont;
    }

    public void setData(LocalDate data) {
        this.data = data;
    }

    public void setDislikes(int dislikes) {
        this.dislikes = dislikes;
    }

    public void setDuracao(int duracao) {
        this.duracao = duracao;
    }

    public void setLikes(int likes) {
        this.likes = likes;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setResol(int resol) {
        this.resol = resol;
    }

    public void setComentario(String comentario) {
        this.comentario = comentario;
    }

    public String toString(Youtube youtube)
    {
        return "Nome: "+this.nome+"\nCont: "+this.cont+"\nData: "+this.data+"\nResol: "+this.resol+"\nDuracao: "+this.duracao+"\nComentario: "+this.comentario+"\nLikes: "+this.likes+"\nDislikes: "+this.dislikes;
    }

    public void insereComentario(String comentario)
    {
        this.comentario = comentario;
    }
    /*
    public long qtsDiasDepois()
    {
        int dia = this.data.getDayofMonth();
        int mes = this.data.getMonthValue;
        int ano = this.data.getYear();
    }
    */
    public void thumbsUp()
    {
        this.likes++;
    }

    public String processa()
    {
        return this.toString();
    }
}