#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#define LOOP_ITER 120
#define NUM_OF_INSTR 5
#define BUF_SIZE 255

void check_argument_num(int argc, char** argv);
void check_argument_k(int argc, char** argv);
void redirect_output(int argc, char** argv);

void print_code_unscheduled(int k, char label[BUF_SIZE], char instr[NUM_OF_INSTR][LOOP_ITER][BUF_SIZE]);
void print_code_scheduled(int k, char label[BUF_SIZE], char instr[NUM_OF_INSTR][LOOP_ITER][BUF_SIZE]);
void print_statistics(int k, int r, int s, int rreg_count, int freg_count);

#endif // HELPER_H_INCLUDED
