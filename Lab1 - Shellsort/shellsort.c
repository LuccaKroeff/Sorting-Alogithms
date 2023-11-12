#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Ordenação ShellSort Knuth
void shell_sort_knuth(int *a, int size, FILE *arq)
{
    int i , j , value;
    int h = 1;
  
    for(int s = 0; s < size; s++)
        fprintf(arq, "%d ", a[s]);
    fprintf(arq, "SEQ=KNUTH\n");
    
    do {
        h = 3*h+1;
    } while(h < size);

    do {
         h = h / 3;
        for(i = h; i < size; i++) {
        value = a[i];
        j = i - h;
            while (j >= 0 && value < a[j]) {
                a[j + h] = a[j];
                j = j - h;
            }
            a[j + h] = value;
        }
        for(int k = 0; k < size; k++){
           fprintf(arq,"%d ", a[k]);
        }
        fprintf(arq,"INCR=%d\n", h);
    }while(h > 1);
}

void shell_sort_knuth_tempo(int *a, int size, FILE *arq)
{
    int i , j , value;
    int h = 1;
    do {
        h = 3*h+1;
    } while(h < size);

    do {
         h = h / 3;
        for(i = h; i < size; i++) {
        value = a[i];
        j = i - h;
            while (j >= 0 && value < a[j]) {
                a[j + h] = a[j];
                j = j - h;
            }
            a[j + h] = value;
        }
    }while(h > 1);
}


//Ordenação ShellSort
void shell_sort(int *a, int size, FILE *arq)
{
    int i , j , value;
    int h = 1;
  
  
    for(int s = 0; s < size; s++)
        fprintf(arq, "%d ", a[s]);
    fprintf(arq, "SEQ=SHELL\n");
    
    do {
        h = h * 2;
    } while(h < size);

    do {
         h = h / 2;
        for(i = h; i < size; i++) {
        value = a[i];
        j = i - h;
            while (j >= 0 && value < a[j]) {
                a[j + h] = a[j];
                j = j - h;
            }
            a[j + h] = value;
        }
        for(int k = 0; k < size; k++){
           fprintf(arq,"%d ", a[k]);
        }
        fprintf(arq,"INCR=%d\n", h);
    }while(h > 1);
}

void shell_sort_tempo(int *a, int size, FILE *arq)
{
    int i , j , value;
    int h = 1;

    do {
        h = h * 2;
    } while(h < size);

    do {
         h = h / 2;
        for(i = h; i < size; i++) {
        value = a[i];
        j = i - h;
            while (j >= 0 && value < a[j]) {
                a[j + h] = a[j];
                j = j - h;
            }
            a[j + h] = value;
        }
    }while(h > 1);
}

//Ordenação ShellSort Ciura
void shell_sort_ciura(int *a, int size, FILE *arq)
{
    int i , j , value;
    int h = 1;
    int cont = 0;
    int vet_c[8] = {1, 4, 10, 23, 57, 132, 301, 701};
    int auxiliar = 0;
  
    for(int s = 0; s < size; s++)
        fprintf(arq, "%d ", a[s]);
    fprintf(arq, "SEQ=CIURA\n");
    
    do {
        if(cont <= 7){
            h = vet_c[cont];
            cont++;
        }
        else
            h = 2.25 * h;
    } while(h < size);

    do {
        if(cont < 8){
            cont--;
            h = vet_c[cont];
        }
        else h = h / 2.25;
        
        for(i = h; i < size; i++) {
        value = a[i];
        j = i - h;
            while (j >= 0 && value < a[j]) {
                a[j + h] = a[j];
                j = j - h;
            }
            a[j + h] = value;
        }

        if(auxiliar != 0){
            for(int k = 0; k < size; k++){
              fprintf(arq,"%d ", a[k]);
            }
            fprintf(arq,"INCR=%d\n", h);
        }
        auxiliar++;
    }while(h > 1);
}

void shell_sort_ciura_tempo(int *a, int size, FILE *arq)
{
    int i , j , value;
    int h = 1;
    int cont = 0;
    int vet_c[8] = {1, 4, 10, 23, 57, 132, 301, 701};
    
    do {
        if(cont <= 7){
            h = vet_c[cont];
            cont++;
        }
        else
            h = 2.25 * h;
    } while(h < size);

    do {
        if(cont < 8){
            cont--;
            h = vet_c[cont];
        }
        else h = h / 2.25;
        
        for(i = h; i < size; i++) {
        value = a[i];
        j = i - h;
            while (j >= 0 && value < a[j]) {
                a[j + h] = a[j];
                j = j - h;
            }
            a[j + h] = value;
        }
    }while(h > 1);
}

int main(){

    FILE *arq_ent;
    FILE *arq_sai;
    FILE *arq_ent2;
    FILE *arq_sai2;
    int tam_vetor = 0;
    static int vet[1000000], vet_knuth[1000000], vet_ciura[1000000];
    int i = 0;
    clock_t start_t, end_t;  //variáveis criadas para cronometrar tempo
    double total_t;

    arq_ent = fopen("entrada1.txt", "r");
    arq_sai = fopen("saida1.txt", "w");

    arq_ent2 = fopen("entrada2.txt", "r");
    arq_sai2 = fopen("saida2.txt", "w");

    if(arq_ent == NULL || arq_sai == NULL){
        printf("Problemas ao abrir o arquivo.\n");
    }

    if(arq_ent2 == NULL || arq_sai2 == NULL){
        printf("Problemas ao abrir o arquivo.\n");
    }

    //1a Parte do laboratório

    fscanf(arq_ent, "%d", &tam_vetor);

    do{
        i = 0;    
       //printf("\nTamanho do vetor: %d\n", tam_vetor);
        while (i < tam_vetor){
            fscanf(arq_ent, "%d", &vet[i]);
            i++;
        }

        for(int k = 0; k <= tam_vetor; k++){
            vet_ciura[k] = vet[k];
            vet_knuth[k] = vet[k];
        }

        shell_sort(vet, i, arq_sai);
        shell_sort_knuth(vet_knuth, i, arq_sai);
        shell_sort_ciura(vet_ciura, i, arq_sai);

    }while(fscanf(arq_ent, "%d", &tam_vetor) != EOF);

//=============================================================================

    //2a Parte do laboratório

    fscanf(arq_ent2, "%d", &tam_vetor);

    do{
        i = 0;    
        while (i < tam_vetor){
            fscanf(arq_ent2, "%d", &vet[i]);
            i++;
        }

        for(int k = 0; k <= tam_vetor; k++){
            vet_ciura[k] = vet[k];
            vet_knuth[k] = vet[k];
        }

        start_t = clock();
        shell_sort_tempo(vet, i, arq_sai);
        end_t = clock();
        total_t = (double) (end_t - start_t) / CLOCKS_PER_SEC;
        fprintf(arq_sai2, "SHELL, %d, %.3lf\n", tam_vetor, total_t);

        start_t = clock();
        shell_sort_knuth_tempo(vet_knuth, i, arq_sai);
        end_t = clock();
        total_t = (double) (end_t - start_t) / CLOCKS_PER_SEC;
        fprintf(arq_sai2, "KNUTH, %d, %.3lf\n", tam_vetor, total_t);

        start_t = clock();
        shell_sort_ciura_tempo(vet_ciura, i, arq_sai);
        end_t = clock();
        total_t = (double) (end_t - start_t) / CLOCKS_PER_SEC;
        fprintf(arq_sai2, "CIURA, %d, %.3lf\n", tam_vetor, total_t);

    }while(fscanf(arq_ent2, "%d", &tam_vetor) != EOF);

    fclose(arq_ent);
    fclose(arq_ent2);
    fclose(arq_sai);
    fclose(arq_sai2);
    
    return 0;
}