#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

void check_argument_num(int argc, char** argv)
{
    if(argc <= 3)
    {
        fprintf(stderr, "ERROR: In main(...): ");
        fprintf(stderr, "Too few arguments have been passed!\n");
        exit(1);
    }
    else if(argc >= 6)
    {
        fprintf(stderr, "ERROR: In main(...): ");
        fprintf(stderr, "Too many arguments have been passed!\n");
        exit(1);
    }
}

void check_argument_k(int argc, char** argv)
{
    int k = atoi(argv[1]);
    if(k < 1 || k > LOOP_ITER)
    {
        fprintf(stderr, "ERROR: In main(...): ");
        fprintf(stderr, "The number of unrolls is not in the proper range!\n");
        exit(1);
    }
    //
    //Include if k is restricted to integer divisors of 120.
    //
    //  else if((LOOP_ITER % k) != 0)
    //  {
    //      fprintf(stderr, "ERROR: In main(...): ");
    //      fprintf(stderr, "The number of unrolls is not a divisor of the number of loop iterations!\n");
    //      exit(1);
    //  }
}

void redirect_output(int argc, char** argv)
{
    if(argc == 5)
    {
        freopen(argv[4], "w", stdout);
    }
}

void print_code_unscheduled(int k, char label[BUF_SIZE], char instr[NUM_OF_INSTR][LOOP_ITER][BUF_SIZE])
{
    int i = 0;

    printf("%s", label);
    for(i = 0; i < k; i++)
    {
        printf("%s", instr[0][i]);
        printf("%s", instr[1][i]);
        printf("%s", instr[2][i]);
    }
    printf("%s", instr[3][0]);
    printf("%s", instr[4][0]);

    for(i = 0; i < LOOP_ITER % k; i++)
    {
        printf("%s", instr[0][i]);
        printf("%s", instr[1][i]);
        printf("%s", instr[2][i]);
    }
}

void print_code_scheduled(int k, char label[BUF_SIZE], char instr[NUM_OF_INSTR][LOOP_ITER][BUF_SIZE])
{
    int i = 0;

    printf("%s", label);
    for(i = 0; i < k; i++)
        printf("%s", instr[0][i]);
    for(i = 0; i < k; i++)
        printf("%s", instr[1][i]);
    for(i = 0; i < k; i++)
        printf("%s", instr[2][i]);
    printf("%s", instr[3][0]);
    printf("%s", instr[4][0]);

    for(i = 0; i < LOOP_ITER % k; i++)
        printf("%s", instr[0][i]);
    for(i = 0; i < LOOP_ITER % k; i++)
        printf("%s", instr[1][i]);
    for(i = 0; i < LOOP_ITER % k; i++)
        printf("%s", instr[2][i]);
}

void print_statistics(int k, int r, int s, int rreg_count, int freg_count)
{
    int reg_count = rreg_count + freg_count;

    printf("\n");
    printf("===================================================\n");
    printf("Number of Unrolls: %d\n", k);
    printf("Register Reuse Allowed: %s\n", r?"Yes":"No");
    printf("Scheduling Allowed: %s\n", s?"Yes":"No");
    printf("\n");
    printf("Number of Integer Registers: %d\n", rreg_count);
    printf("Number of Floating Point Registers: %d\n", freg_count);
    printf("Number of Registers: %d\n", reg_count);
    printf("===================================================\n");
}
