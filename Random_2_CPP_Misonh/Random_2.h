#ifndef __RANDOM_2_CPP__
#define __RANDOM_2_CPP__

#include <cmath>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <climits>
#include <iostream>

using namespace std;

/* описані всі типи даних*/
typedef double DType;
typedef int IType;
typedef unsigned NType;

/* описані всі функції*/
class Random_2 {

    NType a, c, m, s0, s_n;
    DType r_n;

public:

    Random_2();

    void generate_numbers_Random_2();

    NType next_s_n_Random_2();

    DType next_r_n_Random_2();

    IType generate_integer_Random_2();

    DType generate_real_Random_2();

    vector<DType> generate_vector_Random_2(NType n=1000);

    DType correlationCoefficient(vector<DType> X, vector<DType> Y, FILE* fout = 0);

    DType sphere_volume_Monte_Carlo_Random_2(NType N = 3, FILE* fout = 0);

    template<typename T>
    void print_Random_2(FILE* fout, const char* text, T num) {
        printf(text, num);
        fprintf(fout, text, num);
    }
};

#endif
