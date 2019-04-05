//
// Created by rami96 on 11/15/18.
//
#include "MatrixMultiplication_Int.h"
/*Two arrays used to hold number of rows and columns for the three matrices*/
int num_rows[3];
int num_cols[3];


/*Define Three Global Matrices*/
typedef vector<vector<int>> Matrix;
Matrix matA;
Matrix matB;
Matrix matC;

/*First Method*/
/*A Thread For Each Element In The Matrix*/
void* mult1(void *info)
{
    mult_operationInfo *data = (mult_operationInfo*)info;
    int i;
    matC[data->row][data->column] = 0;
    for (i = 0; i < num_cols[0]; i++) {
        matC[data->row][data->column] += (matA[data->row][i] * matB[i][data->column]);
    }
    //Exit the thread
    free(data);
    pthread_exit(0);

}

/*Second Method*/
/*A Thread For Each Row In The Matrixx*/
void* mult2(void *info)
{
    mult_operationInfo *data = (mult_operationInfo*)info;
    for(int j=0;j<num_cols[1];j++)
    {
        for(int i=0;i<num_cols[0];i++)
        {
            matC[data->row][j] += (matA[data->row][i] * matB[i][j]);
        }
    }
}

/*Matrix Multiplication First Method Threads Creation*/
void MatrixMultiplication1(int matC_size) {
    pthread_t threads[matC_size];
    mult_operationInfo *info; //Info For Operation
    int tid = 0;//iterator for pthread array
    /* Process Matrix, by row, column */
    for (int row = 0; row < num_rows[2]; row++) {
        for (int column = 0; column < num_cols[2]; column++) {
            info = (mult_operationInfo *) malloc(sizeof(mult_operationInfo));
            info->row = row;
            info->column = column;
            pthread_create(&(threads[tid++]), NULL, mult1,
                           (void *) info);
        }
    }

    for (int i = 0; i < matC_size; i++) {
        pthread_join(threads[i], NULL);
    }
}

/*Matrix Multiplication Second Method Threads Creation*/
void MatrixMultiplication2(int matC_size)
{
    mult_operationInfo *info; //Info For Operation
    pthread_t threads[num_rows[2]];
    int tid=0;
    /*Process Matrix*/
    for(int row=0; row<num_rows[2]; row++)
    {
        info = (mult_operationInfo *) malloc(sizeof(mult_operationInfo));
        info->row = row;
        info->column = 0;
        pthread_create(&(threads[tid++]), NULL, mult2, (void*) info);
    }

    for (int i = 0; i < num_rows[2]; i++) {
        pthread_join(threads[i], NULL);
    }
}

void PrintMatrix()
{
    //Print out the resulting matrix
    for(int i = 0; i < num_rows[2]; i++) {
        for(int j = 0; j < num_cols[2]; j++) {
            printf("%d ", matC[i][j]);
        }
        printf("\n");
    }
}

void MatrixMultiplicationDriver()
{
    FILE *InputFile;
    InputFile = fopen("/home/rami96/CLionProjects/MultiThreading_Lab2/MatrixMultiplication/inputMatrix.txt","r");
    if (InputFile == NULL){
        printf("Could not open file");
        return;
    }
    ReadFileMatrix(InputFile);

    if(num_cols[0]!=num_rows[1])
    {
        printf("Invalid Matrices Sizes");
        exit(0);
    }

    else {
        num_rows[2] = num_rows[0];
        num_cols[2] = num_cols[1];
        int matC_size = num_rows[2] * num_cols[2];

        //Initialize The Matrix
        Row r(num_cols[2], 0);
        for (int i = 0; i < num_rows[2]; i++)
            matC.push_back(r);
        clock_t t;
        double time_taken;
        t = clock();
        MatrixMultiplication2(matC_size);
        PrintMatrix();
        t = clock() - t;
        time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
        cout<<"Time Taken By Method 1 = "<<time_taken<<"\n";
        t = clock();
        MatrixMultiplication1(matC_size);
        t = clock() - t;
        time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
        cout<<"Time Taken By Method 2 = "<<time_taken<<"\n";
        PrintMatrix();
    }
}

void ReadFileMatrix(FILE *InputFile)
{
    size_t len = 0;
    int mat_index = 0; //Used to determine which matrix i'm working on
    char *input = NULL, *token=NULL; //Input: to read the line and token: for tokenization of line
    char read_locater = 0; //Used to determine where am i in the file
    while (!feof(InputFile)) {
        getline(&input, &len, InputFile); //read this line
        char *newline = strchr( input, '\n' ); //used to remove the new line character
        if ( newline )
            *newline = 0;
        token = strtok(input, " "); //tokenize the first digit
        while (token != NULL) //This Loop Is For Processing of Text File
        {
            if (read_locater < 2) //this means i'm in the line that has the dimension of matrix
            {
                if (read_locater == 0) //this means this is row size
                    num_rows[mat_index] = atoi(token);
                else if(read_locater ==1) //this means this is column size
                    num_cols[mat_index] = atoi(token);

                read_locater++;


                token = strtok(NULL, " ");
            } else //Now I'm going to read the matrix data
            {

                if (mat_index == 0)
                {
                    while (token != NULL)
                    {
                        Row matRow(num_cols[mat_index]);
                        for(int m=0 ; m<num_rows[mat_index] ; m++)
                        {
                            for(int c=0 ; c<num_cols[mat_index] ; c++)
                            {
                                matRow[c] = atoi(token);
                                token = strtok(NULL, " ");
                            }
                            matA.push_back(matRow);
                            if(m<num_rows[mat_index]-1)
                            {
                                getline(&input, &len, InputFile);
                                char *newline = strchr(input, '\n');
                                if (newline)
                                    *newline = 0;
                                token = strtok(input, " ");
                            }
                        }
                    }
                }
                if (mat_index == 1)
                {
                    while (token != NULL)
                    {

                        Row matRow(num_cols[mat_index]);
                        for(int m=0 ; m<num_rows[mat_index] ; m++)
                        {
                            for(int c=0 ; c<num_cols[mat_index] ; c++)
                            {
                                matRow[c] = atoi(token);
                                token = strtok(NULL, " ");
                            }
                            matB.push_back(matRow);
                            if(m<num_rows[mat_index]-1)
                            {
                                getline(&input, &len, InputFile);
                                char *newline = strchr(input, '\n');
                                if (newline)
                                    *newline = 0;
                                token = strtok(input, " ");
                            }
                        }
                    }

                }
                mat_index++; //To Start Working On the Next Matrix
                read_locater=0;
            }

        }
    }
    fclose(InputFile);
}
