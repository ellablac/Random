using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Contest0420
{
    class Problem1
    {
        static void Main(string[] args)
        {
            // The code provided will print ‘Hello World’ to the console.
            // Press Ctrl+F5 (or go to Debug > Start Without Debugging) to run your app.
            Console.WriteLine("Hello World!");
            Console.ReadKey();
            //string[] lines = System.IO.File.ReadAllLines(@".C:\Ella\LeetCode\Contest0413\input.txt");

            Solution sol = new Solution();

            int [][] answ = sol.AllCellsDistOrder(100, 100, 50, 50);

            Console.WriteLine("Answer: " + answ.ToString());
            for (int i=0; i<answ.Length; i++)
            {
                Console.WriteLine(answ[i][0] + "," + answ[i][1]);
            }
        }
    }

    public class Solution
    {
        public int[][] allCells;
        public int index = 0;
        public int[][] AllCellsDistOrder(int R, int C, int r0, int c0)
        {
            allCells = new int[R * C][];

            int[] firstCell = new int[] { r0, c0 };
            allCells[index] = firstCell;
            index++;
            if (R == 1 && C == 1) return allCells;

            int maxDist = Math.Max(r0, R - r0 - 1) + Math.Max(c0, C - c0 - 1);
            if(maxDist == 1)
            {
                AddCell(r0 + 1, c0, R, C);
                AddCell(r0 - 1, c0, R, C);
                AddCell(r0, c0 + 1, R, C);
                AddCell(r0, c0 - 1, R, C);

                return allCells;
            }

            int dist = 1;
            while (dist <= maxDist)
            {
                int r = dist, c = 0;

                // The first one is special case because c is 0.
                // Note: the distance is at least 1
                AddCell(r0 + r, c0, R, C);
                AddCell(r0 - r, c0, R, C);
                r--;
                c++;

                while (r > 0)
                {
                    AddCell(r0 + r, c0 + c, R, C);
                    AddCell(r0 + r, c0 - c, R, C);
                    AddCell(r0 - r, c0 + c, R, C);
                    AddCell(r0 - r, c0 - c, R, C);
                    r--;
                    c++;
                }

                // The last one is special case because r is 0.
                AddCell(r0, c0 + c, R, C);
                AddCell(r0, c0 - c, R, C);
                r--;
                c++;
                dist++;
            }
            return allCells;
        }
        public void AddCell(int r, int c, int R, int C)
        {
            if (r < R && c < C && r >= 0 && c >= 0)
            {
                int[] newCell = new int[] { r, c };
                allCells[index] = newCell;
                index++;
            }
        }
    }
}
