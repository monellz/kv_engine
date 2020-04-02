#ifndef WISCKEY_H_
#define WISCKEY_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>

namespace polar_race {

static const uint8_t kMaxKeyLen = 32;

struct WiscKey {
    char key[kMaxKeyLen];
    uint32_t key_size;
    WiscKey(): key(""), key_size(0) {}
    WiscKey(const std::string& str) {
        key_size = str.size();
        memcpy(key, str.data(), key_size);
    }
    bool operator==(const WiscKey& y) const {
        return key_size == y.key_size && (memcmp(key, y.key, key_size) == 0);
    }
    bool operator!=(const WiscKey& y) const {
        return !(*this == y);
    }
    bool operator>(const WiscKey& y) const {
        const size_t min_len = (key_size < y.key_size)? key_size: y.key_size;
        int r = memcmp(key, y.key, min_len);
        return r > 0 || (r == 0 && key_size > y.key_size);
    }
    bool operator<(const WiscKey& y) const {
        const size_t min_len = (key_size < y.key_size)? key_size: y.key_size;
        int r = memcmp(key, y.key, min_len);
        return r < 0 || (r == 0 && key_size < y.key_size);
    }
};

struct WiscValue {
    int file_idx;
    int offset;
    WiscValue(): file_idx(0), offset(0) {}
    WiscValue(int idx_, int offset_): file_idx(idx_), offset(offset_) {} 
};

std::ostream& operator<<(std::ostream &out, const WiscKey& k);

std::ostream& operator<<(std::ostream &out, const WiscValue& v);

}




#endif