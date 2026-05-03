#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// Function to perform insertion sort
void insertionSort(std::vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Function to partition the array for quicksort
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Function to perform quicksort
void quicksort(std::vector<int>& arr, int low, int high, int maxDepth) {
    if (low < high) {
        if (maxDepth == 0) {
            // If the maximum depth is reached, switch to heapsort
            std::make_heap(arr.begin() + low, arr.begin() + high + 1);
            std::sort_heap(arr.begin() + low, arr.begin() + high + 1);
        } else {
            int pi = partition(arr, low, high);
            quicksort(arr, low, pi - 1, maxDepth - 1);
            quicksort(arr, pi + 1, high, maxDepth - 1);
        }
    }
}

// Function to perform introsort
void introsort(std::vector<int>& arr) {
    int n = arr.size();
    int maxDepth = log2(n) * 2;

    quicksort(arr, 0, n - 1, maxDepth);
    insertionSort(arr, 0, n - 1);
}

// Function to print the array
void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> numbers = {5, 2, 9, 1, 5, 6};
    int size = numbers.size();

    std::cout << "Original array: ";
    printArray(numbers);

    introsort(numbers);

    std::cout << "Sorted array: ";
    printArray(numbers);

    return 0;
}
