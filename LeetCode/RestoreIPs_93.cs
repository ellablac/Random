using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RestoreIPs_93
{
    class Program
    {
        static void Main(string[] args)
        {
            // The code provided will print ‘Hello World’ to the console.
            // Press Ctrl+F5 (or go to Debug > Start Without Debugging) to run your app.
            Console.WriteLine("Hello World!");
            Console.ReadKey();

            Solution sol = new Solution();

            IList<string> ipList = sol.RestoreIpAddresses("25525511135");
            foreach (string ip in ipList)
                Console.WriteLine(ip);
        }
    }

    public class Solution
    {
        private IList<string> ips = new List<string>();
        private string s = null;
        public IList<string> RestoreIpAddresses(string s)
        {
            this.s = s;
            int[] indx = new int[3] {-1, -1, -1 }; // array of indxes of indexes representing
                                     // locations of each dot (index of a digit
                                     // followed by a dot)
            GenerateIps(0, 0, indx);
            return ips;

        }

        public void GenerateIps(int start, int group, int[] ix)
        {
            int left = s.Length - start;

            // can't have more than 3 digits per group
            if (left > (4 - group) * 3)
                return;

            // If we are on the last group, and it is a valid group,
            // then generate the dot-delimeted IP address,
            // and append it to the list of all valid IPs
            // Otherwise, return to the previous recursion level
            if (group == 3)
            {
                if (left > 3 || left < 1 || !IsValidGroup(s.Substring(start, left)) )
                    return;

                UpdateIPs(ix);
                return;
                
            }
            for (int i=0; i<3; i++)
            {
                // check if enough digits remain
                if (s.Length - start - i < 4 - group)
                    return;
                // check if the group of digits is valid
                if (!IsValidGroup(s.Substring(start, i + 1)))
                    return;
                // recursive call
                ix[group] = start + i;
                GenerateIps(start + i + 1, group + 1, ix);

            }
        }

        private bool IsValidGroup(string group)
        {
            if (group == "0")
                return true;
            if (group.Substring(0, 1) == "0")
                return false;
            if (!int.TryParse(group, out int numValue))
                return false;
            if (numValue < 1 || numValue > 255)
                return false;

            return true;
        }

        // Given an array of indexes of periods
        // in the IP address, places the periods
        // in appropriate locations, and adds the
        // resulting IP to the list of valid IPs.
        private void UpdateIPs(int[] ix)
        {
            string validIP = string.Empty;
            int first = 0;
            for (int i = 0; i<3; i++)
            {
                validIP += s.Substring(first, ix[i] - first + 1);
                validIP += ".";
                first = ix[i] + 1;
                s.f
            }
            validIP += s.Substring(first, s.Length - first);

            ips.Add(validIP);
        }
    }
}