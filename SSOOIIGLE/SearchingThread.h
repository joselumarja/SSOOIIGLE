#pragma once

#include <string>
#include <shared_mutex>
#include "ThreadInfo.h"

enum class SearchingState
{
	AllowedCharacter,
	ComparingWords,
	PatternFinded,
	WrongWord
};

class SearchingThread
{
public:
	SearchingThread(ThreadInfo &ThrInfo, std::shared_ptr<std::mutex> &MutexPointer);
	void operator()();
	void initTask();
	~SearchingThread();
private:
	ThreadInfo ThrInfo;
	std::shared_ptr<std::mutex> MutexPointer;
	int CurrentLine;

	void createMatch(std::string PreviousWord, std::string MatchingWord, std::string NextWord);
	void analyzeLine(std::string Line);
	bool analyzeWord(std::string Word);

};

