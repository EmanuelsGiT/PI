package Model.Formulas;

public class FormulaMuon implements FormulaEnergia {
    public String getId(){return "Muon";}
    public double calculo(double base, double imposto, double consumoDispositivo, double multiplicador) {
        return base+imposto*consumoDispositivo+multiplicador;
    }
    public FormulaEnergia clone()
    {
    	return new FormulaMuon();
    }
}
