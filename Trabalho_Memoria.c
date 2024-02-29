#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
int main(int argc, char *arg[]){
    int i, j, l1, l2, c1, c2, aux, j1, j2, jogadas, turno;
    char resultado;
    char visual[6][6] = {
    {' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' '},
    };
    char gabarito[6][6] = {
    {'a', 'a', 'b', 'b', 'c', 'c'},
    {'d', 'd', 'e', 'e', 'f', 'f'},
    {'g', 'g', 'h', 'h', 'i', 'i'},
    {'j', 'j', 'k', 'k', 'l', 'l'},
    {'m', 'm', 'n', 'n', 'o', 'o'},
    {'p', 'p', 'q', 'q', 'r', 'r'},
    };
    srand(time(NULL));
    for(i = 0; i < 73; i++){
        l1 = rand()%6;
        c1 = rand()%6;
        l2 = rand()%6;
        c2 = rand()%6;
        aux = gabarito[l2][c2];
        gabarito[l2][c2] = gabarito[l1][c1];
        gabarito[l1][c1] = aux;
    }
    j1 = 0;
    j2 = 0;
    turno = 1;
    while(jogadas < 36){
        printf("    0  1  2  3  4  5\n");
        for(i = 0; i < 6; i++){
            printf(" %d ", i);
            for(j = 0; j < 6; j++){
                printf("[%c]", visual[i][j]);
            }
            printf("\n");
        }
        printf("Jogador 1 = %d / Jogador 2 = %d", j1, j2);
        printf("\n(Jogador %d) [linha 1 coluna 1 linha 2 coluna 2]: ", turno);
        scanf("%d %d %d %d", &l1, &c1, &l2, &c2);
        if((l1 >= 0)&&(l1 < 6)&&(c1 >= 0)&&(c1 < 6)&&(l2 >= 0)&&(l2 < 6)&&(c2 >= 0)&&(c2 < 6)&&((l1 != l2)||(c1 != c2))){
                if((visual[l1][c1] == ' ')&&visual[l2][c2] == ' '){
                    if(gabarito[l1][c1] == gabarito[l2][c2]){
                        visual[l1][c1] = gabarito[l1][c1];
                        visual[l2][c2] = gabarito[l2][c2];
                        printf("    0  1  2  3  4  5\n");
                        for(i = 0; i < 6; i++){
                            printf(" %d ", i);
                            for(j = 0; j < 6; j++){
                                printf("[%c]", visual[i][j]);
                            }
                            printf("\n");
                        }
                        printf("Iguais\n");
                        if(turno == 1){
                            j1 = j1 + 2;
                            turno = 2;
                        }
                        else{
                            j2 = j2 + 2;
                            turno = 1;
                        }
                        jogadas = jogadas + 2;
                    }
                    else{
                        visual[l1][c1] = gabarito[l1][c1];
                        visual[l2][c2] = gabarito[l2][c2];
                        printf("    0  1  2  3  4  5\n");
                        for(i = 0; i < 6; i++){
                            printf(" %d ", i);
                            for(j = 0; j < 6; j++){
                                printf("[%c]", visual[i][j]);
                            }
                            printf("\n");
                        }
                        printf("Diferentes\n");
                        visual[l1][c1] = ' ';
                        visual[l2][c2] = ' ';
                        if(turno == 1){
                            turno = 2;
                        }
                        else{
                            turno = 1;
                        }
                    }
                }
                else{
                    printf("JOGUE NOVAMENTE, uma das pecas ja foi aberta\n");
                }
            }
            else{
                printf("JOGUE NOVAMENTE, coordenadas invalidas\n");
            }
        }
        if(j1 > j2){
            printf("\nO jogador 1 venceu!\n");
        }
        else{
            if(j1 < j2){
                printf("\nO jogador 2 venceu!\n");
            }
            else{
                printf("\nHouve um empate!\n");
            }
        }
    return 0;
}
