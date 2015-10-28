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

double metropolis(double T, double &E, mat &spin_matrix, int n)
{
    // E is in units of E/J and T = 1/beta*J
    srand(time(NULL));
    int x[n], y;
    double w, DE_x, DE_y, DE;
    for (int i=0; i<n; i++)
    {
    for (int j=0; j<n; j++)
    {
        x[i] = 2*((double) rand() / (RAND_MAX));

        cout << "x=" << x[i] << endl;
        y = 2*((double) rand() / (RAND_MAX));
    if (x[i]<1)
    {
        DE_x = 2*spin_matrix(x[i],y)*spin_matrix(x[i]+1,y);
    }
    else
    {
        DE_x = 2*spin_matrix(x[i],y)*spin_matrix(x[i]-1,y);
    }
    if (y<1)
    {
        DE_y = 2*spin_matrix(x[i],y)*spin_matrix(x[i],y+1);
    }
    else
    {
        DE_y = 2*spin_matrix(x[i],y)*spin_matrix(x[i],y-1);
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
    }
    }

}


int main()
{
    int n=2;
    double E = 10;
    double T = 1.0;
    mat spin(n,n);
    spin(0,0) =-1;
    spin(0,1) = -1;
    spin(1,0) = 1;
    spin(1,1) = 1;
    double E_expectation = 0;
    int mccycles = 10;
    for (int cycles = 1; cycles <= mccycles; cycles++)
    {
        metropolis(T,E,spin, n);
        E_expectation += E;
        cout << "cycle:" << setw(10) << cycles << setw(10) << "E:" << E << endl;
    }
    cout << "Expectation value:" << setw(20) << E_expectation << endl;
    return 0;
}

