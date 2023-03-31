package Model.Formulas;

public class FormulaEnat implements FormulaEnergia {
    public String getId(){return "Enat";}
    public double calculo(double base, double imposto, double consumoDispositivo, double multiplicador) {
        return ((base-1)+consumoDispositivo)+multiplicador*imposto;
    }
    public FormulaEnergia clone()
    {
    	return new FormulaEnat();
    }
}
