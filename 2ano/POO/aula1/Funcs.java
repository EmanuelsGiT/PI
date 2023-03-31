public class Funcs
{
    public double celsiusParaFarenheit(double graus)
    {
        return ((graus*1.8)+32);
    }

    public int maximoNumeros(int a, int b)
    {
        if (a>b)
        {
            System.out.println("O maior é "+a);
            return a;
        }
        else
        {
            System.out.println("O maior é "+b);
            return b;
        }
    }

    public String criaDescriacaoConta(String nome, double saldo)
    {
        return "Nome :"+nome+"\nSaldo: "+saldo;
    }

    public double eurosParaLibras(double valor, double taxaConversao)
    {
        int now = valor * taxaConversao;
        System.out.println("Novo Valor: "+now);
        return now;
    }

    public double media(int a, int b)
    {
        int media = (a+b)/2;
        if (a<b)
        {
            System.out.println("Menor: "+a+"\nMaior: "+b+"Media: "+media);
        }
        else
        {
            System.out.println("Menor: "+b+"\nMaior: "+a+"Media: "+media);
        }
        return media;
    }

    public long factorial(int num)
    {
        int fact=num;
        for(int i = num-1; i>0;i--)
            fact = fact*i;

        return fact;
    }

}
