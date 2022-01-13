double ixnos(struct matrix A){

     if(A.rows == A.cols ) {

          int trace=0.0;
          double k =0.0;

             for(int i=0; i<A.rows; i++)
                {
                     for(int j=0; j<A.cols; j++)
                         {
                             if(i==j)
                                 k=A.mat[i][j];
                             else
                                 k=0.0;

                             trace+=k;
                         }
                 }

             return trace;
     }
