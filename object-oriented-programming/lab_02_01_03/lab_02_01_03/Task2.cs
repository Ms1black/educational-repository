using System;

namespace Task2
{

    public class StringDigitSum
    {
        public static int SumDigitsInString(string s)
        {
            if (s == null) return 0;

            int sum = 0;
            foreach (char c in s)
            {
                if (char.IsDigit(c))
                {
                    sum += (int)char.GetNumericValue(c);
                }
            }
            return sum;
        }

        public static void MainTask2()
        {
            Console.WriteLine("СТРОКИ - А)");
            string str1 = "abc123xyz45";
            Console.WriteLine($"{str1}: сумма цифр - {SumDigitsInString(str1)}");
        }
    }
}