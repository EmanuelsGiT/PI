package Model.Tests;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import static org.junit.jupiter.api.Assertions.*;
import java.time.temporal.ChronoUnit;
import org.junit.jupiter.api.Test;
import Model.*;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class CasaInteligenteTest 
{
    public CasaInteligenteTest()
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
        CasaInteligente casa = new CasaInteligente ("123","Emanuel",913913913,"Rua 25 de Abril","EDP");
        assertNotNull(casa);
        CasaInteligente casa2 = new CasaInteligente(casa);
        assertNotNull(casa2);
    }

    @Test
    public void testGetIdFornecedor() 
    {
        CasaInteligente casa = new CasaInteligente ("123","Emanuel",913913913,"Rua 25 de Abril","EDP");
        assertEquals("EDP",casa.getIdFornecedor());
    }

    @Test
    public void testSetIdFornecedor() 
    {
        CasaInteligente casa = new CasaInteligente ("123","Emanuel",913913913,"Rua 25 de Abril","EDP");
        casa.setIdFornecedor("Iberdrola");
        assertEquals("Iberdrola",casa.getIdFornecedor());
    }

    @Test
    public void testSetMorada() 
    {
        CasaInteligente casa = new CasaInteligente ("123","Emanuel",913913913,"Rua 25 de Abril","EDP");
        casa.setMorada("Rua 26 de maio");
        assertEquals("Rua 26 de maio",casa.getMorada());
    }

    @Test
    public void testSetProprietario() 
    {
        CasaInteligente casa = new CasaInteligente ("123","Emanuel",913913913,"Rua 25 de Abril","EDP");
        casa.setProprietario("Rita");
        assertEquals("Rita",casa.getProprietario());
    }

    @Test
    public void testSetIdHome() 
    {
        CasaInteligente casa = new CasaInteligente ("123","Emanuel",913913913,"Rua 25 de Abril","EDP");
        casa.setIdHome("456");
        assertEquals("456",casa.getIdHome());
    }

    @Test
    public void testSetNIF() 
    {
        CasaInteligente casa = new CasaInteligente ("123","Emanuel",913913913,"Rua 25 de Abril","EDP");
        casa.setNIF(123456789);
        assertEquals(123456789,casa.getNIF());
    }

    @Test
    public void testGetMorada() 
    {
        CasaInteligente casa = new CasaInteligente ("123","Emanuel",913913913,"Rua 25 de Abril","EDP");
        assertEquals("Rua 25 de Abril",casa.getMorada());
    }

    @Test
    public void testGetProprietario() 
    {
        CasaInteligente casa = new CasaInteligente ("123","Emanuel",913913913,"Rua 25 de Abril","EDP");
        assertEquals("Emanuel",casa.getProprietario());
    }

    @Test
    public void testGetNIF() 
    {
        CasaInteligente casa = new CasaInteligente ("123","Emanuel",913913913,"Rua 25 de Abril","EDP");
        assertEquals(913913913,casa.getNIF());
    }

    @Test
    public void testGetIdHome() 
    {
        CasaInteligente casa = new CasaInteligente ("123","Emanuel",913913913,"Rua 25 de Abril","EDP");
        assertEquals("123",casa.getIdHome());
    }

    @Test
    public void testeGetDevices()
    {
        SmartDevice n = new SmartCamera("cam",true,"1920x1880",1,10);
        SmartDevice n4 = new SmartCamera("cam4",true,"1920x1880",1,10);
        SmartDevice n2 = new SmartCamera("cam2",true,"1920x1880",1,10);
        SmartDevice n3 = new SmartCamera("cam3",true,"1920x1880",1,10);

        Map<String, SmartDevice> s = new HashMap<>();
        s.put(n.getID(),n.clone());
        s.put(n2.getID(),n2.clone());
        s.put(n3.getID(),n3.clone());
        s.put(n4.getID(),n4.clone());
        
        CasaInteligente casa = new CasaInteligente ("123","Emanuel",913913913,"Rua 25 de Abril","EDP");
        casa.setDevices(s);
        
        assertEquals(s,casa.getDevices());
    }

    @Test
    public void testGetFaturas()
    {
        Fatura fat = new Fatura(5.0,"fatura1",LocalDateTime.of(2022,3,25,15,45),LocalDateTime.of(2022,3,25,15,45),"Rua 25 Abril",123456789,"EDP",10.0);
        Fatura fat2 = new Fatura(5.0,"fatura2",LocalDateTime.of(2022,3,25,15,45),LocalDateTime.of(2022,3,25,15,45),"Rua 26 Abril",897654321,"EDP",20.0);
        
        Map<String, Fatura> faturas = new HashMap<>();
        faturas.put(fat.getIdFatura(),fat.clone());
        faturas.put(fat2.getIdFatura(),fat2.clone());
        
        CasaInteligente casa = new CasaInteligente ("123","Emanuel",913913913,"Rua 25 de Abril","EDP");
        casa.setFaturas(faturas);

        assertEquals(faturas,casa.getFaturas());
    }
    
    @Test
    public void testSetDevices()
    {
        SmartDevice n = new SmartCamera("cam",true,"1920x1880",1,10);
        SmartDevice n2 = new SmartCamera("cam2",true,"1920x1880",1,10);

        Map<String, SmartDevice> s = new HashMap<>();
        s.put(n.getID(),n.clone());
        s.put(n2.getID(),n2.clone());
        
        CasaInteligente casa = new CasaInteligente ("123","Emanuel",913913913,"Rua 25 de Abril","EDP");
        casa.setDevices(s);
        
        assertEquals(s,casa.getDevices());
    }

    @Test
    public void testSetFaturas()
    {
        Fatura fat = new Fatura(5.0,"fatura1",LocalDateTime.of(2022,3,25,15,45),LocalDateTime.of(2022,3,25,15,45),"Rua 25 Abril",123456789,"EDP",10.0);
        Fatura fat2 = new Fatura(5.0,"fatura2",LocalDateTime.of(2022,3,25,15,45),LocalDateTime.of(2022,3,25,15,45),"Rua 26 Abril",897654321,"EDP",20.0);
        
        Map<String, Fatura> faturas = new HashMap<>();
        faturas.put(fat.getIdFatura(),fat.clone());
        faturas.put(fat2.getIdFatura(),fat2.clone());
        
        CasaInteligente casa = new CasaInteligente ("123","Emanuel",913913913,"Rua 25 de Abril","EDP");
        casa.setFaturas(faturas);

        assertEquals(faturas,casa.getFaturas());
    }

    @Test
    public void testGetLocations()
    {
        Fatura fat = new Fatura(5.0,"fatura1",LocalDateTime.of(2022,3,25,15,45),LocalDateTime.of(2022,3,25,15,45),"Rua 25 Abril",123456789,"EDP",10.0);
        Fatura fat2 = new Fatura(5.0,"fatura2",LocalDateTime.of(2022,3,25,15,45),LocalDateTime.of(2022,3,25,15,45),"Rua 26 Abril",897654321,"EDP",20.0);
        
        Map<String, Fatura> faturas = new HashMap<>();
        faturas.put(fat.getIdFatura(),fat.clone());
        faturas.put(fat2.getIdFatura(),fat2.clone());
        
        CasaInteligente casa = new CasaInteligente ("123","Emanuel",913913913,"Rua 25 de Abril","EDP");
        casa.setFaturas(faturas);

        assertEquals(faturas,casa.getFaturas());
    }

    @Test
    public void testGetLogs()
    {
        Log log = new Log(LocalDateTime.of(2023,4,26,16,46),false);
        Log log2 = new Log(LocalDateTime.of(2023,4,26,16,46),false);

        Map<String, List<Log>> logs = new HashMap<>();
        //logs.put(log.getIdLog(),log.clone());
        //logs.put(log2.getIdLog(),log2.clone());
        
        CasaInteligente casa = new CasaInteligente ("123","Emanuel",913913913,"Rua 25 de Abril","EDP");
        casa.setLogs(logs);

        assertEquals(logs,casa.getLogs());  
    }

    @Test
    public void testSetLogs()
    {
        Log log = new Log(LocalDateTime.of(2022,3,25,15,45),true);
        Log log2 = new Log(LocalDateTime.of(2023,4,26,16,46),false);

        Map<String, List<Log>> logs = new HashMap<>();
        //logs.put(log.getIdLog(),log.clone());
        //logs.put(log2.getIdLog(),log2.clone());
        
        CasaInteligente casa = new CasaInteligente ("123","Emanuel",913913913,"Rua 25 de Abril","EDP");
        casa.setLogs(logs);

        assertEquals(logs,casa.getLogs());  
    }


    @Test
    public void testSetDeviceOn()
    {
        SmartDevice n = new SmartCamera("cam",true,"1920x1880",1,10);
        SmartDevice n2 = new SmartCamera("cam2",true,"1920x1880",1,10);

        Map<String, SmartDevice> s = new HashMap<>();
        s.put(n.getID(),n.clone());
        s.put(n2.getID(),n2.clone());
        
        CasaInteligente casa = new CasaInteligente ("123","Emanuel",913913913,"Rua 25 de Abril","EDP");
        casa.setDevices(s);
        
        assertEquals(s,casa.getDevices());
    }

    @Test
    public void testSetDeviceOff()
    {
    }

    @Test
    public void testSetAll()
    {
    }

    @Test
    public void testSetAlldivision()
    {
    }

    @Test
    public void testConsumoTotalHome()
    {
    }

    @Test
    public void testNumeroDispositivos()
    {
    }

    @Test
    public void testNumeroDispositivosDivisao()
    {
    }

    @Test
    public void testExistsDeviceHome() 
    {
    }

    @Test
    public void testChecksAllrooms()
    {
    }

    @Test
    public void testSetDevice() 
    {
    }

    @Test
    public void testAddRoom() 
    {
    }

    @Test
    public void testHasRoom() 
    {
    }

    @Test
    public void testAddToRoom() 
    {
    }

    @Test
    public void testRoomHasDevice() 
    {
    }

    @Test
    public void testRemoveDispositivoemDivisao()
    {
    }

    @Test
    public void testRemoveDevicesFromRoom()
    {
    }

    @Test
    public void testEquals()
    {
    }

    @Test
    public void testToString()
    {
    }

    @Test
    public void testParseCasa()
    {
    }

    @Test
    public void testClone()
    {
    }

    @Test
    public void testAddDevice()
    {
    }

    @Test
    public void testGetDevice()
    {
    }

    @Test
    public void testAddFatura()
    {
    }

    @Test
    public void testHasFatura()
    {
    }

    @Test
    public void testRemoveFatura()
    {
    }

    @Test
    public void testLigadoPeriodoTempo()
    {
    }

    @Test
    public void testHasLog() 
    {
    }

    @Test
    public void testHasLogByDay() 
    {
    }

    @Test
    public void testAddLog()
    {
    }

    @Test
    public void testRemoveLog()
    {
    }

    @Test
    public void testAddAllLogs()
    {
    }

    @Test
    public void testAddAllLogsAllDays()
    {
    }

    @Test
    public void testGetAllLogs()
    {
    }

    @Test
    public void testNumberDevicesOn()
    {
    }

    @Test
    public void testConsumoAllDevicesDia()
    {
    }

}
