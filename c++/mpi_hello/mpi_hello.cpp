#include <mpi.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using namespace MPI;

int main(int argc, char *argv[]){
    
    string greeting;
    // Initialize MPI.
    MPI::Init();

    // Get the individual process ID
    int rank = MPI::COMM_WORLD.Get_rank();

    // Get the number of processes
    int size = MPI::COMM_WORLD.Get_size();

    int len; char name[MPI_MAX_PROCESSOR_NAME];

    MPI::Get_processor_name(name, len);

    cout <<"Greetings from process " << rank << " of " << size << " on " << name << endl;

    MPI::Finalize();

    return 0;
}