// Task1.cs
using System;
using System.Linq;

namespace Task1
{
    public class MaxSeriesFinder
    {
        private int[] inputArray;
        private int maxSeriesLength;
        private int seriesValue;
        private string seriesNotFoundMessage;


        public MaxSeriesFinder()
        {
            this.inputArray = new int[0];
            this.maxSeriesLength = 0;
            this.seriesValue = 0;
            this.seriesNotFoundMessage = "серии нет";
        }

        public void Set(int[] array)
        {
            this.inputArray = array ?? new int[0];
        }

        public void Run()
        {
            if (this.inputArray == null || this.inputArray.Length == 0)
            {
                this.maxSeriesLength = 0;
                return;
            }

            this.maxSeriesLength = 0;
            this.seriesValue = this.inputArray[0];

            if (this.inputArray.Length == 1)
            {
                this.maxSeriesLength = 1;
                this.seriesValue = this.inputArray[0];
                return;
            }

            int currentSeriesLength = 0;
            currentSeriesLength = 1;

            for (int i = 1; i < this.inputArray.Length; i++)
            {
                if (this.inputArray[i] == this.inputArray[i - 1])
                {
                    currentSeriesLength++;
                }
                else
                {
                    if (currentSeriesLength > this.maxSeriesLength)
                    {
                        this.maxSeriesLength = currentSeriesLength;
                        this.seriesValue = this.inputArray[i - 1];
                    }
                    currentSeriesLength = 1;
                }
            }

            if (currentSeriesLength > this.maxSeriesLength)
            {
                this.maxSeriesLength = currentSeriesLength;
                this.seriesValue = this.inputArray[this.inputArray.Length - 1];
            }

            if (this.inputArray.Length > 0 && this.maxSeriesLength == 0)
            {
                this.maxSeriesLength = 1;
                this.seriesValue = this.inputArray[0]; 
            }

        }

        public void Print()
        {
            Console.WriteLine("ФУНКЦИИ (простейшие):");
            if (this.inputArray == null || this.inputArray.Length == 0)
            {
                Console.WriteLine(this.seriesNotFoundMessage);
                return;
            }

            Console.WriteLine("исходный массив - " + string.Join(", ", this.inputArray));
            if (this.maxSeriesLength > 0)
            {
                Console.WriteLine($"максимальная серия: число - {this.seriesValue}, длина - {this.maxSeriesLength}");
            }
            else 
            {
                Console.WriteLine("ошибка");
            }
        }

        public static void MainTask1()
        {
            MaxSeriesFinder finder = new MaxSeriesFinder();

            int[] X1 = { 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1 };
            finder.Set(X1);
            finder.Run();
            finder.Print();
        }
    }
}