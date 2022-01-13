double ixnos(struct matrix A){

     if(A.rows == A.cols ) {

          double trace=0; //θέλουμε να ειναι double ετσι ωστε η τιμη που επιστρεφουμε να ειναι και αυτη double 
          double k=0; //δεν χρειαζεται να βαλουμε 0.0 γτ ο υπολογιστης το μετατρεπει αυτοματα σε δεκαδικο επειδη γραψαμε απο μπροστα double
          
          //αν θεταμε int a = 2.43 τοτε αυτο επιστρεφει το ακεραιο μερος δλδ a=2
          //αν θέταμε double b = 3.3432 τοτε αυτο επιστρέφει 3.343200 ή αν θέταμε double c = 3 τότε αυτο επιστρέφει 3.000000

             for(int i=0; i<A.rows; i++)
                {
                     for(int j=0; j<A.cols; j++)
                         {
                             if(i==j)
                                 k=A.mat[i][j];
                             else
                                 k=0;

                             trace+=k;
                         }
                 }

             return trace;
     }
