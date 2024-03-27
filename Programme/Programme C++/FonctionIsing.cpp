#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

vector<double> LectureVariables(int A)
{
	vector<double> Variables(A); //Création vecteur
	fstream f;
	f.open("variables.txt", ios::in);
	for(int i=0; i<Variables.size(); i++)
		{
			f>>Variables[i]; //Ajoute variables dans le vecteur 
		}
	f.close( );
	return Variables; 
}

vector< vector<int> > CreationGrille(int A)
{
	vector<int> V(A); //Création vecteur 
	vector< vector<int>  > Grille(A, V); //Création d'un vecteur de vecteur = Matrice. Fonctionne comme les tableaux mais en version dynamique 
	
	for(int i=0; i<A; i++) //Parcours colonnes
	 {
	 	for(int j=0; j<A; j++) //Parcours lignes 
	 	{
	 		double x = rand()/double(RAND_MAX)-0.5; //Génération nombre entre -0.5 et 0.5 
	 		if(x<0)
		 		Grille[i][j]=-1; 
			else
		 		Grille[i][j]=+1; 
		}
	}
		return Grille;	
}

int magnetisation(const vector< vector<int>  > & A)	
{	
	int somme=0;
	for(int i=0; i<A.size();i++)
	{
		for(int j=0; j<A.size();j++)
		{
			somme=somme+A[i][j];
		}
	}
	return somme; 
}

int PremierVoisin(const vector< vector<int>  > & A, int xi,int yi) 
{			
	int Nord= 0;
	int Est = 0; 
	int Sud = 0;
	int Ouest = 0; 
	int N= A.size();
	
	Est=A[(xi+1)%N][yi];
	Ouest=A[(xi-1+N)%N][yi];
	Nord=A[xi][(yi+1)%N];
	Sud=A[xi][(yi-1+N)%N];

	//cout<<"Voisin : "<<Sud<<" ; "<<Nord<<" ; "<<Est<<" ;" <<Ouest<<endl;
	int SPV= Sud + Nord + Est + Ouest;
	return SPV;
}

void AffichageGrille(vector< vector<int>  > & Grille, double T)
{
	fstream f;
	string s = "Grille"+to_string (T)+".txt";
				
	f.open(s, ios::out);	
	for(int i=0; i<Grille.size(); i++)
		{
			for(int j=0; j<Grille.size(); j++)
			{
				f<<i<<" "<<j<<" "<<Grille[i][j]<<endl;
			}
						
		}
	f.close();
}

vector<vector< vector<int>> > CreationGrille3D(int A)
{
	vector<int> V(A); //Création vecteur 
	//vector< vector<int>  > Grille(A, V); //Création d'un vecteur de vecteur = Matrice. Fonctionne comme les tableaux mais en version dynamique 
	vector< vector< vector<int> > > Grille3D(A, vector<vector<int>>(A, V));
	
	for(int i=0; i<A; i++) //Parcours colonnes
	 {
	 	for(int j=0; j<A; j++) //Parcours lignes 
	 	{
	 		for(int z=0; z<A; z++) //Parcours lignes 
	 		{
	 			double x = rand()/double(RAND_MAX)-0.5; //Génération nombre entre -0.5 et 0.5 
	 			if(x<0)
		 			Grille3D[i][j][z]=-1; 
				else
		 			Grille3D[i][j][z]=+1; 
			}
		}
	}
	return Grille3D;	
}	

int magnetisation3D(const vector< vector< vector<int> > > & Grille3D)	
{
	int somme=0;
	for(int i=0; i<Grille3D.size();i++)
	{
		for(int j=0; j<Grille3D.size();j++)
		{
			for(int z=0; z<Grille3D.size()-1;z++)
			{
			somme=somme+Grille3D[i][j][z];
			}
		}
	}	
	return somme; 
}		

void AffichageGrille3D(const vector< vector< vector<int> > > &Grille3D, double T)
{
	fstream f;
	string s = "Grille3D_"+to_string (T)+".txt";
				
	f.open(s, ios::out);	
	for(int i=0; i<Grille3D.size(); i++)
	{
		for(int j=0; j<Grille3D.size(); j++)
		{
			for(int z=0; z<Grille3D.size(); z++)
			{
				f<<i<<" "<<j<<" "<<z<<" "<<Grille3D[i][j][z]<<endl;
			}			
		}
	}
}

int PremierVoisin3D(const vector< vector< vector<int> > > & Grille3D, int xi,int yi, int zi) 
{			
		int Nord= 0;
		int Est = 0; 
		int Sud = 0;
		int Ouest = 0; 
		int Front = 0;
		int Back = 0; 
		int N= Grille3D.size();
		
		Est=Grille3D[(xi+1)%N][yi][zi];
		Ouest=Grille3D[(xi-1+N)%N][yi][zi];
		Nord=Grille3D[xi][(yi+1)%N][zi];
		Sud=Grille3D[xi][(yi-1+N)%N][zi];
		Front=Grille3D[xi][yi][(zi-1+N)%N];
		Back=Grille3D[xi][yi][(zi+1+N)%N];

		//cout<<"Voisin : "<<Sud<<" ; "<<Nord<<" ; "<<Est<<" ;" <<Ouest<<" ; "<<Front<<" ;" <<Back<<endl;
	int SPV= Sud + Nord + Est + Ouest + Front + Back;
	return SPV;
}

void Simulation(double Tmin, double Tmax, double PasTemp, double B, double J, int DimSimu, double Taffi, int iteration, int DimGrille, int affi)
{
	
	double Kb =1.380649e-23;

	double Js=J*1e21; //Affiche mieux pour le txt 
	double Bs=B*1e21; //Idem 
	fstream s;
	fstream f;
	if(DimSimu==2)
	{
		
		
		vector< vector<int> > Grille= CreationGrille(DimGrille); //Creation de la grille 
		//double mag = magnetisation(Grille); //Calcul de la magnétisation initiale 
		//cout<<"MagIni= "<<mag<<endl;
		string w = "Cv_Se_J="+to_string (Js)+"_B="+to_string (Bs)+"_N="+to_string (DimGrille)+".txt";
		string v = "Mag_Me_J="+to_string (Js)+"_B="+to_string (Bs)+"_N="+to_string (DimGrille)+".txt";
				
		s.open(w, ios::out);
		f.open(v, ios::out);

		for(double  T = Tmax; T >= Tmin; T=T-PasTemp)
		{	
			double E=0;
			cout<<"T= "<<T<<endl;
			double Se =E;
			double See=E*E;
			double mag = magnetisation(Grille);
			double Me=mag;
			double Mee=mag*mag;
			
			for(int z=0; z<iteration;z++)
			{
			
				//Site aléatoire sur la grille
				int xi= rand()%Grille.size();
				int yi= rand()%Grille.size();
			
			
				//Calcul de l'energie 
				double DeltaE = 2*Grille[xi][yi]*(B+J*PremierVoisin(Grille,xi,yi));
			
				if(DeltaE<0)
				{
					Grille[xi][yi]=-Grille[xi][yi];   //Reverse le spin
					E= E+ DeltaE;
					mag= mag + 2*Grille[xi][yi];
		
				
				}
				
				else
				{
					double p = (double)rand()/(double)RAND_MAX;   //Génération double entre 0 et 1 	
					if( p< exp(-DeltaE/(Kb*T)))
					{
					
						Grille[xi][yi]=-Grille[xi][yi];
						E= E+ DeltaE;
						mag= mag + 2*Grille[xi][yi];
						
					}
				}
					
				if(T==Taffi and affi==0)
				{
					AffichageGrille(Grille,Taffi);
				}
				Se =Se+ E;
				See =See+ E*E;
				Me= Me + mag;
				Mee = Mee + mag*mag; 				
			}
			Se=Se/iteration; //Moyenne des Se par temperature 
			See=See/iteration; //Moyenne des See par temperature 
			double div=DimGrille*DimGrille;
			double div2=div*div; 
			div *= iteration;
			div2 *= iteration;
			Me=Me/div; //Moyenne des Me par temperature 
			Mee=Mee/div2; //Moyenne des Mee par temperature 
			double Cv=(See-(Se*Se))/((Kb*T)*(Kb*T));
			double Xi=(Mee-(Me*Me))/(Kb*T);
		
			s<<T<<" "<<Cv<<" "<<Se<<endl; 
			f<<T<<" "<<Xi<<" "<<Me<<endl;
		}	
	}
	if(DimSimu==3)
	{
		vector< vector< vector<int>> > Grille3D = CreationGrille3D(DimGrille);
		

		string w = "3DCv_Se_J="+to_string (Js)+"_B="+to_string (Bs)+".txt";
		string v = "3DMag_Me_J="+to_string (Js)+"_B="+to_string (Bs)+".txt";

		s.open(w, ios::out);
		f.open(v, ios::out);
		
		
		for(double  T = Tmax; T >= Tmin; T=T-PasTemp)
		{	
			double E=0;
			cout<<"T= "<<T<<endl;
			double Se =E;
			double See=E*E;
			int mag = magnetisation3D(Grille3D);
			double Me=mag;
			double Mee=mag*mag;
			
			for(int g=0; g<iteration;g++)
			{
				//Site aléatoire sur la grille
				int xi= rand()%Grille3D.size();
				int yi= rand()%Grille3D.size();
				int zi= rand()%Grille3D.size();
				
				//Calcul de l'energie 
				double DeltaE = 2*Grille3D[xi][yi][zi]*(B+J*PremierVoisin3D(Grille3D,xi,yi,zi));
			
				if(DeltaE<0)
				{
					Grille3D[xi][yi][zi]=-Grille3D[xi][yi][zi];   //Reverse le spin
					E= E+ DeltaE;
					mag= mag + 2*Grille3D[xi][yi][zi];
				
				}
				
				else
				{
					double p = (double)rand()/(double)RAND_MAX;   //Génération double entre 0 et 1 	
					
					if( p< exp(-DeltaE/(Kb*T)))
					{
						Grille3D[xi][yi][zi]=-Grille3D[xi][yi][zi];
						E= E+ DeltaE;
						mag= mag + 2*Grille3D[xi][yi][zi];
					}
				}
				Se = Se+ E;
				See = See + E*E;
				Me = Me + mag;
				Mee = Mee + mag*mag; 		
				
				if(T==Taffi and affi==0)
				{
					AffichageGrille3D(Grille3D,Taffi);
				}
						
			}
			Se=Se/iteration;
			See=See/iteration;
			double div3=DimGrille*DimGrille*DimGrille;
			double div4=div3*div3; 
			div3 *= iteration;
			div4 *= iteration;
			Me=Me/div3;
			Mee=Mee/div4; 
		
			double Cv=(See-(Se*Se))/((Kb*T)*(Kb*T));
			double Xi=(Mee-(Me*Me))/(Kb*T);
			s<<T<<" "<<Cv<<" "<<Se<<endl; 
			f<<T<<" "<<Xi<<" "<<Me<<endl;
		

		}	
	
	}
	s.close( ); 
	f.close();
}


