using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SequentialMatrixMultiplication
{
    class Program
    {
        static void Main(string[] args)
        {
            Random rand = new Random();

            string strOutput;
            int value;
            int n = rand.Next(1, 100);
            var stopwatch = new System.Diagnostics.Stopwatch();

            int[,] arrayInput1 = new int[n, n];
            int[,] arrayInput2 = new int[n, n];
            int[,] arrayOutput = new int[n, n];

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j <n; j++)
                {
                    arrayInput1[i, j] = rand.Next(100);
                    arrayInput2[i, j] = rand.Next(100);
                }
            }

            stopwatch.Start();

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    value = 0;
                    for (int k = 0; k < n; k++)
                    {
                        value += arrayInput1[i, k] * arrayInput2[k, j];
                    }
                    arrayOutput[i, j] = value;

                }
            }

            stopwatch.Stop();

            printArrays();

            Console.WriteLine("Runtime is: ");
            Console.WriteLine(stopwatch.Elapsed.ToString());

            void printArrays()
            {
                strOutput = "Input Array One\n[";

                for (int i = 0; i < n; i++)
                {
                    strOutput += "[";

                    for (int j = 0; j < n; j++)
                    {
                        strOutput += arrayInput1[i, j] + ",";
                    }

                    strOutput += "]\n";
                }

                strOutput += "]\n";

                Console.WriteLine(strOutput);

                strOutput = "Input Array Two\n[";

                for (int i = 0; i < n; i++)
                {
                    strOutput += "[";

                    for (int j = 0; j < n; j++)
                    {
                        strOutput += arrayInput2[i, j] + ",";
                    }

                    strOutput += "]\n";
                }

                strOutput += "]\n";

                Console.WriteLine(strOutput);

                strOutput = "Output Array\n[";

                for (int i = 0; i < n; i++)
                {
                    strOutput += "[";

                    for (int j = 0; j < n; j++)
                    {
                        strOutput += arrayOutput[i, j] + ",";
                    }

                    strOutput += "]\n";
                }

                strOutput += "]\n";

                Console.WriteLine(strOutput);
            }
        }
    }
}
