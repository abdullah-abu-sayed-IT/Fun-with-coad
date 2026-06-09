#include<stdio.h>
#include<stdlib.h>

int main() {
    int ar[3],i,sum=0;
    printf("Input the numbers ");
    for (i=0; i<3; i++)
        scanf("%d",&ar[i]);


    for (i=0; i<3; i++)
    {
        printf("%d",ar[i]);
        sum = sum + ar[i];
    }

    printf("total is %d\n",sum);



    return 0;
}
