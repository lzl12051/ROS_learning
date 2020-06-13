#include <iostream>
#include <bitset>
using namespace std;
int main()
{
    unsigned long a = 999999999999999999+999999999999;
    std::cout << "bin:i=" << bitset<sizeof(unsigned long) * 8>(a) << endl;
    unsigned long b = a << 4;
    std::cout << "bin:i=" << bitset<sizeof(unsigned int) * 8>(b) << endl;
    std::cout << b << endl;
    unsigned long c = a^b;
    std::cout << c << endl;
    std::cout << "bin:i=" << bitset<sizeof(unsigned int) * 8>(c) << endl;

    

    return 0;
}