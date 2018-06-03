#pragma once
#include <vector>

class Time
{
public:
	double PCFreq = 0.0;
	__int64 CounterStart = 0;
	std::vector <double> measurements;
	void StartCounter();
	void GetCounter();
	double printAverage();
	void reset();
};

