package Model;

import java.time.LocalDateTime;

public class Pedido {
    private LocalDateTime date;
    private String tipo; //pode ser "casa" ou "fornecedor"
    private String id;
    private String funcao;
    private String especificacoes;
    private boolean mode;

    public Pedido(LocalDateTime date, String tipo, String id, String funcao, String especificacoes, boolean mode)
    {
        this.date = date;
        this.tipo = tipo;
        this.id = id;
        this.funcao = funcao;
        this.especificacoes = especificacoes;
        this.mode = mode;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public String getTipo() {
        return tipo;
    }

    public void setTipo(String tipo) {
        this.tipo = tipo;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getFuncao() {
        return funcao;
    }

    public void setFuncao(String funcao) {
        this.funcao = funcao;
    }

    public String getEspecificacoes() {
        return especificacoes;
    }

    public void setEspecificacoes(String especificacoes) {
        this.especificacoes = especificacoes;
    }

    public boolean getMode() {
        return mode;
    }

    public void setMode(boolean mode) {
        this.mode = mode;
    }

    @Override
    public String toString() {
        return "Pedido{" +
                "date=" + date +
                ", tipo='" + tipo + '\'' +
                ", id='" + id + '\'' +
                ", funcao='" + funcao + '\'' +
                ", especificacoes='" + especificacoes + '\'' +
                ", mode=" + mode +
                '}';
    }
}
