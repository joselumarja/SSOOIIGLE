#include <string>
#include <vector>


#ifndef UTILITIES_H
#define UTILITIES_H
	const std::vector<wchar_t> aAccents = { L'�' ,L'�' ,L'�',L'�',L'�',L'�',L'�'};
	const std::vector<wchar_t> eAccents = { L'�', L'�' ,L'�' ,L'�'};
	const std::vector<wchar_t> iAccents = { L'�' ,L'�' ,L'�' ,L'�'};
	const std::vector<wchar_t> oAccents = { L'�' ,L'�' ,L'�' ,L'�'};
	const std::vector<wchar_t> uAccents = { L'�' ,L'�' ,L'�',L'�'};
	const std::vector<wchar_t> yAccents = { L'�' ,L'�'};

	const std::vector<wchar_t> AAccents = { L'�' ,L'�' ,L'�' ,L'�',L'�',L'�'};
	const std::vector<wchar_t> EAccents = { L'�', L'�', L'�', L'�'};
	const std::vector<wchar_t> IAccents = { L'�',L'�',L'�',L'�'};
	const std::vector<wchar_t> OAccents = { L'�', L'�' ,L'�', L'�'};
	const std::vector<wchar_t> UAccents = {L'�',L'�',L'�',L'�'};
	const std::vector<wchar_t> YAccents = {L'�'};

	unsigned int countFileLines(std::string FilePath);
	void seekFileLine(std::wifstream &File, unsigned int LineNumber);

	bool isTheSameCharacterWithAccent(wchar_t Character1, wchar_t Character2);
	bool isTheSameCharacterWithAccentImplicitDeclaration(wchar_t Character, wchar_t CharacterWithAccent);
	bool checkIfCharIsInList(wchar_t Character, std::vector<wchar_t> CharacterList);
#endif