import java.util.Scanner;
//import java.time.LocalDate ex 4

public class Exercicio1
{
    public static void main(String[] args)
    {
        System.out.println("Insira dois inteiros");
        maior();
    }

    /*public static void maior()
    {
        Scanner sc = new Scanner(System.in);
        int num1 = sc.nextInt();
        int num2 = sc.nextInt();

        if (num1>num2)
        {
            System.out.println("O maior é " +num1);
        }
        else
        {
            System.out.println("O maior é " +num2);
        }
    }*/

    public static void maior()
    {
        Scanner sc = new Scanner(System.in);
        int num1 = sc.nextInt();
        int num2 = sc.nextInt();

        int maior = Math.max(num1,num2);
        System.out.println("O maior é "+maior);
    }
}
