package Model.Tests;
import Model.SmartCamera;
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class SmartCameraTest
{

    public SmartCameraTest()
    {
    }


    @BeforeEach
    public void setUp()
    {
    }


    @AfterEach
    public void tearDown()
    {
    }

    @Test
    public void testConstructor()
    {
        SmartCamera smartCam = new SmartCamera("cam","(1280x720)",3,4);
        assertNotNull(smartCam);
        smartCam = new SmartCamera("cam",false,"(1280x720)",3,4.5);
        assertNotNull(smartCam);
        smartCam = new SmartCamera(smartCam);
        assertNotNull(smartCam);
    }

    @Test
    public void testGetResolucao()
    {
        SmartCamera smartCam = new SmartCamera("cam","(1280x720)",3,4);
        assertEquals("(1280x720)", smartCam.getResolucao());
        smartCam = new SmartCamera("cam",false,"(1280x720)",3,4);
        assertEquals("(1280x720)", smartCam.getResolucao());
        SmartCamera smartCam2 = new SmartCamera(smartCam);
        assertEquals("(1280x720)", smartCam.getResolucao());
        smartCam = new SmartCamera(smartCam2);
        assertEquals("(1280x720)", smartCam.getResolucao());
    }

    @Test
    public void testSetResolucao()
    {
        SmartCamera cam = new SmartCamera("cam","(1280x720)",3,4);
        cam.setResolucao("(1920x1080)");
        assertEquals("(1920x1080)", cam.getResolucao());
    }

    @Test
    public void testGetTamanho()
    {
        SmartCamera smartCam = new SmartCamera("cam","(1280x720)",3,4);
        assertEquals(3, smartCam.getTamanho());
        smartCam = new SmartCamera("cam",false,"(1280x720)",-3,4.5);
        assertEquals(-3, smartCam.getTamanho());
        SmartCamera smartCam2 = new SmartCamera(smartCam);
        assertEquals(-3, smartCam.getTamanho());
        smartCam = new SmartCamera(smartCam2);
        assertEquals(-3, smartCam.getTamanho());
    }

    @Test
    public void testSetTamanho()
    {
        SmartCamera cam = new SmartCamera("cam","(1280x720)",3,4);
        cam.setTamanho(3);
        assertEquals(3, cam.getTamanho());
        for (int i=0; i<25; i++) cam.setTamanho(i);
        assertEquals(24, cam.getTamanho());
    }

    @Test
    public void testTurnCameraOn()
    {
        SmartCamera cam = new SmartCamera("cam","(1280x720)",3,4);
        cam.turnCameraOn();
        assertTrue(cam.getModo());
    }

    @Test
    public void testTurnCameraOff()
    {
        SmartCamera cam = new SmartCamera("cam",true,"(1280x720)",3,4.5);
        cam.turnCameraOff();
        assertFalse(cam.getModo());
    }

    @Test
    public void testConsumoDiario()
    {
        SmartCamera cam = new SmartCamera("cam",true,"(1280x720)",3,4.5);
        assertEquals(13.5, cam.consumoDiario());
        cam = new SmartCamera("cam","(1280x720)",3,4.5);
        assertEquals(2000000, cam.consumoDiario());
        cam = new SmartCamera(cam);
        assertEquals(2000000, cam.consumoDiario());
    }
    
    @Test
    public void testToString()
    {
        SmartCamera cam = new SmartCamera("cam","(1280x720)",3,4.5);
        assertEquals("Tamanho: 3Mb; Resolução: (1280x720)px; ID: cam; Modo: ; Consumo Base: 4.5;", cam.toString());

        cam = new SmartCamera("cam",true,"(1280x720)",3,4.5);
        assertEquals("Tamanho: 3Mb; Resolução: (1280x720)px; ID: cam; Modo: true; Consumo Base: 4.5;", cam.toString());
        SmartCamera camera = new SmartCamera(cam);
        assertEquals("Tamanho: 3Mb; Resolução: (1280x720)px; ID: cam; Modo: true; Consumo Base: 4.5;", camera.toString());
    }

    @Test
    public void testEquals()
    {
        SmartCamera cam = new SmartCamera("cam",true,"(1280x720)",3,4.5);
        SmartCamera cam2 = new SmartCamera("cam2",true,"(1280x720)",3,4.5);
        if(cam.equals(cam2)) System.out.print("Equals Errado");
        if(!cam.equals(cam)) System.out.print("Equals Errado");
    }
    
    @Test
    public void testClone()
    {
        SmartCamera cam = new SmartCamera("cam",true,"(1280x720)",3,4.5);
        if(!cam.equals(cam.clone())) System.out.print("Clone Errado");
    }

}




