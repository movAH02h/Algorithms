#include <algorithm>
#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>

int do_option_to_file(const char* name_file, const char* name_option);

int write_to_file(const char* file_read, const char* file_write);

int print_file(const char* file_name);

namespace mystd
{
    std::vector<const char*>::iterator find(std::vector<const char*>& strings, const char* target);
}

