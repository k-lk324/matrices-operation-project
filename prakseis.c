#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "prakseis.h"
#define ROWS_MAX 20
#define COLS_MAX 20
#define NOT_DEBUG

struct matrix define_matrix();

/* Υπολογισμός προσαρτημένου πίνακα:
 *
 * Παράμετρος struct matrix A: πίνακας του οποίου υπολογίζεται ο προσαρτημένος
 * Επιστρέφει: structure με τον προσαρτημένο πίνακα
 */
struct matrix adj(struct matrix A) {
    struct matrix y = define_matrix();
    y.cols = A.cols;
    y.rows = A.rows;

    for(int i = 0; i < y.rows; i++) {
        for(int j = 0; j < y.cols; j++)
            y.mat[i][j] = pow(-1, (i + 1) + (j + 1)) * A.mat[i][j];
    }
    return transpose_matrix(y);
}

/* Υπολογισμός αντίστροφου πίνακα:
 * Έλεγχος αν ο πίνακας που δώθηκε είναι αντιστρέψιμος
 *
 * Παράμετρος struct matrix A: τετραγωνικός πίνακας του οποίου υπολογίζεται ο αντίστροφος
 * Επιστρέφει: structure με τον αντίστροφο πίνακα
 */
struct matrix inverse_matrix(struct matrix A) {
    struct matrix X = define_matrix();
    X.cols = X.rows = A.rows;

    if(det(A) == 0) {
        puts("Ο πίνακας δεν ειναι αντιστρέψιμος");
        X.invalid = true;
    } else {
        for(int i = 0; i < X.rows; i++)
            for(int j = 0; j < X.rows; j++)
                //Α^-1 = (1/|Α|) * adj(A)
                X.mat[i][j] = (1 / det(A)) * adj(A).mat[i][j];
    }
    return X;
}

/* Δυνάμεις πινάκων:
 * Πολλαπλασιασμός τετραγωνικού πίνακα με τον ευατό του ν φορές
 *
 * Παράμετρος struct matrix A: πίνακας του οποίου υπολογίζεται ο αντίστροφος
 * Παράμετρος int power: ακέραιος που δηλώνει την δύναμη που θα υψωθεί ο πίνακας
 * Επιστρέφει: structure με τον εκθετικό πίνακα
 */
struct matrix exp_matrix(struct matrix A, int power) {
    struct matrix y = A;

    if(A.cols == A.rows) {
        for(int i = 0; i < power; i++)
            y = multiplication_matrix(y, A);
    } else {
        y.invalid = true;
        puts("O πίνακας δεν είναι τετραγωνικός");
    }

    return y;
}

/* Ίχνος πίνακα:
 * Έλεγχος αν ο πίνακας είναι τετραγωνικός
 * Πρόσθεση στοιχείων της κύριας διαγωνίου
 *
 * Παράμετρος struct matrix A: structure με πίνακα
 * Επιστρέφει: το ίχνος ως δεκαδικό αριθμό
 */
double ixnos(struct matrix A) {

    double trace = 0;
    if(A.rows == A.cols) {
        for(int i = 0; i < A.rows; i++) {
            for(int j = 0; j < A.cols; j++) {
                if(i == j)
                    trace += A.mat[i][j];
            }
        }
    } else {
        puts("Ο πίνακας δεν είναι τετραγωνικός");
    }
    return trace;
}

//υπολογιζει το εσωτερικο γινομενο 2 διανυσματων
//@επιστρεφει το εσωτερικο γινομενο
double esgin(struct matrix A, struct matrix B) {

    double p = 0;
    if(A.rows == B.rows && A.cols == B.cols) {
        for(int i = 0; i < A.rows; i++)
            p += A.mat[i][0] * B.mat[i][0];
    } else
        puts("Τα διανύσματα δεν έχουν τις ίδιες διαστάσεις");

    return p;
}

//βρίσκει τον ανάστροφο ενός πίνακα
//@επιστρέφει structure με τον ανάστροφο
struct matrix transpose_matrix(struct matrix A) {
    struct matrix At = define_matrix();
    At.rows = A.cols;
    At.cols = A.rows;

    for(int i = 0; i < A.rows; i++) {
        for(int j = 0; j < A.cols; j++)
            At.mat[j][i] = A.mat[i][j];
    }
    return At;
}

//πολλαπλασιαζει 2 πίνακες
//@επιστρέφει structure με τον πίνακα γινόμενο
struct matrix multiplication_matrix(struct matrix A, struct matrix B) {
    struct matrix C = define_matrix();

    if(A.cols == B.rows) {
        int k = A.cols;
        C.rows = A.rows;
        C.cols = B.cols;

        int sum = 0;
        for(int i = 0; i < C.rows; i++) {
            for(int j = 0; j < C.cols; j++) {
                for(int l = 0; l < k; l++)
                    sum += A.mat[i][l] * B.mat[l][j];
                C.mat[i][j] = sum;
                sum = 0;
            }
        }
    } else C.invalid = true;

    return C;
}

//αφαιρεί 2 πίνακες
//@επιστρέφει structure με τον πίνακα διαφοράς
struct matrix subtraction_matrix(struct matrix A, struct matrix B) {
    struct matrix C = define_matrix();

    if(A.rows == B.rows && A.cols == B.cols) {
        C.rows = A.rows;
        C.cols = A.cols;
        if(C.cols == 1)
            C.vect = true;

        for(int i = 0; i < A.rows; i++)
            for(int j = 0; j < A.cols; j++)
                C.mat[i][j] = A.mat[i][j] - B.mat[i][j];
    } else C.invalid = true;

    return C;
}

//προσθέτει 2 πίνακες
//@επιστρέφει structure με τον πίνακα αθροίσματος
struct matrix sum_matrix(struct matrix A, struct matrix B) {

    struct matrix C = define_matrix();

    if(A.rows == B.rows && A.cols == B.cols) {
        C.rows = A.rows;
        C.cols = A.cols;
        if(C.cols == 1)
            C.vect = true;

        for(int i = 0; i < A.rows; i++)
            for(int j = 0; j < A.rows; j++)
                C.mat[i][j] = A.mat[i][j] + B.mat[i][j];
    } else {
        C.invalid = true;
        puts("Οι πίνακες δεν έχουν τις ίδιες διαστάσεις");
    }

    return C;
}

//υπολογίζει ορίζουσα ενός πίνακα
//@επιστρέφει την ορίζουσα
double det(struct matrix A) {
#ifdef DEBUG
    printf("\nΑΡΧΗ ΤΗΣ DET\n");
#endif // DEBUG
    int n = A.rows;
    double d = 0;
    double *pd = &d;

    if(n == 1)
        *pd = A.mat[0][0];
    else {
        for(int j = 0; j < n; j++) {
            int sign = pow(-1, (j + 1) + 1);
            printf("sign: %d\n", sign);
            *pd += sign * A.mat[0][j] * det(cofactor(A, 0, j));
        }
    }
    return *pd;
}

//βρίσκει τον συμπαράγοντα πίνακα Αxy
//@επιστρέφει structure με τον συμπαράγοντα
struct matrix cofactor(struct matrix A, int x, int y) {
#ifdef DEBUG
    puts("αρχη της cofactor");
#endif // DEBUG

    int n = A.rows;
    struct matrix B = define_matrix();
    B.rows = B.cols = n - 1;
    int a = 0, b = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i != x && j != y) {
                B.mat[a][b] = A.mat[i][j];
                if(++b == n - 1) {
                    a++;
                    b = 0;
                }
            }
        }
    }
    return B;
}

//υπολογίζει εξωτερικό γινόμενο 2 διανυσματων
//@επιστρέφει structure με το εξωτερικο γινομενο
struct matrix vector_product(struct matrix A, struct matrix B) {
    //δημιουργία πίνακα αποτελέσματος
    struct matrix C = define_matrix();
    C.vect = true;
    C.cols = 1;
    C.rows = 3;

    //αν οι συστοιχίες είναι διανύσματα και έχουν 3 διαστάσεις
    if(A.cols == 1 && B.cols == 1 && A.rows == 3 && B.rows == 3) {

        C.mat[0][0] = A.mat[1][0] * B.mat[2][0] - A.mat[2][0] * B.mat[1][0];
        C.mat[1][0] = A.mat[2][0] * B.mat[0][0] - A.mat[0][0] * B.mat[2][0];
        C.mat[2][0] = A.mat[0][0] * B.mat[1][0] - A.mat[1][0] * B.mat[0][0];
    } else {
        puts("Το εξωτερικό γινόμενο επιτρέπει μόνο διανύσματα 3 διαστάσεων");
        C.invalid = true;
    }
    return C;
}
