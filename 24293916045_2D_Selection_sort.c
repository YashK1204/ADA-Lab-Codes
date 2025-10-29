# include <stdio.h>
# include <stdlib.h>
# include <time.h>

void swap(int* a, int* b){
    int temp;
    temp =  *a;        
    *a = *b;    
    *b = temp;      
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {   
        int min_idx = i;
        

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(&arr[i], &arr[min_idx]);
    }
}

void generate_random_array(int arr[],int n){
    for(int i=0;i<n;i++){
        arr[i]=rand() % 100000; 
    }
}

int main(){
    int n;
    
    printf("Enter number of elements:");
    scanf("%d",&n); 

    int* arr= (int*)malloc(n*sizeof(int)); 
    if (arr==NULL){
        printf("Memory allocation failed");
        return 0;
    }

    generate_random_array(arr,n);
    clock_t start=clock();
    for (int i=0; i<100; i++){
        selectionSort(arr,n); 
    }
    clock_t end=clock();

    double time_taken = ((double)end-start)/CLOCKS_PER_SEC/100.0;  
    
    printf("Time taken to sort %d elements is : %f seconds\n",n,time_taken);
    free (arr);

    return 0;
}
