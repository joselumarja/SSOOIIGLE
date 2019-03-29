#include "pch.h"
#include "MatchInfo.h"


MatchInfo::MatchInfo(int Line, std::string PreviousWord, std::string MatchingWord, std::string NextWord)
{
	this->Line = Line;
	this->PreviousWord = PreviousWord;
	this->MatchingWord = MatchingWord;
	this->NextWord = NextWord;
}


MatchInfo::~MatchInfo()
{
}

std::string MatchInfo::getString()
{
	return std::string(":: line " + std::to_string(Line) + " :: ... " + PreviousWord + " " + MatchingWord + " " + NextWord + " ...");
}
