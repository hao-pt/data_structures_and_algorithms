#include "KMP.h"
int main() {
	CKMP a;
	a.input();
	int k = a.KMP_searching();
	cout << k << endl;
	if (k)
		cout << "This is subString";
	else
		cout << "This isn't subString";
	cout << endl;

	k = a.BruteForce_searching();
	cout << k << endl;
	cout << a.rabinKarp_searching();
	cin.get();
	return 0;
}