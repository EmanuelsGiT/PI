import java.util.Iterator;
import java.util.Map;
import java.util.stream.Collectors;

public class TurmaMap
{

    private Map<String,Aluno> turma;
    private String nome;


    public TurmaMap()
    {
        this.nome = "PL8";
        this.turma = new HashMap<>();
    }

    public TurmaMap(String nome, Map<String,Aluno> turma)
    {
        this.nome = nome;
        // Iterador Externo com ForEach pelas chaves

        this.turma =new HashMap<>();
        for (String chave: turma.keySet())
        {
            this.turma.put(chave,turma.get(chave).clone());
        }

        // Iterador Externo com ForEach pelas EntrySet
        this.turma = new HashMap<>();
        for (Map.Entry<String,Aluno> entry: turma.entrySet())
        {
            this.turma.put(entry.getKey(),entry.getValue().clone());
        }

        // Iterador Interno por stream()
        this.turma = new HashMap<>();

        // com agregacao
        this.turma = turma.entrySet().stream().collect(Collectors.toMap(Map.Entry::getKey,Map.Entry::getValue));

        // com composicao
        this.turma = turma.entrySet().stream().collect(Collectors.toMap(entry -> entry.getKey(),entry -> entry.getValue().clone()));
    }   

    public TurmaMap(TurmaMap umaTurma)
    {
        //
    }

    public boolean existeAluno(String numero)
    {
        return this.turma.containKey(numero);
    }

    public Set<Aluno> ordenaTurma()
    {
        return this.turma.values().stream().map(Aluno::clone).collect(Collectors.toSet());
    }

    public Set<Aluno> ordenaCriterio()
    {
        ComparadorAlunos comparadorAlunos = new ComparadorAlunos();
        Set<Aluno> turma_ordenada = new TreeSet<>(comparadorAlunos);


        Iterator<Aluno> iterator = this.turma.values().iterator();
        while (iterator.hasNext())
        {
            turma_ordenada.add(iterator.next().clone());
        }

        return turma_ordenada;
    }
}