//
// Created by rbx on 14.03.23.
//
#include "sorting_algorithms.h"

#include <iostream>

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
                //std::cout << arr[j] << std::endl;
        }
    }
}

void combSort(int arr[], int n){
    int gap = n;
    bool replace = true;
    while(gap > 1 || replace){
        gap = gap * 10 / 13;
        if(gap == 0)
            gap = 1;

        replace = false;
        for(int i = 0; i + gap < n; i++){
            if(arr[i + gap] < arr[i]){
                swap(&arr[i], &arr[i + gap]);
                replace = true;
            }
        }
    }
}

void cocktailSort(int arr[], int n){
    bool swapped = true;
    int start = 0;
    int end = n - 1;
    while (swapped){
        swapped = false;
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
        swapped = false;
        --end;
        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                swapped = true;
            }
        }
        ++start;
    }
}

int getMax(int arr[], int n) {
    int maximum = arr[0];
    for(int i = 2; i <= n; i++) {
        if(arr[i] > maximum)
            maximum = arr[i];
    }
    return maximum;
}

void countingSort(int arr[], int n) {
    int maxVal = arr[0], minVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }
    int range = maxVal - minVal + 1;

    int* count = new int[range];
    int* output = new int[n];

    for (int i = 0; i < range; i++) {
        count[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        count[arr[i] - minVal]++;
    }

    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    delete[] count;
    delete[] output;
}
