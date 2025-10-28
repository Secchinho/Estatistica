#ifndef ESTATISTICA_H
#define ESTATISTICA_H

#include "lista.h"

void media(NoLista **l);
void mediana(NoLista **l);
void moda(NoLista **l);
void amplitudeTotal(NoLista **l);
void varianciaDesvio(NoLista **l);
void coeficienteVariacao(NoLista **l);
void covariancia();
void correlacao();
void mediaAgrupada(int numClass, double pontoMedio[numClass], double frequenciaRelativa[numClass]);
void medianaAgrupada(int numClass, int totalAmostra, int frequenciaAbsoluta[numClass], double limitInf[numClass], double limitSup[numClass]);
void modaAgrupada(int numClass, int frequenciaAbsoluta[numClass], double limitInf[numClass], double limitSup[numClass]);
void varianciaDesvioAgrupados(int numClass, double pontoMedio[numClass], double frequenciaRelativa[numClass], int frequenciaAbsoluta[numClass], int totalAmostra);

#endif