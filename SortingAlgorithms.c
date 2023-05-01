/*1- Implementar os algoritmos de ordenação Insertion Sort, Selection Sort, Quick Sort e Merge Sort.
2- O programa deve solicitar o tamanho do vetor de números (n) que será ordenado
3- O programa deve preencher um vetor de tamanho n com números aleatórios. Usar srand(time(NULL)); no inicio do programa.
4- Faça um código que verifica se o resultado dado por cada algoritmo de ordenação está correto.
5- Use a melhor lib (defina a melhor no item 7) para calcular quanto tempo cada algoritmo de ordenação levou para terminar: https://levelup.gitconnected.com/8-ways-to-measure-execution-time-in-c-c-48634458d0f9
6- No 1:1 vou perguntar sobre questões de desempenho relacionadas a esse exercício, então pense sobre desempenho, otimizações, avaliação de tempo, complexidade, hardware, etc
7- Faça teste de leaks de memória.*/

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void insertionSort(int *array, int n);
void quickSort(int *data, int start, int end);
void selectionSort(int *array, int n);
int *mergeSort(int *array, int n);
int *merge(int *leftArr, int *rightArr, int n, int leftSize, int rightSize);
bool isSorted(int *array, int numsSize);

int main () {

    
    int min = 0;
	int max = 500000;
    int n;
	int esc;

    printf("Elementos: ");
    scanf("%d", &n);
	int *array = malloc(sizeof(int) * n);

	srand(time(NULL));
	for (int k = 0; k < n; k++){
		int number = (rand() % (max - min + 1)) + min;
		array[k] = number;
	}

    struct timeval begin, end;
    printf("1- Insertion Sort\n");
    printf("2- Selection Sort\n");
    printf("3- Quick Sort\n");
    printf("4- Merge Sort\n");

    printf("Escolha: ");
    scanf("%d", &esc);


    switch (esc)
    {
    case 1:
        gettimeofday(&begin, 0);
        insertionSort(array, n);
        break;
    case 2:
        gettimeofday(&begin, 0);
        selectionSort(array, n);
        break;
    case 3:
        gettimeofday(&begin, 0);
        quickSort(array, 0, n-1);
        break;
    case 4:
        gettimeofday(&begin, 0);
        array = mergeSort(array, n);
        break;
    default:
        break;
    }



    
    // Stop measuring time and calculate the elapsed time
    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;
    
    printf("Time measured: %.3f seconds.\n", elapsed);
    
    printf("\n%d\n", isSorted(array, n));

    return 0;
}

void insertionSort(int *array, int n){
    	int swap;

	for (int i = 1; i < n; i++){
		int tmp = array[i];
		for (int j = i-1; j >= 0; j--){
			if (tmp < array[j]){
                swap = array[j];
                array[j] = tmp;
                array[j+1] = swap;
            }
            else{
                break;
            }
		}
	}

}

void selectionSort(int *array, int n){

    int lowest;
    int swap;
    int lowestidx;

    for (int i = 0; i < n; i++){
        for (int j = i; j < n; j++){
            if (j == i){
                lowest = array[j];
                lowestidx = j;
            }
            if (array[j] < lowest){
                lowest = array[j];
                lowestidx = j;
            }
        }
        swap = array[i];
        array[i] = lowest;
        array[lowestidx] = swap;
    }

}

void quickSort(int *data, int start, int end){

    if (end <= start){
        return;
    }

    int i = start - 1;
    int j = start;
    int pivot = data[end];
    int tmp;

    while (j != end)
        if (data[j] < pivot){
            i++;
            tmp = data[i];
            data[i] = data[j];
            data[j] = tmp;
            j++;
        }
        else{
            j++;
        }
    i++;
    tmp = data[i];
    data[i] = data[j];
    data[j] = tmp;

    quickSort(data, start, i-1);
    quickSort(data, i+1, end);

}

int *mergeSort(int *array, int n){

    if (n <= 1){
        return array;
    }

    int mid = n / 2;
    int *left = malloc(sizeof(int) * mid);
    int *right = malloc(sizeof(int) * (n - mid));
    int *resultado;
    int idx = 0;

    for (int i = 0; i < mid; i++){
        left[i] = array[i];
    }
    for (int j = mid; j < n; j++){
        right[idx] = array[j];
        idx++;
    }

    left = mergeSort(left, mid);
    right = mergeSort(right, n - mid);
    resultado = merge(left, right, n, mid, n - mid);

    return resultado;

}

int *merge(int *leftArr, int *rightArr, int n, int leftSize, int rightSize){

    int *output = malloc(sizeof(int) * n);
    int i = 0, l = 0, r = 0;

    while (l < leftSize && r < rightSize){
        if (leftArr[l] < rightArr[r]){
            output[i] = leftArr[l];
            i++;
            l++;
        }
        else{
            output[i] = rightArr[r];
            i++;
            r++;
        }
    }
    while (l < leftSize){
        output[i] = leftArr[l];
        i++;
        l++;
    }
    while (r < rightSize){
        output[i] = rightArr[r];
        i++;
        r++;
    }

    return output;
}

bool isSorted(int *array, int numsSize){

    for (int i = 0; i < numsSize-1; i++){
        if (array[i] > array[i+1]){
            return false;
        }
    }
    return true;
}