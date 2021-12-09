#ifndef __RANDOM_2_C__
#define __RANDOM_2_C__

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef double DType;
typedef int IType;
typedef unsigned NType;

typedef struct Random_2 {

    NType a, c, m, s0, s_n;
    DType r_n;

}Random_2;

void generate_numbers_Random_2(Random_2* self);

NType next_s_n_Random_2(Random_2* self);

DType next_r_n_Random_2(Random_2* self);

IType generate_integer_Random_2(Random_2* self);

DType generate_real_Random_2(Random_2* self);

DType* generate_vector_Random_2(Random_2* self, NType n);

DType correlationCoefficient(DType* X, DType* Y, NType n, FILE* fout);

DType sphere_volume_Monte_Carlo_Random_2(Random_2* self, NType N, FILE* fout);

void print_integer_Random_2(FILE* fout, const char* text, int num);

void print_double_Random_2(FILE* fout, const char* text, double num);

#endif
