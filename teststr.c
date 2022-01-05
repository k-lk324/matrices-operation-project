struct array
{
    int arr[8];
};
struct array getarray()
{
    struct array y;
    printf("Enter the elements in an array : ");
    for(int i=0;i<8;i++)
    {
        scanf("%d",&y.arr[i]);
    }
    return y;
}

////

struct matrix
{
    int rows, cols;
    double mat[ROWS_MAX][COLS_MAX];
};

struct matrix getmatrix()
{

    struct matrix y;

    //διαστάσεις
    printf("\nΔώσε διαστάσεις\nΓραμμές: ");
    scanf("%d", &y.rows);
    printf("Στήλες: ");
    scanf("%d", &y.cols);

    //εισαγωγη στοιχειων
    printf("\nΔώσε στοιχεία πίνακα χωρισμένα με κένο\n");
    printf ("π.χ. ένας πίνακας 2x3:\n1 0 45.87\n2 5.8 89\n\n");

    for (int i=0; i<y.rows; i++){
        for (int j=0; j<y.cols; j++)
            scanf("%lf", &y.mat[i][j]);
    }
    return y;
}
