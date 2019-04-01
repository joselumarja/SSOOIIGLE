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
	SearchingThread(ThreadInfo* ThrInfo, std::mutex *Mutex);
	void operator()();
	void initTask();
	~SearchingThread();
private:
	ThreadInfo *ThrInfo;
	std::mutex *Mutex;
	int CurrentLine;

	void createMatch(std::wstring PreviousWord, std::wstring MatchingWord, std::wstring NextWord);
	void analyzeLine(std::wstring Line);
	bool analyzeWord(std::wstring Word);

};

