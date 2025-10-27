#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "estatistica.h"
#include "lista.h"

void media(NoLista** l){
    if(!estaVazia(l)){
        double soma = 0;
        double media = 0;
        NoLista *p;
        for(p = *l; p != NULL; p = p->prox){
            soma += p->info;
        }
        media = soma/qtdElementos(l);

        printf("A média é: %.2lf", media);
    }else{
        printf("\nLista vazia!!!\n");
    }
}

void mediana(NoLista **l){
    if(!estaVazia(l)){
        int metade = 0;
        NoLista *p = *l;

        metade = qtdElementos(l) / 2;
        if(qtdElementos(l) % 2 == 0){
            for(int i = 0; i < metade - 1; i++){
                p = p->prox;
            }

            printf("A mediana é: %.2lf", (p->info + p->prox->info) / 2);
        }else{
            for(int i = 0; i < metade; i++){
                p = p->prox;
            }

            printf("A mediana é: %.2lf", p->info);
        }
    }else{
        printf("\nLista vazia!!!\n");
    }
}

void moda(NoLista **l) {
    
    if (estaVazia(l)) {
        printf("\nLista vazia!!!\n");
        return;
    }

    int N = qtdElementos(l);
    
    if (N == 1) {
        printf("Unimodal. A moda é: %.2lf\n", (*l)->info);
        return;
    }

    double valoresUnicos[N];
    int freqValores[N];
    int countUnique = 0;

    memset(freqValores, 0, sizeof(freqValores));

    NoLista *p;

    for (p = *l; p != NULL; p = p->prox) {
        double valorAtual = p->info;
        int encontrado = 0;

        for (int i = 0; i < countUnique; i++) {
            if (valoresUnicos[i] == valorAtual) {
                freqValores[i]++;
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            valoresUnicos[countUnique] = valorAtual;
            freqValores[countUnique] = 1;
            countUnique++;
        }
    }

    int maxFreq = 0;
    for (int i = 0; i < countUnique; i++) {
        if (freqValores[i] > maxFreq) {
            maxFreq = freqValores[i];
        }
    }

    int countModes = 0;
    for (int i = 0; i < countUnique; i++) {
        if (freqValores[i] == maxFreq) {
            countModes++;
        }
    }

    if (countModes == countUnique && countUnique > 1) {
        printf("Amodal (sem moda definida, todos os valores aparecem %d vez(es)).\n", maxFreq);
    } 
    else {
        if (countModes == 1) {
            printf("Unimodal. A moda é: ");
        } else if (countModes == 2) {
            printf("Bimodal. As modas são: ");
        } else {
            printf("Multimodal. As modas são: ");
        }

        int impressos = 0;
        for (int i = 0; i < countUnique; i++) {
            if (freqValores[i] == maxFreq) {
                printf("%.2lf", valoresUnicos[i]);
                impressos++;
                if (impressos < countModes) {
                    printf(", "); 
                }
            }
        }
        printf(" (frequência: %d)\n", maxFreq);
    }
}

void mediaAgrupada(int numClass, double pontoMedio[numClass], double frequenciaRelativa[numClass]){
    double mediaAgrup = 0;
    for(int i = 0; i < numClass; i++){
        mediaAgrup += pontoMedio[i] * frequenciaRelativa[i];
    }

    printf("O valor da média agrupada é: %.2lf", mediaAgrup);
}

void medianaAgrupada(int numClass, int totalAmostra, int frequenciaAbsoluta[numClass], double limitInf[numClass], double limitSup[numClass]){
    int localMediana = 0;
    double mediana = totalAmostra / 2.0;
    double linfMd = 0;
    double totalFreqAbsolAnt = 0;
    double amplitudeClasse = 0;
    double freqAbsolClasse = 0;
    double medianaAgrupada = 0;

    for(int i = 0; i < numClass; i++){
        if(localMediana > mediana){
            linfMd = limitInf[i - 1];
            amplitudeClasse = limitSup[i - 1] - limitInf[i - 1];
            freqAbsolClasse = frequenciaAbsoluta[i - 1];
            break;
        }
        else{
            localMediana += frequenciaAbsoluta[i];
        }
    }

    for(int i = 0; limitInf[i] < linfMd; i++){
        totalFreqAbsolAnt += frequenciaAbsoluta[i];
    }

    medianaAgrupada = linfMd + (((totalAmostra / 2) - totalFreqAbsolAnt) * amplitudeClasse) / freqAbsolClasse;

    printf("A mediana agrupada é: %.2lf", medianaAgrupada);

}

void modaAgrupada(int numClass, int frequenciaAbsoluta[numClass], double limitInf[numClass], double limitSup[numClass]){
    int maior = 0;
    int posMaior = 0;
    double limInfMod = 0;
    double delta1 = 0;
    double delta2 = 0;
    double amplitude = 0;
    double modaAgrupada = 0;

    for(int i = 0; i < numClass; i ++){
        if(frequenciaAbsoluta[i] > maior){
            maior = frequenciaAbsoluta[i];
            posMaior = i;
            limInfMod = limitInf[i];
            amplitude = limitSup[i] - limitInf[i];
        }
    }

    if(posMaior == 0){
        delta1 = frequenciaAbsoluta[posMaior];
        delta2 = frequenciaAbsoluta[posMaior] - frequenciaAbsoluta[posMaior + 1];
    }else if(posMaior == numClass - 1){
        delta1 = frequenciaAbsoluta[posMaior] - frequenciaAbsoluta[posMaior - 1];
        delta2 = frequenciaAbsoluta[posMaior];
    }else{
        delta1 = frequenciaAbsoluta[posMaior] - frequenciaAbsoluta[posMaior - 1];
        delta2 = frequenciaAbsoluta[posMaior] - frequenciaAbsoluta[posMaior + 1];
    }

    modaAgrupada = limInfMod + (delta1 * amplitude)/(delta1 + delta2);

    printf("A moda agrupada é: %.2lf\n", modaAgrupada);
}
