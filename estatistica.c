#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include "estatistica.h"
#include "lista.h"

double media(NoLista** l){
    double soma = 0;
    double media = 0;
    NoLista *p;
    for(p = *l; p != NULL; p = p->prox){
        soma += p->info;
    }
    media = soma/qtdElementos(l);

    return media;
}

void mediana(NoLista **l){
    int metade = 0;
    NoLista *p = *l;

    metade = qtdElementos(l) / 2;
    if(qtdElementos(l) % 2 == 0){
        for(int i = 0; i < metade - 1; i++){
            p = p->prox;
        }

        printf("A mediana eh: %.2lf", (p->info + p->prox->info) / 2);
    }else{
        for(int i = 0; i < metade; i++){
            p = p->prox;
        }

        printf("A mediana eh: %.2lf", p->info);
    }
}

void moda(NoLista **l) {
    
    if (estaVazia(l)) {
        printf("\nLista vazia!!!\n");
        return;
    }

    int N = qtdElementos(l);
    
    if (N == 1) {
        printf("Unimodal. A moda eh: %.2lf\n", (*l)->info);
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
            printf("Unimodal. A moda eh: ");
        } else if (countModes == 2) {
            printf("Bimodal. As modas sao: ");
        } else {
            printf("Multimodal. As modas sao: ");
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
        printf(" (frequencia: %d)\n", maxFreq);
    }
}

void amplitudeTotal(NoLista **l){
    NoLista *q = *l;
    double amplitudeTotal = 0;
    double menorValor = q->info;
    double maiorValor = 0;

    for(NoLista *p = *l; p != NULL; p = p->prox){
        if (p->info > maiorValor){
            maiorValor = p->info;
        }   
    }

    amplitudeTotal = maiorValor - menorValor;

    printf("A amplitude total eh de: %.2lf\n", amplitudeTotal);
}

double variancia(NoLista **l){
    double somaQuad = 0;
    double mediaL = 0;
    double variancia = 0;

    mediaL = media(l);

    for(NoLista *p = *l; p != NULL; p = p->prox){
        somaQuad += pow((p->info - mediaL), 2);
    }

    variancia = somaQuad / (qtdElementos(l) - 1);

    return variancia;
}

double desvio(NoLista **l, double variancia){
    return sqrt(variancia);
}

void coeficienteVariacao(NoLista **l){
    double somaQuad = 0;
    double mediaL = 0;
    double var = 0;
    double des = 0;
    double coeficienteVar = 0;
    
    mediaL = media(l);

    var = variancia(l);
    des = desvio(l , var);

    coeficienteVar = (des / mediaL) * 100;

    printf("O Coeficiente de Variacao eh de: %.2lf\n", coeficienteVar);

    if(coeficienteVar <= 10){
        printf("Baixa Dispersao\n");
    }else if(coeficienteVar >= 20){
        printf("Alta Dispersao\n");
    }else{
        printf("Média Dispersao\n");
    }
}

void covariancia(){
    double num = -1;
    double somaMult = 0;
    double covar = 0;
    int i = 1;

    NoLista *list;
    criarLista(&list);
    printf("Insira os valores (Digite -1 para sair)\n\n");

    do{
        printf("Valor %d: ", i);
        scanf("%lf", &num);
        if(num == -1)
            break;

        insere(&list, num);
        i++;
    }while(1);

    NoLista *list2;
    criarLista(&list2);
    
    printf("Insira os valores da segunda lista (Digite -1 para sair)\n\n");
    do{
        printf("Valor %d: ", i);
        scanf("%lf", &num);
        if(num == -1)
        break;
        
        insere(&list2, num);
        i++;
    }while(1);
    
    NoLista *q = list2;
    double media1 = 0;
    NoLista *r;

    media1 = media(&list);

    double media2 = 0;
    media2 = media(&list2);

    for(NoLista *p = list; p != NULL; p = p->prox){
        somaMult += (p->info - media1) * (q->info - media2);
        q = q->prox;
    }

    covar = somaMult / (qtdElementos(&list) - 1);

    printf("A Covariancia eh: %.2lf\n", covar);
}

void correlacao(){
    double num = -1;
    double somaMult = 0;
    int i = 1;

    NoLista *list;
    criarLista(&list);
    printf("Insira os valores (Digite -1 para sair)\n\n");

    do{
        printf("Valor %d: ", i);
        scanf("%lf", &num);
        if(num == -1)
            break;

        insere(&list, num);
        i++;
    }while(1);

    NoLista *list2;
    criarLista(&list2);

    printf("Insira os valores da segunda lista (Digite -1 para sair)\n\n");
    i = 1;
    do{
        printf("Valor %d: ", i);
        scanf("%lf", &num);
        if(num == -1)
        break;
        
        insere(&list2, num);
        i++;
    }while(1);

    NoLista *q = list2;

    for(NoLista *p = list; p != NULL; p = p->prox){
        somaMult += (p->info) * (q->info);
        q = q->prox;
    }

    double soma1 = 0;
    for(NoLista *r = list; r != NULL; r = r->prox){
        soma1 += r->info;
    }

    double soma2 = 0;
    for(NoLista *r = list2; r != NULL; r = r->prox){
        soma2 += r->info;
    }

    double soma1Quad = 0;
    for(NoLista *r = list; r != NULL; r = r->prox){
        soma1Quad += pow(r->info, 2);
    }

    double soma2Quad = 0;
    for(NoLista *r = list2; r != NULL; r = r->prox){
        soma2Quad += pow(r->info, 2);
    }

    double quadSoma1 = 0;
    double quadSoma2 = 0;

    quadSoma1 = pow(soma1, 2);
    quadSoma2 = pow(soma2, 2);

    double correlacao = 0;

    correlacao = (somaMult - ((soma1 * soma2) / qtdElementos(&list))) / (sqrt(soma1Quad - (quadSoma1 / qtdElementos(&list))) * sqrt(soma2Quad - (quadSoma2 / qtdElementos(&list))));

    printf("A correlação é %.2lf\n", correlacao);
}


double mediaAgrupada(int numClass, double pontoMedio[numClass], double frequenciaRelativa[numClass]){
    double mediaAgrup = 0;
    for(int i = 0; i < numClass; i++){
        mediaAgrup += pontoMedio[i] * frequenciaRelativa[i];
    }

    return mediaAgrup;
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

    printf("A mediana agrupada eh: %.2lf", medianaAgrupada);

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

    printf("A moda agrupada eh: %.2lf\n", modaAgrupada);
}

void varianciaDesvioAgrupados(int numClass, double pontoMedio[numClass], double frequenciaRelativa[numClass], int frequenciaAbsoluta[numClass], int totalAmostra){
    double mediaAgrup = 0;
    double somaQuad = 0;
    double varianciaAgrup = 0;
    double desvioAgrup = 0;
    double coeficienteVariacao = 0;

    mediaAgrup = mediaAgrupada(numClass, pontoMedio, frequenciaRelativa);

    for(int i = 0; i < numClass; i++){
        somaQuad += pow((pontoMedio[i] - mediaAgrup), 2) * frequenciaAbsoluta[i];
    }

    varianciaAgrup = somaQuad / (totalAmostra - 1);
    desvioAgrup = sqrt(varianciaAgrup);

    coeficienteVariacao = (desvioAgrup / mediaAgrup) * 100;

    printf("A Variancia Agrupada eh: %.2lf\n", varianciaAgrup);
    printf("O Desvio Agrupado eh: %.2lf\n", desvioAgrup);

    printf("O Coeficiente de Variacao eh de: %.2lf\n", coeficienteVariacao);

    if(coeficienteVariacao <= 10){
        printf("Baixa Dispersao\n");
    }else if(coeficienteVariacao >= 20){
        printf("Alta Dispersao\n");
    }else{
        printf("Media Dispersao\n");
    }
}
