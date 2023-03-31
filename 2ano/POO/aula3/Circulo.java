public class Circulo
{
    private int x;
    private int y;
    private double raio;

    public Circulo()
    {
        this.x = 0;
        this.y = 0;
        this.raio = 0;
    }

    public Circulo(int x, int y, double raio)
    {
        this.x = x;
        this.y = y;
        this.raio = raio;
    }

    public Circulo(Circulo circulo)
    {
        this.x = circulo.getX();
        this.y = circulo.getY();
        this.raio = circulo.getRaio();
    }

    public int getX()
    {
        return this.x;
    }

    public int getY()
    {
        return this.y;
    }
    /**
     * Retorna o raio do circulo desta instancia
     * @return double com o valor do raio
     * */
    public double getRaio()
    {
        return this.raio;
    }

    public void setX(int x)
    {
        this.x = x;
    }

    public void setY(int y)
    {
        this.y = y;
    }

    public void setRaio(double raio)
    {
        this.raio = raio;
    }

    public String toString(Circulo circulo)
    {
        return "x: "+this.x+ " y: " + this.y + " raio: " + this.raio;
    }

    public Circulo clone()
    {
        return new Circulo(this);
    }

    public boolean equals(Object object)
    {
        if (this == object)
            return true;

        if (this == null || this != object)
            return false;

        Circulo circulo = (Circulo) object;
        if (this.x == circulo.getX() && this.y == circulo.getY() && this.raio == circulo.getRaio())
            return true;

        return false;
    }

    public void alteraCentro(int x, int y)
    {
        this.x = x;
        this.y = y;
    }

    public double calculaArea()
    {
        double area = Math.pow((Math.PI * this.raio),2);
        return area;
    }

    public double calculaPerimetro()
    {
        double perimetro = 2 * Math.PI * this.raio;
        return perimetro;
    }
}
