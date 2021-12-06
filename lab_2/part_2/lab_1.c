#include <stdio.h>
#include <stdlib.h>

//размер массива
int SIZE = 40;

//объявление структуры, для создания бинарного дерева
typedef struct tree {
    int key;
    int data;
    int size_tree;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
} node;

//функция которая создает корень дерева, и в корень записывается значение
node *create_tree(int key, int data, int size_tree) {
    node *tmp = malloc(sizeof(node));
    tmp->size_tree = size_tree;
    tmp->data = data;
    tmp->key = key;
    tmp->parent = tmp->right = tmp->left = NULL;
    return tmp;
}

//поиск определенного узла дерева по ключу
node *search_knot(node *root, int data) {
    if ((root == NULL) || (root->data = data))
        return root;
    if (data < root->data)
        return search_knot(root->left, data);
    else
        return search_knot(root->right, data);
}

//функция добавления узлов в дерево
node *add_leaf(node *root, int key, int data) {
    node *walk_root = root;
    node *walk_parent_root = NULL;
    node *tmp = malloc(sizeof(node));

    tmp->data = data;

    while (walk_root != NULL) {
        walk_parent_root = walk_root;
        if (data < walk_root->data) 
            walk_root = walk_root->left;
        else
            walk_root = walk_root->right;
        key++;
    }

    tmp->key = key;
    root->size_tree = -1;
    tmp->size_tree = -1;
    tmp->parent = walk_parent_root;
    tmp->right = tmp->left = NULL;

    if (data < walk_parent_root->data) 
        walk_parent_root->left = tmp;
    else
        walk_parent_root->right = tmp;

    return root;
}

//функция поиска минимального ключа в дереве
node *search_min_key(node *root) {
    node *left_under_tree = root;
    while (left_under_tree->left != NULL) {
        left_under_tree = left_under_tree->left;
    }
    return left_under_tree;
}

//функция поиска максимального ключа в дереве
node *search_max_key(node *root) {
    node *right_under_tree = root;
    while (right_under_tree->right != NULL) {
        right_under_tree = right_under_tree->right;
    }
    return right_under_tree;
}

//функция обхода дерева по убыванию ключей 
void walk_descending_tree(node *root) {
    if (root == NULL)
        return;
    walk_descending_tree(root->left);
    walk_descending_tree(root->right);
}

//функция обхода дерева по возрастанию ключей
void walk_ascending_tree(node *root) {
    if (root == NULL)
        return;
    walk_ascending_tree(root->right);
    walk_ascending_tree(root->left);
}

//функция построения дерева
node *building_the_tree(int* arr, int size) {
    node *root = create_tree(0, arr[0], 0);
    for(int i = 1; i < size; i++)
        add_leaf(root, 0, arr[i]);
    return root;
}

//функция вращения относительно узла вправо
node* rot_right(node *root) {
    node *tmp_root = NULL;
    if (root != NULL) {
        tmp_root = root->left;
        root->left = tmp_root->right;
        tmp_root->right = root;
    }
    return tmp_root;
}

//функция вращения относительно узла влево
node* rot_left(node *root) {
    node *tmp_root = NULL;
    if (root != NULL) {
        tmp_root = root->right;   
        root->right = tmp_root->left;
        tmp_root->left = root;
    }
    return tmp_root;
}

//функция для перемещения выбранного узла в корень дерева
node *part_tree_right(node *root, int size_tree) {
    if (root->left != NULL) {
        int tmp_size_tree = root->left->size_tree;
        if (tmp_size_tree > size_tree) {
            root->left = part_tree_right(root->left, size_tree);
            root = rot_right(root);
        }
        if (tmp_size_tree < size_tree) {
            if (root->right != NULL) {
                root->right = part_tree_right(root->right, size_tree - tmp_size_tree - 1);
                root = rot_left(root);
            }
        } 
    }
    return root;
}

node *part_tree_left(node *root, int size_tree) {
    if (root->right != NULL) {
        int tmp_size_tree = root->right->size_tree;
        if (tmp_size_tree > size_tree) {
            if (root->left != NULL) {
                root->left = part_tree_left(root->left, size_tree);
                root = rot_right(root);
            }
        }
        if (tmp_size_tree < size_tree) {
            root->right = part_tree_left(root->right, size_tree - tmp_size_tree - 1);
            root = rot_left(root);
        } 
    }
    return root;
}
//рекурсивная функция для балансировки всех дерева и его поддеревьев
node *balance_tree_right(node *root) {
    if (root != NULL) {
        if (root->size_tree < 2) 
            return root;
        root = part_tree_right(root, root->size_tree / 2);
        root->left = balance_tree_right(root->left);
        root->right = balance_tree_right(root->right);
    }
    return root;
}

node *balance_tree_left(node *root) {
    if (root != NULL) {
        if (root->size_tree < 2) 
            return root;
        root = part_tree_left(root, root->size_tree / 2);
        root->left = balance_tree_left(root->left);
        root->right = balance_tree_left(root->right);
    }
    return root;
}
//функция печати дерева в консоль
void print_tree(node *root, int level) {
    if (root != NULL) {
        if (root->right) {
            print_tree(root->right, level + 1);
        }
        for (int i = 0; i < level; i++) 
            printf(" ");
        printf("%d\n", root->data);
        if (root->left) {
            print_tree(root->left, level + 1);
        }
    }
}

//функция для вычисления количества всех узлов определенного узла
void count_knot_of_tree(node *root, int *count) {
    if (root != NULL) {
        count_knot_of_tree(root->right, count);
        (*count)++;
        count_knot_of_tree(root->left, count);
    }
}

//функция вычисления всех количества узлов каждого узла дерева
void count_knot_of_all_trees(node *root) {
    if (root != NULL) {
        count_knot_of_all_trees(root->right);
        count_knot_of_all_trees(root->left);
        count_knot_of_tree(root, &root->size_tree);
    }
}

node *search_delete_element(node *root) {
    node *tmp_right = root, *tmp_left = NULL;

    if (tmp_right->right != NULL) 
        return search_min_key(tmp_right->right);

    tmp_left = tmp_right->parent;

    while ((tmp_left != NULL) && (tmp_right == tmp_left->right)) {
        tmp_right = tmp_left;
        tmp_left = tmp_left->parent;
    }

    return tmp_left;
}

node *delete_tree_value(node *root, int data) {
    node *tmp_left = NULL, *tmp_mid = NULL;

    tmp_left = search_knot(root, data);

    if ((tmp_left->left == NULL) && (tmp_left->right == NULL)) {
        tmp_mid = tmp_left->parent;
        if (tmp_left == tmp_mid->right) 
            tmp_mid->right = NULL;
        if (tmp_left != tmp_mid->right)
            tmp_mid->left = NULL;
        free(tmp_left);
    }

    if ((tmp_left->left == NULL) && (tmp_left->right != NULL)) { 
        tmp_mid = tmp_left->parent;
        if (tmp_left == tmp_mid->right) 
            tmp_mid->right = tmp_left->right;
        if (tmp_left != tmp_mid->right)
            tmp_mid->left = tmp_left->right;
        free(tmp_left);
    }

    if ((tmp_left->left != NULL) && (tmp_left->right == NULL)) {
        tmp_mid = tmp_left->parent;
        if (tmp_left == tmp_mid->right) 
            tmp_mid->right = tmp_left->left;
        if (tmp_left != tmp_mid->right)
            tmp_mid->left = tmp_left->left;
        free(tmp_left);
    }

    if ((tmp_left->left != NULL) && (tmp_left->right != NULL)) {
        tmp_mid = search_delete_element(tmp_left);
        tmp_left->data = tmp_mid->data;
        if (tmp_mid->right == NULL) 
            tmp_mid->parent->left = NULL;
        else
            tmp_mid->parent->left = tmp_mid->right;
        free(tmp_mid);
    }

    return root;
}

void delete_tree(node *root, int *arr, int size) {
    for (int i = size - 1; i >= 0; i--)
        delete_tree_value(root, arr[i]);
}

//основной метод
int main(int argc, char* argv[]) {
    int arr[] = { 200, 202, 345, 643, 653, 624, 137, 795, 1234, 670, 15, 111, 81, 21, 12, 101, 131, 161, 42, 35, 20, 76, 23, 14, 60, 32, 65, 91, 100, 45, 146, 43, 44, 67, 79, 83, 150, 38, 25, 102 };
    node* root = building_the_tree(arr, SIZE); 
    count_knot_of_all_trees(root);
    printf("%d\n", root->data);
    print_tree(root, 0);
    root = balance_tree_right(root);
    root = balance_tree_left(root);
    print_tree(root, 0);
    printf("%d\n", root->data);
    return 0;
}
