# include <stdio.h>
# include <stdlib.h>
# include <time.h>

// clock() = returns the CPU time your program has used, measured in clock ticks (not seconds)
// CLOCK_PER_SEC - tells you how many ticks correspond to 

void merge(int arr[], int l, int m, int r){
    int i,j,k;
    int n1, n2;
    
    i=0;
    j=0;
    n1= m-l+1;
    n2=r-m;
    // dynamically allocating array
    
    int* L=(int*) malloc (n1*sizeof(int));
    int* R=(int*) malloc (n2*sizeof(int));

    for (i=0;i<n1;i++){
        L[i]=arr[l+i];
    }
    for (j=0;j<n2;j++){
        R[j]=arr[m+1+j];
    }

    k=l;
    while(i<n1 && j<n2){
        if(L[i]<R[j]){
            arr[k]=L[i];
            i++;
        }
        else{
            arr[k]=R[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        arr[k]=L[i];
        i++;
        k++;
    }
    while(j<n2){
        arr[k]=R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}
 
void merge_sort(int arr[], int l, int r){
    if(l<r){
        int m = l + (r-l)/2;
        
        merge_sort(arr,l,m);
        merge_sort(arr,m+1,r);

        merge(arr,l,m,r);
    }
}

void generate_random_array(int arr[],int n){
    for(int i=0;i<n;i++){
        arr[i]=rand() % 100000; // will generate random numbers in range 0 to 99999
                                //  arr[i]=rand() % 10 - will generate random numbers in range 0 to 9
    }
}

int main(){
    int n;
    
    printf("Enter number of elements:");
    scanf("%d",&n); /*
    if(n<=5000){
        printf("enter value greater than 5000");
        return 1;
    }*/

    int* arr= (int*)malloc(n*sizeof(int)); 
    if (arr==NULL){
        printf("Memory allocation failed");
        return 0;
    }

    generate_random_array(arr,n);
    clock_t start=clock();
    for (int i=0; i<100; i++){  // we are performing it 1000 times as with such powerful machines if we run only once then it will give infinitely small time  
        merge_sort(arr,0,n-1);
    }
    clock_t end=clock();

    double time_taken = ((double)end-start)/CLOCKS_PER_SEC/100.0;  // time for one iteration by dividing it by 100 as we did it 1000 times
    // typecasting 'end-start ' from 'clock_t' to 'double'
    
    printf("Time taken to sort %d elements is : %f seconds\n",n,time_taken);
    free (arr);

    return 0;
}
