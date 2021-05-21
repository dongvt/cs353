#include <iostream>
using namespace std;

int main()
{
   long fibs[2] = {0, 1};

   for (int i = 3; i < 42; i++)
      fibs[i % 2] = fibs[0] + fibs[1];

   cout << fibs[0] << endl;

   return 0;
}