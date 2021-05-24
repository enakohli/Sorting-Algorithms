#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack>
#include <iostream>
#include <chrono>
#include <assert.h>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
using ns = chrono::nanoseconds;
using get_time = chrono::steady_clock;
using namespace std;

// BucketSort helper function that is going to be used in MSDSort below
void bucketSort(vector<unsigned long int> &A, int d, int m) {
	int n = A.size(); //size of array
        int val = 1;

	//finds the digit we want to find
	int digitVal = m - d - 1;
	while(digitVal != 0) {
		val = val * 10;
		digitVal--;
	}

	//initializes array of empty lists
	vector<vector<unsigned long int>> B(10);

	//for loop for adding the appropriate values to B
	for (int t = 0; t < n; t++) {
		unsigned long int num = (A[t]/val) % 10;
		B[num].push_back(A[t]);
	}

	//adding the appropriate values back into A
	int i = 0;
	for (int j = 0; j < B.size(); j++) {
		for (int k = 0; k < B[j].size(); k++) {
			A[i++] = B[j][k];
		}
	}
}

// InsertionSort helper function that is going to be used in MSDSort below                                        
void insertionSort(vector<unsigned long int> &A, int n) {
    unsigned long int key = 0;
    int j = 0;
    //goes through the values for sorting
    for (int i = 1; i < n; i++) {
        key = A[i];
        j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = key;
    }
} 

// MSDSort implemented as in the assignment description
void MSDSort(vector<unsigned long int> &A, int m, int l, int r, int d, int threshold, int &total_num_calls) {
	total_num_calls++;
	int size = A.size();
	//calls insertion sort of the size is less than or equal to threshold
	if ((r - l + 1) <= threshold) {
		insertionSort(A, size);
	}
	//if l < r
	else if (l < r) {
		total_num_calls++;	
		//creates a new vector B to hold the values in between l and r
		vector<unsigned long int> B;
		for (int i = l; i <= r; i++) {
			B.push_back(A[i]);
		}
		//calls bucket sort on B
		bucketSort(B, d, m);

		//reassign whatever is in B to A
		for (int k = 0; k < B.size(); k++) {
			A[k] = B[k];
		}

		//checks if there are still digits
		if (d < m) {
			int newL = l;
			while (newL <= r) {
				//need to split into groups
				int newR = 0;

				//m-d number of times we need to divide A[i] by 10
				//creates new temp vector C that holds the digits we need
				vector<unsigned long int> C;
				
				//extracts the appropriate digit from the values in the array
				for (int t = 0; t < A.size(); t++) {
					int digitVal = m - d - 1;
					unsigned long int temp;
					while (digitVal != 0) {
						temp = A[t]/10;
						digitVal--;
					}
					int dig = temp % 10;
					C.push_back(dig);
				}
				newR = newL;	
				//compares side by side values and increases r' by 1 if they are the same
				for (int s = 0; s < C.size() - 1; s++) {
					if (C[s] == C[s+1]) {
						newR++;
					}
					else {
						break;
					}
				}
				//increases total number of calls
				//recursive call
				MSDSort(A, m, newL, newR, d+1, threshold, total_num_calls);
				newL = newR + 1;	
			}
		}
	}
}

// helper function to generage a random array 
void getRandomArray(vector<unsigned long int>& A) {
    for (unsigned int i = 0; i < A.size(); i++)
        A[i] = (unsigned long int) rand() * (unsigned long int)  rand() * (unsigned long int)  rand();

}

#ifndef TESTING
int main() {
    int m = 10;
    int threshold = 2;
    int n = 100000;
    vector<unsigned long int> A;
    bool read_input_from_cin = true;
    
    if (read_input_from_cin) {
        cin >> n; 
        cin >> threshold;  
        A.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> A[i];
	}

    }
    else {
        A.resize(n);
        getRandomArray(A);

    }
    auto start = get_time::now(); 
    int total_num_calls = 0;
    MSDSort(A, m, 0, n-1, 0, threshold, total_num_calls);
 
    auto end = get_time::now();
    auto diff = end - start;

    bool sorted = true;  
    cout << A[0] << endl;
    for (int i = 1; i < n; i++) {
        cout << A[i] << endl;
        if (A[i] < A[i - 1]) {
            sorted = false;   
	}    
    }
    cout << total_num_calls << endl;
    return 0;

}

#endif
