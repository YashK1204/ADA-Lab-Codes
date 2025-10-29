# include <stdio.h>
# include <stdlib.h>
# include <time.h>

typedef struct{
    int start;
    int end;  // used for sorting
} Activity;

void swap(Activity* a, Activity* b) {
    Activity t = *a;
    *a = *b;
    *b = t;
}

int partition(Activity arr[], int low, int high) {
    int pivot = arr[high].end;  // finishing time of the last activity 
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].end < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}


void quick_sort(Activity arr[], int low, int high) {  // sorting in ascending order
    if (low < high) {
        int pi = partition(arr, low, high);

        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

void Recursive_ASP(Activity arr[], int n, int m, int p){
    if (m>n-1 || p>n-1) return; // base case 

    if (arr[p].start >= arr[m].end){ 
        printf("(%d, %d)\n", arr[p].start, arr[p].end);
        //count+=1;
        m=p;
        Recursive_ASP(arr, n, m, p+1);
    }

    else{  
        Recursive_ASP(arr, n, m, p+1);
    }
}


int main(){
    int start_time[] = {5, 1, 3, 0, 5, 8};
    int end_time[] = {9, 2, 4, 6, 7, 9};
    
    int n = sizeof(end_time) / sizeof(end_time[0]);
    
    Activity arr[n];
    for (int i = 0; i < n; i++) {
        arr[i].start = start_time[i];
        arr[i].end = end_time[i];
    }

    quick_sort(arr, 0,n-1);  
    // sorted = [(1,2),(3,4),(0,6),(5,7),(5,9),(8,9)]

    printf("(%d, %d)\n", arr[0].start, arr[0].end); // printing the first sorted activity

    clock_t start=clock();
    Recursive_ASP(arr, n, 0, 1); // while calling i have put m=0 & n=1, since first acitivity is already selected
    clock_t end=clock();

    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;  
    
    printf("Time taken is : %f seconds\n",time_taken);
    return 0;
}

// time complexity = n log n + n (for recursion ) = n logn




