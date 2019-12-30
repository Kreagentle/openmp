#include <iostream>
#include <stdlib.h>
#include <omp.h> 
using namespace std;

int main() {
    int n = 3;
    int o = 4;
    int p = 5;

    int A[n][o];
    int B[o][p];
    int H[n][p];

    for(int i=0; i<n; i++) {  //заполняем и выводим матрицу А
        cout << endl;
        for(int k=0; k<o; k++) {
            A[i][k] = rand() % 100;
            cout<<A[i][k]<<" ";
        }
    }
    cout<<endl;
    cout<<endl;

    for(int i=0; i<o; i++) {  //заполняем и выводим матрицу В
        cout<<endl;
        for(int k=0; k<p; k++) {
            B[i][k] = rand() % 100;
            cout<<B[i][k]<<" ";
        }
    }
    cout<<endl;
    cout<<endl;

    int i, j, k;
    #pragma omp parallel for private(i, j, k)
    for (int i = 0; i < n; i++) { // умножение матриц
        for (int j = 0; j < p; j++){
            H[i][j] = 0;
            for (int t = 0; t < o; t++){
                cout << omp_get_thread_num() << endl; // какая именно нить задействована
                H[i][j] += A[i][t] * B[t][j];
            }
        }
    }

    for(int i=0; i<n; i++) {
        cout<<endl;
        for(int k=0; k<p; k++) {
            cout<<H[i][k]<<" ";
            }
    }
    cout<<endl;
    cout<<endl;
    
    return 0;
}
