#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
int ramo = 0;
int farinha_de_osso = 0;
int baga = 0;
int jogadas = 1;
char caverna[25][90];
void inicializa(){
    int i, j, lin, col;
    for(i = 0; i < 25; i++){
        for(j = 0; j < 90; j++){
            caverna[i][j] = ' ';
        }
    }
    for(j = 0; j < 10; j++){
        col = rand()%90;
        caverna[0][col] = ':';
    }
    for(j = 0; j < 4; j++){
        col = rand()%89;
        for(i = 24; i > 19; i--){
            caverna[i][col] = '.';
            caverna[i][col+1] = '.';
        }
    }
    for(j = 0; j < 3; j++){
        col = rand()%88;
        for(i = 24; i > 18; i--){
            caverna[i][col] = '.';
            caverna[i][col+1] = '.';
            caverna[i][col+2] = '.';
        }
    }
    for(j = 0; j < 10; j++){
        col = rand()%90;
        if(caverna[24][col] == ' '){
            caverna[24][col] = '^';
        }else{
            j--;
        }
    }
    for(i = 0; i < 13; i++){
        lin = 6 + rand()%13;
        col = rand()%90;
        if(caverna[lin][col] == ' '){
            caverna[lin][col] = 'V';
        }else{
            i--;
        }
    }
    for(i = 0; i < 31; i++){
        lin = 6 + rand()%13;
        col = rand()%90;
        if(caverna[lin][col] == ' '){
            caverna[lin][col] = 'W';
        }else{
            i--;
        }
    }
}
void imprime(){
    int i, j;
    printf("\n              11111111112222222222333333333344444444445555555555666666666677777777778888888888\n");
    printf("    012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n");
    for(i = 0; i < 25; i++){
        printf("[%2d]", i);
        for(j = 0; j < 90; j++){
            printf("%c", caverna[i][j]);
        }
        printf("\n");
    }
}
void fertilizar(){
    int lin,col;
    if(farinha_de_osso > 0){
        printf("Fertilizar ramo [linha coluna]: ");
        scanf("%d %d", &lin, &col);
        getchar();
        if((lin > 0)&&(lin <= 24)&&(col >= 0)&&(col <= 89)){
            if(caverna[lin][col] == ':'){
                caverna[lin][col] = '%';
                farinha_de_osso--;
                jogadas++;
            }else{
                printf("\n--Coordenada sem ramo--\n");
            }
        }else{
            printf("\n--Coordenada invalida--\n");
        }
    }else{
        printf("\n--Sem saldo de Farinha de osso--\n");
    }
}
void colher(){
    int lin, col;
    printf("Colher ramo ou baga [linha coluna]: ");
    scanf("%d %d", &lin, &col);
    getchar();
    if((lin > 0)&&(lin <= 24)&&(col >= 0)&&(col <= 89)){
        if((caverna[lin][col] == ':')||(caverna[lin][col] == '%')){
            for(lin = lin; lin < 25; lin++){
                if(caverna[lin][col] == ':'){
                    caverna[lin][col] = ' ';
                    ramo++;
                }else{
                    if(caverna[lin][col] == '%'){
                        caverna[lin][col] = ' ';
                        baga++;
                    }else{
                        lin = 25;
                    }
                }
            }
            jogadas++;
        }else{
            printf("\n--Coordenada sem ramo ou baga--\n");
        }
    }else{
        printf("\n--Coordenada invalida--\n");
    }
}
void ninho(){
    int lin, col;
    if(ramo >= 4){
        printf("Construir ninho [linha coluna]: ");
        scanf("%d %d", &lin, &col);
        if((lin >= 0)&&(lin < 24)&&(col >= 0)&&(col <= 89)){
            if(caverna[lin+1][col] == '.'){
                caverna[lin][col] = '#';
                ramo = ramo - 4;
                jogadas++;
            }else{
                printf("\n--Sem pedra elevada--\n");
            }
        }else{
            printf("\n--Coordenada invalida--\n");
        }
    }else{
        printf("\n--Sem saldo de ramos--\n");
    }
}
void alimentar(){
    int lin, col;
    if(baga > 0){
        printf("Alimentar coruja [linha coluna]: ");
        scanf("%d %d", &lin, &col);
        getchar();
        if((lin >= 0)&&(lin <= 24)&&(col >= 0)&&(col <= 89)){
            if(caverna[lin][col] == 'v'){
                caverna[lin][col] = 'V';
                baga--;
                jogadas++;
            }else{
                if((caverna[lin][col] == 'V')&&(lin <= 22)&&(caverna[lin+1][col] == 'V')&&(caverna[lin+2][col] == '#')){
                    caverna[lin+2][col] = 'v';
                    baga--;
                    jogadas++;
                }else{
                    printf("\n--Nao pode alimentar--\n");
                }
            }
        }else{
            printf("\n--Coordenada invalida--\n");
        }
    }else{
        printf("\n--Sem saldo de baga--\n");
    }
}
void mover(){
    int lin0,col0, lin1, col1;
    char aux;
    printf("Mover coruja - Origem [linha coluna]: ");
    scanf("%d %d", &lin0, &col0);
    getchar();
    if((lin0 >= 0)&&(lin0 <= 24)&&(col0 >= 0)&&(col0 <= 89)){
        if((caverna[lin0][col0] == 'V')||(caverna[lin0][col0] == 'v')){
            printf("Mover coruja - Destino [linha coluna]: ");
            scanf("%d %d", &lin1, &col1);
            if((lin1 >= 0)&&(lin1 <= 24)&&(col1 >= 0)&&(col1 <= 89)){
                if((abs(lin1 - lin0) <= 1)&&(abs(col1 - col0) <= 1)){
                    if(caverna[lin1][col1] == ' '){
                        aux = caverna[lin0][col0];
                        caverna[lin0][col0] = ' ';
                        caverna[lin1][col1] = aux;
                        jogadas++;
                    }else{
                        if((caverna[lin0][col0] == 'V')&&(caverna[lin1][col1] == 'W')){
                            caverna[lin0][col0] = ' ';
                            caverna[lin1][col1] = 'V';
                            jogadas++;
                            farinha_de_osso++;
                        }else{
                            printf("\n--Movimento invalido--\n");
                        }
                    }
                }else{
                    printf("\n--Destino nao vizinho--\n");
                }
            }else{
                printf("\n--Coordenada de destino invalida--\n");
            }
        }else{
            printf("\n--Sem coruja na origem--\n");
        }
    }else{
        printf("\n--Coordenada de origem invalida--\n");
    }
}
void dia(){
    int i, j, lin, col;
    for(i = 0; i < 25; i++){
        for(j = 0; j < 90; j++){
            if(caverna[i][j] == 'W'){
                caverna[i][j] = ' ';
            }
        }
    }
    for(j = 0; j < 90; j++){
        if((caverna[0][j] == ':')&&(rand()%100 < 15)){
            for(i = 1; i < 25; i++){
                if(caverna[i][j] == ' '){
                    caverna[i][j] = ':';
                    break;
                }
            }
        }
    }
    for(j = 0; j < 90; j++){
        if((caverna[24][j] == '^')&&(rand()%100 < 15)){
            for(i = 23; i > 19; i--){
                if(caverna[i][j] == ' '){
                    caverna[i][j] = '^';
                    break;
                }
            }
        }
    }
    for(i = 0; i < 31; i++){
        lin = 6 + rand()%13;
        col = rand()%90;
        if(caverna[lin][col] != 'W'){
            caverna[lin][col] = 'W';
        }else{
            i--;
        }
    }
    jogadas++;
}
int main(int argc, char *argv[]){
    printf("--Bem-vindo(a) ao simulador de corujas!--\n");
    char opcao = ' ';
    srand(time(NULL));
    inicializa();
    while(opcao != 's'){
        imprime();
        printf("\nRamo = %d  Farinha de osso = %d  Baga = %d\n", ramo, farinha_de_osso, baga);
        printf("(f)ertilizar / (c)olher / (n)inho / (a)limentar / (m)over / (d)ia / (s)air  ");
        printf("[Jogada %d]: ", jogadas);
        opcao = getch();
        printf("%c\n", opcao);
        switch(opcao){
            case 'f':
                fertilizar();
                break;
            case 'c':
                colher();
                break;
            case 'n':
                ninho();
                break;
            case 'a':
                alimentar();
                break;
            case 'm':
                mover();
                break;
            case 'd':
                dia();
                break;
            case 's':
                break;
            default:
                printf("\n[Opcao invalida]\n");
        }
        if(jogadas > 7){
            jogadas = 0;
            imprime();
            dia();
        }
    }
    return 0;
}


