#include <iostream>
#include <string>
#include "lsm.h"

using namespace std;

using namespace polar_race;


int main() {
    LSM lsm("test_lsm");    
    WiscKey k("abc");
    string v("abc");
    lsm.insert_key(k, v);

    for (int i = 0; i < 200; ++i) {
        WiscKey k(to_string(i));
        string v(to_string(i));
        lsm.insert_key(k, v);
        cout << i << " inserted" << endl;
    }

    cout << "inserted" << endl;
    for (int i = 0; i < 200; ++i) {
        WiscKey k(to_string(i));
        string v;
        if (lsm.lookup(k, v)) {
            cout << i << " found: " << v << endl;
        } else {
            cout << i << " not found" << endl;
        }
    }
}
