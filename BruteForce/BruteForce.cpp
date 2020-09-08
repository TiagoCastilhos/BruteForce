#include <iostream>
#include <string>
#include <fstream>
#ifdef _OPENMP
#include <omp.h>
#else if
#define omp_get_thread_num() 0
#endif
#define NUMTHREADS 8
using namespace std;

char chars[] = { '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
string t;
double startTime, endTime = 0;

void checkPassword(string password);
void recurse(int width, int position, string baseString);

int main() {
	cout << "Enter a string: " << endl;
	cin >> t;
	int maxChars = 13;

	startTime = omp_get_wtime();

	for (int i = 0; i < maxChars + 1; i++) {
		recurse(i, 0, "");
	}

	return 0;
}

void recurse(int width, int position, string baseString) {
#pragma omp parallel num_threads(NUMTHREADS)
#pragma omp for
	for (int i = 0; i < 35; i++) {
		if (position < width - 1) {
			recurse(width, position + 1, baseString + chars[i]);
		}
		checkPassword(baseString + chars[i]);
	}
}

void checkPassword(string password) {
	if (password == t) {
		cout << "Senha encontrada [" << password << "]" << endl;
		endTime = omp_get_wtime();
		cout << "Processo levou " << endTime - startTime << " segundos";
		exit(1);
	}
}