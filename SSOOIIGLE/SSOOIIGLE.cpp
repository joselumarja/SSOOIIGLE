// SSOOIIGLE.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "pch.h"
#include "Utilities.h"
#include "MatchInfo.h"
#include "ThreadInfo.h"
#include "SearchingThread.h"
#include "PrintColorText.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <fstream>
#include <io.h>
#include <locale>
#include <fcntl.h>
#include <mutex>

void printUsage();
void parseArguments(int argc, char *argv[], std::string &FilePath, std::wstring &WordToFind, unsigned int &NumberOfThreads);
void checkArgumentValues(unsigned int &NumberOfThreads, unsigned int &NumberOfLines, std::string FilePath);

void initializeDataStructures(std::vector<ThreadInfo>& ThreadInfoVector, unsigned int NumberOfThreads, unsigned int NumberOfLines, std::string FilePath, std::wstring WordToFind);

void launchThreads(int NumberOfThreads, std::vector<std::thread>& ThreadVector, std::vector<ThreadInfo>& ThreadInfoVector);
void waitThreadFinalization(std::vector<std::thread> & ThreadVector);

void printSearchResult(std::vector<ThreadInfo> & ThreadInfoVector, float SearchTime);
unsigned int calcTotalMatchs(std::vector<ThreadInfo> & ThreadInfoVector);

 /*Vector of characters that are allowed in the word we are looking for*/
std::vector<wchar_t> AllowedCharacterList = { L'!',L'¡',L'¿',L'?',L',',L';',L'.',L'(',L')',L'{', L'}',L'[',L']',L'-',L'_',L'¨',L'"',L'+',L'*',L'$',L'%',L'&' };

/*traffic light to avoid collisions in the writing of matches found*/
std::mutex Mutex;

int main(int argc, char *argv[])
{

	setlocale(LC_ALL, "");

	clock_t Start, End;
	Start = clock();
	
	std::string FilePath;
	std::wstring WordToFind;
	unsigned int NumberOfThreads;
	unsigned int NumberOfLines;

	std::vector<std::thread> ThreadVector = std::vector<std::thread>();
	std::vector<ThreadInfo> ThreadInfoVector = std::vector<ThreadInfo>();

	parseArguments(argc, argv, FilePath, WordToFind, NumberOfThreads);
	checkArgumentValues(NumberOfThreads, NumberOfLines, FilePath);

	initializeDataStructures(ThreadInfoVector, NumberOfThreads, NumberOfLines, FilePath, WordToFind);

	launchThreads(NumberOfThreads, ThreadVector, ThreadInfoVector);

	std::cout << "\nSearching: \"" + std::string(WordToFind.begin(),WordToFind.end()) + "\" in \"" + FilePath + "\"\n";

	waitThreadFinalization(ThreadVector);
	
	End = clock();
	float SearchTime = (float) (End - Start) / CLK_TCK;

	printSearchResult(ThreadInfoVector, SearchTime);

	return EXIT_SUCCESS;
}

void printUsage()
{
	std::cout << "<Program Path> <File Target Path> <Word To Find In File> <Nº Of Threads To Launch>" << std::endl;
}

void parseArguments(int argc, char *argv[], std::string &FilePath, std::wstring &WordToFind, unsigned int &NumberOfThreads)
{
	if (argc != 4)
	{
		printErrorColorText("Fail, Wrong Argument Number",ColorText::RedTextColor);
		printUsage();
		exit(EXIT_FAILURE);
	}

	FilePath = argv[1];
	std::string Temp = argv[2];
	WordToFind = std::wstring(Temp.begin(),Temp.end());
	NumberOfThreads = std::atoi(argv[3]);
}

void checkArgumentValues(unsigned int & NumberOfThreads, unsigned int & NumberOfLines, std::string FilePath)
{

	unsigned int MaxThreadNumber = std::thread::hardware_concurrency();
	NumberOfLines = countFileLines(FilePath);

	if (NumberOfLines == 0)
	{
		printErrorColorText("The specified file is empty", ColorText::RedTextColor);
		printUsage();
		exit(EXIT_FAILURE);
	}

	if (NumberOfThreads > MaxThreadNumber)
	{
		printColorText(std::to_string(NumberOfThreads)+" is greather than the number of cores", ColorText::YellowTextColor);
		NumberOfThreads = MaxThreadNumber;
	}

	if (NumberOfLines < NumberOfThreads)
	{
		NumberOfThreads = NumberOfLines;
	}
}

void initializeDataStructures(std::vector<ThreadInfo> & ThreadInfoVector, unsigned int NumberOfThreads, unsigned int NumberOfLines, std::string FilePath, std::wstring WordToFind)
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

void launchThreads(int NumberOfThreads, std::vector<std::thread>& ThreadVector, std::vector<ThreadInfo>& ThreadInfoVector)
{
	printColorText("Creating " + std::to_string(NumberOfThreads) +" threads" , ColorText::GreenTextColor);

	for (int i = 0; i < NumberOfThreads; i++)
	{
		ThreadVector.push_back(std::thread(SearchingThread(&ThreadInfoVector[i], &Mutex)));
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

void printSearchResult(std::vector<ThreadInfo> & ThreadInfoVector, float SearchTime)
{
	std::cout << "\n\nSearching results: \n\n\tSearch Time: "<<std::to_string(SearchTime)<<"\n\tMatchs Finded: "<<std::to_string(calcTotalMatchs(ThreadInfoVector)) << std::endl;
	for (ThreadInfo ThrInfo : ThreadInfoVector)
	{
		ThrInfo.printInfo();
	}
}

unsigned int calcTotalMatchs(std::vector<ThreadInfo> & ThreadInfoVector)
{
	unsigned int TotalMatchs = 0;

	for (ThreadInfo ThrInfo : ThreadInfoVector)
	{
		TotalMatchs += ThrInfo.getMatchsSize();
	}

	return TotalMatchs;
}
// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
