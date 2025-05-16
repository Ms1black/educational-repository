using System;

namespace Task4
{
    public partial class ArrayManipulations
    {
        public static int[] GetElementsEndingWithK(int[] array, int k)
        {

            int count = 0;
            foreach (int num in array)
            {
                if (Math.Abs(num % 10) == k)
                {
                    count++;
                }
            }

            int[] resultArray = new int[count];

            int index = 0;
            foreach (int num in array)
            {
                if (Math.Abs(num % 10) == k)
                {
                    resultArray[index] = num;
                    index++;
                }
            }
            return resultArray;
        }

        public static void ReverseEvenColumns(int[,] matrix)
        {
            int rows = matrix.GetLength(0);
            int cols = matrix.GetLength(1);

            for (int j = 0; j < cols; j++)
            {
                if (j % 2 == 0)
                {
                    for (int i = 0; i < rows / 2; i++)
                    {
                        int temp = matrix[i, j];
                        matrix[i, j] = matrix[rows - 1 - i, j];
                        matrix[rows - 1 - i, j] = temp;
                    }
                }
            }
        }

        public static void PrintMatrix(int[,] matrix)
        {
            int rows = matrix.GetLength(0);
            int cols = matrix.GetLength(1);
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    Console.Write($"{matrix[i, j],4}");
                }
                Console.WriteLine();
            }
        }

        public static string SortWordsInString(string text)
        {
            if (string.IsNullOrEmpty(text))
            {
                return string.Empty;
            }

            char[] delimiters = new char[] { ' ', ',', '.', ';', ':', '!', '?', '\t', '\n', '\r' };
            string[] words = text.Split(delimiters, StringSplitOptions.RemoveEmptyEntries);
            Array.Sort(words);

            return string.Join(" ", words);
        }


        public static void MainTask4()
        {
            Console.WriteLine("ОДНОМЕРНЫЙ МАССИВ:");
            int[] sourceArray1D = { 12, 23, 5, 42, 125, 50, -15, 22 };
            int kVal = 2;
            Console.WriteLine($"до - [{string.Join(", ", sourceArray1D)}], K = {kVal}");

            int[] filteredArray = GetElementsEndingWithK(sourceArray1D, kVal);
            Console.WriteLine($"после - [{string.Join(", ", filteredArray)}]");

            Console.WriteLine("ДВУМЕРНЫЙ МАССИВ:");

            int[,] matrix = {
                    {1, 2, 3, 4},
                    {5, 6, 7, 8},
                    {9, 10, 11, 12},
                    {13, 14, 15, 16}
                };

            Console.WriteLine("до ");
            PrintMatrix(matrix);

            ReverseEvenColumns(matrix);

            Console.WriteLine("после ");
            PrintMatrix(matrix);

            Console.WriteLine("СТРОКИ:");
            string inputText = "Брич Вайпер! Рейна Джетт Чамбер?";
            Console.WriteLine($"до - \"{inputText}\"");

            string sortedText = SortWordsInString(inputText);
            Console.WriteLine($"после - \"{sortedText}\"");

        }
    }
}