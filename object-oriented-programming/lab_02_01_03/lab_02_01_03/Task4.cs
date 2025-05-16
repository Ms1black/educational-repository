using System;
using System.Text.RegularExpressions;

namespace Task4
{


    public class DateFinder
    {
        public static string FindCurrentYearDates(string text)
        {
            if (string.IsNullOrEmpty(text))
            {
                return string.Empty;
            }

            int currentActualYear = DateTime.Now.Year;
            Regex dateRegex = new Regex($@"\b(0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[0-2])\.({currentActualYear})\b");
            Match match = dateRegex.Match(text);

            return match.Success ? match.Value : string.Empty;
        }

        public static void MainTask4()
        {
            Console.WriteLine("РЕГУЛЯРНЫЕ ВЫРАЖЕНИЯ:");

            string text1 = "25.12.2005, аРбуZ  24.12.2005. m 15.08.1999.  е 01.01.2010.";
            Console.WriteLine(text1);
            string date1 = FindCurrentYearDates(text1);
            Console.WriteLine(!string.IsNullOrEmpty(date1) ? date1 : $"текущего {DateTime.Now.Year} года нет");

        }
    }
}