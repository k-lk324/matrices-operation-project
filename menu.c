#include <stdio.h>

//προβολή αρχικού μενού και επιστρέφει την επιλογή
int prime_menu(){

    //

    printf("ΠΡΑΞΕΙΣ ΠΙΝΑΚΩΝ\n\n\
           1.Δημιουργία συστυχίας\n\
           2.Προβολή διαθέσιμων πινάκων\n\
           3.Πράξεις πινάκων\n\
           4.Πράξεις διανυσμάτων\n\n");

    printf("Επιλογή: ");
    int choice;
    scanf("%d", &choice);

    return choice;

}


int main()
{
    enum {create_matrix, show_matrix,
        matrix_operations, vector_operarations};

    switch(prime_menu()) {

        case create_matrix:
            //δημιουργια πίνακα
            break;
        case show_matrix:
            //προβολή πίνακα
            break;
        case matrix_operations:
            //πραξεις πινάκων
            break;
        case vector_operations:
            //πράξεις διανυσμάτων
            break;
        //default:
            //stuff
    }

        default:


    }

    return 0;
}

