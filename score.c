#include "score.h"
#include <stdio.h>
#include <stdlib.h>

int bestScore(){
    FILE *lerPontuacao;
    lerPontuacao = fopen("score.txt", "r");
    char aux[100];
    int best = 0;
    while(fgets(aux, 100, lerPontuacao) != NULL){
        if(atoi(aux) > best){
            best = atoi(aux);
        }
    }
    fclose(lerPontuacao);
    return best;
}

int mostRecentScore(){
    FILE *lerPontuacao;
    int recent = 0;
    char aux[100];
    lerPontuacao = fopen("score.txt", "r");
    while(fgets(aux, 100, lerPontuacao) != NULL){
        recent = atoi(aux);
    }
    fclose(lerPontuacao);
    return recent;
}