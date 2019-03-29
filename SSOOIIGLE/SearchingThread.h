#pragma once

#include <string>
#include "ThreadInfo.h"

class SearchingThread
{
public:
	SearchingThread();
	void initTask(std::string FilePath, std::string WordToFind, ThreadInfo &ThrInfo);
	~SearchingThread();

};

