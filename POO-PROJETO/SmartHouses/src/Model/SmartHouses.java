package Model;

import Model.Formulas.*;
import Model.Exceptions.*;


import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.Collectors;

import static java.util.stream.Collectors.toMap;


public class SmartHouses implements Serializable {
    private Map<String, CasaInteligente> casas; // id casa -> CASA
    private Map<String,SmartDevice> dispositivos; // ID Device -> DEVICE
    private Map<String,Fornecedor> fornecedores; // ID Model.Fornecedor -> FORNECEDOR
    private Map<String,FormulaEnergia> formulas;
    private LocalDateTime Now;

    public SmartHouses(){
        this.casas = new HashMap<>();
        this.dispositivos = new HashMap<>();
        this.fornecedores = new HashMap<>();
        this.formulas = new HashMap<>();
        this.Now = java.time.LocalDateTime.now();
        formulas.put("EDP Comercial", new FormulaEDP());
        formulas.put("Galp Energia", new FormulaGalp());
        formulas.put("Iberdrola", new FormulaIberdrola());
        formulas.put("Endesa", new FormulaEndesa());
        formulas.put("Gold Energy", new FormulaGoldEnergy());
        formulas.put("Coopernico", new FormulaCoopernico());
        formulas.put("Enat", new FormulaEnat());
        formulas.put("YIce", new FormulaYIce());
        formulas.put("MEO Energia", new FormulaMEO());
        formulas.put("Muon", new FormulaMuon());
        formulas.put("Luzboa", new FormulaLuzboa());
        formulas.put("Energia Simples", new FormulaEnergiaSimples());
        formulas.put("SU Electricidade", new FormulaSUElectricidade());
        formulas.put("EDA", new FormulaEDA());
    }

    public SmartHouses(Map<String,CasaInteligente> casas, Map<String,SmartDevice> dispositivos,Map<String,Fornecedor> fornecedores, LocalDateTime date){
        setCasas(casas);
        setDispositivos(dispositivos);
        setFornecedores(fornecedores);
        this.formulas = new HashMap<>();
        this.Now = date;
        formulas.put("EDP Comercial", new FormulaEDP());
        formulas.put("Galp Energia", new FormulaGalp());
        formulas.put("Iberdrola", new FormulaIberdrola());
        formulas.put("Endesa", new FormulaEndesa());
        formulas.put("Gold Energy", new FormulaGoldEnergy());
        formulas.put("Coopernico", new FormulaCoopernico());
        formulas.put("Enat", new FormulaEnat());
        formulas.put("YIce", new FormulaYIce());
        formulas.put("MEO Energia", new FormulaMEO());
        formulas.put("Muon", new FormulaMuon());
        formulas.put("Luzboa", new FormulaLuzboa());
        formulas.put("Energia Simples", new FormulaEnergiaSimples());
        formulas.put("SU Electricidade", new FormulaSUElectricidade());
        formulas.put("EDA", new FormulaEDA());
    }

    public SmartHouses(SmartHouses sh){
        setCasas(sh.getCasas());
        setDispositivos(sh.getDispositivos());
        setFornecedores(sh.getFornecedores());
        this.formulas = new HashMap<>();
        formulas.put("EDP Comercial", new FormulaEDP());
        formulas.put("Galp Energia", new FormulaGalp());
        formulas.put("Iberdrola", new FormulaIberdrola());
        formulas.put("Endesa", new FormulaEndesa());
        formulas.put("Gold Energy", new FormulaGoldEnergy());
        formulas.put("Coopernico", new FormulaCoopernico());
        formulas.put("Enat", new FormulaEnat());
        formulas.put("YIce", new FormulaYIce());
        formulas.put("MEO Energia", new FormulaMEO());
        formulas.put("Muon", new FormulaMuon());
        formulas.put("Luzboa", new FormulaLuzboa());
        formulas.put("Energia Simples", new FormulaEnergiaSimples());
        formulas.put("SU Electricidade", new FormulaSUElectricidade());
        formulas.put("EDA", new FormulaEDA());
        this.Now = sh.getDate();
    }

    public void parser(String filename) throws LinhaException, SmartDeviceAlreadyExistsException, CasaInteligenteAlreadyExistsException, CasaInteligenteNotExistsException {
        Map<String, CasaInteligente> casas = new HashMap<>();
        Map<String, SmartDevice> dispositivos = new HashMap<>();
        Map<String,Fornecedor> fornecedores = new HashMap<>();
        Map<String,FormulaEnergia> formulas = new HashMap<>();
        formulas.put("EDP Comercial", new FormulaEDP());
        formulas.put("Galp Energia", new FormulaGalp());
        formulas.put("Iberdrola", new FormulaIberdrola());
        formulas.put("Endesa", new FormulaEndesa());
        formulas.put("Gold Energy", new FormulaGoldEnergy());
        formulas.put("Coopernico", new FormulaCoopernico());
        formulas.put("Enat", new FormulaEnat());
        formulas.put("YIce", new FormulaYIce());
        formulas.put("MEO Energia", new FormulaMEO());
        formulas.put("Muon", new FormulaMuon());
        formulas.put("Luzboa", new FormulaLuzboa());
        formulas.put("Energia Simples", new FormulaEnergiaSimples());
        formulas.put("SU Electricidade", new FormulaSUElectricidade());
        formulas.put("EDA", new FormulaEDA());

        String[] linhaPartida;
        try {
            List<String> linhas = lerFicheiro(filename);
            String divisao = null;
            SmartDevice sd;
            int i = 0;
            CasaInteligente casaMaisRecente = null;
            for (String linha : linhas) {
                linhaPartida = linha.split(":", 2);
                //divide a linha em 2
                switch (linhaPartida[0]) {
                    case "Casa":
                        if (i >= 1) casas.put(casaMaisRecente.getIdHome(), casaMaisRecente);
                        CasaInteligente ci = CasaInteligente.parseCasa(linhaPartida[1]);
                        casas.put(ci.getIdHome(), ci.clone());
                        if ((fornecedores.get(ci.getIdFornecedor()) != null))
                            if ((fornecedores.get(ci.getIdFornecedor())).addCasa(ci) == 1)
                                throw new CasaInteligenteAlreadyExistsException("Fornecedor já tem essa casa");
                        casaMaisRecente = ci;
                        i++;
                        break;
                    case "Divisao":
                        if (casaMaisRecente == null) throw new LinhaException("Linha Inválida!");
                        divisao = linhaPartida[1];
                        casaMaisRecente.addRoom(divisao);
                        break;
                    case "SmartBulb":
                        if (divisao == null) throw new LinhaException("Linha Inválida!");
                        sd = SmartBulb.parseSmartBulb(linhaPartida[1]);
                        if (casaMaisRecente.addDevice(sd) == 1)
                            throw new SmartDeviceAlreadyExistsException("O SmartDevice com id " + sd.getID() + "já existe");
                        casaMaisRecente.addToRoom(divisao, sd.getID());
                        dispositivos.put(sd.getID(), sd);
                        break;
                    case "SmartCamera":
                        if (divisao == null) throw new LinhaException("Linha Inválida!");
                        sd = SmartCamera.parseSmartCamera(linhaPartida[1]);
                        if (casaMaisRecente.addDevice(sd) == 1)
                            throw new SmartDeviceAlreadyExistsException("O SmartDevice com id " + sd.getID() + "já existe");
                        casaMaisRecente.addToRoom(divisao, sd.getID());
                        dispositivos.put(sd.getID(), sd);
                        break;
                    case "SmartSpeaker":
                        if (divisao == null) throw new LinhaException("Linha Inválida!");
                        sd = SmartSpeaker.parseSmartSpeaker(linhaPartida[1]);
                        if (casaMaisRecente.addDevice(sd) == 1)
                            throw new SmartDeviceAlreadyExistsException("O SmartDevice com id " + sd.getID() + "já existe");
                        casaMaisRecente.addToRoom(divisao, sd.getID());
                        dispositivos.put(sd.getID(), sd);
                        break;
                    case "Fornecedor":
                        Fornecedor f = Fornecedor.parseFornecedor(linhaPartida[1], formulas);
                        fornecedores.put(f.getId(), f.clone());
                        break;
                    default:
                        throw new LinhaException("Linha Inválida!");
                }
                if (linha.equals(linhas.get(linhas.size() - 1)))
                    casas.put(casaMaisRecente.getIdHome(), casaMaisRecente);
            }
            setDispositivos(dispositivos);
            setCasas(casas);
            setFornecedores(fornecedores);
        }
        catch (FileNotFoundException e){
            System.out.println(e.getMessage());
        }
    }

    public void guardarEstado() throws IOException {
        FileOutputStream file = new FileOutputStream("estado.obj");
        ObjectOutputStream out = new ObjectOutputStream(file);
        out.writeObject(this);
        out.flush();
        out.close();
    }

    public void carregarEstado(String ficheiro) throws IOException, ClassNotFoundException {
        FileInputStream f = new FileInputStream(ficheiro);
        ObjectInputStream in = new ObjectInputStream(f);
        SmartHouses smartHouses = (SmartHouses) in.readObject();
        in.close();
        setDispositivos(smartHouses.getDispositivos());
        setCasas(smartHouses.getCasas());
        setFornecedores(smartHouses.getFornecedores());
    }

    public boolean existsDevice(String id){
        return this.dispositivos.containsKey(id);
    }

    public boolean existsFornecedor(String id){
        return this.fornecedores.containsKey(id);
    }

    public void adicionaDevice(String idDevice,SmartDevice sd) throws SmartDeviceAlreadyExistsException {
        if(this.dispositivos.get(idDevice)!=null) throw new SmartDeviceAlreadyExistsException("Device com esse id já existe");
        this.dispositivos.put(idDevice,sd.clone());
    }

    public void adicionaFornecedor(String id ,Fornecedor f)  {
        this.fornecedores.put(id,f.clone());
    }

    public void removeDevice(String idDevice,String idHome) throws LogNotExistsException {
        this.casas.get(idHome).removeDevicesFromRoom(idDevice);
    }

    public void removePermanenteDevice(String idDevice,String idHome)
    {
        this.dispositivos.remove(idDevice);
        this.casas.get(idHome).removeDeviceFromHome(idDevice);
    }

    public void addDeviceToRoomSameHouse(String idDevice,String idHome, String room) throws RoomNotExistsException
    {
        if(this.casas.get(idHome).hasRoom(room))
            this.casas.get(idHome).addDeviceToRoom(idDevice,room);
        else throw  new RoomNotExistsException("A localização não existe");
    }

    public void gestaoDevices(String idHome, String idDevice,boolean modo) throws SmartDeviceNotExistsException{ //id device
        this.dispositivos.get(idDevice).setModo(modo);
        this.casas.get(idHome).getDevice(idDevice).setModo(modo);
    }

    public void colocaTon(String idHome,String idDevice,int ton) throws SmartDeviceNotExistsException { //id device
        if(ton==1)
            if(this.dispositivos.get(idDevice) instanceof SmartBulb)
            {
                ((SmartBulb) this.dispositivos.get(idDevice)).setMode(SmartBulb.Mode.WARM);
                ((SmartBulb) this.casas.get(idHome).getDevice(idDevice)).setMode(SmartBulb.Mode.WARM);
            }
        if(ton==2)
            if(this.dispositivos.get(idDevice) instanceof SmartBulb)
            {
                ((SmartBulb) this.dispositivos.get(idDevice)).setMode(SmartBulb.Mode.COLD);
                ((SmartBulb) this.casas.get(idHome).getDevice(idDevice)).setMode(SmartBulb.Mode.COLD);
            }
        if(ton==3)
            if(this.dispositivos.get(idDevice) instanceof SmartBulb)
            {
                ((SmartBulb) this.dispositivos.get(idDevice)).setMode(SmartBulb.Mode.NEUTRAL);
                ((SmartBulb) this.casas.get(idHome).getDevice(idDevice)).setMode(SmartBulb.Mode.NEUTRAL);
            }
    }

    public void colocaVol(String idHome, String idDevice,int vol)  throws SmartDeviceNotExistsException{ //id device
            if (this.dispositivos.get(idDevice) instanceof SmartSpeaker)
            {
                ((SmartSpeaker) this.dispositivos.get(idDevice)).setVolume(vol);
                ((SmartSpeaker) this.casas.get(idHome).getDevice(idDevice)).setVolume(vol);
            }
    }


    public boolean existsHome(String idHome){
        return this.casas.containsKey(idHome);
    }

    public boolean existsHomeInFornecedor(String idHome, String idFornecedor){
        return this.fornecedores.get(idFornecedor).hasCasa(idHome);
    }

    public boolean existeDeviceHomes(String deviceId){
        boolean exists = false;
        long r = this.casas.values().stream().filter((e)->e.existsDeviceHome(deviceId)).count();
        if(r>0) exists=true;
        return exists;
    }

    public boolean existeDeviceInHome(String deviceId, String idHome){
        return this.casas.get(idHome).hasDevice(deviceId);
    }

    public void adicionaHome(String fornecedor,CasaInteligente ci){
        this.casas.put(ci.getIdHome(),ci.clone());
        this.fornecedores.get(fornecedor).addCasa(ci.clone());
    }

    public void removeHome(String idFornecedor,String idHome) throws CasaInteligenteNotExistsException,FornecedorNotExistsException{
        if(this.fornecedores.get(idFornecedor)==null) throw new FornecedorNotExistsException("O fornecedor "+idFornecedor+" não existe.");
        if(this.fornecedores.get(idFornecedor).removeCasa(idHome)==1) throw new CasaInteligenteNotExistsException("O fornecedor "+idFornecedor+" não tem a casa "+idHome);
    }

    public String dispositovosTostring(){
        StringBuilder sb = new StringBuilder();
        this.dispositivos.forEach((key, value) -> sb.append("*ID DEVICE -> ").append(key).append(" * ").append("\n").append(" - INFO -> ").append(value.toString()).append("\n\n"));
        return sb.toString();
    }

    public String casasTostring(){
        StringBuilder sb = new StringBuilder();
        this.casas.forEach((key, value) -> sb.append("* ID HOUSE -> ").append(key).append(" * ").append("\n").append(" - INFO -> ").append(value.toString()).append("\n\n"));
        return sb.toString();
    }

    public Map<String,CasaInteligente> getCasas() {
        return casas.entrySet().stream().collect(toMap(Map.Entry::getKey, v->v.getValue().clone()));
    }

    public void setCasas(Map<String,CasaInteligente> casas){
        this.casas = new HashMap<>(casas.values().stream().collect(toMap(CasaInteligente::getIdHome, CasaInteligente::clone)));
    }

    public Map<String,SmartDevice> getDispositivos(){
        return dispositivos.entrySet().stream().collect(toMap(Map.Entry::getKey, v->v.getValue().clone()));
    }

    public void setDispositivos(Map<String,SmartDevice> dispositivos) {
        this.dispositivos = new HashMap<>(dispositivos.values().stream().collect(toMap(SmartDevice::getID, SmartDevice::clone)));
    }

    public Map<String, Fornecedor> getFornecedores() {
        return fornecedores.entrySet().stream().collect(toMap(Map.Entry::getKey, v->v.getValue().clone()));
    }

    public Map<String, FormulaEnergia> getFormulas() {
        return formulas.entrySet().stream().collect(toMap(Map.Entry::getKey, v->v.getValue().clone()));
    }

    public void setFornecedores(Map<String,Fornecedor> fornecedores){
        this.fornecedores = new HashMap<>(fornecedores.values().stream().collect(toMap(Fornecedor::getId, Fornecedor::clone)));
    }

    public void setFormulas(Map<String,FormulaEnergia> fornecedores){
        this.formulas = new HashMap<>(formulas.values().stream().collect(toMap(FormulaEnergia::getId, FormulaEnergia::clone)));
    }

    public LocalDateTime getDate()
    {
        return this.Now;
    }

    public void setDate(LocalDateTime date)
    {
        this.Now = date;
    }

    public List<String> lerFicheiro(String nomeFich) throws FileNotFoundException {
        List<String> lines;
        try { lines = Files.readAllLines(Paths.get(nomeFich), StandardCharsets.UTF_8); }
        catch(IOException exc) { lines = new ArrayList<>(); }
        if(lines.isEmpty()) throw new FileNotFoundException("Ficheiro não encontrado");
        return lines;
    }

    public void atualiza(LocalDateTime newDate) throws Model.Exceptions.LogNotExistsException
    {
        for(Fornecedor f: this.fornecedores.values())
            f.addFatura(this.Now, newDate);

        for(CasaInteligente c: this.casas.values())
        {
            if(this.fornecedores.get(c.getIdFornecedor())!=null)
                c.addFatura(c.getIdFornecedor(), this.Now, newDate, this.fornecedores.get(c.getIdFornecedor()).getValorFornecedor(c.getIdHome(),this.Now,newDate,c.calculaConsumo(this.Now,newDate)));
        }
    }

    public Map<String,Fatura> getFaturas(String idHome)
    {
        return this.casas.get(idHome).getFaturas();
    }

    public List<Log> getLogsDevice(String idDevice, String idHome)
    {
        return this.casas.get(idHome).getLogs().get(idDevice);
    }


    public void alteraFornecedor(String idHome, String idFornecedor) throws CasaInteligenteNotExistsException{
        if (this.fornecedores.get(this.casas.get(idHome).getIdFornecedor()).removeCasa(idHome) == 1) throw new CasaInteligenteNotExistsException("O fornecedor nao possui a casa");
        this.casas.get(idHome).setIdFornecedor(idFornecedor);
        this.fornecedores.get(idFornecedor).addCasa(this.casas.get(idHome).clone());
    }

    public void setAllDevicesHome(String idHome, boolean modo)
    {
        this.casas.get(idHome).setallDevices(modo);
        this.dispositivos.values().forEach(a->a.setModo(modo));
    }

    public void setAlldivision(String idHome, String room, boolean modo)  throws RoomNotExistsException,SmartDeviceNotExistsException
    {
        if(this.casas.get(idHome).hasRoom(room))
        {
            this.casas.get(idHome).setAlldivision(modo,room);
            for(SmartDevice s:this.dispositivos.values())
            {
                if(this.casas.get(idHome).getLocations().get(room).contains(s.getID()))
                    s.setModo(modo);
            }
            this.dispositivos.values().forEach(a->a.setModo(modo));
        }

        else throw  new RoomNotExistsException("A localização não existe");
    }

    public void addLogExecute(String idHome, String idDevice, Log g) throws LogAlreadyExistsException,CasaInteligenteNotExistsException
    {
        this.casas.get(idHome).addLog(idDevice,g.clone());
        this.fornecedores.get(this.casas.get(idHome).getIdFornecedor()).getCasa(idHome).addLog(idDevice,g.clone());
    }

    public void addLogChangeMode(String idHome, LocalDateTime date, Boolean mode) throws LogAlreadyExistsException, CasaInteligenteNotExistsException
    {
        CasaInteligente ci = this.casas.get(idHome);
        CasaInteligente ci2 = this.fornecedores.get(this.casas.get(idHome).getIdFornecedor()).getCasa(idHome);
        for(SmartDevice s: ci.getDevices().values())
        {
            ci.addLog(s.getID(),new Log(date,mode));
            ci2.addLog(s.getID(),new Log(date,mode));
        }
    }

    public void addLogChangeMode(String idHome, LocalDateTime date, Boolean mode, String room) throws LogAlreadyExistsException, CasaInteligenteNotExistsException
    {
        CasaInteligente ci = this.casas.get(idHome);
        CasaInteligente ci2 = this.fornecedores.get(this.casas.get(idHome).getIdFornecedor()).getCasa(idHome);
        for(String s: ci.getLocations().get(room))
        {
            ci.addLog(s,new Log(date,mode));
            ci2.addLog(s,new Log(date,mode));
        }
    }

    public void addDeviceToRoom(String idHouse, String room, SmartDevice sd) throws SmartDeviceAlreadyExistsException,RoomNotExistsException
    {
        this.casas.get(idHouse).addToRoom(room,sd);
    }

    public void setFornecedor(Map<String,Fornecedor> fornecedores)
    {
        this.fornecedores = new HashMap<>();
        fornecedores.forEach((id,value)->{this.fornecedores.put(id,value.clone());});
    }

    public Fornecedor getFornecedor(String id) throws FornecedorNotExistsException
    {
        if(!this.containsFornecedor(id)) throw new FornecedorNotExistsException ("O Model.Fornecedor com id " + id + " não existe");
        else return this.fornecedores.get(id).clone();
    }

    public boolean containsFornecedor(String f)
    {
        return this.fornecedores.containsKey(f);
    }

    public void addFornecedor (Fornecedor f) throws FornecedorAlreadyExistsException
    {
        if(this.containsFornecedor(f.getId())) throw new FornecedorAlreadyExistsException ("O Model.Fornecedor com id " + f.getId() + " já existe");
        this.fornecedores.put(f.getId(),f.clone());
    }

    public void removeFornecedor (String id) throws FornecedorNotExistsException
    {
        if(this.containsFornecedor(id)) throw new FornecedorNotExistsException ("O Model.Fornecedor com id " + id + " não existe");
        this.fornecedores.remove(id);
    }

    public SmartHouses clone(){
        return new SmartHouses(this);
    }


    public String casaGastouMaisPeriodoVariosFornecedores(LocalDateTime init, LocalDateTime finit) throws LogNotExistsException
    {
        String r = "";
        double max = 0, gasto = 0;
        for(CasaInteligente c: this.casas.values())
        {
            gasto = c.calculaConsumo(init,finit);
            if(gasto>max)
            {
                max=gasto;
                r = c.getIdHome();
            }

        }
        if(r.compareTo("")==0) return "Nenhuma casa tem valor superior a 0€";
        return "A casa que consumiu mais foi a " + r;
    }

    //retorna o id (String) do fornecedor que tem mais faturação
    public String fornecedorComMaisFaturacao(LocalDateTime init, LocalDateTime finit)
    {
        String id = "";
        double total, max = 0;
        for(Fornecedor f: this.fornecedores.values())
        {
            total = f.faturaçaoFornecedor(init,finit);

            if(total>max) {
                max = total;
                id = f.getId();
            }
        }
        if(id.compareTo("")==0) id = "Não há faturas registadas.";
        return "O fornecedor com mais faturação é o " + id;
    }
    public List<Fornecedor> ordenarFornecedores(LocalDateTime init, LocalDateTime finit)
    {
        Comparator<Fornecedor> c = (Fornecedor a, Fornecedor b)->
        {return Double.compare(a.faturaçaoFornecedor(init,finit),b.faturaçaoFornecedor(init,finit));};

        return this.fornecedores.values().stream().map(Fornecedor::clone).sorted(c).collect(Collectors.toList());
    }

    public void addRoom(String s, String idHome)
    {
        System.out.println(s);
        String[] div = s.split(";");
        int i = 1;
        while(i<div.length)
        {
            this.casas.get(idHome).addRoom(div[i]);
            i++;
        }
    }

    public void changeFormula(String idFornecedor, String f)
    {
        this.fornecedores.get(idFornecedor).setFormula(this. formulas.get(f));
    }


}
