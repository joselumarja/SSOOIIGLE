#include <string>

#ifndef UTILITIES_H
#define UTILITIES_H
	int countFileLines(std::string FilePath);
	void seekFileLine(std::ifstream &File, unsigned int LineNumber);
#endif