# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>

void generate_random_array(int arr[],int n){
    for(int j=0; j<n ; j++){
        arr[j]=rand() % 4;
    }
}

int** allocate_Matrix(int n) {
    int** matrix = (int**) malloc(n * sizeof(int*));  
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*) malloc (n* sizeof(int));
        for(int j = 0; j < n; j++){
            matrix[i][j]=0;
        }
    }
    return matrix;
}

void free_matrix(int** mat, int size) {
    for (int i = 0; i < size; i++) {
        free(mat[i]);
    }
    free(mat);
}

int** multiply_matrix(int **mat1, int **mat2, int n){

    int** matrix = allocate_Matrix(n);

    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++)
            matrix[i][j] += mat1[i][k] * mat2[k][j];  
        }
    }
    return matrix;
}

int** add_matrix(int **A, int **B, int n){
    int** mat = allocate_Matrix(n);

    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            mat[i][j] = A[i][j] + B[i][j];  
        }
    }
    return mat;
}

int** subt_matrix(int **A, int **B, int n){
    int** mat = allocate_Matrix(n);

    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            mat[i][j] = A[i][j] - B[i][j];  
        }
    }
    return mat;
}


int ** Strassen_method(int **A, int **B, int n){
    if (n == 1){
        int** C = allocate_Matrix(1);
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }
    
    int newsize=n/2;
    int** A11 = allocate_Matrix(newsize);   // Top-left
    int** A12 = allocate_Matrix(newsize);   // top-right
    int** A21 = allocate_Matrix(newsize);   // bottom-left
    int** A22 = allocate_Matrix(newsize);   // bottom-right

    int** B11 = allocate_Matrix(newsize);   // Top-left
    int** B12 = allocate_Matrix(newsize);   // top-right
    int** B21 = allocate_Matrix(newsize);   // bottom-left
    int** B22 = allocate_Matrix(newsize);   // bottom-right


    for (int i=0; i<newsize; i++){      // Top-left
        for(int j=0; j<newsize; j++){ 
            
        A11[i][j] = A[i][j] ;
        B11[i][j] = B[i][j] ; 
        }
    }
    for (int i=0; i<newsize; i++){      // top-right
        for(int j=newsize; j<n; j++){  
            
        A12[i][j-newsize] = A[i][j] ;
        B12[i][j-newsize] = B[i][j] ; 
            
        }
    }
    for (int i=newsize; i<n; i++){      // bottom-left 
        for(int j=0; j<newsize; j++){   
            
        A21[i-newsize][j] = A[i][j] ;
        B21[i-newsize][j] = B[i][j] ; 
        }
    }
    for (int i=newsize; i<n; i++){      // bottom-right
        for(int j=newsize; j<n; j++){ 

        A22[i-newsize][j-newsize] = A[i][j] ;
        B22[i-newsize][j-newsize] = B[i][j] ; 
        }
    }

// Strassen's 7 products with proper memory management
    int **S1 = add_matrix(A11, A22, newsize); 
    int **S2 = add_matrix(B11, B22, newsize);

    int **M1 = Strassen_method(S1, S2, newsize); // M1

    free_matrix(S1, newsize);
    free_matrix(S2, newsize);

    S1 = add_matrix(A21, A22, newsize);
    int **M2 = Strassen_method(S1, B11, newsize);   // M2
    free_matrix(S1, newsize);

    S1 = subt_matrix(B12, B22, newsize);
    int **M3 = Strassen_method(A11, S1, newsize);   // M3
    free_matrix(S1, newsize);

    S1 = subt_matrix(B21, B11, newsize);
    int **M4 = Strassen_method(A22, S1, newsize);
    free_matrix(S1, newsize);                       //M4

    S1 = add_matrix(A11, A12, newsize);
    int **M5 = Strassen_method(S1, B22, newsize);   // M5
    free_matrix(S1, newsize);

    S1 = subt_matrix(A21, A11, newsize);
    S2 = add_matrix(B11, B12, newsize);
    int **M6 = Strassen_method(S1, S2, newsize);    // M6
    free_matrix(S1, newsize);
    free_matrix(S2, newsize);

    S1 = subt_matrix(A12, A22, newsize);
    S2 = add_matrix(B21, B22, newsize);
    int **M7 = Strassen_method(S1, S2, newsize);   //M7
    free_matrix(S1, newsize);
    free_matrix(S2, newsize);
    
    // Calculating result quadrants
    int **C11_temp1 = add_matrix(M1, M4, newsize);
    int **C11_temp2 = subt_matrix(M7, M5, newsize);

    int **C11 = add_matrix(C11_temp1, C11_temp2, newsize);
    free_matrix(C11_temp1, newsize);
    free_matrix(C11_temp2, newsize);

    int **C12 = add_matrix(M3, M5, newsize);
    int **C21 = add_matrix(M2, M4, newsize);

    int **C22_temp1 = subt_matrix(M1, M2, newsize);
    int **C22_temp2 = add_matrix(M3, M6, newsize);
    
    int **C22 = add_matrix(C22_temp1, C22_temp2, newsize);
    free_matrix(C22_temp1, newsize);
    free_matrix(C22_temp2, newsize);


    int** C = allocate_Matrix(n);

    for (int i = 0; i < n/2; i++) {
        for (int j = 0; j < n/2; j++) {
            C[i][j] = C11[i][j];                         // Top-left
            C[i][j + n/2] = C12[i][j];                   // Top-right
            C[i + n/2][j] = C21[i][j];                   // Bottom-left
            C[i + n/2][j + n/2] = C22[i][j];             // Bottom-right
        }
    }

    free_matrix(A11, newsize); free_matrix(A12, newsize);
    free_matrix(A21, newsize); free_matrix(A22, newsize);
    free_matrix(B11, newsize); free_matrix(B12, newsize);
    free_matrix(B21, newsize); free_matrix(B22, newsize);
    free_matrix(M1, newsize);  free_matrix(M2, newsize);
    free_matrix(M3, newsize);  free_matrix(M4, newsize);
    free_matrix(M5, newsize);  free_matrix(M6, newsize);
    free_matrix(M7, newsize);  
    free_matrix(C11, newsize); free_matrix(C12, newsize);
    free_matrix(C21, newsize); free_matrix(C22, newsize);

    return C;
}


int main(){
    int n, p;
    printf("Enter positive power of 2 for order of matrix:");
    scanf("%d",&p);

    n=pow(2, p);

    int* array1 = (int*)malloc((n*n)* sizeof(int));
    int* array2 = (int*)malloc((n*n)* sizeof(int));
    if (array1==NULL || array2==NULL){
        printf("Memory allocation failed");
        return 0;
    }

    int **mat1 = allocate_Matrix(n);
    int **mat2 = allocate_Matrix(n);
      
    generate_random_array(array1,(n*n));
    generate_random_array(array2,(n*n));

    int k=0;
    for(int i=0;i<n;i++){
        for (int j=0; j<n;j++){
            mat1[i][j]=array1[k];
            mat2[i][j]=array2[k];
            k++;
        }
    }

    clock_t start=clock();
    for (int i=0; i<1000; i++){   // 1000 times 
        Strassen_method(mat1, mat2, n);   // IT CREATES NUMEROUS MEMORY LEAKS
    }  
    clock_t end=clock();

    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;

    printf("Time taken to multiply 2 matrices of order %d using divide and conquer is : %f seconds\n",n ,time_taken);
    
    free (array1);
    free (array2);

    free_matrix(mat1,n);
    free_matrix(mat2,n);

    return 0;
} 

