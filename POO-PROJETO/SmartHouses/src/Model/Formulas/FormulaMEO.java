package Model.Formulas;

public class FormulaMEO implements FormulaEnergia {
    public String getId(){return "MEO";}

    public double calculo(double base, double imposto, double consumoDispositivo, double multiplicador) {
        return (base+imposto+consumoDispositivo)*multiplicador;
    }
    public FormulaEnergia clone()
    {
    	return new FormulaMEO();
    }
}
