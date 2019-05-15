#include<iostream>
#include<string.h>
#include<stdio.h>
#include<time.h>

#define SIZE 4

using namespace std;

void battle(int planet1, int distance1, int planet2, int &troops1, int &troops2);

int main() {


	int contor = 0;
	int var1=9;
	int var2=9;
	int i;

	char c;

	srand(time(NULL));

	int planets[SIZE] = { 0,1,2,3 };
	int distance[SIZE] = { 4,9,12,3 };
	int troops[SIZE];
	int loserPlanets[SIZE+1] = { 9,9,9,9,9 }, cnt = 0, k = 0;
	int winner = 0;
	int pass = 0;
	int loserCount = 0;

	int k1 = 0;

	int oldVar1, oldVar2;

	for (i = 0; i < SIZE; i++) {
		troops[i] = rand() % 40;
		printf("Planeta %d are %d trupe\n", i + 1, troops[i]);
		//printf("%d\n", troops[i]);
	}
	while (winner == 0) {
		printf("VENI AICI\n");
		var1 = rand() % 4;
		while (pass == 0) {
			for (i = 0; i < SIZE+1; i++) {
				if (var1 == loserPlanets[i]) {
				//	printf("var1 e %d si lose e %d\n", var1, loserPlanets[i]);
					k1++;
					break;
				}
			}

			if (k1 > 0) {
				var1 = rand() % 4;
			//	printf("CAT E VAR1:%d\n", var1);
				k1 = 0;
			}
			else {
				pass = 1;
				break;
			}
			
		}
		printf("Ies cu %d\n", var1);
		pass = 0;

		var2 = rand() % 4;
		while (pass == 0) {
			for (i = 0; i < SIZE+1; i++) {
				if (var2 == loserPlanets[i]) {
					k1++;
					break;
				}
			}

			if (k1 > 0) {
				var2 = rand() % 4;
				//printf("CAT E VAR1:%d\n", var1);
				k1 = 0;
			}
			else {
				
				pass = 1;
				break;
			}

		}
		printf("Ies cu %d\n", var2);
		for (int i = 0; i < SIZE+1; i++) {
			printf("%d ", loserPlanets[i]);
		}
		pass = 0;
		if (var1 == var2) {
			loserPlanets[4] = var1;
			while (pass == 0) {
				for (i = 0; i < SIZE+1; i++) {
					if (var2 == loserPlanets[i]) {
						k1++;
						break;
					}
				}

				if (k1 > 0) {
					var2 = rand() % 4;
					//printf("CAT E VAR1:%d\n", var1);
					k1 = 0;
				}
				else {

					pass = 1;
					break;
				}

			}
		}
		printf("Ies din nou cu %d\n", var2);
		/*if (var1 == var2) {
			while (var1 == var2) {
				var1 = rand() % 4;
				var2 = rand() % 4;
			}
		}*/
		printf("\n");
		printf("Prima batalie este intre planeta %d si planeta %d\n", planets[var1], planets[var2]);
		printf("\n");
		battle(planets[var1], distance[var1], planets[var2],
			troops[var1], troops[var2]);

		printf("Trupe1 %d Trupe2 %d\n", troops[var1], troops[var2]);

		if (troops[var1] == 0) {

			loserPlanets[cnt] = planets[var1];
			loserCount++;
			cnt++;
		}
		else if (troops[var2] == 0) {

			loserPlanets[cnt] = planets[var2];
			loserCount++;
			cnt++;
		}

		oldVar1 = var1;
		oldVar2 = var2;

		var1 = rand() % 4;
		var2 = rand() % 4;
		if (loserCount == 1) {
			while (var1 == oldVar1 || var1 == oldVar2) {
				var1 = rand() % 4;
			}
			while (var2 == oldVar1 || var2 == oldVar2 || var2 == var1) {
				var2 = rand() % 4;
			}
			printf("\n");
			printf("A doua batalie este intre planeta %d si planeta %d\n", planets[var1], planets[var2]);
			printf("\n");
			battle(planets[var1], distance[var1], planets[var2],
				troops[var1], troops[var2]);

			if (troops[var1] == 0) {
				loserPlanets[cnt] = planets[var1];
				cnt++;
			}
			else if (troops[var2] == 0) {
				loserPlanets[cnt] = planets[var2];
				cnt++;
			}

			for (i = 0; i < SIZE+1; i++) {
				if (loserPlanets[i] != 0)
					printf("LUZ:%d\n", loserPlanets[i]);
			}
		}
		for (i = 0; i < SIZE; i++) {
			//daca 3 trupe sunt egale cu zero
			//spun care planeta castiga
			if (troops[i] == 0)
			{
				k++;
			}
			if (k == SIZE - 1) {
				for (i = 0; i < SIZE; i++) {
					if (troops[i] > 0) {
						printf("Planeta care castiga razboiul este %d\n", i);
						winner = 1;
					}
				}
			}
		}

		k = 0;

	}
	c = getchar();
}

void battle(int planet1, int distance1, int planet2, int &troops1, int &troops2) {

	/*printf("Planeta 1 %d\n", planet1);
	printf("Planeta 2 %d\n", planet2);

	printf("Distanta p1:%d\n", distance1);

	printf("Trupe p1:%d\n", troops1);
	printf("Trupe p2:%d\n", troops2);*/

	printf("Planeta %d vrea sa invadeze planeta\n", planet2, planet1);
	printf("Va trebui sa calatoreasca spre ea %d timpi\n", distance1);

	printf("Intre timp planeta %d isi mareste trupele\n", planet1);
	troops1 = troops1 + distance1;
	printf("Trupele planetei gazda sunt acum %d\n", troops1);

	if (troops1 < troops2) {
		printf("Planeta %d pierde si planeta %d castiga\n", planet1, planet2);
		troops2 = troops2 - troops1;
		troops1 = 0;
		printf("Planeta %d ramane cu %d trupe\n", planet2, troops2);
	}
	else if (troops1 > troops2) {
		printf("Planeta %d castiga si planeta %d pierde\n", planet1, planet2);
		troops1 = troops1 - troops2;
		troops2 = 0;
		printf("Planeta %d ramane cu %d trupe\n", planet1, troops1);
	}
	else if (troops1 == troops2) {
		printf("E egal,ambele planete pierd!\n");
		troops1 = 0;
		troops2 = 0;
	}

	printf("\n\n");

}