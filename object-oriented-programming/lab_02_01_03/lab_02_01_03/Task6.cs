using System;
using System.IO;

namespace Task6
{
    public class TextFileOperations
    {
        public static void PrintLinesOfSpecificLength(string filePath, int requiredLength)
        {
            if (!File.Exists(filePath))
            {
                Console.WriteLine($"нет такого файла - {filePath}");
                return;
            }

            try
            {
                using (StreamReader reader = new StreamReader(filePath))
                {
                    string line;
                    bool found = false;
                    Console.WriteLine($"файл - '{filePath}' длина - {requiredLength}:");
                    while ((line = reader.ReadLine()) != null)
                    {
                        if (line.Length == requiredLength)
                        {
                            Console.WriteLine(line);
                            found = true;
                        }
                    }
                    if (!found)
                    {
                        Console.WriteLine("таких строк нет");
                    }
                }
            }
            catch (IOException ex)
            {
                Console.WriteLine($"ошибка при чтении {ex.Message}");
            }
        }

        public static void MainTask6()
        {
            Console.WriteLine("РАБОТА С ТЕКСТОВЫМИ ФАЙЛМАИ:");
            string textFilePath = "example.txt";

            string[] linesToWrite = {
                    "FFFFFFFFF",
                    "12345", 

                };
            File.WriteAllLines(textFilePath, linesToWrite);

            int length2 = 5;
            PrintLinesOfSpecificLength(textFilePath, length2);

        }
    }
}