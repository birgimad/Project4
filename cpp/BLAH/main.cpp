#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;

int main()
{
    int x = 0;
    int y = 0;
    srand(time(NULL));
    x = 2*((double) rand() / (RAND_MAX));
    y = 2*((double) rand() / (RAND_MAX));
    cout << x << endl;
    cout << y << endl;
    cout << time(NULL) << endl;
    return 0;
}

