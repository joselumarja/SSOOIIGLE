#include "pch.h"
#include "SearchingThread.h"
#include "Utilities.h"
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <locale>
#include <codecvt>

SearchingThread::SearchingThread(ThreadInfo* ThrInfo, std::mutex *Mutex)
{	
	this->ThrInfo = ThrInfo;
	this->Mutex = Mutex;
	CurrentLine = -1;
}

void SearchingThread::operator()()
{
	initTask();
}

void SearchingThread::initTask()
{
	std::wifstream File;
	std::wstring Buffer;
	unsigned int Line = (*ThrInfo).getStartLine();
	unsigned int FinalLine = (*ThrInfo).getFinalLine();

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	File.open((*ThrInfo).getFilePath(), std::ios::in);

	if (!File.is_open())
	{
		std::cerr << "Fail opening the file: " << (*ThrInfo).getFilePath() << std::endl;
		exit(EXIT_FAILURE);
	}

	seekFileLine(File, Line);

	while (!File.eof() && Line <= FinalLine)
	{
		std::getline(File, Buffer);
		CurrentLine = Line;
		analyzeLine(Buffer);
		Line++;
	}

	File.close();
}


SearchingThread::~SearchingThread()
{
}

void SearchingThread::createMatch(std::wstring PreviousWord, std::wstring MatchingWord, std::wstring NextWord)
{
	MatchInfo Match(CurrentLine, PreviousWord, MatchingWord, NextWord);

	std::lock_guard<std::mutex> lock(*Mutex);

	(*ThrInfo).addToMatchs(Match);
}

void SearchingThread::analyzeLine(std::wstring Line)
{
	std::wstring PreviousWord = L"",Temp;
	std::wstring MatchingWord;
	bool FindedWord = false;

	unsigned int i = 0;
	std::wistringstream StringStream(Line);
	std::vector<std::wstring> StringsVector;

	while (std::getline(StringStream, Temp, L' '))
		StringsVector.push_back(Temp);

	for(std::wstring Word : StringsVector)
	{
		if (FindedWord)
		{
			createMatch(PreviousWord, MatchingWord, Word);
			PreviousWord = MatchingWord;
			FindedWord = false;
		}

		if (analyzeWord(Word))
		{
			MatchingWord = Word;
			FindedWord = true;
		}
		else
		{
			PreviousWord = Word;
		}
	}

	if (FindedWord)
	{
		createMatch(PreviousWord, MatchingWord, L"");
	}
	
}

bool SearchingThread::analyzeWord(std::wstring Word)
{
	unsigned int PositionCounter = 0;
	std::wstring WordToFind = (*ThrInfo).getWordToFind();
	SearchingState State = SearchingState::WrongWord;

	if (tolower((char)Word[0]) == tolower((char)WordToFind[0]) || isTheSameCharacterWithAccent(Word[0], WordToFind[0]))
	{
		State = SearchingState::ComparingWords;
		PositionCounter++;
	}
	else if((*ThrInfo).isAAllowedCharacter(Word[0]))
	{
		State = SearchingState::AllowedCharacter;
	}

	for (unsigned int i = 1; i < Word.size(); i++)
	{
		switch (State) 
		{
		case SearchingState::AllowedCharacter:
			if (tolower((char)Word[i]) == tolower((char)WordToFind[PositionCounter]) || isTheSameCharacterWithAccent(Word[i],WordToFind[PositionCounter]))
			{
				State = SearchingState::ComparingWords;
				PositionCounter++;
			}
			else if (!(*ThrInfo).isAAllowedCharacter(Word[0]))
			{
				State = SearchingState::WrongWord;
			}
			break;
		case SearchingState::ComparingWords:
			if (tolower((char)Word[i]) == tolower((char)WordToFind[PositionCounter]) || isTheSameCharacterWithAccent(Word[i], WordToFind[PositionCounter]))
			{
				if (++PositionCounter == WordToFind.size())
				{
					State = SearchingState::PatternFinded;
				}
			}
			else
			{
				State = SearchingState::WrongWord;
			}
			break;
		case SearchingState::PatternFinded:
			if (!(*ThrInfo).isAAllowedCharacter(Word[i]))
			{
				State = SearchingState::WrongWord;
			}
			break;
		case SearchingState::WrongWord:
			return false;
		}
	}

	if (State == SearchingState::PatternFinded)
	{
		return true;
	}

	return false;
	
}
