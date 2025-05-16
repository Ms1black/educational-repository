using System;

namespace Task5
{
    public partial class ArrayModification
    {
        public static int[] AddElementToArrayEnd(int[] originalArray, int elementToAdd)
        {
            int oldLength = originalArray.Length;
            int[] newArray = new int[oldLength + 1];

            for (int i = 0; i < oldLength; i++)
            {
                newArray[i] = originalArray[i];
            }
            newArray[oldLength] = elementToAdd;
            return newArray;
        }



        
        
        public static int[,] DeleteColumn(int[,] originalMatrix, int columnIndexToDelete)
        {
            int rows = originalMatrix.GetLength(0);
            int cols = originalMatrix.GetLength(1);

            if (columnIndexToDelete < 0 || columnIndexToDelete >= cols)
            {
                Console.WriteLine("неправильный индекс!");
                return originalMatrix; 
            }

            if (cols == 1 && columnIndexToDelete == 0)
            {
                return new int[rows, 0];
            }

            int[,] newMatrix = new int[rows, cols - 1];
            for (int i = 0; i < rows; i++)
            {
                int newColIndex = 0;
                for (int j = 0; j < cols; j++)
                {
                    if (j == columnIndexToDelete)
                    {
                        continue; 
                    }
                    newMatrix[i, newColIndex] = originalMatrix[i, j];
                    newColIndex++;
                }
            }
            return newMatrix;
        }

        public static void MainTask5()
        {
            Console.WriteLine("ДИНАМИЧЕСКИЙ ОДНОМЕРНЫЙ МАССИВ:");
            int[] myArray = { 1, 2, 3 };
            Console.WriteLine("до - [" + string.Join(", ", myArray) + "]");

            myArray = AddElementToArrayEnd(myArray, 4);
            Console.WriteLine($"после - [" + string.Join(", ", myArray) + "]");

            myArray = AddElementToArrayEnd(myArray, 50);
            Console.WriteLine($"после - [" + string.Join(", ", myArray) + "]");

            Console.WriteLine("ДИНАМИЧЕСКИЙ ДВУМЕРНЫЙ МАССИВ:");
            int[,] matrix = {
                {1, 2, 3, 4},
                {5, 6, 7, 8},
                {9, 10, 11, 12}
            };

            Console.WriteLine("до");
            Task4.ArrayManipulations.PrintMatrix(matrix); 

            int[,] modifiedMatrix = DeleteColumn(matrix, 1);

            Console.WriteLine($"после");
            if (modifiedMatrix.GetLength(1) > 0) 
            {
                Task4.ArrayManipulations.PrintMatrix(modifiedMatrix);
            } 
            else 
            {
                Console.WriteLine("матрица пустая!");
            }
        }
    }
}

