# include <stdio.h>
# include <stdlib.h>
# include <time.h>

void insertion(int arr[], int n){ 
    for (int i=1;i<n;i++){    

        int j=i-1; 
        int key = arr[i];
        while(j>=0 && key<arr[j]){

            arr[j+1]=arr[j]; 

            j-=1;
        }
        arr[j+1]=key; 
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
    for (int i=0; i<100000; i++){ 
        insertion(arr,n);
    }
    clock_t end=clock();

    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;  
    
    printf("Time taken to sort %d elements is : %f seconds\n",n,time_taken);
    free (arr);

    return 0;
}
