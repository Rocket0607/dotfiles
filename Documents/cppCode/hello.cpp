#include <iostream>
#include <string>

using namespace std;
int main() {
  string name;
  cout << "What is your name?" << endl;
  cin >> name;
  if (name == "Bob" || name == "Alice") {
    cout << "Hello " << name << endl;
  }
  else {
    cout << "Sorry " << name << ", we do not have the correct permissions to greet you :(" << endl;
  }
}
