#include "pch.h"
#include "MatchInfo.h"


MatchInfo::MatchInfo(int Line, std::wstring PreviousWord, std::wstring MatchingWord, std::wstring NextWord)
{
	this->Line = Line;
	this->PreviousWord = PreviousWord;
	this->MatchingWord = MatchingWord;
	this->NextWord = NextWord;
}


MatchInfo::~MatchInfo()
{
}

std::wstring MatchInfo::getString()
{
	return std::wstring(L":: line " + std::to_wstring(Line) + L":: ... " + PreviousWord + L" " + MatchingWord + L" " + NextWord + L" ...");
}
