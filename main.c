#include <stdio.h>
#include <stdlib.h>
#include "estatistica.h"
#include "lista.h"

int main(){
    double num = -1;
    int i = 1;
    int op = 0;
    NoLista *list;
    criarLista(&list);

    menu_inicial:
        printf("\nROL de dados ou dados agrupados?\n");
        printf("-------------------------------------\n");
        printf("1 - ROL de dados\n");
        printf("2 - Dados agrupados\n");
        printf("3 - Covariancia\n");
        printf("4 - Correlacao\n");
        printf("5 - Sair\n");
        printf("-------------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &op);

    switch (op){
        case 1:
            printf("Insira os valores (Digite -1 para sair)\n\n");

            do{
                printf("Valor %d: ", i);
                scanf("%lf", &num);
                if(num == -1)
                    break;

                insereOrdenado(&list, num);
                i++;
            }while(1);

            do{
                printf("\nDigite a operacao desejada: \n");
                printf("-------------------------------------\n");
                printf("1 - Media\n");
                printf("2 - Mediana\n");
                printf("3 - Moda\n");
                printf("4 - Amplitude Total\n");
                printf("5 - Coeficiente de Variacao\n");
                printf("6 - Variancia e Desvio Padrao\n");
                printf("7 - Imprime lista\n");
                printf("8 - Sair para o menu\n");
                printf("-------------------------------------\n");
                printf("Opcao: ");
                scanf("%d", &op);

                switch (op){
                    case 1:
                        printf("A media eh: %.2lf", media(&list));
                        printf("\n");
                        break;
                    case 2:
                        mediana(&list);
                        printf("\n");
                        break;
                    case 3:
                        moda(&list);
                        printf("\n");
                        break;
                    case 4:
                        amplitudeTotal(&list);
                        printf("\n");
                        break;
                    case 5:
                        coeficienteVariacao(&list);
                        printf("\n");
                        break;
                    case 6:
                        double var = variancia(&list);
                        printf("A Variancia eh: %.2lf\n", var);
                        printf("O Desvio Padrao eh: %.2lf\n", desvio(&list, var));
                        printf("\n");
                        break;
                    case 7:
                        imprimeElementos(&list);
                        printf("\n");
                        break;
                    case 8:
                        printf("Saindo...\n");
                        liberarLista(&list);
                        goto menu_inicial;
                        break;
                    default:
                        printf("Erro!!!\n");
                        liberarLista(&list);
                        break;
                }
            }while(op != 99);
            
            break;
        case 2:
        {
            int numClass = 0;
            printf("Digite a quantidade de classes: ");
            scanf("%d", &numClass);

            int frequenciaAbsoluta[numClass];
            int totalAmostra = 0;
            double limitSup[numClass];
            double limitInf[numClass];
            double pontoMedio[numClass];
            double frequenciaRelativa[numClass];

            for(int j = 0; j < numClass; j++){
                printf("\nDigite o limite inferior da classe %d: ", j + 1);
                scanf("%lf", &limitInf[j]);
                printf("Digite o limite superior da classe %d: ", j + 1);
                scanf("%lf", &limitSup[j]);
                printf("Digite a Frequencia Absoluta da classe %d: ", j + 1);
                scanf("%d", &frequenciaAbsoluta[j]);
                pontoMedio[j] = (limitInf[j] + limitSup[j]) / 2.0;
                totalAmostra += frequenciaAbsoluta[j];
            }

            printf("\n");

            for(int j = 0; j < numClass; j++){
                printf("\nO ponto medio da classe %d eh: %.2lf\n", j + 1, pontoMedio[j]);
                frequenciaRelativa[j] = (double)frequenciaAbsoluta[j] / totalAmostra;
                printf("A frequência relativa da classe %d eh: %.2lf\n", j + 1, frequenciaRelativa[j]);
            }

            do{
                printf("\nDigite a operacao desejada: \n");
                printf("-------------------------------------\n");
                printf("1 - Media Agrupada\n");
                printf("2 - Mediana Agrupada\n");
                printf("3 - Moda Agrupada\n");
                printf("4 - Variancia e Desvio Agrupados\n");
                printf("5 - Sair para o menu\n");
                printf("-------------------------------------\n");
                printf("Opcao: ");
                scanf("%d", &op);

                switch (op){
                    case 1:
                        printf("O valor da media agrupada eh: %.2lf", mediaAgrupada(numClass, pontoMedio, frequenciaRelativa));
                        printf("\n");
                        break;
                    case 2:
                        medianaAgrupada(numClass, totalAmostra, frequenciaAbsoluta, limitInf, limitSup);
                        printf("\n");
                        break;
                    case 3:
                        modaAgrupada(numClass,frequenciaAbsoluta, limitInf, limitSup);
                        printf("\n");
                        break;
                    case 4:
                        varianciaDesvioAgrupados(numClass, pontoMedio, frequenciaRelativa, frequenciaAbsoluta, totalAmostra);
                        printf("\n");
                        break;
                   case 5:
                        printf("Saindo...\n");
                        goto menu_inicial;
                        break;
                    default:
                        printf("Erro!!!\n");
                        break;
                }
            }while(op != 99);
            break;
        }

        case 3:
            covariancia();
            printf("\n");
            break;
        case 4:
            correlacao();
            printf("\n");
            break;
        case 5:
            printf("Fechando...\n");
            break;
        default:
            printf("Erro!!! Opcao invalida\n");
            break;
    }

    return 0;
}