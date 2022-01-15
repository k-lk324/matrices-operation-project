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

enum home{createMatrix = 1, show_matrix, ld_matrix, del,
          matrix_operations, vectorOperations, end};

//μενού για πράξεις πινάκων
char *matrOp_menu = "\n1.Πρόσθεση\n\
2.Aφαίρεση\n\
3.Πολλαπλασιασμός\n\
4.Ορίζουσα\n\
5.Αντίστροφος\n\
6.Ανάστροφος\n\
7.Δυνάμεις πινάκων\n\
8.Επιστροφή στο αρχικό μενού\n\n";

//περιπτώσεις πράξεων
enum {sum = 1, subtraction, multiplication, determinant, inverse, transpose, power, backToHome};

//μενού για πράξεις διανυσμάτων
char *vectOp_menu = "1.Πρόσθεση\n\
2.Aφαίρεση\n\
3.Εσωτερικό\n\
4.Διανυσματικό γινόμενο\n\n";

int menu(char* menu);

struct matrix define_matrix();
struct matrix getmatrix();
struct matrix choose_matrix(char*);
struct matrix matrix_result(int);
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

                if (!create_matrix())
                    puts("Παρουσιάστηκε σφάλμα");
                break;

            case show_matrix:
                //προβολή διαθέσιμων πινάκων
                if (show_matrixes())
                    print_elements();
                else
            puts("Παρουσιάστηκε σφάλμα");
            break;

        case ld_matrix:
            //φόρτωση πίνακα
            if(!load_matrix())
                printf("Aδυναμία άνοιγμα αρχείου\n");
            break;

        case matrix_operations:
            //πράξεις πινάκων
            {
                int choice = menu(matrOp_menu);

                struct matrix result = matrix_result(choice);
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
        for(int i=0; i<3; i++)
            printf("\n");
    }
    return 0;
}

//ζητάει απο χρήστη πίνακα: διαστάσεις και στοιχεία
//@επιστρέφει τον structure με τον πίνακα
struct matrix getmatrix(){
    struct matrix y = define_matrix();

    //διαστάσεις
    printf("\nΟρισμός διαστάσεων\nΠροσοχή! Μέγιστες διαστάσεις: %dx%d\n\nΓραμμές: ", ROWS_MAX, COLS_MAX);
    scanf("%d", &y.rows);
    printf("Στήλες: ");
    scanf("%d", &y.cols);

    //εισαγωγη στοιχειων
    printf("\nΣυμπλήρωση τιμών:\nΔώσε στοιχεία πίνακα χωρισμένα με κένο αλλαγή γραμμής\n");
    printf("π.χ. ένας πίνακας 2x3:\n1 0 45.87\n2 5.8 89\n\n");

    for(int i=0; i<y.rows; i++) {
        for(int j=0; j<y.cols; j++)
            scanf("%lf", &y.mat[i][j]);
    }
    return y;
}

//δημιουργεί συστοιχία και αποθηκεύει σε txt file
/*@επιστρέφει false αν δεν κατάφερει να ανοιξει το αρχείο
true αν εκτελεστεί ο κώδικας κανονικά*/
bool create_matrix() {

    char name[50];
    bool unique_name = true;

    //άνοιγμα αρχείου διαθέσιμων συστοιχιών σε read mode
    FILE* am_fp;
    am_fp = fopen("available_matrix.txt", "a");
    if(am_fp == NULL)
        return false;

    while (!unique_name){
        //αναγνωριστικο πίνακα
        printf("\nΟρισμός αναγνωριστικού: ");
        scanf("%s", name);
        fflush(stdin);

    #ifndef DEBUGSTR

        //έλεγχος οτι δεν έχει οριστεί πίνακας με το ίδιο αναγνωριστικό
        char matrixName[50];
        while(fscanf(am_fp, "%s", matrixName) != EOF) {
            if(strcmp(name, matrixName) == 0) {
                printf("Το αναγνωριστικό %s χρησιμοποιείται ήδη", name);
                unique_name = false;
            }
            else
                unique_name = true;
        }
    }
    //έλεγχος fscanf

    //κλεισιμο αρχειου διαθέσιμων συστοιχιών
    fclose(am_fp);

    //άνοιγμα αρχειου διαθεσιμων συστοιχιων σε append mode
    FILE* am_file;
    am_file = fopen("available_matrix.txt", "a");
    if(am_file == NULL)
        return false;

    //καταγραφή αναγνωριστικου
    fprintf(am_file, "%s\n", name);
    //κλεισιμο αρχειου διαθέσιμων συστοιχιών
    fclose(am_file);

    //πρόσθεσε την καταληξη ".txt" στο αναγνωριστικο
    strcat(name, ".txt");

    //δημιούργησε αρχείο "αναγνωριστικο".txt
    FILE *file;
    file = fopen(name, "w");
    if(file == NULL)
        return false;

    //δημιουργία πίνακα
    struct matrix x =getmatrix();

    //πρώτες 2 σειρες τύπωσε τις διαστάσεις
    fprintf(file, "%d\n%d\n", x.rows, x.cols);

    for(int i=0; i<x.rows; i++) {
        for(int j=0; j<x.cols; j++) {
            ;
            fprintf(file, "%lf ", x.mat[i][j]);
        }
        fprintf(file, "\n");
    }
    //κλεισιμο αρχείο συστοιχίας
    fclose(file);
#endif // DEBUGSTR
    return true;
}

//προβάλει τους διαθέσιμους πίνακες
//@επιστρέφει true αν εκτελεστει επιτυχώς ο κώδικας και false αν παρουσιαστεί σφάλμα
bool show_matrixes() {
    //άνοιγμα αρχείου σε read mode
    FILE* AM;
    AM = fopen("available_matrix.txt", "r");

    if (AM == NULL)
        return false;

    char matrixName[50];
    //επανέλαβε μέχρι το τέλος του αρχείου
    while((fscanf(AM, "%s", matrixName))!= EOF)
        printf("%s\n", matrixName);

    //έλεγχος οτι δεν ειναι σφαλμα της scanf
    if(!feof(AM))
        return false;

    //κλείσιμο αρχείου
    fclose(AM);

    return true;
}

//φορτώνει δισδιάστατη συστοιχία από αρχείο txt
//@επιστρέφει true αν εκτελεστεί επιτυχώς
bool load_matrix() {
    // οδηγίες για φόρτωση αρχείου
    printf("\tOδηγίες:\n\
-Το αρχείο πρέπει να έχει επέκταση txt και στο ίδιο directory\n\
-Ο αριθμός των γραμμών να αναγράφεται στην πρώτη γραμμή\n\
-Ο αριθμός των στηλών να αναγράφεται στην δεύτερη γραμμή\n\
-Μέγιστες δυνατές διαστάσεις: %dx%D\n\n", ROWS_MAX,COLS_MAX);

    //εισαγωγη ονοματος συστοιχιας απο το χρηστη
    char matrixName[50];
    char filename[50];
    printf("Εισαγωγή ονόματος συστοιχίας (χωρίς επέκταση txt): ");
    scanf("%s", matrixName);

    strcpy(filename, matrixName);
    strcat(filename, ".txt");

    //ανοιγμα αρχείου σε read mode
    FILE *fp;
    fp = fopen(filename, "r");

    if(fp == NULL){  //αν υπάρξει αδυναμία άνοιγμα αρχείου
        return false;
    }

        //κλείσιμο αρχείου συστοιχίας
        fclose(fp);

        //άνοιγμα αρχείου διαθέσιμων πινάκων
        FILE* am_file;
        am_file = fopen("available_matrix.txt", "a");
        if(am_file == NULL)
            printf("Αδυναμία φόρτωσης συστοιχίας\n");

        //συμπληρώνει το όνομα του πίνακα στους διαθέσιμους πίνακες
        fprintf(am_file, "%s\n", matrixName);

        //κλείσιμο αρχείου διαθέσιμων πίνακων
        fclose(am_file);

    return true;
}

//τυπώνει μενού με επιλόγές και ζητάει επιλογή απο τον χρήστη
//@επιστρέφει την επιλογή του χρήστη
int menu(char* menu) {
    int choice;
    printf("%s", menu);
    printf("Επιλογή: ");

    fflush(stdin);
    scanf("%d", &choice);
    return choice;
}

//τυπώνει τα στοιχεία ενος πίνακα επιλογής του χρήστη
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

        for(int i=0; i<r; i++) {
            for(int j=0; j<c; j++) {
                double element;
                fscanf(fp, "%lf", &element);
                printf("%.3lf ", element);
            }
            printf("\n");
        }
        fclose(fp);
    }
}

//διαγράφει το όνομα της συστοιχίας απο το "available_matrix.txt"
//@επιστρέφει false αν παρουσιαστεί σφάλμα και true αν εκτελεστεί επιτυχώς
bool delete_matrixName(char* name) {
    FILE *am_fp, *copy_fp;
    char matrixName[50];
    char available_matrix[] = "available_matrix.txt";

    //άνοιγμα αρχειου σε read mode
    am_fp = fopen(available_matrix, "r");
    //άνοιγμα αρχειου σε write mode
    copy_fp = fopen("copy.txt", "w");

    while(fscanf(am_fp, "%s", matrixName) != EOF) {
        //εκτος απο την συστοιχια για διαγραφη
        if(strcmp(name, matrixName) != 0) {
            //αντέγραψε ολες τις υπόλοιπες γραμμες στο copy.txt
            fprintf(copy_fp, "%s\n", matrixName);
        } else
            printf("Ο πίνακας εντωπίστηκε\n");
    }

    // ελεγχος οτι δεν ειναι σφάλμα της fscanf
    if(!feof(am_fp)) {
        printf("Παρουσιάστηκε σφάλμα\n");
        return false;
    }

    //κλείσιμο αρχείων
    fclose(am_fp);
    fclose(copy_fp);

    //διαγραφη αρχικου αρχειου
    if(remove(available_matrix) != 0)
        return false;

    //μετονομασια του copy.txt σε available_matrix.txt
    rename("copy.txt", "available_matrix.txt");

    return true;
}

//διαγράφει συστοιχία
void delete_matrix() {
    char name[50];
    show_matrixes();
    printf("Εισαγωγή συστοιχίας για διαγραφή: ");
    scanf("%s", name);

    char filename[50];
    strcpy(filename, name);

    //προσθεσε την καταληξη ".txt"
    strcat(filename, ".txt");

    //για να μην έμφανίζεται στους διαθέσιμους πίνακες
    bool check1 = delete_matrixName(name);
    //διαγραφή αρχείου
    bool check2 = remove(filename) == 0;

    //έλεγχος διαγραφής
    if(check1 && check2)
        printf("Διαγράφτηκε επιτυχως\n");
    else
        printf("Αδυναμία διαγραφης\n");
}

//δίνει στον χρήστη την επιλογή να γράψει μια συστοιχία ή να διαλέξει από αρχείο
//@επιστρέφει structure με την συστοιχία
struct matrix choose_matrix(char* m_identifier) {
    printf("Επιλογή συστοιχίας %s", m_identifier);
    int choice = menu("\n1.Επιλογή από διαθέσιμες συστοιχίες\n2.Εισαγωγή συστοιχίας\n\n");

    while (choice!=1 && choice!=2){
        puts("Η επιλογή αυτή δεν υπάρχει");
        choice = menu("\n1.Επιλογή από διαθέσιμες συστοιχίες\n2.Εισαγωγή συστοιχίας\n\n");
    }

    if(choice == 2)
        return getmatrix();

    struct matrix matrix = define_matrix();
    //τύπωσε τους διαθέσιμους πίνακες
    show_matrixes();

    //επιλογή
    char filename[50];
    scanf("%s", filename);
    strcat(filename, ".txt");

    //ανοιξε αρχειο σε read mode
    FILE* fp;
    fp = fopen(filename, "r");

    //επανέλαβε μέχρι input matches αναγνωριστικό
    while(fp == NULL) {
        printf("Ο πίνακας δεν υπάρχει\n");
        scanf("%s", filename);
        strcat(filename, ".txt");
        fp = fopen(filename, "r");
    }

    //δες διαστάσεις: γραμμές & στήλες
    fscanf(fp, "%d", &matrix.rows);
    fscanf(fp, "%d", &matrix.cols);

    //μετέφερε πίνακα απο το αρχείο
    for(int i=0; i<matrix.rows; i++)
        for(int j=0; j<matrix.cols; j++)
            fscanf(fp, "%lf", &matrix.mat[i][j]);

    return matrix;
}


struct matrix matrix_result(int operation) {

    //δημιουργία συστοιχίας αποτελέσματος
    struct matrix matrixC = define_matrix();

    switch(operation) {
        case sum:
            //πρόσθεση
            {
            struct matrix A = choose_matrix("A");
            struct matrix B = choose_matrix("Β");
            matrixC = sum_matrix(A,B);
            }
            break;
        case subtraction:
            //αφαίρεση
            {
            struct matrix A = choose_matrix("A");
            struct matrix B = choose_matrix("Β");
            matrixC = subtraction_matrix(A,B);
            }
        case multiplication:
            //πολλαπλασιασμός
            {
            //πολσμος με αριθμο ή πινακα επιλογη
            struct matrix A = choose_matrix("A");
            struct matrix B = choose_matrix("Β");
            matrixC = multiplication_matrix(A,B);
            }
            break;

        case determinant:
            //ορίζουσα
            matrixC.invalid = true;
            struct matrix A = choose_matrix("A");
            if(A.rows == A.cols) {
                double d = det(A);
                printf("Ορίζουσα: %.2lf\n", d);
            } else
                puts("Ο πίνακας πρέπει να είναι τετραγωνικός");
            break;
        case inverse:
            //αντίστροφος
            matrixC = inverse_matrix(choose_matrix(""));
            break;
        case transpose:
            //ανάστροφος
            matrixC = transpose_matrix(choose_matrix(""));
            break;
        case power:
            //δυνάμεις πινάκων
            {
                int power = 0;
                struct matrix A = choose_matrix("");
                printf("Δώσε δύναμη: ");
                scanf("%d", &power);

                matrixC = exp_matrix(A, power);
            }
            break;
        case backToHome:
            matrixC.invalid = true;
            break;
        default:
            puts("Η επίλογη αυτή δεν υπάρχει");
            matrixC.invalid = true;
    }

    return matrixC;
}


struct matrix vector_operations(int operation){
    //δημιουργία συστοιχίας αποτελέσματος
    struct matrix C = define_matrix();

    enum vector {sum = 1, subtraction, dotProduct, vectorProduct, backToHome2};

    switch(operation) {
        case sum:
            //πρόσθεση
            {
            struct matrix A = choose_matrix("A");
            struct matrix B = choose_matrix("Β");
            if (A.cols ==1 && B.cols == 1)
                C = sum_matrix(A,B);
            else{
                puts("Ένας τουλάχιστον πίνακας δεν είναι διάνυσμα");
                C.invalid = true;
            }

            }
            break;
        case subtraction:
            //αφαίρεση
            {
            struct matrix A = choose_matrix("A");
            struct matrix B = choose_matrix("Β");
                        if (A.cols ==1 && B.cols == 1)
                C = subtraction_matrix(A,B);
            else{
                puts("Ένας τουλάχιστον πίνακας δεν είναι διάνυσμα");
                C.invalid = true;
            }

            }
            break;
        case dotProduct:
            //εσωτερικό γινόμενο
            {
            struct matrix A = choose_matrix("A");
            struct matrix B = choose_matrix("Β");
            C.invalid = true;

            printf("Eσωτερικό γινόμενο: %.2lf", esgin(A,B));}
            break;
        case vectorProduct:
            //εξωτερικό γινόμενο
            {
            struct matrix A = choose_matrix("A");
            struct matrix B = choose_matrix("Β");
            C = vector_product(A,B);
            }
        case backToHome2:
            //επιστροφή
            C.invalid = true;
            break;
        default:
            puts("Η επίλογη αυτή δεν υπάρχει");
            C.invalid = true;
    }
    return C;
}


//προβολη συστοιχίας
void print_matrix(struct matrix A){
    if (!A.invalid){
        for(int i=0; i<A.rows; i++){
            for(int j=0; j<A.cols; j++)
                printf("%.3lf ", A.mat[i][j]);
            printf("\n");
        }
    }
}

//αρχικοποίηση συστοιχίας
struct matrix define_matrix() {
    struct matrix y;
    y.invalid = false;
    y.rows = y.cols = 0;
    return y;
}
