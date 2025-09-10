#include <stdio.h>

int main() {
    // =============================================
    // BATALHA NAVAL - NIVEL AVENTUREIRO
    // Tabuleiro 10x10 com navios horizontais,
    // verticais e também diagonais
    // =============================================

    int tabuleiro[10][10]; // matriz que representa o tabuleiro
    int i, j;

    // --------------------------
    // Inicializando o tabuleiro
    // --------------------------
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0; // começa tudo com 0 (água)
        }
    }

    // --------------------------
    // Criando os navios (tamanho 3)
    // --------------------------
    int navio1[3] = {3, 3, 3}; // navio horizontal
    int navio2[3] = {3, 3, 3}; // navio vertical
    int navio3[3] = {3, 3, 3}; // navio diagonal ↘
    int navio4[3] = {3, 3, 3}; // navio diagonal ↙

    // --------------------------
    // Posicionando navio horizontal
    // Linha 2, colunas C-E
    // --------------------------
    int linhaH = 1, colunaH = 2; 
    for (i = 0; i < 3; i++) {
        tabuleiro[linhaH][colunaH + i] = navio1[i];
    }

    // --------------------------
    // Posicionando navio vertical
    // Linha 6-8, coluna H
    // --------------------------
    int linhaV = 5, colunaV = 7;
    for (i = 0; i < 3; i++) {
        tabuleiro[linhaV + i][colunaV] = navio2[i];
    }

    // --------------------------
    // Posicionando navio diagonal ↘
    // Linha 1-3, colunas A-C
    // --------------------------
    int linhaD1 = 0, colunaD1 = 0;
    for (i = 0; i < 3; i++) {
        tabuleiro[linhaD1 + i][colunaD1 + i] = navio3[i];
    }

    // --------------------------
    // Posicionando navio diagonal ↙
    // Linha 3-5, colunas J-H
    // --------------------------
    int linhaD2 = 2, colunaD2 = 9;
    for (i = 0; i < 3; i++) {
        tabuleiro[linhaD2 + i][colunaD2 - i] = navio4[i];
    }

    // --------------------------
    // Exibindo o tabuleiro
    // --------------------------
    printf("=== TABULEIRO BATALHA NAVAL ===\n\n");
    printf("Legenda: 0 = agua | 3 = navio\n\n");

    // imprimir letras das colunas (A até J)
    printf("   "); 
    for (j = 0; j < 10; j++) {
        printf(" %c ", 'A' + j);
    }
    printf("\n");

    // imprimir cada linha com número
    for (i = 0; i < 10; i++) {
        printf("%2d ", i + 1);
        for (j = 0; j < 10; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    printf("\nNavios posicionados com sucesso!\n");

    return 0;
}
