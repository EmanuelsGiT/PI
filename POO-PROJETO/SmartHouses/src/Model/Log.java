package Model;

import java.time.LocalDateTime;

public class Log {
    private LocalDateTime dia;
    private Boolean mode; // true se o dispositivo está ligado

    public Log()
    {
        this.dia = null;
        this.mode = false;
    }

    public Log(LocalDateTime dia, Boolean mode)
    {
        this.dia = dia;
        this.mode = mode;
    }

    public Log(Log l)
    {
        this.mode = l.getMode();
        this.dia = l.getDia();
    }

    public LocalDateTime getDia() {
        return this.dia;
    }

    public void setDia(LocalDateTime dia) {
        this.dia = dia;
    }

    public Boolean getMode() {
        return this.mode;
    }

    public boolean equals(Object o){
        if(o==this) return true;
        if(o==null || o.getClass()!=this.getClass()) return false;
        Log l = (Log) o;
        return this.dia.equals(l.getDia()) &&
                this.mode == l.getMode();
    }

    public Log clone() {
        return new Log(this);
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("\tDia: ").append(this.dia).append("; ")
                .append("\tEstá ligado?: ").append(this.mode).append("; ");
        return sb.toString();
    }

}