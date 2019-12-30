#include <iostream>
#include <stdlib.h>
#include <omp.h> 
#include <math.h>
using namespace std;

 
int main() {
    int n = 2;
    int o = 2;
    int p = 2;
 
    int A[n][o];
    int B[o][p];
    int posl[n][p];
    int lent[n][p];
    int block[n][p] = {0};
    
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
    
    double start_posl = omp_get_wtime();
    for (int i = 0; i < n; i++) { // умножение матриц
        for (int j = 0; j < p; j++){
            posl[i][j] = 0;
            for (int t = 0; t < o; t++){
                posl[i][j] += A[i][t] * B[t][j];
            }
        }
    }
    cout<<endl;
    double end_posl = omp_get_wtime();
    cout << "Время последовательного решения:" << end_posl - start_posl << endl << endl;

    cout << "Последовательное решение:" << endl;
    for(int i=0; i<n; i++) {
        cout<<endl;
        for(int k=0; k<p; k++) {
            cout<<posl[i][k]<<" ";
            }
    }
    cout<<endl;
    cout<<endl;

    
    double start_lent = omp_get_wtime();
    int i, j, k;
    omp_set_nested(true);
    omp_set_num_threads (2); 
    #pragma omp parallel for private(j, k)
    for (int i = 0; i < n; i++) { // умножение матриц
        #pragma omp parallel for private (k)
        for (int j = 0; j < p; j++){
            lent[i][j] = 0;
            for (int t = 0; t < o; t++){
                // cout << omp_get_thread_num() << endl; // какая именно нить задействована
                lent[i][j] += A[i][t] * B[t][j];
            }
        }
    }
    cout<<endl;
    double end_lent = omp_get_wtime();
    cout << "Время при ленточном разделении данных:" << end_lent - start_lent << endl << endl;

    cout << "Ленточное разделение данных:" << endl;
    for(int i=0; i<n; i++) {
        cout<<endl;
        for(int k=0; k<p; k++) {
            cout<<lent[i][k]<<" ";
            }
    }
    cout<<endl;
    cout<<endl;
    

    double start_block = omp_get_wtime();
    int gridsize = int (sqrt((double)3));
    int blocksize = p/gridsize;
    omp_set_num_threads(3); 
#pragma omp parallel 
    {
    int id = omp_get_thread_num();
    int strid = id/gridsize;
    int stlid = id%gridsize;
    for (int iter=0; iter<gridsize; iter++) {
        for (int i=strid*blocksize; i<(strid+1)*blocksize; i++)
           for (int j=stlid*blocksize; j<(stlid+1)*blocksize; j++)
              for (int k=iter*blocksize; k<(iter+1)*blocksize; k++)
                 block[i][j] += A[i][k] * B[k][j];
    }
    } 
    cout<<endl;
    double end_block = omp_get_wtime();
    cout << "Время при блочном разделении данных:" << end_block - start_block << endl << endl;

    cout << "Блочное разделение данных:" << endl;
    for(int i=0; i<n; i++) {
        cout<<endl;
        for(int k=0; k<p; k++) {
            cout<<block[i][k]<<" ";
            }
    }
    cout<<endl;
    cout<<endl;
    return 0;
}
