#include <utility>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <string>
#include <math.h>
using namespace std;

// a helper function to print arrays
void print(vector <int> const &a) {
    for (int i = 0; i < a.size(); i++) {
        cout << a.at(i) << " ";
    	cout << endl;
    }
}

// ArgMin(M) is a helper function that returns the index of the lowest value
int ArgMin(const vector<pair<int,int>> & M) {
        int l = 0;
        //gets the size of M
        int m = M.size();

        //iterates from 0 to m
        for (int i = 0; i < m; i++) {
                //comparison between the ith position and the lth position
                if (M[i].first < M[l].first) {
                        l = i;
                }
        }

        //returns the index l
        return l;
}

// splits A into k sub-arrays
vector<vector<int>> split(const vector<int> & A, int k) {
        //size of array
        int n = A.size();
        int q = n/k;
        int r = n%k;

        //sets index to 0
        int index = 0;
        int val = 0;

        //creates a temp vectors of vectors to return
        vector<vector<int>> newA;

        for (int i = 0; i < r; i++) {
                vector<int> A1;
                for (int j = 0; j <= q; j++){
                        val = A[index];
                        A1.push_back(val);
                        index++;
                }
                //adds vector into vector of vectors
                newA.push_back(A1);
        }

        for (int i = r; i < k; i++) {
                vector<int> A2;
                for (int j = 0; j < q; j++) {
                        val = A[index];
                        A2.push_back(val);
                        index++;
                }
                //adds vector into vector of vectors
                newA.push_back(A2);
        }

        //need to return vector of vectors (the k subarrays)
        return newA;
}

/*k-way merge implemented as in the assignment    
 if all Aj's are sorted, the output must be      
 sorted as well
 */                                  
vector<int> kWayMerge(const vector<vector<int>> & Aj)
{
        //k is the size of Aj
        int k = Aj.size();
        int n = 0;

        //adds up all of the lengths of the vectors inside of the vector Aj
        for (int a = 0; a < k; a++) {
                n = n + Aj[a].size();
        }

        //creates I, which is filled with 0s at the beginning
        vector<int> I(k);

        //sets j to 1 and l to 0
        int j = 1;
        int l = 0;

        //creates an array A
        vector<int> A;

        for (int i = 0; i < n; i++) {
                //vector of pairs
                vector<pair<int,int>> M;
                for (int j = 0; j < k; j++) {
			//checks if I[j] is not equal to the size of Aj[j]
                        if (I[j] != Aj[j].size()) {
                                //adds the pair to M
                                M.push_back(make_pair(Aj[j][I[j]], j));
                        }
                }

		//changes l and j
                l = ArgMin(M);
                j = M[l].second;

                //adds in these values into A
                A.push_back(Aj[j][I[j]]);
                I[j] = I[j] + 1;
        }
        //return a vector, A
        return A;
}

// mergesort                               //
void kWayMergeSort(vector<int> & A, int k)
{
        //base case if array is <= 1 in length
        int size = A.size();
        if (size <= 1) {
                //returns whatever is already there
                return;
        }
        else {
                //creates a vector of vectors to store result of split
                vector<vector<int>> B = split(A, k);

                //recursion
                for (int j = 0; j < k; j++) {
                        kWayMergeSort(B[j], k);
                }
                //calls kWayMerge
                A = kWayMerge(B);
        }
}

#ifndef TESTING
int main()
{
    string line;
    getline(cin, line);
    vector<int> A;
    int k = atoi(line.c_str());
    while(true) {
        string line;
        if(!getline(cin, line)) {
            break;
	}
        int a = atoi(line.c_str());
        A.push_back(a);
    }
    print(A);
    kWayMergeSort(A, k);
    print(A);
}
#endif
