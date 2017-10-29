#include <stdio.h>
#include <string.h>  /* For strlen */
#include <mpi.h>     /* For MPI functions, etc */

int main(){
    int my_rank;
    int comm_sz;
    int n = 1024;
    int local_n;
    double local_integral;
    double total_integral;
    int source;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    h = (b-a)/n;            // h is the same for all processes
    local_n = n / comm_sz;  // So is the number of trapezoids

    local_a = a + my_rank * local_n * h;
    local_b = local_a + local_n * h;
    local_integral = Trap(local_a, local_b, local_n, h);

    if (my_rank != 0){
        MPI_Send(&local_integral, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    else {
        total_integral = local_integral;
        for (source = 1; source < comm_sz; source++){
            MPI_Recv(&local_integral, 1, MPI_DOUBLE, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_integral += local_integral;
        }
    }

    if (my_rank == 0){
        printf("With n = %d trapezoids, our estimate\n", n);
        printf("of the integral from %f to %f = %.15e\n", a, b, total_integral);
    }

    MPI_Finalize();
    return 0;
}

double Trap(
    double left_endpt;
    double right_endpt;
    int trap_count;
    double base_len){

        double estimate;
        double x;
        int i;

        estimate = (f)
    }