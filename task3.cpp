#include <iostream>
#include <stdlib.h>
#include <omp.h> 
using namespace std;
 
int main() {
    int n = 3; // количество строк 
    int o = 4; // количество столбцов
    int A[n][o];
    int b[o];
    int result_vector_pos[o];
    int result_vector_str[o];
    int result_vector_stl[o];
    int result_vector_block[o];
    
    for(int i=0; i<n; i++) {  //заполняем и выводим матрицу А
        cout << endl;
        for(int k=0; k<o; k++) {
            A[i][k] = rand() % 100;
            cout<<A[i][k]<<" ";
        }
    }
    cout<<endl;
    cout<<endl;

    for(int i=0; i<o; i++) {  //заполняем и выводим вектор b
            b[i] = rand() % 100;
            cout<<b[i]<<" ";
            cout << endl;
    }
    cout<<endl;
    cout<<endl;
    
    double start_posl = omp_get_wtime();
    for(int i=0; i<n; i++) {  
	result_vector_pos[i]=0;							
	for(int j=0; j<o; j++) {
	    result_vector_pos[i]+=A[i][j]*b[j];  
	}
    }
    cout << endl; 
    double end_posl = omp_get_wtime();
    cout << "Время последовательного разделения данных:"<< end_posl - start_posl << endl << endl;

    cout << "Последовательное решение:" << endl;
    for(int i=0; i<n; i++) {  
            cout<<result_vector_pos[i]<<" ";
            cout << endl;
    } 
    
for (int THREADS=0; THREADS<4; THREADS++) {
    omp_set_num_threads(THREADS);
    double start_str = omp_get_wtime();
    // разделение данных по строкам 
    int i, j;  
    #pragma omp paralell for private (j)
    for(int i=0; i<n; i++) {  
	result_vector_str[i]=0;							
	for(int j=0; j<o; j++) {
            // cout << omp_get_thread_num() << endl; // какая именно нить задействована
	    result_vector_str[i]+=A[i][j]*b[j];  
	}
    }
   cout << endl; 
   double end_str = omp_get_wtime();
   cout << "Время разделения данных по строкам для количества потоков " << THREADS+1 << ":" << end_str - start_str << endl << endl;

   /* cout << "Разделение данных по строкам:" << endl;
   for(int i=0; i<n; i++) {  //вывод результата для разделения данных по строкам
            cout<<result_vector_str[i]<<" ";
            cout << endl;
    } */
    
    double start_stl = omp_get_wtime();		
    // разделение данных по столбцам 
    double sum; 
    for(int i=0; i<n; i++) {  
	sum=0;
        #pragma omp parallel for reduction(+:sum)							
	for(int j=0; j<o; j++) {
            // cout << omp_get_thread_num() << endl; // какая именно нить задействована
	    sum+=A[i][j]*b[j];  
	}
        result_vector_stl[i]=sum;
    }
   cout << endl; 
   double end_stl = omp_get_wtime();
   cout << "Время разделения данных по столбцам для количества потоков " << THREADS+1 << ":" << end_stl - start_stl << endl << endl;

   /* cout << "Разделение данных по столбцам:" << endl;
   for(int i=0; i<n; i++) {  //вывод результата для разделения данных по столбцам
            cout<<result_vector_stl[i]<<" ";
            cout << endl;
    }
    cout<<endl; */
    
    double start_block = omp_get_wtime();	
    // блочное разделение данных 
    omp_set_num_threads(4);
    omp_set_nested(true);
    #pragma omp parallel for
    for(int i=0; i<n; i++) {  
	double result = 0;
        #pragma omp parallel for reduction(+:result)
	for(int j=0; j<o; j++) {
            // cout << omp_get_thread_num() << endl; // какая именно нить задействована
	    result+=A[i][j]*b[j];  
	}
        result_vector_block[i] = result;
    }
   cout << endl; 
   double end_block = omp_get_wtime();
   cout << "Время блочного разделения данных для количества потоков " << THREADS+1 << ":" << end_block - start_block << endl << endl;

   /* cout << "Блочное разделение данных:" << endl;
   for(int i=0; i<n; i++) {  //вывод результата для блочного разделения данных
            cout<<result_vector_block[i]<<" ";
            cout << endl;
    }
    cout<<endl; */
    }

    return 0;
}
