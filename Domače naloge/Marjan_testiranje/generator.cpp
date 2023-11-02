#include <iostream>
#include <random>
using namespace std;

int main()
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr1(1, 15); // define the range
    int n = 15;
    int k = 3;
    int a = 1;
    cout << n << " " << k << " " << a <<"\n";
    for (int i = 0; i < n; i++)
    {
        cout << (distr1(gen)) << "\n";
    }
    
    return 0;
}
