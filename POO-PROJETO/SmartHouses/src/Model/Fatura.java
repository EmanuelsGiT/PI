package Model;

import java.text.DecimalFormat;
import java.time.LocalDateTime;

public class Fatura {
    private String idFatura;
    private LocalDateTime inicio;
    private LocalDateTime fim;
    private double valor;
    private int NIF;
    private String morada;
    private String idFornecedor;
    private double consumo;


    public Fatura()
    {
        this.idFatura = "";
        this.morada="";
        this.NIF= 0;
        this.idFornecedor = "";
        this.valor=0;
        this.fim = null;
        this.inicio = null;
    }

    public Fatura(double consumo, String idFatura,LocalDateTime init, LocalDateTime finit, String morada, int NIF, String idFornecedor, double valor)
    {
        this.idFatura = idFatura;
        this.morada = morada;
        this.idFornecedor = idFornecedor;
        this.inicio = init;
        this.fim = finit;
        this.valor = valor;
        this.NIF = NIF;
        this.consumo = consumo;
    }

    public Fatura(Fatura f)
    {
        this.idFatura = f.getIdFatura();
        this.morada = f.getMorada();
        this.idFornecedor = f.getIdFornecedor();
        this.fim = f.getFim();
        this.inicio = f.getInicio();
        this.valor = f.getValor();
        this.NIF = f.getNIF();
        this.consumo = f.getConsumo();
    }

    public void setConsumo(double consumo)
    {
        this.consumo = consumo;
    }

    public void setIdFatura(String id)
    {
        this.idFatura = id;
    }

    public void setValor(double valor)
    {
        this.valor = valor;
    }

    public void setMorada(String morada)
    {
        this.morada = morada;
    }

    public void setIdFornecedor(String id)
    {
        this.idFornecedor = id;
    }

    public void setInicio(LocalDateTime init)
    {
        this.inicio = init;
    }

    public void setFim(LocalDateTime fim)
    {
        this.fim = fim;
    }

    public void setNIF(int NIF)
    {
        this.NIF = NIF;
    }

    public double getConsumo()
    {
        return this.consumo;
    }

    public double getValor()
    {
        return this.valor;
    }

    public int getNIF()
    {
        return this.NIF;
    }

    public String getIdFatura()
    {
        return this.idFatura;
    }

    public String getMorada()
    {
        return this.morada;
    }

    public String getIdFornecedor()
    {
        return this.idFornecedor;
    }

    public LocalDateTime getInicio()
    {
        return this.inicio;
    }

    public LocalDateTime getFim()
    {
        return this.fim;
    }

    public String toString(){
        StringBuilder sb = new StringBuilder();
        DecimalFormat formato = new DecimalFormat("#.##");
        sb.append("\nIdFatura: " + this.getIdFatura())
            .append("\nIdFornecedor: " + this.getIdFornecedor())
            .append("\nNIF: " + this.getNIF())
            .append("\nConsumo: " + formato.format(this.getConsumo()))
            .append("\nValor: " + formato.format(this.getValor()));
        return sb.toString();
    }

    public boolean equals(Object o){
        if(o==this) return true;
        else if(o==null || o.getClass()!=this.getClass()) return false;
        Fatura sd = (Fatura) o;
        return this.idFatura.equals(sd.getIdFatura()) &&
                this.idFornecedor.equals(sd.getIdFornecedor()) &&
                this.fim.equals(sd.getFim()) &&
                this.inicio.equals(sd.getInicio()) &&
                this.valor==sd.getValor() &&
                this.morada.equals(sd.morada) &&
                this.NIF==sd.NIF &&
                this.consumo == sd.consumo;
    }

    public Fatura clone()
    {
        return new Fatura(this);
    }

}