#pragma once

#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include "MatchInfo.h"

class ThreadInfo
{
public:
	ThreadInfo(int ThreadNumber, int StartLine, int FinalLine, std::string FilePath, std::string WordToFind);
	ThreadInfo(int ThreadNumber, int StartLine, int FinalLine, std::string FilePath, std::string WordToFind, std::vector<char> & AllowedCharacterList);
	ThreadInfo();
	~ThreadInfo();

	int getStartLine();
	int getFinalLine();
	std::string getFilePath();
	std::string getWordToFind();

	void printInfo();

	const bool isAAllowedCharacter(char charToCheck);
	void addToMatchs(MatchInfo Match);

private:
	int ThreadNumber;
	int StartLine;
	int FinalLine;
	std::string FilePath;
	std::string WordToFind;
	std::vector<char> AllowedCharacterList;
	std::queue<MatchInfo> MatchInfoQueue;

};

