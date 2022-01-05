#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define ROWS_MAX 100
#define COLS_MAX 100
#define NOT_DEBUG


struct matrix
{
    float mat[ROWS_MAX][COLS_MAX];
    int rows,cols;
};
struct matrix getmatrix();

//1η επιλογη
bool save_matrix();

//2η επιλογή
bool show_matrixes();

char *prime_menu = "\tΠΡΑΞΕΙΣ ΠΙΝΑΚΩΝ\n\n1.Δημιουργία συστυχίας\n2.Προβολή διαθέσιμων πινάκων\n3.Πράξεις πινάκων\n4.Πράξεις διανυσμάτων\n\n";

//προβολή αρχικού μενού και επιστρέφει την επιλογή
int menu(char* menu);

void print_elements();

int main()
{
    enum {create_matrix, show_matrix,
          matrix_operations, vector_operations
         };

    //while(char != stop)
    while(true)
    {
        switch(menu(prime_menu))
        {

        case create_matrix:
            save_matrix();
            break;

        case show_matrix:
            show_matrixes();
            print_elements();
            break;

        case matrix_operations:
            //πραξεις πινάκων

            break;
        case vector_operations:
            //πράξεις διανυσμάτων
            break;
        default:
            printf("Η επιλογη που βάλατε δεν υπάρχει\n");
        }
    }

    return 0;
}

struct matrix getmatrix()
{
    struct matrix y;

    //διαστάσεις
    printf("\nΔώσε διαστάσεις\nΓραμμές: ");
    scanf("%d", &y.rows);
    printf("Στήλες: ");
    scanf("%d", &y.cols);

    //εισαγωγη στοιχειων
    printf("\nΔώσε στοιχεία πίνακα χωρισμένα με κένο\n");
    printf ("π.χ. ένας πίνακας 2x3:\n1 0 45.87\n2 5.8 89\n\n");

    for(int i=0;i<y.rows;i++)
    {
        for (int j=0; j<y.cols; j++)
        scanf("%f", &y.mat[i][j]);
    }

    return y;
}

//δημιουργεί συστυχία και αποθηκεύει σε txt file
bool save_matrix(){

    #ifdef DEBUG
    printf("save_matrix test 1 line 135");
    #endif // DEBUG

    //αναγνωριστικο πίνακα
    printf("\nΟρισμός αναγνωριστικού: ");
    char name[50];
    scanf("%s", name);

#ifndef DEBUGSTR

    //δημιουργία πίνακα
    struct matrix x =getmatrix();

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

    //πρώτες 2 σειρες τύπωσε τις διαστάσεις
    fprintf(file, "%d\n%d\n", x.rows,x.cols);

    for (int i=0; i<x.rows; i++){
        for (int j=0; j<x.cols; j++){;
            fprintf(file, "%lf ", x.mat[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    #endif // DEBUGSTR
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


int menu(char* menu)
{

    printf(prime_menu);

    printf("Επιλογή: ");
    int choice;
    fflush(stdin);
    scanf("%d", &choice);

    return choice-1;
}

void print_elements()
{
    printf("\nΕπιλογή πίνακα για προβολή: ");
    char name[50];
    scanf("%s", name);
    strcat(name, ".txt");

    FILE *fp;
    fp = fopen(name,"r");

    if (fp == NULL)
        printf("Ο πίνακας που επιλέξατε δεν υπάρχει\n");
    else
    {
        //οι πρώτες δύο γραμμές δίνουν τις διαστάσεις
        int r,c;
        fscanf(fp, "%d", &r);
        fscanf(fp, "%d", &c);

        for (int i=0; i<r; i++)
        {
            for (int j=0; j<c; j++)
            {
                double element;
                fscanf(fp, "%lf", &element);
                printf("%lf ", element);
            }
            printf("\n");
        }
        fclose (fp);
    }
}
