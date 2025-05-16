using System;

public abstract class AbstractBase
{
    public abstract string MyProperty { get; set; }
    public abstract int this[string key] { get; set; }
    public abstract void AbstractMethod(string message);
}

public interface IMyInterface1
{
    string MyProperty { get; set; }
    int this[string key] { get; set; }
    void InterfaceMethod(string message);
}

public interface IMyInterface2
{
    string MyProperty { get; set; }
    int this[string key] { get; set; }
    void InterfaceMethod(string message);
}

public class ConcreteDerived : AbstractBase, IMyInterface1, IMyInterface2
{
    private string abstractProperty = "Abstract";
    public override string MyProperty
    {
        get { return abstractProperty; }
        set { abstractProperty = value; Console.WriteLine("Свойство Abstract установлено на: " + value); }
    }

    private int abstractIndexerValue;
    public override int this[string key]
    {
        get { Console.WriteLine("Индексатор Abstract: получение по ключу " + key); return abstractIndexerValue; }
        set { Console.WriteLine("Индексатор Abstract: ключ " + key + ", значение " + value); abstractIndexerValue = value; }
    }

    public override void AbstractMethod(string message)
    {
        Console.WriteLine("Метод Abstract: " + message);
    }

    private string i1Property = "I1";
    string IMyInterface1.MyProperty
    {
        get { return i1Property; }
        set { i1Property = value; Console.WriteLine("Свойство IMyInterface1 установлено на: " + value); }
    }

    private int i1IndexerValue;
    int IMyInterface1.this[string key]
    {
        get { Console.WriteLine("Индексатор IMyInterface1: получение по ключу " + key); return i1IndexerValue; }
        set { Console.WriteLine("Индексатор IMyInterface1: ключ " + key + ", значение " + value); i1IndexerValue = value; }
    }

    void IMyInterface1.InterfaceMethod(string message)
    {
        Console.WriteLine("Метод IMyInterface1: " + message);
    }

    private string i2Property = "I2";
    string IMyInterface2.MyProperty
    {
        get { return i2Property; }
        set { i2Property = value; Console.WriteLine("Свойство IMyInterface2 установлено на: " + value); }
    }

    private int i2IndexerValue;
    int IMyInterface2.this[string key]
    {
        get { Console.WriteLine("Индексатор IMyInterface2: получение по ключу " + key); return i2IndexerValue; }
        set { Console.WriteLine("Индексатор IMyInterface2: ключ " + key + ", значение " + value); i2IndexerValue = value; }
    }

    void IMyInterface2.InterfaceMethod(string message)
    {
        Console.WriteLine("Метод IMyInterface2: " + message);
    }
}

public class Program
{
    public static void Main()
    {
        ConcreteDerived obj = new ConcreteDerived();

        obj.MyProperty = "Новое значение abstract свойства";
        Console.WriteLine("Свойство MyProperty: " + obj.MyProperty);
        obj["ключ_1"] = 10;
        Console.WriteLine("Значение индексатора: " + obj["ключ_1"]);
        obj.AbstractMethod("Сообщение для метода abstract");

        IMyInterface1 iv1 = obj;
        iv1.MyProperty = "Новое значение 1";
        Console.WriteLine("Свойство IMyInterface1: " + iv1.MyProperty);
        iv1["ключ_2"] = 20;
        Console.WriteLine("Значение индексатора IMyInterface1: " + iv1["ключ_2"]);
        iv1.InterfaceMethod("Сообщение 1");

        IMyInterface2 iv2 = obj;
        iv2.MyProperty = "Новое значение 2";
        Console.WriteLine("Свойство IMyInterface2: " + iv2.MyProperty);
        iv2["ключ_3"] = 30;
        Console.WriteLine("Значение индексатора IMyInterface2: " + iv2["ключ_3"]);
        iv2.InterfaceMethod("Сообщение 3");
    }
}
