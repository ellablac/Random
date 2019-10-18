using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Contest0413
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            Console.ReadKey();
            //string[] lines = System.IO.File.ReadAllLines(@".C:\Ella\LeetCode\Contest0413\input.txt");

            Solution sol = new Solution();

            bool answ = sol.DivisorGame(4);

            Console.Write("Answer: ");
            if (answ)
            Console.Write("true");
            else
            Console.Write("false");
        }
    }
    public class Solution
    {
        public bool DivisorGame(int N)
        {
            return Play(0, N);
            
        }

        public bool Play (int turn, int N )
        {
            if (N == 2) // win
                return (turn == 0); // Alice
            for (int x = 1; x < N; x++)
            {
                if (N%x == 0)
                {
                    return Play(1 - turn, N - x);
                }
            }
            return (turn == 1); // Bob lost
        }
    }
}
