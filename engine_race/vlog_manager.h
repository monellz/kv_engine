#ifndef VLOG_MANAGER_H_
#define VLOG_MANAGER_H_

#include <string>
#include "wisckey.h"
#include "util.h"

namespace polar_race {

static const int kSingleFileSize = 1024 * 1024 * 100;

struct VlogManager {
    std::string file_prefix;
    int current_file_idx;
    int next_location;

    VlogManager(const std::string& prefix): file_prefix(prefix), current_file_idx(0), next_location(0) {};
    bool append(const std::string& value, WiscValue& wv);
    bool search(const WiscValue& value, std::string& res);
};


}

#endif