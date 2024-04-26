#include "stringHash.h"
size_t StringHash::operator()(const std::string& s)const {
    if (s.empty()){
        // should never happen
        return 0;
    }
    size_t hash = 0;
    std::string toHash = s;
    for (char c : toHash) {
        // makes smaller hashes 31 is prime
        hash = hash * 31 + c;

    }
    /*
    if (s.compare("jscockburn@yahoo.com")==0){
        std::cout << "test hash: " << std::to_string(hash) << std::endl;

    }
    if (s.compare("leemedical@verizon.net")==0){
        std::cout << "test hash: " << std::to_string(hash) << std::endl;

    }
    */
    return hash;
}
