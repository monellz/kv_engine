#include "wisckey.h"

namespace polar_race {

std::ostream& operator<<(std::ostream &out, const WiscKey& k) {
    for (int i = 0; i < (int)k.key_size; ++i) out << k.key[i];
    return out;
}

std::ostream& operator<<(std::ostream &out, const WiscValue& v) {
    out << "(" << v.file_idx << ", " << v.offset << ")";
    return out;
}


}