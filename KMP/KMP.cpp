#include "KMP.h"

void CKMP::input() {
	txt = "abxabcabcaby";
	/*pattern = "abcaby";*/

	pattern = "aaata";
}

int* CKMP::computeTempArray() {
	int n = pattern.length();
	int *tmp = new int[n];
	tmp[0] = 0;
	int idx = 0;
	for (int i = 1; i < n;)
	{
		if (pattern[i] == pattern[idx]) {
			tmp[i] = idx + 1;
			if (pattern[tmp[i]] == pattern[i + 1]) // KMP: kiểm tra xem kí tự lùi về có khớp với kí tự bị mis-match là p[i + 1]
				tmp[i] = tmp[tmp[i] - 1];
			i++; idx++;
		}
		else {
			if (idx != 0)
				idx = tmp[idx - 1];
			else {
				tmp[i] = 0;
				i++;
			}
		}
	}
	return tmp;
}
int CKMP::KMP_searching() {
	int *tmp = computeTempArray();
	for (int i = 0; i < pattern.length(); i++) {
		cout << tmp[i] << " ";
	}
	cout << endl;

	int i = 0, j = 0;
	while (i < txt.length() && j < pattern.length()) {
		if (txt[i] == pattern[j]) {
			i++; j++;
		}
		else {
			if (j != 0) {
				j = tmp[j - 1];
			}
			else
				i++;
		}
	}
	if (j == pattern.length())
		return i - j;
	return 0;
}
int CKMP::BruteForce_searching() {
	for (int i = 0; i < txt.size(); i++)
	{
		int j = 0;
		while (j < pattern.size() && pattern[j] == txt[i + j]) {
			j++;
		}
		if (j == pattern.size())
			return i;
	}
	return -1;
}
const int PRIME = 101;
int createHash(string text, int end) {
	int hash = 0;
	for (int i = 0; i < end; i++)
	{
		hash += text[i] * pow(PRIME, i);
	}
	return hash;
}
int recalculateHash(string text, int oldIndex, int nexIndex, int oldHash, int patternLength) {
	int newHash = oldHash - text[oldIndex];
	newHash /= PRIME;
	newHash += text[nexIndex] * pow(PRIME, patternLength - 1);
	return newHash;
}
bool isEqual(string text, int start, int end, string pattern, int start2, int end2) {
	while (start <= end && start2 <= end2)
	{
		if (text[start] != pattern[start2])
			return 0;
		start++;
		start2++;
	}
	return 1;
}
int CKMP::rabinKarp_searching() {
	int n = txt.size();
	int m = pattern.size();
	int textHash = createHash(txt, m);
	int patternHash = createHash(pattern, m);
	for (int i = 0; i < n - m + 1; i++)
	{
		if (textHash == patternHash && isEqual(txt, i, i + m - 1, pattern, 0, m - 1))
			return i;
		else {
			patternHash = recalculateHash(txt, i, i + m, textHash, m);
		}
	}
	return 0;
}

CKMP::CKMP()
{
}


CKMP::~CKMP()
{
}
