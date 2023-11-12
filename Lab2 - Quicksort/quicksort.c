#include <stdio.h>
#include <time.h>
#include <stdlib.h>
long int contador_swaps;
long int contador_recursao;

void troca(int *num1, int *num2){
    int aux = *num1;
    *num1 = *num2;
    *num2 = aux;
}

int mediana(int a, int b, int c, int vet[]){
    if( (a <= b && a >= c) || (a >= b && a <= c)) 
        return a;

    else if((b <= a && b >= c) || (b >= a && b <= c)){
        troca(&vet[a], &vet[b]);
        contador_swaps++;
        return b;
    }

    else{
        troca(&vet[a], &vet[c]);
        contador_swaps++;
        return c;
    }
}

int particao_hoare(int vet[], int i, int f, int metodo){

    int k = i-1;
    int j = f + 1;
    int particionador;
    srand(time(NULL));

    //definindo particionador (mediana)
    
    if(metodo == 1){
        particionador = mediana(vet[i], vet[(i+f)/2], vet[f], vet);
    }

    //definindo particionador (aleatório)
    else{
        int valor = vet[(rand() % (f - i + 1)) + i];
        particionador = vet[valor];
        troca(&vet[i], &vet[valor]);
        contador_swaps++;
    }
    
     while (1) {
        do{
            k++;
        } while (vet[k] < particionador);
        do {
            j--;
        } while (vet[j] > particionador);
        if (k >= j)
            return j;
        troca(&vet[k], &vet[j]);
        contador_swaps++;
    }
}

int particao_lomuto(int vet[], int i, int f, int metodo){

    int particionador;
    srand(time(NULL));

    //definindo particionador (mediana)
    if(metodo == 1){
    particionador = mediana(vet[i], vet[(i+f)/2], vet[f], vet);
    }

    //definindo particionador (aleatório)
    else{
        int valor = (rand() % (f - i + 1)) + i;
        particionador = vet[valor];
        troca(&vet[i], &vet[valor]);
        contador_swaps++;
    }
    int k = i;
    for (int j = k+1; j <= f; j++) {
        if (vet[j] <= particionador) {
            k++;
            troca(&vet[k], &vet[j]);
            contador_swaps++;
    }
  }
    troca(&vet[k], &vet[i]);
    contador_swaps++;
    return (k);
}

void quicksort(int vet[], int i, int f, int metodo_particionador, int metodo_particao){
    int part;
    if(metodo_particao == 1){
        if(i < f){
            part = particao_hoare(vet, i, f, metodo_particionador);
            contador_recursao++;
            quicksort(vet, i, part, metodo_particionador, metodo_particao);
            contador_recursao++;
            quicksort(vet, part+1, f, metodo_particionador, metodo_particao);
        }
    }
    else{
        if(i < f){
            part = particao_lomuto(vet, i, f, metodo_particionador);
            contador_recursao++;
            quicksort(vet, i, part-1, metodo_particionador, metodo_particao);
            contador_recursao++;
            quicksort(vet, part+1, f, metodo_particionador, metodo_particao);
        }
    }
}

int main(){
    FILE *arq_ent;
    FILE *arq_hoare1;
    FILE *arq_hoare2;
    FILE *arq_lomuto1;
    FILE *arq_lomuto2;
    int tam_vetor, i;
    static int vet[1000000];
    static int vet2[1000000];
    static int vet3[1000000];
    static int vet4[1000000];
    double total_t;
    clock_t inicio_t, final_t;

    arq_ent = fopen("entrada-quicksort.txt", "r");
    arq_hoare1 = fopen("stats-mediana-hoare.txt", "w");
    arq_lomuto1 = fopen("stats-mediana-lomuto.txt", "w");
    arq_hoare2 = fopen("stats-aleatorio-hoare.txt", "w");
    arq_lomuto2 = fopen("stats-aleatorio-lomuto.txt", "w");

    if(arq_ent == NULL || arq_hoare1 == NULL || arq_hoare2 == NULL 
    || arq_lomuto1 == NULL || arq_lomuto2 == NULL){
        printf("Não foi possível abrir o arquivo!");
        return 0;
    }

    fscanf(arq_ent, "%d", &tam_vetor);
    do{
        i = 0;    
        while (i < tam_vetor){
            fscanf(arq_ent, "%d", &vet[i]);
            i++;
        }

        for(i = 0; i < tam_vetor; i++){
            vet2[i] = vet[i];
            vet3[i] = vet[i];
            vet4[i] = vet[i];
        }

        contador_swaps = 0;
        contador_recursao = 0;

        fprintf(arq_hoare1, "TAMANHO ENTRADA %d\n", tam_vetor);
        inicio_t = clock();
        quicksort(vet, 0, tam_vetor-1, 1, 1);  //quicksort hoare mediana
        final_t = clock();
        total_t = (double) (final_t - inicio_t) / CLOCKS_PER_SEC;
        fprintf(arq_hoare1, "SWAPS %ld\n", contador_swaps);
        fprintf(arq_hoare1, "RECURSOES %ld\n", contador_recursao);
        fprintf(arq_hoare1, "TEMPO %.3lf\n", total_t);

        contador_swaps = 0;
        contador_recursao = 0;

        fprintf(arq_lomuto1, "TAMANHO ENTRADA %d\n", tam_vetor);
        inicio_t = clock();
        quicksort(vet2, 0, tam_vetor-1, 1, 0);  //quicksort lomuto mediana
        final_t = clock();
        total_t = (double) (final_t - inicio_t) / CLOCKS_PER_SEC;
        fprintf(arq_lomuto1, "SWAPS %ld\n", contador_swaps);
        fprintf(arq_lomuto1, "RECURSOES %ld\n", contador_recursao);
        fprintf(arq_lomuto1, "TEMPO %.3lf\n", total_t);

        contador_swaps = 0;
        contador_recursao = 0;

        fprintf(arq_hoare2, "TAMANHO ENTRADA %d\n", tam_vetor);
        inicio_t = clock();
        quicksort(vet3, 0, tam_vetor-1, 0, 1);  //quicksort hoare aleatório
        final_t = clock();
        total_t = (double) (final_t - inicio_t) / CLOCKS_PER_SEC;
        fprintf(arq_hoare2, "SWAPS %ld\n", contador_swaps);
        fprintf(arq_hoare2, "RECURSOES %ld\n", contador_recursao);
        fprintf(arq_hoare2, "TEMPO %.3lf\n", total_t);

        contador_swaps = 0;
        contador_recursao = 0;

        fprintf(arq_lomuto2, "TAMANHO ENTRADA %d\n", tam_vetor);
        inicio_t = clock();
        quicksort(vet4, 0, tam_vetor-1, 0, 0);  //quicksort lomuto aleatório
        final_t = clock();
        total_t = (double) (final_t - inicio_t) / CLOCKS_PER_SEC;
        fprintf(arq_lomuto2, "SWAPS %ld\n", contador_swaps);
        fprintf(arq_lomuto2, "RECURSOES %ld\n", contador_recursao);
        fprintf(arq_lomuto2, "TEMPO %.3lf\n", total_t);
        
    }while(fscanf(arq_ent, "%d", &tam_vetor) != EOF);

    fclose(arq_ent);
    fclose(arq_hoare1);
    fclose(arq_hoare2);
    fclose(arq_lomuto1);
    fclose(arq_lomuto2);
    return 0;
}