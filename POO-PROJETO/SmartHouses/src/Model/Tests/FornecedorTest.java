package Model.Tests;
import Model.Formulas.*;
import Model.Fornecedor;
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

public class FornecedorTest {

    public FornecedorTest()
    {}

    @org.junit.jupiter.api.BeforeEach
    public void setUp()
    {}

    @org.junit.jupiter.api.AfterEach
    public void tearDown()
    {}

    @Test
    public void testConstructor() 
    {
        FormulaEDP form =  new FormulaEDP();

        Fornecedor forn= new Fornecedor("EDP",10);
        assertNotNull(forn);
        forn= new Fornecedor(10,"EDP",form);
        assertNotNull(forn);
        Fornecedor forn2= new Fornecedor(forn);
        assertNotNull(forn2);
    }

    @Test
    public void testSetId()
    {
        FormulaEDP form =  new FormulaEDP();

        Fornecedor forn= new Fornecedor(10,"EDP",form);
        forn.setId("b");
        assertEquals("b", forn.getId());
    }
    
    @Test
    public void testSetImposto()
    {
        FormulaEDP form =  new FormulaEDP();

        Fornecedor forn= new Fornecedor(10,"EDP",form);
        forn.setImposto(3);
        assertEquals(3, forn.getImposto());
        for (int i=0; i<25; i++) forn.setImposto(i);
        assertEquals(24, forn.getImposto());
    }

    @Test
    public void testGetId()
    {
        FormulaEDP form =  new FormulaEDP();

        Fornecedor forn = new Fornecedor(10, "EDP",form);
        assertEquals("EDP", forn.getId());
        forn = new Fornecedor(forn);
        assertEquals("EDP", forn.getId());
        forn = new Fornecedor(1, "",form);
        assertEquals("", forn.getId());
    }

    @Test
    public void testGetImposto() 
    {
        FormulaEDP form =  new FormulaEDP();

        Fornecedor forn= new Fornecedor(10,"EDP",form);
        assertEquals(2, forn.getImposto());
        forn= new Fornecedor(-2,"EDP",form);
        assertEquals(-2, forn.getImposto());
        forn= new Fornecedor(forn);
        assertEquals(-2, forn.getImposto());
    }

    @Test
    public void testSetFormula()
    {
        FormulaEDP form =  new FormulaEDP();

        Fornecedor forne = new Fornecedor(10,"EDP",form);
        forne.setFormula(form);
        assertEquals(form,forne.getFormula());

    }

    @Test
    public void testEquals()
    {
        FormulaEDP form =  new FormulaEDP();

        Fornecedor forn = new Fornecedor(10,"EDP",form);
        Fornecedor forn2 = new Fornecedor(15,"Iberdrola",form);
        if(forn.equals(forn2)) System.out.print("Equals Errado");
        if(!forn.equals(forn)) System.out.print("Equals Errado");
    }
    
    @Test
    public void testToString()
    {
        FormulaEDP form =  new FormulaEDP();

        Fornecedor forn = new Fornecedor(10,"EDP",form);
        assertEquals("Id: EDP; Imposto:10;",forn.toString());
    }
    
    @Test
    public void testClone()
    {
        FormulaEDP form =  new FormulaEDP();

        Fornecedor forn = new Fornecedor(10,"EDP",form);
        if(!forn.equals(forn.clone())) System.out.print("Clone Errado");
    }

}
