//
// Created by rami96 on 11/15/18.
//
#include "MergeSort_Int.h"
vector<int> array;
int array_size=0;
int thread_part=0;
void merge(int l,int m,int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = array[l + i];
    for (j = 0; j < n2; j++)
        R[j] = array[m + 1+ j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            array[k] = L[i];
            i++;
        }
        else
        {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        array[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int low,int high)
{
    if(low<high)
    {
        int mid = low+(high-low)/2;
        mergeSort(low,mid);
        mergeSort(mid+1,high);
        merge(low,mid,high);
    }
}

/*A Thread For Each Half Of The Array To Be Sorted*/
void* thread_sortFunc(void* arg)
{
    int low=0,high=0;

    if(thread_part==0)
    {
        //Working on first part
        low = 0;
        high = (array_size-1)/2;
        thread_part=1;
    }

    else
    {
        //Working on second part
        low =  ((array_size-1)/2)+1;
        high = array_size-1;
        thread_part=0;
    }

    int mid = low + (high - low) / 2;
    if (low < high) {
        mergeSort(low, mid);
        mergeSort(mid + 1, high);
        merge(low, mid, high);
    }
}

void ReadFileMergeSort(FILE *InputFile)
{
    size_t len = 0;
    char *input = NULL, *token=NULL; //Input: to read the line and token: for tokenization of line
    char read_locater = 0; //Used to determine where am i in the file

    while(!feof(InputFile))
    {
        getline(&input, &len, InputFile); //read this line
        char *newline = strchr(input, '\n'); //used to remove the new line character
        if (newline)
            *newline = 0;
        token = strtok(input, " ");
        if(read_locater==0)
        {
            array_size = atoi(token);
            array.resize(array_size,0);
            read_locater++;
        }

        else
        {
            for(int i=0;i<array_size;i++)
            {
                array[i] = atoi(token);
                token = strtok(NULL," ");
            }
        }
    }



}


void MergeSortDriver()
{
    FILE *InputFile;
    InputFile = fopen("/home/rami96/CLionProjects/MultiThreading_Lab2/MergeSort/inputSort.txt","r");
    ReadFileMergeSort(InputFile);
    pthread_t threads[2];
    printf("Array Before Sorting:\n");
    for (int i = 0; i <array_size ; ++i) {
        printf("%d ",array[i]);
    }
    printf("\n");
    for (int i = 0; i < 2; i++)
        pthread_create(&threads[i], NULL, thread_sortFunc,
                       (void*)NULL);

    for (int i = 0; i < 2; i++)
        pthread_join(threads[i], NULL);

    //We here merge the two subproblems
    merge(0,(array_size-1)/2,array_size-1);

    printf("Array After Sorting:\n");
    for (int i = 0; i <array_size ; ++i) {
        printf("%d ",array[i]);
    }
}

