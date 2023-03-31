package Model.Formulas;

public class FormulaEnergiaSimples implements FormulaEnergia {
    public String getId(){return "EnergiaSimples";}
    public double calculo(double base, double imposto, double consumoDispositivo, double multiplicador) {
        return base+consumoDispositivo+(multiplicador*0.1)+imposto;
    }
    public FormulaEnergia clone()
    {
    	return new FormulaEnergiaSimples();
    }
}
