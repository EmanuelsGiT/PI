import java.time.LocalDate;
import java.util.Scanner;

public class Diadasemana
{
    public static void main(String [] args)
    {
        diaSemana();
    }

    public static void diaSemana()
    {
        Scanner sc = new Scanner(System.in);
        System.out.println("Insira dia mes e ano");
        int dia = sc.nextInt();
        int mes = sc.nextInt();
        int ano = sc.nextInt();

        //a.i
        int dias = (ano-1900)*365;

        //a.ii
        dias += (ano-1900)/4;

        //a.iii
        LocalDate date = LocalDate.of(ano,mes,dia);
        boolean bissexto = date.isLeapYear();

        if (bissexto && (mes == 1 || mes == 2))
        {
            dias = dias-1;
        }

        //a.iv
        dias = dias +date.getDayOfYear();

        //b
        dias = dias%7;
        System.out.println("O dia da semana é " +dias);

        switch (dias)
        {
            case 0:
                System.out.println("O dia da semana é Domingo.");
                break;

            case 1:
                System.out.println("O dia da semana é Segunda.");
                break;
            case 2:
                System.out.println("O dia da semana é Terça.");
                break;
            case 3:
                System.out.println("O dia da semana é Quarta.");
                break;
            case 4:
                System.out.println("O dia da semana é Quinta.");
                break;
            case 5:
                System.out.println("O dia da semana é Sexta.");
                break;
            case 6:
                System.out.println("O dia da semana é Sábado.");
                break;
            default:
                System.out.println("Algo correu mal.");
                break;
        }
    }
}
