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
int search_binary(int* arr, int low, int high, int need_element, int* count_compare_in_binary_search) {
    if(need_element < arr[low] || need_element > arr[high]) {
        (*count_compare_in_binary_search)++;
        return -1;
    }

    int mid = (high + low) / 2;
    int quit = 1; 
    int need_position = -1;

    if(need_element == arr[mid] && quit) {
        need_position = mid;
        quit = 0;
        (*count_compare_in_binary_search)++;
    }

    if(need_element == arr[low] && quit) {
        need_position = low;
        quit = 0;
        (*count_compare_in_binary_search)++;
    }

    if(need_element == arr[high] && quit) {
        need_position = high;
        quit = 0;
        (*count_compare_in_binary_search)++;
    }

    if(need_element < arr[mid] && quit) {
        (*count_compare_in_binary_search)++;
        return search_binary(arr, low, mid + 1, need_element, count_compare_in_binary_search);
    }

    if(need_element > arr[mid] && quit) {
        (*count_compare_in_binary_search)++;
        return search_binary(arr, mid + 1, high, need_element, count_compare_in_binary_search);
    }

    return need_position;
}

//функция для поиска элемента в массиве(интерполяционный поиск)
int search_interpolar(int* arr, int low, int high, int need_element, int* count_compare_in_interpolar_search) {
    int position;

    if(low <= high && need_element >= arr[low] && need_element <= arr[high]) {
        (*count_compare_in_interpolar_search)++;
        position = low + (((double)(high - low) /  (arr[high] - arr[low])) * (need_element - arr[low]));

        if(arr[position] == need_element) {
            (*count_compare_in_interpolar_search)++;
            return position;
        }

        if(arr[position] < need_element) {
            (*count_compare_in_interpolar_search)++;
            return search_interpolar(arr, position + 1, high, need_element, count_compare_in_interpolar_search);
        }

        if(arr[position] < need_element) {
            (*count_compare_in_interpolar_search)++;
            return search_interpolar(arr, low, position - 1, need_element, count_compare_in_interpolar_search);
        }
    }

    return -1;
}

//главный метод
int main(int argc, char* argv[])
{
    //создание массива на SIZE элементов 
    int* arr = malloc(SIZE * sizeof(int));
    int count_compare_in_binary_search = 0;
    int count_compare_in_interpolar_search = 0;
    FILE *f = NULL;
    int ar[] = {-12,-15,-3,-1,10,3,4,16,19,13};
    read_number_from_file_and_write_to_array(f, arr, SIZE);
    printf("%d\n", search_binary(ar, 0, 10 - 1, 10, &count_compare_in_binary_search));
    printf("%d\n", search_interpolar(ar, 0, 10 - 1, 10, &count_compare_in_interpolar_search));
    printf("количество сравнений в бинарном поиске: %d, количество сравнений в интерполяционном поиске: %d\n", count_compare_in_binary_search, count_compare_in_interpolar_search);
    //удалние массива из памяти
    delete_array(arr);
    return 0;
}
