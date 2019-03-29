#include "pch.h"
#include "ThreadInfo.h"

ThreadInfo::ThreadInfo(int ThreadNumber, int StartLine, int FinalLine, std::string FilePath, std::string WordToFind)
{
	this->ThreadNumber = ThreadNumber;
	this->StartLine = StartLine;
	this->FinalLine = FinalLine;
	this->FilePath = FilePath;
	this->WordToFind = WordToFind;
	MatchInfoQueue = std::queue<MatchInfo>();
}

ThreadInfo::ThreadInfo(int ThreadNumber, int StartLine, int FinalLine, std::string FilePath, std::string WordToFind, std::vector<char> & AllowedCharacterList)
{
	ThreadInfo(ThreadNumber, StartLine, FinalLine, FilePath, WordToFind);
	this->AllowedCharacterList = AllowedCharacterList;
}

ThreadInfo::ThreadInfo()
{
}


ThreadInfo::~ThreadInfo()
{
}

int ThreadInfo::getStartLine()
{
	return StartLine;
}

int ThreadInfo::getFinalLine()
{
	return FinalLine;
}

std::string ThreadInfo::getFilePath()
{
	return FilePath;
}

std::string ThreadInfo::getWordToFind()
{
	return WordToFind;
}

void ThreadInfo::printInfo()
{
	std::string ThreadInfoString= "[Thread " + std::to_string(ThreadNumber) + " start: " + std::to_string(StartLine) + " -  end: " + std::to_string(FinalLine) + "] ";

	while (!MatchInfoQueue.empty())
	{
		std::cout << ThreadInfoString << MatchInfoQueue.front().getString();
	}
}

const bool ThreadInfo::isAAllowedCharacter(char charToCheck)
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
