#include <chrono>
#include "stringHash.h"
#include "threadHelper.h"


int main(int argc, char *argv[]) {
    std::string data_dir = "../data/";
    std::string hash_path = data_dir + "hashed.txt";
    std::fstream hashFile(hash_path, std::ios::out | std::ios::app);

    if (!hashFile) {
        std::cerr << "Error opening hashed.txt" << std::endl;
        return 1;
    }
    // if file has no contents
    if (hashFile.tellg() == 0) {
        // assemble file
        // Concat paths together
        std::string plaintext_path = data_dir + "realCredentials1.txt";
        std::cout << "hashed.txt is empty or dosen\'t exist \nStarted hashing realCredentials1.txt" << std::endl;
        // Save timePoint of systemClock
        auto start = std::chrono::system_clock::now();
        distributeWork(plaintext_path, hashFile, 4);  // 4 threads
        auto end = std::chrono::system_clock::now();
        // calculate time it took to hash and write file
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        std::cout << "Time taken to build: " << duration.count() << "s" << std::endl;
        hashFile.close();
    }

    // Check command line user input arguments
    if(argc != 2) {
        std::cout << "usage: breachedApp <email_string>" << std::endl;
        return 2;
    }
    // Get string from argument
    std::string plainText = argv[1];

    // Get Hash
    StringHash hash_fn;
    size_t hash = hash_fn(plainText);
    std::cout << "Hash: " << std::to_string(hash) << std::endl;

    // Search for hash in hashed.txt
    auto start = std::chrono::system_clock::now();
    distributeSearch(hash_path, hash, 4);
    auto end = std::chrono::system_clock::now();
    // calculate time it took to find the hash
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cout << "Search time: " << duration.count() << "s" << std::endl;
    return 0;
}
