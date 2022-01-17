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

//αρχικό μενού
char *prime_menu = "\tΠΡΑΞΕΙΣ ΜΕΤΑΞΥ ΠΙΝΑΚΩΝ\n\n\
1.Δημιουργία συστοιχίας\n\
2.Προβολή διαθέσιμων συστοιχιών\n\
3.Φόρτωση συστοιχίας\n\
4.Διαγραφή συστοιχίας\n\
5.Πράξεις πινάκων\n\
6.Πράξεις διανυσμάτων\n\
7.Έξοδος\n\n";

enum home {createMatrix = 1, showMatrix, ld_matrix, del, matrixOperations, vectorOperations, end};

//μενού για πράξεις πινάκων
char *matrixOp_menu = "\n\
1.Πρόσθεση\n\
2.Aφαίρεση\n\
3.Πολλαπλασιασμός\n\
4.Ορίζουσα\n\
5.Αντίστροφος\n\
6.Ανάστροφος\n\
7.Δυνάμεις πινάκων\n\
8.Ίχνος\n\
9.Επιστροφή στο αρχικό μενού\n\n";

//περιπτώσεις πράξεων πινάκων
enum matrixOp {sum = 1, subtraction, multiplication, determinant, inverse, transpose, power, trace, backToHome};

//μενού για πράξεις διανυσμάτων
char *vectOp_menu = "\n\
1.Πρόσθεση\n\
2.Aφαίρεση\n\
3.Εσωτερικό Γινόμενο\n\
4.Διανυσματικό γινόμενο\n\
5.Επιστροφή στο αρχικό μενού\n\n";

//περιπτώσεις πράξεων διανυσμάτων
enum vectorOp {sum2 = 1, subtraction2, dotProduct, vectorProduct, backToHome2};

int menu(char* menu);

struct matrix define_matrix();
struct matrix getmatrix(bool);
struct matrix choose_matrix(char*, bool);
struct matrix matrix_operations(int);
struct matrix vector_operations(int);
void print_matrix(struct matrix);


//συναρτήσεις για αλληλεπίδραση με αρχεία
bool create_matrix();
bool show_matrixes();
bool load_matrix();
void delete_matrix();
void print_elements();
bool delete_matrixName(char* name);

//συναρτήσεις πράξεων
//struct matrix cofactor(struct matrix A, int i, int j);
//double det(struct matrix A);
//struct matrix sum_matrix(struct matrix A, struct matrix B);
//struct matrix subtraction_matrix(struct matrix A, struct matrix B);
//struct matrix multiplication_matrix(struct matrix A, struct matrix B);
//struct matrix traspose(struct matrix A);


int main() {
    bool stop = false;

    //μέχρι ο χρήστης να επιλέξει να σταματήσει το πρόγραμμα
    while(!stop) {
        fflush(stdin);

        //επιλογές του αρχικού μενού
        switch(menu(prime_menu)) {
            case createMatrix:
                //δημιουργία πίνακα
                {
                    bool error = !create_matrix();
                    if(error)
                        puts("Παρουσιάστηκε σφάλμα");
                }
                break;

            case showMatrix:
                //προβολή διαθέσιμων πινάκων
                if(show_matrixes())
                    print_elements();
                else
                    puts("Παρουσιάστηκε σφάλμα");
                break;

            case ld_matrix:
                //φόρτωση πίνακα
                if(!load_matrix())
                    printf("Aδυναμία άνοιγμα αρχείου\n");
                break;

            case matrixOperations:
                //πράξεις πινάκων
                {
                    int choice = menu(matrixOp_menu);

                    struct matrix result = matrix_operations(choice);
                    //προβολή αποτελέσματος
                    print_matrix(result);

                }
                break;
            case vectorOperations:
                //πράξεις διανυσμάτων
                {
                    int choice = menu(vectOp_menu);
                    struct matrix result = vector_operations(choice);

                    //προβολή αποτελέσματος
                    print_matrix(result);
                }
                break;

            case del:
                //διαγραφή συστοιχίας
                delete_matrix();
                break;

            case end:
                //έξοδος προγράμματος
                stop = true;
                break;

            default:
                puts("Η επιλογή που βάλατε δεν υπάρχει");
        }

        //άφησε 3 κενές γραμμές
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
            printf("Στήλες: ");
            scanf("%d", &y.cols);
        } else {
            printf("\nΟρισμός διαστάσεων\nΜέγιστες διαστάσεις: %d \n", ROWS_MAX);
            scanf("%d", &y.rows);
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

/* Δημιουργία Πίνακα:
 * Εισαγωγή πίνακα από χρήστη
 * Αποθήκευση πίνακα σε αρχείο
 *
 * Παράμετρος bool vect: αληθές όταν ζητείται μονοδιάστατος πίνακας (διάνυσμα)
 * Επιστρέφει: false αν παρουσιαστεί σφάλμα και true αν εκτελεστεί επιτυχώς
 */
bool create_matrix() {

    char name[50];
    bool unique_name = true;

    //άνοιγμα αρχείου διαθέσιμων συστοιχιών σε read mode
    FILE* am_fp;
    am_fp = fopen("available_matrix.txt", "a");
    if(am_fp == NULL)
        return false;

    //Eισαγωγή αναγνωριστικού από τον χρήστη
    while(!unique_name) {
        printf("\nΟρισμός αναγνωριστικού: ");
        scanf("%s", name);
        fflush(stdin);

        //έλεγχος οτι δεν έχει οριστεί πίνακας με το ίδιο αναγνωριστικό
        char matrixName[50];
        while(fscanf(am_fp, "%s", matrixName) != EOF) {
            if(strcmp(name, matrixName) == 0) {
                printf("Το αναγνωριστικό %s χρησιμοποιείται ήδη", name);
                unique_name = false;
            } else
                unique_name = true;
        }
    }
    //έλεγχος της fscanf
    if (!feof(am_fp)){
        fclose(am_fp);
        return false;
    }


    //κλείσιμο αρχείου διαθέσιμων συστοιχιών
    fclose(am_fp);

    //άνοιγμα αρχείου διαθέσιμων συστοιχιών σε append mode
    FILE* am_file;
    am_file = fopen("available_matrix.txt", "a");
    if(am_file == NULL)
        return false;

    //καταγραφή αναγνωριστικού
    fprintf(am_file, "%s\n", name);
    //κλείσιμο αρχείου διαθέσιμων συστοιχιών
    fclose(am_file);

    //πρόσθεσε την κατάληξη ".txt" στο αναγνωριστικό
    strcat(name, ".txt");

    //δημιουργία αρχείου "αναγνωριστικο".txt σε write mode
    FILE *file;
    file = fopen(name, "w");
    if(file == NULL)
        return false;

    //δημιουργία πίνακα
    struct matrix x = getmatrix(false);
    if(x.cols == 1)
        x.vect = true;

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
bool show_matrixes() {
    //άνοιγμα αρχείου σε read mode
    FILE* AM;
    AM = fopen("available_matrix.txt", "r");
    if(AM == NULL)
        return false;

    char matrixName[50];
    //επανέλαβε μέχρι το τέλος του αρχείου
    while((fscanf(AM, "%s", matrixName)) != EOF)
        printf("%s\n", matrixName);

    //έλεγχος ότι δεν είναι σφάλμα της scanf
    if(!feof(AM)){
        fclose(AM);
        return false;
    }

    //κλείσιμο αρχείου
    fclose(AM);

    return true;
}

/* Φόρτωση πίνακα:
 * Εισαγωγή αναγνωριστικού συστοιχίας απο το χρήστη
 * και συμπλήρωση αναγνωριστικού συστοιχίας στο αρχείο διαθέσιμων συστοιχιών
 *
 * Επιστρέφει: false αν παρουσιαστεί σφάλμα και true αν εκτελεστεί επιτυχώς
 */
bool load_matrix() {
    //οδηγίες για φόρτωση αρχείου
    printf("\tOδηγίες:\n\
-Το αρχείο πρέπει να έχει επέκταση txt και στο ίδιο directory\n\
-Ο αριθμός των γραμμών να αναγράφεται στην πρώτη γραμμή\n\
-Ο αριθμός των στηλών να αναγράφεται στην δεύτερη γραμμή\n\
-Μέγιστες δυνατές διαστάσεις: %dx%d\n\n", ROWS_MAX, COLS_MAX);

    //εισαγωγή αναγνωριστικού συστοιχίας απο το χρήστη
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
    return choice;
}

/* Προβολή στοιχείων συστοιχίας από αρχείο:
 * Εισαγωγή αναγνωριστικού συστοιχίας από τον χρήστη,
 * άνοιγμα αρχείου συστοιχίας και προβολή στοιχείων
 */
void print_elements() {
    printf("\nΕπιλογή πίνακα για προβολή: ");
    char name[50];
    scanf("%s", name);
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
void delete_matrix() {
    char name[50];
    show_matrixes();
    printf("Εισαγωγή συστοιχίας για διαγραφή: ");
    scanf("%s", name);

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
        printf("Διαγράφτηκε επιτυχως\n");
    else
        printf("Αδυναμία διαγραφης\n");
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
    printf("Επιλογή συστοιχίας %s", m_identifier);
    int choice = menu("\n1.Επιλογή από διαθέσιμες συστοιχίες\n2.Εισαγωγή συστοιχίας\n\n");

    while(choice != 1 && choice != 2) {
        puts("Η επιλογή αυτή δεν υπάρχει");
        choice = menu("\n1.Επιλογή από διαθέσιμες συστοιχίες\n2.Εισαγωγή συστοιχίας\n\n");
    }

    if(choice == 2)
        return getmatrix(vect);

    struct matrix matrix = define_matrix();
    //προβολή διαθέσιμων πινάκων
    show_matrixes();

    //επιλογή
    char filename[50];
    scanf("%s", filename);
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
    fscanf(fp, "%d", &matrix.cols);

    //μεταφορά στοιχείων συστοιχίας από το αρχείο σε πίνακα σε structure
    for(int i = 0; i < matrix.rows; i++)
        for(int j = 0; j < matrix.cols; j++)
            fscanf(fp, "%lf", &matrix.mat[i][j]);

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
                matrixC = sum_matrix(A, B);
            }
            break;
        case subtraction:
            //αφαίρεση
            {
                struct matrix A = choose_matrix("A", false);
                struct matrix B = choose_matrix("Β", false);
                matrixC = subtraction_matrix(A, B);
            }
        case multiplication:
            //πολλαπλασιασμός
            {
                //πολσμος με αριθμο ή πινακα επιλογη
                struct matrix A = choose_matrix("A", false);
                struct matrix B = choose_matrix("Β", false);
                matrixC = multiplication_matrix(A, B);
            }
            break;

        case determinant:
            //ορίζουσα
            matrixC.invalid = true;
            struct matrix A = choose_matrix("A", false);

            if(A.rows == A.cols) {
                double d = det(A);
                printf("Ορίζουσα: %.2lf\n", d);
            } else{
                puts("Ο πίνακας πρέπει να είναι τετραγωνικός");
                matrixC.invalid = true;
            }
            break;
        case inverse:
            //αντίστροφος
            if(A.rows == A.cols) {
               matrixC = inverse_matrix(choose_matrix("A", false));
            } else{
                puts("Ο πίνακας πρέπει να είναι τετραγωνικός");
                matrixC.invalid = true;
            }
            break;
        case transpose:
            //ανάστροφος
            matrixC = transpose_matrix(choose_matrix("", false));
            break;
        case power:
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
            if(A.cols == 1 && B.cols == 1)
                C = sum_matrix(A, B);
            else {
                puts("Ένας τουλάχιστον πίνακας δεν είναι διάνυσμα");
                C.invalid = true;
            }
        }
        break;
    case subtraction2:
            //αφαίρεση
            {
                struct matrix A = choose_matrix("A", true);
                struct matrix B = choose_matrix("Β", true);
                if(A.cols == 1 && B.cols == 1)
                    C = subtraction_matrix(A, B);
                else {
                    puts("Ένας τουλάχιστον πίνακας δεν είναι διάνυσμα");
                    C.invalid = true;
                }
            }
            break;
        case dotProduct:
            //εσωτερικό γινόμενο
            {
                struct matrix A = choose_matrix("A", true);
                struct matrix B = choose_matrix("Β", true);
                C.invalid = true;

                printf("Eσωτερικό γινόμενο: %.2lf", esgin(A, B));
            }
            break;
        case vectorProduct:
            //εξωτερικό γινόμενο
            {
                struct matrix A = choose_matrix("A", true);
                struct matrix B = choose_matrix("Β", true);
                C = vector_product(A, B);
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
struct matrix define_matrix() {
    struct matrix y;
    y.invalid = false;
    y.vect = false;
    y.rows = y.cols = 0;
    return y;
}
