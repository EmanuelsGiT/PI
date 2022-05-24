package Model;

public class SmartBulb extends SmartDevice{
    public enum Mode
    {
        COLD,
        WARM,
        NEUTRAL,
    }
    public static Mode fromString(String x) {
        switch(x) {
            case "Cold":
                return Mode.COLD;
            case "Warm":
                return Mode.WARM;
            case "Neutral":
                return Mode.NEUTRAL;
        }
        return null;
    }
    private Mode mode;

    private int dimensao;


    private static final double vfixo = 0.70;
    private static final double factorWarm = 1.5 ;
    private static final double factorCold = 1.1;
    private static final double factorNeutral = 1.0;

    private static final double cneutral = vfixo + factorNeutral; //consumo neutral
    private static final double cwarm = vfixo + factorWarm;
    private static final double ccold = vfixo + factorCold;


    //public SmartBulb(String id)
    //{
    //    super(id);
    //    this.dimensao = 5;
    //}
    public SmartBulb(String id,String intensidade,boolean modo, int dim,double consumoBase){
        super(id,modo,consumoBase);
        this.mode = fromString(intensidade);
        this.dimensao = dim;
    }
    public SmartBulb(String id,String intensidade, int dim,double consumoBase){
        super(id,consumoBase);
        this.mode = fromString(intensidade);
        this.dimensao = dim;
    }

    public SmartBulb(SmartBulb smartBulb){
        super(smartBulb);
        this.mode = smartBulb.getMode();
        this.dimensao = smartBulb.getDimensao();
    }

    public int getDimensao() {
        return this.dimensao;
    }

    public void setDimensao(int dimensao) {
        this.dimensao = dimensao;
    }

    public Mode getMode() {
        return this.mode;
    }

    public void setMode(Mode mode) {
        this.mode = mode;
    }

    public void turnOFFlamp(){
        turnOff();
        if(this.getModo()) {
            if (this.mode == Mode.COLD) {
                calculaCold();
            }
            if (this.mode == Mode.WARM) {
                calculaWarm();
            }
            if (this.mode == Mode.NEUTRAL) {
                calculaNeutral();
            }
        }
    }

    public void turnOnLamp(){
        turnOn();
    }

    public void changetoCold(){
        if(!getModo()) turnOn();
        if (this.mode == Mode.WARM) {
            calculaWarm();
        }
        if (this.mode == Mode.NEUTRAL) {
            calculaNeutral();
        }
        this.mode = Mode.COLD;
    }

    public void changetoWarm(){
        if (this.mode == Mode.COLD) {
            calculaCold();
        }
        if (this.mode == Mode.NEUTRAL) {
            calculaNeutral();
        }
        this.mode = Mode.WARM;
    }

    public void changetoNeutral(){
        if (this.mode == Mode.WARM) {
            calculaWarm();
        }
        if (this.mode == Mode.COLD) {
            calculaCold();
        }
        this.mode = Mode.NEUTRAL;
    }

    //consumo total acumulado
    public double calculaCold(){
        return 4 * cwarm;
    }
    //consumo total acumulado
    public double calculaWarm(){
        return 1 * ccold;
    }
    //consumo total acumulado
    public double calculaNeutral(){
        return 2 * cneutral;
    }
    /*
        //consumo desde a última vez que se desligou a lampada
        public double consumoAtual() {
            double atual = 0;
            if (this.tonalidade == 2) atual = getPeriodoConsumo() * this.cwarm;
            else if (this.tonalidade == 0) atual =  getPeriodoConsumo() * this.ccold;
            else if (this.tonalidade == 1) atual = getPeriodoConsumo() * this.cneutral;
            return atual;
        }
    */
    public double consumoDiario(){
        // consumo total : mede os consumos anteriores
        // consumoAtual : mede o consumo atual
        double total=0;
        if(this.mode==Mode.WARM) {
            calculaWarm();
            total = calculaWarm();
        }
        else if(this.mode==Mode.COLD) {
            total = calculaCold();
        }
        else{
                total = calculaNeutral();
        }
        return total;
    }

    public static SmartBulb parseSmartBulb(String line){
        String[] parte = line.split(",");
        return new SmartBulb(parte[3],parte[0],Integer.parseInt(parte[1]),Double.parseDouble(parte[2]));
    }
//logs: Model.SmartBulb:Neutral,7,9.35,bulb3,2022-03-29 07:38:27,2022-05-31 20:23:44,false
    //    public Model.SmartBulb(String id,String intensidade, boolean modo , int dim,LocalDateTime timeon ,LocalDateTime timeoff){


    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(super.toString());
        sb.append("\tModo: ").append(this.mode).append("; ")
                .append("\tDimensao: ").append(this.dimensao).append("; ");
        return sb.toString();
    }

    public boolean equals(Object o) {
        if (this==o) return true;
        if ((o == null) || (this.getClass() != o.getClass())) return false;
        if (!super.equals(o)) return false;
        SmartBulb s = (SmartBulb) o;
        return  s.getMode() == this.mode &&
                s.getDimensao() == this.dimensao;
    }

    public SmartDevice clone(){
        return new SmartBulb(this);
    }

}
