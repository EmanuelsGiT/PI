package Model;

import Model.Exceptions.*;

import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;
import java.util.*;
import java.util.stream.Collectors;

public class CasaInteligente {

    private String idHome;
    private String morada;
    private String proprietario;
    private int NIF;
    private Map<String, SmartDevice> devices; // identificador -> Model.SmartDevice
    private Map<String, List<String>> locations; // Espaço -> Lista codigo dos devices
    private Map<String, List<Log>> logs; // identificador -> idDispositivo
    private Map<String, Fatura> faturas;
    private String idFornecedor;


    public CasaInteligente(String id,String proprietario,int NIF,String morada,String idFornecedor) {
        // initialise instance variables
        this.idHome = id;
        this.morada = morada;
        this.devices = new HashMap<>();
        this.locations = new HashMap<>();
        this.proprietario = proprietario;
        this.NIF = NIF;
        this.idFornecedor = idFornecedor;
        this.logs = new HashMap<>();
        this.faturas = new HashMap<>();
    }

    public CasaInteligente(String id, String morada, Map<String,SmartDevice> dv , Map<String, List<String>> espacos,int nif, String nome, String idFornecedor) {
        // initialise instance variables
        this.idHome = id;
        this.morada = morada;
        this.proprietario = nome;
        this.NIF = nif;
        this.idFornecedor = idFornecedor;
        setDevices(dv);
        setLocations(espacos);
        this.faturas = new HashMap<>();
        this.logs = new HashMap<>();
        setLogs(null);
    }

    public CasaInteligente(CasaInteligente ci) {
        // initialise instance variables
        this.idHome = ci.getIdHome();
        this.morada = ci.getMorada();
        this.proprietario = ci.getProprietario();
        this.NIF = ci.getNIF();
        this.idFornecedor = ci.getIdFornecedor();
        setDevices(ci.getDevices());
        setLocations(ci.getLocations());
        setFaturas(ci.getFaturas());
        setLogs(ci.getLogs());
    }

    public String getIdFornecedor() {
        return idFornecedor;
    }

    public void setIdFornecedor(String idFornecedor) {
        this.idFornecedor = idFornecedor;
    }

    public void setMorada(String morada) {
        this.morada = morada;
    }

    public void setProprietario(String proprietario) {
        this.proprietario = proprietario;
    }

    public void setIdHome(String idHome) {
        this.idHome = idHome;
    }

    public void setNIF(int NIF) {
        this.NIF = NIF;
    }

    public String getMorada() {
        return this.morada;
    }

    public String getProprietario() {
        return this.proprietario;
    }

    public int getNIF() {
        return this.NIF;
    }

    public String getIdHome() {
        return idHome;
    }

    public Map<String,SmartDevice> getDevices(){
        return this.devices.entrySet().stream().collect(Collectors.toMap(Map.Entry::getKey,(e)->e.getValue().clone()));
    }

    public Map<String,Fatura> getFaturas(){
        return this.faturas.entrySet().stream().collect(Collectors.toMap(Map.Entry::getKey,(e)->e.getValue().clone()));
    }
    
    public void setDevices(Map<String,SmartDevice> mdevices){
        this.devices = new HashMap<>();
        mdevices.forEach((String,SmartDevice)->this.devices.put(String,SmartDevice.clone()));
    }

    public void setFaturas(Map<String,Fatura> f){
        this.faturas = new HashMap<>();
        f.forEach((String,Fatura)->this.faturas.put(String,Fatura.clone()));
    }


    public Map<String,List<String>> getLocations(){
        return this.locations.entrySet().stream().collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    public Map<String,List<Log>> getLogs(){
        return this.logs.entrySet().stream().collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    public void setLogs(Map<String,List<Log>> ml){
        this.logs = new HashMap<>();
        ml.forEach((key,value)->this.logs.put(key, new ArrayList<>(value)));
    }

    public void setLocations(Map<String,List<String>> ml){
        this.locations = new HashMap<>();
        ml.forEach((key,value)->this.locations.put(key, new ArrayList<>(value)));
    }

    /*Ligar um dispositivo especifico*/
    public void setDeviceOn(String devCode) throws SmartDeviceNotExistsException {
        if(!this.existsDeviceHome(devCode)) throw new SmartDeviceNotExistsException ("O Model.SmartDevice com id " + devCode + " não existe");
        else this.devices.get(devCode).turnOn();
    }

    /*Desligar um dispositivo especifico*/
    public void setDeviceOff(String devCode) throws SmartDeviceNotExistsException {
        if(!this.existsDeviceHome(devCode)) throw new SmartDeviceNotExistsException ("O Model.SmartDevice com id " + devCode + " não existe");
        else this.devices.get(devCode).turnOff();
    }

    /*Desligar ou Ligar todos os dispositivos*/
    public void setallDevices(boolean b) {
        this.devices.values().forEach(a->a.setModo(b));
    }

    /*Desligar ou Ligar todos os dispositivos de uma divisao*/
    public void setAlldivision(boolean b,String divisao) throws SmartDeviceNotExistsException
    {
        for( String a :this.locations.get(divisao)){
            getDevice(a).setModo(b);
        }
    }

    public int numeroDispositivos(){
        return this.locations.entrySet().stream().mapToInt((e)->e.getValue().size()).sum();
    }

    public int numeroDispositivosDivisao(String divisao){
        return this.locations.get(divisao).size();
    }

    public boolean existsDeviceHome(String id) {
        return this.devices.containsKey(id);
    }

    public boolean checksAllrooms(String id){
        boolean exists=false;
        long num = this.locations.values().stream().filter((e)->e.contains(id)).count();
        if(num>0) exists= true;
        return exists;
    }

    public void setDevice(String s, boolean b) {
        this.devices.get(s).setModo(b);
    }

    public void addRoom(String s) {
        List<String> lista = new ArrayList<>();
        this.locations.put(s,lista);
    }

    public boolean hasRoom(String s) {
        return (this.locations.get(s) != null);
    }

    public void addToRoom (String division, String id) throws SmartDeviceAlreadyExistsException{
        if(!roomHasDevice(division, id)) this.locations.get(division).add(id);
        else throw new SmartDeviceAlreadyExistsException("O dispositivo já existe nesta divisão da casa");
    }

    public boolean hasDevice (String id) {
        return this.devices.containsKey(id);
    }

    public boolean roomHasDevice (String divisao, String id) {
        boolean exists = false;
        if (this.locations.containsKey(divisao)) {
            if(this.locations.get(divisao).contains(id)) exists = true;
        }
        return exists;
    }

    public void removeDevicesFromRoom(String idDevice){
        for(List<String> l : this.locations.values()){
            if(l.contains(idDevice)) l.remove(idDevice);
        }
    }

    public void addDeviceToRoom(String idDevice, String room)
    {
        this.removeDevicesFromRoom(idDevice);
        this.locations.get(room).add(idDevice);
    }

    public void removeDeviceFromHome(String idDevice)
    {
        this.devices.remove(idDevice);
    }


    public boolean equals(Object o){
        if(o==this) return true;
        if(o==null || o.getClass()!=this.getClass()) return false;
        CasaInteligente ci = (CasaInteligente) o;
        return this.locations.equals(ci.getLocations()) && this.devices.equals(ci.getDevices())
                && this.proprietario.equals(ci.getProprietario()) && this.NIF==ci.getNIF() && this.morada.equals(ci.getMorada()) && this.idFornecedor.equals(ci.getIdFornecedor());
    }

    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("\nID Home: ").append(this.idHome).append("\n")
                .append("Morada: ").append(this.morada).append("\n")
                .append("Fornecedor: ").append(this.idFornecedor).append("\n");
        sb.append("Proprietario: ").append(this.proprietario).append("\n")
                .append("NIF: ").append(this.NIF).append("\n");
        //this.devices.entrySet().forEach(a->{ sb.append("ID: ").append(a.getKey()).append(" --- Model.SmartDevice: ").append(a.getValue().toString()).append("\n");});
              sb.append("----------------------Divisão/Dispositivos----------------------").append("\n");
        this.locations.entrySet().forEach(a->{ sb.append("Divisão: ").append(a.getKey()).append(" - Dispositos -> ").append(a.getValue().toString()).append("\n");});
                        sb.append("----------------------------------------------------------------");
        return sb.toString();

    }

    public static CasaInteligente parseCasa(String line){
        String[] parte = line.split(",");
        return new CasaInteligente(parte[3],parte[0],Integer.parseInt(parte[1]),parte[4],parte[2]);
    }

    public CasaInteligente clone() {
        return new CasaInteligente(this);
    }

    public int addDevice(SmartDevice s) {
        int r=1;
        if(!existsDeviceHome(s.getID())){
            this.devices.put(s.getID(), s);
            r= 0;
        }
        return r;
    }

    public SmartDevice getDevice(String s) throws SmartDeviceNotExistsException{
        if(!this.existsDeviceHome(s)) throw new SmartDeviceNotExistsException ("O Model.SmartDevice com id " + s + " não existe");
        else return this.devices.get(s);
    }



    //terceira condição confirma se existe em qualquer sala o dispositivo
    public void addToRoom (String idRoom, SmartDevice device) throws SmartDeviceAlreadyExistsException, RoomNotExistsException {
        if (this.getLocations().containsKey(idRoom) && this.roomHasDevice(idRoom,device.getID()) && this.getDevices().containsKey(device.getID()))
            throw new SmartDeviceAlreadyExistsException("O device " + device.getID() +" já existe");
        if(!this.locations.containsKey(idRoom))
            throw new RoomNotExistsException("A divisao " + idRoom +" não existe");
        else if(!this.getDevices().containsKey(device.getID()))
        {
            this.devices.put(device.getID(), device);
            this.locations.get(idRoom).add(device.getID());
        }
        else
        {
            removeDevicesFromRoom(device.getID());
            this.locations.get(idRoom).add(device.getID());
        }

    }
    public void addFatura(String idFornecedor, LocalDateTime init, LocalDateTime finit, double valor)
    {
        Fatura f = new Fatura(calculaConsumo(init,finit),idHome+":"+init+" to "+finit, init, finit, morada, NIF, idFornecedor, valor);
        this.faturas.put(f.getIdFatura(),f.clone());

    }

    public double calculaConsumo(LocalDateTime init, LocalDateTime finit)
    {
        boolean flag = false;
        int i, len;
        double consumo = 0;

        for(SmartDevice sd: this.devices.values())
        {
            if(this.logs.get(sd.getID())!=null)
            {
                len = this.logs.get(sd.getID()).size()-1;
                i=0;
                Log l = this.logs.get(sd.getID()).get(i);
                while (i < len && l.getDia().isBefore(init)) {
                    flag = l.getMode();
                    i++;
                    l = this.logs.get(sd.getID()).get(i);
                }
                if(i<=len)
                {
                    while(i<=len && this.logs.get(sd.getID()).get(i).getDia().isBefore(finit))
                    {
                        if(!this.logs.get(sd.getID()).get(i).getMode() && flag) {
                            consumo += sd.consumoDiario() * ChronoUnit.MINUTES.between(init,this.logs.get(sd.getID()).get(i).getDia())  / 60;
                            flag = false;
                        }
                        if(this.logs.get(sd.getID()).get(i).getMode() && !flag)
                        {
                            flag = true;
                            init = this.logs.get(sd.getID()).get(i).getDia();
                        }
                        i++;
                    }
                    if (i>len && flag) {
                        consumo += sd.consumoDiario() * ChronoUnit.MINUTES.between(init, finit) / 60;
                    }
                }
            }
        }
        return consumo;
    }

    public boolean hasFatura(String idFatura)
    {
        return this.faturas.containsKey(idFatura);
    }

    public void removeFatura(String idFatura) throws FaturaNotExistsException
    {
        if(!hasFatura(idFatura)) throw new FaturaNotExistsException("A fatura com o id " + idFatura + " não existe");
        this.faturas.remove(idFatura);
    }

    public List<Fatura> getFaturas(String idFornecedor)
    {
        List<Fatura> faturas = new ArrayList<>();

        for(Fatura f: this.faturas.values())
        {
            if(f.getIdFornecedor().compareTo(idFornecedor)==0)
                faturas.add(f.clone());
        }

        return faturas;
    }

    public boolean hasLog(String s) {
        return (this.logs.get(s) != null);
    }

    public boolean hasLogByDevice(String idDevice, Log l) {
        if(!hasLog(idDevice)) return false;
        if(this.logs.get(idDevice).size()==0) return false;
        for(Log log: this.logs.get(idDevice))
            if(log.equals(l)) return true;
        return false;
    }

    public void addLog(String idDevice,Log g) throws LogAlreadyExistsException
    {
        //if(this.hasLogByDevice(idDevice,g)) throw new LogAlreadyExistsException("O log " + g + "já existe");
        if(this.logs.get(idDevice)==null)
        {
            List newLogD = new ArrayList();
            newLogD.add(g.clone());
            this.logs.put(idDevice,newLogD);
        }
        else this.logs.get(idDevice).add(g.clone());
    }

    public void addLog(LocalDateTime date, String idDevice, boolean mode)
    {
        Log g = new Log(date,mode);
        if(this.logs.get(idDevice).size()==0)
        {
            List newLogD = new ArrayList();
            newLogD.add(g.clone());
            this.logs.put(idDevice,newLogD);
        }
        else
        {
            this.logs.get(idDevice).add(g.clone());
        }
    }

    // quando se remove um dispositivo, removesse também todos os logs associados a ele da hash de logs
    public void removeLog(String idDevice) throws LogNotExistsException
    {
        if(!this.hasLog(idDevice)) throw new LogNotExistsException ("Não existem logs no device " + idDevice);
        else this.logs.remove(idDevice);
    }

    public int numberDevicesOn(LocalDateTime dia)
    {
        int count = 0;
        
        for(Log l: this.logs.get(dia.toString()))
        {
            if(l.getMode() && l.getDia().equals(dia))
                count++;
        } 
        return count;
    }
}
