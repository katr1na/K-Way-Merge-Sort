/*
 * sorter.h
 *
 * Declares a template function:
 *    
 *   sorter() : k-way merge sort.
 * 
 */

#ifndef _SORTER_H
#define _SORTER_H

#include <string>
#include <cstddef>
#include <vector>

using namespace std;

template <class T>
void merge(vector<T> &vec, vector<vector<T>> &vecs) {
	size_t counter = 0; // O(1)
	
	// while result vector has not been filled
	// O(n)
	while (counter < vec.size()) {
		size_t target = 0;
		// check if target vector is empty; if yes, move on to next vector
		while (vecs[target].size() == 0) {
			target++;
		}

		// set max to be last element of first vector to check
		T max = vecs[target].back(); // O(1)
		size_t maxVec = target; // O(1)

		// loop through all vectors, skipping empty ones
		// O(n)
		while (target < vecs.size()) {
			// O(1)
			if (vecs[target].size() > 0) {
				if (vecs[target].back() > max) {
					max = vecs[target].back();
					maxVec = target;
				}
			}
			target++;
		}

		// add max to next spot in result vector and remove last element in corresponding vector
		vec[vec.size()-counter-1] = max; //O(1)
		vecs[maxVec].pop_back(); //O(1)
		counter++; //O(1)
	}
}

template <class T>
void sorter(vector<T> &vec, int k) {  
	if (vec.size() == 1 || vec.size() == 0) {
		return;
	}

	int remainingElements = vec.size() % k;
	int curr = 0;

	// if vector size is less than k, reset k to vector size and avoid making empty vectors
	if (vec.size() < k) {
		k = vec.size();
		remainingElements = 0;
	} 

	vector<int> sizes(k);
	for (int i = 0; i < k; i++) {
		sizes[i] = vec.size() / k;
	}

	vector<vector<T>> vecs(k);

	for (int i = 0; i < k; i++) {
		vector<T> temp(sizes[i]);
		vecs[i] = temp;
	}

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < vecs[i].size(); j++) {
			vecs[i][j] = vec[curr];
			curr++;
		}
	}

	for (int i = 0; i < remainingElements; i++) {
		vecs[i].push_back(vec[vec.size()-1-i]);
	}

	// for (int i = 0; i < vecs.size(); i++) {
	// 	for (int j = 0; j < vecs[i].size(); j++) {
	// 		cout << vecs[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }

	for (int i = 0; i < k; i++) {
		sorter(vecs[i], k);
	}

	merge(vec, vecs);
}
#endif

// // make vector containing all split vectors and assign corresponding values of input vector to split vectors
// 	vector<vector<T>> vecs;
// 	int j = 0;
// 	int remainingElements = vec.size() % k;
// 	for (int i = 0; i < k; i++) {
// 		j = i * (vec.size() / k);
// 		cout <<  "j: " << j << endl;
// 		// vector<T> b(vec.begin() + j, vec.begin() + j + (vec.size()/k));

// 		vector<T> b;
// 		if (i == k-1 && (vec.size() % 2 == 0) && k % 2 == 0) {
// 			b = {vec.begin() + j, vec.end()};
// 		} else {
// 			b = {vec.begin() + j, vec.begin() + j + (vec.size()/k)};
// 		}

// 		// add remaining elements to vectors in order from the start until there are none left
// 		if (remainingElements > 0) {
// 			b.push_back(vec[vec.size()-remainingElements]);
// 			remainingElements--;
// 		}
// 		vecs.push_back(b);
// 	}
// 	cout << endl;

// 	cout << "Vecs size: " << vecs.size() << endl;

// 	for (int i = 0; i < vecs.size(); i++) {
// 		for (int j = 0; j < vecs[i].size(); j++) {
// 			cout << vecs[i][j] << " ";
// 		}
// 		cout << endl;
// 	}