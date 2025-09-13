#include <stdio.h>
#include <stdlib.h>

#define N 10

void initBoard(int b[N][N]) {
    for (int i=0;i<N;++i) for (int j=0;j<N;++j) b[i][j]=0;
}

void printBoardShips(int b[N][N]) {
    printf("Tabuleiro (0 livre, 3 navio):\n");
    for (int i=0;i<N;++i) {
        for (int j=0;j<N;++j) printf("%d ", b[i][j]);
        printf("\n");
    }
    printf("\n");
}

void printCoordinatesOfShip(const char *name, int coords[][2], int len) {
    printf("%s (tamanho %d) coordenadas:\n", name, len);
    for (int k=0;k<len;++k) {
        printf(" (%d,%d)", coords[k][0], coords[k][1]);
    }
    printf("\n\n");
}

void applySkill(int affected[N][N], int skillRows, int skillCols, int skill[skillRows][skillCols], int centerR, int centerC) {
    int centerSkillR = skillRows/2;
    int centerSkillC = skillCols/2;
    for (int i=0;i<skillRows;++i) {
        for (int j=0;j<skillCols;++j) {
            if (skill[i][j] == 1) {
                int boardR = centerR + (i - centerSkillR);
                int boardC = centerC + (j - centerSkillC);
                if (boardR >= 0 && boardR < N && boardC >= 0 && boardC < N) {
                    affected[boardR][boardC] = 1;
                }
            }
        }
    }
}

void printSkillMatrix(int rows, int cols, int skill[rows][cols]) {
    for (int i=0;i<rows;++i) {
        for (int j=0;j<cols;++j) printf("%d ", skill[i][j]);
        printf("\n");
    }
    printf("\n");
}

void printAffectedBoard(int affected[N][N]) {
    printf("Áreas afetadas (0 = não, 1 = afetado):\n");
    for (int i=0;i<N;++i) {
        for (int j=0;j<N;++j) printf("%d ", affected[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main() {
    int board[N][N];
    initBoard(board);

    /* --- Definição manual dos 4 navios (variáveis no código) --- */
    /* Escolhi aqui 4 navios: horizontal, vertical, diagonal down-right, diagonal down-left */
    /* Você pode alterar as posições/tamanhos abaixo para testar outros casos */

    /* Navio 1: horizontal tamanho 5, início (1,1) */
    int ship1Len = 5;
    int ship1Coords[5][2];
    int r1 = 1, c1 = 1;
    for (int k=0;k<ship1Len;++k) {
        ship1Coords[k][0] = r1;
        ship1Coords[k][1] = c1 + k;
        board[r1][c1 + k] = 3;
    }

    /* Navio 2: vertical tamanho 4, início (3,7) */
    int ship2Len = 4;
    int ship2Coords[4][2];
    int r2 = 3, c2 = 7;
    for (int k=0;k<ship2Len;++k) {
        ship2Coords[k][0] = r2 + k;
        ship2Coords[k][1] = c2;
        board[r2 + k][c2] = 3;
    }

    /* Navio 3: diagonal down-right tamanho 3, início (6,2) */
    int ship3Len = 3;
    int ship3Coords[3][2];
    int r3 = 6, c3 = 2;
    for (int k=0;k<ship3Len;++k) {
        ship3Coords[k][0] = r3 + k;
        ship3Coords[k][1] = c3 + k;
        board[r3 + k][c3 + k] = 3;
    }

    /* Navio 4: diagonal down-left tamanho 2, início (0,9) -> fica em (0,9) e (1,8) */
    int ship4Len = 2;
    int ship4Coords[2][2];
    int r4 = 0, c4 = 9;
    for (int k=0;k<ship4Len;++k) {
        ship4Coords[k][0] = r4 + k;
        ship4Coords[k][1] = c4 - k;
        board[r4 + k][c4 - k] = 3;
    }

    /* Exibir tabuleiro com navios e coordenadas */
    printBoardShips(board);
    printCoordinatesOfShip("Navio 1 (horizontal)", ship1Coords, ship1Len);
    printCoordinatesOfShip("Navio 2 (vertical)", ship2Coords, ship2Len);
    printCoordinatesOfShip("Navio 3 (diagonal DR)", ship3Coords, ship3Len);
    printCoordinatesOfShip("Navio 4 (diagonal DL)", ship4Coords, ship4Len);

    /* --- Matrizes de habilidade (usando os padrões do enunciado) --- */
    int coneRows = 3, coneCols = 5;
    int cone[3][5] = {
        {0,0,1,0,0},
        {0,1,1,1,0},
        {1,1,1,1,1}
    };

    int crossRows = 3, crossCols = 5;
    int cross[3][5] = {
        {0,0,1,0,0},
        {1,1,1,1,1},
        {0,0,1,0,0}
    };

    int octaRows = 3, octaCols = 5;
    int octa[3][5] = {
        {0,0,1,0,0},
        {0,1,1,1,0},
        {0,0,1,0,0}
    };

    /* --- Aplicar habilidades em centros escolhidos (variáveis no código) --- */
    /* Você pode mudar centerConeR/centerConeC etc. para testar */
    int centerConeR = 2, centerConeC = 4;
    int centerCrossR = 5, centerCrossC = 5;
    int centerOctaR = 8, centerOctaC = 2;

    int affectedCone[N][N], affectedCross[N][N], affectedOcta[N][N], affectedCombined[N][N];
    initBoard(affectedCone); initBoard(affectedCross); initBoard(affectedOcta); initBoard(affectedCombined);

    applySkill(affectedCone, coneRows, coneCols, cone, centerConeR, centerConeC);
    applySkill(affectedCross, crossRows, crossCols, cross, centerCrossR, centerCrossC);
    applySkill(affectedOcta, octaRows, octaCols, octa, centerOctaR, centerOctaC);

    /* criar mapa combinado (1 se qualquer habilidade afetou) */
    for (int i=0;i<N;++i) for (int j=0;j<N;++j)
        affectedCombined[i][j] = (affectedCone[i][j] || affectedCross[i][j] || affectedOcta[i][j]) ? 1 : 0;

    /* --- Exibir cada habilidade (matriz) e o tabuleiro afetado --- */
    printf("Habilidade: CONE (matriz):\n");
    printSkillMatrix(coneRows, coneCols, cone);
    printf("Centro aplicado em (%d,%d)\n", centerConeR, centerConeC);
    printAffectedBoard(affectedCone);

    printf("Habilidade: CRUZ (matriz):\n");
    printSkillMatrix(crossRows, crossCols, cross);
    printf("Centro aplicado em (%d,%d)\n", centerCrossR, centerCrossC);
    printAffectedBoard(affectedCross);

    printf("Habilidade: OCTAEDRO (matriz):\n");
    printSkillMatrix(octaRows, octaCols, octa);
    printf("Centro aplicado em (%d,%d)\n", centerOctaR, centerOctaC);
    printAffectedBoard(affectedOcta);

    printf("Mapa combinado de habilidades (qualquer uma afetou):\n");
    printAffectedBoard(affectedCombined);

    /* Opcional: exibir quais navios foram atingidos (interseção navio x afetado) */
    printf("Intersecção navios x habilidades (3 = navio, 1 = área afetada -> mostrando 3+1 = 4 quando ambos):\n");
    for (int i=0;i<N;++i) {
        for (int j=0;j<N;++j) {
            int val = 0;
            if (board[i][j] == 3) val += 3;
            if (affectedCombined[i][j] == 1) val += 1;
            printf("%d ", val);
        }
        printf("\n");
    }
    printf("\n(na matriz acima: 0=livre, 3=navio não afetado, 1=área afetada sem navio, 4=navio afetado)\n");

    return 0;
}
