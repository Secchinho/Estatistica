#include <stdio.h>
#include <stdlib.h>
#include "estatistica.h"
#include "lista.h"

void media(NoLista** l){
    if(!estaVazia(l)){
        double soma = 0;
        double media = 0;
        NoLista *p;
        for(p = *l; p->prox != NULL; p = p->prox){
            soma += p->info;
        }
        soma += p->info;
        media = soma/qtdElementos(l);

        printf("A média é: %.2lf", media);
    }else{
        printf("\nLista vazia!!!\n");
    }
}

void mediaAgrupada(NoLista **l);
