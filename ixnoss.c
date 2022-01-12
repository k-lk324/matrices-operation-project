int main()
{

double ixnos(struct matrix A)

if(A.rows == A.cols ) {


     double k;

        for(int i=0; i<A.rows; i++)
           {
                for(int j=0; j<A.cols; j++)
                    {
                        if(i=j)
                            k=A.mat[i][j];
                        else
                            k=0;

                        ixnos+=k;
                    }
            }

        return ixnos;

}
