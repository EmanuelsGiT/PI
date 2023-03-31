package com.company;
/*public class OlaMundo
{
    public static void main(String[] args)
    {
        System.out.print("Ola Mundo");
    }
}
*/
// java olamundo.java
// .out == olamundo.class

public class OlaMundo
{
    public static void main(String[] args)
    {
        String retorno = geraSaudacao("Emanuel");
        System.out.println(retorno);
    }

    public static String geraSaudacao(String nome)
    {
        String saudacao = "Olá Mundo "+nome;
        return saudacao;
    }
}
/*
public class main
{

    final double pi = 3.1416;
    //declara uma constante
}*/