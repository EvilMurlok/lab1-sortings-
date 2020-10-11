// lab1(sorting).cpp

#include <iostream>
#include <string>
#include <ctime>
#include<list>
#include "utils.h"
#include "Sortings.h"
#include "profile.h"

using namespace std;


enum numberOfSeq {
	ARR = 0, LIST
};

enum kindsOfSortings {
	BUBBLESORT = 0, SHAKERSORT, SELECTIONSORT, INSERTIONSORT, GNOMESORT, MERGESORT, QUICKSORT, SHELLSORT
};

int main() {
	srand(time(NULL));
	cout << "Hello there!\nThis application let you to find out abount different kinds of sortings." << endl;
	cout << "You can test:\n" <<
			"1)Bubble sort\n" <<
			"2)ShakerSort\n" <<
			"3)selectionSort\n" <<
			"4)insertionSort\n" << 
			"5)gnomeSort\n" <<
			"6)mergeSort\n" << 
			"7)quickSort\n" << 
			"8)ShellSort\n" << endl;
	char yourChoise = 'n';

	do {
		cout << "Would you like to continue? (y/n)";
		cin >> yourChoise;
		if (tolower(yourChoise) != 'y') { return EXIT_SUCCESS; }

		cout << "You can work with dynamic array or with linked list (only with digits!)" <<
			"Please, enter the number of sequence:\n" <<
			"0 - array\n" <<
			"1 - linked list" << endl;

		int numberOfSeq = 0, amountOfElements = 0, kindOfSorting = 0;
		do {
			cin >> numberOfSeq;
		} while (numberOfSeq != LIST && numberOfSeq != ARR);
		cout << "Please, enter the amount of elements" << endl;
		do {
			cin >> amountOfElements;
			if (amountOfElements < 0) {
				cerr << "The amount of elements MUST be more than zero!!!";
			}
		} while (amountOfElements < 0);
		
		if (numberOfSeq == LIST) {
			ListSequence<int> testList = createRandomDigitalListSequence<int>(amountOfElements);
			cout << "OK, that's great! You have the list with " << amountOfElements << " elements\n" <<
					"now you should decide what type of sotring you would like to check:\n" <<
					"0 - Bubble sort\n" <<
					"1 - ShakerSort\n" <<
					"2 - selectionSort\n" <<
					"3 - insertionSort\n" <<
					"4 - gnomeSort\n" <<
					"5 - mergeSort\n" <<
					"6 - quickSort\n" <<
					"7 - ShellSort\n" 
					"other value - the end of working with the list with " << amountOfElements << " elements\n" << endl;
			cin >> kindOfSorting;
			switch (static_cast<kindsOfSortings>(kindOfSorting))
			{
			case BUBBLESORT:
				timeOfSort(testList, [](int a, int b) {return a < b; }, "BUBBLESORT");
				break;
			case SHAKERSORT:
				timeOfSort(testList, [](int a, int b) {return a < b; }, "SHAKERSORT");
				break;
			case SELECTIONSORT:
				timeOfSort(testList, [](int a, int b) {return a < b; }, "SELECTIONSORT");
				break;
			case INSERTIONSORT:
				timeOfSort(testList, [](int a, int b) {return a < b; }, "INSERTIONSORT");
				break;
			case GNOMESORT:
				timeOfSort(testList, [](int a, int b) {return a < b; }, "GNOMESORT");
				break;
			case MERGESORT:
				timeOfSort(testList, [](int a, int b) {return a < b; }, "MERGESORT");
				break;
			case QUICKSORT:
				timeOfSort(testList, [](int a, int b) {return a < b; }, "QUICKSORT");
				break;
			case SHELLSORT:
				timeOfSort(testList, [](int a, int b) {return a < b; }, "SHELLSORT");
				break;
			default:
				continue;
				break;

			}
			cout << "Do you want to check sorted list?(y/n)" << endl;
			char choise = 'n';
			cin >> choise;
			if (tolower(choise) == 'y') { 
				cout << testList << endl;
			}
		}
		else {
			ArraySequence<int> testArray = createRandomDigitalArrSequence<int>(amountOfElements);
			cout << "OK, that's great! You have the array with " << amountOfElements << " elements\n" <<
				"now you should decide what type of sotring you would like to check:\n" <<
				"0 - Bubble sort\n" <<
				"1 - ShakerSort\n" <<
				"2 - selectionSort\n" <<
				"3 - insertionSort\n" <<
				"4 - gnomeSort\n" <<
				"5 - mergeSort\n" <<
				"6 - quickSort\n" <<
				"7 - ShellSort\n"
				"other value - the end of working with the array with " << amountOfElements << " elements\n" << endl;
			cin >> kindOfSorting;
			switch (static_cast<kindsOfSortings>(kindOfSorting))
			{
			case BUBBLESORT:
				timeOfSort(testArray, [](int a, int b) {return a < b; }, "BUBBLESORT");
				break;
			case SHAKERSORT:
				timeOfSort(testArray, [](int a, int b) {return a < b; }, "SHAKERSORT");
				break;
			case SELECTIONSORT:
				timeOfSort(testArray, [](int a, int b) {return a < b; }, "SELECTIONSORT");
				break;
			case INSERTIONSORT:
				timeOfSort(testArray, [](int a, int b) {return a < b; }, "INSERTIONSORT");
				break;
			case GNOMESORT:
				timeOfSort(testArray, [](int a, int b) {return a < b; }, "GNOMESORT");
				break;
			case MERGESORT:
				timeOfSort(testArray, [](int a, int b) {return a < b; }, "MERGESORT");
				break;
			case QUICKSORT:
				timeOfSort(testArray, [](int a, int b) {return a < b; }, "QUICKSORT");
				break;
			case SHELLSORT:
				timeOfSort(testArray, [](int a, int b) {return a < b; }, "SHELLSORT");
				break;
			default:
				continue;
				break;

			}
			cout << "Do you want to check sorted list?(y/n)" << endl;
			char choise = 'n';
			cin >> choise;
			if (tolower(choise) == 'y') {
				cout << testArray << endl;
			}
		}
	} while (tolower(yourChoise) != 'n');
	return EXIT_SUCCESS;
}

