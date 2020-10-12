#pragma once
#include <iostream>
using namespace std;

class CNode
{
	int ver;
	int cost;
public:
	int getCost() {
		return cost;
	}
	int getVer() { return ver; }
	CNode();
	~CNode();

	friend class CPriorityQueue;
};

