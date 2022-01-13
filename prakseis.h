#ifndef PRAKSEIS
#define PRAKSEIS
#define ROWS_MAX 20
#define COLS_MAX 20

struct matrix {
    bool invalid;
    double mat[ROWS_MAX][COLS_MAX];
    int rows, cols;
};

struct mattix adj(struct matrix A);
struct matrix inverse(struct matrix A);
struct matrix exp_matrix(struct matrix A, int power);


#endif // PRAKSEIS
