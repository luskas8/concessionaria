/* automovel.c
 *
 * Modulo de implementação das funções de automoveis
 *
 * Artur Freire dos Santos
 * Lucas Silva dos Anjos
 * 
 * Ciências da Computação
 * 
 * 27/11/2020
*/

#include <stdio.h>
#include "automovel.h"

void cadastrar_automovel(void) {
    automovel carro;
    FILE * automoveisFile;
    // Verifica se há algo de errado com o arquivo
    if ((automoveisFile = fopen(ARQ_AUTOMOVEIS, "r+b")) == NULL) {
        printf("\n\n\tERRO: O arquivo %s NAO pode ser encontrado!\n", ARQ_AUTOMOVEIS);
        pausarTela();
        return;
    }

    // Move o ponteiro de posição para o final do arquivo
    fseek(automoveisFile, 0, SEEK_END);
    // Encontra-se o ultimo carro cadastrado e cria-se este novo carro na próxima posição
    carro.codigo = ftell(automoveisFile) / sizeof(automovel) + 1;
    carro.vendido = false;

    printf("Marca do carro: ");
    read_line(carro.marca, 21);
    printf("Modelo do carro: ");
    read_line(carro.modelo, 21);
    printf("Ano do carro: ");
    read_int(&carro.ano);
    printf("Preco do carro: ");
    read_float(&carro.preco);

    // Escreve no arquivo as informações desse novo carro
    if (fwrite(&carro, sizeof(automovel), 1, automoveisFile) < 1) {
        printf("\tERRO: NAO foi possivel cadastrar o carro.\n");
    } else {
        printf("\tSUCESSO: Carro cadastrado!\n");
    }

    pausarTela();
    fclose(automoveisFile);
}

void listar_todos_automoveis(void) {
    FILE * automoveisFile;
    if ((automoveisFile = fopen(ARQ_AUTOMOVEIS, "rb")) == NULL) {
        printf("\n\n\tERRO: O arquivo %s NAO pode ser encontrado!\n", ARQ_AUTOMOVEIS);
        pausarTela();
        return;
    }
    
    // Move o ponteiro de posição para o final do arquivo
    fseek(automoveisFile, 0, SEEK_END);
    // Calcula-se o tamanha do vetor de carros cadastrados
    int TAMANHO = ftell(automoveisFile) / sizeof(automovel);
    automovel carros[TAMANHO];
    
    // Retornar o ponteiro de leitura para o começo do arquivo
    rewind(automoveisFile);
    fread(carros, sizeof(automovel), TAMANHO, automoveisFile);

    // Ordena os carros em ordem crescente de preço
    ordenar_automoveis(TAMANHO, carros);

    printf("\n\n\t\tLISTA DE CARROS CADASTRADOS\n\n");
    printf("\tCodigo\t\tMarca\t\t\tModelo\t\t     Ano\tPreco\n");
    printf("\t----------------------------------------------------------------------------------------------\n");
    int i;
    for (i = 0; i < TAMANHO; i++) {
        // Lista as informações do automovel i
        printf("\t%03d\t\t%-21s\t%-21s%4d\t%.2f\n", 
          carros[i].codigo, 
          carros[i].marca, 
          carros[i].modelo, 
          carros[i].ano,
          carros[i].preco
        );
        printf("\t----------------------------------------------------------------------------------------------\n");
    }
    fclose(automoveisFile);
    pausarTela();
}

void listar_automoveis_a_venda(void) {
    FILE * automoveisFile, * carrosAVendaFile;
    if ((automoveisFile = fopen(ARQ_AUTOMOVEIS, "rb")) == NULL) {
        printf("\n\n\tERRO: O arquivo %s NAO pode ser encontrado!\n", ARQ_AUTOMOVEIS);
        pausarTela();
        return;
    }

    if ((carrosAVendaFile = fopen(ARQ_A_VENDA, "w")) == NULL) {
        printf("\n\n\tERRO: O arquivo %s NAO pode ser encontrado!\n", ARQ_A_VENDA);
        fclose(automoveisFile);
        pausarTela();
        return;
    }
    
    // Move o ponteiro de posição para o final do arquivo
    fseek(automoveisFile, 0, SEEK_END);
    // Calcula-se o tamanha do vetor de carros cadastrados
    int TAMANHO = ftell(automoveisFile) / sizeof(automovel);
    automovel carros[TAMANHO];
    automovel carrosAVenda[TAMANHO];

    // Retornar o ponteiro de leitura para o começo do arquivo
    rewind(automoveisFile);
    fread(carros, sizeof(automovel), TAMANHO, automoveisFile);

    int i, j = 0, tamCarrosAVenda;
    for (i = 0; i < TAMANHO; i++) {
        if (!carros[i].vendido) {
            // Coloca o carro i na posição j do vetor de carros a vendidos
            carrosAVenda[j++] = carros[i];
        }
    }
    fclose(automoveisFile);

    tamCarrosAVenda = j;

    // Ordena os carros em ordem crescente de preço
    ordenar_automoveis(j, carrosAVenda);

    printf("\n\n\t\tLISTA DE CARROS A VENDA\n\n");
    printf("\tCodigo\t\tMarca\t\t\tModelo\t\t     Ano\tPreco\n");
    printf("\t----------------------------------------------------------------------------------------------\n");
    for (i = 0; i < j; i++) {
        printf("\t%06d\t\t%-21s\t%-21s%4d\t%.2f\n", 
          carros[i].codigo, 
          carros[i].marca, 
          carros[i].modelo, 
          carros[i].ano,
          carros[i].preco
        );
        printf("\t----------------------------------------------------------------------------------------------\n");
    }

    printf("\tGostaria de salvar em arquivo? [S]im | [N]ao\n");
    char op;
    read_line(&op, 1);

    if (op == 'S' || op == 's') {
        fprintf(carrosAVendaFile, "\tCodigo\t\tMarca\t\t\t\t\t\t\t\t Modelo\t\t\t\t\t\t\t\tAno\t\t\t\t\tPreco\n");
        fprintf(carrosAVendaFile, "\t----------------------------------------------------------------------------------------------\n");
        for (i = 0; i < tamCarrosAVenda; i++) {
          fprintf(carrosAVendaFile, "\t%06d\t\t%-21s%-21s%4d\t\t\t\t%.2f\n", 
            carros[i].codigo, 
            carros[i].marca, 
            carros[i].modelo, 
            carros[i].ano,
            carros[i].preco
          );
          fprintf(carrosAVendaFile, "\t----------------------------------------------------------------------------------------------\n");
        }
    }
    
    fclose(carrosAVendaFile);
    printf("\n");
}

void alterar_automovel(void) {
    automovel carro;
    FILE * automoveisFile;
    if ((automoveisFile = fopen(ARQ_AUTOMOVEIS, "r+b")) == NULL) {
        printf("\n\n\tERRO: O arquivo %s NAO pode ser encontrado!\n", ARQ_AUTOMOVEIS);
        pausarTela();
        return;
    }

    int codigo;
    printf("\n\n\tINFORME O CODIGO DO CARRO A SE ALTERAR: ");
    read_int(&codigo);

    // Caso o codigo seja menos que 1 ou o fim do arquivo seja excedido
    if (!automovel_valido(codigo)) {
        printf("\tERRO: Carro com codigo invalido, por favor tente novamente.\n");
    } else {
        // Coloca o ponteiro de leitura no fim do automovel anterior ao que deseja alterar
        fseek(automoveisFile, (codigo - 1) * sizeof(automovel), SEEK_SET); 
        // Lê-se os dados do automovel de código especificado e os armazena na variavel carro
        fread(&carro, sizeof(automovel), 1, automoveisFile); 
        printf("\tCodigo\t\tMarca\t\tModelo\t\tAno\tPreco\n");
        printf("\t------------------------------------------------------------------------\n");
        printf("\t%06d\t\t%s\t\t%s\t\t%4d\t%.2f\n", 
          carro.codigo, carro.marca, carro.modelo, carro.ano, carro.preco
        );
        printf("\t------------------------------------------------------------------------\n");

        char novaMarca[21], novoModelo[21];
        float novoPreco;
        printf("\tAlterar marca: ");
        read_line(carro.marca, 21);
        printf("\tAlterar modelo: ");
        read_line(carro.modelo, 21);
        printf("\tAno do carro: ");
        read_int(&carro.ano);
        printf("\tAlterar preco: ");
        read_float(&carro.preco);
        
        fseek(automoveisFile, -sizeof(automovel), SEEK_CUR);
        if (fwrite(&carro, sizeof(automovel), 1, automoveisFile) < 1) {
            printf("\tERRO: NAO foi possivel alterar as informacoes do carro.\n");
        } else {
            printf("\tSUCESSO: Carro alterado!\n");
        }
    }
    
    fclose(automoveisFile);
    pausarTela();
}

void ordenar_automoveis(int TAMANHO, automovel carros[]) {
    quicksort(carros, 0, TAMANHO);
}

void quicksort(automovel a[], int inicio, int fim) {
    int i = inicio, j = fim-1;
    automovel aux, x = a[(inicio + fim) / 2];
    
    while (i <= j) {
        while (a[i].preco < x.preco) i++; 
        while (a[j].preco > x.preco) j--;
        // Caso I e J não tenham se cruzado ou se encontrado, trocam de posição
        if (i <= j) {
            aux = a[i];
            a[i++] = a[j];
            a[j--] = aux;
        }
    }

    // Se J não chegou no inicio faz-se o processo de novo
    if (j > inicio) quicksort(a, inicio, j);
    // Se I não chegou ao fim faz-se o processo de novo
    if (i < fim) quicksort(a, i, fim);
}

bool automovel_valido(int codigo) {
    automovel carro;
    FILE * automoveisFile;
    if ((automoveisFile = fopen(ARQ_AUTOMOVEIS, "rb")) == NULL) {
        printf("\n\n\tERRO: O arquivo %s NAO pode ser encontrado!\n", ARQ_AUTOMOVEIS);
        pausarTela();
        return false;
    }

    // Coloca o ponteiro de leitura no fim do automovel anterior ao que deseja alterar
    fseek(automoveisFile, (codigo - 1) * sizeof(automovel), SEEK_SET);
    // Lê-se os dados do automovel de código especificado
    fread(&carro, sizeof(automovel), 1, automoveisFile); 

    fclose(automoveisFile);
    return codigo < 1 || feof(automoveisFile) ? false : true;
}

void vender_automovel(int codigo) {
    automovel carro;
    FILE * automoveisFile;
    if ((automoveisFile = fopen(ARQ_AUTOMOVEIS, "r+b")) == NULL) {
        printf("\n\n\tERRO: O arquivo %s NAO pode ser encontrado!\n", ARQ_AUTOMOVEIS);
        pausarTela();
        return;
    }

    // Caso o codigo seja menos que 1 ou o fim do arquivo seja excedido
    if (!automovel_valido(codigo)) {
        printf("\tERRO: Carro com codigo invalido, por favor tente um valido.\n");
        pausarTela();
    } else {
        // Coloca o ponteiro de leitura no fim do automovel anterior ao que deseja alterar
        fseek(automoveisFile, (codigo - 1) * sizeof(automovel), SEEK_SET); 
        // Lê-se os dados do automovel de código especificado
        fread(&carro, sizeof(automovel), 1, automoveisFile); 
        carro.vendido = true;
        fseek(automoveisFile, -sizeof(automovel), SEEK_CUR);
        // Altera no arquivo o automovel desejado
        fwrite(&carro, sizeof(automovel), 1, automoveisFile); 
    }
    fclose(automoveisFile);
}