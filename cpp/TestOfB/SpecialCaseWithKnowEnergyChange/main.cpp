#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;
#include "include\armadillo"
using namespace arma;

int main()
{
    int n=2;
    double E = 0, M = 0;   //initializing energy
    double T = 1.0; //temperature
    mat spin_matrix(n,n);
    spin_matrix(0,0) = 1;
    spin_matrix(0,1) = -1;
    spin_matrix(1,0) = 1;
    spin_matrix(1,1) = 1;

    cout << "spin matrix before switching spin:" << endl;
    cout << spin_matrix << endl;

    int x, y;
    double w, DE_x, DE_y, DE;

    //choose to switch spin in first row, second column
    x = 0;
    y = 1;
    //cout << "x=" << setw(5) << x[i] << setw(5) << "y=" << setw(5) << y[i] << endl;
    if (x<1)
    {
        DE_x = 4*spin_matrix(x,y)*spin_matrix(x+1,y);
    }
    else
    {
        DE_x = 4*spin_matrix(x,y)*spin_matrix(x-1,y);
    }
    if (y<1)
    {
        DE_y = 4*spin_matrix(x,y)*spin_matrix(x,y+1);
    }
    else
    {
        DE_y = 4*spin_matrix(x,y)*spin_matrix(x,y-1);
    }
    DE = DE_x+DE_y;
    if (DE <= 0)
    {
        E += DE;
        M += -2*spin_matrix(x,y);
        spin_matrix(x,y) = -spin_matrix(x,y);
    }
    else
    {
        w = exp(-DE/T);
        if (w > ((double) rand() / (RAND_MAX)))
        {
            E += DE;
            M += -2*spin_matrix(x,y);
            spin_matrix(x,y) = -spin_matrix(x,y);
        }
    }

    cout << "spin matrix after switching spin:" << endl;
    cout << spin_matrix << endl;

    cout << setw(10) << "change in energy due to switch of spin:" << E << endl;
    cout << setw(10) << "change in magnetization due to switch of spin:" << M << endl;

    return 0;
}



