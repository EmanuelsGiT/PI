import java.util.ArrayList;
import java.util.*;

public class CasaInteligente
{
    private int idHome;
    private String morada;
    private List<Lampada> lamps;
    private String proprietario;
    private int NIF;

    public CasaInteligente()
    {
        this.morada = "";
        this.lamps = new ArrayList<>();
        this.proprietario = "";
    }

    public void addLampada(Lampada l)
    {
        this.casa.add(l);
    }

    public void ligaLampadaNormal(int index)
    {
        this.lamps.setModo = ON;
    }

    public void ligaLampadaEco(int index)
    {
        this.lamps(index).setModo = ECO;
    }

    public void qtEmEco()
    {
        //
    }

    public void removeLampada(int index)
    {
        //
    }

    public void ligaTodaEco()
    {
        //
    }

    public void ligaTodasMax()
    {
        //
    }

    public double consumoTotal()
    {
        return 0;
    }

    public Lampada maisGastadora()
    {
        return Lampada;
    }

    public Set<Lampada> podiumEconomia()
    {
        //
    }

    public void reset()
    {
        //
    }

}