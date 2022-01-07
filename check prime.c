#include <stdio.h>

int main()

{
    int n,i,isPrime=0;
    printf("this program only will verify positive prime number");
    printf("\ninput your number :");
    scanf("%d",&n);
    fflush(stdin);


    for (i = 2; i <= sqrt(n); i++)
        {

        //any composite integer  n  must have at least one factor <= n^1/2
        if (n % i == 0)
            {

                if (n<=1)
                {
                    printf("%d is not a prime number", n);
                    isPrime=1;
                }
                isPrime=1;
                printf("%d is not a prime number", n);
                break;

            }
        }
    if (isPrime != 1)
    {
        printf("%d is  a prime number", n);
    }



    return 0;

}
