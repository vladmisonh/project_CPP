#include "../Random_2.h"

// g++ Random_2_test.c ../file_mod/Random_2.c -o test
// test.exe

int main() {
    srand(time(NULL)); // викоритовується для того щоб дійсно всі згенеровані числа не мали спільного (щоб звірити значення потрібно буде просто закоментувати)
    Random_2 test;
    generate_numbers_Random_2(&test);
    char c;
    NType n = 0, m = 0;

    printf("Select data entry method (console/file .txt)\nc/f: ");
    scanf("%c", &c);
    if (c == 'f') {
        const char* filename = "Random_2_test.txt";
        FILE* finp = fopen(filename, "r");
        fscanf(finp, "%u%u", &n, &m);
        fclose(finp);
    }

    FILE* fout = fopen("output.txt", "w");
    print_integer_Random_2(fout, "Next s_n: %u\n", next_s_n_Random_2(&test));
    print_double_Random_2(fout, "Next r_n: %lf\n", next_r_n_Random_2(&test));
    print_integer_Random_2(fout, "Random integer: %i\n", generate_integer_Random_2(&test));
    print_double_Random_2(fout, "Random real: %lf\n", generate_real_Random_2(&test));
    DType* v1_large = generate_vector_Random_2(&test, 1000);
    DType* v2_large = generate_vector_Random_2(&test, 1000);
    correlationCoefficient(v1_large, v2_large, 1000, fout);

    if (!n) {
        printf("Enter dimension of vectors: ");
        scanf("%u", &n);
    }
    DType* v1 = generate_vector_Random_2(&test, n);
    DType* v2 = generate_vector_Random_2(&test, n);
    correlationCoefficient(v1, v2, n, fout);

    if (!m) {
        printf("Enter dimension of sphere: ");
        scanf("%u", &m);
    }
    sphere_volume_Monte_Carlo_Random_2(&test, m, fout);

    fclose(fout);
    free(v1_large);
    free(v2_large);
    free(v1);
    free(v1);
    return 0;
}
