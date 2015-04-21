// Note that this code has been written to produce a solution that utilizes a minimal number of
// registers. Although this requires some special handling of the register numbering at the
// beginning of the unrolling due to the placement of the constant register, it means that
// constraints on the number of registers used can be met without extra register renaming.

#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

int main(int argc, char **argv)
{
    // =============================================================================================
    // Check and Collect Input Arguments
    // =============================================================================================

    check_argument_num(argc, argv);
    check_argument_k(argc, argv);
    redirect_output(argc, argv);

    int k = atoi(argv[1]);
    int r = atoi(argv[2]);
    int s = atoi(argv[3]);

    // =============================================================================================
    // Declare Constants
    // =============================================================================================

    const int CONST_REG = 2;

    const int LD_DEST_INITIAL = r ? 0 : 0;
    const int LD_DEST_INCR = r ? 1 : 2;
    const int ADD_DEST_INITIAL = r ? 0 : 1;
    const int ADD_DEST_INCR = r ? 1 : 2;

    const int LDSD_OFFSET_INITIAL = 0;
    const int LDSD_OFFSET_INCR = -8;

    const int RREG_INITIAL = 2;
    const int RREG_INCR = r ? 0 : 0;
    const int FREG_INITIAL = 1;
    const int FREG_INCR = r ? 1 : 2;

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

    int i = 0;

    char label[BUF_SIZE];
    char instr[NUM_OF_INSTR][LOOP_ITER][BUF_SIZE];

    // =============================================================================================
    // Generate Code and Statistics
    // =============================================================================================

    // Assign label to string
    sprintf(label, "Loopinit:\n");

    for(i = 0; i < k; i++)
    {
        // Check for and deal with register conflicts with constant register
        if(ld_dest_counter_cur == CONST_REG)
        {
            // Shift both the ld destination and the add destination forward
            ld_dest_counter_cur += 1;
            add_dest_counter_cur += 1;

            // Shift the next values by one to account for the conflict
            // Then shift the next values by the appropriate offset
            ld_dest_counter_next += LD_DEST_INCR+1;
            add_dest_counter_next += ADD_DEST_INCR+1;
        }
        else if(add_dest_counter_cur == CONST_REG)
        {
            // Shift only the add destination forward
            add_dest_counter_cur += 1;

            // Shift the next values by one to account for the conflict
            // Then shift the next values by the appropriate offset
            ld_dest_counter_next += LD_DEST_INCR+1;
            add_dest_counter_next += ADD_DEST_INCR+1;
        }
        else
        {
            // Shift the next values by the appropriate offset
            ld_dest_counter_next += LD_DEST_INCR;
            add_dest_counter_next += ADD_DEST_INCR;
        }

        // Assign repeated instructions to strings
        sprintf(instr[0][i], "LD   F%d, %d(R1)\n", ld_dest_counter_cur, ldsd_offset_counter);
        sprintf(instr[1][i], "ADDD F%d, F%d, F%d\n", add_dest_counter_cur, ld_dest_counter_cur, CONST_REG);
        sprintf(instr[2][i], "SD   F%d, %d(R1)\n", add_dest_counter_cur, ldsd_offset_counter);

        // Update the counters
        ld_dest_counter_cur = ld_dest_counter_next;
        add_dest_counter_cur = add_dest_counter_next;
        ldsd_offset_counter += LDSD_OFFSET_INCR;
        rreg_count += RREG_INCR;
        freg_count += FREG_INCR;
    }

    // Assign non-repeated instructions to strings
    sprintf(instr[3][0], "ADDI R1, R1, %d\n", ldsd_offset_counter);
    sprintf(instr[4][0], "BNEZ R1, R2, Loopinit\n");

    // =============================================================================================
    // Print Code and Statistics
    // =============================================================================================

    if(s == 0)
        print_code_unscheduled(k, label, instr);
    else
        print_code_scheduled(k, label, instr);

    print_statistics(k, r, s, rreg_count, freg_count);

    // =============================================================================================
    // End
    // =============================================================================================

    return 0;
}
