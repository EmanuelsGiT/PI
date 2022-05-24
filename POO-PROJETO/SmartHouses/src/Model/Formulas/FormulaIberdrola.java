package Model.Formulas;

public class FormulaIberdrola implements FormulaEnergia {
    public String getId(){return "Iberdrola";}
    public double calculo(double base, double imposto, double consumoDispositivo, double multiplicador) {
        return base*imposto*(consumoDispositivo+(1-multiplicador));
    }
    public FormulaEnergia clone()
    {
    	return new FormulaIberdrola();
    }
}
