

double esgin(struct matrix A, struct matrix B){

     if(A.rows == B.rows && A.cols == B.cols) {
     double p=0.0;

        for(int i=0; i<A.rows; i++)
                for(int j=0; j<A.cols; j++)
                        p+=A.mat[i][j]* B.mat[i][j];

        return p;
     }
}
