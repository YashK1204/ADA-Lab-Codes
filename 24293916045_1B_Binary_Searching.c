# include <stdio.h>
# include <stdlib.h>
# include <time.h>

// Array must be sorted //

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);  
    return i + 1;                    
}


void quickSort(int arr[], int low, int high) {
    if (low < high) {
        
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int binary_search_iterative(int arr[], int l,int r, int key){
    while(l<=r){
        int mid = l + (r-l)/2; //   inside 'while'

        if(arr[mid]==key){
            //printf("Element found at index : %d",mid);
            return 1;
        }
        if(arr[mid]>key){
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return 0;

}

int binary_search_recursive(int arr[], int low, int high, int key){
    if(low<=high){
        int mid = low + (high-low)/2; // inside 'if'

        if(arr[mid]==key){
            //printf("Element found at index : %d",mid);
            return 1;
        }
        if(arr[mid]>key){
            return binary_search_recursive(arr, low, mid-1, key);
        }
        else{
            return binary_search_recursive(arr, mid+1, high, key);
        }
    }
    return 0;
}

void generate_random_array(int arr[],int n){
    for(int j=0; j<n ; j++){
        arr[j]=rand() % 100;
    }/*
    for (int k=0; k<n;k++){
        printf("%d",arr[k]);
    }*/
}

int main(){
    int n;
    printf("Enter number of elements:");
    scanf("%d",&n);

    int value;
    printf("Enter element to be searched:");
    scanf("%d",&value);

    int* array = (int*)malloc(n* sizeof(int));
    if (array==NULL){
        printf("Memory allocation failed");
        return 0;
    }

    generate_random_array(array,n);
    quickSort(array,0,n-1);           // low=0 & high=n-1 
    
    clock_t start_1=clock();
    for (int i=0; i<10000000; i++){   // 1 crore times
        binary_search_iterative(array, 0, n-1, value);
    }  
    clock_t end_1=clock();

    clock_t start_2=clock();
    for (int i=0; i<10000000; i++){ // 1 crore times
        binary_search_recursive(array, 0, n-1, value);
    }
    clock_t end_2=clock();

    double time_taken_1 = ((double)end_1-start_1)/CLOCKS_PER_SEC;
    double time_taken_2 = ((double)end_2-start_2)/CLOCKS_PER_SEC; 

    printf("Time taken to search %d iteratively is : %f seconds\n", value, time_taken_1);
    printf("Time taken to search %d recursively is : %f seconds\n", value, time_taken_2);
    
    free (array);

    return 0;
}    


