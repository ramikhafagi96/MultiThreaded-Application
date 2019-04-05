//
// Created by rami96 on 11/15/18.
//

#ifndef MULTITHREADING_LAB2_MERGESORT_INT_H
#define MULTITHREADING_LAB2_MERGESORT_INT_H

#include "../ImportantIncludes.h"
void* thread_sortFunc(void* arg);
void mergeSort(int low,int high);
void merge(int l,int m,int r);
void MergeSortDriver();
/*Read Function For Reading The Array To Be Sorted From File*/
void ReadFileMergeSort(FILE *InputFile);

/*This Global Vector Is Used To Hold The Array*/



#endif //MULTITHREADING_LAB2_MERGESORT_INT_H
