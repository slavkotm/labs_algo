#include <stdio.h>
#include <stdlib.h>

//размер массива
int SIZE = 1000000;

//функция для удаления массива
void delete_array(int* arr)
{
    free(arr);
}

//функция печати массива в консоль
void print_array(int* arr, int size)
{
    for(int i = 0; i < size; i++)
        printf("%d\n", arr[i]);
}

//функция для чтения чисел из файла в массив
void read_number_from_file_and_write_to_array(FILE* f, int *arr, int size)
{
    f = fopen("../data.txt", "r");
    for(int i = 0; i < size; i++)
        fscanf(f, "%d", &arr[i]);
    fclose(f);
    f = NULL;
}

//функция записи массива в файл
void write_array_in_file(FILE* f, int *arr, int size) {
    
    f = fopen("out.txt", "w");
    for(int i = 0; i < size; i++) {
        fprintf(f, "%d\n", arr[i]);
    }
    fclose(f);
    f = NULL;
}

//функция для упорядочивания элементов массива меньших опорного в первую часть массива
int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = low;
    for(int j = low; j < high; j++) {
        if(arr[j] <= pivot) {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
        }
    }    
    int tmp = arr[i];
    arr[i] = arr[high];
    arr[high] = tmp;
    return i;
}

//сортировка вставками
void insert_sort(int* arr, int low, int high) {
    int i, key, j;
    for(i = low + 1; i < high; i++) {
        key = arr[i];
        j = i - 1;
        while(j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

//быстрая сортировка
void quick_sort(int *arr, int low, int high) {
    if(low < high) {
        int p = partition(arr, low, high);
        quick_sort(arr, low, p - 1);
        quick_sort(arr, p + 1, high);
    }
}

//смешанная сортировка вставками с быстрой
void mix_insert_and_quick_sort(int* arr, int low, int high, int k) {
    if(low < high) {
        int p = partition(arr, low, high);
        if(p - low <= k) {
            insert_sort(arr, low, p); 
        }
        if(p - low > k) {
            mix_insert_and_quick_sort(arr, low, p - 1, k);
        }
        if(high - p <= k) {
            insert_sort(arr, p, high + 1); 
        }
        if(high - p > k) {
            mix_insert_and_quick_sort(arr, p + 1, high, k);
        }
    }
}

//функция для выбора вида сортировки
void sorts(int* arr, int SIZE, int sort_type, int k) {
    if(sort_type == 1) {
        quick_sort(arr, 0, SIZE - 1);
    }

    if(sort_type == 2) {
        insert_sort(arr, 0, SIZE);
    }

    if(sort_type == 3) {
        mix_insert_and_quick_sort(arr, 0, SIZE - 1, k);
    }
}

//главный метод
int main(int argc, char* argv[])
{
    //создание массива на SIZE элементов 
    int* arr = malloc(SIZE * sizeof(int));
    int k = 10;
    FILE *f = NULL;
    read_number_from_file_and_write_to_array(f, arr, SIZE);
    sorts(arr, SIZE, 3, k);
    write_array_in_file(f, arr, SIZE);
    //удалние массива из памяти
    delete_array(arr);
    return 0;
}
