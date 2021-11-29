#include <stdio.h>
#include <stdlib.h>

int SIZE = 1000000;

void delete_array(int* arr)
{
    free(arr);
}

void print_array(int* arr, int size)
{
    for(int i = 0; i < size; i++)
        printf("%d\n", arr[i]);
}

void read_number_from_file_and_write_to_array(FILE* f, int *arr, int size)
{
    f = fopen("../data.txt", "r");
    for(int i = 0; i < size; i++)
        fscanf(f, "%d", &arr[i]);
    fclose(f);
    f = NULL;
}

void write_array_in_file(FILE* f, int *arr, int size) {
    
    f = fopen("out.txt", "w");
    for(int i = 0; i < size; i++) {
        fprintf(f, "%d\n", arr[i]);
    }
    fclose(f);
    f = NULL;
}

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

void quick_sort(int *arr, int low, int high) {
    if(low < high) {
        int p = partition(arr, low, high);
        quick_sort(arr, low, p - 1);
        quick_sort(arr, p + 1, high);
    }
}

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

void merge(int* arr, int mid, int left, int right) {
    int i, j, k;
    int length_left_array = mid - left + 1;
    int length_right_array = right - mid;

    int left_array[length_left_array], right_array[length_right_array];

    for(i = 0; i < length_left_array; i++) {
        left_array[i] = arr[left + i];
    }
    for(j = 0; j < length_right_array; j++) {
        right_array[j] = arr[mid + 1 + j];
    }

    j = i = 0;
    k = left;

    while(i < length_left_array && j < length_right_array) {
        if(left_array[i] <= right_array[j]) {
            arr[k] = left_array[i];
            i++;
        }
        else {
            arr[k] = right_array[j];
            j++;
        }
        k++;
    }

    while(i < length_left_array) {
        arr[k] = left_array[i];
        i++;
        k++;
    }

    while(j < length_right_array) {
        arr[k] = right_array[j];
        j++;
        k++;
    }
}

void merge_sort(int* arr, int left, int right) {
    if(left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        merge(arr, mid, left, right);
    }
}

void mix_insert_merge_sort(int* arr, int left, int right, int k) {
    if(left < right) {
        int mid = left + (right - left) / 2;
        if(mid - left <= k) {
            insert_sort(arr, left, mid + 1);
        }
        if(mid - left > k) {
            mix_insert_merge_sort(arr, left, mid, k);
        }
        if(right - (mid + 1) <= k) {
            insert_sort(arr, mid + 1, right + 1);
        }
        if(right - (mid + 1) > k) {
            mix_insert_merge_sort(arr, mid + 1, right, k);
        }
        
        merge(arr, mid, left, right);
    }
}

void sorts(int* arr, int SIZE, int sort_type, int k) {
    if(sort_type == 1) {
        merge_sort(arr, 0, SIZE - 1);
    }

    if(sort_type == 2) {
        insert_sort(arr, 0, SIZE);
    }

    if(sort_type == 3) {
        mix_insert_merge_sort(arr, 0, SIZE - 1, k);
    }
}

int main(int argc, char* argv[])
{
    int* arr = malloc(SIZE * sizeof(int));
    FILE *f = NULL;
    read_number_from_file_and_write_to_array(f, arr, SIZE);
    sorts(arr, SIZE, 3, 1000);
    write_array_in_file(f, arr, SIZE);
    delete_array(arr);
    return 0;
}
