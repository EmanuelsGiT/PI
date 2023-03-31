package Model;

public class SmartSpeaker extends SmartDevice {
    public static final int MAX = 100; //volume máximo

    private int volume;
    private String marca;
    private String channel;

    public SmartSpeaker(String id, boolean modo, int vol, String marca, String canal, double consumoBase) {
        super(id, modo, consumoBase);
        this.volume = vol;
        this.channel = canal;
        this.marca = marca;
    }
    public SmartSpeaker(String id, int vol, String marca, String canal, double consumoBase) {
        super(id, consumoBase);
        this.volume = vol;
        this.channel = canal;
        this.marca = marca;
    }

    public SmartSpeaker(SmartSpeaker ss) {
        super(ss);
        this.volume = ss.getVolume();
        this.channel = ss.getChannel();
        this.marca = ss.getMarca();
    }

    public void volumeUp() {
        if (this.volume < MAX) this.volume++;
    }

    public void volumeDown() {
        if (this.volume > 0) this.volume--;
    }

    public int getVolume(){
        return this.volume;
    }

    public String getMarca(){
        return this.marca;
    }

    public String getChannel(){
        return this.channel;
    }

    public void setChannel(String c){
        this.channel = c;
    }

    public void setMarca(String m){
        this.marca = m;
    }

    public void setVolume(int v){
        if(v>=MAX) this.volume= MAX;
        else if(v<=0) this.volume =0;
        else this.volume=v;
    }

    public double consumoDiario() {
        return (this.getConsumoBase()*this.getVolume())/100;
    }

    public void turnSpeakerOn(){
        turnOn();
    }

    public void turnSpeakerOff(){
        turnOff();
    }

    public static SmartSpeaker parseSmartSpeaker(String line){
        String[] parte = line.split(",");
        return new SmartSpeaker(parte[4],Integer.parseInt(parte[0]),parte[2],parte[1],Double.parseDouble(parte[3]));
    }
    //Model.SmartSpeaker:2,Radio Renascenca,LG,5.54,speaker1,2022-04-11 09:23:48,2022-05-30 06:33:00,false
    //    public Model.SmartSpeaker(String id, boolean modo, int vol, String marca, String canal, LocalDateTime timeon, LocalDateTime timeoff) {


    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append(super.toString());
        sb.append("\tVolume: ").append(this.volume).append("; ")
            .append("\tMarca: ").append(this.marca).append("; ")
            .append("\tCanal: ").append(this.channel).append("\n");
        return sb.toString();
    }

    public boolean equals(Object o) {
        if (this==o) return true;
        if ((o == null) || (this.getClass() != o.getClass())) return false;
        SmartSpeaker s = (SmartSpeaker) o;
        return super.equals(o) && this.volume==s.getVolume()
                && this.channel.equals(s.getChannel())
                && this.marca.equals(s.getMarca());
    }

    public SmartDevice clone(){
        return new SmartSpeaker(this);
    }

}