#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>

void printArray(double **matrix, int rowsOfMatrix, int colsOfMatrix)
{
    int i,j;
    for (i = 0;i<rowsOfMatrix;i++)
    {
        for (j = 0;j<colsOfMatrix;j++)
        {
            printf("%lf ",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

double** multiply(double **a, double **b, int rowsOfA, int colsOfA, int rowsOfB, int colsOfB)
{
    int i,j,k;
    double sum;
    double** ptr = (double**)malloc((rowsOfA)*sizeof(double*));
    for (int i = 0;i<rowsOfA;i++)
    {
        ptr[i] = (double*)malloc(colsOfB*sizeof(double));
    }

    if (!(colsOfA == rowsOfB))
    {
        exit(EXIT_FAILURE);
    }
    else
    {
        for (i = 0;i<rowsOfA;i++)
        {
            for (j = 0; j<colsOfB;j++)
            {
                sum = 0;
                for (k = 0;k < rowsOfB;k++)
                {
                    sum = sum + a[i][k] * b[k][j];
                }
                ptr[i][j] = sum;
            }
        }
    }
    return ptr;
}

double** transpose(double **a, int rows, int cols)
{
    
    double** ptr = (double**)malloc((cols)*sizeof(double*));
    for (int i = 0;i<cols;i++)
    {
        ptr[i] = (double*)malloc(rows*sizeof(double));
        for (int j = 0; j < rows;j++)
        {
            ptr[i][j] = a[j][i];
        }
    }
    return ptr;
}

double **inverse(double **M, int rows, int cols)
{
    double** N = (double**)malloc((rows)*sizeof(double*));
    int n = cols;
    for (int i = 0;i<rows;i++)
    {
        N[i] = (double*)malloc(cols*sizeof(double));
        for (int j = 0;j<rows;j++)
        {
            if (i != j)
            {
                N[i][j] = 0;
            }
            else 
            {
                N[i][j] = 1;
            }
        }
    }
    if (rows != cols)
    {
        exit(EXIT_FAILURE);
    }
    else
    {
        for (int p = 0;p<n;p++)
        {
            double f = M[p][p];
            for (int j = 0;j<n;j++)
            {
                M[p][j] = M[p][j] / f;
                N[p][j] = N[p][j] / f; 
            }
            for (int i = p+1;i<n;i++)
            {
                f = M[i][p];
                for (int k = 0;k<n;k++)
                {
                    M[i][k] = M[i][k] -  (M[p][k] * f);
                    N[i][k] = N[i][k] -  (N[p][k] * f); 
                }
            }
        }
        for (int p = n-1;p>=0;p--)
        {
            for (int i = p-1;i>=0;i--)
            {
                double f = M[i][p];
                for (int k = 0;k<n  ;k++)
                {
                    M[i][k] = M[i][k] -  (M[p][k] * f);
                    N[i][k] = N[i][k] -  (N[p][k] * f); 
                }
            }
        }
    }
    return N;
}

void freeMatrix(double **M,int rows)
{
    for (int i = 0;i<rows;i++)
    {
        free(M[i]);
    }
    free(M);
}
int main(int argc, char *argv[])
{ 
    FILE *fp = fopen(argv[1],"r");
    char *useless = (char*)malloc(15*sizeof(char));
    int k; //columns
    int n; //rows
    double tempTrain; //temp var for fscanf
    fscanf(fp, "%5s", useless);
    fscanf(fp, "%d",&k); 
    k += 1;
    fscanf(fp,"%d",&n);
    if (fp == NULL)
    {
        printf("Error reading file");
        exit(EXIT_FAILURE);
    }
    double** X = (double**)malloc((n)*sizeof(double*));
    double** Y = (double**)malloc((n)*sizeof(double*));
    for (int i = 0;i<n;i++)
    {
        X[i] = (double*)malloc(k*sizeof(double));
        Y[i] = (double*)malloc(1*sizeof(double));
        for (int j = 0; j < k;j++)
        {
            fscanf(fp,"%lf",&tempTrain);
            if (j == k-1)
                Y[i][0] = tempTrain;
            else if (j == 0)
            {
                X[i][0] = 1;
                X[i][j+1] = tempTrain;
            }
            else
                X[i][j+1] = tempTrain;
        }
    }
    double **xTransposed = transpose(X,n,k);
    double **XTX = multiply(xTransposed,X,k,n,n,k);
    double **xInversed = inverse(XTX,k,k);
    double **xInversedMultiplied = multiply(xInversed,xTransposed,k,k,k,n);
    double **W = multiply(xInversedMultiplied,Y,k,n,n,1);

    FILE *dp = fopen(argv[2],"r");
    char *uselessTwo = (char*)malloc(15*sizeof(char));
    int p; //attributes, cols
    int m; //houses, rows
    double sum;
    double tempData;
    fscanf(dp, "%4s", uselessTwo);
    fscanf(dp, "%d",&p);
    fscanf(dp, "%d",&m);
    for (int i = 0;i<m;i++)
    {
        sum = W[0][0];
        int count = 1;
        for (int j = 0;j<p;j++)
        {
            fscanf(dp,"%lf",&tempData);
            sum += (W[count++][0] * tempData);
        }
        printf("%.0f\n",sum);
    }
    freeMatrix(X,n);
    freeMatrix(Y,n);
    freeMatrix(xTransposed,k);
    freeMatrix(XTX,k);
    freeMatrix(xInversed,k);
    freeMatrix(xInversedMultiplied,k);
    freeMatrix(W,k);
    free(useless);
    free(uselessTwo);
    return EXIT_SUCCESS;
}