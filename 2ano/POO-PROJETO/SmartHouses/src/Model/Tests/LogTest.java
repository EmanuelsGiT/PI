package Model.Tests;
import Model.Log;
import java.time.LocalDateTime;
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;


public class LogTest 
{
    public LogTest()
    {}

    @org.junit.jupiter.api.BeforeEach
    public void setUp()
    {}

    @org.junit.jupiter.api.AfterEach
    public void tearDown()
    {}

    @Test
    public void testConstrutor()
    {
        Log log = new Log();
        assertNotNull(log);
        log = new Log(LocalDateTime.of(2022,3,25,15,45),false);
        assertNotNull(log);
        Log log2 = new Log(log);
        assertNotNull(log2);
    }

    @Test
    public void testGetDia()
    {
        Log log = new Log();
        assertNull(log.getDia());
        log = new Log(LocalDateTime.of(2022,3,25,15,45),false);
        assertEquals(LocalDateTime.of(2022,3,25,15,45),log.getDia());
        Log log2 = new Log(log);
        assertEquals(LocalDateTime.of(2022,3,25,15,45),log2.getDia());
    }

    @Test
    public void testSetDia()
    {
        Log log = new Log();
        log.setDia(LocalDateTime.of(2022,3,25,15,45));
        assertEquals(LocalDateTime.of(2022,3,25,15,45),log.getDia());
        log = new Log(LocalDateTime.of(2023,4,26,16,46),false);
        log.setDia(LocalDateTime.of(2022,3,25,15,45));
        assertEquals(LocalDateTime.of(2022,3,25,15,45),log.getDia());
        Log log2 = new Log(log);
        log.setDia(LocalDateTime.of(2022,3,25,15,45));
        assertEquals(LocalDateTime.of(2022,3,25,15,45),log2.getDia());
    }

    @Test
    public void testGetMode()
    {
        Log log = new Log();
        assertNull(log.getMode());
        log = new Log(LocalDateTime.of(2023,4,26,16,46),false);
        assertEquals(false,log.getMode());
        Log log2 = new Log(log);
        assertEquals(false,log2.getMode());
    }

    @Test
    public void testEquals()
    {
        Log log = new Log();
        Log log2 = new Log(LocalDateTime.of(2023,4,26,16,46),false);
        if(log.equals(log2)) System.out.print("Equals Errado");
        if(!log.equals(log)) System.out.print("Equals Errado");
    }

    @Test
    public void testToString() 
    {
        Log log = new Log();
        assertEquals("Dia: ; Está ligado?: ",log.toString());
        log = new Log(LocalDateTime.of(2022,3,25,15,45),false);
        assertEquals("Dia: 2022-3-25 15:45; Está ligado?: false",log.toString());
    }
    
    @Test
    public void testClone() 
    {
        Log log = new Log(LocalDateTime.of(2023,4,26,16,46),false);
        if(!log.equals(log.clone())) System.out.print("Clone Errado");
    }
}

