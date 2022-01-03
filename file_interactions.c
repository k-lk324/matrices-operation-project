#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*int rowsOfMatrix(char *filename); //filename --> �������������
int colsOfMatrix(char *filename); */

//���������� �������� ��� ���������� �� txt file
bool save_matrix(){

    //������������� ������
    printf("\n���� ������������� ������: ");
    char name[50];
    scanf("%s", name);

    //����������
    int r,c;
    printf("\n���� ����������\n�������: ");
    scanf("%d", &r);
    printf("������: ");
    scanf("%d", &c);

    //��������� �� ����� ��� ������ ��� �� ������ �� ������������ �� ����������
    FILE* am_file;
    am_file = fopen("available_matrix.txt", "a");
    fprintf (am_file,"%s\n",name);
    fclose(am_file);

    //�� ����� �������� ��������� ����� ��� �� ��������� ������
    if(c == 0){
        FILE* vector_file;
        vector_file = fopen ("vectors.txt", "a");
        fprintf(vector_file,"%s\n",name);
        fclose(vector_file);
    }


    //�������� ��� �������� ".txt" ��� �������������
    strcat(name, ".txt");

    //����������� ������ "�������������".txt
    FILE *file;
    file = fopen(name, "w");

    //������ 2 ������ ������ ��� ����������
    fprintf(file, "%d\n%d\n", r,c);

    //���� �� �������� ��� ������ ��� ������ �� ��� ������
    printf("\n���� �������� ������ ��������� �� ����\n");
    printf ("�.�. ���� ������� 2x3:\n1 0 45\n2 5 89\n\n");

        for (int i=0; i<r; i++){
            for (int j=0; j<c; j++){
                double element;
                scanf("%lf", &element);
                fprintf(file, "%lf ", element);
            }

            fprintf(file, "\n");
        }

    //������ �� ������
    fclose(file);


    return true;
}

//������� ���� ����������� �������
bool show_matrixes(){
    FILE* AM;
    AM = fopen("available_matrix.txt", "r");

    char matrixName[50];
    //��������� ����� �� ����� ��� �������
     while ((fscanf(AM,"%s",matrixName))!=EOF){
        printf("%s\n", matrixName);
     }

    return true;
}


int main()
{

    return 0;
}
