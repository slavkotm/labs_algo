#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int SIZE = 100;

typedef struct knot {
    int data;
    struct knot *next;
} node;

typedef struct under_knot {
    int under_data;
    struct knot *next;
    struct under_knot* under;
} under_node;

under_node *create_list(int data_of_array) {
    under_node *first = malloc(sizeof(under_node));
    first->under_data = data_of_array;
    first->next = NULL;
    first->under = NULL;
    return first;
}

under_node *add_element_to_general_list(under_node* list, int data_of_array) {
    under_node *last = list;
    while (last->under != NULL)
        last = last->under;
    under_node *tmp_node = malloc(sizeof(under_node));
    tmp_node->under_data = data_of_array;
    tmp_node->next = NULL;
    tmp_node->under = NULL;
    last->under = tmp_node;
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

int count_element_general_list(under_node *list) {
    int count = 0;
    while (list->under != NULL) {
        count++;
        list = list->under;
    }
    count++;
    return count;
}

under_node *add_element_index_to_under_list(under_node* general_list, int index, int data_of_array) {
    if (index <= count_element_general_list(general_list)) {
        int count = 0;
        while (count < index) {
            count++;
            general_list = general_list->under;
        }
        if (general_list->next == NULL) {
            general_list->next = malloc(sizeof(node));
            general_list->next->data = data_of_array;
            general_list->next->next = NULL;
            return general_list;
        }
        else if (general_list->next != NULL) {
            node *last = general_list->next;
            while (last->next != NULL)
                last = last->next;
            node *tmp_node = malloc(sizeof(node));
            tmp_node->data = data_of_array;
            tmp_node->next = NULL;
            last->next = tmp_node;
        }
    }
    else { 
        printf("обращение к не существующему элементу\n");
        return NULL;
    }
    return general_list;
}

void print_general_list(under_node* list) {
    if (list == NULL)
        return;
    while (list->under != NULL) {
        printf("%d\n", list->under_data);
        list = list->under;
    }
    printf("%d\n", list->under_data);
}

void print_under_list(under_node* list, int index) {
    if (list == NULL)
        return;
    int count = 0;
    while (count < index) {
        count++;
        list = list->under;
    }
    while (list->next->next != NULL) {
        printf("%d\n", list->next->data);
        list->next = list->next->next;
    }
}

void print_together_lists(under_node *list) {
    if (list == NULL)
        return;
    while (list->under != NULL) {
        printf("%d { ", list->under_data);
        if (list->next != NULL) { 
            while (list->next->next != NULL) {
                printf("%d ", list->next->data);
                list->next = list->next->next;
            }
            printf("%d }", list->next->data);
        }
        list = list->under;
        printf("\n");
    }
    printf("%d { ", list->under_data);
    if (list->next != NULL) {
        while (list->next->next != NULL) {
            printf("%d ", list->next->data);
            list->next = list->next->next;
        }
        printf("%d }", list->next->data);
    }
    printf("\n");
}

int hash_function(int key) {
    int N = 10;
    double A = 0.6180339887;
    return N * fmod(key * A, 1);
}

under_node *hash_chain(under_node *list, int *arr, int *unique_arr, int size, int unique_arr_size) {
    if (list == NULL)
        list = create_list(unique_arr[0]);

    for (int i = 1; i < unique_arr_size; i++) {
        add_element_to_general_list(list, unique_arr[i]);
    }
    print_general_list(list);
    under_node *tmp_list = list;
    for (int i = 0; i < count_element_general_list(list); i++) {
        for (int j = 0; j < size; j++) {
            if (tmp_list->under_data == hash_function(arr[j])) {
                add_element_index_to_under_list(list, i, arr[j]);
            }
        }
        tmp_list = tmp_list->under;
    }
    return list;
}

int main(int argc, char* argv[]) {
    under_node *list = NULL;
    int *arr = malloc(SIZE * sizeof(int));
    int *any_arr = malloc(SIZE * sizeof(int));
    int new_size = 0, k = 0, f = 0;// check_for_unique = 0, j = 0;
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % SIZE + SIZE / pow(SIZE, 2);
    }
    for (int i = 0; i < SIZE; i++) {
        printf("%d %d\n", hash_function(arr[i]), arr[i]);
    }
    for (int i = 0; i < SIZE; i++) {
        any_arr[i] = arr[i];
    }
    for (int i = 0; i < SIZE; i++) {
        arr[i] = hash_function(arr[i]);
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = i; j < SIZE; j++) {
            if (arr[i] == arr[j] && i != j) {
                new_size++;
                break;
            }
        }
    }
    int *ar = malloc(new_size * sizeof(int));
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = i; j < SIZE; j++) {
            if (arr[i] == arr[j] && i != j) {
                ar[k] = j;
                k++;
                break;
            }
        }
    }
    int *a = malloc((SIZE - new_size) * sizeof(int));
    insert_sort(ar, 0, new_size);
    k = 0;
    for (int i = 0; i < SIZE; i++) {
        if (ar[k] == i) {
            k++;
            continue;
        }
        else {
            a[f] = arr[i];
            f++;
        }
    }

    for (int i = 0; i < SIZE - new_size; i++) {
        printf("%d\n", a[i]);
    }
    printf("\n");
    list = hash_chain(list, any_arr, a, SIZE, SIZE - new_size);
    //printf("%d\n", new_size);
    print_together_lists(list);
    free(arr);
    return 0;
}
