#include "stringHash.h"
#include "threadHelper.h"


std::atomic<bool> found(false);

// Searches a given set of lines for a specific hash value, stopping if found by this or any thread.
void searchHash(const std::vector<std::string>& lines, size_t targetHash) {
    // Iterate over each line provided to this thread
    for (const std::string& line : lines) {
        // check if the hash was already found
        if (found.load(std::memory_order_acquire)) {
            return;
        }

        std::istringstream line_stream(line);
        std::string part;
        // Split the line get part
        if (std::getline(line_stream, part, ':')) {
            size_t currentHash = std::stoull(part); // convert ro size_t
            // Check if the converted hash matches the target hash.
            if (currentHash == targetHash) {
                found.store(true, std::memory_order_release); // Indicate hash found for all threads.
                std::cout << "Hash found: " << part << std::endl; // Output found hash.
                return; // Exit since the target hash has been found.
            }
        }
    }
}

// Distributes the work of searching for a hash across multiple threads.
void distributeSearch(const std::string& input_path, size_t targetHash, int num_threads) {
    std::ifstream input_file(input_path); // Open the file located at input_path.
    // Check if the file was successfully opened.
    if (!input_file.is_open()) {
        std::cerr << "Failed to open file: " << input_path << std::endl; // Error message if file cannot be opened.
        return; // Exit the function on failure to open the file.
    }

    std::vector<std::thread> threads; // Vector to hold all threads.
    std::vector<std::vector<std::string>> work(num_threads); // Work distribution vector.
    std::string line; // Variable to read lines of the file.
    int index = 0;

    // Read lines from the file and distribute them to workers
    while (getline(input_file, line)) {
        work[index % num_threads].push_back(line); // Assign line to a worker thread
        index++; // Increment index and send next line to the next thread
    }

    // Create and start threads
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(searchHash, std::ref(work[i]), targetHash); // Start a new thread for each set of work.
    }

    // wait for all threads
    for (auto& thread : threads) {
        if(thread.joinable()){
            thread.join(); // Ensure each thread has completed before continuing.
        }
    }

    // Check if the hash was found by a thread
    if (!found.load()) {
        std::cout << "Hash not found in any thread." << std::endl; // Message if hash was not found.
    }
}
void hashLinesTask(const std::vector<std::string>& lines, std::fstream& out_file, std::mutex& out_mutex) {
    StringHash hash_fn;
    std::stringstream ss;

    // for every line
    for (const std::string& line : lines) {
        std::string username, password;
        std::istringstream line_stream(line);

        // Get username string from the lineStream and split with :
        getline(line_stream, username, ':');
        // Get password string from lineStream
        getline(line_stream, password);

        // Hash username string
        size_t hash_username = hash_fn(username);
        // Hash password string
        size_t hash_password = hash_fn(password);
        // write username and hash to string stream
        ss << std::to_string(hash_username) << ":" << std::to_string(hash_password) << std::endl;
    }
    // Lock the mutex to safely write to the output file
    std::lock_guard<std::mutex> lock(out_mutex);
    // Write buffered data
    out_file << ss.str();
}

// for distributing the hashLinesTask to different threads
void distributeWork(const std::string& input_path, std::fstream& out_file, int num_threads) {
    // open realCredentials1.txt
    std::ifstream input_file(input_path);
    // Vector of all treads
    std::vector<std::thread> threads;
    // mutex to sync file writing
    std::mutex out_mutex;
    // holds each line read
    std::string line;
    // work distribution vector
    std::vector<std::vector<std::string>> work(num_threads);

    int index = 0; // Index to distribute lines to threads
    while (getline(input_file, line)) {
        work[index % num_threads].push_back(line);
        ++index;
    }

    // Create threads and assign them their respective chunks to process
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(hashLinesTask, std::ref(work[i]), std::ref(out_file), std::ref(out_mutex));
    }
    // Wait for threads to finish
    for (auto& t : threads) {
        t.join();
    }
}