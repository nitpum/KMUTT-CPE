#include <mpi.h>
#include <stdio.h>
#define MSG_SIZE 32

int main (int argc, char *argv[]) {
  int i;
  int id; /* process rank */
  int p;  /* number of process */
  char message[MSG_SIZE];
  MPI_Status status;

  MPI_Init(&argc, &argv);

  MPI_Comm_size(MPI_COMM_WORLD, &p);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);

  if (id == 0) {
    for (i = 1; i < p; i++) {
      MPI_Recv(message, MSG_SIZE, MPI_CHAR, i, 0, MPI_COMM_WORLD, &status);
      puts(message);
    }
  } else {
    sprintf(message, "Hello rank 0, I'm rank %d", id);
    MPI_Send(message, MSG_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}
