# include <stdio.h>
# include <stdlib.h>
# include <time.h>

void generate_random_array(int arr[],int n){
    for(int j=0; j<n ; j++){
        arr[j]=rand() % 100;
    }
}

int** allocate_Matrix(int n) {
    int** matrix = (int**) malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*) malloc (n* sizeof(int));
    }
    return matrix;
}

int** multiply(int **mat1, int **mat2, int n){

    int** matrix = (int**) malloc(n * sizeof(int*));  // the new matrix must be set to zero for each element
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*) malloc (n* sizeof(int));
        for(int j = 0; j < n; j++){
            matrix[i][j]=0;
        }
    }

    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++)
            matrix[i][j] += mat1[i][k] * mat2[k][j];  // as we want 'k' to change coz 'i' & 'j' get fixed
        }
    }
    return matrix;
}


int main(){
    int n;
    printf("Enter order of matrix:");
    scanf("%d",&n);

    int* array1 = (int*)malloc(n* sizeof(int));
    int* array2 = (int*)malloc(n* sizeof(int));
    if (array1==NULL || array2==NULL){
        printf("Memory allocation failed");
        return 0;
    }

    int **mat1 = allocate_Matrix(n);
    int **mat2 = allocate_Matrix(n);
      
    generate_random_array(array1,n);
    generate_random_array(array2,n);

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
        multiply(mat1,mat2,n);
    }  
    clock_t end=clock();

    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;

    printf("Time taken to multiply 2 matrices of order %d is : %f seconds\n",n ,time_taken);
    
    free (array1);
    free (array2);

    return 0;
} 



        
