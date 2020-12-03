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
    if ((automoveisFile = fopen(ARQ_AUTOMOVEIS, "a+b")) == NULL) {
        printf(ERR_OPEN_ARC, ARQ_AUTOMOVEIS);
        pausarTela();
        return;
    }

    fseek(automoveisFile, 0, SEEK_END);
    // Encontra-se o ultimo carro cadastrado e cria-se este novo carro na próxima posição
    carro.codigo = ftell(automoveisFile) / sizeof(automovel) + 1;
    carro.vendido = false;

    printf("Marca do automovel: ");
    read_line(carro.marca, 21);
    printf("Modelo do automovel: ");
    read_line(carro.modelo, 21);
    printf("Ano do automovel: ");
    read_int(&carro.ano);
    printf("Preco do automovel: ");
    read_float(&carro.preco);

    if (fwrite(&carro, sizeof(automovel), 1, automoveisFile) < 1) {
        printf("\tERRO: NAO foi possivel cadastrar o automovel.\n");
    } else {
        printf("\tSUCESSO: Automovel cadastrado!\n");
    }

    pausarTela();
    fclose(automoveisFile);
}

void listar_todos_automoveis(void) {
    FILE * automoveisFile;
    if ((automoveisFile = fopen(ARQ_AUTOMOVEIS, "rb")) == NULL) {
        printf(ERR_OPEN_ARC, ARQ_AUTOMOVEIS);
        pausarTela();
        return;
    }
    
    fseek(automoveisFile, 0, SEEK_END);
    int TAMANHO = ftell(automoveisFile) / sizeof(automovel);
    automovel carros[TAMANHO];
    
    rewind(automoveisFile);
    fread(carros, sizeof(automovel), TAMANHO, automoveisFile);

    // Ordena os carros em ordem crescente de preço
    ordenar_automoveis(TAMANHO, carros);

    printf("\n\n\t\tLISTA DE CARROS CADASTRADOS\n\n");
    printf("\tCodigo\t\tMarca\t\t\tModelo\t\t     Ano\tPreco\n");
    printf("\t----------------------------------------------------------------------------------------------\n");
    int i;
    for (i = 0; i < TAMANHO; i++) {
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
        printf(ERR_OPEN_ARC, ARQ_AUTOMOVEIS);
        pausarTela();
        return;
    }

    if ((carrosAVendaFile = fopen(ARQ_A_VENDA, "w")) == NULL) {
        printf(ERR_OPEN_ARC, ARQ_A_VENDA);
        fclose(automoveisFile);
        pausarTela();
        return;
    }
    
    fseek(automoveisFile, 0, SEEK_END);
    int TAMANHO = ftell(automoveisFile) / sizeof(automovel);
    automovel carros[TAMANHO];
    automovel carrosAVenda[TAMANHO];

    rewind(automoveisFile);
    fread(carros, sizeof(automovel), TAMANHO, automoveisFile);

    int i, j = 0, tamCarrosAVenda;
    for (i = 0; i < TAMANHO; i++) {
        if (!carros[i].vendido) {
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
          carrosAVenda[i].codigo, 
          carrosAVenda[i].marca, 
          carrosAVenda[i].modelo, 
          carrosAVenda[i].ano,
          carrosAVenda[i].preco
        );
        printf("\t----------------------------------------------------------------------------------------------\n");
    }

    printf("\tGostaria de salvar em arquivo? [S]im | [N]ao\n");
    char op;
    read_line(&op, 1);

    if (op == 'S' || op == 's') {
        fprintf(carrosAVendaFile, "\tCodigo\t\tMarca\t\t\t\t Modelo\t\t\t\t  Ano\t\tPreco\n");
        fprintf(carrosAVendaFile, "\t----------------------------------------------------------------------------------------------\n");
        for (i = 0; i < tamCarrosAVenda; i++) {
          fprintf(carrosAVendaFile, "\t%06d\t\t%-21s%-21s%4d\t\t%.2f\n", 
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

    int codigo;
    printf("- ALTERANDO UM AUTOMOVEL\n\n");
    printf("Nao deseja estar aqui? Entre com '-1' para voltar ao menu principal.\n\n");
    printf("Codigo do automovel: ");
    read_int(&codigo);
    if (codigo == -1) return;

    automovel carro;
    FILE * automoveisFile;
    if ((automoveisFile = fopen(ARQ_AUTOMOVEIS, "r+b")) == NULL) {
        printf(ERR_OPEN_ARC, ARQ_AUTOMOVEIS);
        pausarTela();
        return;
    }

    if (!automovel_valido(codigo, &carro)) {
        printf("\tERRO: Automovel com codigo invalido, por favor tente novamente.\n");
    } else {        
        printf("\n\tCodigo\t\tMarca\t\tModelo\t\tAno\tPreco\n");
        printf("\t------------------------------------------------------------------------\n");
        printf("\t%06d\t\t%-16s%s\t\t%4d\t%.2f\n", 
          carro.codigo, carro.marca, carro.modelo, carro.ano, carro.preco
        );
        printf("\t------------------------------------------------------------------------\n");

        char novaMarca[21], novoModelo[21];
        float novoPreco;
        printf("\tAlterar marca: ");
        read_line(carro.marca, 21);
        printf("\tAlterar modelo: ");
        read_line(carro.modelo, 21);
        printf("\tAno do automovel: ");
        read_int(&carro.ano);
        printf("\tAlterar preco: ");
        read_float(&carro.preco);
        
        fseek(automoveisFile, (codigo - 1) * sizeof(automovel), SEEK_SET);
        if (fwrite(&carro, sizeof(automovel), 1, automoveisFile) < 1) {
            printf("\tERRO: NAO foi possivel alterar as informacoes do automovel.\n");
        } else {
            printf("\tSUCESSO: Automovel alterado!\n");
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
        if (i <= j) {
            aux = a[i];
            a[i++] = a[j];
            a[j--] = aux;
        }
    }

    if (j > inicio) quicksort(a, inicio, j);
    if (i < fim) quicksort(a, i, fim);
}

bool automovel_valido(int codigo, automovel *c) {
    FILE * automoveisFile;
    if ((automoveisFile = fopen(ARQ_AUTOMOVEIS, "rb")) == NULL) {
        printf(ERR_OPEN_ARC, ARQ_AUTOMOVEIS);
        pausarTela();
        return false;
    }

    fseek(automoveisFile, (codigo - 1) * sizeof(automovel), SEEK_SET);
    fread(c, sizeof(automovel), 1, automoveisFile);

    fclose(automoveisFile);
    return codigo < 1 || feof(automoveisFile) ? false : true;
}

void vender_automovel(int codigo) {
    automovel carro;
    FILE * automoveisFile;
    if ((automoveisFile = fopen(ARQ_AUTOMOVEIS, "r+b")) == NULL) {
        printf(ERR_OPEN_ARC, ARQ_AUTOMOVEIS);
        pausarTela();
        return;
    }
    // Coloca o ponteiro de leitura no fim do automovel anterior ao que deseja alterar
    fseek(automoveisFile, (codigo - 1) * sizeof(automovel), SEEK_SET); 
    fread(&carro, sizeof(automovel), 1, automoveisFile); 
    carro.vendido = true;
    fseek(automoveisFile, -sizeof(automovel), SEEK_CUR);
    fwrite(&carro, sizeof(automovel), 1, automoveisFile); 
    fclose(automoveisFile);
}
