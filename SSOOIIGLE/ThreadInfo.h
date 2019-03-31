#pragma once

#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include "MatchInfo.h"

class ThreadInfo
{
public:
	ThreadInfo(unsigned int ThreadNumber,unsigned int StartLine,unsigned int FinalLine, std::string FilePath, std::string WordToFind);
	ThreadInfo(unsigned int ThreadNumber,unsigned int StartLine, unsigned int FinalLine, std::string FilePath, std::string WordToFind, std::vector<char> & AllowedCharacterList);
	ThreadInfo();
	~ThreadInfo();
	ThreadInfo(const ThreadInfo&) = default;

	unsigned int getStartLine();
	unsigned int getFinalLine();
	std::string getFilePath();
	inline std::string getWordToFind() { return WordToFind; }
	unsigned int getMatchsSize();

	void printInfo();
	void operator =(ThreadInfo &Thr);
	const bool isAAllowedCharacter(char charToCheck);
	void addToMatchs(MatchInfo Match);

private:
	unsigned int ThreadNumber;
	unsigned int StartLine;
	unsigned int FinalLine;
	std::string FilePath;
	std::string WordToFind;
	std::vector<char> AllowedCharacterList;
	std::queue<MatchInfo> MatchInfoQueue;

};

