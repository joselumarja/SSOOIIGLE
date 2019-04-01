#include "pch.h"
#include "ThreadInfo.h"
#include <Windows.h>

ThreadInfo::ThreadInfo(unsigned int ThreadNumbe, unsigned int StartLine, unsigned int FinalLine, std::string FilePath, std::wstring WordToFind)
{
	ThreadNumber = ThreadNumbe;
	this->StartLine = StartLine;
	this->FinalLine = FinalLine;
	this->FilePath = FilePath;
	WordToFind = WordToFind;
	MatchInfoQueue = std::queue<MatchInfo>();
}

ThreadInfo::ThreadInfo(unsigned int ThreadNumber, unsigned int StartLine, unsigned int FinalLine, std::string FilePath, std::wstring WordToFind, std::vector<wchar_t> & AllowedCharacterList)
{
	this->ThreadNumber = ThreadNumber;
	this->StartLine = StartLine;
	this->FinalLine = FinalLine;
	this->FilePath = FilePath;
	this->WordToFind = WordToFind;
	MatchInfoQueue = std::queue<MatchInfo>();
	this->AllowedCharacterList = AllowedCharacterList;
}

ThreadInfo::ThreadInfo()
{
}

void ThreadInfo::operator=(ThreadInfo & Thr)
{
	this->ThreadNumber = Thr.ThreadNumber;
	this->StartLine = Thr.StartLine;
	this->FinalLine = Thr.FinalLine;
	this->FilePath = Thr.FilePath;
	this->WordToFind = Thr.WordToFind;
	this->AllowedCharacterList = AllowedCharacterList;
	this->MatchInfoQueue = Thr.MatchInfoQueue;
}

ThreadInfo::~ThreadInfo()
{
}

unsigned int ThreadInfo::getStartLine()
{
	return StartLine;
}

unsigned int ThreadInfo::getFinalLine()
{
	return FinalLine;
}

std::string ThreadInfo::getFilePath()
{
	return FilePath;
}

unsigned int ThreadInfo::getMatchsSize()
{
	return (unsigned int) MatchInfoQueue.size();
}

void ThreadInfo::printInfo()
{
	std::string Temp, ThreadInfoString= "[Thread " + std::to_string(ThreadNumber)  + " start: " + std::to_string(StartLine) + " -  end: " + std::to_string(FinalLine) + "] ";
	
	while (!MatchInfoQueue.empty())
	{
		std::wstring ResultString(MatchInfoQueue.front().getString());
		Temp = std::string(ResultString.begin(), ResultString.end());
		std::cout << "\t"<< ThreadInfoString <<Temp << "\n";
		MatchInfoQueue.pop();
	}
}

const bool ThreadInfo::isAAllowedCharacter(wchar_t charToCheck)
{
	for (unsigned int i = 0; i < AllowedCharacterList.size(); i++)
	{
		if (charToCheck == AllowedCharacterList.at(i))
		{
			return true;
		}
	}
	return false;
}

void ThreadInfo::addToMatchs(MatchInfo Match)
{
	MatchInfoQueue.push(Match);
}
