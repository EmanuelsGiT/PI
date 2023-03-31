package Model.Formulas;

public class FormulaEDP implements FormulaEnergia {
    public String getId(){return "EDP";}

    public double calculo(double base, double imposto, double consumoDispositivo, double multiplicador) {
        return base*imposto*(consumoDispositivo+multiplicador);
    }
    public FormulaEnergia clone()
    {
    	return new FormulaEDP();
    }
}
