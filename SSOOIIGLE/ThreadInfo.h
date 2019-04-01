#pragma once

#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include "MatchInfo.h"

class ThreadInfo
{
public:
	ThreadInfo(unsigned int ThreadNumber,unsigned int StartLine,unsigned int FinalLine, std::string FilePath, std::wstring WordToFind);
	ThreadInfo(unsigned int ThreadNumber,unsigned int StartLine, unsigned int FinalLine, std::string FilePath, std::wstring WordToFind, std::vector<wchar_t> & AllowedCharacterList);
	ThreadInfo();
	~ThreadInfo();
	ThreadInfo(const ThreadInfo&) = default;

	unsigned int getStartLine();
	unsigned int getFinalLine();
	std::string getFilePath();
	inline std::wstring getWordToFind() { return WordToFind; }
	unsigned int getMatchsSize();

	void printInfo();
	void operator =(ThreadInfo &Thr);
	const bool isAAllowedCharacter(wchar_t charToCheck);
	void addToMatchs(MatchInfo Match);

private:
	unsigned int ThreadNumber;
	unsigned int StartLine;
	unsigned int FinalLine;
	std::string FilePath;
	std::wstring WordToFind;
	std::vector<wchar_t> AllowedCharacterList;
	std::queue<MatchInfo> MatchInfoQueue;

};

