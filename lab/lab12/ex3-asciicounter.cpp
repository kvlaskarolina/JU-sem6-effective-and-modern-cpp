#include <iostream>
#include <fstream>
#include <thread>
#include <future>
#include <vector>
#include <string>

void fileSum(const std::string& filePath, std::promise<long long> promise) {
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        promise.set_exception(std::make_exception_ptr(
            std::runtime_error("Cannot open file: " + filePath)
        ));
        return;
    }

    long long sum = 0;
    char c;
    while (file.get(c)) {
        sum += static_cast<unsigned char>(c);
    }

    promise.set_value(sum);
}

int main(int argc, char* argv[]) {

    std::vector<std::string> files(argv + 1, argv + argc);
    std::vector<std::thread> threads;
    std::vector<std::future<long long>> futures;

    
    for (const auto& file : files) {
        std::promise<long long> promise;
        futures.push_back(promise.get_future());
        threads.emplace_back(fileSum, file, std::move(promise));
    }

    for (auto& th : threads)
        th.join();

    std::vector<long long> sums(files.size());
    for (size_t i = 0; i < futures.size(); i++) {
        try {
            sums[i] = futures[i].get();
            std::cout << files[i] << " : " << sums[i] << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error reading " << files[i] << ": " << e.what() << "\n";
            sums[i] = -1;
        }
    }

    
    std::cout << "\nta sama suma\n";
    bool found = false;
    for (size_t i = 0; i < files.size(); i++) {
        for (size_t j = i + 1; j < files.size(); j++) {
            if (sums[i] != -1 && sums[i] == sums[j]) {
                std::cout << files[i] << " == " << files[j]
                          << "  (suma = " << sums[i] << ")\n";
                found = true;
            }
        }
    }

    if (!found)
        std::cout << "---\n";

    return 0;
}