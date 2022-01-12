#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#define ROWS_MAX 20
#define COLS_MAX 20
#define NOT_DEBUG
#define NOT_DEBUGSTR

char *prime_menu = "\tΠΡΑΞΕΙΣ ΜΕΤΑΞΥ ΠΙΝΑΚΩΝ\n\n\
1.Δημιουργία συστοιχίας\n\
2.Προβολή διαθέσιμων συστοιχιών\n\
3.Φόρτωση συστοιχίας\n\
4.Διαγραφή συστοιχίας\n\
5.Πράξεις πινάκων\n\
6.Πράξεις διανυσμάτων\n\
7.Ορίζουσα\n\
8.Ανάστροφος\n\
9.Έξοδος\n\n";

enum {createMatrix=1, show_matrix, ld_matrix, del,
          matrix_operations, vector_operations, determinant, transpose, end};

int menu(char* menu);

struct matrix {
    double mat[ROWS_MAX][COLS_MAX];
    int rows, cols;
};

struct matrix getmatrix();
struct matrix choose_matrix(char*);
struct matrix matrix_result(int);
void print_matrix(struct matrix);


//συναρτήσεις για αλληλεπίδραση με αρχεία
bool create_matrix();
bool show_matrixes();
bool load_matrix();
void delete_matrix();
void print_elements();
bool delete_matrixName(char* name);

//συναρτήσεις πράξεων
struct matrix cofactor(struct matrix A, int i, int j);
double det(struct matrix A);
struct matrix sum_matrix(struct matrix A, struct matrix B);
struct matrix substraction_matrix(struct matrix A, struct matrix B);
struct matrix multiplication_matrix(struct matrix A, struct matrix B);
struct matrix traspose(struct matrix A);


int main() {
    bool stop = false;

    //μέχρι ο χρήστης να επιλέξει να σταματήσει το πρόγραμμα
    while(!stop) {
        fflush(stdin);

        //επιλογές του αρχικού μενού
        switch(menu(prime_menu)) {
            case createMatrix:      //δημιουργία πίνακα
                create_matrix();
                break;

            case show_matrix:       //προβολή διαθέσιμων πινάκων
                show_matrixes();
                print_elements();
                break;

            case ld_matrix:         //φόρτωση πίνακα
                load_matrix();
                break;

            case matrix_operations: //πράξεις πινάκων
            {
                int choice = menu("\n1.Πρόσθεση\n2.Aφαίρεση\n3.Πολλαπλασιασμός\n\n");
                if(choice >= 1 && choice <=3) {
                    struct matrix result = matrix_result(choice);
                    //προβολή αποτελέσματος
                    print_matrix(result);
                }
                else
                    puts("H επιλογή αυτή δεν υπάρχει");
            }
                break;
            case vector_operations: //πράξεις διανυσμάτων
                //printf("\n");
//                int choice = menu("1.Πρόσθεση\n2.Aφαίρεση\n3.Εσωτερικό\n4.Διανυσματικό γινόμενο\n\n");
//                if (choice >= 1 && choice <=4){
//                   struct matrix matrixC = αποτελεσμα διανυσματων(choice)
//
//                    //προβολή αποτελέσματος
//                      print_matrix(matrixC);
//                }
//                else
//                    printf("H επιλογή δεν υπάρχει\n");
                break;

            case del:           //διαγραφή συστοιχίας
                delete_matrix();
                break;

            case end:           //έξοδος προγράμματος
                stop = true;
                break;

            case determinant:   //ορίζουσα
            {
                struct matrix A = choose_matrix("A");
                if(A.rows == A.cols){
                    double d = det(A);
                    printf("Ορίζουσα: %.2lf\n", d);
                }
                else
                    puts("Ο πίνακας πρέπει να είναι τετραγωνικός");
            }
            break;

            case transpose:     //ανάστροφος
                print_matrix(traspose(choose_matrix("")));
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
//@επιστρέφει τον πίνακα
struct matrix getmatrix(){
    struct matrix y;

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

    //αναγνωριστικο πίνακα
    printf("\nΟρισμός αναγνωριστικού: ");
    char name[50];
    scanf("%s", name);
    fflush(stdin);

#ifndef DEBUGSTR

    //δημιουργία πίνακα
    struct matrix x =getmatrix();

    //κατέγραψε το όνομα του πίνακα για να μπορει να παρουσιαστεί ως διαθέσιμος
    FILE* am_file;
    am_file = fopen("available_matrix.txt", "a");
    if(am_file == NULL) return false;

    fprintf(am_file, "%s\n", name);
    fclose(am_file);

    //πρόσθεσε την καταληξη ".txt" στο αναγνωριστικο
    strcat(name, ".txt");

    //δημιούργησε αρχείο "αναγνωριστικο".txt
    FILE *file;
    file = fopen(name, "w");
    if(file == NULL) return false;

    //πρώτες 2 σειρες τύπωσε τις διαστάσεις
    fprintf(file, "%d\n%d\n", x.rows, x.cols);

    for(int i=0; i<x.rows; i++) {
        for(int j=0; j<x.cols; j++) {
            ;
            fprintf(file, "%lf ", x.mat[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
#endif // DEBUGSTR
    return true;
}

//προβάλει τους διαθέσιμους πίνακες
bool show_matrixes() {

    //άνοιγμα αρχείου σε read mode
    FILE* AM;
    AM = fopen("available_matrix.txt", "r");

    if (AM == NULL)
    {
        printf("Παρουσιάστηκε σφάλμα\n");
        return false;
    }

    char matrixName[50];
    //επανέλαβε μέχρι το τέλος του αρχείου
    while((fscanf(AM, "%s", matrixName))!= EOF)
        printf("%s\n", matrixName);

    if(!feof(AM)) {
        printf("Παρουσιάστηκε σφάλμα\n");
        return false;
    }

    //κλείσιμο αρχείου
    fclose(AM);

    return true;
}

//φορτώνει δισδιάστατη συστοιχία από αρχείο txt
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

    if(fp == NULL)  //αν υπάρξει αδυναμία άνοιγμα αρχείου
        printf("Aδυναμία άνοιγμα αρχείου\n");
    else {
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
    }
    return 0;
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

//
//@
struct matrix choose_matrix(char* m_identifier) {
    printf("Επιλογή συστοιχίας %s", m_identifier);
    int choice = menu("\n1.Επιλογή από διαθέσιμες συστοιχίες\n2.Εισαγωγή συστοιχίας\n\n");

    while (choice!=1 && choice!=2){
        puts("Η επιλογή αυτή δεν υπάρχει");
        choice = menu("\n1.Επιλογή από διαθέσιμες συστοιχίες\n2.Εισαγωγή συστοιχίας\n\n");
    }

    if(choice == 2)
        return getmatrix();

    struct matrix matrix;
    //τύπωσε τους διαθέσιμους πίνακες
    show_matrixes();

    //επιλογή
    char filename[50];
    scanf("%s", filename);
    strcat(filename, ".txt");

    //ανοιξε αρχειο
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

    //μετέφερε πίνακα απο το αρχειο
    for(int i=0; i<matrix.rows; i++)
        for(int j=0; j<matrix.cols; j++)
            fscanf(fp, "%lf", &matrix.mat[i][j]);

    return matrix;
}


struct matrix matrix_result(int operation) {

    //δημιουργία συστοιχίας αποτελέσματος
    struct matrix matrixC;

    //περιπτώσεις πράξεων
    enum {sum=1, subtraction, multiplication};
    switch(operation) {
    case sum:
        matrixC = sum_matrix(choose_matrix("A"), choose_matrix("Β"));
        break;
    case subtraction:
        matrixC = substraction_matrix(choose_matrix("A"), choose_matrix("Β"));
        break;
    case multiplication:
        matrixC = multiplication_matrix(choose_matrix("A"), choose_matrix("Β"));
        break;
    default:
        puts("Η επίλογη αυτή δεν υπάρχει");
    }

    return matrixC;
}

//βρίσκει τον συμπαράγοντα πίνακα Αxy
//@επιστρέφει structure με τον συμπαράγοντα
struct matrix cofactor(struct matrix A, int x, int y) {
#ifdef DEBUG
    puts("αρχη της cofactor");
#endif // DEBUG

    int n = A.rows;
    struct matrix B;
    B.rows = B.cols = n-1;
    int a=0, b=0;

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(i!= x && j!= y) {
                B.mat[a][b] = A.mat[i][j];
                if(++b == n-1) {
                    a++;
                    b=0;
                }
            }
        }
    }

    return B;
}

//υπολογίζει ορίζουσα ενός πίνακα
//@επιστρέφει την ορίζουσα
double det(struct matrix A) {
#ifdef DEBUG
    printf("\nΑΡΧΗ ΤΗΣ DEF\nδιαστάσεις: %d\n", n);
#endif // DEBUG
    int n = A.rows;
    double d=0;
    double *pd = &d;

    if(n == 1)
        *pd = A.mat[0][0];
    else {
        for(int j = 0; j<n; j++) {
            int sign =pow(-1, (j+1)+1);
            printf("sign: %d\n", sign);
            *pd += sign * A.mat[0][j] * det(cofactor(A, 0, j));
        }
    }
    return *pd;
}



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

void print_matrix(struct matrix A){
    for(int i=0; i<A.rows; i++){
        for(int j=0; j<A.cols; j++)
            printf("%.3lf ",A.mat[i][j]);
        puts("");
    }
}
