#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

    char command;
    printf("[----- [한민우]  [2018038047] -----]\n");

    int row = 0 , col = 0;
    srand(time(NULL));

    while(1){              // 숫자가 아닌 값이나 0 이하의 숫자를 입력시 재입력 하도록 반복
        printf("Input row and col : ");
        int checknum = scanf("%d %d", &row, &col);
        
        if(checknum == 2 && row > 0 && col > 0) break;

        else {
            printf("Check the size of row and col!\n");
            while(getchar() != '\n'); // 입력버퍼 비우기
        }
    }

    /* matrix 동적 할당 */
    int** matrix_a = create_matrix(row, col);
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);

    if (matrix_a == NULL || matrix_b == NULL) {
        printf("Matrix is not created.\n");
        return -1;
        }

    printf("Matrix Created.\n");

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");
        
        while(1){             // 잘못된 값 입력시 재입력 하도록 반복
            printf("Command = ");
            int checkchar = scanf(" %c", &command);
            if(checkchar == 1) break;
            else {
                printf(" Check your Command!\n");
                while(getchar() != '\n'); // 입력버퍼 비우기
            }
        }

        switch(command) {
        /* matrix initialize */
        case 'z': case 'Z':
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;

        /* print matrix */
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;

        /* add matrix */
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;

        /* subtract matrix */
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        
        /* transpose matrix */
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, row, col);
            break;

        /* matrix multiply */
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;

        /* quit program */
        case 'q': case 'Q':
            /* 동적 할당된 메모리 해제 */
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        
        /* user input error */
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');
    /* 동적 할당된 메모리 해제 */
    free_matrix(matrix_a_t, col, row);
    free_matrix(matrix_a, row, col);
    free_matrix(matrix_b, row, col);
    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    int **arr = (int**)malloc(sizeof(int*)*row);
    
    /* check pre conditions */
    if(row <= 0 || col <=0) {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }
   
    arr[0] = (int*)malloc(sizeof(int)*row*col);
    for( int i=1; i<row; i++) arr[i] = arr[i-1] + col;

    /* check post conditions */
    if(arr==NULL) {
        printf("create matrix failed");
        return NULL;
        }

    return arr;
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    for( int i = 0; i < row; i++){
        for( int j = 0; j < col; j++){
            printf(" %4d ",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    free(matrix[0]);
    free(matrix);
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
         /* check pre conditions */
    if(matrix == NULL || row<=0 || col<=0){
        printf("Check matrix,row and col!\n");
        return -1;
    }

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            matrix[i][j] = rand() % 20;
        }
    }
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
          /* check pre conditions */
    if(matrix_a == NULL || matrix_b == NULL || row <= 0 || col <= 0){
        printf("Check matrix,row and col!\n");
        return -1;
    }

    /* make temporary for storage added matrix */
    int** matrix_sum = create_matrix(row,col);

     /* add two matrices */
    for(int i=0; i < row; i++){
        for(int j=0; j < col; j++){
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];
        }
    }

        /* print added matrix */
    print_matrix(matrix_sum,row,col);

        /* free allocated matrix */
    free_matrix(matrix_sum, row, col);
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
           /* check pre conditions */
    if(matrix_a == NULL || matrix_b == NULL || row <= 0 || col <= 0){
        printf("Check matrix,row and col!\n");
        return -1;
    }

    /* make temporary for storage subtracted matrix */
    int** matrix_sub = create_matrix(row,col);

    /* subtract two matrices */
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            matrix_sub[i][j] = matrix_a[i][j] + matrix_b[i][j];
        }
    }

     /* print subtracted matrix */
    print_matrix(matrix_sub,row,col);

    /* free allocated matrix */
    free_matrix(matrix_sub, row, col);
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
        /* check pre conditions */
    if(matrix == NULL || matrix_t == NULL || row <= 0 || col <= 0){
        printf("Check matrix,row and col!\n");
        return -1;
    }
        /* make transposed matrix matrix_t */
    for(int i = 0;i < row;i++){
        for(int j=0;j<col;j++) matrix_t[i][j] = matrix[j][i];
    }
        /* check post conditions */
        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                if(matrix_t[i][j] != matrix[j][i])
                printf("Transpose the matrix failed.\n");
                return -1;
            }
        }
}

/* matrix_axt = matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    /* check pre conditions */
    if(matrix_a == NULL || matrix_t == NULL || row <= 0 || col <= 0){
        printf("Check matrix,row and col!\n");
        return -1;
    }
    /* make temporary for storage multiplied matrix */
    int** matrix_axt = create_matrix(row,col);

    /* multiply two matrices */
    for(int i = 0; i < row; i++){
        for(int j = 0; j< col; j++){
            for(int k = 0; k < row; k++){
                matrix_axt[i][j] += matrix_a[i][k] + matrix_t[k][j];
            }
        }
    }
    /* print multiplied matrix */
    print_matrix(matrix_axt,row,col);
    
    /* free allocated matrix */
    free_matrix(matrix_axt, row, col);
}

