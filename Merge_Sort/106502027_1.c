#include <stdio.h>
#define MAXLEN 30000

void merge(long int arr[], int front, int mid, int rear)
{
    int i, j, k, n1, n2;

    n1 = mid - front + 1;
    n2 =  rear - mid;

    //long int L[n1], R[n2];
    long int *L,*R;

    L = malloc(sizeof(long int) * n1);
    R = malloc(sizeof(long int) * n2);

    for (i = 0 ; i < n1 ; i++)
        L[i] = arr[front + i];
    for (j = 0 ; j < n2 ; j++)
        R[j] = arr[mid + 1 + j];


    i = j = 0;
    k = front;
    while (i < n1 && j < n2){
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }


    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }


    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(long int tmp[], int front, int rear)
{
    if (front < rear){

        int mid = front + (rear-front)/2;

        mergeSort(tmp, front, mid);
        mergeSort(tmp, mid+1, rear);
        merge(tmp, front, mid, rear);
    }
}

void printArray(long int k[], int size)
{
    int i;

    for (i=0; i < size; i++)
        printf("%ld ", k[i]);

    printf("\n");
}

void clear(long int a[]){
int i;
    for(i = 0 ; i < MAXLEN ; i ++){
        a[i] = 0;
    }
}

int main()
{
    long int tmp[MAXLEN], temp;
    int N,i,n,sign;
    char c;

    scanf("%d\n",&N);

    for(i = 0 ; i < N ; i ++){
        temp = n = 0;
        sign = 1;
        clear(tmp);

        while((c=getchar())!='\n'){
            if (c == '-') {
                sign = -1;
            } else {
                if (c != ',')
                    temp = temp * 10 + (c-48);
                else {
                    tmp[n ++] = temp * sign;
                    temp = 0;
                    sign = 1;
                }
            }
        }
        tmp[n++] = temp * sign;
        mergeSort(tmp, 0, n - 1);
        printArray(tmp, n);
    }




    //printf("\nSorted array is \n");

    return 0;
}
