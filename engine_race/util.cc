#include "util.h"

namespace polar_race {

int file_append(int fd, const std::string& value) {
    if (fd < 0) return -1;

    size_t value_len = value.size();
    const char* pos = value.data();
    while (value_len > 0) {
        ssize_t r = write(fd, pos, value_len);
        if (r < 0) {
            if (errno == EINTR) {
                continue;
            }
            return -1;
        }
        pos += r;
        value_len -= r;
    }
    return 0;
}


}