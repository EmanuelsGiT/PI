package Model.Formulas;

public class FormulaEDA implements FormulaEnergia {
    public String getId(){return "EDA";}
    public double calculo(double base, double imposto, double consumoDispositivo, double multiplicador) {
        return (base*consumoDispositivo)+(multiplicador*imposto*0.1);
    }
    public FormulaEnergia clone()
    {
    	return new FormulaEDA();
    }
}
