#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){

    MPI::Init();
    int rank = MPI::COMM_WORLD.Get_rank();
    int size = MPI::COMM_WORLD.Get_size();
    int len; char name[MPI_MAX_PROCESSOR_NAME];

    MPI::Get_processor_name(name, len);

    cout <<"Greetings from process " << rank << " of " << size << " on " << name << endl;

    MPI::Finalize();

    return 0;
}