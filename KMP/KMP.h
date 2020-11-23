#pragma once
#include <iostream>
#include <string>
using namespace std;
class CKMP
{
private:
	string txt,pattern;
public:
	void input();
	int* computeTempArray();
	int KMP_searching();
	int BruteForce_searching();
	int rabinKarp_searching();
	CKMP();
	~CKMP();
};

