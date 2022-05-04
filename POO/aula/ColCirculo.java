import java.util.ArrayList;

public class ColCirculo 
{
    private Array.List<Circulo> colecao;

    public ColCirculo()
    {
        this.colecao = new ArrayList<Circulo>();
    }

    public ColCirculo(ArrayList<Circulo> colecao)
    {   
        this.colecao = new ArrayList<Circulo>(colecao);
    }

    public ColCirculo(ColCirculo colCirculo)
    {
        //this.colecao = new ArrayList<Circulo>();
        this.setColecao(colCirculo.getColecao);
    }   

    public ArrayList<Circulo> getColecao()
    {
        return new ArrayList<Colecao>(this.colecao);
    }

    public void setColecao(ArrayList<Circulo> colecao)
    {
        //this.colecao = new ArrayList<Circulo>(colecao);
        this.colecao = new ArrayList<Circulo>();
        for (Circulo aux: colecao)
            this.colecao.add(aux);
    }

    public int qualEoIndice(Circulo circulo)
    {
        return this.colecao.indexOf(circulo);
    }

    public void remove(Circulo circulo)
    {
        if(this.colecao.contains(circulo))
            this.colecao.remove(circulo);
    }
}
