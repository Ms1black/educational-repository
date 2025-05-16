using System;

namespace Task1
{


    public class FunctionTable
    {

        public static double CalculateY(double x, out bool defined)
        {
            defined = true;

            double term1_arg = Math.Pow(x, 4) - 1;
            if (term1_arg <= 0)
            {
                defined = false;
                return double.NaN;
            }

            double term2_arg = 1 + x;
            if (term2_arg <= 0)
            {
                defined = false;
                return double.NaN;
            }

            try
        {
            double ln_term1 = Math.Log(term1_arg); 
            double ln_term2 = Math.Log(term2_arg);
            return ln_term1 * ln_term2;
        }
        catch (ArgumentOutOfRangeException) 
        {
            defined = false;
            return double.NaN;
        }

        }

        public static void PrintFunctionTable(double a, double b, double h)
        {

            Console.WriteLine("   x          y      ");

            for (double x = a; x <= b; x += h)
            {

                bool isDefined;
                double y = CalculateY(x, out isDefined);

                if (isDefined)
                {
                    Console.WriteLine($" {x,7:F3}  {y,11:F5} ");
                }
                else
                {
                    Console.WriteLine($" {x,7:F3}   не определена  ");
                }
            }
        }

        public static void MainTask1()
        {
            Console.WriteLine("ИСКЛЮЧИТЕЛЬНЫЕ СИТУАЦИИ:");

            double a1 = 1.1;
            double b1 = 2.0;
            double h1 = 0.1;
            PrintFunctionTable(a1, b1, h1);

        }
    }
}