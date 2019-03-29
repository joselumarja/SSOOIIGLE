#include "pch.h"
#include "Utilities.h"
#include <fstream>
#include <iostream>

int countFileLines(std::string FilePath)
{
	std::ifstream File;
	int LinesCounter = 0;
	std::string Buffer;

	File.open(FilePath, std::ios::in);
	
	if (!File.is_open())
	{
		std::cerr << "Fail opening the file: " << FilePath << std::endl;
		exit(EXIT_FAILURE);
	}

	while (!File.eof())
	{
		File.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		LinesCounter++;
	}

	File.close();

	return LinesCounter;
}

void seekFileLine(std::ifstream & File, unsigned int LineNumber)
{
	for (unsigned int i = 0; i < LineNumber; i++)
	{
		File.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}
