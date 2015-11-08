#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;
#include "armadillo"
using namespace arma;

int main()
{
    int n=2;
    double T;
    int mccycles;
    cout << "Please enter value of T:\n>";
    cin >> T;
    cout << "Please enter number of MC cycles:\n>";
    cin >> mccycles;
    double E = 0, M = 0, E_squared = 0, M_squared = 0, susceptibility, specific_heat;    //initialize energy and magnetization
    mat spin_matrix(n,n);
    spin_matrix(0,0) =-1;
    spin_matrix(0,1) = -1;
    spin_matrix(1,0) = 1;
    spin_matrix(1,1) = 1;
    double E_expectation = 0, M_expectation = 0, M_expectation2 = 0;

    int x[n], y[n];
    double w, DE_x, DE_y, DE;
    srand(time(NULL));

    for (int cycles = 1; cycles <= mccycles; cycles++)
        {
    for (int k=0; k<n; k++)
    {
    for (int i=0; i<n; i++)
    {
    x[i] = 1.99999*((double) rand() / (RAND_MAX));  //making sure that the row and column number is either 0 or 1 (randomly chosen - almost uniform)
    y[i] = 1.99999*((double) rand() / (RAND_MAX));
    //cout << "x=" << setw(5) << x[i] << setw(5) << "y=" << setw(5) << y[i] << endl;
    if (x[i]<1)
    {
        DE_x = 4*spin_matrix(x[i],y[i])*spin_matrix(x[i]+1,y[i]);
    }
    else
    {
        DE_x = 4*spin_matrix(x[i],y[i])*spin_matrix(x[i]-1,y[i]);
    }
    if (y[i]<1)
    {
        DE_y = 4*spin_matrix(x[i],y[i])*spin_matrix(x[i],y[i]+1);
    }
    else
    {
        DE_y = 4*spin_matrix(x[i],y[i])*spin_matrix(x[i],y[i]-1);
    }
    DE = DE_x+DE_y;
    if (DE <= 0)
    {
        E += DE;
        M += -2*spin_matrix(x[i],y[i]);
        spin_matrix(x[i],y[i]) = -spin_matrix(x[i],y[i]);
    }
    else
    {
        w = exp(-DE/T);
        if (w > ((double) rand() / (RAND_MAX)))
        {
            E += DE;
            M += -2*spin_matrix(x[i],y[i]);
            spin_matrix(x[i],y[i]) = -spin_matrix(x[i],y[i]);
        }
    }
    }
    }
//The computed energies are in the unit of E/J
//The computed susectibilty is in the unit J*Chi
//The computed specific heat is in the unit c_v / k_B
    E_expectation += E;
    M_expectation += M;
    M_expectation2 += fabs(M);
    E_squared += E*E;
    M_squared += M*M;
    //cout << "cycle:" << setw(10) << cycles << setw(10) << "E:" << E << endl;
}

    susceptibility = 1/T * (M_squared/mccycles -(M_expectation2/mccycles)*(M_expectation2/mccycles));
    specific_heat = 1/T*(E_squared/mccycles -(E_expectation/mccycles)*(E_expectation/mccycles));
cout << "Number of MC cycles:" << setw(10) << mccycles << endl;
cout << "Most likely state" << endl;
cout << spin_matrix << endl;
cout << "Expectation value of energy:" << setw(10) << E_expectation/mccycles << endl;
cout << "Expectation value of magnetization:" << setw(10) << M_expectation/mccycles << endl;
cout << "Specific heat:" << setw(10) << specific_heat << endl;
cout << "Susceptibilty:" << setw(10) << susceptibility << endl;

    return 0;
}



