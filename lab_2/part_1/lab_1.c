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
    f = fopen("../out.txt", "r");
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

//функция для поиска элемента в массиве(бинарный поиск)
int search_binary(int* arr, int low, int high, int need_element) {
    int mid = (high + low) / 2;
    int quit = 1; 
    int need_position;

    if(need_element == arr[mid]) {
        need_position = mid;
        quit = 0;
    }

    if(need_element == arr[low]) {
        need_position = low;
        quit = 0;
    }

    if(need_element == arr[high]) {
        need_position = high;
        quit = 0;
    }

    if(need_element < arr[mid] && quit)
        return search_binary(arr, low, mid + 1, need_element);

    if(need_element > arr[mid] && quit)
        return search_binary(arr, mid + 1, high, need_element);

    return need_position;
}

int search_interpolar() {
    return 0;
}

//главный метод
int main(int argc, char* argv[])
{
    //создание массива на SIZE элементов 
    int* arr = malloc(SIZE * sizeof(int));
    FILE *f = NULL;
    int ar[] = {-12,-5,-3,-1,0,3,4,6,9,13};
    read_number_from_file_and_write_to_array(f, arr, SIZE);
    write_array_in_file(f, arr, SIZE);
    printf("%d\n",search_binary(ar, 0, 10 - 1, 13));
    //удалние массива из памяти
    delete_array(arr);
    return 0;
}
