#pragma once

#include <string>

class MatchInfo
{
public:
	MatchInfo(int Line, std::wstring PreviousWord, std::wstring MatchingWord, std::wstring NextWord);
	~MatchInfo();
	std::wstring getString();
private:
	int Line;
	std::wstring PreviousWord;
	std::wstring MatchingWord;
	std::wstring NextWord;
};

