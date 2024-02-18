from lexer import tokener
from yacc import converter

def print_menu():
    print("\033[36m\033[1m---------------------------------------- MENU ----------------------------------------\033[0m")
    print("\033[1m\033[36m(A)\033[0m Lexer")
    print("\033[1m\033[36m(B)\033[0m Conversor")
    print("\033[91m(0) Sair\033[0m")


while(True):
    print_menu()
    print("\n\033[1mEscolha uma opção:\033[0m ")
    op = input()
    op=op.upper()
    if (op=='A'):
        tokener()
    elif (op=='B'):
        converter()
    elif (op=='0'):
        break
    else: print("\033[91m\033[1mOpção inválida.\033[0m")