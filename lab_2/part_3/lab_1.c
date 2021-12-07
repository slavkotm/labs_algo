#include <stdio.h>
#include <stdlib.h>

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
        int count = 1;
        while (count <= index) {
            count++;
            general_list = general_list->under;
        }
        if (general_list->next == NULL) {
            general_list->next = malloc(sizeof(node));
            general_list->next->data = data_of_array;
            general_list->next->next = NULL;
        }
        if (general_list->next != NULL) {
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
    while (list->under != NULL) {
        printf("%d\n", list->under_data);
        list = list->under;
    }
    printf("%d\n", list->under_data);
}

void print_under_list(under_node* list, int index) {
    int count = 1;
    while (count <= index) {
        count++;
        list = list->under;
    }
    while (list->next->next != NULL) {
        printf("%d\n", list->next->data);
        list->next = list->next->next;
    }
}

void print_together_lists(under_node *list) {
    while (list->under != NULL) {
        printf("%d ", list->under_data);
        if (list->next != NULL) 
            while (list->next->next != NULL) {
                printf("%d ", list->next->data);
                list->next = list->next->next;
            }
        list = list->under;
        printf("\n");
    }
    printf("%d\n", list->under_data);
    if (list->next != NULL) 
        while (list->next->next != NULL) {
            printf("%d ", list->next->data);
            list->next = list->next->next;
        }
}

int main(int argc, char* argv[]) {
    under_node *list = create_list(4);
    add_element_to_general_list(list, 2);
    add_element_to_general_list(list, 6);
    add_element_to_general_list(list, 7);
    add_element_index_to_under_list(list, 2, 5);
    add_element_index_to_under_list(list, 2, 5);
    add_element_index_to_under_list(list, 2, 5);
    //print_general_list(list);
    //print_under_list(list, 2);
    print_together_lists(list);
    return 0;
}
