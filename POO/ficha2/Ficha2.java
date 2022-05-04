import java.util.Arrays;
import java.util.Scanner;

public class Ficha2
{
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Insira a dimensao do array: ");
        int dimensao = scanner.nextInt();

        Funcs aula = new Funcs(dimensao,scanner);
        
        //int resultado = aula.populaArrayEncontraMin();
        //System.out.println("O mínimo é "+resultado);

        System.out.println("O mínimo é "+aula.populaArrayEncontraMin());

        System.out.println("Insrira os dois indices: ");
        int idx1 = scanner.nextInt();
        int idx2 = scanner.nextInt();

        System.out.println("O array pretendido é "+ Arrays.toString(aula.exercicio1b(idx1,idx2)));

        int[] array1 = {2,54,21,65};
        int[] array2 = {65,21,3,7};

        aula.comuns(array1,array2);
        
        int[][] array = new int[2][2];

        aula.ex2a(array);

        aula.ex2b(array);

        aula.ex2c(array);

        aula.ex2d(array);

        //aula.insereData();

        scanner.close();
    }
}

/*
    javac Ficha2.java Funcs.java // compila
    java Aula2                   // executa
*/
