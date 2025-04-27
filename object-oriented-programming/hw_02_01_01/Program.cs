using System;

namespace MyListProject
{

    public class Node
    {
        public int data;
        public Node next;

        public Node(int data)
        {
            this.data = data;
            next = null;
        }
    }

    public class LinkedList
    {
        private Node head;

        public LinkedList()
        {
            head = null;
        }

        public void Push(int[] values)
        {
            foreach (var value in values)
            {
                Node newNode = new Node(value);
                newNode.next = head;
                head = newNode;
            }
        }

        public void Enqueue(int[] values)
        {
            foreach (var value in values)
            {
                Node newNode = new Node(value);
                if (head == null)
                {
                    head = newNode;
                }
                else
                {
                    Node current = head;
                    while (current.next != null)
                    {
                        current = current.next;
                    }
                    current.next = newNode;
                }
            }
        }

        public void InsertAfter(int key, int value)
        {
            Node current = head;

            while (current != null)
            {
                if (current.data == key)
                {
                    Node newNode = new Node(value);
                    newNode.next = current.next;
                    current.next = newNode;
                    return;
                }
                current = current.next;
            }

            Console.WriteLine("Ключ не найден.");
        }

        public void DeleteByKey(int key)
        {
            if (head == null) return;

            if (head.data == key)
            {
                head = head.next;
                return;
            }

            Node current = head;
            Node previous = null;

            while (current != null && current.data != key)
            {
                previous = current;
                current = current.next;
            }

            if (current == null)
            {
                Console.WriteLine("Элемент с ключом не найден.");
                return;
            }

            previous.next = current.next;
        }

        public void Traverse()
        {
            if (head == null)
            {
                Console.WriteLine("Список пуст.");
                return;
            }

            Node current = head;
            Console.Write("Список: ");
            while (current != null)
            {
                Console.Write(current.data + " ");
                current = current.next;
            }
            Console.WriteLine();
        }

        public void Clear()
        {
            Console.Clear();
        }
    }

    class Program
    {
        static void Main()
        {
            LinkedList list = new LinkedList();
            bool running = true;

            while (running)
            {
                Console.WriteLine("\nМеню.");
                Console.WriteLine("1. создать стек");
                // Console.WriteLine("2. создать очередь");
                Console.WriteLine("3. Показать список");
                Console.WriteLine("4. Удалить элемент по ключу");
                Console.WriteLine("5. Добавить элемент после ключа");
                Console.WriteLine("6. Очистить консоль");
                Console.WriteLine("0. Выход");
                Console.Write("Выбор: ");

                string input = Console.ReadLine();
                Console.WriteLine();

                switch (input)
                {
                    case "1":
                        Console.Write("Введите элементы стека через пробел: ");
                        int[] stackValues = Array.ConvertAll(
                            Console.ReadLine().Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries),
                            int.Parse
                        );
                        list = new LinkedList(); 
                        list.Push(stackValues);
                        break;

                    case "2":
                        Console.Write("Введите элементы очереди через пробел: ");
                        int[] queueValues = Array.ConvertAll(
                            Console.ReadLine().Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries),
                            int.Parse
                        );
                        list = new LinkedList(); 
                        list.Enqueue(queueValues);
                        break;

                    case "3":
                        list.Traverse();
                        break;

                    case "4":
                        Console.Write("Введите ключ для удаления: ");
                        if (int.TryParse(Console.ReadLine(), out int keyToDelete))
                            list.DeleteByKey(keyToDelete);
                        else
                            Console.WriteLine("Некорректный ввод.");
                        break;

                    case "5":
                        Console.Write("Введите ключ, после которого добавить: ");
                        if (int.TryParse(Console.ReadLine(), out int key))
                        {
                            Console.Write("Введите новое значение: ");
                            if (int.TryParse(Console.ReadLine(), out int value))
                                list.InsertAfter(key, value);
                            else
                                Console.WriteLine("Некорректное значение.");
                        }
                        else
                        {
                            Console.WriteLine("Некорректный ключ.");
                        }
                        break;

                    case "6":
                        list.Clear();
                        break;

                    case "0":
                        running = false;
                        break;

                    default:
                        Console.WriteLine("Неверный ввод.");
                        break;
                }
            }

            Console.WriteLine("Выход из программы.");
        }
    }
}
