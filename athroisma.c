#include<stdio.h>

int main(void)
{
    int n, guess,sum=0;

    printf("dose enan akeraio arithmo:");
    scanf ("%d", & n);
    printf ("Mantepse to apotelesma:");
    scanf("%d", & guess);

    for (int i=1; i<=n; i++)
        {
            printf("%d", i);
            printf("%c",i<n ? '+' : '=' );
            sum += i;

        }

    printf("%d\n", sum);


    sum==guess ? printf ("sosto") : printf("lathos");

    return 0;







}
