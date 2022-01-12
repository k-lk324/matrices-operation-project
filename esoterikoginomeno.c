

double esgin(struct matrix A, struct matrix B)

if(A.rows == B.rows && A.cols == B.cols) {


     double p;

        for(int i=0; i<A.rows; i++)
           {
                for(int j=0; j<A.cols; j++)
                    {
                        p=A.mat[i][j]* B.mat[i][j];
                        esgin+=p;
                    }
            }

        return esgin;

}
