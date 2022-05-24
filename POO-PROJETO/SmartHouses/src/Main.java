import Model.SmartHouses;

public class Main {
    public static void main(String[] args) {
        SmartHouses smartHouses = new SmartHouses();
        //Map<String, Model.Formulas.FormulaEnergia> formulas= new HashMap<>();


      /*  try{
            smartHouses.parser("Model.SmartHouses/src/logs.txt");
        } catch (Model.Exceptions.LinhaException msg) {
            System.out.println("Nao foi possivel carregar a aplicação.");
        }*/
        //System.out.println(smartHouses.casasTostring());
        //System.out.println(smartHouses.getCasas().get("casa119"));
        UI ui = new UI(smartHouses);

        //ui.executeMenu(formulas);
        ui.executeMenu();

    }



}