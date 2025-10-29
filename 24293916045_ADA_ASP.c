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


void quick_sort(Activity arr[], int low, int high) {  // soritng in ascending order
    if (low < high) {
        int pi = partition(arr, low, high);

        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

void Maximum_Activities(Activity arr[], int n) {

    quick_sort(arr, 0,n-1);

    printf("Max activities that are mutually compatible are:\n");
    int count=1;
    // Select the first activity and maintain 'i' and 'j'
    int i = 0;
    printf("(%d, %d)\n", arr[i].start, arr[i].end);

    // For the remaining activities
    for (int j = 1; j < n; j++){          // no need of j+=1 as j is in loop

        if (arr[j].start >= arr[i].end) {
            printf("(%d, %d)\n", arr[j].start, arr[j].end);
            count+=1;
            i = j; 
        }
    }
    printf("The number of non-overlapping activities is: %d\n",count);
}


int main(){
    int start_time[] = {5, 1, 3, 0, 5, 8};
    int end_time[] = {9, 2, 4, 6, 7, 9};

    // sorted = [(1,2),(3,4),(0,6),(5,7),(5,9),(8,9)]
    
    int n = sizeof(end_time) / sizeof(end_time[0]);
    
    Activity arr[n];
    for (int i = 0; i < n; i++) {
        arr[i].start = start_time[i];
        arr[i].end = end_time[i];
    }

    clock_t start=clock();
    Maximum_Activities(arr, n);    
    clock_t end=clock();

    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;  
    
    printf("Time taken is : %f seconds\n",time_taken);
    return 0;
}
// Time complexity : n logn + n = n logn

/*
For input of starting and finishing time from user

printf("Enter the start and finish times for each activity (finish time must be >= start time):\n");
for (int i = 0; i < n; i++) {
    printf("Activity %d (start finish): ", i + 1);

    if (scanf("%d %d", &arr[i].start, &arr[i].finish) != 2 || arr[i].start > arr[i].finish){ // if two inputs are not given by the user
        printf("Invalid time input or start time is greater then end time. \n");
        return 1;
    }
}
*/

