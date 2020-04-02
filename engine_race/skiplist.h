#ifndef SKIPLIST_H_
#define SKIPLIST_H_

#include <cstring>
#include <cstdlib>
#include <iostream>

template<class K, class V, unsigned int MAX_LEVEL>
struct SkipListNode {
    const K key;
    V value;
    SkipListNode* forward[MAX_LEVEL + 1];
    SkipListNode(const K& k): key(k) {
        //memset(forward, NULL, sizeof(forward));
        for (int i = 0; i <= MAX_LEVEL; ++i) {
            forward[i] = nullptr;
        }
    }
    SkipListNode(const K& k, const V& v): key(k), value(v) {
        //memset(forward, NULL, sizeof(forward));
        for (int i = 0; i <= MAX_LEVEL; ++i) {
            forward[i] = nullptr;
        }
    }

};

template<class K, class V, unsigned int MAX_LEVEL = 16>
struct SkipList {
    typedef SkipListNode<K, V, MAX_LEVEL> Node;
    Node* head;
    K min_key;
    K max_key;
    int size;
    int level;

    SkipList(): head(NULL), size(0), level(0) {
        head = new Node(K());
    }

    int random_level() {
        static const unsigned int p = 4;     
        int lvl = 0;
        while (lvl < MAX_LEVEL && (rand() % p == 0)) {
            lvl++;
        }
        return lvl;
    }

    void insert(const K& key, const V& value) {
        Node* update[MAX_LEVEL + 1];
        auto cur = this->head;
        for (int i = this->level; i >= 0; i--) {
            while (cur->forward[i] != nullptr && cur->forward[i]->key < key) {
                cur = cur->forward[i];
            }
            update[i] = cur;
        }
        cur = cur->forward[0];
        if (cur == nullptr || cur->key != key) {
            //insert 
            if (key > max_key || size == 0) max_key = key;
            else if (key < min_key || size == 0) min_key = key;
            auto lvl = random_level();
            if (lvl > this->level) {
                for (int i = this->level + 1; i <= lvl; ++i) {
                    update[i] = this->head;
                }
                this->level = lvl;
            }
            auto new_node = new Node(key, value);
            for (int i = 0; i <= lvl; ++i) {
                new_node->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = new_node;
            }
            this->size++;
        } else {
            //update
            cur->value = value;
        }
    }

    bool lookup(const K& key, V& value) {
        auto cur = this->head;
        for (int i = this->level; i >= 0; i--) {
            while (cur->forward[i] != nullptr && cur->forward[i]->key < key) {
                cur = cur->forward[i];
            }
        }
        cur = cur->forward[0];
        if (cur != nullptr && cur->key == key) {
            value = cur->value;
            return true;
        } else {
            return false;
        }
    }

    void show_list() {
        std::cout << "----skip list---- size:" << size << std::endl;
        for (int i = 0; i <= this->level; ++i) {
            auto cur = this->head->forward[i];
            while (cur != nullptr) {
                std::cout << "(" << cur->key << "," << cur->value << ")";
                if (cur->forward[i] != nullptr) {
                    std::cout << "->";
                }
                cur = cur->forward[i];
            }
            std::cout << std::endl;
        }
    }

    ~SkipList() {
        auto cur = this->head->forward[0];
        while (cur != nullptr) {
            auto tmp = cur;
            cur = cur->forward[0];
            delete tmp;
        }
        delete this->head;
    }
};




#endif //SKIPLIST_H_
