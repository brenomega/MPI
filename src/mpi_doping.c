#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char* argv[]) {
int meu_ranque, num_procs;
int origem, destino, etiq = 0;
int mensagem;
double tempo_inicial;
MPI_Status estado;    

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    if (meu_ranque != 0) {
        origem = meu_ranque - 1;
        destino = (meu_ranque == num_procs - 1) ? 0 : meu_ranque + 1;
        MPI_Recv(&mensagem, 1, MPI_INT, origem, etiq, MPI_COMM_WORLD, &estado);
        printf("[P%d] Recebi %d de P%d. Somando meu rank...\n", meu_ranque, mensagem, estado.MPI_SOURCE);
        mensagem += meu_ranque;
        MPI_Send(&mensagem, 1, MPI_INT, destino, etiq, MPI_COMM_WORLD);
    }
    else {
        tempo_inicial = MPI_Wtime();
        mensagem = 1000;
        destino = 1;
        origem = num_procs - 1;
        printf("[P0] Iniciando anel com valor %d\n", mensagem);
        MPI_Send(&mensagem, 1, MPI_INT, destino, etiq, MPI_COMM_WORLD);
        MPI_Recv(&mensagem, 1, MPI_INT, origem, etiq, MPI_COMM_WORLD, &estado);
        printf("[P0] Bastao retornou! Valor final: %d | Tempo: %f s\n", mensagem, MPI_Wtime() - tempo_inicial);
    }
    MPI_Finalize();
    return (0);
}
