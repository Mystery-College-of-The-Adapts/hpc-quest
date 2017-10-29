#include <stdio.h>
#include <string.h>  /* For strlen */
#include <mpi.h>     /* For MPI functions, etc */
#include <math.h>

void Get_data(int comm_sz, int my_rank, double *a_p, double *b_p, int *n_p );

double Trap(double local_a, double local_b, int local_n, double h);

double f(double x);

double Get_max(double my_val, int my_rank, int comm_sz);


int main(){
    int             my_rank;             /* My process rank */
    int             comm_sz;             /* The number of processes */
    int             n;                   /* Number of trapezoids */
    double          a;                   /* Left endpoint */
    double          b;                   /* Right endpoint */
    double          h;                   /* Trapezoid base length */
    double          local_a;             /* Left endpoint my process */
    double          local_b;             /* Right endpoint my process */
    int             local_n;             /* Number of trapezoids for my calculation */
    double          my_int;              /* Integral over my integral */
    double          r_int;               /* Received integral */
    double          total;               /* Total integral */
    int             source;              /* Process sending integral */
    int             dest = 0;            /* All messages go to 0 */
    int             tag = 0;             
    MPI_Status      status;
    double          start, finish, my_elapsed, elapsed;

    /* Let the system do what it needs to start up MPI */
    MPI_Init(NULL, NULL);

    /* Get my process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    /* Find out how many processes are being used */
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    
    Get_data(comm_sz, my_rank, &a, &b, &n);

    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();

    h = (b-a)/n;            // h is the same for all processes
    local_n = n / comm_sz;  // So is the number of trapezoids
    
    /* Length of each process' interval of
     * integration = local_n*h.  So my interval
     * starts at: */

    local_a = a + my_rank * local_n * h;
    local_b = local_a + local_n * h;
    my_int = Trap(local_a, local_b, local_n, h);

    /* Add up the areas calculated by each process */
    if (my_rank != 0){
        MPI_Send(&my_int, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
    }

    else {
        total = my_int;
        for (source = 1; source < comm_sz; source++){
            MPI_Recv(&r_int, 1, MPI_DOUBLE, source, tag, MPI_COMM_WORLD, &Status);
            total += r_int;
        }
    }

    finish = MPI_Wtime();

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