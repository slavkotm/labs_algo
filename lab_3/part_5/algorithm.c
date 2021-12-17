#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int SIZE = 15;

// создание структуры подсписка
typedef struct secondary_item {
    int id_job;
    int mark_interesting;
    int mark_effeciency; 
    struct secondary_item *secondary_next;
} secondary_list;

// создание структуры списка
typedef struct primary_item {
    int id_worker;
    struct secondary_item *secondary_next;
    struct primary_item* primary_next;
} primary_list;

// функция создания списка
primary_list *create_list(int data_id_worker) {
    primary_list *first = malloc(sizeof(primary_list));
    first->id_worker = data_id_worker;
    first->secondary_next = NULL;
    first->primary_next = NULL;
    return first;
}

// функция добавления элемента в список
primary_list *add_element_to_general_list(primary_list* list, int data_id_worker) {
    primary_list *last = list;
    while (last->primary_next != NULL)
        last = last->primary_next;
    primary_list *tmp_node = malloc(sizeof(primary_list));
    tmp_node->id_worker = data_id_worker;
    tmp_node->secondary_next = NULL;
    tmp_node->primary_next = NULL;
    last->primary_next = tmp_node;
    return list;
}

// функция подсчета элементов в списке
int count_element_general_list(primary_list *list) {
    int count = 0;
    while (list->primary_next != NULL) {
        count++;
        list = list->primary_next;
    }
    count++;
    return count;
}

primary_list *distribution_tasks(primary_list *list) {
    int arr[4][2] = { {0, 0}, {0, 0}, {0, 0}, {0, 0}};

    arr[0][0] = 0; 
    arr[0][1] = 1;
    arr[1][0] = 2;
    arr[1][1] = 3;
    arr[2][0] = 1;
    arr[2][1] = 2;
    arr[3][0] = 3;
    arr[3][1] = 4;
    for (int i = 0; i < 4; i++) {
        printf("id_job:%d <---> id_worker:%d\n", arr[i][0], arr[i][1]);
    }

    return list;
}

// функция добавления элемента в подсписок списка
primary_list *add_element_index_to_under_list(primary_list* general_list, int index, int data_id_job, int data_mark_interesting, int data_mark_effeciency) {
    if (index <= count_element_general_list(general_list)) {
        int count = 0;
        while (count < index) {
            count++;
            general_list = general_list->primary_next;
        }
        if (general_list->secondary_next == NULL) {
            general_list->secondary_next = malloc(sizeof(secondary_list));
            general_list->secondary_next->mark_interesting = data_mark_interesting;
            general_list->secondary_next->mark_effeciency = data_mark_effeciency;
            general_list->secondary_next->id_job = data_id_job;
            general_list->secondary_next->secondary_next = NULL;
            return general_list;
        }
        else if (general_list->secondary_next != NULL) {
            secondary_list *last = general_list->secondary_next;
            while (last->secondary_next != NULL)
                last = last->secondary_next;
            secondary_list *tmp_node = malloc(sizeof(secondary_list));
            tmp_node->mark_interesting = data_mark_interesting;
            tmp_node->mark_effeciency = data_mark_effeciency;
            tmp_node->id_job = data_id_job;
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

// функция печати списка списков
void print_together_lists(primary_list *list) {
    if (list == NULL)
        return;
    while (list->primary_next != NULL) {
        printf("\nid_worker:%d\n", list->id_worker);
        if (list->secondary_next != NULL) { 
            while (list->secondary_next->secondary_next != NULL) {
                printf("{id_job:%d, mark_interesting:%d, mark_effeciency:%d}\n", list->secondary_next->id_job, list->secondary_next->mark_interesting, list->secondary_next->mark_effeciency);
                list->secondary_next = list->secondary_next->secondary_next;
            }
            printf("{id_job:%d, mark_interesting:%d, mark_effeciency:%d}\n", list->secondary_next->id_job, list->secondary_next->mark_interesting, list->secondary_next->mark_effeciency);
        }
        list = list->primary_next;
    }
    printf("\nid_worker:%d\n", list->id_worker);
    if (list->secondary_next != NULL) {
        while (list->secondary_next->secondary_next != NULL) {
            printf("{id_job:%d, mark_interesting:%d, mark_effeciency:%d}\n", list->secondary_next->id_job, list->secondary_next->mark_interesting, list->secondary_next->mark_effeciency);
            list->secondary_next = list->secondary_next->secondary_next;
        }
        printf("{id_job:%d, mark_interesting:%d, mark_effeciency:%d}\n", list->secondary_next->id_job, list->secondary_next->mark_interesting, list->secondary_next->mark_effeciency);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    primary_list* list = create_list(0);
        add_element_index_to_under_list(list, 0, 0, 5, 50);
        add_element_index_to_under_list(list, 0, 1, 6, 10);
        add_element_index_to_under_list(list, 0, 2, 8, 80);
        add_element_index_to_under_list(list, 0, 3, 3, 40);

    add_element_to_general_list(list, 1);
        add_element_index_to_under_list(list, 1, 0, 4, 70);
        add_element_index_to_under_list(list, 1, 1, 9, 30);
        add_element_index_to_under_list(list, 1, 2, 7, 86);
        add_element_index_to_under_list(list, 1, 3, 2, 14);

    add_element_to_general_list(list, 2);
        add_element_index_to_under_list(list, 2, 0, 0, 71);
        add_element_index_to_under_list(list, 2, 1, 1, 55);
        add_element_index_to_under_list(list, 2, 2, 7, 86);
        add_element_index_to_under_list(list, 2, 3, 2, 12);

    add_element_to_general_list(list, 3);
        add_element_index_to_under_list(list, 3, 0, 4, 38);
        add_element_index_to_under_list(list, 3, 1, 0, 49);
        add_element_index_to_under_list(list, 3, 2, 7, 82);
        add_element_index_to_under_list(list, 3, 3, 4, 23);

    
        print_together_lists(list); 
        distribution_tasks(list);
    return 0;
}














