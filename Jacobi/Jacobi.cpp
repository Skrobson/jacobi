#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>

bool input();
bool createAB();
bool calculateJacobi();

bool analyze();


double ** initialMatrix = nullptr;
double * initialVector = nullptr;

double ** alfa = nullptr;
double * beta = nullptr;

int N = 0;
int MLI = 0;
double epsilon = 0.0f;

//funkcja testowa
void writeMatrix(double ** m,double* v,std::string title);


int main(int argc, char* argv[])
{
	if (input())
	{
		writeMatrix(initialMatrix, initialVector, "initial");
		if (createAB())
		{
			std::cout << "macierz poprawna" << std::endl;
			writeMatrix(alfa, beta, "AB");
		}

		calculateJacobi();

	}
//	if()
//	delete[]vector;
	//if (matrix)
	//for (int i = 0; i < N; ++i)
//	{
//		delete[] *matrix;
//	}
//	delete[] matrix;
	char c;
		std::cin >> c;
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
	std::string filename;
	std::cin >> filename;
	std::fstream file(filename, std::ios::in);
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
	std::cout << std::endl << "Podaj dok�adnos� epsilon: ";
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
			std::cout << std::endl << "Z�a macierz, dzielenie przez zero w " << i << "," << i << std::endl;
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
	do
	{
		norm = 0;
		++iterrations;
		std::copy(X,X + N, prevX);
		
		for (int i = 0; i < N; ++i)
		{
			X[i] = beta[i];
			for (int j = 0; j < N; ++j)
			{
				if (i != j) // tego warunku nie jestem pewien
				{
					X[i] += alfa[i][j] * prevX[j];
				}
				
				//std::cout << X[i] << "=" << alfa[i][j] << "*" << prevX[j]<<std::endl;
			}
			//obliczanie norm
			norm += abs(X[i] - prevX[i]);
			
		}
		//test
		//std::cout << "iteracja: " << iterrations<<std::endl;
		//for (int i = 0; i < N; ++i)
		//	std::cout << prevX[i] << "	" << X[i] << std::endl;

		//warunek stopu
		norm /= N;
		//std::cout <<"norma: "<< norm << std::endl;
		//std::cout <<"epsilon: "<< epsilon << std::endl;
	} while (iterrations < MLI && norm >= epsilon);
	//test
	std::cout << "iteracja: " << iterrations<<std::endl;
	for (int i = 0; i < N; ++i)
		std::cout << prevX[i] << "	" << X[i] << std::endl;
	
	return false;
}

bool analyze()
{
	double a1;
	return false;
}


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

}