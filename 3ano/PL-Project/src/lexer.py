import ply.lex as lex

# Lista de tokens
tokens = (
    'TABLE',
    'STRING',
    'STRING_BIG',
    'INTEGER',
    'DECIMAL',
    'EXPONENT',
    'LOCAL_DATE',
    'LOCAL_TIME',
    'LOCAL_DATE_TIME',
    'OFFSET_DATE_TIME',
    'LEFT_BRACKET',
    'RIGHT_BRACKET',
    'LEFT_CURLY',
    'RIGHT_CURLY',
    'EQUALS',
    'COMMA',
    'BOOLEAN',
    'ARRAY_TABLES',
    'OCTA',
    'HEXA',
    'BIN',
    'NAME'

)

# Expressões regulares para cada token
t_LEFT_BRACKET = r'\['
t_RIGHT_BRACKET = r'\]'
t_LEFT_CURLY = r'\{'
t_RIGHT_CURLY = r'\}'
t_EQUALS = r'\='
t_COMMA = r'\,'

# Ignora espaços em branco e tabulações
t_ignore = ' \t\r\n'

def t_OFFSET_DATE_TIME(t):
    r'(\d{4}\-\d{2}\-\d{2}T\d{2}\:\d{2}\:\d{2})(Z)?(\.\d+)?(\-\d+:\d+)?'
    return t

def t_LOCAL_DATE_TIME(t):
    r'(\d{4}\-\d{2}\-\d{2}T\d{2}\:\d{2}\:\d{2})(\.\d+)?'
    return t

def t_LOCAL_DATE(t):
    r'\d{4}\-\d{2}\-\d{2}'
    return t

def t_LOCAL_TIME(t):
    r'(\d{2}\:\d{2}\:\d{2})(\.\d+)?'
    return t

def t_BOOLEAN(t):
    r'(true|false)'
    if str(t.value).lower() == "true": t.value = True
    else: t.value = False
    return t

def t_EXPONENT(t):
    r'((\+|\-)?\d+(\.\d+)?(e|E)(\+|\-)?\d+)'
    return t

def t_DECIMAL(t):
    r'(\+|\-)?(\d+\.\d+)'
    t.value = float(t.value)
    return t

def t_HEXA(t):
    r'(0x)([0-9a-f]+)'
    t.value = int(t.value[2:],16)
    return t

def t_OCTA(t):
    r'(0o)([0-8]+)'
    t.value = int(t.value[2:],8)
    return t

def t_BIN(t):
    r'(0b)([0-1]+)'
    t.value = int(t.value[2:],2)
    return t

def t_INTEGER(t):
    r'(\+|\-)?(\d+)'
    t.value = int(t.value)
    return t

def t_NAME(t):
    r'[\w\-\.]+'
    return t

def t_TABLE(t): 
    r'(?<=\n)(\[([\w\-]+\.?)+\])(?!=)'
    t.value = t.value[1:-1]
    return t

def t_ARRAY_TABLES(t): 
    r'(?<=\n)(\[\[([\w\-]+\.?)+\]\])(?!=)'
    t.value = t.value[2:-2]
    return t

def t_STRING_BIG(t):
    r'(\"\"\")[\w\s\-]+(\"\"\")'
    t.value = t.value[3:-3]
    return t

def t_STRING(t):
    r'(\'|\")[\w\s\-\.\,]+(\'|\")'
    t.value = t.value[1:-1]
    return t

# Ignora comentários
def t_COMMENT(t):
    r'\#.*'
    pass

# Rastreia o número da linha atual
def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

# Trata erros de caracteres inválidos
def t_error(t):
    print(f"Caracter inválido: {t.value[0]}")
    t.lexer.skip(1)

# Constrói o lexer
lexer = lex.lex()

def tokener():
    file = input("Insira o nome do ficheiro: ")
    with open(file, 'r') as f: 
        data = f.read()
        lexer.input(data)
        while tok := lexer.token():
            print(tok)