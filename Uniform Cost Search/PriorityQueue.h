#pragma once
#include "Node.h"

class CPriorityQueue
{
	CNode *a;
	int lagSize;
	int size;
	const int initSize = 100;

public:
	void min_heapify(int i) {
		int left = 2 * i + 1;
		int right = left + 1;
		int smallest = i;

		if (left < size && a[smallest].cost > a[left].cost)
			smallest = left;
		if (right < size && a[smallest].cost > a[right].cost)
			smallest = right;

		if (smallest != i) {
			swap(a[i], a[smallest]);
			min_heapify(smallest);
		}
	}

	void initQueue() {
		size = 0;
		lagSize = initSize;
		a = new CNode[lagSize];
		if (a == NULL) {
			cout << "Error!\n";
			return;
		}
	}
	void enQueue(int ver, int cost) {
		// Resize if it don't have enough memmory
		if (size == lagSize) {
			lagSize = lagSize * 2;

			CNode *tmp = (CNode*)realloc(a, lagSize * sizeof(CNode));
			a = tmp;
			if (a == NULL)
				cout << "Don't have enough memorry to allocate!";
			return;
		}

		// Insert last
		int idx, parent;
		// Index of array start from 0
		idx = size++;
		// Move all costeys parent have cost < cost behind 
		for (; idx; idx = parent)
		{
			parent = (idx - 1) / 2;
			if (a[parent].cost <= cost) break;
			a[idx] = a[parent];
		}
		// put cost in the correct location
		a[idx].ver = ver;
		a[idx].cost = cost;

	}
	void deQueue() {
		--size;
		// Move all key backward
		for (int i = 0; i < size; i++)
			a[i] = a[i + 1];

		// resize if the large size is 2x then size
		if (size > initSize && lagSize / size >= 2) {
			lagSize /= 2;
			a = (CNode*)realloc(a, lagSize * sizeof(CNode));
		}

		// heapify recursively that tree
		min_heapify(0);

	}

	CNode front() {
		return a[0];
	}

	bool empty() {
		return size == 0;
	}

	// Ham cap nhat gia tri
	void set(int ver, int nCost) {
		int i;
		for (i = 0; i < size; i++)
		{
			if (a[i].ver == ver) {
				a[i].cost = nCost;
				break;
			}
		}
		// heapify from i to the parent
		while (i >= 0){
			min_heapify(i);
			i--;
		}
	}
		

	// Ham nay tra ve chi phi cua 1 dinh
	int findCost(int ver) {
		for (int i = 0; i < size; i++)
		{
			if (a[i].ver == ver)
				return a[i].cost;
		}
		// Neu khong tim thay
		return -1;
	}

	CPriorityQueue();
	~CPriorityQueue();


};

