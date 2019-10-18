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
            Console.ReadKey();
            //string[] lines = System.IO.File.ReadAllLines(@".C:\Ella\LeetCode\Contest0413\input.txt");

            Solution sol = new Solution();
            int[] seq = new int[] { 20, 1, 15, 3, 10, 5, 8 };

            int answ = sol.LongestArithSeqLength(seq);
 
                Console.WriteLine("Answer: " + answ);
        }
    }
    public class Solution
    {
        public int[] A;
        public int LongestArithSeqLength(int[] A)
        {
            this.A = A;
            int maximum = 2;
            int len = A.Length;
            for (int i = 0; i < len-1; i++)
            {
                int first = A[i];
                for (int y=i+1; y<len; y++)
                {
                    int second = A[y];
                    int diff = first - second;
                    int maximal = 2 + Count(y, diff);
                    if (maximal > maximum)
                        maximum = maximal;
                }

            }
            return maximum;
        }
        public int Count(int start, int diff)
        {
            int first = A[start];
            for (int i = start + 1; i < A.Length; i++)
            {
                if (first - A[i] == diff)
                    return 1 + Count(i, diff);
            }
            return 0;
        }
    }

}
