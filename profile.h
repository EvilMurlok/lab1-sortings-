#ifndef PROFILE_H_
#define PROFILE_H_
/*

	This file is for measurment of time
	There is a class which helps us do it
	Also there are two functions for measurment
	It was taken from the course on "COURSERA" named "Основы разработки на С++: Красный пояс по С++" by Yandex.

*/
#include <chrono>
#include <iostream>
#include <string>
#include<algorithm> //it's only for 'transform'


using namespace std::chrono;

class LogDuration {
public:
    explicit LogDuration(const std::string& msg = "") : message(msg + ": "), start(steady_clock::now()) {}

    ~LogDuration() {
        auto finish = steady_clock::now();
        auto dur = finish - start;
        std::cerr << message << duration_cast<milliseconds>(dur).count() << " ms" << std::endl;
    }
private:
	std::string message;
    steady_clock::time_point start;
};

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define LOG_DURATION(message) \
  LogDuration UNIQ_ID(__LINE__){message};


template <typename Sort>
void measureTimeOfSort(Sort fcn, const std::string& msg) {
	{
		LOG_DURATION(msg);
		fcn();
	}
}

template <typename Sequence, typename Comperison>
void timeOfSort(Sequence& seq, Comperison cmp,  std::string typeOfSort) {
	std::transform(typeOfSort.begin(), typeOfSort.end(), typeOfSort.begin(), std::toupper);
	if (typeOfSort == "INSERTIONSORT") {
		measureTimeOfSort([&seq, cmp]() {insertionSort(seq, cmp); }, "The time of insertionSort with " + to_string(seq.len()) + " elements");
	}
	else if (typeOfSort == "BUBBLESORT") {
		measureTimeOfSort([&seq, cmp]() {bubbleSort(seq, cmp); }, "The time of bubbleSort with " + to_string(seq.len()) + " elements");
	}
	else if (typeOfSort == "SHAKERSORT") {
		measureTimeOfSort([&seq, cmp]() {shakerSort(seq, cmp); }, "The time of shakerSort with " + to_string(seq.len()) + " elements");
	}
	else if (typeOfSort == "QUICKSORT") {
		measureTimeOfSort([&seq, cmp]() { quickSort(seq, 0, seq.len() - 1, cmp); }, "The time of quickSort with " + to_string(seq.len()) + " elements");
	}
	else if (typeOfSort == "MERGESORT") {
		measureTimeOfSort([&seq, cmp]() {mergeSort(seq, cmp); }, "The time of mergeSort with " + to_string(seq.len()) + " elements");
	}
	else if (typeOfSort == "SHELLSORT") {
		measureTimeOfSort([&seq, cmp]() {ShellSort(seq, cmp); }, "The time of shellSort with " + to_string(seq.len()) + " elements");
	}
	else if (typeOfSort == "SELECTIONSORT") {
		measureTimeOfSort([&seq, cmp]() {selectionSort(seq, cmp); }, "The time of selectionSort with " + to_string(seq.len()) + " elements");
	}
	else if (typeOfSort == "GNOMESORT") {
		measureTimeOfSort([&seq, cmp]() {gnomeSort(seq, cmp); }, "The time of gnomeSort with " + to_string(seq.len()) + " elements");
	}
	else {
		throw runtime_error("Unknown type of sorting");
	}
}

#endif // !PROFILE_H_