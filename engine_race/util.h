#ifndef UTIL_H_
#define UTIL_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>

namespace polar_race {

int file_append(int fd, const std::string& value);


} //namespace polar_race
#endif
