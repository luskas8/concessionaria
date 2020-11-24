/* vendedor.c
 *
 * Modulo de imprementação das funções de vendedor
 *
 * Artur Freire
 * Lucas Silva dos Anjos
 * 
 * Ciência da Computação
 * 
 * 24/11/2020
*/

#include <stdio.h>
#include "vendedor.h"

void cadastrar_vendedor(void) {
    vendedor v;
    FILE * vendedorFile;
    // Verifica se há algo de errado com o arquivo
    if ((vendedorFile = fopen(ARQ_VENDEDORES, "r+b")) == NULL) {
        printf("\n\n\tERRO: Algo de errado com seu arquivo %s, por favor verifique e tente novamente!\n", ARQ_VENDEDORES);
        pausarTela();
        return;
    }

    // Move o ponteiro de posição para o final do arquivo
    fseek(vendedorFile, 0, SEEK_END);
    // Encontra-se o ultimo carro cadastrado e cria-se este novo carro na próxima posição
    v.codigo = ftell(vendedorFile) / sizeof(vendedor) + 1;

    printf("Nome do vendedor: ");
    scanf(" %40[^\n]", &v.nome);

    if (fwrite(&v, sizeof(vendedor), 1, vendedorFile) < 1) {
        printf("\tERRO: Algo de errado aconteceu, por favor tente novamente!\n");
        pausarTela();
    } else {
        printf("\tSUCESSO: Vendedor cadastrado!\n");
        pausarTela();
    }
    fclose(vendedorFile);
}

void listar_vendedores(void) {
    FILE * vendedorFile;
    // Verifica se há algo de errado com o arquivo
    if ((vendedorFile = fopen(ARQ_VENDEDORES, "r+b")) == NULL) {
        printf("\n\n\tERRO: Algo de errado com seu arquivo %s, por favor verifique e tente novamente!\n", ARQ_VENDEDORES);
        pausarTela();
        return;
    }

    // Move o ponteiro de posição para o final do arquivo
    fseek(vendedorFile, 0, SEEK_END);
    // Calcula-se o tamanha do vetor de vendedores cadastrados
    int TAMANHO = ftell(vendedorFile) / sizeof(vendedor);
    vendedor p[TAMANHO];

    // Retornar o ponteiro de leitura para o começo do arquivo
    rewind(vendedorFile);
    fread(p, sizeof(vendedor), TAMANHO, vendedorFile);
    fclose(vendedorFile);

    printf("\n\n\t\tLISTA DE VENDEDORES CADASTRADOS\n\n");
    printf("\tCodigo\t\tNome\n");
    printf("\t---------------------------------------\n");
    int i;
    for (i = 0; i < TAMANHO; i++) {
        // Lista os dados do vendedor i
        printf("\t%d\t\t%s\n", p[i].codigo, p[i].nome);
        printf("\t---------------------------------------\n");
    }
    pausarTela();
}

void alterar_vendedor(void) {
    vendedor v;
    FILE * vendedorFile;
    // Verifica se há algo de errado com o arquivo
    if ((vendedorFile = fopen(ARQ_VENDEDORES, "r+b")) == NULL) {
        printf("\n\n\tERRO: Algo de errado com seu arquivo %s, por favor verifique e tente novamente!\n", ARQ_VENDEDORES);
        pausarTela();
        return;
    }

    int codigo;
    printf("\n\n\tINFORME O CODIGO DO VENDEDOR A SE ALTERAR: ");
    scanf("%d", &codigo);

    fseek(vendedorFile, (codigo - 1) * sizeof(vendedor), SEEK_SET); // Coloca o ponteiro de leitura no fim do vendedor anterior ao que deseja alterar
    fread(&v, sizeof(vendedor), 1, vendedorFile); // Lê-se os dados do vendedor de código especificado

    if (codigo < 1 || feof(vendedorFile)) {
        printf("\tERRO: Vendedor com codigo invalido, por favor tente um valido.\n");
        fclose(vendedorFile);
        pausarTela();
        return;
    } else {
        printf("\tCodigo\t\tNome\n");
        printf("\t---------------------------------------\n");
        printf("\t%d\t\t%s\n", v.codigo, v.nome);
        printf("\t---------------------------------------\n");

        char novoNome[41];
        printf("Alterar nome: ");
        scanf(" %40[^\n]", &novoNome);

        // Copia o novo nome para a estrutura de vendedor
        strcpy(v.nome, novoNome);

        fseek(vendedorFile, -sizeof(vendedor), SEEK_CUR);
        if (fwrite(&v, sizeof(vendedor), 1, vendedorFile) < 1) {
            printf("\tERRO: Algo de errado aconteceu, por favor tente novamente!\n");
            pausarTela();
        } else {
            printf("\tSUCESSO: Vendedor alterado!\n");
            pausarTela();
        }
    }

    fclose(vendedorFile);
}

bool vendedor_valido(int codigo) {
    vendedor v;
    FILE * vendedorFile;
    // Verifica se há algo de errado com o arquivo
    if ((vendedorFile = fopen(ARQ_VENDEDORES, "rb")) == NULL) {
        printf("\n\n\tERRO: Algo de errado com seu arquivo %s, por favor verifique e tente novamente!\n", ARQ_VENDEDORES);
        pausarTela();
        return false;
    }

    fseek(vendedorFile, (codigo - 1) * sizeof(vendedor), SEEK_SET); // Coloca o ponteiro de leitura no fim do vendedor anterior ao que deseja alterar
    fread(&v, sizeof(vendedor), 1, vendedorFile); // Lê-se os dados do vendedor de código especificado

    // Caso o codigo seja menos que 1 ou o fim do arquivo seja excedido
    if (codigo < 1 || feof(vendedorFile)) {
        printf("\tERRO: Vendedor com codigo invalido, por favor tente um valido.\n");
        fclose(vendedorFile);
        pausarTela();
        return false;
    } else {
        printf("VENDEDOR: %-21s\n\n", v.nome);

        fclose(vendedorFile);
        return true;
    };
}