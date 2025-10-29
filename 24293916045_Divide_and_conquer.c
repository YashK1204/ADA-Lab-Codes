# include <stdio.h>
# include <stdlib.h>
# include <time.h>

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

int** add_matrix(int **A, int **B, int n){
    int** mat = allocate_Matrix(n);

    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            mat[i][j] = A[i][j] + B[i][j];  
        }
    }
    return mat;
}

int** trim_matrix(int** C,int n){
    int ** matrix= allocate_Matrix(n-1);
    for(int i=0; i<n-1;i++){
        for(int j=0; j<n-1; j++){
            matrix[i][j]=C[i][j];
        }
    }
    return matrix;
}

int ** Divide_and_Conquer(int **A, int **B, int n){
    
    if (n==1){
        int** result = allocate_Matrix(1);
        result[0][0] = (A[0][0] * B[0][0]);
        return result;
    }
    if (n==2){

        int A11 =A[0][0]; int B11=B[0][0];
        int A12 =A[0][1]; int B12=B[0][1];
        int A21 =A[1][0]; int B21=B[1][0];
        int A22 =A[1][1]; int B22=B[1][1];

        int** C = allocate_Matrix(n);

        C[0][0]=(A11 * B11)+(A12 * B21);
        C[0][1]=(A11 * B12)+(A12 * B22);
        C[1][0]=(A21 * B11)+(A22 * B21);
        C[1][1]=(A21 * B12)+(A22 * B22);

        return C;
    }

    if (n>2 && n%2==0){
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

        // Recursive multiplications
        int** M1 = Divide_and_Conquer(A11, B11, newsize);
        int** M2 = Divide_and_Conquer(A12, B21, newsize);
        int** M3 = Divide_and_Conquer(A11, B12, newsize);
        int** M4 = Divide_and_Conquer(A12, B22, newsize);
        int** M5 = Divide_and_Conquer(A21, B11, newsize);
        int** M6 = Divide_and_Conquer(A22, B21, newsize);
        int** M7 = Divide_and_Conquer(A21, B12, newsize);
        int** M8 = Divide_and_Conquer(A22, B22, newsize);

        // Combine results
        int** C11 = add_matrix(M1, M2, newsize);
        int** C12 = add_matrix(M3, M4, newsize);
        int** C21 = add_matrix(M5, M6, newsize);
        int** C22 = add_matrix(M7, M8, newsize);


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
        free_matrix(M7, newsize);  free_matrix(M8, newsize);
        free_matrix(C11, newsize); free_matrix(C12, newsize);
        free_matrix(C21, newsize); free_matrix(C22, newsize);

        return C;
        
    }

    if (n>2 && n%2!=0){
        
        int newsize=(n+1)/2;

        int** X = allocate_Matrix(n+1);
        int** Y = allocate_Matrix(n+1);

        for (int i=0;i<n;i++){
            for(int j=0; j<n;j++){
                X[i][j]=A[i][j];
                Y[i][j]=B[i][j];
            }
        }
    
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
            
            A11[i][j] = X[i][j] ;
            B11[i][j] = Y[i][j] ; 
            }
        }
        for (int i=0; i<newsize; i++){      // top-right
            for(int j=newsize; j<(n+1); j++){  
            
            A12[i][j-newsize] = X[i][j] ;
            B12[i][j-newsize] = Y[i][j] ; 
            
            }
        }
        for (int i=newsize; i<(n+1); i++){      // bottom-left
            for(int j=0; j<newsize; j++){   
            
            A21[i-newsize][j] = X[i][j] ;
            B21[i-newsize][j] = Y[i][j] ; 
            }
        }
        for (int i=newsize; i<(n+1); i++){      // bottom-right
            for(int j=newsize; j<(n+1); j++){ 

            A22[i-newsize][j-newsize] = X[i][j] ;
            B22[i-newsize][j-newsize] = Y[i][j] ; 
            }
        }

        // Recursive multiplications
        int** M1 = Divide_and_Conquer(A11, B11, newsize);
        int** M2 = Divide_and_Conquer(A12, B21, newsize);
        int** M3 = Divide_and_Conquer(A11, B12, newsize);
        int** M4 = Divide_and_Conquer(A12, B22, newsize);
        int** M5 = Divide_and_Conquer(A21, B11, newsize);
        int** M6 = Divide_and_Conquer(A22, B21, newsize);
        int** M7 = Divide_and_Conquer(A21, B12, newsize);
        int** M8 = Divide_and_Conquer(A22, B22, newsize);

        // Combine results
        int** C11 = add_matrix(M1, M2, newsize);
        int** C12 = add_matrix(M3, M4, newsize);
        int** C21 = add_matrix(M5, M6, newsize);
        int** C22 = add_matrix(M7, M8, newsize);
        
        int** C = allocate_Matrix(n+1);

        for (int i = 0; i < newsize; i++) {
            for (int j = 0; j < newsize; j++) {
                C[i][j] = C11[i][j];                         // Top-left
                C[i][j + newsize] = C12[i][j];                   // Top-right
                C[i + newsize][j] = C21[i][j];                   // Bottom-left
                C[i + newsize][j + newsize] = C22[i][j];             // Bottom-right
            }
        } 

        free_matrix(A11, newsize); free_matrix(A12, newsize);
        free_matrix(A21, newsize); free_matrix(A22, newsize);
        free_matrix(B11, newsize); free_matrix(B12, newsize);
        free_matrix(B21, newsize); free_matrix(B22, newsize);
        free_matrix(M1, newsize);  free_matrix(M2, newsize);
        free_matrix(M3, newsize);  free_matrix(M4, newsize);
        free_matrix(M5, newsize);  free_matrix(M6, newsize);
        free_matrix(M7, newsize);  free_matrix(M8, newsize);
        free_matrix(C11, newsize); free_matrix(C12, newsize);
        free_matrix(C21, newsize); free_matrix(C22, newsize);
        free_matrix(X,n+1); free_matrix(Y,n+1);


        int** Matrix_C = trim_matrix(C,n+1);
        free_matrix(C,n+1);
        return Matrix_C;
    }        
}


int main(){
    int n;
    printf("Enter order of matrix:");
    scanf("%d",&n);

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
    for (int i=0; i<10000; i++){   // 10,000 times 
        Divide_and_Conquer(mat1, mat2, n);   // IT CREATES NUMEROUS MEMORY LEAKS
    }  
    clock_t end=clock();

    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;

    printf("Time taken to multiply 2 matrices of order %d using divide and conquer is : %f seconds\n",n ,time_taken);
    
    free (array1);
    free (array2);

    return 0;
} 
