import java.time.LocalDateTime;

public class fase1 
{
    public enum Ativ
    {
        Corrida,
        Canoagem,
        Abdominais
    }

    private int idade = nascimento.getYear() - LocalDate.now().getYear();

    private int id;
    private String [] descricao;
    private LocalDateTime data; 
    private int tmp; // minutos

    private Ativ atividade;

    private int distancia;
    private int altimetria;
    private String curso;
    private String embarcacao;
    private int velVento;
    private String dirVento;
    private int voltas;   

    //public int CaloriasCorrida = distancia ∗ peso ∗ tempo ∗ idade/50;
    //public int CaloriasCanoagem = distancia ∗ ventocontra ∗ tempo ∗ idade/4;
    //public int CaloriasAbdominais = tempo ∗ repeticoes ∗ 3/5;


    public boolean existeUtilizador(String email)
    public int quantos()
    public int quantos(String actividade, String email)
    public Utilizador getUtilizador(String email)
    public void adiciona(String email, Actividade act)
    public List<Actividade> getAllActividades()
    public void adiciona(String email, Set<Actividade>activs)
    public int tempoTotalUtilizador(String email)
    public Actvidade actividadeMaisExigente()
    public Utilizador utilizadorMaisActivo()
    public void actualizaDesportoFav()
}
