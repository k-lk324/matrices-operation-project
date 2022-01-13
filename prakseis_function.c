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


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#define ROWS_MAX 1000
#define COLS_MAX 1000
#define DEBUG

//υπολογίζει τον προσαρτημένο ενος πίνακα
//@επιστρέφει structure με τον προσαρτημένο
struct mattix adj(struct matrix A){
    struct matrix y = define_matrix();
    y.cols = A.cols;
    y.rows = A.rows;

    for (int i=0; i<y.rows; i++){
        for (int j=0; j<y.cols; j++){
            y.mat[i][j]= pow(-1,(i+1)+(j+1)) * A.mat[i][j];
        }
    }
    return traspose(y);

}

//υπολογιζει τον αντιστροφο ενος πίνακα
//@επιστρέφει structure με τον αντίστροφο
struct matrix inverse(struct matrix A){
    struct matrix X = define_matrix();
    X.cols = A.rows;
    X.rows = A.cols;

   if (det(A) == 0){
        puts("Ο πίνακας δεν ειναι αντιστρέψιμος");
        X.invalid = true;
    }
    else {
        for(int i=0; i<X.rows; i++)
            for(int j=0; j<X.rows; j++)
                X.mat[i][j] = (1/det(A)) * adj(A).mat[i][j];
    }
    return X;
}


//υπολογίζει εναν τετραγωνικο πίνακα εις την κάποια δύναμη
//@επιστρεφει τον εκθετικο
struct matrix exp(struct matrix A, int power){
    struct matrix y = A;

    if(A.cols == A.rows) {
        for(int i=0; i<power; i++)
            y = multiplication_matrix(y,A);
    }
    else{
        y.invalid = true;
    }

  return y;
}
