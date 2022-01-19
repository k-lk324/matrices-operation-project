#ifndef PRAKSEIS
#define PRAKSEIS
#define ROWS_MAX 20
#define COLS_MAX 20

struct matrix {
    bool invalid;
    bool vect;
    int rows, cols;
    double mat[ROWS_MAX][COLS_MAX];

};

struct matrix adj(struct matrix A);
struct matrix inverse_matrix(struct matrix A);
struct matrix exp_matrix(struct matrix A, int power);
double ixnos(struct matrix A);
struct matrix transpose_matrix();
struct matrix multiplication_matrix();
double det(struct matrix);
struct matrix cofactor(struct matrix, int, int);
struct matrix subtraction_matrix(struct matrix A, struct matrix B);
struct matrix sum_matrix(struct matrix A, struct matrix B);
struct matrix vector_product(struct matrix A, struct matrix B);
double esgin(struct matrix, struct matrix);
struct matrix vector_product(struct matrix A, struct matrix B);
struct matrix multiply_byNumber(struct matrix, double);


#endif // PRAKSEIS
