#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include "estatistica.h"
#include "lista.h"

void media(NoLista** l){
    double soma = 0;
    double media = 0;
    NoLista *p;
    for(p = *l; p != NULL; p = p->prox){
        soma += p->info;
    }
    media = soma/qtdElementos(l);

    printf("A média é: %.2lf", media);

}

void mediana(NoLista **l){
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

    printf("A amplitude total é de: %.2lf\n", amplitudeTotal);
}

void varianciaDesvio(NoLista **l){
    double somaQuad = 0;
    double soma = 0;
    double media = 0;
    double variancia = 0;
    double desvio = 0;
    
    for(NoLista *p = *l; p != NULL; p = p->prox){
        soma += p->info;
    }
    media = soma/qtdElementos(l);

    for(NoLista *p = *l; p != NULL; p = p->prox){
        somaQuad += pow((p->info - media), 2);
    }

    variancia = somaQuad / (qtdElementos(l) - 1);
    desvio = sqrt(variancia);

    printf("A Variância é: %.2lf\n", variancia);
    printf("O Desvio Padrão é: %.2lf\n", desvio);
}

void coeficienteVariacao(NoLista **l){
    double somaQuad = 0;
    double soma = 0;
    double media = 0;
    double variancia = 0;
    double desvio = 0;
    double coeficienteVar = 0;
    
    for(NoLista *p = *l; p != NULL; p = p->prox){
        soma += p->info;
    }
    media = soma/qtdElementos(l);

    for(NoLista *p = *l; p != NULL; p = p->prox){
        somaQuad += pow((p->info - media), 2);
    }
    variancia = somaQuad / (qtdElementos(l) - 1);
    desvio = sqrt(variancia);

    coeficienteVar = (desvio / media) * 100;

    printf("O Coeficiente de Variação é de: %.2lf\n", coeficienteVar);

    if(coeficienteVar <= 10){
        printf("Baixa Dispersão\n");
    }else if(coeficienteVar >= 20){
        printf("Alta Dispersão\n");
    }else{
        printf("Média Dispersão\n");
    }
}

void covariancia(NoLista **l){
    double num = -1;
    double somaMult = 0;
    double covar = 0;
    int i = 1;
    NoLista *list2;
    criarLista(&list2);
    NoLista *q = list2;

    printf("Insira os valores da segunda lista (Digite -1 para sair)\n\n");
    do{
        printf("Valor %d: ", i);
        scanf("%lf", &num);
        if(num == -1)
            break;

        insereOrdenado(&list2, num);
        i++;
    }while(1);

    double soma = 0;
    double media1 = 0;
    NoLista *r;
    for(r = *l; r != NULL; r = r->prox){
        soma += r->info;
    }
    media1 = soma/qtdElementos(l);

    double media2 = 0;
    soma = 0;
    for(r = *l; r != NULL; r = r->prox){
        soma += r->info;
    }
    media2 = soma/qtdElementos(l);

    for(NoLista *p = *l; p != NULL && q!= NULL; p = p->prox, q = q->prox){
        somaMult += (p->info - media1) * (q->info - media2);
    }

    covar = somaMult / (qtdElementos(l) - 1);

    printf("A Covariância é: %.2lf\n", covar);
}

void correlacao(NoLista **l){
    /*
    double num = -1;
    double somaMult = 0;
    double covar = 0;
    int i = 1;
    NoLista *list2;
    criarLista(&list2);
    
    printf("Insira os valores da segunda lista (Digite -1 para sair)\n\n");
    do{
        printf("Valor %d: ", i);
        scanf("%lf", &num);
        if(num == -1)
        break;
        
        insereOrdenado(&list2, num);
        i++;
    }while(1);
    
    NoLista *q = list2;
    
    double soma = 0;
    double media1 = 0;
    NoLista *r;
    for(r = *l; r != NULL; r = r->prox){
        soma += r->info;
    }
    media1 = soma/qtdElementos(l);

    double media2 = 0;
    soma = 0;
    for(r = list2; r != NULL; r = r->prox){
        soma += r->info;
    }
    media2 = soma/qtdElementos(l);

    for(NoLista *p = *l; p != NULL && q != NULL; p = p->prox, q = q->prox){
        somaMult += (p->info - media1) * (q->info - media2);
    }

    covar = somaMult / (qtdElementos(l) - 1);

    double somaQuad = 0;
    double variancia1 = 0;
    double desvio1 = 0;
    double variancia2 = 0;
    double desvio2 = 0;

    for(NoLista *p = *l; p != NULL; p = p->prox){
        somaQuad += pow((p->info - media1), 2);
    }

    variancia1 = somaQuad / (qtdElementos(l) - 1);
    desvio1 = sqrt(variancia1);

    somaQuad = 0;
    for(NoLista *p = list2; p != NULL; p = p->prox){
        somaQuad += pow((p->info - media2), 2);
    }

    variancia2 = somaQuad / (qtdElementos(l) - 1);
    desvio2 = sqrt(variancia2);

    double correlacao = 0;
    correlacao = covar / (desvio1 * desvio2);

    printf("O coeficiente de Correlação é: %.2lf\n", correlacao);

    if(correlacao <= 0.5 && correlacao >= 0){
        printf("Relação linear fraca\n");
    }else if(correlacao > 0.8){
        printf("Relação linear forte\n");
    }else{
        printf("Relação linear moderada\n");
    }

    liberarLista(&list2);
    */
   printf("\nEm desenvolvimento...\n");
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

void varianciaDesvioAgrupados(int numClass, double pontoMedio[numClass], double frequenciaRelativa[numClass], int frequenciaAbsoluta[numClass], int totalAmostra){
    double mediaAgrup = 0;
    double somaQuad = 0;
    double varianciaAgrup = 0;
    double desvioAgrup = 0;
    double coeficienteVariacao = 0;

    for(int i = 0; i < numClass; i++){
        mediaAgrup += pontoMedio[i] * frequenciaRelativa[i];
    }

    for(int i = 0; i < numClass; i++){
        somaQuad += pow((pontoMedio[i] - mediaAgrup), 2) * frequenciaAbsoluta[i];
    }

    varianciaAgrup = somaQuad / (totalAmostra - 1);
    desvioAgrup = sqrt(varianciaAgrup);

    coeficienteVariacao = (desvioAgrup / mediaAgrup) * 100;

    printf("A Variância Agrupada é: %.2lf\n", varianciaAgrup);
    printf("O Desvio Agrupado é: %.2lf\n", desvioAgrup);

    printf("O Coeficiente de Variação é de: %.2lf\n", coeficienteVariacao);

    if(coeficienteVariacao <= 10){
        printf("Baixa Dispersão\n");
    }else if(coeficienteVariacao >= 20){
        printf("Alta Dispersão\n");
    }else{
        printf("Média Dispersão\n");
    }
}
