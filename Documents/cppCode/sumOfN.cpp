#include <iostream>
#include <string>

using namespace std;

int main() {
  string input;
  int finalNum = 0;
  cout << "Pick a number:" << endl;
  cin >> input;

  int n = stoi(input);

  for(int i = 0; i <=n; ++i) {
    if(i % 3 ==0 || i % 5 ==0) {
      finalNum = finalNum + i;
    }
  }
  cout << finalNum << endl;
}
