import java.io.FileNotFoundException;
import java.io.IOException;
import java.text.DecimalFormat;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import Model.Exceptions.*;
import Model.*;
import Model.Pedido;
import Model.SmartHouses;

import java.time.format.DateTimeParseException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;

public class UI{

    private SmartHouses smarthouses;

    private List<Pedido> pedidos;
    private List <Pedido> pedidosMudancaFornecedor;

    public UI(SmartHouses newSmarthouses) {

        this.smarthouses = new SmartHouses(newSmarthouses);
        this.pedidos = new ArrayList<>();
        this.pedidosMudancaFornecedor = new ArrayList<>();
    }

    public void executaListPedidos(int i)
    {
        if(i==0 && this.pedidos!=null)
        {
            for(Pedido pedido: this.pedidos)
            {
                executaPedido(pedido);
            }
            this.pedidos.clear();
        }
        if(i==1 && this.pedidosMudancaFornecedor!=null)
        {
            for(Pedido pedido: this.pedidosMudancaFornecedor)
            {
                executaPedido(pedido);
            }
            this.pedidosMudancaFornecedor.clear();
        }

    }

    public void addDeviceExecute(String idHome, String idDevice, String room, SmartDevice sd, LocalDateTime date, boolean mode)
    {
        try {
            this.smarthouses.adicionaDevice(idDevice, sd);
            this.smarthouses.addDeviceToRoom(idHome,room,sd);
            //System.out.println("IDHome:" + idHome + ", IDDecvice:"+ idDevice+"\n");
            this.smarthouses.addLogExecute(idHome,idDevice,new Log(date,mode));
        }
        catch (SmartDeviceAlreadyExistsException | LogAlreadyExistsException | CasaInteligenteNotExistsException | RoomNotExistsException e) {
            System.out.println(e.getMessage());
        }
    }

    public void executaPedido(Pedido pedido)
    {
        String[] linha;
        boolean on;
        if(pedido.getTipo().compareTo("casa")==0)
        {
            switch (pedido.getFuncao())
            {
                case "adicionaBulb":
                    linha = pedido.getEspecificacoes().split(",");
                    //linha = id+","+tonalidade+","+dimensao+","+consumo+","+room
                    SmartDevice sdB = new SmartBulb(linha[0], linha[1],pedido.getMode(), Integer.parseInt(linha[2]),Double.parseDouble(linha[3]));
                    addDeviceExecute(pedido.getId(),linha[0],linha[4],sdB,pedido.getDate(),pedido.getMode());
                    break;
                case "adicionaCamera":
                    // id+","+tamanho+","+res+","+consumo+","+room
                    linha = pedido.getEspecificacoes().split(",");
                    SmartDevice sdC = new SmartCamera(linha[0], pedido.getMode(), linha[2], Double.parseDouble(linha[1]),Double.parseDouble(linha[3]));
                    addDeviceExecute(pedido.getId(),linha[0],linha[4],sdC,pedido.getDate(),pedido.getMode());
                    break;
                case "adicionaSpeaker":
                    // id + "," + volume + "," + marca + "," + channel + "," + consumo + "," + room
                    linha = pedido.getEspecificacoes().split(",");
                    SmartDevice sdS = new SmartSpeaker(linha[0],pedido.getMode(), Integer.parseInt(linha[1]), linha[2], linha[3],Double.parseDouble(linha[4]));
                    addDeviceExecute(pedido.getId(),linha[0],linha[5],sdS,pedido.getDate(),pedido.getMode());
                    break;
                case "removeDispositivo":
                    try{
                        linha = pedido.getEspecificacoes().split(",");
                        if(pedido.getMode())
                        {
                            this.smarthouses.removeDevice(linha[0],pedido.getId());
                            this.smarthouses.removePermanenteDevice(linha[0],pedido.getId());
                        }
                        else
                        {
                            this.smarthouses.removeDevice(linha[0],pedido.getId());
                            this.smarthouses.addDeviceToRoomSameHouse(linha[0],pedido.getId(),linha[1]);
                        }
                    }
                    catch (LogNotExistsException | RoomNotExistsException e)
                    {
                        System.out.println(e.getMessage());
                    }
                    break;
                case "ligaDesliga":
                    linha = pedido.getEspecificacoes().split(",");
                    try {
                        this.smarthouses.gestaoDevices(pedido.getId(),linha[0],pedido.getMode());
                        this.smarthouses.addLogChangeMode(pedido.getId(), pedido.getDate(), pedido.getMode());
                    }
                    catch (LogAlreadyExistsException | SmartDeviceNotExistsException | CasaInteligenteNotExistsException e)
                    {
                        System.out.println(e.getMessage());
                    }
                    break;
                case "tonBulb":
                    linha = pedido.getEspecificacoes().split(",");
                    try{
                        this.smarthouses.colocaTon(pedido.getId(),linha[0],Integer.parseInt(linha[1]));
                    }
                    catch (SmartDeviceNotExistsException e)
                    {
                        System.out.println(e.getMessage());
                    }
                    break;
                case "volSpk":
                    linha = pedido.getEspecificacoes().split(",");
                    try{
                        this.smarthouses.colocaVol(pedido.getId(),linha[0],Integer.parseInt(linha[1]));
                    }
                    catch (SmartDeviceNotExistsException e)
                    {
                        System.out.println(e.getMessage());
                    }
                    break;
                case "alteraFornecedor":
                    try {
                        this.smarthouses.alteraFornecedor(pedido.getId(),pedido.getEspecificacoes());
                    } catch (CasaInteligenteNotExistsException e) {
                        e.printStackTrace();
                    }
                    break;
                case "setAllDevicesHome":
                    try{
                        if(pedido.getEspecificacoes().compareTo("")==0)
                        {// ligar/desligar em todas as divisões
                            this.smarthouses.setAllDevicesHome(pedido.getId(), pedido.getMode());
                            this.smarthouses.addLogChangeMode(pedido.getId(), this.smarthouses.getDate(), pedido.getMode());
                        }
                        else
                        {// ligar/desligar numa divisão especifica
                            this.smarthouses.setAlldivision(pedido.getId(),pedido.getEspecificacoes(),pedido.getMode());
                            this.smarthouses.addLogChangeMode(pedido.getId(), this.smarthouses.getDate(), pedido.getMode(),pedido.getEspecificacoes());
                        }
                    }
                    catch (LogAlreadyExistsException | CasaInteligenteNotExistsException | SmartDeviceNotExistsException | RoomNotExistsException e)
                    {
                        System.out.println(e.getMessage());
                    }
                    break;
                default:
                    break;
            }
        }
        else if(pedido.getTipo().compareTo("fornecedor")==0)
        {
            switch (pedido.getFuncao()) {
                case "removeCasas":
                    try {
                        this.smarthouses.removeHome(pedido.getId(),pedido.getEspecificacoes());
                    } catch (CasaInteligenteNotExistsException e) {
                        System.out.println(e.getMessage());
                    } catch (FornecedorNotExistsException f) {
                        System.out.println("erro fornecedor nao existe");
                    }
                    break;
                case "removeFornecedores":
                    try{
                        this.smarthouses.removeFornecedor(pedido.getId());
                    }
                    catch(FornecedorNotExistsException e )
                    {
                        System.out.println(e.getMessage());
                    }
                    break;
                case "adicionaCasas":
                    linha = pedido.getEspecificacoes().split(",");
                    this.smarthouses.adicionaHome(pedido.getId(),new CasaInteligente(linha[0],linha[1],Integer.parseInt(linha[2]),linha[3],pedido.getId()));
                    this.smarthouses.addRoom(linha[4],linha[0]);
                    break;
                case "adicionaFornecedores":
                    this.smarthouses.adicionaFornecedor(pedido.getId(),new Fornecedor(pedido.getId(),Double.parseDouble(pedido.getEspecificacoes())));
                default:
                    break;
            }
        }
    }

    public void executeMenu(){

        List<String> opcoes = new ArrayList<>();
        opcoes.add("Casa que mais gastou num período de tempo\n");
        opcoes.add("Comercializador com maior volume de facturação\n");
        opcoes.add("Listagem de facturas emitidas por um comercializador\n");
        opcoes.add("Ordenação dos maiores consumidores de energia durante um período de tempo\n");
        opcoes.add("Casas\n");
        opcoes.add("Fornecedores\n");
        opcoes.add("Salvar estado\n");
        opcoes.add("Carregar estado\n");
        opcoes.add("Carregar do ficheiro logs.txt\n");
        opcoes.add("Alterar data\n");
        opcoes.add("Automatizar\n");
        opcoes.add("Sair da aplicação");
        Scanner scanner = new Scanner(System.in);
        int i=0;
        Menu menu = new Menu(opcoes);
        do {
            menu.executa();
            switch (menu.getOpcao()) {
                case 1:
                    executaDados(1);
                    break;
                case 2:
                    executaDados(2);
                    break;
                case 3:

                    System.out.println("Id/Nome do Fornecedor: ");
                    String id = scanner.nextLine();
                    Fornecedor f = new Fornecedor(this.smarthouses.getFornecedores().get(id));
                    if(f.faturasEmitidas().size()==0) System.out.print("Não há faturas registadas\n\n");
                    else f.faturasEmitidas().forEach(a->System.out.println(a.toString()));
                    break;
                case 4:
                    executaDados(4);
                    break;
                case 5:
                    consultaCasas();
                    break;
                case 6:
                    Fornecedores();
                    break;
                case 7:
                    try {
                        this.smarthouses.guardarEstado();
                    } catch (IOException e) {
                        e.printStackTrace();
                        System.out.println("Não foi possível guardar o estado da aplicação.");
                    }
                    break;
                case 8:
                    try {
                        this.smarthouses.carregarEstado("estado.obj");
                    }catch (FileNotFoundException fnf){
                        System.out.println("Não foi possível carregar o estado da aplicação.");
                    } catch (IOException | ClassNotFoundException e) {
                        e.printStackTrace();
                        System.out.println("Não foi possível carregar o estado da aplicação.");
                    }
                    break;
                case 9:
                    System.out.println("Digite o nome do ficheiro:");
                    Scanner sc = new Scanner(System.in);
                    String nome=sc.nextLine();
                    try{
                        this.smarthouses.parser("SmartHouses/src/"+nome);
                    }catch (LinhaException msg) {
                        System.out.println("Nao foi possivel carregar a aplicação - Erro linha.");
                    }catch (SmartDeviceAlreadyExistsException msg) {
                        System.out.println("Nao foi possivel carregar a aplicação- Erro device já existe.");
                    }catch (CasaInteligenteAlreadyExistsException msg) {
                        System.out.println("Nao foi possivel carregar a aplicação- Erro casa já existe.");
                    }
                    catch (CasaInteligenteNotExistsException msg) {
                        System.out.println("Nao foi possivel carregar a aplicação- Erro casa não existe.");
                    }
                    break;
                case 10:
                    try {
                        System.out.println("Nova data(YYYY-MM-DD HH:MM): ");
                        String date = scanner.nextLine();
                        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
                        LocalDateTime newDate = LocalDateTime.parse(date, formatter);
                        if(this.smarthouses.getDate().compareTo(newDate)>=0)
                            System.out.println("Não pode colocar uma data anterior a " + this.smarthouses.getDate().format(formatter));
                        else
                        {
                            executaListPedidos(0); // executa os pedidos normais
                            this.smarthouses.atualiza(newDate); // cria faturas
                            executaListPedidos(1); // executa as mudanças de fornecedores
                            this.smarthouses.setDate(newDate);
                            System.out.println("Data atualizada\n");
                        }
                    }
                    catch (DateTimeParseException e)
                    {
                        System.out.println("Formato data errado");
                    }
                    catch (LogNotExistsException e)
                    {
                        System.out.println("Erro ao criar os logs");
                    }
                    break;
                case 11:
                    System.out.println("Caminho para o ficheiro: ");
                    String path = scanner.nextLine();
                    automatizar("SmartHouses/src/"+path);
                    break;
                case 12:
                    i=12;
                    menu.setOpcao(12);
                    System.exit(0);
                default:
                    break;
            }
        } while (menu.getOpcao() != 0);
    }

    public void Dispositivos(String idHome){
        List<String> opcoes = new ArrayList<>();
        opcoes.add("SmartBulb\n");
        opcoes.add("SmartSpeaker\n");
        opcoes.add("SmartCamera\n");
        opcoes.add("Configurações\n");
        opcoes.add("SmartBulb - Tonalidade\n");
        opcoes.add("SmartSpeaker - Volume\n");
        opcoes.add("Ligar/Desligar todos os dispositivos\n");
        opcoes.add("Ligar/Desligar todos os dispositivos de uma divisão\n");
        opcoes.add("Consultar dispositivos\n");
        opcoes.add("Voltar");

        Menu menu = new Menu(opcoes);
        do {
            menu.executa();
            switch (menu.getOpcao()) {
                case 1:
                    geraDispositivos(1,idHome);
                    break;
                case 2:
                    geraDispositivos(2,idHome);
                    break;
                case 3:
                    geraDispositivos(3,idHome);
                    break;
                case 4:
                    ligaDesliga(idHome);
                    break;
                case 5:
                    tonBulb(idHome);
                    break;
                case 6:
                    volSpk(idHome);
                    break;
                case 7:
                    setAllDevicesHome(idHome,true);
                    break;
                case 8:
                    setAllDevicesHome(idHome,false);
                    break;
                case 9:
                    consultaDispositivos(idHome);
                    break;
                case 10:
                    executeMenu();
                    break;
                default:
                    break;
            }
        } while (menu.getOpcao() != 0);
    }

    public void geraDispositivos(int x, String idHome) {
        List<String> opcoes = new ArrayList<>();
        opcoes.add("Adicionar dispositivo\n");
        opcoes.add("Remover dispositivo\n");
        opcoes.add("Voltar");

        Menu menu = new Menu(opcoes);
        do {
            menu.executa();
            switch (menu.getOpcao()) {
                case 1:
                    if(x==1) adicionaBulb(idHome);
                    if(x==3) adicionaCamera(idHome);
                    if(x==2) adicionaSpeaker(idHome);
                    break;
                case 2:
                    removeDispositivo(idHome);
                    break;
                case 3:
                    Dispositivos(idHome);
                    break;
                default:
                    break;
            }
        } while (menu.getOpcao() != 0);

    }

    public void geraCasas(String idFornecedor) {
        List<String> opcoes = new ArrayList<>();
        opcoes.add("Adicionar casa\n");
        opcoes.add("Remover casa\n");
        opcoes.add("Voltar");

        Menu menu = new Menu(opcoes);
        do {
            menu.executa();
            switch (menu.getOpcao()) {
                case 1:
                    adicionaCasas(idFornecedor);
                    break;
                case 2:
                    removeCasas(idFornecedor);
                    break;
                case 3:
                    executeMenu();
                    break;
                default:
                    break;
            }
        } while (menu.getOpcao() != 0);

    }


    public void adicionaBulb(String idHome){

        System.out.println("Digite o ID do dispositivo: ");
        Scanner scanner = new Scanner(System.in);
        String id = scanner.nextLine();
        if(!this.smarthouses.existeDeviceInHome(id,idHome)) {
            boolean on;
            CasaInteligente ci = this.smarthouses.getCasas().get(idHome);
            System.out.println("Em que divisão pretende adicionar o dispositivo? ");
            String room = scanner.nextLine();
            if (!ci.hasRoom(room)) {
                System.out.println("Divisão não existe\n");
            }
            else {
                System.out.println("(On/OFF): ");
                String modo = scanner.nextLine();
                on = modo.equals("on") || modo.equals("On") || modo.equals("ON") || modo.equals("oN");
                System.out.println("Tonalidade: ");
                String tonalidade = scanner.nextLine();
                System.out.println("Dimensão: ");
                String dimensao = scanner.nextLine();
                System.out.println("Consumo base: ");
                String consumo = scanner.nextLine();
                this.pedidos.add(new Pedido(smarthouses.getDate(), "casa", idHome, "adicionaBulb", id + "," + tonalidade + "," + dimensao + "," + consumo + "," + room, on));
                executaListPedidos(0);
            }
        }
        //scanner.close();
    }


    public void adicionaCamera(String idHome){

        System.out.println("Digite o ID do dispositivo: ");
        Scanner scanner = new Scanner(System.in);
        String id = scanner.nextLine();
        if(!this.smarthouses.existeDeviceInHome(id,idHome)) {
            boolean on;
            CasaInteligente ci = this.smarthouses.getCasas().get(idHome);
            System.out.println("Em que divisão pretende adicionar o dispositivo? ");
            String room = scanner.nextLine();
            if (!ci.hasRoom(room)) {
                System.out.println("Divisão não existe\n");
            } else {
                System.out.println("(On/OFF): ");
                String modo = scanner.nextLine();
                on = modo.equals("on") || modo.equals("On") || modo.equals("ON") || modo.equals("oN");
                System.out.println("Tamanho: ");
                String tamanho = scanner.nextLine();
                System.out.println("Resolução (axb): ");
                String res = scanner.nextLine();
                System.out.println("Consumo base: ");
                String consumo = scanner.nextLine();
                this.pedidos.add(new Pedido(smarthouses.getDate(), "casa", idHome, "adicionaCamera", id + "," + tamanho + "," + res + "," + consumo + "," + room, on));
                executaListPedidos(0);
            }
        }
        //scanner.close();
    }

    public void adicionaSpeaker(String idHome){

        System.out.println("Digite o ID do dispositivo: ");
        Scanner scanner = new Scanner(System.in);
        String id = scanner.nextLine();
        if(!this.smarthouses.existeDeviceInHome(id,idHome)) {

            boolean on;
            CasaInteligente ci = this.smarthouses.getCasas().get(idHome);
            System.out.println("Em que divisão pretende adicionar o dispositivo? ");
            String room = scanner.nextLine();
            if (!ci.hasRoom(room)) {
                System.out.println("Divisão não existe\n");
            }
            else {
                System.out.println("(On/OFF): ");
                String modo = scanner.nextLine();
                on = modo.equals("on") || modo.equals("On") || modo.equals("ON") || modo.equals("oN");
                System.out.println("Volume: ");
                String volume = scanner.nextLine();
                scanner.nextLine();
                System.out.println("Marca: ");
                String marca = scanner.nextLine();
                System.out.println("Channel: ");
                String channel = scanner.nextLine();
                System.out.println("Consumo base: ");
                String consumo = scanner.nextLine();
                this.pedidos.add(new Pedido(smarthouses.getDate(), "casa", idHome, "adicionaSpeaker", id + "," + volume + "," + marca + "," + channel + "," + consumo + "," + room, on));
                executaListPedidos(0);
            }
        }
        //scanner.close();
    }

    public void removeDispositivo(String idHome) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Digite o ID do dispositivo a remover: ");
        String idDevice = scanner.nextLine();
        System.out.println("Remover permanentemente da casa? ");
        System.out.println("(Sim/Nao)");
        String modo = scanner.nextLine();
        boolean on = modo.equals("sim") || modo.equals("SIM") || modo.equals("Sim") || modo.equals("s");
        String divisao = "";
        if(this.smarthouses.existeDeviceInHome(idDevice,idHome))
        {
            if(!on)
            {
                System.out.println("Qual a divisão da casa que irá adicionar: ");
                divisao = scanner.nextLine();
            }
            this.pedidos.add(new Pedido(smarthouses.getDate(),"casa",idHome,"removeDispositivo",idDevice+","+divisao,on));
            executaListPedidos(0);
        }
        else System.out.println("O device não existe nesta casa.");
        //scanner.close();
    }

    public void removeCasas(String idFornecedor) {
        System.out.println("Digite o ID da casa a remover: ");
        Scanner scanner = new Scanner(System.in);
        String idHome = scanner.nextLine();

        if(this.smarthouses.existsHomeInFornecedor(idHome,idFornecedor))
        {
            this.pedidos.add(new Pedido(smarthouses.getDate(),"fornecedor",idFornecedor,"removeCasas",idHome, false));
            executaListPedidos(0);
        }
        else System.out.println("A casa que digitou nao existe.");
        //scanner.close();
    }

    public void removeFornecedores() {
        System.out.println("Digite o ID do fornecedor a remover: ");
        Scanner scanner = new Scanner(System.in);
        String id = scanner.nextLine();

        if(this.smarthouses.existsFornecedor(id)) {
            this.pedidos.add(new Pedido(smarthouses.getDate(), "fornecedor", id, "removeFornecedores", "",false));
            executaListPedidos(0);
        }
        else System.out.println("O fornecedor que digitou nao existe.");
        //scanner.close();
    }

    public void consultaCasas(){
        Scanner scanner = new Scanner(System.in);
        System.out.println("Digite o ID da casa: ");
        String idHome = scanner.nextLine();
        if(this.smarthouses.existsHome(idHome))
        {

            List<String> opcoes = new ArrayList<>();
            opcoes.add("Informações gerais da Casa\n");
            opcoes.add("Dispositivos\n");
            opcoes.add("Mudar de Fornecedor\n");
            opcoes.add("Mostrar faturas\n");
            opcoes.add("Voltar");

            Menu menu = new Menu(opcoes);
            do
            {
                menu.executa();
                switch (menu.getOpcao()) {
                    case 1:
                        System.out.println(this.smarthouses.getCasas().get(idHome));
                        break;
                    case 2:
                        Dispositivos(idHome);
                        break;
                    case 3:
                        System.out.println("Digite o id do Fornecedor: ");
                        String idFornecedor = scanner.nextLine();
                        this.pedidosMudancaFornecedor.add(new Pedido(smarthouses.getDate(),"casa",idHome,"alteraFornecedor",idFornecedor, false));
                        break;
                    case 4:
                        if(this.smarthouses.getCasas().get(idHome).getFaturas(idHome)==null) System.out.println("Não há faturas\n");
                        this.smarthouses.getFaturas(idHome).forEach((a,b)->System.out.println(b.toString()));
                        break;
                    case 5:
                        executeMenu();
                        break;

                }
            } while (menu.getOpcao() != 0);
        }
        else System.out.println("A casa que digitou não existe.");
        //scanner.close();
    }

    public void ligaDesliga(String idHome){
        Scanner scanner = new Scanner(System.in);
        System.out.println("Digite o ID do dispositivo: ");
        String idDevice = scanner.nextLine();
        if(this.smarthouses.existeDeviceInHome(idDevice,idHome))
        {
            System.out.println("(On/OFF): ");
            String modo = scanner.nextLine();
            boolean on = modo.equals("on") || modo.equals("ON") || modo.equals("On") || modo.equals("oN");
            this.pedidos.add(new Pedido(smarthouses.getDate(),"casa",idHome,"ligaDesliga",idDevice,on));
            executaListPedidos(0);
        }
        else System.out.println("O dispositivo que digitou não existe nesta casa.");
        //scanner.close();
    }
    public void tonBulb(String idHome){
        Scanner scanner = new Scanner(System.in);
        System.out.println("Digite o ID do dispositivo: ");
        String idDevice = scanner.nextLine();
        if(this.smarthouses.existeDeviceInHome(idDevice,idHome))
        {
            System.out.print("1-WARM\n2-COLD\n3-NEUTRAL\nTonalidade->");
            String ton = scanner.nextLine();
            this.pedidos.add(new Pedido(smarthouses.getDate(),"casa",idHome,"tonBulb",idDevice+","+ton, false));
            executaListPedidos(0);
        }
        else System.out.println("O dispositivo que digitou não existe nesta casa.");
        //scanner.close();
    }

    public void volSpk(String idHome){
        System.out.println("Digite o ID do dispositivo: ");
        Scanner scanner = new Scanner(System.in);
        String idDevice = scanner.nextLine();
        if(this.smarthouses.existeDeviceInHome(idDevice,idHome)) {
            System.out.println("Volume: ");
            String vol = scanner.nextLine();
            this.pedidos.add(new Pedido(smarthouses.getDate(),"casa",idHome,"volSpk",idDevice+","+vol,false));
            executaListPedidos(0);
        }
        else System.out.println("O dispositivo que digitou não existe nesta casa.");
        //scanner.close();
    }

    public void consultaDispositivos(String idHome){
        System.out.println("Digite o ID do dispositivo: ");
        Scanner scanner = new Scanner(System.in);
        String idDevice = scanner.nextLine();
        if(this.smarthouses.existeDeviceInHome(idDevice,idHome)) {
            System.out.println(this.smarthouses.getDispositivos().get(idDevice));
            if(this.smarthouses.getLogsDevice(idDevice,idHome)!=null)
                this.smarthouses.getLogsDevice(idDevice,idHome).forEach((a)->System.out.println(a.toString()));
            else System.out.println("Não existem logs neste dispositivo.\n");
        }
        else System.out.println("O dispositivo que digitou não existe nesta casa.");
    }

    public void adicionaCasas(String idFornecedor) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Digite o ID da casa: ");
        String idHome = scanner.nextLine();
        if(!this.smarthouses.existsHome(idHome)) {
            System.out.println("Digite a morada da casa : ");
            String morada = scanner.nextLine();

            System.out.println("NIF do proprietário: ");
            String nif = scanner.nextLine();
            System.out.println("Nome do proprietário : ");
            String proprietario = scanner.nextLine();
            System.out.println("Quantas divisões terá a casa?");
            int n = scanner.nextInt();
            scanner.nextLine();
            System.out.println("Divisões:");
            String divisoes = "";
            while (n >= 0) {
                String divisao = scanner.nextLine();
                System.out.println(divisao);
                divisoes = divisoes+";"+divisao;
                n--;
            }
            String divisao = scanner.nextLine();
            divisoes = divisoes+divisao;
            System.out.println(divisoes);
            this.pedidos.add(new Pedido(smarthouses.getDate(),"fornecedor",idFornecedor,"adicionaCasas",idHome+","+morada+","+nif+","+proprietario+","+divisoes,false));
            executaListPedidos(0);
        }
        else System.out.println("Casa com esse id já existe");
        //scanner.close();
    }

    public void adicionaFornecedores(){
        System.out.println("Digite o fornecedor de energia: ");
        Scanner scanner = new Scanner(System.in);
        String idFornecedor = scanner.nextLine();
        if(!this.smarthouses.existsFornecedor(idFornecedor)){
            System.out.println("Digite o imposto base: ");
            //double imposto = scanner.nextDouble();
            String imposto = scanner.nextLine();
            //Fornecedor f = new Fornecedor(idFornecedor,imposto);
            this.pedidos.add(new Pedido(smarthouses.getDate(),"fornecedor",idFornecedor,"adicionaFornecedores",imposto,false));
            executaListPedidos(0);
            System.out.println("Digite o número  de casas: ");
            int n = scanner.nextInt();
            while(n>0){
                adicionaCasas(idFornecedor);
                n--;
            }
        }else System.out.println("Fornecedor já existe");
    }

    public void Fornecedores(){
        List<String> opcoes = new ArrayList<>();
        opcoes.add("Consultar fornecedor\n");
        opcoes.add("Adicionar fornecedor\n");
        opcoes.add("Remover fornecedor\n");
        opcoes.add("Voltar");

        Menu menu = new Menu(opcoes);
        do {
            menu.executa();
            switch (menu.getOpcao()) {
                case 1:
                    System.out.println("Digite o id do fornecedor:");
                    Scanner scanner = new Scanner(System.in);
                    String id =scanner.nextLine();
                    if(this.smarthouses.getFornecedores().get(id)!=null) {
                        List<String> opcoes2 = new ArrayList<>();
                        opcoes2.add("Informações gerais do Fornecedor\n");
                        opcoes2.add("Casas\n");
                        opcoes2.add("Muda formula\n");
                        opcoes2.add("Voltar");

                        Menu menu2 = new Menu(opcoes2);
                        do
                        {
                            menu2.executa();
                            switch (menu2.getOpcao()) {
                                case 1:
                                    System.out.println(this.smarthouses.getFornecedores().get(id));
                                    break;
                                case 2:
                                    geraCasas(id);
                                    break;
                                case 3:
                                    System.out.println("Para que formula pretende alterar?");
                                    String f = scanner.nextLine();
                                    this.smarthouses.changeFormula(id,f);
                                    break;
                                case 4:
                                    Fornecedores();
                                    break;
                            }
                        } while (menu2.getOpcao() != 0);

                    }
                    else System.out.println("O fornecedor que digitou não existe.");
                    break;
                case 2:
                    adicionaFornecedores();
                    break;
                case 3:
                    removeFornecedores();
                    break;
                case 4:
                    executeMenu();
                    break;
                default:
                    break;
            }
        } while (menu.getOpcao() != 0);

    }

    public void executaDados(int n){
        Scanner scanner = new Scanner(System.in);
        String inicio, fim;

        try
        {
            System.out.println("Data de início(YYYY-MM-DD HH:MM): ");
            inicio = scanner.nextLine();

            System.out.println("Data de fim(YYYY-MM-DD HH:MM): ");
            fim = scanner.nextLine();

            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
            LocalDateTime datai = LocalDateTime.parse(inicio, formatter);
            LocalDateTime dataf = LocalDateTime.parse(fim, formatter);

           if(n==1) System.out.println(this.smarthouses.casaGastouMaisPeriodoVariosFornecedores(datai, dataf));
           if(n==2) System.out.println(this.smarthouses.fornecedorComMaisFaturacao(datai, dataf));
           if(n==4)
           {
               DecimalFormat d = new DecimalFormat("#0.00");
               for(Fornecedor f: this.smarthouses.ordenarFornecedores(datai,dataf))
                   System.out.println(f.getId() + ": " + d.format(f.faturaçaoFornecedor(datai, dataf)) + "€");
           }
        }
        catch (DateTimeParseException e)
        {
            System.out.println("Formato data errado");
        }
        catch(LogNotExistsException c){
            System.out.println(c.getMessage());
        }

    }

    public void setAllDevicesHome(String idHome, boolean all)
    {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Modo(on/off): ");
        String modo = scanner.nextLine();
        boolean on = modo.equals("on") || modo.equals("ON") || modo.equals("On") || modo.equals("oN");
        if(all) this.pedidos.add(new Pedido(smarthouses.getDate(),"casa",idHome,"setAllDevicesHome","",on));
        else {
            System.out.println("Divisao: ");
            String divisao = scanner.nextLine();
            this.pedidos.add(new Pedido(smarthouses.getDate(),"casa",idHome,"setAllDevicesHome",divisao,on));
        }
        executaListPedidos(0);
    }

    public void automatizar(String filename)
    {
        String[] parte;
        String especificacoes;
        try {
            List<String> linhas = this.smarthouses.lerFicheiro(filename);

            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
            LocalDateTime date;
            LocalDateTime init = java.time.LocalDateTime.now();
            boolean on;

            for (String linha : linhas) {
                parte = linha.split(",");
                System.out.println(linha);
                try {
                    date = LocalDateTime.parse(parte[0], formatter);

                    if (!this.smarthouses.getDate().isBefore(date))
                        System.out.println("Não pode colocar uma data anterior a " + init.format(formatter));
                    else if (this.smarthouses.getDate().compareTo(date) < 0) {
                        executaListPedidos(0); // executa os pedidos normais
                        this.smarthouses.atualiza(date); // cria faturas
                        executaListPedidos(1); // executa as mudanças de fornecedores
                        this.smarthouses.setDate(date);

                        if (parte[2].compareTo("alteraFornecedor") == 0) {
                            this.pedidosMudancaFornecedor.add(new Pedido(date, parte[1], parte[2], parte[3], parte[4], false));
                        } else if (parte[4].compareTo("") == 0) {
                            this.pedidos.add(new Pedido(date, parte[1], parte[2], parte[3], parte[4], false));
                        } else {
                            on = parte[5].equals("on") || parte[5].equals("On") || parte[5].equals("ON") || parte[5].equals("oN");
                            System.out.println(parte[5] + "." + on);
                            if (parte[3].compareTo("adicionaBulb") == 0 || parte[3].compareTo("adicionaCamera") == 0) {
                                //id+","+tonalidade+","+dimensao+","+consumo+","+room
                                on = parte[9].equals("on") || parte[9].equals("On") || parte[9].equals("ON") || parte[9].equals("oN");
                                especificacoes = parte[4] + "," + parte[5] + "," + parte[6] + "," + parte[7] + "," + parte[8];
                                this.pedidos.add(new Pedido(date, parte[1], parte[2], parte[3], especificacoes, on));
                            }
                            else if (parte[3].compareTo("adicionaSpeaker") == 0) {
                                //id+","+volume+","+marca+","+calnal+","+consumo+","+room
                                on = parte[10].equals("on") || parte[10].equals("On") || parte[10].equals("ON") || parte[10].equals("oN");
                                especificacoes = parte[4] + "," + parte[5] + "," + parte[6] + "," + parte[7] + "," + parte[8] + "," + parte[9];
                                this.pedidos.add(new Pedido(date, parte[1], parte[2], parte[3], especificacoes, on));
                            }
                            else if(parte[3].compareTo("removeDispositivo") == 0 || parte[3].compareTo("tonBulb") == 0 || parte[3].compareTo("volSpk") == 0 )
                            {
                                on = parte[6].equals("Sim") || parte[6].equals("sim") || parte[6].equals("SIM");
                                especificacoes = parte[4] + "," + parte[5];
                                this.pedidos.add(new Pedido(date, parte[1], parte[2], parte[3], especificacoes, on));
                            }
                            else this.pedidos.add(new Pedido(date, parte[1], parte[2], parte[3], parte[4], on));
                        }
                    }
                    executaListPedidos(0); // executa os pedidos normais
                    if(this.smarthouses.getDate().compareTo(date) > 0)
                    {
                        this.smarthouses.atualiza(this.smarthouses.getDate().plusDays(1)); // cria faturas
                        executaListPedidos(1); // executa as mudanças de fornecedores
                    }
                } catch (DateTimeParseException e) {
                    System.out.println("Formato data errado");
                } catch (Model.Exceptions.LogNotExistsException l) {
                    System.out.println("Não existem dados em memória de logs");
                }
            }
        }
        catch (java.io.FileNotFoundException e) {
            System.out.println(e.getMessage());
        }
    }
}
