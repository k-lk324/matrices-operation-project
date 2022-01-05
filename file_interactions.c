#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#define ROWS_MAX 1000
#define COLS_MAX 1000

struct matrix
{
    int rows, cols;
    double mat[ROWS_MAX][COLS_MAX];
};

//δημιουργεί πίνακα με input απο τον χρήστη
struct matrix getmatrix()
{
    struct matrix y;

    //διαστάσεις
    printf("\nΔώσε διαστάσεις\nΓραμμές: ");
    scanf("%d", &y.rows);
    printf("Στήλες: ");
    scanf("%d", &y.cols);

    printf("\nΔώσε στοιχεία πίνακα χωρισμένα με κένο\n");
    printf ("π.χ. ένας πίνακας 2x3:\n1 0 45.87\n2 5.8 89\n\n");

    for (int i=0; i<y.rows; i++){
        for (int j=0; j<y.cols; j++)
            scanf("%lf", &y.mat[i][j]);
    }
    return y;
}


//δημιουργεί συστυχία και αποθηκεύει σε txt file
bool save_matrix(){

    //αναγνωριστικο πίνακα
    printf("\nΟρισμός αναγνωριστικού: ");
    char name[50];
    scanf("%s", name);

    //δημιουργία πίνακα
    struct matrix x = getmatrix();

    //κατέγραψε το όνομα του πίνακα για να μπορει να παρουσιαστεί ως διαθέσιμος
    FILE* am_file;
    am_file = fopen("available_matrix.txt", "a");
    if (am_file == NULL) return false;

    fprintf (am_file,"%s\n",name);
    fclose(am_file);

    //αν ειναι διανυσμα κατέγραψε όνομα και σε ξεχωριστό αρχειο
    if(x.cols == 0){
        FILE* vector_file;
        vector_file = fopen ("vectors.txt", "a");
        if (vector_file == NULL) return false;

        fprintf(vector_file,"%s\n",name);
        fclose(vector_file);
    }

    //πρόσθεσε την καταληξη ".txt" στο αναγνωριστικο
    strcat(name, ".txt");

    //δημιούργησε αρχείο "αναγνωριστικο".txt
    FILE *file;
    file = fopen(name, "w");

    //στις πρώτες 2 σειρες τύπωνει τις διαστάσεις
    fprintf(file, "%d\n%d\n", x.rows,x.cols);

    for (int i=0; i<x.rows; i++){
        for (int j=0; j<x.cols; j++){;
            fprintf(file, "%lf ", x.mat[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return true;
}

//τυπώνει τους διαθέσιμους πίνακες
bool show_matrixes(){
    FILE* AM;
    AM = fopen("available_matrix.txt", "r");

    char matrixName[50];
    //επανέλαβε μέχρι το τέλος του αρχείου
    while ((fscanf(AM,"%s",matrixName))!= EOF){
		//&& ελεγχος οτι δεν ειναι σφάλμα της fscanf
		
        printf("%s\n", matrixName);
     }

    return true;
}

