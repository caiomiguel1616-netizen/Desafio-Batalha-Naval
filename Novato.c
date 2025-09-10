#include <stdio.h>

int main() {
    // =============================================
    // BATALHA NAVAL - NIVEL NOVATO
    // Tabuleiro 10x10 e dois navios (um horizontal e outro vertical)
    // =============================================

    int tabuleiro[10][10]; // matriz que representa o tabuleiro
    int i, j;

    // --------------------------
    // Inicializando o tabuleiro
    // --------------------------
    // Preenche todo o tabuleiro com 0 (que significa água)
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // --------------------------
    // Criando navios (tamanho 3)
    // --------------------------
    // Cada navio vai ocupar 3 posições
    int navioHorizontal[3] = {3, 3, 3}; 
    int navioVertical[3]   = {3, 3, 3};

    // Coordenadas iniciais dos navios
    int linhaH = 2, colunaH = 1;  // navio horizontal começa na linha 2, coluna 1
    int linhaV = 5, colunaV = 7;  // navio vertical começa na linha 5, coluna 7

    // --------------------------
    // Posicionando navio horizontal
    // --------------------------
    for (i = 0; i < 3; i++) {
        tabuleiro[linhaH][colunaH + i] = navioHorizontal[i];
    }

    // --------------------------
    // Posicionando navio vertical
    // --------------------------
    for (i = 0; i < 3; i++) {
        tabuleiro[linhaV + i][colunaV] = navioVertical[i];
    }

    // --------------------------
    // Exibindo o tabuleiro
    // --------------------------
    printf("=== TABULEIRO BATALHA NAVAL ===\n\n");
    printf("Legenda: 0 = agua | 3 = navio\n\n");

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]); // mostra cada célula com espaço
        }
        printf("\n"); // quebra de linha ao terminar a linha do tabuleiro
    }

    printf("\nNavios posicionados com sucesso!\n");

    return 0;
}
