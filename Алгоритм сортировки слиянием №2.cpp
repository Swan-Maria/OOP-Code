#include <iostream>
using namespace std;

// Merge function to merge two sorted arrays
void merge(int arr[], int left[], int leftSize, int right[], int rightSize) {
    int i = 0, j = 0, k = 0;
    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        }
        else {
            arr[k++] = right[j++];
        }
    }
    while (i < leftSize) {
        arr[k++] = left[i++];
    }
    while (j < rightSize) {
        arr[k++] = right[j++];
    }
}

// Recursive Merge Sort function to sort the array
void recursiveMergeSort(int arr[], int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    recursiveMergeSort(arr, left, mid);
    recursiveMergeSort(arr, mid + 1, right);

    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    int* leftArr = new int[leftSize];
    int* rightArr = new int[rightSize];

    for (int i = 0; i < leftSize; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < rightSize; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }
    merge(arr + left, leftArr, leftSize, rightArr, rightSize);

    delete[] leftArr;
    delete[] rightArr;
}

// Driver code to test the Recursive Merge Sort function
int main() {
    int arr[] = { 38, 27, 43, 3, 9, 82, 10 };
    int size = sizeof(arr) / sizeof(arr[0]);
    cout << "Original array:" << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    recursiveMergeSort(arr, 0, size - 1);
    cout << "Sorted array:" << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
