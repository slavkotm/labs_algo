#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

// размер хеш таблицы
const int T_S = 5;

// создание класса хеш таблицы
class HashTable {

   public:


      int k; // параметр ключа
      int v; // параметр значения

      HashTable(int k, int v) {
         this->k = k;
         this->v = v;
      }

};

// создание класса удаления элемента из таблицы, который наследуется от класса хеш таблицы
class DelNode : public HashTable {

   private:
      static DelNode *en;
      DelNode() : HashTable(-1, -1) {}

   public:
      static DelNode *getNode() {
         if (en == NULL)
            en = new DelNode();
         return en;
     }
};

DelNode *DelNode::en = NULL;

// создание класса хеш таблицы (ключ, значение)
class HashMapTable {
   private:

      HashTable **ht;
   public:
      // создание хеш таблицы(инициализация)
      HashMapTable() {
         ht = new HashTable* [T_S];
         for (int i = 0; i < T_S; i++) {
            ht[i] = NULL;
         }
      }
        
      void printHashTable() {
          for(int i = 0; i < T_S; i++) {
              cout << "key: " << ht[i]->k << " ---> value:" << ht[i]->v  << endl;
          }
      }

      // хеш функция 
      int HashFunc(int k) {
         return k % T_S;
      }

      // вставка в хеш таблицу
      void Insert(int k, int v) {
         int hash_val = HashFunc(k);
         int init = -1;
         int delindex = -1;
         while (hash_val != init && ((ht[hash_val]  == DelNode::getNode()) || (ht[hash_val] != NULL) && (ht[hash_val]->k != k))) {
            if (init == -1)
               init = hash_val;
            if (ht[hash_val] == DelNode::getNode())
               delindex = hash_val;
               hash_val = HashFunc(hash_val + 1);
         }
         if (ht[hash_val] == NULL || hash_val == init) {
            if(delindex != -1)
               ht[delindex] = new HashTable(k, v);
            else
               ht[hash_val] = new HashTable(k, v);
         }
         if(init != hash_val) {
            if (ht[hash_val] != DelNode::getNode()) {
               if (ht[hash_val] != NULL) {
                  if (ht[hash_val]->k== k)
                     ht[hash_val]->v = v;
               }
            } else
            ht[hash_val] = new HashTable(k, v);
         }
      }

      // поиск ключа в хеш таблице
      int SearchKey(int k) {
         int hash_val = HashFunc(k);
         int init = -1;
         while (hash_val != init && (ht[hash_val] == DelNode::getNode() || ht[hash_val] != NULL && ht[hash_val]->k!= k)) {
            if (init == -1)
               init = hash_val;
               hash_val = HashFunc(hash_val + 1);
         }
         if (ht[hash_val] == NULL || hash_val == init)
            return -1;
         else
            return ht[hash_val]->v;
      }

      // удаление ключа из хеш таблицы
      void Remove(int k) {
         int hash_val = HashFunc(k);
         int init = -1;
         while (hash_val != init && (ht[hash_val] == DelNode::getNode() || ht[hash_val] != NULL && ht[hash_val]->k!= k)) {
            if (init == -1)
               init = hash_val;
               hash_val = HashFunc(hash_val + 1);
         }
         if (hash_val != init && ht[hash_val] != NULL) {
            delete ht[hash_val];
            ht[hash_val] = DelNode::getNode();
         }
      }

      // деструктор
      ~HashMapTable() {
         delete[] ht;
      }
};

int main() {
   HashMapTable hash;
   
   hash.Insert(4, 6);
   hash.Insert(2, 8);
   hash.Insert(1, 12);
   hash.Insert(23, 7);
   hash.Insert(45, 434);
   hash.Insert(2, 4);

   hash.printHashTable();




   return 0;
}
