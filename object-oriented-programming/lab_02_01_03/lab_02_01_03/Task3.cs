using System;

namespace Task3
{
    public partial class LongestWordsFinder
    {
        public static string[] FindAllLongestWords_NoList(string message)
        {
            if (string.IsNullOrWhiteSpace(message))
            {
                return new string[0];
            }

            char[] delimiters = new char[] { ' ', ',', '.', ';', ':', '!', '?', '\t', '\n', '\r', '(', ')', '[', ']', '{', '}' };
            string[] words = message.Split(delimiters, StringSplitOptions.RemoveEmptyEntries);

            if (words.Length == 0)
            {
                return new string[0];
            }

            int maxLength = 0;
            foreach (string word in words)
            {
                if (word.Length > maxLength)
                {
                    maxLength = word.Length;
                }
            }

            int countLongest = 0;
            foreach (string word in words)
            {
                if (word.Length == maxLength)
                {
                    countLongest++;
                }
            }

            string[] longestWordsArray = new string[countLongest];
            int index = 0;
            foreach (string word in words)
            {
                if (word.Length == maxLength)
                {
                    longestWordsArray[index] = word;
                    index++;
                }
            }
            return longestWordsArray;
        }

        public static void MainTask3() 
        {
            Console.WriteLine("СТРОКИ - Б)");
            string text1 = "Бла бла блааа блэ блэ блэээ блу блу блууууу";

            Console.WriteLine($"\"{text1}\"");
            string[] result1 = FindAllLongestWords_NoList(text1); 
            Console.WriteLine("самые длинные слова - [" + string.Join(", ", result1) + "]");

        }
}
}