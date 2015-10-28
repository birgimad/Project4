#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;
#include "include\armadillo"
using namespace arma;

int main()
{
    int n=2;
    double E = 0;
    double T = 1.0;
    mat spin_matrix(n,n);
    spin_matrix(0,0) =-1;
    spin_matrix(0,1) = -1;
    spin_matrix(1,0) = 1;
    spin_matrix(1,1) = 1;
    double E_expectation = 0;
    int mccycles = 20;

    int x[n], y[n];
    double w, DE_x, DE_y, DE;
    srand(time(NULL));

    for (int cycles = 1; cycles <= mccycles; cycles++)
        {
    for (int k=0; k<n; k++)
    {
    for (int i=0; i<n; i++)
    {
    x[i] = 2*((double) rand() / (RAND_MAX));
    y[i] = 2*((double) rand() / (RAND_MAX));
    //cout << "x=" << setw(5) << x[i] << setw(5) << "y=" << setw(5) << y[i] << endl;
    if (x[i]<1)
    {
        DE_x = 2*spin_matrix(x[i],y[i])*spin_matrix(x[i]+1,y[i]);
    }
    else
    {
        DE_x = 2*spin_matrix(x[i],y[i])*spin_matrix(x[i]-1,y[i]);
    }
    if (y[i]<1)
    {
        DE_y = 2*spin_matrix(x[i],y[i])*spin_matrix(x[i],y[i]+1);
    }
    else
    {
        DE_y = 2*spin_matrix(x[i],y[i])*spin_matrix(x[i],y[i]-1);
    }
    DE = DE_x+DE_y;
    if (DE <= 0)
    {
        E += DE;
    }
    else
    {
        w = exp(-DE/T);
        if (w > ((double) rand() / (RAND_MAX)))
        {
            E += DE;
        }
    }
    spin_matrix(x[i],y[i]) = -spin_matrix(x[i],y[i]);
    }
    }

    E_expectation += E;
    cout << "cycle:" << setw(10) << cycles << setw(10) << "E:" << E << endl;
}
cout << "Expectation value:" << setw(20) << E_expectation/mccycles << endl;

    return 0;
}



