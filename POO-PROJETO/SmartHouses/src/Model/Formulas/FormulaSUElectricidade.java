package Model.Formulas;

public class FormulaSUElectricidade implements FormulaEnergia {
    public String getId(){return "SUElectricidade";}
    public double calculo(double base, double imposto, double consumoDispositivo, double multiplicador) {
        return (base+imposto)*consumoDispositivo*multiplicador;
    }
    public FormulaEnergia clone()
    {
    	return new FormulaSUElectricidade();
    }
}
