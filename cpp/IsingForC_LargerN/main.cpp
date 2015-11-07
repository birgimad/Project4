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

int periodic(int entrance, int pm, int spins)
//Takes care of the periodic boundary condition of lattice
{
    return (entrance + pm + spins) % spins;
}

int initialize(int spins, double temp, mat spin_matrix, int &E, int &M)
{
    E=0; M=0;
    for (int i = 0; i < spins; i++)
    {
        for (int j = 0; j < spins; j++)
        {
            M += spin_matrix(i,j);
            E -= spin_matrix(i,j)
                    *(spin_matrix(i,periodic(j,-1,spins))
                      +spin_matrix(periodic(i,-1,spins),j));
        }
    }
}

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
    int E, M; //initialize energy and magnetization
    double susceptibility, specific_heat;
    mat spin_matrix(n,n);
    spin_matrix.ones();
    initialize(n,T,spin_matrix,E,M);
    double E_expectation = 0, M_expectation = 0, E_squared = 0, M_squared = 0;

    int x[n*n], y[n*n];
    int microstates = pow(2,n*n)+1;
    //Compute w before MC to use the fact that the change of energy only can take 5 different values
    double w[microstates];
    for (int i =0; i < microstates; i++){
        w[i] = 0;
    }
    for (int dE = -8; dE <= 8; dE+=4){
        w[dE+8] = exp(-dE/T);
    }
    int DE;
    srand(time(NULL));
    for (int cycles = 1; cycles <= mccycles; cycles++)
        {
    for (int i=0; i<n*n; i++)
    {
    x[i] = (n-0.000001)*((double) rand() / (RAND_MAX));  //making sure that the row and column number is either 0 or 1 (randomly chosen - almost uniform)
    y[i] = (n-0.000001)*((double) rand() / (RAND_MAX));
    DE = 2*spin_matrix(x[i],y[i])
            *(spin_matrix(x[i],periodic(y[i],-1,n))+spin_matrix(x[i],periodic(y[i],1,n))
            + spin_matrix(periodic(x[i],-1,n),y[i]) + spin_matrix(periodic(x[i],1,n),y[i]));
    if (w[DE+8] >= ((double) rand() / (RAND_MAX)))
    {
        spin_matrix(x[i],y[i]) = -spin_matrix(x[i],y[i]);
        E += DE;
        M += 2*spin_matrix(x[i],y[i]);
    }
    }
    //The computed energies are in the unit of E/J
    //The computed susectibilty is in the unit J*Chi
    //The computed specific heat is in the unit c_v / k_B
        E_expectation += E;
        M_expectation += fabs(M);
        E_squared += E*E;
        M_squared += M*M;
    }
    susceptibility = 1/T * (M_squared/mccycles -(M_expectation/mccycles)*(M_expectation/mccycles));
    specific_heat = 1/(T*T)*(E_squared/mccycles -(E_expectation/mccycles)*(E_expectation/mccycles));
    cout << "Number of MC cycles:" << setw(10) << mccycles << endl;
    //cout << "Most likely state" << endl;
    //cout << spin_matrix << endl;
    cout << "Expectation value of energy:" << setw(10) << E_expectation/mccycles << endl;
    cout << "Expectation value of magnetization:" << setw(10) << M_expectation/mccycles << endl;
    cout << "Specific heat:" << setw(10) << specific_heat << endl;
    cout << "Susceptibilty:" << setw(10) << susceptibility << endl;

    ofstream myfile ("IsingForC_LargerN_2.txt");
        if (myfile.is_open())
        {
            myfile << "Expectation value of energy and magnetization and specific heat and susceptibility computed by generalized Ising method using Metropolis algorithm:" <<endl;
            myfile << "n = " << n << endl;
            myfile << "T = " << T << endl;
            myfile << "Number of MC cycles:" << setw(10) << mccycles << endl;
            //myfile << "Most likely state" << endl;
            //myfile << spin_matrix << endl;
            myfile << "Expectation value of energy:" << setw(10) << E_expectation/mccycles << endl;
            myfile << "Expectation value of magnetization:" << setw(10) << M_expectation/mccycles << endl;
            myfile << "Specific heat:" << setw(10) << specific_heat << endl;
            myfile << "Susceptibilty:" << setw(10) << susceptibility << endl;

        }

        return 0;
    }






