#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <cctype>
#include <ctime>
#include <thread>
#include <utility>
#include <thread>
#include <chrono>
using namespace std;


std::mutex random_mutex;

template <int N>
struct Array{
    int a[N];
    // int i  = 0;
    // int value = 1;
	long long sum = 0;

	int f(int x){
		int y = x%11;
		return (y*y+1);
	}

	void generateArray(int begin, int end) {
        for (int i = begin; i < end; ++i)
            a[i] = gen();

        for (int i = begin; i < end; ++i)
            a[i] = f(a[i]);
    }

	int gen(){
		std::lock_guard<std::mutex> lock(random_mutex);
		return rand();
	}
	
	long long computeSum(){
	    sum = 0;
		for(int x : a){
			sum += x;
		}
		return sum;
	}
};

int main(){
	srand(2019);
	using A = Array<1000>;
	A array;
	std::thread t1(&A::generateArray, &array, 0,   500);
    std::thread t2(&A::generateArray, &array, 500, 1000);

    t1.join();
    t2.join();
	for(int i=0; i<40; i++){
		cout << array.a[0+i] << "  ";
	}
	long long sum = array.computeSum();
	cout << "\n sum = " << sum << endl;	
}