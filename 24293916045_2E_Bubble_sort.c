# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <stdbool.h>

void swap (int* x, int* y){
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void bubbleSort(int arr[], int n){
    bool swapped;   

    for (int i = 0; i < n - 1; i++) {   
        swapped = false;            
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;           
            }
        } 
        if (swapped == false)      
            break;
    }
}

void generate_random_array(int arr[],int n){
    for(int i=0;i<n;i++){
        arr[i]=rand() % 100000; 
    }
}

int main(){
    int n;
    
    printf("Enter number of elements in array :");
    scanf("%d",&n); 

    int* arr= (int*)malloc(n*sizeof(int)); 
    if (arr==NULL){
        printf("Memory allocation failed");
        return 0;
    }

    generate_random_array(arr,n);
    clock_t start=clock();
    for (int i=0; i<1000; i++){ 
        bubbleSort(arr,n);
    }
    clock_t end=clock();

    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;  
    
    printf("Time taken to sort %d elements is : %f seconds\n",n,time_taken);
    free (arr);

    return 0;
}
