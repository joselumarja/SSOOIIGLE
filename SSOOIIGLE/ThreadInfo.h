#pragma once

#include <queue>
#include <vector>
#include "MatchInfo.h"

class ThreadInfo
{
public:
	ThreadInfo(int StartLine, int FinalLine);
	ThreadInfo(int StartLine, int FinalLine, std::vector<char> & AllowedCharacterList);
	ThreadInfo();
	~ThreadInfo();

	int getStartLine();
	int getFinalLine();
	const bool isAAllowedCharacter(char charToCheck);
	void addToMatchs(MatchInfo Match);

private:
	int StartLine;
	int FinalLine;
	std::vector<char> AllowedCharacterList;
	std::queue<MatchInfo> MatchInfoQueue;

};

