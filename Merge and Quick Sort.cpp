#include <iostream>
#include <time.h>

bool IsSorted(int arr[], size_t size) 
{
	for (size_t i = 1; i < size; i++)
	{
		if (arr[i - 1] > arr[i])
			return false;
	}
	return true;
}

void print(int* arr, size_t size)
{
	for (size_t i = 0; i < size; i++)
		std::cout << arr[i] << ' ';
	std::cout << '\n';
}

void Merge(int arr[], int left, int mid, int right)
{
	int size_left = mid - left + 1;
	int size_right = right - mid;

	int* Left = new int[size_left];
	int* Right = new int[size_right];

	for (int i = 0; i < size_left; i++)
		Left[i] = arr[left + i];
	for (int i = 0; i < size_right; i++)
		Right[i] = arr[mid + i + 1];

	int i = 0, j = 0, k = left;

	while (i < size_left && j < size_right)
	{
		if (Left[i] <= Right[j])
			arr[k++] = Left[i++];
		else
			arr[k++] = Right[j++];
	}

	while (j < size_right) 
		arr[k++] = Right[j++];

	while (i < size_left)
		arr[k++] = Left[i++];

	delete[] Left;
	delete[] Right;
}

void MergeSort(int arr[], int left, int right)
{
	if (left < right)
	{
		int mid = left + (right - left) / 2;
		print(arr, right+1); // Исправлено на right + 1
		MergeSort(arr, left, mid);
		MergeSort(arr, mid + 1, right);

		Merge(arr, left, mid, right);
	}
}

void QuickSort(int arr[], size_t size)
{
	std::cout << "\nArray at start of quicksort function:\n";
	print(arr, size); 
	if (size <= 1) return;

	int i = 0, j = size - 1; 
	int pivot = arr[(i + j) / 2];
	std::cout << "\nPivot number = " << pivot << '\n';

	int count = 0;
	while (i <= j)
	{
		while (arr[i] < pivot) i++;
		while (arr[j] > pivot) j--;

		if (i <= j)
		{
			std::swap(arr[i++], arr[j--]);

			count++;
			std::cout << "Swap number " << count << ": " << '\n';
			print(arr, size);
		}
	}
	std::cout << "\nBefore new step of recursion: \n";
	print(arr, size);
	if (j > 0)
		QuickSort(arr, j + 1); // Исправлено на j + 1

	if (i < size)
		QuickSort(arr + i, size - i);
}

int main()
{
	srand(time(NULL));

	const size_t size = 10;

	int arr[size];

	for (size_t i = 0; i < size; i++)
		arr[i] = rand() % 100 + 1;

	std::cout << "Before sort: \n";
	print(arr, size);

	std::cout << "Call sort function\n";

	//MergeSort(arr, 0, size - 1);
	QuickSort(arr, size);

	std::cout << "\nAfter sort: " << '\n';
	print(arr, size);

	return 0;
}