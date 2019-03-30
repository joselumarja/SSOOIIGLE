// SSOOIIGLE.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "pch.h"
#include "Utilities.h"
#include "MatchInfo.h"
#include "ThreadInfo.h"
#include "SearchingThread.h"
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <fstream>
#include <mutex>

void parseArguments(int argc, char *argv[], std::string &FilePath, std::string &WordToFind, unsigned int &NumberOfThreads);
void checkArgumentValues(unsigned int &NumberOfThreads, unsigned int &NumberOfLines, std::string FilePath);

void initializeDataStructures(std::vector<ThreadInfo>& ThreadInfoVector, unsigned int NumberOfThreads, unsigned int NumberOfLines, std::string FilePath, std::string WordToFind);

void launchThreads(int NumberOfThreads, std::vector<std::thread>& ThreadVector, std::vector<ThreadInfo>& ThreadInfoVector, std::shared_ptr<std::mutex> MutexPointer);
void waitThreadFinalization(std::vector<std::thread> & ThreadVector);

void printSearchResult(std::vector<ThreadInfo> & ThreadInfoVector);

std::vector<char> AllowedCharacterList = { '!','¡','¿','?',',',';','.','(',')','{', '}','[',']','-','_','¨','"','+','*','$','%','&' };

int main(int argc, char *argv[])
{
	std::string FilePath;
	std::string WordToFind;
	unsigned int NumberOfThreads;
	unsigned int NumberOfLines;

	std::mutex Mutex;
	std::shared_ptr<std::mutex> MutexPointer(&Mutex);

	std::vector<std::thread> ThreadVector = std::vector<std::thread>();
	std::vector<ThreadInfo> ThreadInfoVector = std::vector<ThreadInfo>();

	parseArguments(argc, argv, FilePath, WordToFind, NumberOfThreads);
	checkArgumentValues(NumberOfThreads, NumberOfLines, FilePath);

	initializeDataStructures(ThreadInfoVector, NumberOfThreads, NumberOfLines, FilePath, WordToFind);

	launchThreads(NumberOfThreads, ThreadVector, ThreadInfoVector,MutexPointer);
	waitThreadFinalization(ThreadVector);
	
	printSearchResult(ThreadInfoVector);

	return EXIT_SUCCESS;
}

void parseArguments(int argc, char *argv[], std::string &FilePath, std::string &WordToFind, unsigned int &NumberOfThreads)
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

void checkArgumentValues(unsigned int & NumberOfThreads, unsigned int & NumberOfLines, std::string FilePath)
{

	unsigned int MaxThreadNumber = std::thread::hardware_concurrency();
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

void initializeDataStructures(std::vector<ThreadInfo> & ThreadInfoVector, unsigned int NumberOfThreads, unsigned int NumberOfLines, std::string FilePath, std::string WordToFind)
{
	unsigned int i;
	unsigned int LowerLimit = 0;
	unsigned int Increment = NumberOfLines / NumberOfThreads;
	unsigned int UpperLimit = Increment - 1;

	for (i = 0; i < NumberOfThreads - 1; i++)
	{
		ThreadInfoVector.emplace_back(i, LowerLimit, UpperLimit, FilePath, WordToFind, AllowedCharacterList);
		LowerLimit += Increment;
		UpperLimit = LowerLimit + Increment - 1;
	}

	UpperLimit = NumberOfLines - 1;
	ThreadInfoVector.emplace_back(i,LowerLimit, UpperLimit, FilePath, WordToFind, AllowedCharacterList);
}

void launchThreads(int NumberOfThreads, std::vector<std::thread>& ThreadVector, std::vector<ThreadInfo>& ThreadInfoVector, std::shared_ptr<std::mutex> MutexPointer)
{
	std::cout << "Creating " << NumberOfThreads << " threads" << std::endl;
	for (int i = 0; i < NumberOfThreads; i++)
	{
		ThreadVector.push_back(std::thread(SearchingThread(&ThreadInfoVector[i], MutexPointer)));
	}
}

void waitThreadFinalization(std::vector<std::thread> & ThreadVector)
{
	for (unsigned int i = 0; i < ThreadVector.size(); i++)
	{
		if (ThreadVector.at(i).joinable())
		{
			ThreadVector.at(i).join();
		}
	}
}

void printSearchResult(std::vector<ThreadInfo> & ThreadInfoVector)
{
	std::cout << "Searching results: " << std::endl;
	for (ThreadInfo ThrInfo : ThreadInfoVector)
	{
		ThrInfo.printInfo();
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
