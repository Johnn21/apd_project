#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 4

int main(int argc, char *argv[]) {

	int numprocs, rank, sendcount, recvcount, source;
	int sendbuf[SIZE] = { {0},{1},{2},{3} };
	int sendbufDist[SIZE] = { {4},{7},{2},{1} };
	int recvbuf[SIZE];
	int timp = 0;
	int recvbufDist[SIZE];
	int troops, i, partner;
	int copy_troops1, copy_troops2;
	int copy_planet;
	int oldProcess, conqueredPlanet = 0;
	int egal = 0;
	int var = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Status status;
	if (numprocs == SIZE) {
		source = 1;
		sendcount = 1;
		recvcount = 1;
		MPI_Scatter(sendbuf, sendcount, MPI_INT, recvbuf, recvcount, MPI_INT, source, MPI_COMM_WORLD);
		printf("rank= %d  Planeta: %d \n", rank, recvbuf[0]);
		MPI_Scatter(sendbufDist, sendcount, MPI_INT, recvbufDist, recvcount, MPI_INT, source, MPI_COMM_WORLD);
		printf("rank= %d  Distanta: %d \n", rank, recvbufDist[0]);

	}
	else
		printf("Must specify %d processors. Terminating.\n", SIZE);
	//  MPI_Finalize();

	//while(timp<= recvbufDist[0])

	srand(time(NULL) + rank);

	troops = rand() % 20 +1;
	//troops = 5;
	copy_troops1 = troops;
	copy_troops2 = troops;
	copy_planet = recvbuf[0];

	//troops1 sunt numerele de trupe din procesul in care eu trimit trupele 
	//troops2 sunt numerele de trupe pe care le trimit pentru invazie
	//copy_planet e planeta care vine sa invadeze 
	//recvbuf[0] e planeta care va fi invadata


	printf("Planeta %d din procesul %d are %d trupe\n", recvbuf[0], rank, troops);



	if (rank < numprocs / 2) {
		partner = numprocs / 2 + rank;
		MPI_Send(&copy_troops2, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
		MPI_Send(&copy_planet, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
		MPI_Recv(&copy_troops2, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&copy_planet, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
	}
	else if (rank >= rank / 2) {
		partner = rank - numprocs / 2;
		MPI_Send(&copy_troops2, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
		MPI_Send(&copy_planet, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
		MPI_Recv(&copy_troops2, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&copy_planet, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);

	}

	if (rank == 0 || rank == 1) {

		printf("Procesul %d are %d trupe\n", rank, copy_troops1);
		printf("Planeta %d vrea sa invadeze planeta %d,ea va calatori spre ea o distanta de %d\n", copy_planet, recvbuf[0], recvbufDist[0]);


		while (timp < recvbufDist[0]) {


			copy_troops1 = copy_troops1 + 1;//+timp

			printf("A trecut %d timp\n", timp + 1);

			timp += 1;

		}


		printf("Planeta %d si-a marit trupele! Acum are: %d trupe\n", recvbuf[0], copy_troops1);
		printf("Procesul %d a primit trupele %d\n", rank, copy_troops2);



		if (copy_troops1 < copy_troops2) {
			printf("Planeta %d din procesul %d a fost invadata\n", recvbuf[0], rank);
			troops = 0;
			printf("Planeta %d are acum %d trupe\n", recvbuf[0], troops);
			copy_troops2 = copy_troops2 - copy_troops1;
		}
		else if (copy_troops1 > copy_troops2) {
			printf("Planeta %d din procesul %d nu a fost invadata\n", recvbuf[0], rank);
			troops = copy_troops1 - copy_troops2;
			copy_troops1 = troops;
			printf("Planeta %d are acum %d trupe\n", recvbuf[0], troops);
			copy_troops2 = 0;
		}
		else if (copy_troops1 == copy_troops2) {
			printf("Egal!\n");
			copy_troops2 = 0;
			troops = 0;
			egal = 1;
		}

	}


	MPI_Barrier(MPI_COMM_WORLD);

	if (egal == 1) {
		if (troops > 0) {
			printf("PLANETA %d e castigatoare!\n", rank);
		}
	}
	else {

		//UPDATE THE TROOPS !

		printf("TRIMIT %d trupe in procesu %d din procesu %d", copy_troops2, partner, rank);

		if (rank < numprocs / 2) {
			partner = numprocs / 2 + rank;
			MPI_Send(&copy_troops2, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);

			MPI_Recv(&copy_troops2, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);

		}
		else if (rank >= rank / 2) {
			partner = rank - numprocs / 2;

			MPI_Send(&copy_troops2, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);

			MPI_Recv(&copy_troops2, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);

		}

		printf("Rank %d si trupe %d\n", rank, copy_troops2);

		if (rank == 2 || rank == 3) {
			troops = copy_troops2;
			printf("Trupele actualizate din procesul %d sunt %d\n", rank, troops);
		}

		printf("Trupele din %d sunt %d\n", rank, troops);


		if (troops > 0) {
			copy_planet = rank;
		}

		copy_troops2 = troops;
		copy_troops1 = troops;

		if (copy_planet < numprocs / 2) {

			var = rand() % 2;
			//var = 1;
			if (copy_planet == 0) {
				if (var == 0) {
					partner = 1;
				}
				else if (var == 1) {
					partner = 3;
				}
			}
			else if (copy_planet == 1) {
				if (var == 0) {
					partner = 0;
				}
				else if (var == 1) {
					partner = 2;
				}

			}

			MPI_Send(&copy_troops2, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);

			MPI_Recv(&copy_troops2, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);

		}
		else if (copy_planet >= numprocs / 2) {

			var = rand() % 2;
			//var = 1;
			if (copy_planet == 2) {
				if (var == 0) {
					partner = 1;
				}
				else if (var == 1) {
					partner = 3;
				}
			}
			else if (copy_planet == 3) {
				if (var == 0) {
					partner = 0;
				}
				else if (var == 1) {
					partner = 2;
				}

			}


			MPI_Send(&copy_troops2, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);

			MPI_Recv(&copy_troops2, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);

		}

		//if(rank == copy_planet)
		//printf("Comunic din %d cu procesu %d care are trupele %d\n", rank, partner,copy_troops2);

		copy_troops2 = troops;

		if (rank == copy_planet && (rank < numprocs / 2)) {
			if (copy_troops2 == 0) {
				//copy_troops2 = troops;
				if (copy_planet == 0) {
					if (partner == 1)
						partner = 3;
					else if (partner == 3)
						partner = 1;
				}
				else if (copy_planet == 1) {
					if (partner == 0)
						partner = 2;
					else if (partner == 2)
						partner = 0;
				}
			}

			MPI_Send(&copy_troops2, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);

			MPI_Recv(&copy_troops2, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);

		}
		else if (rank == copy_planet && (rank >= numprocs / 2)) {
			if (copy_troops2 == 0) {
				//	copy_troops2 = troops;
				if (copy_planet == 2) {
					if (partner == 1)
						partner = 3;
					else if (partner == 3)
						partner = 1;
				}if (copy_planet == 3) {
					if (partner == 0)
						partner = 2;
					else if (partner == 2)
						partner = 0;
				}
			}
			MPI_Send(&copy_troops2, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);

			MPI_Recv(&copy_troops2, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);

		}

		if (rank == copy_planet)
			//printf("Comunic din %d cu procesu %d care are trupele %d\n", rank, partner,copy_troops2);
			printf("Copy Troops %d din procesu %d si Trupe %d\n", copy_troops2, partner, troops);


		if (rank < numprocs / 2 && rank == copy_planet) {
			if (troops < copy_troops2) {
				printf("PLANETA %d e castigatoare\n", partner);
			}
			else if (troops > copy_troops2) {
				printf("PLANETA %d e castigatoare\n", rank);
			}
			else if (troops == copy_troops2) {
				printf("AVEM EGALITATE!\n");
			}
		}
	}

	printf("\n\n");



	MPI_Finalize();





}