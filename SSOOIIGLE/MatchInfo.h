#pragma once

#include <string>

class MatchInfo
{
public:
	MatchInfo(int Line, std::string PreviousWord, std::string MatchingWord, std::string NextWord);
	~MatchInfo();
	std::string getString();
private:
	int Line;
	std::string PreviousWord;
	std::string MatchingWord;
	std::string NextWord;
};

