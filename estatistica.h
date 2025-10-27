#ifndef ESTATISTICA_H
#define ESTATISTICA_H

#include "lista.h"

void media(NoLista **l);
void mediana(NoLista **l);
void moda(NoLista **l);
void mediaAgrupada(int numClass, double pontoMedio[numClass], double frequenciaRelativa[numClass]);
void medianaAgrupada(int numClass, int totalAmostra, int frequenciaAbsoluta[numClass], double limitInf[numClass], double limitSup[numClass]);
void modaAgrupada(int numClass, int frequenciaAbsoluta[numClass], double limitInf[numClass], double limitSup[numClass]);
void varianciaDesvio();
void coeficienteVariacao();
void curtose();
void assimetria();
void separatriz();
void correlacao();

#endif