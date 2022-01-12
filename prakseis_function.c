#define ROWS_MAX 20
#define COLS_MAX 20

struct matrix{
    int rows,cols;
    double mat[ROWS_MAX][COLS_MAX];
};

//προσθέτει 2 πίνακες
//@επιστρέφει structure με τον πίνακα αθροίσματος
struct matrix sum_matrix(struct matrix A, struct matrix B) {

    struct matrix C;

    if(A.rows == B.rows && A.cols == B.cols) {
        C.rows = A.rows;
        C.cols = A.cols;

        for(int i=0; i<A.rows; i++)
            for(int j=0; j<A.rows; j++)
                C.mat[i][j]=A.mat[i][j]+ B.mat[i][j];
    }

    return C;
}

//αφαιρεί 2 πίνακες
//@επιστρέφει structure με τον πίνακα διαφοράς
struct matrix substraction_matrix(struct matrix A, struct matrix B) {
    struct matrix C;

    if(A.rows == B.rows && A.cols == B.cols) {
        C.rows = A.rows;
        C.cols = A.cols;

        for(int i=0; i<A.rows; i++)
            for(int j=0; j<A.cols; j++)
                C.mat[i][j]=A.mat[i][j]- B.mat[i][j];
    }

    return C;
}

//πολλαπλασιαζει 2 πίνακες
//@επιστρέφει structure με τον πίνακα γινόμενο
struct matrix multiplication_matrix(struct matrix A, struct matrix B) {
    struct matrix C;

    if(A.cols == B.rows) {
        int k = A.cols;
        C.rows = A.rows;
        C.cols = B.cols;

        int sum = 0;
        for(int i=0; i<C.rows; i++) {
            for(int j=0; j<C.cols; j++) {
                for(int l=0; l<k; l++)
                    sum += A.mat[i][l]*B.mat[l][j];
                C.mat[i][j]=sum;
                sum=0;
            }
        }
    }
    return C;
}

//βρίσκει τον ανάστροφο ενός πίνακα
//@επιστρέφει structure με τον ανάστροφο
struct matrix traspose(struct matrix A){
    struct matrix At;
    At.rows = A.cols;
    At.cols = A.rows;

    for(int i=0; i<A.rows; i++){
        for(int j=0; j<A.cols; j++){
            At.mat[j][i] = A.mat[i][j];
        }
    }
    return At;
}
