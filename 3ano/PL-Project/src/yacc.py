import json
from lexer import tokens
import ply.yacc as yacc
import tkinter as tk
from tkinter import ttk

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
    Value : Array
          | Dict
          | OFFSET_DATE_TIME
          | LOCAL_DATE_TIME
          | LOCAL_DATE
          | LOCAL_TIME
          | DECIMAL
          | EXPONENT
          | OCTA
          | HEXA
          | BIN
          | INTEGER
          | BOOLEAN
          | STRING_BIG
          | STRING
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

# Ler o arquivo de entrada
def converter():
    file = input("Insira o nome do ficheiro: ")
    with open(file, 'r') as f: 
        data = f.read()
        out = parser.parse(data)
        print(out)
        print((type(out)))
        print("********************************")
        output = input("Insira o nome do ficheiro de output: ")
        out = "../out/" + output
        with open(out, 'w') as o:
            json.dump(out, o,indent=4)
            print("Ficheiro criado com sucesso!")
