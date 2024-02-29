#include<stdio.h>

char gabarito[][10] = {
    {' ', ' ', ' ', '1', '*', '*', '1', ' ', ' ', ' '},
    {' ', '1', '1', '3', '3', '3', '1', ' ', ' ', ' '},
    {' ', '1', '*', '2', '*', '1', ' ', ' ', ' ', ' '},
    {'1', '2', '3', '3', '2', '1', ' ', ' ', ' ', ' '},
    {'1', '*', '2', '*', '1', ' ', ' ', ' ', ' ', ' '},
    {'1', '1', '2', '1', '1', '1', '1', '2', '1', '1'},
    {' ', ' ', ' ', '1', '1', '2', '*', '1', '*', '1'},
    {' ', ' ', ' ', '1', '*', '2', '1', '2', '1', '1'},
    {' ', ' ', '1', '2', '2', '1', ' ', ' ', ' ', ' '},
    {' ', ' ', '1', '*', '1', ' ', ' ', ' ', ' ', ' '}};

char visual[][10] = {
    {'?', '?', '?', '?', '?', '?', '?', '?', '?', '?'},
    {'?', '?', '?', '?', '?', '?', '?', '?', '?', '?'},
    {'?', '?', '?', '?', '?', '?', '?', '?', '?', '?'},
    {'?', '?', '?', '?', '?', '?', '?', '?', '?', '?'},
    {'?', '?', '?', '?', '?', '?', '?', '?', '?', '?'},
    {'?', '?', '?', '?', '?', '?', '?', '?', '?', '?'},
    {'?', '?', '?', '?', '?', '?', '?', '?', '?', '?'},
    {'?', '?', '?', '?', '?', '?', '?', '?', '?', '?'},
    {'?', '?', '?', '?', '?', '?', '?', '?', '?', '?'},
    {'?', '?', '?', '?', '?', '?', '?', '?', '?', '?'}};

void imprime(int l, int c){
    if(l <= 9){
        printf("[%c]", visual[l][c]);
        if((c + 1) <= 9){
            imprime(l, c+1);
        }else{
            printf("\n");
            imprime(l + 1, 0);
        }
    }
}
void buscaMina(int l, int c){
    if(l <= 9){
        if(gabarito[l][c] == '*'){
            printf("[%d][%d]\n", l, c);
        }
        if((c + 1) <= 9){
            buscaMina(l, c+1);
        }else{
            buscaMina(l+ 1, 0);
        }
    }
}
void abreMina(int l, int c){
    if((l >= 0)&&(l <= 9)&&(c >= 0)&&(c <= 9)){
        if(gabarito[l][c] == ' '){
            gabarito[l][c] = '.';
            visual[l][c] = ' ';
            abreMina(l-1, c-1);
            abreMina(l-1, c);
            abreMina(l-1, c+1);
            abreMina(l, c-1);
            abreMina(l, c+1);
            abreMina(l+1, c-1);
            abreMina(l+1, c);
            abreMina(l+1, c+1);
        }
    }
}
int main(int argc, char *argv[]) {
    int i, j, lin, col;
    printf("Digite [linha coluna]: ");
    scanf("%d %d", &lin, &col);
    buscaMina(0, 0);
    abreMina(lin,col);
    imprime(0, 0);
    return 0;
}
