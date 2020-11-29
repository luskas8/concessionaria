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
    if ((vendedorFile = fopen(ARQ_VENDEDORES, "r+b")) == NULL) {
        printf("\n\n\tERRO: O arquivo %s NAO pode ser encontrado!\n", ARQ_VENDEDORES);
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
        printf("\n\n\tERRO: O arquivo %s NAO pode ser encontrado!\n", ARQ_VENDEDORES);
        pausarTela();
        return;
    }

    // Move o ponteiro de posição para o final do arquivo
    fseek(vendedorFile, 0, SEEK_END);
    // Calcula-se o tamanha do vetor de vendedores cadastrados
    int TAMANHO = ftell(vendedorFile) / sizeof(vendedor);
    vendedor vendedores[TAMANHO];

    // Retornar o ponteiro de leitura para o começo do arquivo
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
    vendedor v;
    FILE * vendedorFile;
    // Verifica se há algo de errado com o arquivo
    if ((vendedorFile = fopen(ARQ_VENDEDORES, "r+b")) == NULL) {
        printf("\n\n\tERRO: O arquivo %s NAO pode ser encontrado!\n", ARQ_VENDEDORES);
        pausarTela();
        return;
    }

    int codigo;
    printf("\n\n\tINFORME O CODIGO DO VENDEDOR A SE ALTERAR: ");
    read_int(&codigo);

    if (!vendedor_valido(codigo)) {
        printf("\tERRO: Vendedor com codigo invalido, por favor tente um valido.\n");
    } else {
        // Coloca o ponteiro de leitura no fim do vendedor anterior ao que deseja alterar
        fseek(vendedorFile, (codigo - 1) * sizeof(vendedor), SEEK_SET);
        
        // Lê-se os dados do vendedor de código especificado
        fread(&v, sizeof(vendedor), 1, vendedorFile); 
        printf("\tCodigo\t\tNome\n");
        printf("\t---------------------------------------\n");
        printf("\t%06d\t\t%s\n", v.codigo, v.nome);
        printf("\t---------------------------------------\n");

        char novoNome[41];
        printf("Alterar nome: ");
        read_line(v.nome, 41);

        fseek(vendedorFile, -sizeof(vendedor), SEEK_CUR);
        if (fwrite(&v, sizeof(vendedor), 1, vendedorFile) < 1) {
            printf("\tERRO: NAO foi possivel alterar o vendedor.\n");
        } else {
            printf("\tSUCESSO: Vendedor alterado!\n");
        }
    }
    pausarTela();
    fclose(vendedorFile);
}

bool vendedor_valido(int codigo) {
    vendedor v;
    FILE * vendedorFile;
    // Verifica se há algo de errado com o arquivo
    if ((vendedorFile = fopen(ARQ_VENDEDORES, "rb")) == NULL) {
        printf("\n\n\tERRO: O arquivo %s NAO pode ser encontrado!\n", ARQ_VENDEDORES);
        pausarTela();
        return false;
    }

    // Coloca o ponteiro de leitura no fim do vendedor anterior ao que deseja alterar
    fseek(vendedorFile, (codigo - 1) * sizeof(vendedor), SEEK_SET);
    // Lê-se os dados do vendedor de código especificado
    fread(&v, sizeof(vendedor), 1, vendedorFile); 
    fclose(vendedorFile);
    
    // Caso o codigo seja menos que 1 ou o fim do arquivo seja excedido
    return codigo < 1 || feof(vendedorFile) ? false : true;
}
