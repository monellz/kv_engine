#include "vlog_manager.h"

using namespace polar_race;


bool VlogManager::append(const std::string& value, WiscValue& wv) {
    std::string fn = file_prefix + std::to_string(current_file_idx);
    int fd = open(fn.c_str(), O_APPEND | O_WRONLY | O_CREAT, 0644);
    uint32_t size = value.size();
    char buf[4];
    buf[0] = 0xff & size;
    buf[1] = 0xff & (size >> 8); 
    buf[2] = 0xff & (size >> 16); 
    buf[3] = 0xff & (size >> 24); 
    std::string item = std::string(buf, 4) + value;
    if (file_append(fd, item) < 0) {
        close(fd);
        return false;
    }
    close(fd);
    wv.file_idx = current_file_idx;
    wv.offset = next_location;
    next_location += item.size();

    if (next_location > kSingleFileSize) {
        next_location = 0;
        current_file_idx += 1;
    }

    return true;
}

bool VlogManager::search(const WiscValue& value, std::string& res) {
    std::string fn = file_prefix + std::to_string(value.file_idx);    
    int fd = open(fn.c_str(), O_RDONLY, 0644);
    if (fd < 0) return false;
    lseek(fd, value.offset, SEEK_SET);
    char size_buf[4];
    char* pos = size_buf;

    int len = 4;
    while (len > 0) {
        ssize_t r = read(fd, pos, len);
        if (r < 0) {
            if (errno == EINTR) continue;
            close(fd);
            return false;
        }
        pos += r;
        len -= r;
    }

    uint32_t value_size;
    value_size = size_buf[0] & 0xff;
    value_size |= size_buf[1] << 8;
    value_size |= size_buf[2] << 16;
    value_size |= size_buf[3] << 24;

    char* buf = new char[value_size]();
    pos = buf;

    len = value_size;
    while (len > 0) {
        ssize_t r = read(fd, pos, len);
        if (r < 0) {
            if (errno == EINTR) continue;
            close(fd);
            return false;
        } 
        pos += r;
        len -= r;
    }
    res = std::string(buf, value_size);
    close(fd);
    delete [] buf;

    return true;
}