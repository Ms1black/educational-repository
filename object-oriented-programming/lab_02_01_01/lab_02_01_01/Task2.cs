// Task2.cs
using System;

namespace Task2
{

    public class GradientCalculator
    {

        public delegate double FunctionND(double[] vars);


        public static double CalculateGradientComponent(FunctionND func, double[] point, int varIndex, double delta)
        {

            double[] pointPlusDelta = (double[])point.Clone();
            pointPlusDelta[varIndex] += delta;

            double fAtPoint = func(point);
            double fAtPointPlusDelta = func(pointPlusDelta);

            return (fAtPointPlusDelta - fAtPoint) / delta;
        }

        public static double[] CalculateGradientVector(FunctionND func, double[] point, double delta)
        {
            int numVariables = point.Length;
            double[] gradient = new double[numVariables];

            for (int i = 0; i < numVariables; i++)
            {

                gradient[i] = CalculateGradientComponent(func, point, i, delta);
            }
            return gradient;
        }

        public static double FunctionZ1(double[] vars)
        {
            double x = vars[0];
            double y = vars[1];
            return 2 * x * x - 4 * y * y + 8 * x * y - 2 * x + 1;
        }

        public static double FunctionZ2(double[] vars)
        {
            double x = vars[0];
            double y = vars[1];
            return 8 * x * x * y - 2 * x * y;
        }

        public static void MainTask2()
        {
            Console.WriteLine("ФУНКЦИИ (рекурсивные):");
            double[] pointX = { 4.0, 6.0 };
            double delta = 1e-3;

            double[] gradientZ1 = CalculateGradientVector(FunctionZ1, pointX, delta);
            Console.WriteLine($"Градиент Z1 в точке X(4,6) - ({gradientZ1[0]:F3}, {gradientZ1[1]:F3})");


            double[] gradientZ2 = CalculateGradientVector(FunctionZ2, pointX, delta);
            Console.WriteLine($"Градиент Z2 в точке X(4,6) - ({gradientZ2[0]:F3}, {gradientZ2[1]:F3})");

        }
    }
}