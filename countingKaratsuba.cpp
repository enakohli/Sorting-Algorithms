#include <iostream>
#include <map>
#include <math.h> 
using namespace std;

long long *multiply(long long *A, long long *B, int size) {
    long long *final = new long long[2 * size - 1];

    for (int i = 0; i < (2 * size) - 1; i++) {
        final[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            final[i + j] += A[i] * B[j];
        }
    }
    return final;
}

long long* countFreq(long long arr[], int n) {
    map<int, int> newM;
    for (int i = 0; i < n; i++) {
        newM[arr[i]]++;
    }
 
    long long *temp = new long long[1000];
    for (auto x : newM) {
        temp[x.first] = x.second;
    }
    return temp;
}

int main() {
	int n;
    string temp;
    getline(cin, temp);
    n = stoi(temp);

	long long *a = new long long[n];
    for (int t = 0; t < n; t++) {
            cin >> a[t];
    }
	long long *arr = countFreq(a, n);
    long long *result = multiply(arr, arr, 1000);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] == a[j])  {
                for (int k = j; k < n - 1; k++) {
                    a[k] = a[k + 1];
                }
                n--;
                j--;
            }
        }
    }
    
    int final = 0;
    for (int k = 0; k < n; k++) {
        final += result[a[k]];
    }
    final = floor(final / 2);
    cout << final << endl;
}
