#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int num_Digits (int n) {
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    /*      2147483647 is 2^31-1 - add more ifs as needed
       and adjust this final return as well. */
    return 10;
}

char* int_to_string (int val)
{
    int num = num_Digits(val);

    char* buffer = malloc( num + 1);

    sprintf(buffer, "%d", val);

    return buffer;
}

char* my_strcat (char* fst, char* snd)
{
    int strl1 = strlen(fst), strl2 = strlen(snd), size = strl1 + strl2;
    char* buffer = malloc(size + 1);

    for (int i = 0 ;  i < size ; i++)
    {
        if (i < strl1) buffer[i] = fst[i];
        else buffer[i] = snd[i-strl1]; 
    }

    buffer[size] = 0;

    return buffer;
}

void teste (char* data)
{


    int max = strlen(data) + 1;

    for (int i = 0 ; i<max ; i++)
    {
        if (data[i] == ' ' || data[i] == ':' || data[i] == '-')
        {
            for (int j = i ; j<max ; j++)
            {
                data[j] = data[j+1];
            }
            data[max--] = 0;
            i--;
        }
        
    }

    printf("%s \n%d\n", data, strlen(data) == 14);
}

void function (int* N)
{
    int i;
    *N = 10;

    i = 10;
}

int strtonum (char* str, int *num)
{
    *num = 0;
    for (int i = 0 ; str[i] ; i++)
    {
        if (isdigit(str[i]))
            (*num) = ((*num) * 10) + (str[i] - 48);
        else 
        {
            (*num) = 0;
            return 0;
        }
    }

    return 1;
}

int procura (int *array, int N, int val)
{
    int start = (val <= N/2) ?0 :(N/2), i;

    for (i = start ; i<N && array[i]<val ; i++);

    return (array[i] > val) ?-1 :i;
}

int procura2 (int *array, int N, int val)
{
    for (int i = 0 ; i<N ; i++)
    {
        if (array[i]>val) return -1;
        if (array[i]==val) return i;
    }

    return -1;
}

int procura3 (int *array, int beg, int end, int val)
{
    int mid;

    for (mid = ((end + beg)/2) ; (end - beg-1) ; mid = ((end + beg)/2))
    {
        if (val < array[mid]) end = mid;
        else if (val > array[mid]) beg = mid;
        else return mid;
    }

    return -1;
}

int binarySearch(int arr[], int l, int r, int x)
{
    if (r >= l) {
        int mid = (l+r)/2;
 
        // If the element is present at the middle
        // itself
        if (arr[mid] == x)
            return mid;
 
        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);
 
        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid + 1, r, x);
    }
 
    // We reach here when element is not
    // present in array
    return -1;
}

void radix_lsd (int *array, int N)
{
    int i;
    int *b;
    int maior = array[0];
    int exp = 1;

    b = calloc(N, sizeof(int));

    for (i=0 ; i<N ; i++)
        if (array[i] > maior) maior = array[i];

    while (maior/exp)
    {
        int bucket [10] = {0};

        for (i=0 ; i<N ; i++)
            bucket[(array[i]/exp)%10]++;
        
        for (i=1 ; i<10 ; i++)
            bucket[i] += bucket[i-1];

        for (i=N-1 ; i>=0 ; i--)
            b[--bucket[(array[i]/exp)%10]] = array[i];

        for (i=0 ; i<N ; i++)
            array[i] = b[i];

        exp *= 10;
    }

    free(b);
}

void quicksort (int *array, int beg, int end)
{
    int i = beg, j = end-1;
    int pivot = array[(beg+end)/2];

    while (i<=j)
    {
        while (array[i]<pivot && i<end)
            i++;
        
        while (array[j]>pivot && j>beg)
            j--;

        if (i<=j)
        {
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;  // i = i+1
            j--;
        }
    }

    if (j>beg)
        quicksort(array, beg, j+1);

    if (i<end)
        quicksort(array, i, end);
}

void print_array (int *array, int N)
{
    printf("{ ");
    for (int i = 0 ; i<N ; i++)
        printf("%d ", array[i]);
    printf("}\n");
}

int main ()
{
    int size = 10000000;
    int *array = malloc(size * sizeof(int));
    int *array2 = calloc(size, sizeof(int));

    srand(time(NULL));

    for (int i = 0 ; i<size ; i++)
    {
        int random = rand() % 9;
        // int random = i;
        array[i] = random;
        array2[i] = random;
    }

    array[10] = array2[10] = 99999;

    clock_t fst, snd;

    double tm1, tm2;

    fst = clock();

    quicksort(array, 0, size);

    snd = clock();

    tm1 = (double)(snd-fst) / CLOCKS_PER_SEC;

    fst = clock();

    radix_lsd(array2, size);

    snd = clock();

    tm2 = (double)(snd-fst) / CLOCKS_PER_SEC;

    printf("Tempo com:\n\tQuicksort: %lf\n\tRadixLSD: %lf\n", tm1, tm2);

    // print_array(array, size);
    // print_array(array2, size);


    return 0;
}