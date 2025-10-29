# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>


int recursive(int n){   // Function is to get 'n'th fibonacci number not the fibonacci series
    if(n<=1) return n;
    // base case

    return (recursive(n-1) + recursive(n-2));
}

void print_fib_series(int n){
    //printf("The fibonacci series upto 'n' terms is:");
    for (int j=0; j<n ; j++){
        //printf("%d", recursive(j));
        recursive(j);
    }
    //printf("\n");
}

int main(){
    int n;
    printf("Enter the number of terms: ");
    scanf("%d", &n);
    
    clock_t start=clock();
    for (int i=0; i<1000000; i++){   // 10^6 times 
        print_fib_series(n);
    }  
    clock_t end=clock();

    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;

    printf("Time taken is : %f seconds\n", time_taken);
    
    return 0;
}

/*
Time Complexity: O(2^n)
Auxiliary Space: O(n), due to recursion stack
*/