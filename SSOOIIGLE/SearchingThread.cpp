#include "pch.h"
#include "SearchingThread.h"
#include "Utilities.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

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
	std::ifstream File;
	std::string Buffer;
	unsigned int Line = (*ThrInfo).getStartLine();
	unsigned int FinalLine = (*ThrInfo).getFinalLine();

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

void SearchingThread::createMatch(std::string PreviousWord, std::string MatchingWord, std::string NextWord)
{
	MatchInfo Match(CurrentLine, PreviousWord, MatchingWord, NextWord);

	std::lock_guard<std::mutex> lock(*Mutex);

	(*ThrInfo).addToMatchs(Match);
}

void SearchingThread::analyzeLine(std::string Line)
{
	std::string PreviousWord = "";
	std::string MatchingWord;
	bool FindedWord = false;

	unsigned int i = 0;
	std::istringstream StringStream(Line);
	std::istream_iterator<std::string> StringIterator(StringStream);
	std::vector<std::string> StringsVector(StringIterator, std::istream_iterator<std::string>());

	for(std::string Word : StringsVector)
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
		createMatch(PreviousWord, MatchingWord, "");
	}
	
}

bool SearchingThread::analyzeWord(std::string Word)
{
	unsigned int PositionCounter = 0;
	std::string WordToFind = (*ThrInfo).getWordToFind();
	SearchingState State = SearchingState::WrongWord;

	if (Word[0] == WordToFind[0])
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
			if (Word[i] == WordToFind[PositionCounter])
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
			if (Word[i] == WordToFind[PositionCounter++])
			{
				if (PositionCounter == WordToFind.size())
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
