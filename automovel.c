/* automovel.c
 *
 * Modulo de imprementação das funções de automoveis
 *
 * Artur Freire
 * Lucas Silva dos Anjos
 * 
 * Ciência da Computação
 * 
 * 21/11/2020
*/

#include <stdio.h>
#include "automovel.h"

void cadastrar_automovel(void) {
    automovel carro;
    FILE * automoveisFile;
    // Verifica se há algo de errado com o arquivo
    if ((automoveisFile = fopen(ARQ_AUTOMOVEIS, "r+b")) == NULL) {
        printf("\n\n\tERRO: Algo de errado com seu arquivo %s, por favor verifique e tente novamente!\n", ARQ_AUTOMOVEIS);
        pausarTela();
        return;
    }

    // Move o ponteiro de posição para o final do arquivo
    fseek(automoveisFile, 0, SEEK_END);
    // Encontra-se o ultimo carro cadastrado e cria-se este novo carro na próxima posição
    carro.codigo = ftell(automoveisFile) / sizeof(automovel) + 1;
    carro.vendido = false;

    printf("Marca do carro: ");
    scanf(" %20[^\n]", &carro.marca);
    printf("Modelo do carro: ");
    scanf(" %20[^\n]", &carro.modelo);
    printf("Ano do carro: ");
    scanf("%d", &carro.ano);
    printf("Preco do carro: ");
    scanf("%f", &carro.preco);

    // Escreve no arquivo as informações desse novo carro
    fwrite(&carro, sizeof(automovel), 1, automoveisFile);
    fclose(automoveisFile);
}

void listar_todos_automoveis(void) {
    FILE * automoveisFile;
    if ((automoveisFile = fopen(ARQ_AUTOMOVEIS, "r+b")) == NULL) {
        printf("\n\n\tERRO: Algo de errado com seu arquivo %s, por favor verifique e tente novamente!\n", ARQ_AUTOMOVEIS);
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
    printf("\tCodigo\t\tMarca\t\tModelo\t\tPreco\n");
    printf("\t------------------------------------------------------------------------\n");
    int i;
    for (i = 0; i < TAMANHO; i++) {
        printf("\t%d\t\t%s\t\t%s\t\t%.2f\n", carros[i].codigo, carros[i].marca, carros[i].modelo, carros[i].preco);
        printf("\t------------------------------------------------------------------------\n");
    }
    pausarTela();
}

void ordenar_automoveis(int TAMANHO, automovel carros[]) {
    quicksort(carros, 0, TAMANHO);
}

void quicksort(automovel a[], int inicio, int fim) {
    int i = inicio, j = fim-1;
    automovel aux, x = a[(inicio + fim) / 2];
    
    while (i <= j) {
        while (a[i].preco < x.preco) i++; // Caso o preço do item I seja maior que o X, vai ao próximo item
        while (a[j].preco > x.preco) j--; // Caso o preço do item J seja menor que o X, vai ao item anterior
        if (i <= j) {
            // Caso I e J não tenham se cruzado ou se encontrado, trocam de posição
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