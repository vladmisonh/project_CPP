#include "../Random_2.h"


/*а) Створити функцію, що буде генерувати числа а, с, m, s0, що
задовольняють вказаним умовам*/
void generate_numbers_Random_2(Random_2* self) {
    NType k = 16 + rand() % 16;             // k з [16, 31] тобто значень які є задовільними для роботи С++, тобто не виходять за допустимі межі роботи
    if (k == 31) {
        self->m = INT_MAX;
    } else { self->m = pow(2, k); }         // m - ПАРНЕ ЗАВЖДИ (оскільки це якийсь степінь двійки)
    self->c = rand() % self->m;
    if (self->c % 2 == 0)                    // якщо с парне то (c, m) != 1 і тоді
        self->c += 1;                       // робимо непарне (адже парне число не буде взаємyо простим з парним м)
    self->a = 4*(rand() % (self->m/4)) + 1;
    self->s0 = rand() % self->m;              // радномне s0 < m
    self->s_n = self->s0;

    //printf("m = %d, a = %d, c = %d, s0 = %d\n", self->m, self->a, self->c, self->s0);        // якщо потрібно дізнатись які згенерувались числа
}

/* Наступний член послідовності s_n */
NType next_s_n_Random_2(Random_2* self) {
    self->s_n = (self->a*self->s_n + self->c) % self->m;
    return self->s_n;
}

/* Наступний член послідовності r_n */
DType next_r_n_Random_2(Random_2* self) {
    self->r_n = (DType)(self->s_n + 1)/(self->m + 1);
    next_s_n_Random_2(self);
    return self->r_n;
}

/* б) створити на базі цієї послідовності генератори випадкових цілих чисел  */
IType generate_integer_Random_2(Random_2* self) {
    IType a = INT_MAX*(2*(0.5 - next_r_n_Random_2(self)));
    return a;
}

/* та генератор випадкових дійсних чисел */
DType generate_real_Random_2(Random_2* self) {
    DType a = (DType)generate_integer_Random_2(self) - next_r_n_Random_2(self);
    return a;
}

/* г) на базі даного ГВЧ створить метод, що генерує n-вимірні випадкові
вектори дійсних чисел, кожні дві координтати яких є некорельовані.  (якщо n не вказано то 1000) */
DType* generate_vector_Random_2(Random_2* self, NType n) {
    DType* v = (DType*) malloc(n * sizeof *v);
    for (IType i = 0; i < n; i++)
        v[i] = generate_real_Random_2(self);
    return v;
}

/* Напишить код, який перевіряє на достатньо великій вибірці, що вони
дійсно некорельовані. */
// Коефіціент кореляції двух векторів X и Y
DType correlationCoefficient(DType* X, DType* Y, NType n, FILE* fout) {
    DType sum_X = 0, sum_Y = 0, sum_XY = 0;
    DType squareSum_X = 0, squareSum_Y = 0;

    for (IType i = 0; i < n; i++) {
        sum_X = sum_X + X[i];
        sum_Y = sum_Y + Y[i];
        sum_XY = sum_XY + X[i] * Y[i];
        squareSum_X = squareSum_X + X[i] * X[i];
        squareSum_Y = squareSum_Y + Y[i] * Y[i];
    }

    DType corr = (DType)(n*sum_XY - sum_X*sum_Y)/sqrt((n*squareSum_X - sum_X*sum_X)*(n*squareSum_Y - sum_Y*sum_Y));
    printf("Correlation coefficient of %u-dimensional vectors = %.1lf\n", n, corr);
    if (fout)
        fprintf(fout, "Correlation coefficient of %u-dimensional vectors = %.1lf\n", n, corr);
    return corr;
}

/*д) На базі методу Монте-Карло підрахуйте об“єм n-вимірної сфери */
DType sphere_volume_Monte_Carlo_Random_2(Random_2* self, NType N, FILE* fout) {
    DType vol = 0;
    DType hit = 0;
    DType n_vol = pow(M_PI, N/2.0)/exp(lgamma(N/2.0 + 1.0));    // стандартна формула обрахунку об'єму n-вимірної сфери

    for (IType i = 0; i < 100000; i++) {
        DType r = 0;                                             // квадрат довжини вектора розмірності N = m
        for (IType j = 0; j < N; j++) {                          // j + 1 належить [1, N] - координат вектора
            DType x = 2*(next_r_n_Random_2(self) - 0.5);         // значення в інтервалі (0, 1) - координата вектора
            r += x*x;
        }
        if (sqrt(r) < 1)                                        // r - довжина вектора в квадрате
            hit += 1;                                             // якщо довжина вектора < 1 (радіуса сфери, для методу Монте-Карло) => вектор
    }                                                            // всередині и інкрементуємо hit (підрахунок векторів всередині сфери)

    vol = (pow(2, N)*hit)/100000;
    printf("Volume of a %u-sphere: %lf\n", N, vol);
    printf("Actual volume: %lf\n", n_vol);
    printf("Math error: %lf\n", fabs(n_vol - vol));
    if (fout) {
        fprintf(fout, "Volume of a %u-sphere: %lf\n", N, vol);
        fprintf(fout, "Actual volume: %lf\n", n_vol);
        fprintf(fout, "Math error: %lf\n", fabs(n_vol - vol));
    }
    return vol;
}

void print_integer_Random_2(FILE* fout, const char* text, int num) {
    printf(text, num);
    fprintf(fout, text, num);
}

void print_double_Random_2(FILE* fout, const char* text, double num) {
    printf(text, num);
    fprintf(fout, text, num);
}
