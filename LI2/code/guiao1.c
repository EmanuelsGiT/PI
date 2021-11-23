/**
 * @file Ficheiro que contém a a função principal.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include "calculosG1.h"
#include "stack.h"


/**
* \brief Esta é a função principal que irá receber todos os números e operadores digitados pelo usuário, que serão posteriormente calculados e o resultado será colocado na stack. 
*
* @return 0 se não houver problemas.
*/

int main ()
{   

	/**
     * \brief Lista provisória que armazenará os números, strings, arrays, blocos e operadores.
     */
	char n[10240];

	/**
     * \brief Lista de caracteres segura.
     */
	char nSeguro[10240];


	/**
	 * \brief Coloca a linha do terminal no array n
	 */
    assert(fgets(n,10240,stdin));


    /**
     * \brief Copia o array inicial num array designado de seguro
     */
    strcpy(nSeguro, n);


	/**
	* \brief A função calcular é excutada com a lista criada. 
	* 
	* @param n Lista provisória com os números e operadores a processar.
	* @param nSeguro Lista segura.
	*/
    calcular(n, nSeguro);
    
    return 0;
}
