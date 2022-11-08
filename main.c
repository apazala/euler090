#include <stdio.h>

int diecombinations[211];
int ncomb;


int combination[6];

int squardigits[11][2];


void fillsquares(int n, int m) {
	for (int i = 1; i <= n; i++) {
		int sq = i*i;

		for (int j = 0; j < m; j++) {
			int d = sq % 10;
			if (d == 9) d = 6;

			squardigits[i - 1][j] = (1 << d);

			sq /= 10;
		}

	}
}

void fillcombinations(int v, int i) {
	i++;

	if (i == 6) {
		for (int j = 0; j < 6; j++) {
			diecombinations[ncomb] |= (1<<combination[j]);
		}
		ncomb++;
		return;
	}


	for (int j = v + 1; j < 10; j++) {
		combination[i] = (j == 9 ? 6 : j);
		fillcombinations(j, i);
	}
}


int solve(int n) {
	int res = 0;

	for (int i = 0; i < ncomb; i++) {
		for (int j = i; j < ncomb; j++) {
			int valid = 1;
			for (int isq = 0; valid && isq < n; isq++) {
				valid = (((squardigits[isq][0] & diecombinations[i]) &&
					(squardigits[isq][1] & diecombinations[j])) ||
					((squardigits[isq][1] & diecombinations[i]) &&
					(squardigits[isq][0] & diecombinations[j])));
				
			}
			if (valid) res++;
		}
	}

	return res;
}

void init() {
	fillcombinations(-1, -1);
}


int main()
{
	init();

	int n = 9, m = 2;


	fillsquares(n, m);

	int res = solve(n);

	printf("%d\n", res);

    return 0;
}
