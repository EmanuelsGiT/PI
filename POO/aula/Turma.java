import java.util.ArrayList;
import java.util.Comparator;
import java.util.Iterator;
import java.util.List;
import java.util.stream.Collectors;
import java.util.Set;
import java.util.TreeSet;

public class Turma 
{
    private ArrayList<Aluno> turma;
    private String nome;

    public Turma()
    {
        this.turma = new ArrayList<>();
        this.nome = "PL8";
    }

    public Turma(ArrayList<Aluno>, String nome)
    {
        this.nome = nome;
        this.turma = new ArrayList<>();
        

        //Iterador externo com for each
        /*
        for (Aluno iteracao: turma)
        {
            this.turma.add(iteracao.clone());
        }
        */

        //iterador externo com iterator
        
        /*
        Iterator<E> iterator = turma.iterator();
        while(iterator.hasNext())
        {
            Aluno aux = iterator.next();
            this.turma.add(aux.clone());
        }
        */

        //iterador interno 

        this.turma = turma.stream().map(Aluno::clone).collect(Collectors.toList());
    }

    

    public boolean existeAluno(String numero)
    {
        /*
        for(Aluno iteracao: this.turma)
        {
            if(iteracao.getNumero().equals(numero)) 
                return true;
        }
        */

        return this.turma.stream().anyMatch(iteracao -> iteracao.getNumero().equals(numero));
    }

    public Set<Aluno> ordenaTurma()
    {
        Set<Aluno> tuma_ordenada = new TreeSet<>();
        Iterator<Aluno> iterator = this.turma.iterator();
        while(iterator.hasNext())
        {
            tuma_ordenada.add(iterator.next().clone());
        }

        return tuma_ordenada;
    }

    public Set<Aluno> ordenaCriterio()
    {
        ComparadorAlunos comparadorAlunos = new ComparadorAlunos();
        Set<Aluno> turma_ordenada = new TreeSet<>(comparadorAlunos);

        Iterator<Aluno> iterator = this.turma.iterator();
        while(iterator.hasNext())
        {
            tuma_ordenada.add(iterator.next().clone());
        }

        turma_ordenada = this.tuma.stream().map(Aluno::clone).collect(Collectors-toSet());
        retunr tuma_ordenada;

    }

    public void setTurma(ArrayList<Aluno> turma)
    {
        this.turma = new ArrayList<>();
        this.turma = turma.stream().map(Aluno::clone).collect(Collectors.toList());

    }

    public ArrayList<Aluno> getTurma()
    {
        return (ArrayList<Aluno>)this.turma.stream().map(Aluno::clone).collect(Collectors.toList());
    }

    public void setNome(String nome)
    {
        
    }
}