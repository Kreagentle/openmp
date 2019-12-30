#include <bits/stdc++.h> 
#include <stdlib.h>
#include <omp.h> 
using namespace std; 
  
void search(char* pat, char* file) 
{ 
    int M = strlen(pat); 
    int N = strlen(file); 
  
    for (int i = 0; i <= N - M; i++) { 
        int j; 
        for (j = 0; j < M; j++) 
            if (file[i + j] != pat[j]) 
                break; 
        if (j == M) // если pat[0...M-1] = file[i, i+1, ...i+M-1] 
            cout << "Подстрока найдена на позиции: "
                 << i << endl; 
    } 
} 

void searchParallel(char* pat, char* file) 
{ 
    int M = strlen(pat); 
    int N = strlen(file); 
    
    int i, j;
    #pragma omp parallel for private(i, j)
    for (int i = 0; i <= N - M; i++) { 
        int j;
        for (j = 0; j < M; j++) 
            if (file[i + j] != pat[j]) 
                break; 
        // cout << omp_get_thread_num() << endl; // какая именно нить задействована
        #pragma omp critical
        {
        if (j == M) // если pat[0...M-1] = file[i, i+1, ...i+M-1] 
            cout << "Подстрока начинается с позиции: "
                 << i << endl;
        } 
    } 
} 
  
int main() 
{   
    char pat[] = "AABA";
    char file[50]; 
    ifstream fin("string.txt");
    fin >> file;

    double start_posl = omp_get_wtime();
    search(pat, file); 
    double end_posl = omp_get_wtime();
    cout << "Время последовательного решения:" << end_posl - start_posl << endl << endl;
    double start_par = omp_get_wtime();
    searchParallel(pat, file);	
    double end_par = omp_get_wtime();
    cout << "Время параллельного решения:" << end_par - start_par << endl << endl;
    return 0; 
} 
