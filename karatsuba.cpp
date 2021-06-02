#include <iostream>
#include <string>
using namespace std;

long long* mult(long long *A, long long *B, int size) {
    //temp array
    long long *test = new long long[1];
    test[0] = A[0] * B[0];
    
    if (size == 1) { 
	return test;
    }

    int half = size / 2;

    long long *lowA = new long long[half];
    long long *midA = new long long[half];
    long long *highA = new long long[half];
    long long *lowB = new long long[half];
    long long *midB = new long long[half];
    long long *highB = new long long[half];

    for (int i = 0; i < half; i++) {
        lowA[i] = A[i];
        lowB[i] = B[i];
	highA[i] = A[i + half];
        highB[i] = B[i + half];
    }

    for (int i = 0; i < half; i++) {
        midA[i] = lowA[i] + highA[i];
        midB[i] = lowB[i] + highB[i];
    }

    long long *res0 = mult(lowA, lowB, half);
    long long *res1 = mult(midA, midB, half);
    long long *res2 = mult(highA, highB, half);
    
    //compute the final array
    int size2 = 2 * size + 1;
    long long *final = new long long[size2 + 1];
    for (int i = 0; i < half; i++) {
	final[i] = res0[i];
        final[i + half] = res1[i] - res0[i] - res2[i];
	final[i + size] = res2[i];
    }
    return final;
}

//print function
void print(int size2, long long *res) {
    for (int m = 0; m < size2; m++) {
        cout << res[m] << " ";
    }
    cout << endl;
}

int main() {
   int n;
   string temp;
   getline(cin, temp);
   n = stoi(temp);

   int check = n;
   long long *arr1 = new long long[n+2];
   for (int t = 0; t < (n+1); t++) {
   	cin >> arr1[t];
   }
   
   long long *arr2 = new long long[n+2];
   for (int t = 0; t < (n+1); t++) {
        cin >> arr2[t];
   }

   if (n % 2 == 0) {
        arr1[n+1] = 0;
        arr2[n+1] = 0;
	n++;
   }

   long long *result = mult(arr1, arr2, n+1);
   int val;
   if (check % 2 == 0) {
   	val = (2 * n) - 1;
   }
   else {
   	val = (2 * n) + 1;
   }
   print(val, result);
   
}


