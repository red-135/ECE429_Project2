#include <stdio.h>
#include <stdlib.h>

#define LOOP_ITER 120
#define LD_DEST_INITIAL 0
#define LD_DEST_1ITER 1
#define LD_DEST_2ITER 6
#define LD_DEST_INCR 2
#define ADD_DEST_INITIAL 4
#define ADD_DEST_1ITER 5
#define ADD_DEST_2ITER 7
#define ADD_DEST_INCR 2
#define LDSD_OFFSET_INITIAL 0
#define LDSD_OFFSET_INCR 8
#define RREG_INITIAL 2
#define RREG_INCR 0
#define FREG_INITIAL 1
#define FREG_INCR 2

int main(int argc,char **argv)
{
    // =============================================================================================
    // Check Input Arguments
    // =============================================================================================

    if(argc <= 1)
    {
        fprintf(stderr, "ERROR: In main(...): ");
        fprintf(stderr, "Too few arguments have been passed!\n");
        exit(1);
    }
    else if(argc == 2)
    {
    }
    else if(argc == 3)
    {
        freopen(argv[2], "w", stdout);
    }
    else if(argc >= 4)
    {
        fprintf(stderr, "ERROR: In main(...): ");
        fprintf(stderr, "Too many arguments have been passed!\n");
        exit(1);
    }

    if((LOOP_ITER % atoi(argv[1])) != 0)
    {
        fprintf(stderr, "ERROR: In main(...): ");
        fprintf(stderr, "The number of unrolls is not a divisor of the number of loop iterations!\n");
        exit(1);
    }

    if(atoi(argv[1]) <= 0 || atoi(argv[1]) > LOOP_ITER)
    {
        fprintf(stderr, "ERROR: In main(...): ");
        fprintf(stderr, "The number of unrolls is not in the proper range!\n");
        exit(1);
    }

    // =============================================================================================
    // Declare Variables
    // =============================================================================================

    int ld_dest_counter = LD_DEST_INITIAL;
    int add_dest_counter = ADD_DEST_INITIAL;
    int ldsd_offset_counter = LDSD_OFFSET_INITIAL;
    int rreg_count = RREG_INITIAL;
    int freg_count = FREG_INITIAL;
    int reg_count = 0;
    int i = 0; int k = atoi(argv[1]);

    // =============================================================================================
    // Print File
    // =============================================================================================

    printf("Loopinit:\n");
    for(i = 0; i < k; i++)
    {
        printf("LD   F%d, %d(R1)\n", ld_dest_counter, ldsd_offset_counter);
        printf("ADDD F%d, F%d, F2\n", add_dest_counter, ld_dest_counter);
        printf("SD   F%d, %d(R1)\n", add_dest_counter, ldsd_offset_counter);

        if(ld_dest_counter == 0)
        {
            ld_dest_counter = LD_DEST_1ITER;
            add_dest_counter = ADD_DEST_1ITER;
        }
        else if(ld_dest_counter == 1)
        {
            ld_dest_counter = LD_DEST_2ITER;
            add_dest_counter = ADD_DEST_2ITER;
        }
        else
        {
            ld_dest_counter += LD_DEST_INCR;
            add_dest_counter += ADD_DEST_INCR;
        }
        ldsd_offset_counter += LDSD_OFFSET_INCR;

        rreg_count += RREG_INCR;
        freg_count += FREG_INCR;
        reg_count = rreg_count + freg_count;
    }
    printf("SUBI R1, R1, %d\n", ldsd_offset_counter);
    printf("BNEZ R1, R2, Loopinit\n");

    // =============================================================================================
    // Print Statistics
    // =============================================================================================

    printf("\n");
    printf("===================================================\n");
    printf("Number of Unrolls: %d\n\n", k);
    printf("Number of Integer Registers: %d\n", rreg_count);
    printf("Number of Floating Point Registers: %d\n", freg_count);
    printf("Number of Registers: %d\n", reg_count);
    printf("===================================================\n");

    // =============================================================================================
    // End
    // =============================================================================================

    return 0;
}
