using System;
using System.IO;

namespace Task5
{
    public class BinaryFileOperations
    {
        public static void WriteDoublesToFile(string filePath, double[] numbers)
        {
            try
            {
                using (FileStream fs = new FileStream(filePath, FileMode.Create, FileAccess.Write))
                using (BinaryWriter writer = new BinaryWriter(fs))
                {
                    foreach (double num in numbers)
                    {
                        writer.Write(num);
                    }
                    Console.WriteLine($"файл {filePath}");
                }
            }
            catch (IOException ex)
            {
                Console.WriteLine($"ошибка: {ex.Message}");
            }
        }

        public static void ReadAndPrintPositiveDoubles(string filePath)
        {
            if (!File.Exists(filePath))
            {
                Console.WriteLine($"такого файла нет - {filePath}");
                return;
            }

            try
            {
                using (FileStream fs = new FileStream(filePath, FileMode.Open, FileAccess.Read))
                using (BinaryReader reader = new BinaryReader(fs))
                {
                    Console.WriteLine("положительные числа");
                    while (reader.BaseStream.Position < reader.BaseStream.Length)
                    {
                        try
                        {
                            double num = reader.ReadDouble();
                            if (num > 0)
                            {
                                Console.WriteLine(num);
                            }
                        }
                        catch (EndOfStreamException)
                        {
                            break;
                        }
                    }
                }
            }
            catch (IOException ex)
            {
                Console.WriteLine($"ошибка при чтении {ex.Message}");
            }
        }

        public static void CreateTestBinaryFile(string filePath)
        {
            double[] testNumbers = { 1.5, -2.3, 0.0, 7.8, -0.5, 100.1, 3.14 };
            WriteDoublesToFile(filePath, testNumbers);
        }

        public static void MainTask5()
        {
            Console.WriteLine("РАБОТА С ДВОИЧНЫМИ ФАЙЛАМИ");
            string binaryFilePath = "numbers.dat";

            CreateTestBinaryFile(binaryFilePath);
            ReadAndPrintPositiveDoubles(binaryFilePath);
        }
    }
}