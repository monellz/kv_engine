#include <iostream>
#include "skiplist.h"

using namespace std;


int main() {
    auto list = new SkipList<int, int>();
    list->show_list();
    list->insert(1, 0);
    list->show_list();
    list->insert(2, 1);
    list->show_list();
    list->insert(3, 2);
    list->show_list();
    list->insert(4, 3);
    list->show_list();
    list->insert(5, 4);
    list->show_list();
    list->insert(6, 5);
    list->show_list();
    list->insert(7, 6);
    list->show_list();
    list->insert(8, 7);
    list->show_list();

    int val = -1;
    if (list->lookup(3, val)) {
        cout << "find 3, val: " << val << endl;
    } else {
        cout << "not find 3" << endl;
    }
    if (list->lookup(10, val)) {
        cout << "find 10, val: " << val << endl;
    } else {
        cout << "not find 10" << endl;
    }

    delete list;
    return 0;
}

