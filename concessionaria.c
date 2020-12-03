/* concessionaria.c
 *
 * Implementação de um sistema de controle de vendas de uma
 * concessionária de automóveis.
 *
 * Ciro Cirne Trindade
 * 19/11/2020
 * 
 * Arquivos disponibilizados pelo profº Ciro:
 *  concessionaria.c automovel.h venda.h vendedor.h
 * 
 * Artur Freire dos Santos
 * Lucas Silva dos Anjos
 * 
 * Ciências da Computação
 * 
 * 27/11/2020
 */

#include <stdio.h>
#include "utils.h"
#include "automovel.h"
#include "vendedor.h"
#include "venda.h"

enum menu_opcoes {
 CAD_AUTOMOVEL = 1,
 ALT_AUTOMOVEL = 2,
 LIST_TODOS_AUTOS = 3,
 LIST_AUTOS_A_VENDA = 4,
 CAD_VENDEDOR = 5,
 ALT_VENDEDOR = 6,
 LIST_VENDEDOR = 7,
 CAD_VENDA = 8,
 LIST_VENDAS_MES = 9,
 LIST_VENDAS_VENDEDOR = 10,
 SAIR = 0 
};

/* exibe o menu de opções do sistema e devolve a escolha do usuário */
int menu(char * [], int);

int main() {
    char * opcoes[] = {
        "Cadastrar automovel",
        "Alterar automovel",
        "Listar todos os automoveis",
        "Listar os automoveis a venda",
        "Cadastrar vendedor",
        "Alterar vendedor",
        "Listar vendedores",
        "Cadastrar venda",
        "Listar todas as vendas de um mes/ano",
        "Listar todas as vendas de um vendedor",
        "Sair do programa"
    };

    int op;
    do {
        op = menu(opcoes, sizeof(opcoes) / sizeof(char *));
        switch (op) {
            case CAD_AUTOMOVEL:
                cadastrar_automovel();
            break;
            case ALT_AUTOMOVEL:
                alterar_automovel();
            break;
            case LIST_TODOS_AUTOS:
                listar_todos_automoveis();
            break;
            case LIST_AUTOS_A_VENDA:
                listar_automoveis_a_venda();
            break;
            case CAD_VENDEDOR:
                cadastrar_vendedor();
            break;
            case ALT_VENDEDOR:
                alterar_vendedor();
            break;
            case LIST_VENDEDOR:
                listar_vendedores();
            break;
            case CAD_VENDA:
                cadastrar_venda();
            break;
            case LIST_VENDAS_MES:
                listar_vendas_mes();
            break;
            case LIST_VENDAS_VENDEDOR:
                listar_vendas_vendedor();
            break;
            case SAIR:
            break;
            default:
                printf("\n\tOpcao invalida!\n");
                pausarTela();
        } // fim do switch
    } while (op != SAIR);

    return 0;
}

int menu(char * opcoes[], int num) {
    int i, op;
    printf("\n\n\t\tCONCESSIONARIA DE AUTOMOVEIS\n\n");
    for (i = 0; i < num-1; i++) {
        printf("\t%02d - %s\n", i + 1, opcoes[i]);
    }

    printf("\t%02d - %s\n", SAIR, opcoes[i]);
    printf("\tOpcao: ");
    read_int(&op);
    return op;
}
