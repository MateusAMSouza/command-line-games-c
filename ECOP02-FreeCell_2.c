#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<conio.h>

typedef struct noCarta{
    short int numero;
    char naipe;
    struct t *prox;
}tCarta;

tCarta *primMesa[8] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
tCarta *primNaipe[4] = {NULL,NULL,NULL,NULL};
tCarta *temp[4] = {NULL,NULL,NULL,NULL};
tCarta *primMonte = NULL;

bool ehVermelho(tCarta *carta){
    return ((carta -> naipe >= 3) && (carta -> naipe <= 4));
}//end ehVermelho

bool ehPreto(tCarta *carta){
    return ((carta -> naipe >=5)&&(carta -> naipe <= 6));
}//end ehPreto

bool CoresDiferentes(tCarta *carta1, tCarta *carta2){
    return ((ehVermelho(carta1) && ehPreto(carta2))||
             (ehPreto(carta1) && ehVermelho(carta2)));
}//end CoresDiferentes

void geraBaralho(){
    int i, j;
    tCarta *ult;
    //copas =3, ouros =4, paus = 5, espadas = 6
    for(i = 0; i < 4; i++){
        for(j = 1; j < 14; j++){
            if(primMonte == NULL){
                primMonte = (tCarta *)malloc(sizeof(tCarta));
                ult = primMonte;
            }else{
                ult -> prox = (tCarta *)malloc(sizeof(tCarta));
                ult = ult -> prox;
            }//end if else
            ult -> naipe = i+3;
            ult -> numero = j;
            ult -> prox = NULL;
        }//end for j
    }//end for i
}//end geraBaralho

void embaralhaBaralho(){
    int i, j, sort;
    tCarta *ant, *atual;

    for(i = 0; i < 26; i++){
        //total de mudanca
        sort = rand()%52;
        ant = NULL;
        atual = primMonte;
        for(j = 0; j < sort; j++){
            //localizar a carta no monte
            ant = atual;
            atual = atual->prox;
        }//end for j
        if(sort > 0){
            ant -> prox = atual -> prox;
            atual -> prox = primMonte;
            primMonte = atual;
        }//end if
    }//end for i
}//end embaralhaBaralho

void distribuiMesa(){
    int i = 0;
    tCarta *auxMonte, *auxMesa;

    while(primMonte != NULL){
        auxMonte = primMonte;
        primMonte = primMonte->prox;

        if(primMesa[i] == NULL){
            primMesa[i] = auxMonte;
            primMesa[i] -> prox = NULL;
        }else{
            auxMesa = primMesa[i];
            primMesa[i] = auxMonte;
            primMesa[i] -> prox = auxMesa;
        }//end if else
        if(primMonte == NULL){
            break;
        }//end if
        i = (i + 1)%8;
    }//end while
}//end distribuiMesa

void imprime(){
    tCarta *atual;
    int mesa, t, n;
    printf("[TEMP] = ");
    for(t = 0; t < 4; t++){
        //imprime o temporario
        atual = temp[t];
        if(atual == NULL){
            printf("%d-[    ] ", t);
        }else{
            printf("%d-[%02d/%c] ", t, atual -> numero, atual -> naipe, mesa);
        }
    }// end for temp
    printf("\n\n");
    for(n = 0; n < 4; n++){    //imprime os naipes
        atual = primNaipe[n];
        printf("[NAIPE %d] = ", n);
        while(atual != NULL){
            printf("[%02d/%c]", atual -> numero, atual -> naipe);
            atual = atual -> prox;
        }//end while
        printf("\n");
    }//end for naipes
    printf("\n\n");
    for(mesa = 0; mesa < 8; mesa++){
        //imprime as 8 mesas
        atual = primMesa[mesa];
        printf("[MESA %d] = ", mesa);
        while(atual != NULL){
            printf("[%02d/%c]", atual -> numero, atual -> naipe);
            atual = atual -> prox;
        }//end while
        printf("\n");
    }// end for 8 mesas
    printf("\n");
}// end imprime

void moveMesaTemp(){
    tCarta *ant, *atual, aux;
    int mesa, t;
    printf("Informe a mesa: ");
    scanf("%d", &mesa);
    getchar();
    printf("Informe a posicao do temporario: ");
    scanf("%d", &t);
    getchar();
    ant = NULL;
    atual = primMesa[mesa];
    if(((mesa < 0)||(mesa > 7))||((t < 0)||(t > 3))){
        printf("\nPosicao invalida\n\n");
    }else if(atual == NULL){
        //verifica se há carta na mesa
        printf("\nSem carta na MESA %d\n\n", mesa);
    }else{
        while(atual -> prox != NULL){
            ant = atual;
            atual = atual -> prox;
        }//end while
        if(temp[t] == NULL){
           if(ant == NULL){
                primMesa[mesa] = NULL;
           }//end if
           ant -> prox = NULL;
           temp[t] = atual;
           printf("\n");
        }else{
            printf("TEMP %d ocupado\n\n", t);
        }//end if else
    }//end if else
}//end moveMesaTemp

void moveTempMesa(){
    tCarta *atual, *ant, *aux;
    int mesa, t;
    printf("Informe a posicao do temporario: ");
    scanf("%d", &t);
    getchar();
    printf("Informe a mesa: ");
    scanf("%d", &mesa);
    getchar();
    ant = NULL;
    if(((mesa < 0)||(mesa > 7))||((t < 0)||(t > 3))){
        printf("\nPosicao invalida\n\n");
    }else if(temp[t] == NULL){
        //verifica se há carta na mesa
        printf("\nSem carta no TEMP %d\n\n", t);
    }else{
        if(primMesa[mesa] == NULL){
            primMesa[mesa] = temp[t];
            temp[t] = NULL;
        }else{
            atual = primMesa[mesa];
            while(atual -> prox != NULL){
                ant = atual;
                atual = atual -> prox;
            }//end while
            if((temp[t] -> numero) >= (atual -> numero)){
                //verifica se a carta do temp é menor
                printf("\nCarta do TEMP maior que da MESA %d\n\n", mesa);
            }else{
                if(CoresDiferentes(temp[t], atual)){
                    atual -> prox = temp[t];
                    temp[t] = NULL;
                    printf("\n");
                }else{
                    printf("\nCartas de cores iguais\n\n");
                }
            }//end if else if else
        }// end if else
    }// end else
}//end moveTempMesa

void moveMesaNaipe(){
    tCarta *atual, *ant, *aux;
    int mesa, n;
    printf("Informe a mesa: ");
    scanf("%d", &mesa);
    getchar();
    printf("Informe o naipe: ");
    scanf("%d", &n);
    getchar();
    ant = NULL;
    atual = primMesa[mesa];
    if((mesa > 7)||(mesa < 0)||(n > 3)||(n < 0)){
        printf("\nPosicao invalida\n\n");
    }else if(atual == NULL){ //verifica se há carta na mesa
        printf("\nSem carta na MESA %d\n\n", mesa);
    }else{
        while(atual -> prox != NULL){
            ant = atual;
            atual = atual -> prox;
        }//end while
    }
    if((primNaipe[n] == NULL)&&(atual -> numero != 1)){
        //verifica começo
        printf("\nA pilha do naipe deve comecar com [01/ ]\n\n");
    }else if((primNaipe[n] != NULL)&&(primNaipe[n] -> naipe != atual -> naipe)){
            //verifica se o naipe
        printf("\nCarta da MESA %d nao eh do mesmo NAIPE\n\n", mesa);
    }else if((primNaipe[n] != NULL)&&(atual -> numero) != ((primNaipe[n] -> numero)+1)){
            //verifica se a carta da mesa segue a sequencia do naipe
        printf("\nCarta da MESA %d nao segue a sequencia do NAIPE %d\n\n", mesa);
    }else{
        if(ant == NULL){
            primMesa[mesa] = NULL;
        }
        ant -> prox = NULL;
        if(primNaipe[n] == NULL){
            primNaipe[n] = atual;
        }else{
            aux = primNaipe[n];
            primNaipe[n] = atual;
            primNaipe[n] -> prox = aux;
            printf("\n");
        }//end if else
    }// end else
}//end moveMesaNaipe

void moveNaipeTemp(){
    tCarta *atual;
    int n, t;
    printf("Informe o naipe: ");
    scanf("%d", &n);
    printf("Informe a posicao do temporario: ");
    scanf("%d", &t);
    getchar();
    atual = primNaipe[n];
    if((n > 3)||(n < 0)||(t > 3)||(t < 0)){
        printf("\nPosicao invalida\n\n");
    }else if(atual == NULL){ //verifica se há carta na mesa
        printf("\nSem carta no NAIPE %d\n\n", n);
    }else if(temp[t] != NULL){
        printf("\nTEMP %d ocupado\n\n", t);
    }else{
        temp[t] = atual;
        primNaipe[n] = atual->prox;
        printf("\n");
        }//end else
    }//end moveNaipeTemp

void moveTempNaipe(){
    tCarta *atual, *ant, *aux;
    int n, t;
    printf("Informe a posicao do temporario: ");
    scanf("%d", &t);
    getchar();
    printf("Informe o naipe: ");
    scanf("%d", &n);
    getchar();
    ant = NULL;
    if((n > 3)||(n < 0)||(t > 3)||(t < 0)){
        printf("\nPosicao invalida\n\n");
    }else if(temp[t] == NULL){ //verifica se há carta na mesa
        printf("\nSem carta no TEMP %d\n\n", n);
    }else if((primNaipe[n] != NULL)&&(primNaipe[n] -> naipe != temp[t] -> naipe)){
            //verifica se o naipe
        printf("\nCarta do TEMP %d nao eh do mesmo NAIPE\n\n", t);
    }else if((primNaipe[n] != NULL)&&(temp[t] -> numero) != ((primNaipe[n] -> numero)+1)){
            //verifica se a carta da mesa segue a sequencia do naipe
        printf("\nCarta do TEMP %d nao segue a sequencia do NAIPE\n\n", t);
    }else{
        if(primNaipe[n] == NULL){
            primNaipe[n] = temp[t];
        }else{
            aux = primNaipe[n];
            primNaipe[n] = temp[t];
            primNaipe[n] -> prox = aux;
            temp[t] = NULL;
        }//end else
        temp[t] = NULL;
        printf("\n");
    }//end else
}//end moveTempNaipe

void moveNaipeMesa(){
    tCarta *atual, *ant, *aux;
    int mesa, n;
    printf("Informe o Naipe: ");
    scanf("%d", &n);
    getchar();
    printf("Informe a mesa: ");
    scanf("%d", &mesa);
    getchar();
    ant = NULL;
    if(((mesa < 0)||(mesa > 7))||((n < 0)||(n > 3))){
        printf("\nPosicao invalida\n\n");
    }else if(primNaipe[n] == NULL){
        //verifica se há carta na mesa
        printf("\nSem carta no NAIPE %d\n\n", n);
    }else{
        if(primMesa[mesa] == NULL){
            primMesa[mesa] = primNaipe[n];
            primNaipe[n] = primNaipe[n] -> prox;
        }else{
            atual = primMesa[mesa];
            while(atual -> prox != NULL){
                ant = atual;
                atual = atual -> prox;
            }//end while
            if((primNaipe[n] -> numero) >= (atual -> numero)){
                //verifica se a carta do temp é menor
                printf("\nCarta do NAIPE %d maior que da MESA %d\n\n", n, mesa);
            }else if(CoresDiferentes(primNaipe[n], atual)){
                    atual -> prox = primNaipe[n];
                    aux = atual -> prox;
                    primNaipe[n] = primNaipe[n] -> prox;
                    aux -> prox = NULL;
                    printf("\n");
                }else{
                    printf("\nCartas de cores iguais\n\n");
                }
            }//end if else
        }// end else
}//end moveNaipeMesa

void moveMesaMesa(){
    tCarta *atual_1, *atual_2, *ant_1, *ant_2, *aux;
    int m1, m2, bloco;
    printf("Informe a mesa de retirada: ");
    scanf("%d", &m1);
    getchar();
    printf("Informe a mesa de entrada: ");
    scanf("%d", &m2);
    getchar();
    /*printf("Informe a quantidade de cartas: ");
    scanf("%d", &bloco);
    getchar();*/
    ant_1 = NULL;
    ant_2 = NULL;
    atual_1 = primMesa[m1];
    atual_2 = primMesa[m2];
    if((m1 > 7)||(m1 < 0)||(m2 > 7)||(m2 < 0)){
        printf("\nPosicao invalida\n\n");
    }else if((atual_1 == NULL)||(atual_2 == NULL)){
        //verifica se há carta para ser retirada
        printf("\nSem carta em uma das  MESAS %d\n\n");
    }else{
        while(atual_1 -> prox != NULL){
            ant_1 = atual_1;
            atual_1 = atual_1 -> prox;
        }//end while
        while(atual_2 -> prox != NULL){
            ant_2 = atual_2;
            atual_2 = atual_2 -> prox;
        }//end while
        if((atual_1 -> numero) >= (atual_2 -> numero)){
            //verifica se a carta do temp é menor
            printf("\nCarta da MESA %d maior que da MESA %d\n\n", m1, m2);
        }else if(CoresDiferentes(atual_2, atual_1)){
            if(ant_1 == NULL){
                primMesa[m1] = NULL;
            }
            ant_1 -> prox = NULL;
            aux = atual_2;
            atual_2 -> prox = atual_1;
            printf("\n");
        }else{
            printf("\nCartas de cores iguais\n\n");
        }//end else
    }//end else
}//end moveMesaMesa

int main(int argc, char **argv){
    int op = 0;
    srand(time(NULL));
    geraBaralho();
    embaralhaBaralho();
    distribuiMesa();
    while(op != 8){
        imprime();
        printf("(1)Move Mesa-Temp\n");
        printf("(2)Move Mesa-Naipe\n");
        printf("(3)Move Temp-Mesa\n");
        printf("(4)Move Naipe-Temp\n");
        printf("(5)Move Temp-Naipe\n");
        printf("(6)Move Naipe-Mesa\n");
        printf("(7)Move Mesa-Mesa\n");
        printf("(8)Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();
        switch(op){
            case 1:
                moveMesaTemp();
                break;
            case 2:
                moveMesaNaipe();
                break;
            case 3:
                moveTempMesa();
                break;
            case 4:
                moveNaipeTemp();
                break;
            case 5:
                moveTempNaipe();
                break;
            case 6:
                moveNaipeMesa();
                break;
            case 7:
                moveMesaMesa();
                break;
            case 8:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpcao Invalida\n\n");
                break;
        }
    }
    return 0;
}
