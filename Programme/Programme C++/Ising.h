#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

vector<double> LectureVariables(int A);
void Simulation(double Tmin, double Tmax, double PasTemp, double B, double J, int DimSimu, double Taffi, int iteration, int DimGrille, int affi);
vector< vector<int> > CreationGrille(int A);
int magnetisation(const vector< vector<int>  > & A);
int PremierVoisin(const vector< vector<int>  > & A, int xi,int yi);
void AffichageGrille(vector< vector<int>  > & Grille, double T);
vector<vector< vector<int>> > CreationGrille3D(int A);
int magnetisation3D(const vector< vector< vector<int> > > & Grille3D);
void AffichageGrille3D(const vector< vector< vector<int> > > &Grille3D, double T);
int PremierVoisin3D(const vector< vector< vector<int> > > & Grille3D, int xi,int yi, int zi) ;
