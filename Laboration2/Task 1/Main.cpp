#include <cstdlib>
#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

void InsertionSort(int list[], int size) {
	int temp;
	int i = 1, counter = 1;
	while (i < size) {
		while (list[i] < list[i - 1]) { // if previous number is higher, swap.
			temp = list[i - 1];
			list[i - 1] = list[i];
			list[i] = temp;
			
			if (i <= 1) {
				break;
			}
			i--;
		}
		i =++ counter;
	}
}

int binarySearch(int list[], int item, int low, int high){

	if (high <= low)
		return (item > list[low]) ? (low + 1) : low;

	int mid = (low + high) / 2;

	if (item == list[mid])
		return mid + 1;

	if (item > list[mid])
		return binarySearch(list, item, mid + 1, high);
	return binarySearch(list, item, low, mid - 1);
}

void bInsertionSort(int list[], int size) {
	for (int i = 1; i < size; ++i)
	{
		int j = i - 1;
		int selected = list[i];

		int pos = binarySearch(list, selected, 0, j); // finds location where selected should be inserted 

		// Moves all elements in array after found location to create space
		while (j >= pos)
		{
			list[j + 1] = list[j];
			j--;
		}
		list[j + 1] = selected;
	}
}


void mergeSort(int* list, int k, int size, bool sorter) {
	int leftIndex = 0, rightIndex = size / 2;
	if (size > k) {
		mergeSort(list, k, size / 2, sorter);	
		mergeSort(list + size/2, k, size - size / 2, sorter);


		int *tempArr = new int[size];
		for (int i = 0; i < size; i++) {

			if (list[leftIndex] < list[rightIndex] && leftIndex < size/2) {
				tempArr[i] = list[leftIndex];
				if (leftIndex == size/2) {
					tempArr[i] = list[rightIndex];
					rightIndex++;
				}
				else {
					leftIndex++;
				}
			}
			else if(list[leftIndex] > list[rightIndex]){
				tempArr[i] = list[rightIndex];
				if (rightIndex == size) {
					tempArr[i] = list[leftIndex];
					leftIndex++;
				}
				else {
					rightIndex++;
				}
			}
		}
		for (int i = 0; i < size; i++) {
			list[i] = tempArr[i];
		}
		delete[] tempArr;
	}

	else if(sorter == true) {
		InsertionSort(list, size);
	}
	else {
		bInsertionSort(list, size);
	}
}

void main() {
	srand(time(0));
	int sizeOfList = 1000000;
	int k = 50;
	bool sorter = true;

	int* list = new int[sizeOfList];
	for (int i = 0; i < sizeOfList; i++) {
		list[i] = rand() % sizeOfList;
	}

	cout << endl;
	{
		//Insertion sort method test
		auto start = chrono::high_resolution_clock().now();
		mergeSort(list, k, sizeOfList, sorter);
		auto stop = chrono::high_resolution_clock().now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start).count();
		cout << duration << " microseconds elapsed." << endl;
	}

	cout << endl << endl;

	for (int i = 0; i < sizeOfList; i++) {
		list[i] = rand() % sizeOfList;
	}
	sorter = false;

	{
	//Binary insertion sort method test
	auto start = chrono::high_resolution_clock().now();
	mergeSort(list, k, sizeOfList, sorter);
	auto stop = chrono::high_resolution_clock().now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start).count();
	cout << duration << " microseconds elapsed." << endl;
	}

}