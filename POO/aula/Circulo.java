public class Circulo
{
    private Ponto centro;
    private double raio;

    public Circulo()
    {
        this.centro = new Ponto();
        this.raio = 0.0;
    }

    public Circulo (Ponto centro,double raio)
    {
        this.centro = new Ponto(centro);
        this.raio = raio;
    }

    public Circulo (Circulo umCirculo)
    {
        this.centro = new Ponto(umCirculo.getCentro());
        this.raio = umCirculo.getRaio();
    }

    public Ponto getCentro()
    {
        return new Ponto(centro);
    }

    public void setCentro(Ponto centro)
    {
        this.centro = new Ponto(centro);
    }

    public double getRaio()
    {
        return this.raio;
    } 

    public void setRaio(double raio)
    {
        this.raio = raio;
    }

    public String toString()
    {
        return "Circulo: Ponto"+this.centro.toString+"Raio: "+this.raio.toString;
    } 

    public Circulo clone()
    {
        return new Circulo(this);
    }

    public boolean equals(Object object)
    {
        if (this==object)
            return true;
        
        if (object == null || this.getClass() != object.getClass())
            return false;

            Circulo c = (Circulo) object;
            //return (this.centro == c.getCentro() && this.raio == c.getRaio());

            return (this.centro.equals(c.getCentro()) && this.raio == c.getRaio());
    }
}
