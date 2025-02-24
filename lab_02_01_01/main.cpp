#include <iostream>
#include <random>
#include <algorithm>


int main() 
{
    int min_el = 100;
    const int N = 14, M = 14;
    int start = -6;
    int end = 6;
    int A[N][M];
    int i, j;

    std::cout << "Исходная матрица:\n" << std::endl;


    for (i = 0; i < N; i++) 
    {
        for (j = 0; j < M; j++) 
        {
            A[i][j] = rand() % (end - start + 1) + start;
        }
    }
    

    for (i = 0; i < N; i++) 
    { 
        for (j = 0; j < M; j++) {

            std::cout << A[i][j] << " ";
            
        } std::cout << std::endl; 
            
    }


    int min = A[0][0], max = A[0][0];
    int min_i = 0, min_j = 0, max_i = 0, max_j = 0;

    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < M; j++) 
        {
            if (A[i][j] <= min) 
            {
                min_el = std::min(min, A[i][j]);
                min_i = i;
                min_j = j;
            }
            if (A[i][j] >= max) 
            {
                max = std::max(max, A[i][j]);
                max_i = i;
                max_j = j;
        
            }
        }         
    }


    int row = -1, max_length = 0;
    int left = 0, right = 0;

    for (int i = 0; i < N; i++) 
    {
        int min_pos = -1, max_pos = -1;

        for (int j = 0; j < M; j++) 
        {
            if (A[i][j] == min) min_pos = j;
            if (A[i][j] == max) max_pos = j;
        }

        if (min_pos != -1 && max_pos != -1 && min_pos != max_pos) 
        {
            if (std::abs(min_pos - max_pos) - 1 > max_length) 
                {
                    max_length = std::abs(min_pos - max_pos) - 1;
                    row = i;
                    left = std::min(min_pos, max_pos);
                    right = std::max(min_pos, max_pos);
                }

        }
    }


    if (row != -1) 
    {
        std::cout << "\nСтрока с самой длинной последовательностью: " << row << "\nЭлементы между min и max: ";

        for (int j = left + 1; j < right; j++) 
        {
            std::cout << A[row][j] << " ";
        }
    } 
    
    std::cout << std::endl;


    for (i = 0 ; i < N; i++) 
    {
        for (j = 0; j < M; j++) 
        {
            if(i<=j)
            {
               if(i + j + 1 >= N)
               {
                    if(A[i][j] <= min_el)
                    {
                        min_el = A[i][j];
                    }
               } 
            }
      
        }
    }

    std::cout << "\nМинимальный элемент среди выделенных черным цветом: "<< min_el << std::endl;


    return 0;
}
