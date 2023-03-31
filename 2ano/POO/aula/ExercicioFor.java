import java.util.Scanner;

public class ExercicioFor
{
    public static void main(String []args)
    {
        soma();
    }

    public static void soma()
    {
        Scanner sc = new Scanner(System.in);
        int soma = 0;

        for(int i=0;i<10;i++)
        {
            System.out.println(("Insira o próximo inteiro: "));
            int valor = sc.nextInt();
            soma += valor;
        }
        System.out.println("A soma total é " +soma);
        sc.close();
    }
}
