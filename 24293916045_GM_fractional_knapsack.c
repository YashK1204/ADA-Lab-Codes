# include <time.h>
#include <stdio.h>
#include <stdlib.h>

// We will use a sturcture since we want the weights and profits to be interconnected
typedef struct {
    int id;
    int profit;
    int weight;
    double ratio; // since ratio must be in decimal form for COMPARISON
} Item;  // name of structure

void swap(Item* a, Item* b) {
    Item t = *a;
    *a = *b;
    *b = t;
}

int partition(Item arr[], int low, int high) {
    double pivot = arr[high].ratio;
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].ratio > pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}


void quick_sort(Item arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

double GM_Fractional_Knapsack(int Profits[], int Weights[], int n, int M) {

    Item items[n];  // Item is a datatype and items is name of array with size n
    for (int i = 0; i < n; i++) {
        items[i].id = i;
        items[i].profit = Profits[i];
        items[i].weight = Weights[i];
        items[i].ratio = (double) Profits[i] / Weights[i]; // since we want ratio in decimal
    }

    quick_sort(items, 0, n - 1); // sorting items in descending order

    double result = 0.0;
    int temp = M;

    for (int i = 0; i < n; i++) {
        if (temp <= 0) {
            break; // Knapsack is full.
        }

        if (items[i].weight <= temp) {
            // Take the whole item.
            temp -= items[i].weight;
            result += items[i].profit;
        } else {
            // Take a fraction of the item.
            double fraction = (double)temp / items[i].weight; // taking the required fractional part

            result += fraction * items[i].profit;
            temp = 0; // Knapsack is now full.
        }
    }
    return result;
}

int main() {
    int profits[] = {3, 4, 5, 6};
    int weights[] = {2, 3, 4, 5};
    int M = 5; // Knapsack capacity
    int n = sizeof(profits) / sizeof(profits[0]);

    double max_profit = GM_Fractional_Knapsack(profits, weights, n, M);
    printf("Maximum profit: %.2f\n", max_profit); // Corrected output: 6.50

    clock_t start=clock();
    for (int i=0; i<10000; i++){ 
        GM_Fractional_Knapsack(profits, weights, n, M);
    }
    clock_t end=clock();

    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;  
    
    printf("Time taken is : %f seconds\n",time_taken);

    return 0;
}

// time complexity of this implementation is O(n logn)
//the total space complexity is O(n), primarily for storing the items array

