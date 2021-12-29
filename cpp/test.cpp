#include <iostream>
using namespace std;

bool test(double a)
{
  return a > 5 ? false : true;
}

inline const char *const BoolToString(bool b)
{
  return b ? "true" : "false";
}

int main()
{
  // cout << BoolToString(test(2));
  // cout << "\n";
  double a = -1.2;
  cout << BoolToString(a > -3);
  return 0;
}
