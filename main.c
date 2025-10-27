#include <stdio.h>
#include "estatistica.h"
#include "lista.h"

int main(){
    double num = -1;
    int i = 1;
    int op = 0;
    NoLista *list;
    criarLista(&list);

    printf("ROL de dados ou dados agrupados?\n");
    printf("1 - ROL de dados");
    printf("2 - Dados agrupados");
    scanf("%d", &op);

    switch (op)
    {
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
                printf("\nDigite a operação desejada: \n");
                printf("-------------------------------------\n");
                printf("1 - Média\n");
                printf("2 - Média\n");
                printf("99 - Sair\n");
                scanf("%d", &op);

                switch (op){
                    case 1:
                        media(&list);
                        printf("\n");
                        break;
                    case 2:
                        mediaAgrupada(&list);
                        printf("\n");
                        break;
                    default:
                        printf("Saindo...\n");
                        break;
                }
            }while(op != 99);
            
            break;
        case 2:
            printf("Em desenvolvimento...");
            break;
        default:
            printf("Erro!!! Opção inválida\n");
            break;
    }

    liberarLista(&list);
    return 0;
}