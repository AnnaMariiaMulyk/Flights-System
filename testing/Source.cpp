#include <ctime>
#include <iostream>
using namespace std;
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

int main()
{
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    cout << now->tm_year+1900 << endl;
    cout << now->tm_mon + 1 << endl;
    cout << now->tm_mday << endl;

    return 0;
}