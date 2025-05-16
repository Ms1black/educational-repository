using System;
using System.IO;

abstract class Function
{
    protected string name;
    protected string parameters;

    public Function(string name)
    {
        this.name = name;
        this.parameters = "";
    }

    public abstract double Calculate(double x);

    public virtual void SetParameters(string paramStr)
    {
        parameters = paramStr;
    }

    public virtual void PrintResult(double x)
    {
        try
        {
            double y = Calculate(x);
            Console.WriteLine($"({parameters}): f({x}) = {y:F4}");
        }
        catch (DivideByZeroException)
        {
            Console.WriteLine($"({parameters}): f({x}) = Error (division by zero)");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"({parameters}): f({x}) = Error ({ex.Message})");
        }
    }
}

class Linear : Function
{
    double a, b;

    public Linear() : base("LinearFunction")
    {
        a = 0;
        b = 0;
    }

    public void Set(double aVal, double bVal)
    {
        a = aVal;
        b = bVal;
        parameters = $"a={a}, b={b}";
    }

    public override void SetParameters(string paramStr)
    {
        string[] parts = paramStr.Split(';');
        foreach (string part in parts)
        {
            string[] kv = part.Split('=');
            if (kv[0] == "a") a = double.Parse(kv[1]);
            if (kv[0] == "b") b = double.Parse(kv[1]);
        }
        parameters = $"a={a}, b={b}";
    }

    public override double Calculate(double x)
    {
        return a * x + b;
    }
}

class Quadratic : Function
{
    double a, b, c;

    public Quadratic() : base("QuadraticFunction")
    {
        a = b = c = 0;
    }

    public void Set(double aVal, double bVal, double cVal)
    {
        a = aVal;
        b = bVal;
        c = cVal;
        parameters = $"a={a}, b={b}, c={c}";
    }

    public override void SetParameters(string paramStr)
    {
        string[] parts = paramStr.Split(';');
        foreach (string part in parts)
        {
            string[] kv = part.Split('=');
            if (kv[0] == "a") a = double.Parse(kv[1]);
            if (kv[0] == "b") b = double.Parse(kv[1]);
            if (kv[0] == "c") c = double.Parse(kv[1]);
        }
        parameters = $"a={a}, b={b}, c={c}";
    }

    public override double Calculate(double x)
    {
        return a * x * x + b * x + c;
    }
}

class Hyperbola : Function
{
    double k, d;

    public Hyperbola() : base("HyperbolaFunction")
    {
        k = 1;
        d = 0;
    }

    public void Set(double kVal, double dVal)
    {
        k = kVal;
        d = dVal;
        parameters = $"k={k}, d={d}";
    }

    public override void SetParameters(string paramStr)
    {
        string[] parts = paramStr.Split(';');
        foreach (string part in parts)
        {
            string[] kv = part.Split('=');
            if (kv[0] == "k") k = double.Parse(kv[1]);
            if (kv[0] == "d") d = double.Parse(kv[1]);
        }
        parameters = $"k={k}, d={d}";
    }

    public override double Calculate(double x)
    {
        if (x == 0)
            throw new DivideByZeroException();
        return k / x + d;
    }
}

class FunctionDemo
{
    Function[] functions;
    double evaluationPoint;

    public FunctionDemo()
    {
        functions = new Function[0];
        evaluationPoint = 0;
    }

    public void LoadFunctions(string filePath)
    {
        if (!File.Exists(filePath))
        {
            Console.WriteLine("File not found.");
            return;
        }

        string[] lines = File.ReadAllLines(filePath);
        functions = new Function[lines.Length];

        for (int i = 0; i < lines.Length; i++)
        {
            string[] parts = lines[i].Split(':');
            if (parts.Length != 2) continue;

            string type = parts[0];
            string paramStr = parts[1];

            if (type == "Linear")
            {
                Linear func = new Linear();
                func.SetParameters(paramStr);
                functions[i] = func;
            }
            else if (type == "Quadratic")
            {
                Quadratic func = new Quadratic();
                func.SetParameters(paramStr);
                functions[i] = func;
            }
            else if (type == "Hyperbola")
            {
                Hyperbola func = new Hyperbola();
                func.SetParameters(paramStr);
                functions[i] = func;
            }
        }
    }

    public void SetEvaluationPoint(double x)
    {
        evaluationPoint = x;
    }

    public void Run()
    {
        Console.WriteLine($"оценка функции при x = {evaluationPoint}\n");
        foreach (Function f in functions)
        {
            if (f != null)
                f.PrintResult(evaluationPoint);
        }
    }

    static void Main()
    {
        FunctionDemo demo = new FunctionDemo();

        string filePath = "functions.txt";
        demo.LoadFunctions(filePath);

        demo.SetEvaluationPoint(2.0);
        demo.Run();
    }
}
