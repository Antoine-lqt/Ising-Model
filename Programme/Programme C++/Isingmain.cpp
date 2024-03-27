#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>   // Ajoute espace lors de l'affichage texte 
#include "Ising.h"

using namespace std;

int main()
{
	
	srand((unsigned) time(NULL));
	int NbVar = 12;      // Nombre de variables 
	
	vector<double> Variables = LectureVariables(NbVar);
	
	//Initialisation des variables 
	int DimGrille = Variables[0];
	double Tmin = Variables[1];
	double Tmax = Variables[2];
	double PasTemp= Variables[3];
	double J = Variables[4];
	double B = Variables[5];
	//double mu = Variables[6];
	double Kb = Variables[7]; 
	int DimSimu= Variables[8];
	int Affi = Variables[9];
	double Taffi = Variables[10];
	int iteration = Variables[11];
	
	cout<<"Tc="<<2.0*J/Kb/asinh(1)<<endl;
	
	Simulation(Tmin, Tmax, PasTemp, B, J, DimSimu, Taffi, iteration, DimGrille, Affi);
return 0;
}
