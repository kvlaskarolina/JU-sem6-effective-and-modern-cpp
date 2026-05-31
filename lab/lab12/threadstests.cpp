#include <iostream>
#include <thread>
#include <future>

using namespace std;
int a = 0;
int b = 0;

int f(){
  a = 1;
  auto x = b;
  return x;
}

int g(){
  b = 1;
  auto y = a;
  return y;
}

int main(){
  auto tf = async(f);
  auto tg = async(g);
  cout << tf.get() << " " <<  tg.get() << endl;
}