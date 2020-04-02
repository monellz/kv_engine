#ifndef LSM_H_
#define LSM_H_

#include <iostream>
#include <vector>
#include <mutex>
#include "vlog_manager.h"
#include "skiplist.h"

namespace polar_race {
using namespace std;

typedef SkipList<WiscKey, WiscValue> Memtable;

static const int kMemtableNum = 16;
static const int kMergeNum = 8;
static const int kItemPerTable = 4096;

class LSM {
private:
    vector<Memtable*> memtables;
    int active_table;

    std::string dir_name;
    VlogManager vlog_manager;

public:

    LSM(const std::string& name): vlog_manager(name + "/" + "VLOG"){
        //TODO: recover
        dir_name = name;
        //mkdir
        if (0 != mkdir(dir_name.c_str(), 0755)) {
            return;
        }

        for (int i = 0; i < kMemtableNum; ++i) {
            memtables.push_back(new Memtable());
        }

        active_table = 0;
    }

    void insert_key(const WiscKey& key, const std::string& value) {
        if (memtables[active_table]->size >= kItemPerTable) {
            active_table++;
        }

        //TODO: if active_table >= table_num

        WiscValue wv;
        vlog_manager.append(value, wv);
        memtables[active_table]->insert(key, wv);
    }

    bool lookup(const WiscKey& key, std::string& value) {
        bool found = false;
        WiscValue wv;
        for (int i = active_table; i >= 0; --i) {
            if (memtables[active_table]->lookup(key, wv)) {
                found = true; 
                break;
            }
        }

        if (found) {
            vlog_manager.search(wv, value);
            return true;
        }
        return false;
    }


    ~LSM() {
        //TODO
        for (int i = 0; i < kMemtableNum; ++i) {
            delete memtables[i];
        }
    }
    
};

} //namespace polar_race


#endif //LSM_H_
