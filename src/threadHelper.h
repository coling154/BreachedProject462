#ifndef THREAD_HELPER_H
#define THREAD_HELPER_H

#include <fstream>
#include <sstream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>


// Declares the atomic variable used globally
extern std::atomic<bool> found;

void searchHash(const std::vector<std::string>& lines, size_t targetHash);
void distributeSearch(const std::string& input_path, size_t targetHash, int num_threads);
void hashLinesTask(const std::vector<std::string>& lines, std::fstream& out_file, std::mutex& out_mutex);
void distributeWork(const std::string& input_path, std::fstream& out_file, int num_threads);

#endif // THREAD_HELPER_H
