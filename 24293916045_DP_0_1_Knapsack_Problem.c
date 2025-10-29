# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int DP01_Knapsack(int Profits[], int Weights[], int n, int M){  // 'M' is the capacity, 'n' is number of 
    // Allocate a n x M matrix named 'C'
    int** C = (int**)malloc((n+1)*sizeof(int*)) ;  
    for (int j = 0; j <= n; j++) {
        C[j] = (int*) malloc ((M+1)* sizeof(int));
    }

    // Boundary conditions -
    // since i=0 : there is no object to choose 
    for(int w=0;w<=M;w++){ 
        C[0][w]=0;
    }
    // since w=0 : there is no capacity available
    for(int i=0;i<=n;i++){
        C[i][0]=0;
    }

    for(int i=1; i<=n; i++){
        for(int w=1; w<=M; w++){
            if (Weights[i-1]>w){ // When the weight of current object 'i' exceeds the capacity
                // i-1 because in matrix indexing starts with 0
                C[i][w] = C[i-1][w]; //  take the value of the previous i'th element
            } 
            else{
                if ((Profits[i-1] + C[i-1][w-Weights[i-1]]) > C[i-1][w]) C[i][w] = Profits[i-1] + C[i-1][w-Weights[i-1]];
                else C[i][w] = C[i-1][w];
            }
        }
    }

    //printf("Items selected (by index, from 1 to n): ");

    int* array = (int*)malloc((n+1)*sizeof(int)) ; 
    for(int p=0; p<n;p++){
        array[p]=0;
    }
    int i = n;
    int k = M;
    int x=0;

    while (i > 0 && k > 0) {
        if (C[i][k] != C[i - 1][k]) { // If the value at C[i][k] is different from C[i-1][k], include i'th element
            //printf("%d ",i);
            array[x]=1;
            x++;
            // Move to the previous item and subtract its weight from the capacity
            k = k - Weights[i - 1];
            i = i - 1;
        } 
        else {// The item was not included, so move to the previous item with the same capacity
            i = i - 1;
        }
    }
    //printf("\n");

    //printf("The maximum profit that can be achieved is: %d", C[n][M]);
    //printf("\n");
    
    //printf("The xi array is:");

    for(int r=0; r<n;r++){
        //printf("%d ",array[r]);
    }
    return 0;
}


int main(){
    int profits[] = {3, 4, 5, 6};
    int weights[] = {2, 3, 4, 5};
    int M = 20;
    int n = sizeof(profits) / sizeof(profits[0]);

     
    clock_t start=clock();
    for (int i=0; i<10000; i++){ 
        DP01_Knapsack(profits, weights, n, M);
    }
    clock_t end=clock();

    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;  
    
    printf("Time taken is : %f seconds\n",time_taken);

    return 0;
}

// Time and space complexity : O(n*M)
