using System;

public class FormulaCalculate
{
    private double x, y, z, c, f;

    public FormulaCalculate()
    {
        this.x = 0;
        this.y = 0;
        this.z = 0;
        this.c = 0;
    }
    public FormulaCalculate(double initialX, double initialY, double initialZ, double initialC)
    {
        this.x = initialX;
        this.y = initialY;
        this.z = initialZ;
        this.c = initialC;

    }

    public void Set(double newX, double newY, double newZ, double newC)
    {
        this.x = newX;
        this.y = newY;
        this.z = newZ;
        this.c = newC;
    }

    public void Print()
    {
        Console.WriteLine("f = ((y + (x-1)^(1/3)))^(1/4)) / (|x-y|*(sin(z)^2 + tan(z)))");
        Console.WriteLine($"x = {x}, y = {y}, z = {z}, c = {c}");
        Console.WriteLine($"f = {f}");
    }

    public void Run()
    {
        f = Math.Pow(y + Math.Pow(x - 1, 1.0 / 3.0), 1.0 / 4.0) / (Math.Abs(x - y) * (Math.Pow(Math.Sin(z), 2) + Math.Tan(z)));

    }

    public static void Main()
    {

        double x_val = 3.251;
        double y_val = 0.325;
        double z_val = 0.466 * Math.Pow(10, -4);
        double c_val = 4.25;

        FormulaCalculate evaluatorStatic = new FormulaCalculate();
        evaluatorStatic.Set(x_val, y_val, z_val, c_val);
        evaluatorStatic.Run();
        evaluatorStatic.Print();

        FormulaCalculate evaluatorDynamic = new FormulaCalculate(x_val, y_val, z_val, c_val);
        FormulaCalculate refToDynamic = evaluatorDynamic;
        refToDynamic.Run();
        refToDynamic.Print();

    }
}