import java.util.Comprator;

public class ComparadorAlunos implements Comparator<Aluno>
{
    @Override
    public int compare(Aluno o1, Aluno o2)
    {
        return o1.compareTo(o2);
    }
}