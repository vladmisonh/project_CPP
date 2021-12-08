#include "../Random_2.h"

// g++ Random_2_test.cpp ../file_mod/Random_2.cpp -o test // ввечти в консолі щоб зкомпілювати .exe файл
// test.exe

int main() {
    srand(time(NULL));
    Random_2 test;
    char c;
    NType n = 0, m = 0;

    cout << "Select data entry method (console/file .txt)\nc/f: ";
    cin >> c;
    if (c == 'f') {
        string filename = "Random_2_test.txt";
        ifstream finp(filename);
        finp >> n >> m;
        finp.close();
    }

    FILE* fout = fopen("output.txt", "w");
    test.print_Random_2(fout, "Next s_n: %u\n", test.next_s_n_Random_2());
    test.print_Random_2(fout, "Next r_n: %lf\n", test.next_r_n_Random_2());
    test.print_Random_2(fout, "b) Random integer: %i\n", test.generate_integer_Random_2());
    test.print_Random_2(fout, "b) Random real: %lf\n", test.generate_real_Random_2());
    vector<DType> v1_large = test.generate_vector_Random_2();
    vector<DType> v2_large = test.generate_vector_Random_2();
    test.correlationCoefficient(v1_large, v2_large, fout);

    if (!n) {
        cout << "Enter dimension of vectors: ";
        cin >> n;
    }
    vector<DType> v1 = test.generate_vector_Random_2(n);
    vector<DType> v2 = test.generate_vector_Random_2(n);
    test.correlationCoefficient(v1, v2, fout);

    if (!m) {
        cout << "Enter dimension of sphere: ";
        cin >> m;
    }
    test.sphere_volume_Monte_Carlo_Random_2(m, fout);

    fclose(fout);
    return 0;
}
