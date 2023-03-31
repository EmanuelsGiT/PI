package Model.Tests;
import Model.SmartBulb;
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

public class SmartBulbTest
{
    public SmartBulbTest()
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
        SmartBulb smartBulb = new SmartBulb("bulb1","NEUTRAL",3,10.0);
        assertNotNull(smartBulb);
        smartBulb = new SmartBulb("bulb1","NEUTRAL",false,3,10.0);
        assertNotNull(smartBulb);
        smartBulb = new SmartBulb(smartBulb);
        assertNotNull(smartBulb);
    }

    @Test
    public void testGetDimensao() 
    {
        SmartBulb smartBulb = new SmartBulb("bulb1","NEUTRAL",false,3,10.0);
        Assertions.assertEquals(3, smartBulb.getDimensao());
        smartBulb = new SmartBulb("bulb1","NEUTRAL",false,-3,10.0);
        Assertions.assertEquals(-3, smartBulb.getDimensao());
        smartBulb = new SmartBulb("bulb1","NEUTRAL",false,50,10.0);
        Assertions.assertEquals(50, smartBulb.getDimensao());
        smartBulb = new SmartBulb("bulb1","NEUTRAL",3,10.0);
        Assertions.assertEquals(5, smartBulb.getDimensao());
    }
// done
    @Test
    public void testSetDimensao() 
    {
        SmartBulb bulb = new SmartBulb("bulb1","NEUTRAL",false,3,10.0);
        bulb.setDimensao(3);
        Assertions.assertEquals(3, bulb.getDimensao());
        for (int i=0; i<25; i++) bulb.setDimensao(i);
        Assertions.assertEquals(24, bulb.getDimensao());
    }

    @Test
    public void testGetMode() 
    {
        SmartBulb smartBulb = new SmartBulb("bulb1","NEUTRAL",false,3,10.0);
        Assertions.assertEquals(SmartBulb.fromString("NEUTRAL"), smartBulb.getMode());
        smartBulb = new SmartBulb("bulb1","COLD",false,3,10.0);
        Assertions.assertEquals(SmartBulb.fromString("COLD"), smartBulb.getMode());
        smartBulb = new SmartBulb("bulb1","WARM",false,3,10.0);
        Assertions.assertEquals(SmartBulb.fromString("WARM"), smartBulb.getMode());
    }

    @Test
    public void testSetMode() 
    {
        SmartBulb bulb = new SmartBulb("bulb1","COLD",false,3,10.0);
        bulb.setMode(SmartBulb.Mode.NEUTRAL);
        Assertions.assertEquals(SmartBulb.Mode.NEUTRAL, bulb.getMode());
        bulb.setMode(SmartBulb.Mode.COLD);
        Assertions.assertEquals(SmartBulb.Mode.COLD, bulb.getMode());
        bulb.setMode(SmartBulb.Mode.WARM);
        Assertions.assertEquals(SmartBulb.Mode.WARM, bulb.getMode());

    }

    @Test
    public void testTurnOFFlamp()
    {
        SmartBulb smartBulb = new SmartBulb("bulb1","NEUTRAL",true,3,10.0);
        smartBulb.turnOFFlamp();
        Assertions.assertFalse(smartBulb.getModo());
    }

    @Test
    public void testTurnOnLamp() 
    {
        SmartBulb smartBulb = new SmartBulb("bulb1","NEUTRAL",false,3,10.0);
        smartBulb.turnOnLamp();
        Assertions.assertTrue(smartBulb.getModo());
    }

    @Test
    public void testChangetoCold()
    {
        SmartBulb smartBulb = new SmartBulb("bulb1","NEUTRAL",false,3,10.0);
        smartBulb.changetoCold();
        Assertions.assertEquals(SmartBulb.Mode.COLD, smartBulb.getMode());
    }

    @Test
    public void testChangetoWarm()
    {
        SmartBulb smartBulb = new SmartBulb("bulb1","NEUTRAL",false,3,10.0);
        smartBulb.changetoWarm();
        Assertions.assertEquals(SmartBulb.Mode.WARM, smartBulb.getMode());
    }

    @Test
    public void testChangetoNeutral()
    {
        SmartBulb smartBulb = new SmartBulb("bulb1","COLD",false,3,10.0);
        smartBulb.changetoNeutral();
        Assertions.assertEquals(SmartBulb.Mode.NEUTRAL, smartBulb.getMode());
    }
   @Test
    private void testCalculaCold()
    {
        SmartBulb smartBulb = new SmartBulb("bulb1","COLD",false,3,10.0);
        assertEquals(1.8,smartBulb.calculaCold());
    }

    @Test
    private void testCalculaWarm()
    {
        SmartBulb smartBulb = new SmartBulb("bulb1","COLD",false,3,10.0);
        assertEquals(8.8,smartBulb.calculaWarm());
    }

    @Test
    private void testCalculaNeutral()
    {
        SmartBulb smartBulb = new SmartBulb("bulb1","COLD",false,3,10.0);
        assertEquals(3.4,smartBulb.calculaNeutral());
    }

    @Test
    public void testConsumoDiario()
    {
        SmartBulb smartBulb = new SmartBulb("bulb1","COLD",false,3,10.0);
        assertEquals(8.8,smartBulb.consumoDiario());
        smartBulb = new SmartBulb("bulb1","WARM",false,3,10.0);
        assertEquals(1.8,smartBulb.consumoDiario());
        smartBulb = new SmartBulb("bulb1","NEUTRAL",false,3,10.0);
        assertEquals(3.4,smartBulb.consumoDiario());
    }

    @Test
    public void testToString() {
        SmartBulb bulb = new SmartBulb("bulb1","NEUTRAL",3,10.0);
        Assertions.assertEquals("Modo: Neutral; Dimensão: 3; Consumo Base: 10.0",bulb.toString());
        
        bulb = new SmartBulb("bulb1","NEUTRAL",false,3,10.0);
        Assertions.assertEquals("Modo: Neutral; Dimensão: 3; Consumo Base: 10.0",bulb.toString());

        SmartBulb bul = new SmartBulb(bulb);
        Assertions.assertEquals("Modo: Neutral; Dimensão: 3; Consumo Base: 10.0",bul.toString());
    }

    @Test
    public void testEquals()
    {
        SmartBulb bulb = new SmartBulb("bulb1","NEUTRAL",false,3,10.0);
        SmartBulb bulb2 = new SmartBulb("bulb2","NEUTRAL",false,3,10.0);
        if(bulb.equals(bulb2)) System.out.print("Equals Errado");
        if(!bulb.equals(bulb)) System.out.print("Equals Errado");
    }
    
    @Test
    public void testeClone()
    {
        SmartBulb bulb = new SmartBulb("bulb1","NEUTRAL",false,3,10.0);
        if(!bulb.equals(bulb.clone())) System.out.print("Clone Errado");
    }
}
