#include "pch.h"
#include "SearchingThread.h"
#include "Utilities.h"
#include <fstream>
#include <iostream>

SearchingThread::SearchingThread()
{
}

void SearchingThread::initTask(std::string FilePath, std::string WordToFind, ThreadInfo & ThrInfo)
{
	std::ifstream File;
	std::string Buffer;
	int Line = ThrInfo.getStartLine();
	int FinalLine = ThrInfo.getFinalLine();

	File.open(FilePath, std::ios::in);

	if (!File.is_open())
	{
		std::cerr << "Fail opening the file: " << FilePath << std::endl;
		exit(EXIT_FAILURE);
	}

	seekFileLine(File, Line);

	while (Line < FinalLine)
	{
		std::getline(File, Buffer);

	}
}


SearchingThread::~SearchingThread()
{
}
