#include <iostream>
#include <string>
#include <fstream>

bool input(double** &matrix, double* &vector, int& N, double& epsilon, int& MLI);

bool createAB(double** &matrix, double* &vector, int N);

void writeMatrix(double** iMatrix,double* iVector, double** alfa, double* beta, int N);

int main(int argc, char* argv[])
{
	double **matrix= nullptr;
	double *vector=nullptr;

	double epsilon;
	int N, MLI;

	input(matrix, vector, N, epsilon, MLI);
	 
	//zapisujemy wejsciowy uklad rownan dla raportu koncowego
	 double** initialMatrix = matrix;
	 double* initialVector = vector;


	if (createAB(matrix, vector, N))
	{
		std::cout << "macierz poprawna" << std::endl;
		writeMatrix(initialMatrix, initialVector, matrix, vector, N);
	}

	if(vector)
	delete[]vector;
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



bool input(double ** &matrix, double* &vector, int& N, double& epsilon, int& MLI)
{
	//wczytywanie danych od usera
	std::cout << "Podaj N rozmiar maciezry i wektora: ";
	std::cin >> N;

	//tworzenie macierzy i wektora
	matrix = new double *[N];
	for (int i = 0; i < N; ++i)
		matrix[i] = new double[N];
	
	vector = new double[N];

	if (!matrix || !vector)
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
				file >> matrix[i][j];

		for (int i = 0; i < N; ++i)
			file >> vector[i];

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

bool createAB(double** &matrix, double* &vector, int N)
{
	//sprawdzanie dzielenia przez zero
	for (int i = 0; i < N; ++i)
	{
		if (matrix[i][i] == 0.0f)
		{
			std::cout << std::endl << "Z³a macierz, dzielenie przez zero w " << i << "," << i << std::endl;
			return false;
		}
	}

	//tworzymy macierz Alfa
	double ** alfa = new double *[N];
	for (int i = 0; i < N ; ++i)
	{
		alfa[i] = new double[N + 1];
	}
	//tworzymy wektor Beta
	double *beta = new double[N];
	//obl alfe
	for(int i=0;i<N;++i)
		for (int j = 0; j < N; ++j)
		{
			if (i == j)
				alfa[i][j] = 0;
			else
				alfa[i][j] = - (matrix[i][j] / matrix[i][i]);
		}
	//obl bete
	for (int i = 0; i < N; ++i)
		 beta[i]= vector[i] / matrix[i][i];

	//zamieniamy otrzymane matrix i vector na nowo wyliczone Alfe i Bete
	vector = beta;
	matrix = alfa;

	return true;
}




void writeMatrix( double** iMatrix, double* iVector, double** alfa, double* beta, int N)
{
	for (int i = 0; i < N; ++i)
	{
		std::cout << "| ";
		for (int j = 0; j < N; ++j)
		{
			std::cout << iMatrix[i][j]<<"  ";
		}
		std::cout << " |  | " << iVector[i]<<std::endl;
	}
	std::cout << "----------------"<<std::endl;
	for (int i = 0; i < N; ++i)
	{
		std::cout << "| ";
		for (int j = 0; j < N; ++j)
		{
			std::cout << alfa[i][j] << "  ";
		}
		std::cout << " |  | " <<beta[i]<<std::endl;
	}
}