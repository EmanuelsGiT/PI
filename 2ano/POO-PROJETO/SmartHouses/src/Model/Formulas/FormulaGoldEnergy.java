package Model.Formulas;

public class FormulaGoldEnergy implements FormulaEnergia {
    public String getId(){return "GoldEnergy";}
    public double calculo(double base, double imposto, double consumoDispositivo, double multiplicador) {
        return (base*consumoDispositivo+multiplicador)*imposto;
    }
    public FormulaEnergia clone()
    {
    	return new FormulaGoldEnergy();
    }
}
