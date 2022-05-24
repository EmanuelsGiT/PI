import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.Scanner;
import Model.*;

public class Menu {
    private List<String> opcoes;
    private int opcao;

    public Menu(List<String> opcoes) {
        setOpcoes(opcoes);
        this.opcao =0;
    }

    public void executa() {
        do {
            showMenu();
            this.opcao = lerOpcao();
        } while (this.opcao == -1);
    }

    private void showMenu() {
        System.out.println(" ***********************************-SmartHouses-*************************************** ");
        for (int i=0; i<this.opcoes.size(); i++) {
            if(i != (this.opcoes.size()-1)) {
                System.out.print("| * ");
                System.out.print(i + 1);
                System.out.print(" -");
                System.out.print(this.opcoes.get(i));
            }
            if(i == (this.opcoes.size()-1)){
                System.out.print("| * ");
                System.out.print(i + 1);
                System.out.print(" -");
                System.out.print(this.opcoes.get(i));
                System.out.print("\n_______________________________________________________________________________________\n");
            }
        }
    }

    private int lerOpcao() {
        int op;
        Scanner is = new Scanner(System.in);

        System.out.print("Digite a opção: ");
        try {
            String line = is.nextLine();
            op = Integer.parseInt(line);
        }
        catch (NumberFormatException e) { // Não foi inscrito um int
            op = -1;
        }
        catch (NoSuchElementException f)
        {
            op = -1;
        }
        if (op<0 || op>this.opcoes.size()) {
            System.out.println("Opção Inválida!!!");
            op = -1;
        }
        return op;
    }


    public ArrayList<String> getOpcoes() {
        return new ArrayList<>(this.opcoes);
    }

    public void setOpcoes(List<String> b) {
        this.opcoes = new ArrayList<>(b);
    }

    public int getOpcao() {
        return this.opcao;
    }

    public void setOpcao(int i) {
        this.opcao = i;
    }

}