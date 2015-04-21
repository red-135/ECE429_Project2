// Note that this code has been written to produce a solution that utilizes a minimal number of
// registers. Although this requires some special handling of the register numbering at the
// beginning of the unrolling due to the placement of the constant register, it means that
// constraints on the number of registers used can be met without extra register renaming.

#include <stdio.h>
#include <stdlib.h>

#define LOOP_ITER 120
#define CONST_REG 2
#define LDSD_OFFSET_INITIAL 0
#define LDSD_OFFSET_INCR -8
#define RREG_INITIAL 2
#define FREG_INITIAL 1

int main(int argc,char **argv)
{

    int LD_DEST_INITIAL = -1;
    int LD_DEST_INCR = -1;
    int ADD_DEST_INITIAL = -1;
    int ADD_DEST_INCR = -1;
    int FREG_INCR = -1;
    int RREG_INCR = -1;

    // =============================================================================================
    // Check Input Arguments
    // =============================================================================================

    if(argc <= 2)
    {
        fprintf(stderr, "ERROR: In main(...): ");
        fprintf(stderr, "Too few arguments have been passed!\n");
        exit(1);
    }
    else if(argc == 3)
    {
    }
    else if(argc == 4)
    {
        freopen(argv[3], "w", stdout);
    }
    else if(argc >= 5)
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

    if(atoi(argv[2]) == 0)
    {
        LD_DEST_INITIAL = 0;
        LD_DEST_INCR = 2;
        ADD_DEST_INITIAL = 1;
        ADD_DEST_INCR = 2;
        FREG_INCR = 2;
        RREG_INCR = 0;
    }
    else
    {
        LD_DEST_INITIAL = 0;
        LD_DEST_INCR = 1;
        ADD_DEST_INITIAL = 0;
        ADD_DEST_INCR = 1;
        FREG_INCR = 1;
        RREG_INCR = 0;
    }

    // =============================================================================================
    // Declare Variables
    // =============================================================================================

    int ld_dest_counter_cur = LD_DEST_INITIAL;
    int ld_dest_counter_next = LD_DEST_INITIAL;
    int add_dest_counter_cur = ADD_DEST_INITIAL;
    int add_dest_counter_next = ADD_DEST_INITIAL;
    int ldsd_offset_counter = LDSD_OFFSET_INITIAL;
    int rreg_count = RREG_INITIAL;
    int freg_count = FREG_INITIAL;
    int reg_count = 0;
    int i = 0;
    int k = atoi(argv[1]);
    int r = atoi(argv[2]);

    // =============================================================================================
    // Print File
    // =============================================================================================

    printf("Loopinit:\n");
    for(i = 0; i < k; i++)
    {
        if(ld_dest_counter_cur == CONST_REG)
        {
            ++ld_dest_counter_cur;
            ++add_dest_counter_cur;
            ld_dest_counter_next += ADD_DEST_INCR+1;
            add_dest_counter_next += ADD_DEST_INCR+1;
        }
        else if(add_dest_counter_cur == CONST_REG)
        {
            ++add_dest_counter_cur;
            ld_dest_counter_next += ADD_DEST_INCR+1;
            add_dest_counter_next += ADD_DEST_INCR+1;
        }
        else
        {
            ld_dest_counter_next += LD_DEST_INCR;
            add_dest_counter_next += ADD_DEST_INCR;
        }

        printf("LD   F%d, %d(R1)\n", ld_dest_counter_cur, ldsd_offset_counter);
        printf("ADDD F%d, F%d, F%d\n", add_dest_counter_cur, ld_dest_counter_cur, CONST_REG);
        printf("SD   F%d, %d(R1)\n", add_dest_counter_cur, ldsd_offset_counter);

        ld_dest_counter_cur = ld_dest_counter_next;
        add_dest_counter_cur = add_dest_counter_next;
        ldsd_offset_counter += LDSD_OFFSET_INCR;

        rreg_count += RREG_INCR;
        freg_count += FREG_INCR;
        reg_count = rreg_count + freg_count;
    }
    printf("ADDI R1, R1, %d\n", ldsd_offset_counter);
    printf("BNEZ R1, R2, Loopinit\n");

    // =============================================================================================
    // Print Statistics
    // =============================================================================================

    printf("\n");
    printf("===================================================\n");
    printf("Number of Unrolls: %d\n", k);
    printf("Register Reuse Allowed: %s\n\n", r?"Yes":"No");
    printf("Number of Integer Registers: %d\n", rreg_count);
    printf("Number of Floating Point Registers: %d\n", freg_count);
    printf("Number of Registers: %d\n", reg_count);
    printf("===================================================\n");

    // =============================================================================================
    // End
    // =============================================================================================

    return 0;
}
