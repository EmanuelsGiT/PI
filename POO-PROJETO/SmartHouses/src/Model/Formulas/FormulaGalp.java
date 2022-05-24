package Model.Formulas;

public class FormulaGalp implements FormulaEnergia {
    public String getId(){return "Galp";}
    public double calculo(double base, double imposto, double consumoDispositivo, double multiplicador) {
        return base+imposto+(consumoDispositivo*multiplicador);
    }
    public FormulaEnergia clone()
    {
    	return new FormulaGalp();
    }
}
