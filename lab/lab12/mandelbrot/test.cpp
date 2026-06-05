#include <iostream>
#include <thread>

unsigned int T = std::thread::hardware_concurrency();

int main(){
    std::cout << "Number of threads: " << T << std::endl;
    return 0;
}
