/* vendedor.c
 *
 * Modulo de imprementação das funções de vendedor
 *
 * Artur Freire dos Santos
 * Lucas Silva dos Anjos
 * 
 * Ciências da Computação
 * 
 * 27/11/2020
*/

#include <stdio.h>
#include "vendedor.h"

void cadastrar_vendedor(void) {
    vendedor v;
    FILE * vendedorFile;
    // Verifica se há algo de errado com o arquivo
    if ((vendedorFile = fopen(ARQ_VENDEDORES, "a+b")) == NULL) {
        printf(ERR_OPEN_ARC, ARQ_VENDEDORES);
        pausarTela();
        return;
    }

    // Move o ponteiro de posição para o final do arquivo
    fseek(vendedorFile, 0, SEEK_END);
    // Encontra-se o ultimo carro cadastrado e cria-se este novo carro na próxima posição
    v.codigo = ftell(vendedorFile) / sizeof(vendedor) + 1;

    printf("Nome do vendedor: ");
    read_line(v.nome, 41);

    if (fwrite(&v, sizeof(vendedor), 1, vendedorFile) < 1) {
        printf("\tERRO: NAO foi possivel cadastrar o vendedor.\n");
    } else {
        printf("\tSUCESSO: Vendedor cadastrado!\n");
    }
    pausarTela();
    fclose(vendedorFile);
}

void listar_vendedores(void) {
    FILE * vendedorFile;
    // Verifica se há algo de errado com o arquivo
    if ((vendedorFile = fopen(ARQ_VENDEDORES, "rb")) == NULL) {
        printf(ERR_OPEN_ARC, ARQ_VENDEDORES);
        pausarTela();
        return;
    }

    // Move o ponteiro de posição para o final do arquivo
    fseek(vendedorFile, 0, SEEK_END);

    int TAMANHO = ftell(vendedorFile) / sizeof(vendedor);
    vendedor vendedores[TAMANHO];

    rewind(vendedorFile);
    fread(vendedores, sizeof(vendedor), TAMANHO, vendedorFile);
    fclose(vendedorFile);

    printf("\n\n\tLISTA DE VENDEDORES CADASTRADOS\n\n");
    printf("\tCodigo\t\tNome\n");
    printf("\t---------------------------------------\n");
    for (int i = 0; i < TAMANHO; i++) {
        // Lista os dados do vendedor i
        printf("\t%06d\t\t%s\n", vendedores[i].codigo, vendedores[i].nome);
        printf("\t---------------------------------------\n");
    }
    pausarTela();
}

void alterar_vendedor(void) {
    int codigo;
    printf("\n- ALTERANDO UM VENDEDOR\n\n");
    printf("Nao deseja estar aqui? Entre com '-1' para voltar ao menu principal.\n\n");
    printf("Codigo do vendedor: ");
    read_int(&codigo);
    if (codigo == -1) return;

    vendedor v;
    FILE * vendedorFile;
    
    if ((vendedorFile = fopen(ARQ_VENDEDORES, "r+b")) == NULL) {
        printf(ERR_OPEN_ARC, ARQ_VENDEDORES);
        pausarTela();
        return;
    }

    if (!vendedor_valido(codigo, &v)) {
        printf("\tERRO: Vendedor com codigo invalido! A alteracao NAO pode ser concluida.\n");
    } else {
        printf("\tCodigo\t\tNome\n");
        printf("\t---------------------------------------\n");
        printf("\t%06d\t\t%s\n", v.codigo, v.nome);
        printf("\t---------------------------------------\n");

        char novoNome[41];
        printf("Alterar nome: ");
        read_line(v.nome, 41);

        // Coloca o ponteiro de leitura no fim do vendedor anterior ao que deseja alterar
        fseek(vendedorFile, (codigo - 1) * sizeof(vendedor), SEEK_SET);
        if (fwrite(&v, sizeof(vendedor), 1, vendedorFile) < 1) {
            printf("\tERRO: NAO foi possivel alterar o vendedor.\n");
        } else {
            printf("\tSUCESSO: Vendedor alterado!\n");
        }
    }
    pausarTela();
    fclose(vendedorFile);
}

bool vendedor_valido(int codigo, vendedor * v) {
    FILE * vendedorFile;
    // Verifica se há algo de errado com o arquivo
    if ((vendedorFile = fopen(ARQ_VENDEDORES, "rb")) == NULL) {
        printf(ERR_OPEN_ARC, ARQ_VENDEDORES);
        pausarTela();
        return false;
    }

    fseek(vendedorFile, (codigo - 1) * sizeof(vendedor), SEEK_SET);
    // Lê-se os dados do vendedor de código especificado
    fread(v, sizeof(vendedor), 1, vendedorFile);
    fclose(vendedorFile);
    
    // Caso o codigo seja menos que 1 ou o fim do arquivo seja excedido
    return codigo < 1 || v->codigo != codigo ? false : true;
}
