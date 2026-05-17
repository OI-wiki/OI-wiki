#include <ctime>
#include <iostream>
#include <random>

using namespace std;

int main() {
  mt19937 myrand(time(nullptr));
  cout << myrand() << endl;
  return 0;
}
