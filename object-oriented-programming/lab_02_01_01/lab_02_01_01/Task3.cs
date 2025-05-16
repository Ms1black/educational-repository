using System;

namespace Task3{
    public class SequenceTransformation
    {
        public static int[] TransformSequence(int[] originalSequence)
        {
            if (originalSequence == null || originalSequence.Length == 0)
            {
                return new int[0];
            }

            int maxElement = originalSequence[0];
            for (int i = 1; i < originalSequence.Length; i++)
            {
                if (originalSequence[i] > maxElement)
                {
                    maxElement = originalSequence[i];
                }
            }

            int[] newSequence = new int[originalSequence.Length];
            for (int i = 0; i < originalSequence.Length; i++)
            {
                if (originalSequence[i] == maxElement)
                {
                    newSequence[i] = 1;
                }
                else
                {
                    newSequence[i] = 0;
                }
            }
            return newSequence;
        }


        public static void MainTask3()
        {
            Console.WriteLine("МАССИВЫ:");
            int[] a = { 3, 8, 2, 8, 5, 1, 8 };
            Console.WriteLine("до - " + string.Join(", ", a));

            int[] b = TransformSequence(a);
            Console.WriteLine("после - " + string.Join(", ", b));

            int[] c = { 1, 2, 3, 5, 4 };
            Console.WriteLine("до - " + string.Join(", ", c));
            int[] d = TransformSequence(c);
            Console.WriteLine("после - " + string.Join(", ", d));
        }
    }
}