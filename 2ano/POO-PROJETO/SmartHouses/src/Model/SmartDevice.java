package Model;

public abstract class SmartDevice {

    private String id;
    private boolean modo;//ON: TRUE | OFF: FALSE
    private double consumoBase;

    // usado no parser
    public SmartDevice(String id, double consumoBase)
    {
        this.id = id;
        this.modo=false;
        this.consumoBase = consumoBase;
    }

    public SmartDevice(String id, boolean modo, double consumoBase)
    {
        this.id = id;
        this.modo=modo;
        this.consumoBase = consumoBase;
    }

    public SmartDevice(SmartDevice s) {
        this.id = s.getID();
        this.modo = s.getModo();
        setConsumoBase(s.getConsumoBase());
    }

    public void turnOn(){
        this.modo = true;
    }

    public void turnOff() {
        this.modo = false;
    }

    public double getConsumoBase() {
        return consumoBase;
    }

    public void setConsumoBase(double consumoBase) {
        this.consumoBase = consumoBase;
    }

    public boolean getModo() {
        return this.modo;
    }

    public void setModo(boolean b) {
        this.modo = b;
    }

    public String getID() {
        return this.id;
    }

    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("ID: ").append(this.id).append("\n")
                .append("\tOn: ").append(this.modo).append(";\n")
                .append("\tConsumo Base: ").append(this.consumoBase).append(";\n");
        return sb.toString();
    }

    public boolean equals(Object o){
        if(o==this) return true;
        else if(o==null || o.getClass()!=this.getClass()) return false;
        SmartDevice sd = (SmartDevice) o;
        return this.id.equals(sd.getID());
    }

    public abstract SmartDevice clone();

    public abstract double consumoDiario();
}
