// SSOOIIGLE.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "pch.h"
#include "Utilities.h"
#include "MatchInfo.h"
#include "ThreadInfo.h"
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <fstream>

void parseArguments(int argc, char *argv[], std::string &FilePath, std::string &WordToFind, int &NumberOfThreads);
void checkArgumentValues(int &NumberOfThreads, int &NumberOfLines, std::string FilePath);

void initializeDataStructures(std::vector<ThreadInfo>& ThreadInfoVector, int NumberOfThreads, int NumberOfLines);

int main(int argc, char *argv[])
{
	std::string FilePath;
	std::string WordToFind;
	int NumberOfThreads;
	int NumberOfLines;

	std::vector<std::thread> ThreadVector;
	std::vector<ThreadInfo> ThreadInfoVector = std::vector<ThreadInfo>();

	parseArguments(argc, argv, FilePath, WordToFind, NumberOfThreads);
	checkArgumentValues(NumberOfThreads, NumberOfLines, FilePath);




	
}

void initializeDataStructures(std::vector<ThreadInfo>& ThreadInfoVector, int NumberOfThreads, int NumberOfLines)
{
	int LowerLimit = 0;
	int Increment = NumberOfLines / NumberOfThreads;
	int UpperLimit = Increment - 1;

	for (int i = 0; i < NumberOfThreads - 1; i++)
	{
		ThreadInfoVector.push_back(ThreadInfo(LowerLimit, UpperLimit));
		LowerLimit += Increment;
		UpperLimit = LowerLimit + Increment - 1;
	}

	UpperLimit = NumberOfLines - 1;
	ThreadInfoVector.push_back(ThreadInfo(LowerLimit, UpperLimit));
}

void launchThreads(int NumberOfThreads, std::vector<std::thread>& ThreadVector, std::vector<ThreadInfo>& ThreadInfoVector)
{
	std::cout << "Creating " << NumberOfThreads << " threads" << std::endl;

}

void parseArguments(int argc, char *argv[], std::string &FilePath, std::string &WordToFind, int &NumberOfThreads)
{
	if (argc != 4)
	{
		std::cerr << "Fail, Wrong Argument Number" << std::endl;
		exit(EXIT_FAILURE);
	}

	FilePath = argv[1];
	WordToFind = argv[2];
	NumberOfThreads = std::atoi(argv[3]);
}

void checkArgumentValues(int & NumberOfThreads, int & NumberOfLines, std::string FilePath)
{

	int MaxThreadNumber = std::thread::hardware_concurrency();
	NumberOfLines = countFileLines(FilePath);

	if (NumberOfLines == 0)
	{
		std::cerr << "The specified file has no lines" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (NumberOfThreads > MaxThreadNumber)
	{
		std::cout << NumberOfThreads << " is greather than the number of cores" << std::endl;
		NumberOfThreads = MaxThreadNumber;
	}

	if (NumberOfLines < NumberOfThreads)
	{
		NumberOfThreads = NumberOfLines;
	}
}


// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
