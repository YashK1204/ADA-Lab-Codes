# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>

void print_array(int arr[], int n){
    for(int i=0; i<n; i++){
        printf("%d", arr[i]);
    }
    printf("\n");
}

int bottom_up(int arr[], int n){
    if (n<=1) return n;

    arr[0]=0;
    arr[1]=1;

    for(int i=2; i<=n; i++){
        arr[i]=arr[i-1]+arr[i-2];
    }
}

int main(){
    int n;
    printf("Enter the number of terms: ");
    scanf("%d", &n);

    int* array = (int*) malloc(n *sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    clock_t start=clock();
    for (int i=0; i<1000000; i++){   // 10^6 times 
        bottom_up(array, n); 
    }  
    clock_t end=clock();

    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;

    printf("Time taken is : %f seconds\n", time_taken);
    print_array(array, n);

    return 0;
}

/*
Time Complexity: O(n), the loop runs from 2 to n, performing a constant amount of work per iteration.
Auxiliary Space: O(n), due to the use of an extra array to store Fibonacci numbers up to n.
*/