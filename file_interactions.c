#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*int rowsOfMatrix(char *filename); //filename --> αναγνωριστικο
int colsOfMatrix(char *filename); */

//δημιουργεί συστυχία και αποθηκεύει σε txt file
bool save_matrix(){

    //αναγνωριστικο πίνακα
    printf("\nΟρισμός αναγνωριστικού: ");
    char name[50];
    scanf("%s", name);

    //διαστάσεις
    int r,c;
    printf("\nΔώσε διαστάσεις\nΓραμμές: ");
    scanf("%d", &r);
    printf("Στήλες: ");
    scanf("%d", &c);

    //κατέγραψε το όνομα του πίνακα για να μπορει να παρουσιαστεί ως διαθέσιμος
    FILE* am_file;
    am_file = fopen("available_matrix.txt", "a");
    fprintf (am_file,"%s\n",name);
    fclose(am_file);

    //αν ειναι διανυσμα κατέγραψε όνομα και σε ξεχωριστό αρχειο
    if(c == 0){
        FILE* vector_file;
        vector_file = fopen ("vectors.txt", "a");
        fprintf(vector_file,"%s\n",name);
        fclose(vector_file);
    }


    //πρόσθεσε την καταληξη ".txt" στο αναγνωριστικο
    strcat(name, ".txt");

    //δημιούργησε αρχείο "αναγνωριστικο".txt
    FILE *file;
    file = fopen(name, "w");

    //πρώτες 2 σειρες τύπωσε τις διαστάσεις
    fprintf(file, "%d\n%d\n", r,c);

    //δωσε τα στοιχεια του πίνακα και τύπωσε τα στο αρχειο
    printf("\nΔώσε στοιχεία πίνακα χωρισμένα με κένο\n");
    printf ("π.χ. ένας πίνακας 2x3:\n1 0 45\n2 5 89\n\n");

        for (int i=0; i<r; i++){
            for (int j=0; j<c; j++){
                double element;
                scanf("%lf", &element);
                fprintf(file, "%lf ", element);
            }

            fprintf(file, "\n");
        }

    //κλεισε το αρχειο
    fclose(file);


    return true;
}

//τυπώνει τους διαθέσιμους πίνακες
bool show_matrixes(){
    FILE* AM;
    AM = fopen("available_matrix.txt", "r");

    char matrixName[50];
    //επανέλαβε μέχρι το τέλος του αρχείου
     while ((fscanf(AM,"%s",matrixName))!=EOF){
        printf("%s\n", matrixName);
     }

    return true;
}
