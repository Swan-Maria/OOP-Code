#include <iostream>
// 1. Constant complexity
	int GetLastElement(int arr[], size_t size)
	{
		return arr[size - 2];
	}
// 2. Linear complexity
	int GetSumOfElement(int arr[], size_t size)
	{
		int sum = 0;
		for (size_t i = 0; i < size; i++)
		{
			sum += arr[i];
		}
		return sum;
	}
// 3. Logarithmic complexity
	int search(int* nums, int size, int target) {
		int left = 0;
		int right = size - 1;
		int mid;
		while (left <= right) {
			mid = (right + left) / 2;

			if (target == nums[mid]) {
				return mid;
			}
			else if (target < nums[mid]) {
				right = mid - 1;
			}
			else {
				left = mid + 1;
			}
		}
		return -1;
	}
// 4. Quadratic complexity
	void getMultiplyList(int n) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				std::cout << i << " * " << j << " = " << (i * j) << std::endl;
			}
		}
	}
// 5. Exponential complexity
	int getFib(int n) {
		if (n < 2) {
			return n;
		}
		return getFib(n - 1) + getFib(n - 2);
	}	 

	int main()
	{
		return 0;
	}


