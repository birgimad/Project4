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
    int n, mccycles;
    double T;
    cout << "Please enter number of spins in each direction:\n>";
    cin >> n;
    cout << "Please enter value of T:\n>";
    cin >> T;
    cout << "Please enter number of MC cycles:\n>";
    cin >> mccycles;
    int E = 0, M = 0, E_squared = 0, M_squared = 0; //initialize energy and magnetization
    double susceptibility, specific_heat;
    mat spin_matrix(n,n);
    spin_matrix(0,0) =-1;
    spin_matrix(0,1) = -1;
    spin_matrix(1,0) = 1;
    spin_matrix(1,1) = 1;
    double E_expectation = 0, M_expectation = 0;

    int x[n], y[n];
    int microstates = pow(2,n*n)+1;
    double w[microstates];
    for (int i =0; i < microstates; i++){
        w[i] = 0;
    }
    for (int dE = -8; dE <= 8; dE+=4){
        w[dE+8] = exp(-dE/T);
    }
    int DE_x, DE_y, DE;
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
    if (w[DE+8] >= ((double) rand() / (RAND_MAX)))
    {
        spin_matrix(x[i],y[i]) = -spin_matrix(x[i],y[i]);
        E += DE;
        M += 2*spin_matrix(x[i],y[i]);
    }
    }
    }
//The computed energies are in the unit of E/J
//The computed susectibilty is in the unit J*Chi
//The computed specific heat is in the unit c_v / k_B
    E_expectation += E;
    M_expectation += M;
    E_squared += E*E;
    M_squared += M*M;
    //cout << "cycle:" << setw(10) << cycles << setw(10) << "E:" << E << endl;
}

    susceptibility = 1/T * (M_squared/mccycles -(M_expectation/mccycles)*(M_expectation/mccycles));
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





