#ifndef STRING_HASH_H
#define STRING_HASH_H
#include <iostream>
#include <cstddef>
#include <string>

class StringHash {
public:
    size_t operator()(const std::string& s) const;
};

#endif // STRING_HASH_H
