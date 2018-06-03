#include "Time.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <Math.h>
#include <fstream>

#include <stdio.h>
#include <tchar.h>

void Time::StartCounter() {
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
void Time::GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	measurements.push_back(double(li.QuadPart - CounterStart) / PCFreq);
}

double Time::printAverage()
{
	double average = 0;
	for (unsigned int i = 0; i < measurements.size(); i++) average = average + measurements[i];
	average = average / measurements.size();
	return average;
}

void Time::reset()
{
	PCFreq = 0.0;
	CounterStart = 0;
	measurements.clear();
}