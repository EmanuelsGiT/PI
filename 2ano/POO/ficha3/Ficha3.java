public class Ficha3 
{
    public static void main(String[] args)
    {
        Circulo circulo1 = new Circulo(1,1,1);
        Circulo circulo2 = new Circulo(2,2,2);

        Circulo circulo3 = new Circulo(circulo1);

        Circulo circulo4 = circulo1.clone();

        Telemovel tele = new Telemovel();

        if(tele.existeEspaco(10))
            System.out.println("Há espaço no telemovel!");
        else
            System.out.println("Não há espaço no telemovel!");


    }
}
