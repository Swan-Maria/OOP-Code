#include <iostream> 
#include <ctime> 

void Initialize(int arr[], int size);
void Show(const int arr[], int size);
template <typename T>
void SelectionSort(T arr[], int size);
template <typename T>
bool LinearSearch(const T arr[], int size, T& value);
template <typename T>
bool OptimizedLinearSearch(const T arr[], int size, const T& value);

int main()
{
	srand(static_cast<unsigned>(time(nullptr)));
	const int SIZE = 10;
	int arr[SIZE];

	Initialize(arr, SIZE);
	SelectionSort(arr, SIZE);
	Show(arr, SIZE);

	std::cout << "Enter value that you want to find: ";
	int value;
	std::cin >> value;

	if (OptimizedLinearSearch(arr, SIZE, value))
		std::cout << "The array has your value!\n";
	else
		std::cout << "The array has not your value :(\n";

	return 0;
}

void Initialize(int arr[], int size)
{
	if (arr == nullptr)
		return;
	for (int i = 0; i < size; i++)
		arr[i] = rand() % 100;
}

void Show(const int arr[], int size)
{
	if (arr == nullptr)
		return;
	for (int i = 0; i < size; i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}

template <typename T>
void SelectionSort(T arr[], int size)
{
	for (size_t i = 0; i < size - 1; i++)
		for (size_t j = i + 1; j < size; j++)
			if (arr[j] < arr[i])
				std::swap(arr[j], arr[i]);
}

template <typename T>
bool LinearSearch(const T arr[], int size, T& value)
{
	for (size_t i = 0; i < size; i++)
		if (value == arr[i])
			return true;
	return false;
}

template <typename T>
bool OptimizedLinearSearch(const T arr[], int size, const T& value)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] > value) // якщо поточний елемент б≥льший за шукане значенн€, можна припинити пошук
			return false;
		if (arr[i] == value)
			return true;
	}
	return false;
}