//this file includes the main function
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "prakseis.h"
#define ROWS_MAX 20
#define COLS_MAX 20
#define NOT_DEBUG
#define NOT_DEBUGSTR

//starting menu
char *prime_menu = "\tMATRIX OPERATIONS\n\n\
1.Create matrix\n\
2.Show availabel matrices\n\
3.Load matrix\n\
4.Delete matrix\n\
5.Matrix operations\n\
6.Vector operations\n\
7.Exit\n\n";

enum home {createMatrix = 1, showMatrix, ld_matrix, del, matrixOperations, vectorOperations, end};

//menu for matrix operations
char *matrixOp_menu = "\n\
1.Addition\n\
2.Subraction\n\
3.Multiplication with matrix\n\
4.Multiplication with number\n\
5.Determinant\n\
6.Inverse\n\
7.Transpose\n\
8.Exponential\n\
9.Trace\n\
10.Return to starting menu\n\n";

//cases for matrix operations
enum matrixOp {sum = 1, subtraction, multiplicationMatrix, multiplicationNumber, determinant, inverse, transpose, degree, trace, backToHome};

//menu for vector operations
char *vectOp_menu = "\n\
1.Addition\n\
2.Subtraction\n\
3.Dot Product\n\
4.Cross Product\n\
5.Return to Start Menu\n\n";

//cases for vector operations
enum vectorOp {sum2 = 1, subtraction2, dotProduct, vectorProduct, backToHome2};

void startMsg(void);
int menu(char* menu);

//functions for interacting with structure matrix
struct matrix define_matrix(void);
struct matrix getmatrix(bool);
struct matrix choose_matrix(char*, bool);
struct matrix matrix_operations(int);
struct matrix vector_operations(int);
void print_matrix(struct matrix);


//functions for file interacting
bool save_matrix(struct matrix x);
char *show_matrixes(void);
bool load_matrix(void);
void delete_matrix(void);
void print_elements(char*);
bool delete_matrixName(char* name);

int main(void) {
    startMsg();
    bool stop = false;

    //until the user chooses to stop the program
    while(!stop) {
        fflush(stdin);

        //Start Menu choices
        switch(menu(prime_menu)) {
            case createMatrix:
                //create matrix
                {
                    bool error = !save_matrix(getmatrix(false));
                    if(error)
                        puts("Error");
                }
                break;

            case showMatrix:
                //view available matrices
                {
                    char *matrixForShow = show_matrixes();
                    if(*matrixForShow != '\0')
                        print_elements(matrixForShow);
                }
                break;

            case ld_matrix:
                //load matrix from file
                if(!load_matrix())
                    printf("Unable to open file\n");
                break;

            case matrixOperations:     
                {
                    int choice = menu(matrixOp_menu);
                    struct matrix result = matrix_operations(choice);
                    //view result
                    print_matrix(result);

                    fflush(stdin);
                    //save
                    char answer = '\0';
                    if(!result.invalid) {
                        do {
                            printf("Save array? [y/n]");
                            answer = getchar();

                            if(answer == 'y')
                                save_matrix(result);
                            else if(answer == 'n') {}
                            else
                                puts("This isn't a valid option.");
                        } while(answer != 'n' && answer != 'y');
                    }
                }
                break;
            case vectorOperations:
                {
                    int choice = menu(vectOp_menu);
                    struct matrix result = vector_operations(choice);

                    //view result
                    print_matrix(result);

                    //save result
                    char answer = '\0';
                    if(!result.invalid) {
                        do {
                            printf("Save array?[y/n]");
                            fflush(stdin);
                            answer = getchar();

                            if(answer == 'y')
                                save_matrix(result);
                            else if(answer == 'n') {}
                            else
                                puts("This isn't a valid option");
                        } while(answer != 'n' && answer != 'y');
                    }
                }
                break;

            case del:
                //delete array
                delete_matrix();
                break;

            case end:
                //exist program
                stop = true;
                break;

            default:
                puts("This isn't a valid option");
        }

        //print 3 empty lines
        for(int i = 0; i < 3; i++)
            printf("\n");
    }
    return 0;
}

/* Εισαγωγή πίνακα από χρήστη:
 * Εισαγωγή των διαστάσεων της συστοιχίας (με έλεγχο ορίων των διαστάσεων)
 * και εισαγωγή των στοιχείων τους
 *
 * Παράμετρος bool vect: αληθές όταν ζητείται μονοδιάστατος πίνακας
 * Επιστρέφει: struct με τον πίνακα που έχει εισάγει ο χρήστης
 */
struct matrix getmatrix(bool vect) {
    struct matrix y = define_matrix();
    do {
        //διαστάσεις
        if(!vect) {
            printf("\nΟρισμός διαστάσεων\nΠροσοχή! Μέγιστες διαστάσεις: %dx%d\n\nΓραμμές: ", ROWS_MAX, COLS_MAX);
            scanf("%d", &y.rows);
            y.rows = abs(y.rows);
            printf("Στήλες: ");
            scanf("%d", &y.cols);
            y.cols = abs(y.cols);
        } else {
            printf("\nΟρισμός διαστάσεων\nΜέγιστες διαστάσεις: %d \n", ROWS_MAX);
            scanf("%d", &y.rows);
            y.rows = abs(y.rows);
            y.cols = 1;

        }
    } while(y.rows > ROWS_MAX || y.cols > COLS_MAX);

    //εισαγωγη στοιχειων
    printf("\nΣυμπλήρωση τιμών:\nΔώσε στοιχεία πίνακα χωρισμένα με κένο ή αλλαγή γραμμής\n");
    printf("π.χ. ένας πίνακας 2x3:\n1 0 45.87\n2 5.8 89\n\n");

    for(int i = 0; i < y.rows; i++) {
        for(int j = 0; j < y.cols; j++)
            scanf("%lf", &y.mat[i][j]);
    }
    return y;
}

/* Αποθήκευση Πίνακα σε αρχείο:
 * Εισαγωγή αναγνωριστικού από τον χρήστη και
 * έλεγχος αν είχε χρησιμοποιηθεί ξανά
 * Καταγραφή αναγνωριστικού στις διαθέσιμες συστοιχίες
 * Δημιουγία αρχείου συστοιχίας και συμπλήρωση διαστάσεων και τιμών
 *
 * Παράμετρος struct matrix x: stucture με την συστοιχίας
 * που πρόκειται να αποθηκευτεί
 * Επιστρέφει: false αν παρουσιαστεί σφάλμα και true αν εκτελεστεί επιτυχώς
 */
bool save_matrix(struct matrix x) {
    char name[50];
    bool unique_name = true;

    //άνοιγμα αρχείου διαθέσιμων συστοιχιών σε read mode
    FILE* amReadFp;
    amReadFp = fopen("available_matrix.txt", "r");

    if(amReadFp != NULL) {

        do {
            unique_name = true;
            rewind(amReadFp);

            //Eισαγωγή αναγνωριστικού από τον χρήστη
            printf("\nΟρισμός αναγνωριστικού: ");
            scanf("%s", name);

            //επανάληψη μέχρι το τέλος του αρχείου
            while(!feof(amReadFp)) {
                char matrixName[50];
                fscanf(amReadFp, "%s", matrixName);

                //αν το αναγνωριστικό που δώθηκε είναι ίδιο με ήδη υπάρχον αναγνωριστικό
                if(strcmp(name, matrixName) == 0) {
                    printf("Το αναγνωριστικό %s χρησιμοποιείται ήδη", name);
                    unique_name = false;
                    break;
                }
            }
        } while(!unique_name);

        //κλείσιμο αρχείου διαθέσιμων συστοιχιών
        fclose(amReadFp);
    } else{
            //Eισαγωγή αναγνωριστικού από τον χρήστη
            printf("\nΟρισμός αναγνωριστικού: ");
            scanf("%s", name);
    }

    //άνοιγμα αρχείου διαθέσιμων συστοιχιών σε append mode
    FILE* am_file;
    am_file = fopen("available_matrix.txt", "a");
    if(am_file == NULL)
        return false;

    //καταγραφή αναγνωριστικού
    fprintf(am_file, "%s\n", name);
    //κλείσιμο αρχείου διαθέσιμων συστοιχιών
    fclose(am_file);

    //πρόσθεσε την κατάληξη txt στο αναγνωριστικό
    strcat(name, ".txt");

    //δημιουργία αρχείου "αναγνωριστικο".txt σε write mode
    FILE *file;
    file = fopen(name, "w");
    if(file == NULL)
        return false;

    //πρώτες 2 σειρές τύπωσε τις διαστάσεις
    fprintf(file, "%d\n%d\n", x.rows, x.cols);

    for(int i = 0; i < x.rows; i++) {
        for(int j = 0; j < x.cols; j++)
            fprintf(file, "%lf ", x.mat[i][j]);
        fprintf(file, "\n");
    }
    //κλείσιμο αρχείο συστοιχίας
    fclose(file);
    return true;
}

/* Προβολή διαθέσιμων πινάκων:
 * Άνοιγμα αρχείου διαθέσιμων πινάκων
 * και προβολή των αναγνωριστικών πινάκων
 *
 * Επιστρέφει: false αν παρουσιαστεί σφάλμα και true αν εκτελεστεί επιτυχώς
 */
char *show_matrixes(void) {
    //array με τα αναγνωριστικά των διαθέσιμων συστοιχιών
    static char matrix_catalog[50][50];

    //άνοιγμα αρχείου σε read mode
    FILE* AM;
    AM = fopen("available_matrix.txt", "r");
    if(AM == NULL) {
        puts("Αδυναμία ανοίγματος αρχείου");
        return "";
    }

    char matrixName[50];
    int cnt = 0 ;
    printf("0.Ακύρωση επιλογής\n");
    //επανέλαβε μέχρι το τέλος του αρχείου
    for(int i = 0; (fscanf(AM, "%s", matrixName)) != EOF; i++) {
        cnt++;
        strcpy(matrix_catalog[i], matrixName);
        printf("%d.%s\n", i + 1, matrixName);
    }

    //έλεγχος ότι δεν είναι σφάλμα της scanf
    if(!feof(AM)) {
        fclose(AM);
        puts("Παρουσιάστηκε σφάλμα");
    }

    //εισαγωγή επιλογής από τον χρήστη
    int matrix_choice = menu("\n");

    while(matrix_choice > cnt) {
        puts("Η επιλογή δεν υπάρχει");
        matrix_choice = menu("\n");
    }

    if(matrix_choice == 0)
        return "\0";

    //κλείσιμο αρχείου
    fclose(AM);

    return matrix_catalog[matrix_choice - 1];
}

/* Φόρτωση πίνακα:
 * Εισαγωγή αναγνωριστικού συστοιχίας απο το χρήστη
 * και συμπλήρωση αναγνωριστικού συστοιχίας στο αρχείο διαθέσιμων συστοιχιών
 *
 * Επιστρέφει: false αν παρουσιαστεί σφάλμα και true αν εκτελεστεί επιτυχώς
 */
bool load_matrix(void) {
    //οδηγίες για φόρτωση αρχείου
    printf("\nOδηγίες:\n\
-Το αρχείο πρέπει να έχει επέκταση txt και στο ίδιο directory\n\
-Ο αριθμός των γραμμών να αναγράφεται στην πρώτη γραμμή\n\
-Ο αριθμός των στηλών να αναγράφεται στην δεύτερη γραμμή\n\
-Μέγιστες δυνατές διαστάσεις: %dx%d\n\n", ROWS_MAX, COLS_MAX);

    //εισαγωγή αναγνωριστικού συστοιχίας από το χρήστη
    char matrixName[50];
    char filename[50];
    printf("Εισαγωγή αναγνωριστικού συστοιχίας (χωρίς επέκταση txt): ");
    scanf("%s", matrixName);

    strcpy(filename, matrixName);
    strcat(filename, ".txt");

    //άνοιγμα αρχείου σε read mode
    FILE *fp;
    fp = fopen(filename, "r");

    //αν υπάρξει αδυναμία άνοιγμα αρχείου
    if(fp == NULL)
        return false;

    //κλείσιμο αρχείου συστοιχίας
    fclose(fp);

    //άνοιγμα αρχείου διαθέσιμων πινάκων σε append mode
    FILE* am_file;
    am_file = fopen("available_matrix.txt", "a");
    if(am_file == NULL)
        printf("Αδυναμία φόρτωσης συστοιχίας\n");

    //συμπλήρωση αναγνωριστικού συστοιχίας στις διαθέσιμες συστοιχίες
    fprintf(am_file, "%s\n", matrixName);

    //κλείσιμο αρχείου διαθέσιμων πίνακων
    fclose(am_file);
    puts("Επιτυχής φόρτωση συστοιχίας");
    return true;
}

/* Προβολή μενού:
 * Προβολή επιλογών και
 * εισαγωγή αριθμού επιλογής από το χρήστη
 *
 * Παράμετρος char *menu: κείμενο προβολής επιλογών
 * Επιστρέφει: τον αριθμό επιλογής
 */
int menu(char *menu) {
    int choice;
    printf("%s", menu);
    printf("Επιλογή: ");

    fflush(stdin);
    scanf("%d", &choice);
    return abs(choice);
}

/* Προβολή στοιχείων συστοιχίας από αρχείο:
 * Εισαγωγή αναγνωριστικού συστοιχίας από τον χρήστη,
 * άνοιγμα αρχείου συστοιχίας και προβολή στοιχείων
 */
void print_elements(char *name) {
    strcat(name, ".txt");

    FILE *fp;
    fp = fopen(name, "r");

    if(fp == NULL)
        printf("Ο πίνακας που επιλέξατε δεν υπάρχει\n");
    else {
        //οι πρώτες δύο γραμμές δίνουν τις διαστάσεις
        int r, c;
        fscanf(fp, "%d", &r);
        fscanf(fp, "%d", &c);

        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                double element;
                fscanf(fp, "%lf", &element);
                printf("%.3lf ", element);
            }
            printf("\n");
        }
        fclose(fp);
    }
}

/* Διαγραφή αναγνωριστικού:
 * Μεταφορά όλων των αποθηκευμένων αναγνωριστικών σε νέο αρχείο,
 * έκτος από το αναγνωριστικό που πρόκειται να διαγραφτεί
 * Διαγραφή αρχικού αρχείου και μετονομασία του 2ου σε "available_matrix.txt"
 *
 * Παράμετρος char *name: αναγνωριστικό που πρόκειται να διαγραφτεί
 * Επιστρέφει: false αν παρουσιαστεί σφάλμα και true αν εκτελεστεί επιτυχώς
 */
bool delete_matrixName(char *name) {
    FILE *am_fp, *copy_fp;
    char matrixName[50];
    char available_matrix[] = "available_matrix.txt";

    //άνοιγμα αρχείου σε read mode
    am_fp = fopen(available_matrix, "r");
    //άνοιγμα αρχείου σε write mode
    copy_fp = fopen("copy.txt", "w");

    while(fscanf(am_fp, "%s", matrixName) != EOF) {
        //έκτος από το αναγνωριστικό που πρόκειται να διαγραφτεί
        if(strcmp(name, matrixName) != 0) {
            //αντέγραψε όλες τις υπόλοιπες γραμμές στο copy.txt
            fprintf(copy_fp, "%s\n", matrixName);
        } else
            printf("Ο πίνακας εντωπίστηκε\n");
    }

    //έλεγχος ότι δεν είναι σφάλμα της fscanf
    if(!feof(am_fp)) {
        fclose(am_fp);
        printf("Παρουσιάστηκε σφάλμα\n");
        return false;
    }

    //κλείσιμο αρχείων
    fclose(am_fp);
    fclose(copy_fp);

    //διαγραφή αρχικού αρχείου
    if(remove(available_matrix) != 0)
        return false;

    //μετονομασία του copy.txt σε available_matrix.txt
    rename("copy.txt", "available_matrix.txt");

    return true;
}

/* Διαγραφή συστοιχίας:
 * Εισαγωγή αναγνωριστικού συστοιχίας για διαγραφή από το χρήστη
 * Διαγραφή αναγνωριστικού και διαγραφή αρχείου συστοιχίας
 */
void delete_matrix(void) {
    char *name = show_matrixes();
    if(*name != '\0') {

        char filename[50];
        strcpy(filename, name);

        //προσθήκη κατάληξης ".txt"
        strcat(filename, ".txt");

        //διαγραφή αναγνωριστικού
        bool check1 = delete_matrixName(name);
        //διαγραφή αρχείου
        bool check2 = remove(filename) == 0;

        //έλεγχος διαγραφής
        if(check1 && check2)
            printf("Διαγράφτηκε επιτυχώς\n");
        else
            printf("Αδυναμία διαγραφής\n");
    }
}

/* Επιλογή συστοιχίας:
 * Επιλογή χρήστη αν επιθυμεί να χρησιμοποιήσει μία ήδη υπάρχουσα συστοιχία
 * ή να εισάγει μία εκείνη την στιγμή
 *
 * Παράμετρος char *m_identifier: ονομασία πίνακα
 * Παράμετρος bool vect: αληθές όταν ζητείται μονοδιάστατος πίνακας (διάνυσμα)
 * Επιστρέφει: structure με την συστοιχία επιλογής
 */
struct matrix choose_matrix(char *m_identifier, bool vect) {
    //δημιουργία συστοιχίας
    struct matrix matrix = define_matrix();

    printf("Επιλογή συστοιχίας %s", m_identifier);
    int choice = menu("\n0.Ακύρωση\n1.Επιλογή από διαθέσιμες συστοιχίες\n2.Εισαγωγή συστοιχίας\n\n");

    while(choice != 1 && choice != 2 && choice != 0) {
        puts("Η επιλογή αυτή δεν υπάρχει");
        choice = menu("\n0.Ακύρωση\n1.Επιλογή από διαθέσιμες συστοιχίες\n2.Εισαγωγή συστοιχίας\n\n");
    }

    if(choice == 2)
        return getmatrix(vect);
    else if(choice == 0) {
        matrix.invalid = true;
        return matrix;
    }

    //επιλογή από διαθέσιμους πίνακες
    char *filename = show_matrixes();
    if(*filename != '\0') {
        strcat(filename, ".txt");

        //άνοιξε αρχείο σε read mode
        FILE* fp;
        fp = fopen(filename, "r");

        //επανάληψη μέχρι η εισαγωγή του χρήστη να αντιστοιχεί σε αναγνωριστικό συστοιχίας
        while(fp == NULL) {
            printf("Ο πίνακας δεν υπάρχει\n");
            scanf("%s", filename);
            strcat(filename, ".txt");
            fp = fopen(filename, "r");
        }

        //διαστάσεις: γραμμές & στήλες
        fscanf(fp, "%d", &matrix.rows);
        matrix.rows = abs(matrix.rows); //σε περίπτωση που δώθηκε αρνητική τιμή
        fscanf(fp, "%d", &matrix.cols);
        matrix.cols = abs(matrix.cols); //σε περίπτωση που δώθηκε αρνητική τιμή

        //μεταφορά στοιχείων συστοιχίας από το αρχείο σε πίνακα σε structure
        for(int i = 0; i < matrix.rows; i++)
            for(int j = 0; j < matrix.cols; j++)
                fscanf(fp, "%lf", &matrix.mat[i][j]);
    } else
        matrix.invalid = true;

    return matrix;
}

/* Πράξεις πινάκων:
 * Κάλεσμα συναρτήσεων για πράξεις πινάκων
 * Αν η πράξη δεν έχει αποτέλεσμα πίνακα, γίνεται προβολή αποτελέσματος
 * και ο πίνακας αποτελέσματος γίνεται invalid
 *
 * Παράμετρος int operation: αριθμός που αντιστοιχεί σε πράξη
 * Επιστρέφει: structure με τον πίνακα αποτελέσματος
 */
struct matrix matrix_operations(int operation) {

    //δημιουργία συστοιχίας αποτελέσματος
    struct matrix matrixC = define_matrix();

    switch(operation) {
        case sum:
            //πρόσθεση
            {
                struct matrix A = choose_matrix("A", false);
                struct matrix B = choose_matrix("Β", false);
                if(!A.invalid && !B.invalid)
                    matrixC = sum_matrix(A, B);
                else
                    matrixC.invalid = true;
            }
            break;
        case subtraction:
            //αφαίρεση
            {
                struct matrix A = choose_matrix("A", false);
                struct matrix B = choose_matrix("Β", false);
                if(!A.invalid && !B.invalid)
                    matrixC = subtraction_matrix(A, B);
                else
                    matrixC.invalid = true;

            }
            break;
        case multiplicationMatrix:
            //πολλαπλασιασμός πινακων
            {
                struct matrix A = choose_matrix("A", false);
                struct matrix B = choose_matrix("Β", false);
                if(!A.invalid && !B.invalid)
                    matrixC = multiplication_matrix(A, B);
                else
                    matrixC.invalid = true;

            }
            break;

        case multiplicationNumber:
            //πολλαπλασιασμός με αριθμό
            {
                double number = 0;
                struct matrix A = choose_matrix("", false);
                printf("\nΕισαγωγή αριθμού: ");
                scanf("%lf", &number);
                matrixC = multiply_byNumber(A, number);
            }
            break;

        case determinant:
            //ορίζουσα
            matrixC.invalid = true;
            struct matrix A = choose_matrix("A", false);

            if(A.rows == A.cols) {
                double d = det(A);
                printf("Ορίζουσα: %.2lf\n", d);
            } else {
                puts("Ο πίνακας πρέπει να είναι τετραγωνικός");
                matrixC.invalid = true;
            }
            break;
        case inverse:
            //αντίστροφος
            if(A.rows == A.cols)
                matrixC = inverse_matrix(choose_matrix("A", false));

            else {
                puts("Ο πίνακας πρέπει να είναι τετραγωνικός");
                matrixC.invalid = true;
            }
            break;
        case transpose:
            //ανάστροφος
            matrixC = transpose_matrix(choose_matrix("", false));
            break;
        case degree:
            //δυνάμεις πινάκων
            {
                int power = 0;
                struct matrix A = choose_matrix("", false);
                printf("Δώσε δύναμη: ");
                scanf("%d", &power);

                matrixC = exp_matrix(A, power);
            }
            break;
        case trace:
            //ίχνος
            matrixC.invalid = true;
            printf("Ίχνος: %.2lf", ixnos(choose_matrix("", false)));
            break;
        case backToHome:
            //επιστροφή στο αρχικό μενού
            matrixC.invalid = true;
            break;
        default:
            puts("Η επίλογη αυτή δεν υπάρχει");
            matrixC.invalid = true;
    }
    return matrixC;
}

/* Πράξεις διανυσμάτων:
 * Κάλεσμα συναρτήσεων για πράξεις διανυσμάτων
 * Αν η πράξη δεν έχει αποτέλεσμα διάνυσμα, γίνεται προβολή αποτελέσματος
 * και ο πίνακας αποτελέσματος γίνεται invalid
 *
 * Παράμετρος int operation: αριθμός που αντιστοιχεί σε πράξη
 * Επιστρέφει: structure με τον πίνακα αποτελέσματος
 */
struct matrix vector_operations(int operation) {
    //δημιουργία συστοιχίας αποτελέσματος
    struct matrix C = define_matrix();
    C.vect = true;

    switch(operation) {
        case sum2:
            //πρόσθεση
            {
                struct matrix A = choose_matrix("A", true);
                struct matrix B = choose_matrix("Β", true);
                if(!A.invalid && !B.invalid) {
                    if(A.cols == 1 && B.cols == 1)
                        C = sum_matrix(A, B);
                    else {
                        puts("Ένας τουλάχιστον πίνακας δεν είναι διάνυσμα");
                        C.invalid = true;
                    }
                } else
                    C.invalid = true;
            }
            break;
        case subtraction2:
            //αφαίρεση
            {
                struct matrix A = choose_matrix("A", true);
                struct matrix B = choose_matrix("Β", true);

                //έλεγχος
                if(!A.invalid && !B.invalid) {
                    if(A.cols == 1 && B.cols == 1)
                        C = subtraction_matrix(A, B);
                    else {
                        puts("Ένας τουλάχιστον πίνακας δεν είναι διάνυσμα");
                        C.invalid = true;
                    }
                } else
                    C.invalid = true;
            }
            break;
        case dotProduct:
            //εσωτερικό γινόμενο
            {
                struct matrix A = choose_matrix("A", true);
                struct matrix B = choose_matrix("Β", true);
                if(!A.invalid && !B.invalid) {
                    C.invalid = true;

                    printf("Eσωτερικό γινόμενο: %.2lf", esgin(A, B));
                } else
                    C.invalid = true;
            }
            break;
        case vectorProduct:
            //εξωτερικό γινόμενο
            {
                struct matrix A = choose_matrix("A", true);
                struct matrix B = choose_matrix("Β", true);
                if(!A.invalid && !B.invalid)
                    C = vector_product(A, B);

                else
                    C.invalid = true;
            }
            break;
        case backToHome2:
            //επιστροφή στο αρχικό μενού
            C.invalid = true;
            break;
        default:
            puts("Η επίλογη αυτή δεν υπάρχει");
            C.invalid = true;
    }
    return C;
}

/* Προβολή στοιχείων συστοιχίας:
 *
 * Παράμετρος struct matrix A: structure με συστοιχία για προβολή
 */
void print_matrix(struct matrix A) {
    printf("\n");
    if(!A.invalid) {
        for(int i = 0; i < A.rows; i++) {
            for(int j = 0; j < A.cols; j++)
                printf("%.2lf ", A.mat[i][j]);
            printf("\n");
        }
    }
}

/* Αρχικοποίηση συστοιχίας:
 * Αρχικοποίηση μεταβλητών μέσα στο structure matrix
 *
 * Επιστρέφει: structure matrix με αρχικοποιημένες μεταβλητές
 */
struct matrix define_matrix(void) {
    struct matrix y;
    y.invalid = false;
    y.vect = false;
    y.rows = y.cols = 0;
    return y;
}

/* Προβολή αρχικού μηνύματος:
 * Προβoλή ονομάτων των συγγραφέων του προγράμματος
 */
void startMsg(void) {
    puts("Το παρόν πρόγραμμα γράφτηκε από την Αικατερίνη Παπαγιαννίτση και\n\
Μαρία Μηλιούση ως εργασία του μαθήματος Δομημένος Προγραμματισμός,\nέτος 2021-2022\n");
}

