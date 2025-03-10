#include <random>
#include <algorithm>
#include <iostream>

const int SIZE_MATRIX = 14;

int i, j;

void iPrintMatrix(int matrix[SIZE_MATRIX][SIZE_MATRIX]){

    for (i = 0; i < SIZE_MATRIX; i++)
    {
        for (j = 0; j < SIZE_MATRIX; j++) {

            std::cout << matrix[i][j] << " ";
        } std::cout << std::endl;
    }
}

int main()
{

    int imin_el = 100;
    int imax_column_el = -100;
    int istart = -6;
    int iend = 6;

    int iArray[SIZE_MATRIX][SIZE_MATRIX];

    std::cout << "Исходная матрица:\n" << std::endl;

    for (i = 0; i < SIZE_MATRIX; i++)
    {
        for (j = 0; j < SIZE_MATRIX; j++)
        {
        iArray[i][j] = rand() % (iend - istart + 1) + istart;
        }
    }

    iPrintMatrix(iArray);

    std::cout << "Наибольшие эелементы четных столбцов:\n" << std::endl;
    
    
    for (j = 1; j < SIZE_MATRIX; j+=2)
    {
        for (i = 0; i < SIZE_MATRIX; i++)
        {
            if (iArray[i][j] >= imax_column_el)
            {
            imax_column_el = iArray[i][j];
            }
        }

    std::cout << imax_column_el << " ";

    }

    int imin = iArray[0][0], imax = iArray[0][0];
    int imin_i = 0, imin_j = 0, imax_i = 0, imax_j = 0;

    for (int i = 0; i < SIZE_MATRIX; i++)
    {
        for (int j = 0; j < SIZE_MATRIX; j++)
        {
            if (iArray[i][j] <= imin)
            {
                imin_el = std::min(imin, iArray[i][j]);
                imin_i = i;
                imin_j = j;
            }
            if (iArray[i][j] >= imax) 
            {
                imax = std::max(imax, iArray[i][j]);
                imax_i = i;
                imax_j;
            }
        }
    }

    int iNumberMaxRow = -1, imax_length = 0;
    int ileft = 0, iright = 0;


    for (int i = 0; i < SIZE_MATRIX; i++)
    {

        int imin_pos = -1, imax_pos = -1;

        for (int j = 0; j < SIZE_MATRIX;j++)
        {

        if (iArray[i][j] == imin) imin_pos = j;
        if (iArray[i][j] == imax) imax_pos = j;
        
        }
        if (imin_pos != -1 && imax_pos != -1 && imin_pos != imax_pos)
        {
            if (std::abs(imin_pos - imax_pos) - 1 > imax_length)
            {
                imax_length = std::abs(imin_pos - imax_pos) - 1;
                iNumberMaxRow = i;
                ileft = std::min(imin_pos, imax_pos);
                iright = std::max(imin_pos, imax_pos);
            }
        }
    }

    if (iNumberMaxRow != -1)
    {
        std::cout << "\nСтрока с самой длинной последовательностью: " <<
        iNumberMaxRow << "\nЭлементы между min и max: ";

        for (int j = ileft + 1; j < iright; j++)
        {
            std::cout << iArray[iNumberMaxRow][j] << " ";
        }
    }

    std::cout << std::endl;

    for (i = 0 ; i < SIZE_MATRIX; i++)
    {
        for (j = 0; j < SIZE_MATRIX; j++)
        {
            if(i<=j)
            {
                if(i + j + 1 >= SIZE_MATRIX)
                {
                    if(iArray[i][j] <= imin_el)
                    {
                        imin_el = iArray[i][j];
                    }
                }
            }
        }
    }


    std::cout << "\nМинимальный элемент среди выделенных черным цветом: "<<
    imin_el << std::endl;

    return 0;
}
