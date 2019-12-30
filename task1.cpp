#include <iostream>
#include <stdlib.h>
#include <omp.h> 
using namespace std;

int main()

{
    int strok, stolb, maxmin;
    strok = 2; // количество строк
    stolb = 4; // количество столбцов
    int a[strok][stolb];
    int min[strok];
    for (int i=0;i<strok;i++){ // создание и вывод матрицы 
        cout<<endl;
        for (int j=0;j<stolb;j++){
            a[i][j] = 1 + rand()%100;
            cout<<a[i][j]<<" ";
        }
    }

    for(int i=0;i<strok;i++){ // присвоение минумуму первых элементов 
        min[i] = a[0][i];
    }

    cout << endl << endl;
    int i, j;
    #pragma omp parallel for private(i, j) 	
    for(int i=0;i<strok;i++){ // поиск минимального элемента
        for(int j=0;j<stolb;j++){
            cout << omp_get_thread_num() << endl; // какая именно нить задействована
            if (a[i][j]<min[i]){
                min[i] = a[i][j];
            }
        }
    }

    cout << endl << endl;
    maxmin = min[0];
    #pragma omp parallel for private(i)
    for (int i=0;i<strok;i++){ // поиск максимального элемента
        cout << omp_get_thread_num() << endl; // какая именно нить задействована
        if (min[i]>maxmin){
            maxmin = min[i];
        }
    }
    cout<<endl<<"Максимальное значение среди минимальных:"<<maxmin<<endl;

    return 0;

}
