public class Aluno
{
    public class Aluno implements Comparable Aluno
    {
        
    }
    
    public int compareToAluno(Aluno a)
    {
        return this.getNome().compareTo(a.getNime());
    }
}