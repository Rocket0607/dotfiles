#include <iostream>
#include <string>

using namespace std;

int main() {
  string input;
  string sumOrMultiply;
  cout << "Choose a number:" << endl;
  cin >> input;
  cout << "What would you like to do with this number? (Type in sum or multiply)" << endl;
  cin >> sumOrMultiply;

  int n = stoi(input);

  if(sumOrMultiply == "sum") {
    int finalNum = 0;
    for(int i = 0; i <=n; ++i) {
      finalNum = finalNum + i;
    }
    cout << finalNum << endl;
  }

  else if(sumOrMultiply == "multiply") {
    int finalNum = 1;
    for(int i = 1; i <=n; ++i) {
      finalNum = finalNum * i;
    }
    cout << finalNum << endl;
  }

  else {
    cout << "Please select either sum or multiply." << endl;
  }
}
