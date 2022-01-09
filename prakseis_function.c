struct matrix matrix_result(int operation){

    //δημιουργία συστοιχίας αποτελέσματος
    struct matrix matrixC;

    //περιπτώσεις πράξεων
    enum {sum=1, subtraction, multiplication};
        switch(operation)
    {
        case sum:
            //matrixC = πρόσθεση(matrix("A"), matrix("Β"));
            break;
        case subtraction:
            //matrixC = αφαίρεση(matrix("A"), matrix("Β"));
            break;
        case multiplication:
            //matrixC = πολ/σμος(matrix("A"), matrix("Β"));
            break;
        default:
        printf("Η επίλογη αυτή δεν υπάρχει\n");
    }
  
  //επιστέφει το αποτέλεσμα
    return matrixC;
}
