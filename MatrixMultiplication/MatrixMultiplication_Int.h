//
// Created by rami96 on 11/15/18.
//

#ifndef MULTITHREADING_LAB2_MATRIXMULTIPLICATION_INT_H
#define MULTITHREADING_LAB2_MATRIXMULTIPLICATION_INT_H
#include "../ImportantIncludes.h"
/*Used To Hold Information Used To Do Multiplication Operation*/
/*this information is passed to the thread function*/
typedef struct {
    int row;
    int column;
} mult_operationInfo;



/*This Vector Will Be Used To Push_Back into The Matrices*/
typedef vector<int> Row;

/*A Thread For Each Element In The Matrix*/
void* mult1(void *info);
/*A Thread For Each Row In The Matrixx*/
void* mult2(void *info);
/*Matrix Multiplication First Method Threads Creation*/
void MatrixMultiplication1(int matC_size);
/*Matrix Multiplication Second Method Threads Creation*/
void MatrixMultiplication2(int matC_size);
void PrintMatrix();
/*Read Function For Reading The Matrix From File*/
void ReadFileMatrix(FILE *InputFile);
//Program Driver
void MatrixMultiplicationDriver();
void WriteMatrixToFile();

#endif //MULTITHREADING_LAB2_MATRIXMULTIPLICATION_INT_H
