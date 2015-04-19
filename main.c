#include <stdio.h>
#include <stdlib.h>

#define DEBUG

#define NUMBER_OF_ARGS 2
#define LOOP_ITER 120
#define LD_DEST_INITIAL 0
#define ADD_DEST_INITIAL 4
#define LDSD_OFFSET_INITIAL 0
#define REG_INCR 5
#define MEM_INCR 8

int main(int argc,char **argv)
{
    // =============================================================================================
    // Check Input Arguments
    // =============================================================================================

    if(argc != NUMBER_OF_ARGS+1)
    {
        printf("ERROR: In main(...): ");
        printf("The correct number of arguments has not been passed!\n");
        exit(1);
    }

    if((LOOP_ITER % atoi(argv[1])) != 0)
    {
        printf("ERROR: In main(...): ");
        printf("The number of unrolls is not a divisor of the number of loop iterations!\n");
        exit(1);
    }

    // =============================================================================================
    // Declare Variables
    // =============================================================================================

    int ld_dest_counter = LD_DEST_INITIAL;
    int add_dest_counter = ADD_DEST_INITIAL;
    int ldsd_offset_counter = LDSD_OFFSET_INITIAL;
    int i = 0; int k = atoi(argv[1]);

    // =============================================================================================
    // Print File
    // =============================================================================================

    #ifndef DEBUG
        freopen(argv[2], "w", stdout);
    #endif // DEBUG

    printf("Loopinit:\n");
    for(i = 0; i < k; i++)
    {
        printf("LD   F%d, %d(R1)\n", ld_dest_counter, ldsd_offset_counter);
        printf("ADDD F%d, F%d, F2\n", add_dest_counter, ld_dest_counter);
        printf("SD   F%d, %d(R1)\n", add_dest_counter, ldsd_offset_counter);

        ld_dest_counter += REG_INCR;
        add_dest_counter += REG_INCR;
        ldsd_offset_counter += MEM_INCR;
    }
    printf("SUBI R1, R1, %d\n", ldsd_offset_counter);
    printf("BNEZ R1, R2, Loopinit\n");

    #ifndef DEBUG
        fclose(stdout);
    #endif // DEBUG

    // =============================================================================================
    // End
    // =============================================================================================

    return 0;
}
