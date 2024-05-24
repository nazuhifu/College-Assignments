# Efficient Sorting

## Apa itu Efficient Sorting Algorithm?

Pada praktikum sebelumnya, teman-teman sudah belajar mengenai algoritma sorting yang simpel, seperti _insertion sort_, _selection sort_, dan _bubble sort_. Karakteristik dari algoritma sorting simpel di atas adalah kodenya yang simpel sehingga (relatif) lebih mudah dipahami, kompleksitas waktu yang (relatif) buruk, dan performanya yang kurang baik untuk data besar dan tidak tersortir dengan baik.

Oleh karena itu, penggunaan algoritma sorting sederhana hanya diperuntukkan untuk penggunaan-penggunaan yang sederhana pula, yaitu pada data berjumlah kecil atau sudah hampir tersortir.

Untuk penggunaan yang lebih _advanced_, diperlukan algoritma sorting yang lebih efisien. Dalam materi ini, akan dibahas 2 algoritma sorting yang sangat efisien dan digunakan secara luas, yaitu _quicksort_ dan _mergesort_.

## Quicksort

### Definisi

_Quicksort_ adalah algoritma pertama yang akan kita pelajari pada praktikum kali ini. _Quicksort_ adalah algoritma pengurutan _divide-and-conquer_ rekursif yang bekerja dengan memilih sebuah elemen _pivot_, dan membagi/mempartisi elemen lainnya, berdasarkan dari perbandingan nilai antara elemen tersebut dan elemen _pivot_.

### Kompleksitas Waktu dan Memori

- Best Case: `O(n log n)` menggunakan _simple partition_
- Average Case: `O(n log n)`
- Worst Case: `O(n^2)`
- Kompleksitas memori: secara garis besar `O(log n)`

### Pseudocode

Algoritma _quicksort_ dapat digambarkan dengan pseudocode di bawah.

```
quicksort(arr[], start, end)
    if start >= end
        return
    else
        p := partition(arr)
        quicksort(arr, start, p-1)
        quicksort(arr, p+1, end)
```

Algoritma _partition_ akan kita lompati untuk sekarang, yang memiliki fungsi:

- Menentukan `pivot`, dapat mengambil nilai arbitrer atau random,
- Meletakkan `pivot` ke posisinya dengan menukar posisi `pivot` dengan posisi yang seharusnya,
- Mengurutkan bagian kanan dan kiri dari elemen `pivot`.

### Contoh Lengkap

Contoh lengkap dan simulasi grafis _quicksort_ dapat dilihat di [situs ini](https://visualgo.net/en/sorting), dan pilih _quicksort_.

### Contoh Implementasi

```c++
#include <iostream>
using namespace std;

// This function takes last element as pivot,
// places the pivot element at its correct position
// in sorted array, and places all smaller to left
// of pivot and all greater elements to right of pivot
int partition(int arr[], int low, int high)
{
	// Choosing the pivot
	int pivot = arr[high];

	// Index of smaller element and indicates
	// the right position of pivot found so far
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {

		// If current element is smaller than the pivot
		if (arr[j] < pivot) {

			// Increment index of smaller element
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return (i + 1);
}

// The main function that implements QuickSort
// arr[] --> Array to be sorted,
// low --> Starting index,
// high --> Ending index
void quickSort(int arr[], int low, int high)
{
	if (low < high) {

		// pi is partitioning index, arr[p]
		// is now at right place
		int pi = partition(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

// Driver Code
int main()
{
	int arr[] = { 10, 7, 8, 9, 1, 5, 10, 7, 8, 9, 1, 5, 10, 7, 8, 9, 1, 5, 10, 7, 8, 9, 1, 5,};
	int N = sizeof(arr) / sizeof(arr[0]);

	// Function call
	quickSort(arr, 0, N - 1);
	cout << "Sorted array: " << endl;
	for (int i = 0; i < N; i++)
		cout << arr[i] << " ";

	return 0;
}
```

## Mergesort

### Definisi

Algoritma sorting _Mergesort_ merupakan algoritma divide-and-conquer yang membagi set permasalahan yang akan diurutkan menjadi unit terkecil, lalu membandingkan masing-masing unit dengan unit di sebelahnya dan mengurutkannya. Langkah ini diulang terus-menerus hingga didapatkan hasil akhir berupa set permasalahan yang sudah terurut.

### Kompleksitas Waktu dan Memori

- Best Case: `O(n log n)`
- Average Case: `O(n log n)`
- Worst Case: `O(n log n)`
- Kompleksitas memori: `O(n)`

### Pseudocode

```
mergesort(arr[], left, right)
    if right > left
        middle = left + (right - left) / 2
        mergesort(arr, left, middle)
        mergesort(arr, middle + 1, right)
        merge(arr, left, middle, right)
```

### Contoh Lengkap

Contoh lengkap dan simulasi grafis _mergesort_ dapat dilihat di [situs ini](https://visualgo.net/en/sorting), dan pilih _mergesort_, atau perhatikan gif di bawah ini.

<div align="center">
<img src="https://upload.wikimedia.org/wikipedia/commons/c/cc/Merge-sort-example-300px.gif"></img>
</div>

### Contoh Implementasi

```c++
#include <iostream>
using namespace std;

// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
void merge(int array[], int const left, int const mid,
		int const right)
{
	int const subArrayOne = mid - left + 1;
	int const subArrayTwo = right - mid;

	// Create temp arrays
	auto *leftArray = new int[subArrayOne],
		*rightArray = new int[subArrayTwo];

	// Copy data to temp arrays leftArray[] and rightArray[]
	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
	int indexOfMergedArray = left;

	// Merge the temp arrays back into array[left..right]
	while (indexOfSubArrayOne < subArrayOne
		&& indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	// Copy the remaining elements of
	// left[], if there are any
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}

	// Copy the remaining elements of
	// right[], if there are any
	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
	delete[] leftArray;
	delete[] rightArray;
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(int array[], int const begin, int const end)
{
	if (begin >= end)
		return;

	int mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}

// UTILITY FUNCTIONS
// Function to print an array
void printArray(int A[], int size)
{
	for (int i = 0; i < size; i++)
		cout << A[i] << " ";
	cout << endl;
}

// Driver code
int main()
{
	int arr[] = { 10, 7, 8, 9, 1, 5, 10, 7, 8, 9, 1, 5, 10, 7, 8, 9, 1, 5, 10, 7, 8, 9, 1, 5 };
	int arr_size = sizeof(arr) / sizeof(arr[0]);

	cout << "Given array is \n";
	printArray(arr, arr_size);

	mergeSort(arr, 0, arr_size - 1);

	cout << "\nSorted array is \n";
	printArray(arr, arr_size);
	return 0;
}
// This code is contributed by Mayank Tyagi
// This code was revised by Joshua Estes
```

## Perbandingan Quicksort dan Mergesort

- Persamaan

  - Keduanya merupakan algoritma pengurutan yang sangat efisien dan banyak digunakan untuk implementasi yang luas
  - Merupakan algoritma divide-and-conquer yang membagi masalah besar menjadi banyak masalah-masalah kecil (submasalah)
  - Dengan implementasi yang ideal, memiliki kompleksitas best case dan average case yang sepadan

- Perbedaan

  - _Mergesort_ memiliki kompleksitas worst case yang lebih baik yaitu `O(n log n)` daripada _quicksort_ `O(n^2)`
  - _Mergesort_ memiliki kompleksitas ruang yang sedikit lebih buruk karena bukan merupakan algoritma pengurutan _in-place_, berbeda dengan _quicksort_
  - _Quicksort_ bekerja lebih baik pada data yang kecil, sedangkan _mergesort_ tidak berbeda jauh performanya untuk data kecil maupun besar
