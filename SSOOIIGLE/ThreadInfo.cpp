#include "pch.h"
#include "ThreadInfo.h"

ThreadInfo::ThreadInfo(int StartLine, int FinalLine)
{
	this->StartLine = StartLine;
	this->FinalLine = FinalLine;
	MatchInfoQueue = std::queue<MatchInfo>();
}

ThreadInfo::ThreadInfo(int StartLine, int FinalLine, std::vector<char> & AllowedCharacterList)
{
	ThreadInfo(StartLine, FinalLine);
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

const bool ThreadInfo::isAAllowedCharacter(char charToCheck)
{
	for (int i = 0; i < AllowedCharacterList.size(); i++)
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
