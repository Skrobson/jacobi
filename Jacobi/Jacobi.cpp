#include <iostream>
#include <string>
#include <fstream>

bool input();
bool createAB();
bool calculateJacobi();


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
	input();
	writeMatrix(initialMatrix, initialVector, "initial");
	if (createAB())
	{
		std::cout << "macierz poprawna" << std::endl;
		writeMatrix(alfa,beta,"AB");
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
	std::copy(beta, beta + N, prevX);
	std::copy(beta, beta + N, X);



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