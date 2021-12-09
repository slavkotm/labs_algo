#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int SIZE = 15;

typedef struct secondary_item {
    int data;
    struct secondary_item *secondary_next;
} secondary_list;

typedef struct primary_item {
    int under_data;
    struct secondary_item *secondary_next;
    struct primary_item* primary_next;
} primary_list;

primary_list *create_list(int data_of_array) {
    primary_list *first = malloc(sizeof(primary_list));
    first->under_data = data_of_array;
    first->secondary_next = NULL;
    first->primary_next = NULL;
    return first;
}

primary_list *add_element_to_general_list(primary_list* list, int data_of_array) {
    primary_list *last = list;
    while (last->primary_next != NULL)
        last = last->primary_next;
    primary_list *tmp_node = malloc(sizeof(primary_list));
    tmp_node->under_data = data_of_array;
    tmp_node->secondary_next = NULL;
    tmp_node->primary_next = NULL;
    last->primary_next = tmp_node;
    return list;
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

int count_element_general_list(primary_list *list) {
    int count = 0;
    while (list->primary_next != NULL) {
        count++;
        list = list->primary_next;
    }
    count++;
    return count;
}

primary_list *add_element_index_to_under_list(primary_list* general_list, int index, int data_of_array) {
    if (index <= count_element_general_list(general_list)) {
        int count = 0;
        while (count < index) {
            count++;
            general_list = general_list->primary_next;
        }
        if (general_list->secondary_next == NULL) {
            general_list->secondary_next = malloc(sizeof(secondary_list));
            general_list->secondary_next->data = data_of_array;
            general_list->secondary_next->secondary_next = NULL;
            return general_list;
        }
        else if (general_list->secondary_next != NULL) {
            secondary_list *last = general_list->secondary_next;
            while (last->secondary_next != NULL)
                last = last->secondary_next;
            secondary_list *tmp_node = malloc(sizeof(secondary_list));
            tmp_node->data = data_of_array;
            tmp_node->secondary_next = NULL;
            last->secondary_next = tmp_node;
        }
    }
    else { 
        printf("обращение к не существующему элементу\n");
        return NULL;
    }
    return general_list;
}

void print_general_list(primary_list* list) {
    if (list == NULL)
        return;
    while (list->primary_next != NULL) {
        printf("%d\n", list->under_data);
        list = list->primary_next;
    }
    printf("%d\n", list->under_data);
}

void print_under_list(primary_list* list, int index) {
    if (list == NULL)
        return;
    int count = 0;
    while (count < index) {
        count++;
        list = list->primary_next;
    }
    while (list->secondary_next->secondary_next != NULL) {
        printf("%d\n", list->secondary_next->data);
        list->secondary_next = list->secondary_next->secondary_next;
    }
}

void print_together_lists(primary_list *list) {
    if (list == NULL)
        return;
    while (list->primary_next != NULL) {
        printf("%d { ", list->under_data);
        if (list->secondary_next != NULL) { 
            while (list->secondary_next->secondary_next != NULL) {
                printf("%d ", list->secondary_next->data);
                list->secondary_next = list->secondary_next->secondary_next;
            }
            printf("%d }", list->secondary_next->data);
        }
        list = list->primary_next;
        printf("\n");
    }
    printf("%d { ", list->under_data);
    if (list->secondary_next != NULL) {
        while (list->secondary_next->secondary_next != NULL) {
            printf("%d ", list->secondary_next->data);
            list->secondary_next = list->secondary_next->secondary_next;
        }
        printf("%d }", list->secondary_next->data);
    }
    printf("\n");
}

int hash_function(int key) {
    int N = 10;
    double A = 0.6180339887;
    return N * fmod(key * A, 1);
}

primary_list *hash_chain(primary_list *list, int *arr, int *unique_arr, int size, int unique_arr_size) {
    if (list == NULL)
        list = create_list(unique_arr[0]);

    for (int i = 1; i < unique_arr_size; i++) {
        add_element_to_general_list(list, unique_arr[i]);
    }
    primary_list *tmp_list = list;
    for (int i = 0; i < count_element_general_list(list); i++) {
        for (int j = 0; j < size; j++) {
            if (tmp_list->under_data == hash_function(arr[j])) {
                add_element_index_to_under_list(list, i, arr[j]);
            }
        }
        tmp_list = tmp_list->primary_next;
    }
    return list;
}

int *unique_hashes(int* arr, int size, int *size_last_arr) {
    int size_new_arr = 0, k = 0, f = 0;
    int *tmp_arr = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
        tmp_arr[i] = hash_function(arr[i]);
    
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (tmp_arr[i] == tmp_arr[j] && i != j) {
                size_new_arr++;
                break;
            }
        }
    }
    
    int *last_arr = malloc((size - size_new_arr) * sizeof(int));

    int *arr_of_index = malloc(size_new_arr * sizeof(int));
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (tmp_arr[i] == tmp_arr[j] && i != j) {
                arr_of_index[k] = j;
                k++;
                break;
            }
        }
    }

    insert_sort(arr_of_index, 0, size_new_arr);

    k = 0;

    for (int i = 0; i < size; i++) {
        if (arr_of_index[k] == i) {
            k++;
            continue;
        }
        else {
            last_arr[f] = tmp_arr[i];
            f++;
        }
    }
    
    *(size_last_arr) = size - size_new_arr;

    free(arr_of_index);
    free(tmp_arr);

    return last_arr;
}

int extra_hash_function(int key) {
    return (key % SIZE);
}

int main(int argc, char* argv[]) {
    primary_list *list = NULL;
    int *arr = malloc(SIZE * sizeof(int));
    int *hash_arr = NULL;
    int size_hash_arr = 0;
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % SIZE + SIZE / pow(SIZE, 2);
    }
    hash_arr = unique_hashes(arr, SIZE, &size_hash_arr);
    list = hash_chain(list, arr, hash_arr, SIZE, size_hash_arr);
    print_together_lists(list);
    free(hash_arr);
    free(arr);
    return 0;
}
