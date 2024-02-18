import tkinter as tk
from tkinter import ttk
import json
from lexer import tokens
import ply.yacc as yacc

# Define as regras gramaticais para a conversão de TOML para JSON
def p_Toml(p):
    '''
    Toml : Tables
         | Attributes 
         | Attributes Tables
    '''
    if len(p) == 2:
        p[0] = p[1]
    else:
        p[1].update(p[2])
        p[0] = p[1]

def p_Tables_Table(p):
    '''
    Tables : Table
           | Tables Table
    '''
    if len(p) == 2:
        p[0] = p[1]
    else:
        lista = list(p[2].keys())
        
        nova_lista = lista[0].split('.')
        temp = p[1]
        if len(nova_lista) > 1 :

            for x in nova_lista[:-1]:
                if x not in temp:
                    temp[x] = {}
                temp = temp[x] 
            temp[nova_lista[-1]] = p[2][lista[0]]
            p[0] = p[1]
        else:
            p[1].update(p[2])
            p[0] = p[1]

def p_Tables_Array_Table(p):
    '''
    Tables : Array_Tables
           | Tables Array_Tables 
    '''
    if len(p) == 2:
        p[0] = p[1]
    else:
        lista = list(p[2].keys())
        
        nova_lista = lista[0].split('.')
        temp = p[1]
        if len(nova_lista) > 1 :

            for x in nova_lista[:-1]:
                if x not in temp:
                    temp[x] = {}
                temp = temp[x] 
            if nova_lista[-1] in  temp.keys():
               temp[nova_lista[-1]].append(p[2][lista[0]][0])
            else:     
                temp[nova_lista[-1]] = p[2][lista[0]]
            p[0] = p[1]
        else:
            if nova_lista[-1] in  temp.keys():
               temp[nova_lista[-1]].append(p[2][lista[0]][0])
            else:     
                temp[nova_lista[-1]] = p[2][lista[0]]
            p[0] = p[1]

def p_Table(p):
    '''
    Table : TABLE
          | TABLE Attributes
    '''
    if len(p) == 2:
        p[0] = {p[1] : {}}
    else:
        p[0] = {p[1] : p[2]}

def p_Array_Tables(p):
    ''' 
    Array_Tables : ARRAY_TABLES 
                 | ARRAY_TABLES Attributes
    '''
    if len(p) == 2:
        p[0] = {p[1]:[{}]}
    else:
        p[0] = {p[1]:[p[2]]}

def p_Attributes(p):
    '''
    Attributes : Attribute 
               | Attribute Attributes
    '''
    if len(p) == 2:
        p[0] = p[1]
    else:
        p[1].update(p[2])
        p[0] = p[1]

def p_Attribute(p):
    '''
    Attribute : NAME EQUALS Value
              | STRING EQUALS Value
    '''
    p[0] = {p[1] : p[3]}

def p_Array(p):
    '''
    Array : LEFT_BRACKET RIGHT_BRACKET
          | LEFT_BRACKET Array_Values RIGHT_BRACKET
    '''
    if len(p) == 3:
        p[0] = []
    else:
        p[0] = p[2]

def p_Array_Values(p):
    '''
    Array_Values : Value
                 | Array_Values COMMA Value
    '''
    if len(p) == 2:
        p[0] = [p[1]]
    else:
        p[1].append(p[3]) 
        p[0] = p[1]

def p_Dict(p):
    '''
    Dict : LEFT_CURLY RIGHT_CURLY
         | LEFT_CURLY Dict_Values RIGHT_CURLY
    '''
    if len(p) == 3:
        p[0] = {}
    else:
        p[0] = p[2]

def p_Dict_Values(p):
    '''
    Dict_Values : Attribute
                | Dict_Values COMMA Attribute
    '''
    if len(p) == 2:
        p[0] = p[1]
    else:
        p[1].update(p[3])
        p[0] = p[1]

def p_Value(p):
    '''
    Value : OFFSET_DATE_TIME
          | LOCAL_DATE_TIME
          | LOCAL_DATE
          | LOCAL_TIME
          | STRING_BIG
          | STRING
          | Array
          | EXPONENT
          | OCTA
          | HEXA
          | BIN
          | DECIMAL
          | INTEGER
          | BOOLEAN
          | Dict
    '''
    p[0] = p[1]

# Erro de sintaxe
def p_error(p):
    print(p)
    if p:
        print(f"Erro de sintaxe na linha {p.lineno}: token inesperado {p.value}")
    else:
        print("Erro de sintaxe: fim de entrada inesperado")

# Build parser
parser = yacc.yacc(debug=True)


def aux():
    original_code = original_entry.get("1.0", tk.END)
    converted_code = parser.parse(original_code)
    print(converted_code)
    print((type(converted_code)))
    print("********************************")
    if converted_code == None:
        converted_entry.delete("1.0", tk.END)
        converted_entry.insert(tk.END, "Conversão não suportada(Input inválido).")
    else:
        out = json.dumps(converted_code,indent=4)
        converted_entry.delete("1.0", tk.END)
        converted_entry.insert(tk.END, out)

    
# Cria a janela principal
window = tk.Tk()
window.title("Conversor de Toml para Json")
window.geometry("1280x720")

# Criação dos widgets
original_frame = ttk.Frame(window)
original_frame.pack(side=tk.LEFT, padx=50, pady=100)

original_label = ttk.Label(original_frame, text="Input (TOML) - Paste your TOML here:")
original_label.pack()

original_entry = tk.Text(original_frame, height=80, width=55)
original_entry.pack()

convert_button = ttk.Button(window, text="Converter", command=aux)
convert_button.pack(side=tk.LEFT, padx=100, pady=10)

converted_frame = ttk.Frame(window)
converted_frame.pack(side=tk.RIGHT, padx=50, pady=100)

converted_label = ttk.Label(converted_frame, text="Output (JSON) - The converted JSON:")
converted_label.pack()

converted_entry = tk.Text(converted_frame, height=80, width=55)
converted_entry.pack()

# Inicia o loop do tkinter
window.mainloop()

