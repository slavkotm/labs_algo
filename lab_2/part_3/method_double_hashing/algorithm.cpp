// двойное хеширование
#include <bits/stdc++.h>

using namespace std;
  
// размер хеш таблицы
#define TABLE_SIZE 13
  
// константа для использования в другой хеш функции
#define PRIME 7
  
class DoubleHash {
    // указатель на хеш таблицу
    int* hashTable;
    int curr_size;
  
public:
    // функция проверки полноты хеш таблицы
    bool isFull()
    {
        return (curr_size == TABLE_SIZE);
    }
  
    // функция вычисления первого хеша
    int hash1(int key)
    {
        return (key % TABLE_SIZE);
    }
  
    // функция вычисления второго хеша
    int hash2(int key)
    {
        return (PRIME - (key % PRIME));
    }
  
    // конструктор класса для создания массива и его заполнения
    DoubleHash()
    {
        hashTable = new int[TABLE_SIZE];
        curr_size = 0;
        for (int i = 0; i < TABLE_SIZE; i++)
            hashTable[i] = -1;
    }
  
    // функция вставки ключа в хеш таблицу
    void insertHash(int key)
    {
        // проверка полноты хеш таблицы
        if (isFull())
            return;
  
        // получение индекса из первой хеш фукнции
        int index = hash1(key);
  
        // цикл заполнения хеш таблицы
        if (hashTable[index] != -1) {
            // получение второго индекса из вспомогательной хеш функции
            int index2 = hash2(key);
            int i = 1;
            while (1) {
                // получение нового индекса
                int newIndex = (index + i * index2) % TABLE_SIZE;
  
                // если нет коллизии вставляем ключ в хеш таблицу
                if (hashTable[newIndex] == -1) {
                    hashTable[newIndex] = key;
                    break;
                }
                i++;
            }
        }
  
        // если нет коллизии вставляем элемент в таблицу
        else
            hashTable[index] = key;
        curr_size++;
    }
  
    // функция поиска в хеш таблице по ключу
    void search(int key)
    {
        int index1 = hash1(key);
        int index2 = hash2(key);
        int i = 0;
        while (hashTable[(index1 + i * index2) % TABLE_SIZE] != key) {
            if (hashTable[(index1 + i * index2) % TABLE_SIZE] == -1) {
                cout << key << " does not exist" << endl;
                return;
            }
            i++;
        }
        cout << key << " found" << endl;
    }
  
    // функция вывода хеш таблицы
    void displayHash()
    {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (hashTable[i] != -1)
                cout << i << " --> "
                     << hashTable[i] << endl;
            else
                cout << i << endl;
        }
    }
};
  
// главный метод
int main()
{
    int a[] = { 19, 27, 36, 10, 64 };
    int n = sizeof(a) / sizeof(a[0]);
  
    // вставка ключей в хеш таблицу
    DoubleHash h;
    for (int i = 0; i < n; i++) {
        h.insertHash(a[i]);
    }
    // поиск нескольких ключей
    h.search(36); // этот ключ есть в таблице
    h.search(100); // этого ключа нет в таблице
    // печать хеш функции
    h.displayHash();
    return 0;
}
