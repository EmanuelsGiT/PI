import java.util.Scanner;

public class SomaDatas
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        System.out.println("Insira a 1ª data (dia horas minutos segundos): ");
        int dia = sc.nextInt();
        int hora = sc.nextInt();
        int min = sc.nextInt();
        int seg = sc.nextInt();
        System.out.println("Insira a 2ª data (dia horas minutos segundos): ");
        int dia2 = sc.nextInt();
        int hora2 = sc.nextInt();
        int min2 = sc.nextInt();
        int seg2 = sc.nextInt();
        somaData(dia,hora,min,seg,dia2,hora2,min2,seg2);
        sc.close();

    }

    public static void somaData(int dia, int hora, int min, int seg, int dia2, int hora2, int min2, int seg2)
    {
        int sdia = dia + dia2;
        int shora = hora + hora2;
        int smin = min + min2;
        int sseg = seg + seg2;
        System.out.printf("%d D %d H %d M %d S\n", sdia, shora, smin, sseg);

        System.out.println("End!");
    }
}
