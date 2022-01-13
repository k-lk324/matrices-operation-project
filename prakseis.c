#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "prakseis.h"
#define ROWS_MAX 20
#define COLS_MAX 20
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
struct matrix exp_matrix(struct matrix A, int power){
    struct matrix y = A;

    if(A.cols == A.rows) {
        for(int i=0; i<power-1; i++)
            y = multiplication_matrix(y,A);
    }
    else{
        y.invalid = true;
    }

  return y;
}
