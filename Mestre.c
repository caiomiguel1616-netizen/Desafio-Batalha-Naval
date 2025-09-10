#include <stdio.h>
#include <stdlib.h> // sai abs()

/*
  BATALHA NAVAL - NÍVEL MESTRE
  Adicionando habilidades (cone, cruz, octaedro) e sobrepondo no tabuleiro
  Comentários no estilo "feito por aluno" explicando o que cada parte faz.
*/

#define TAM 10
#define NAV 3      // valor que representa navio no tabuleiro
#define EFEITO 5   // valor que representa área afetada pela habilidade
#define S 5        // tamanho das matrizes de habilidade (5x5)

/*
  Observação: neste código, ao aplicar a habilidade nós escrevemos EFEITO (5)
  no tabuleiro, sobrescrevendo o que havia antes (por exemplo navio = 3).
  Se você preferir que navio permaneça visível (prioridade 3), eu ajusto.
*/

int main() {
    int tabuleiro[TAM][TAM];
    int i, j;

    // --------------------------
    // Inicializa tabuleiro com água (0)
    // --------------------------
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0; // 0 = água
        }
    }

    // --------------------------
    // Posiciona os 4 navios (tamanho 3)
    // mantém as posições que você tinha
    // --------------------------
    // navio horizontal -> linha 2, colunas C-E  (índices r=1, c=2..4)
    for (i = 0; i < 3; i++) tabuleiro[1][2 + i] = NAV;

    // navio vertical -> linhas 6-8, coluna H (índices r=5..7, c=7)
    for (i = 0; i < 3; i++) tabuleiro[5 + i][7] = NAV;

    // navio diagonal ↘ -> linha 1-3, colunas A-C (r=0..2, c=0..2)
    for (i = 0; i < 3; i++) tabuleiro[0 + i][0 + i] = NAV;

    // navio diagonal ↙ -> linha 3-5, colunas J-H (r=2..4, c=9..7)
    for (i = 0; i < 3; i++) tabuleiro[2 + i][9 - i] = NAV;

    // --------------------------
    // Criar matrizes de habilidade SxS dinamicamente
    // --------------------------
    int cone[S][S];
    int cruz[S][S];
    int octa[S][S];

    // inicializa com zeros
    for (i = 0; i < S; i++) {
        for (j = 0; j < S; j++) {
            cone[i][j] = 0;
            cruz[i][j] = 0;
            octa[i][j] = 0;
        }
    }

    // --------------------------
    // Construir CONE (apontando para baixo)
    // ideia: topo central é origem (linha 0 dentro da máscara),
    // e a largura cresce conforme a linha aumenta
    // --------------------------
    int center_col_cone = S / 2; // 2 para S=5
    for (i = 0; i < S; i++) {
        for (j = 0; j < S; j++) {
            // se coluna j estiver dentro do "raio" da linha i, marca 1
            // raio = i (na linha 0 apenas coluna central; linha 1 central±1; etc)
            if ( (j >= center_col_cone - i) && (j <= center_col_cone + i) ) {
                cone[i][j] = 1;
            } else {
                cone[i][j] = 0;
            }
        }
    }

    // --------------------------
    // Construir CRUZ
    // centro na posição S/2,S/2; marca linha e coluna centrais
    // --------------------------
    int center = S / 2; // 2 para S=5
    for (i = 0; i < S; i++) {
        for (j = 0; j < S; j++) {
            if (i == center || j == center) cruz[i][j] = 1;
            else cruz[i][j] = 0;
        }
    }

    // --------------------------
    // Construir OCTAEDRO (vista frontal => losango)
    // aqui usamos distância de Manhattan ao centro para formar um losango
    // condição: |dr| + |dc| <= 1  (pequeno losango 5x5)
    // --------------------------
    for (i = 0; i < S; i++) {
        for (j = 0; j < S; j++) {
            int manh = abs(i - center) + abs(j - center);
            if (manh <= 1) octa[i][j] = 1;
            else octa[i][j] = 0;
        }
    }

    // --------------------------
    // Definir pontos de origem no tabuleiro (fixo, definidos aqui)
    // (linhas/colunas em índices 0..9)
    // - Cone: vamos colocar a ponta (topo) em r=1, c=3  (fica no topo-médio)
    // - Cruz: centro da cruz em r=5, c=5 (meio do tabuleiro)
    // - Octa: centro do losango em r=8, c=2 (parte inferior esquerda)
    // --------------------------
    int origemCone_r = 1, origemCone_c = 3;
    int origemCruz_r = 5, origemCruz_c = 5;
    int origemOcta_r = 8, origemOcta_c = 2;

    // --------------------------
    // Sobrepor CONE no tabuleiro
    // centerRowCone = 0 (origem no topo da máscara), centerColCone = center_col_cone
    // fórmula de mapeamento:
    // board_r = origem_r - centerRow + r
    // board_c = origem_c - centerCol + c
    // --------------------------
    int centerRowCone = 0;
    int centerColCone = center_col_cone;
    for (i = 0; i < S; i++) {
        for (j = 0; j < S; j++) {
            if (cone[i][j] == 1) {
                int br = origemCone_r - centerRowCone + i;
                int bc = origemCone_c - centerColCone + j;
                // checar limites do tabuleiro
                if (br >= 0 && br < TAM && bc >= 0 && bc < TAM) {
                    tabuleiro[br][bc] = EFEITO; // marca área afetada
                }
            }
        }
    }

    // --------------------------
    // Sobrepor CRUZ no tabuleiro (centro da máscara mapeado para origem)
    // centerRow = centerCol = center
    // --------------------------
    for (i = 0; i < S; i++) {
        for (j = 0; j < S; j++) {
            if (cruz[i][j] == 1) {
                int br = origemCruz_r - center + i;
                int bc = origemCruz_c - center + j;
                if (br >= 0 && br < TAM && bc >= 0 && bc < TAM) {
                    tabuleiro[br][bc] = EFEITO;
                }
            }
        }
    }

    // --------------------------
    // Sobrepor OCTAEDRO (losango) no tabuleiro (centro da máscara mapeado)
    // --------------------------
    for (i = 0; i < S; i++) {
        for (j = 0; j < S; j++) {
            if (octa[i][j] == 1) {
                int br = origemOcta_r - center + i;
                int bc = origemOcta_c - center + j;
                if (br >= 0 && br < TAM && bc >= 0 && bc < TAM) {
                    tabuleiro[br][bc] = EFEITO;
                }
            }
        }
    }

    // --------------------------
    // Exibição final do tabuleiro
    // --------------------------
    printf("=== TABULEIRO COM HABILIDADES ===\n\n");
    printf("Legenda: 0 = agua | 3 = navio | 5 = area afetada\n\n");

    // cabeçalho das colunas (A..J)
    printf("   ");
    for (j = 0; j < TAM; j++) printf(" %c ", 'A' + j);
    printf("\n");

    // imprimir linhas numeradas
    for (i = 0; i < TAM; i++) {
        printf("%2d ", i + 1);
        for (j = 0; j < TAM; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    // --------------------------
    // (opcional) imprimir as máscaras geradas para verificação
    // --------------------------
    printf("\nMatriz CONE (1=afetado na máscara):\n");
    for (i = 0; i < S; i++) {
        for (j = 0; j < S; j++) printf("%d ", cone[i][j]);
        printf("\n");
    }

    printf("\nMatriz CRUZ (1=afetado na máscara):\n");
    for (i = 0; i < S; i++) {
        for (j = 0; j < S; j++) printf("%d ", cruz[i][j]);
        printf("\n");
    }

    printf("\nMatriz OCTA (1=afetado na máscara):\n");
    for (i = 0; i < S; i++) {
        for (j = 0; j < S; j++) printf("%d ", octa[i][j]);
        printf("\n");
    }

    printf("\nFim da execução.\n");
    return 0;
}
