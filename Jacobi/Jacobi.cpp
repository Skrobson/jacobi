#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <conio.h>

bool input();
bool createAB();
bool calculateJacobi();
void output(double* prevX, double* X,int iter);

void analyze( double* X);

std::string inFile;


double ** initialMatrix = nullptr;
double * initialVector = nullptr;

double ** alfa = nullptr;
double * beta = nullptr;

int N = 0;
int MLI = 0;
double epsilon = 0.0f;

//funkcja testowa
//void writeMatrix(double ** m,double* v,std::string title);


int main(int argc, char* argv[])
{
	std::cout.precision(10);
	std::cout.setf(std::ios::scientific, std::ios::floatfield);
	
	if (input())
	{
		//writeMatrix(initialMatrix, initialVector, "initial");
		if (createAB())
		{
			std::cout << "macierz poprawna" << std::endl;
			//writeMatrix(alfa, beta, "AB");
		}

		calculateJacobi();

	}
	if(initialVector)
	delete[]initialVector;
	if (initialMatrix)
	{
		for (int i = 0; i < N; ++i)
		{
			delete[]  initialMatrix[i];
		}
	}
	delete[] initialMatrix;
	if (beta)
		delete[] beta;
	if (alfa)
	{
		for (int i = 0; i < N; ++i)
		{
			delete[]  alfa[i];
		}
	}
	std::cout << "Wcisnij dowolny klawisz";
	_getch();
	return 0;
}



bool input()
{
	//wczytywanie danych od usera
	std::cout << "Podaj N rozmiar maciezry i wektora: ";
	std::cin >> N;

	//tworzenie macierzy i wektora
	initialMatrix = new double *[N];
	for (int i = 0; i < N; ++i)
		initialMatrix[i] = new double[N];
	
	initialVector = new double[N];

	if (!initialMatrix || !initialVector)
		return false;

	// wczytywnanie z pliku
	std::cout << std::endl << "Podaj sciezke do pliku: ";
	std::cin >> inFile;
	std::fstream file(inFile, std::ios::in);
	if (file.good())
	{
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				file >> initialMatrix[i][j];

		for (int i = 0; i < N; ++i)
			file >> initialVector[i];

		file.close();
	}
	else
		return false;

	//epsilon i maksymalna liczba iteracji
	std::cout << std::endl << "Podaj dok³adnosæ epsilon: ";
	std::cin >> epsilon;

	std::cout << std::endl << "Podaj maksymalna liczbe iteracji: ";
	std::cin >> MLI;
	return true;
}

bool createAB()
{
	//sprawdzanie dzielenia przez zero
	for (int i = 0; i < N; ++i)
	{
		if (initialMatrix[i][i] == 0.0f)
		{
			std::cout << std::endl << "Z³a macierz, dzielenie przez zero w " << i << "," << i << std::endl;
			return false;
		}
	}
	//tworzymy macierz Alfa
	alfa = new double *[N];
	for (int i = 0; i < N ; ++i)
	{
		alfa[i] = new double[N];
	}
	//tworzymy wektor Beta
	beta = new double[N];
	//obl alfe
	for(int i=0;i<N;++i)
		for (int j = 0; j < N; ++j)
		{
			if (i == j)
				alfa[i][j] = 0;
			else
				alfa[i][j] = - (initialMatrix[i][j] / initialMatrix[i][i]);
		}
	//obl bete
	for (int i = 0; i < N; ++i)
		 beta[i]= initialVector[i] / initialMatrix[i][i];

	return true;
}

bool calculateJacobi()
{
	
	double* prevX=new double[N];
	double* X=new double[N];
	
	std::copy(beta, beta + N, X);
	int iterrations = 0;
	bool stop=false;
	double norm;
	do{
		norm = 0;
		++iterrations;
		std::copy(X,X + N, prevX);
		
		for (int i = 0; i < N; ++i)
		{
			X[i] = beta[i];
			for (int j = 0; j < N; ++j)
			{
				/*if (i != j) // tego warunku nie jestem pewien
				{
					X[i] += alfa[i][j] * prevX[j];
				}*/
				X[i] += alfa[i][j] * prevX[j];		
			}
			//obliczanie normy
			norm += abs(X[i] - prevX[i]);
		}
		//warunek stopu
		norm /= N;	
	} while (iterrations < MLI && norm >= epsilon);
	//test
	/*std::cout << "iteracja: " << iterrations<<std::endl;
	std::cout << "norm: " << norm << std::endl;
	for (int i = 0; i < N; ++i)
		std::cout << prevX[i] << "	" << X[i] << std::endl;*/
	output(prevX, X, iterrations);
	analyze( X);
	return true;
}

void output(double* prevX, double* X,int iter)
{
	std::string outFile;
	int pos=inFile.find_last_of('.');
	outFile = inFile.substr(0,pos+1);
	outFile += "raport.txt";
	std::fstream file(outFile, std::ios::out | std::ios::trunc);
	file.precision(10);
	file.setf(std::ios::scientific, std::ios::floatfield);
	file << "poczatkowy uklad" << std::endl;
	for (int i = 0; i < N; ++i)
	{
		file << "| ";
		for (int j = 0; j < N; ++j)
		{
			file << initialMatrix[i][j] << "  ";
		}
		file << " |  | " << initialVector[i] << std::endl;
	}
	file << "----------------" << std::endl;
	file << "Alfa i Beta" << std::endl;
	for (int i = 0; i < N; ++i)
	{
		file << "| ";
		for (int j = 0; j < N; ++j)
		{
			file << alfa[i][j] << "  ";
		}
		file << " |  | " << beta[i] << std::endl;
	}
	file << "----------------" << std::endl;
	file << "wektor przedostatnio wykonanej iteracji" << std::endl;
	for (int i = 0; i < N; ++i)
	{
		file << prevX[i]<<"	" ;
	}
	file << std::endl;
	file << "wektor ostatnio wykonanej iteracji" << std::endl;
	for (int i = 0; i < N; ++i)
	{
		file << X[i]<<"	";
	}
	file << std::endl;
	file <<"liczba iteracji:"<<iter<< std::endl;

	file.close();
}

void analyze( double* X)
{
	std::string outFile;
	int pos = inFile.find_last_of('.');
	outFile = inFile.substr(0, pos + 1);
	outFile += "analiza.txt";
	std::fstream file(outFile, std::ios::out | std::ios::trunc);
	file.precision(10);
	file.setf(std::ios::scientific, std::ios::floatfield);

	//zbieznosc
	std::vector<double> tempVector;
	double a(0);
	for (int i = 0; i < N; ++i)
	{
		a = 0;
		for (int j = 0; j < N; ++j)
		{
			a += abs(alfa[i][j]);
		}
		tempVector.push_back(a);
	}
	auto max = std::max_element(tempVector.begin(), tempVector.end());
	if (*max < 1)
		file << "Uklad zbiezny" << std::endl;
	else
	{
		tempVector.clear();
	for (int j = 0; j < N; ++j)
	{
		a = 0;
		for (int i = 0; i < N; ++i)
		{
			a += alfa[i][j];
		}
		tempVector.push_back(a);
	}
	auto max = std::max_element(tempVector.begin(), tempVector.end());
	if (*max < 1)
		file << "Uklad  zbiezny" << std::endl;
		else 
		{
			a = 0;
			for (int i = 0; i < N; ++i)
			{
				for (int j = 0; j < N; ++j)
				{
					a += pow(alfa[i][j], 2);
				}
				a = sqrt(a);
				if(a<1)
					file << "Uklad zbiezny" << std::endl;
				
				else
					file << "Uklad nie jest zbiezny" << std::endl;		
			}
		}
	}	
	//blad bezwzgledny
	double precise[] = { 1,1,0,-1,-1 };
	std::vector<double> dVector;
	for (int i = 0; i < N; ++i)
		dVector.push_back(abs(precise[i] - X[i]));
	
	file << "blad bezwzgledny: "<<std::endl;
	for (auto deltaX : dVector)
	{
		file << deltaX<<"	"<<std::endl;
	}
	file.close();
}

/*
void writeMatrix(double** m,double* v,std::string title)
{
	std::cout << title << std::endl;
	for (int i = 0; i < N; ++i)
	{
		std::cout << "| ";
		for (int j = 0; j < N; ++j)
		{
			std::cout << m[i][j]<<"  ";
		}
		std::cout << " |  | " << v[i]<<std::endl;
	}
	std::cout << "----------------"<<std::endl;

}*/