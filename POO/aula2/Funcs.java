import java.util.Arrays;
import java.util.Scanner;

public class Funcs
{
    /*
    int [] valores;

    public Ficha2(int dimensao)
    {
        valores = new int[dimensao];
    }
    */

    int [] valores;
    Scanner scanner;
    public Funcs(int dimensao, Scanner sc)
    {
        valores = new int[dimensao];
        scanner = sc;
    }

    public int populaArrayEncontraMin()
    {

        System.out.println("Insira " +valores.length+ " inteiros");

        int minimo = Integer.MAX_VALUE;

        for (int i=0; i< valores.length; i++)
        {
            valores[i] = scanner.nextInt();
            if (minimo>valores[i])
                minimo = valores[i];
        }

        System.out.println("O array é: "+ Arrays.toString(valores));

        return minimo;
    }

    public int[] exercicio1b(int idx1, int idx2)
    {
        int dimensao = Math.abs(idx2-idx1);
        int[] resultado = new int[dimensao+2];

        int minimo = Math.min(idx1,idx2);

        System.arraycopy(valores, minimo, resultado, 0, dimensao);

        return resultado;
    }

    public boolean vercom( int value, int[] array)
    {
        for(int elem: array)
            if (value==elem) return true;

        return false;
    }

    public void comuns(int[] array1, int[] array2)
    {
        int len = Math.min(array1.length, array2.length);
        int i=0;
        int[] novo = new int[len];

        for (int elem: array1)
            if (vercom(elem,array2))
            {
                novo[i] = elem;
                i++;
            }

        System.out.println("O novo array com os elementos em comun é: "+ Arrays.toString(novo));
    }

    public void ex2a(int[][] array)
    {
        System.out.println("Digite a nota dos alunos: ");
        //for(int[] aluno: array)
        for(int j =0;j<array.length;j++)
        {
            //System.out.printf("%d\n",aluno);
            int i = 1;
            //for (int uc : aluno)
            for (int k=0;k<array.length;k++)
            {
                System.out.printf("Insira a nota da %d UC: ", i);
                //uc = scanner.nextInt();
                array[j][k] = scanner.nextInt();
                i++;
            }
        }
    }

    public void ex2b(int[][] array)
    {
        System.out.println("Digite a UC a calcular: ");
        int choice = scanner.nextInt();
        int soma = 0;
        for (int[] ints : array)
        {
            soma += ints[choice - 1];
        }
        System.out.println("A soma das notas da "+choice+" UC é "+soma+".");
    }

    public void ex2c(int[][] array)
    {
        System.out.println("Digite o numero do aluno: ");
        int choice = scanner.nextInt();
        int soma = 0;
        for(int i=0;i<array.length;i++)
            soma += array[choice-1][i];

        System.out.println("A média é "+soma/array.length);
    }

    public void ex2d(int[][] array)
    {
        System.out.println("Digite a UC a calcular: ");
        int choice = scanner.nextInt();
        int soma = 0;
        for (int[] ints : array)
        {
            soma += ints[choice - 1];
        }
        System.out.println("A média é "+soma/array.length);
    }

    /*
    public void insereData(LocalDate data)
    {

    }
    */
}
