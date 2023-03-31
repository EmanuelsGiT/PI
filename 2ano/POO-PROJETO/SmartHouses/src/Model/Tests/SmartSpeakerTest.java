package Model.Tests;
import Model.SmartSpeaker;
import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

public class SmartSpeakerTest {

    @org.junit.jupiter.api.BeforeEach
    public void setUp()
    {}

    @org.junit.jupiter.api.AfterEach
    public void tearDown()
    {}

    @Test
    public void testConstructor() 
    {
        SmartSpeaker smartSpeaker = new SmartSpeaker("speaker1",50,"JBL","Radio Comercial",5.0);
        assertNotNull(smartSpeaker);
        smartSpeaker = new SmartSpeaker("speaker1",false,50,"JBL","Radio Comercial",5.0);
        assertNotNull(smartSpeaker);
        SmartSpeaker smartSpeaker2 = new SmartSpeaker(smartSpeaker);
        assertNotNull(smartSpeaker2);
    }

    @Test
    public void testVolumeUp() 
    {
        SmartSpeaker smartSpeaker = new SmartSpeaker("speaker1",50,"JBL","Radio Comercial",5.0);
        smartSpeaker.volumeUp();
        Assertions.assertEquals(1, smartSpeaker.getVolume());
        smartSpeaker = new SmartSpeaker("speaker1",false,50,"JBL","Radio Comercial",5.0);
        smartSpeaker.volumeUp();
        Assertions.assertEquals(51, smartSpeaker.getVolume());
        smartSpeaker = new SmartSpeaker("speaker1",false,100,"JBL","Radio Comercial",5.0);
        smartSpeaker.volumeUp();
        Assertions.assertEquals(100, smartSpeaker.getVolume());
    }

    @Test
    public void testVolumeDown() 
    {
        SmartSpeaker smartSpeaker = new SmartSpeaker("speaker1",50,"JBL","Radio Comercial",5.0);
        smartSpeaker.volumeDown();
        Assertions.assertEquals(0, smartSpeaker.getVolume());
        smartSpeaker = new SmartSpeaker("speaker1",false,50,"JBL","Radio Comercial",5.0);
        smartSpeaker.volumeDown();
        Assertions.assertEquals(49, smartSpeaker.getVolume());
    }

    @Test
    public void testGetVolume() 
    {
        SmartSpeaker speaker = new SmartSpeaker("speaker1",false,50,"JBL","Radio Comercial",5.0);
        Assertions.assertEquals(50, speaker.getVolume());
    }

    @Test
    public void testSetVolume() 
    {
        SmartSpeaker speaker = new SmartSpeaker("speaker1",false,0,"JBL","Radio Comercial",5.0);
        speaker.setVolume(50);
        Assertions.assertEquals(50, speaker.getVolume());
        speaker.setVolume(120);
        Assertions.assertEquals(100, speaker.getVolume());
        speaker.setVolume(-5);
        Assertions.assertEquals(0, speaker.getVolume());
    }

    @Test
    public void testGetMarca() 
    {
        SmartSpeaker speaker = new SmartSpeaker("speaker1",false,0,"JBL","Radio Comercial",5.0);
        Assertions.assertEquals("JBL", speaker.getMarca());
    }

    @Test
    public void testSetMarca() 
    {
        SmartSpeaker speaker = new SmartSpeaker("speaker1",false,0,"","Radio Comercial",5.0);
        speaker.setMarca("JBL");
        Assertions.assertEquals("JBL", speaker.getMarca());
    }

    @Test
    public void testGetChannel() 
    {
        SmartSpeaker speaker = new SmartSpeaker("speaker1",false,0,"JBL","Radio Comercial",5.0);
        Assertions.assertEquals("Radio Comercial", speaker.getChannel());
    }

    @Test
    public void testSetChannel() 
    {
        SmartSpeaker speaker = new SmartSpeaker("speaker1",false,0,"JBL","",5.0);
        speaker.setChannel("Radio Comercial");
        Assertions.assertEquals("Radio Comercial", speaker.getChannel());
    }

    @Test
    public void testTurnSpeakerOFF()
    {
        SmartSpeaker speaker = new SmartSpeaker("speaker1",true,0,"JBL","Radio Comercial",5.0);
        speaker.turnSpeakerOff();
        Assertions.assertFalse(speaker.getModo());
    }

    @Test
    public void testTurnSpeakerOn() 
    {
        SmartSpeaker speaker = new SmartSpeaker("speaker1",true,0,"JBL","Radio Comercial",5.0);
        speaker.turnSpeakerOn();
        Assertions.assertTrue(speaker.getModo());
    }

    @Test
    public void testToString() {
        SmartSpeaker speaker = new SmartSpeaker("speaker1",50,"JBL","Radio Comercial",5.0);
        Assertions.assertEquals("ID: Speaker1; On: true; Consumo base: 5.0; Volume: 0, Marca: JBL, Canal: Radio Comercial",speaker.toString());
        
        speaker = new SmartSpeaker("speaker1",true,0,"JBL","Radio Comercial",5.0);
        Assertions.assertEquals("ID: Speaker1; On: true; Consumo base: 5.0; Volume: 0, Marca: JBL, Canal: Radio Comercial",speaker.toString());
        
        SmartSpeaker speaker2 = new SmartSpeaker(speaker);
        Assertions.assertEquals("ID: Speaker1; On: true; Consumo base: 5.0; Volume: 0, Marca: JBL, Canal: Radio Comercial",speaker2.toString());
    }

    @Test
    public void testEquals()
    {
        SmartSpeaker speaker = new SmartSpeaker("speaker1",true,0,"JBL","Radio Comercial",5.0);
        SmartSpeaker speaker2 = new SmartSpeaker("speaker2",true,0,"JBL","Radio Comercial",5.0);
        if(speaker.equals(speaker2)) System.out.print("Equals Errado");
        if(speaker2.equals(speaker)) System.out.print("Equals Errado");
    }
    
    @Test
    public void testeClone()
    {
        SmartSpeaker speaker = new SmartSpeaker("speaker1",true,0,"JBL","Radio Comercial",5.0);
        if(!speaker.equals(speaker.clone())) System.out.print("Clone Errado");
    }
}
