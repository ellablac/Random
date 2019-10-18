#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>
using namespace std;

ifstream inf;
ofstream outf;
vector<int> v;
vector <int> v1D;
vector<vector<int> > v2D;
int total_cost;

int find(int a)
{
	if (v[a] == -1)
		return a;
	else
	{
		v[a] = find(v[a]); // path compression
		return v[a];
	}
}

void unionpath(int a, int b)
{
	int roota = find(a);
	int rootb = find(b);
	if (roota != rootb)
	{
		v[rootb] = roota; // union (a,b)
		total_cost += v2D[a][b];
	}
}

void main()
{
	inf.open ("jungle.in");
	assert (!inf.fail());
	outf.open("jungle.out");

	int nol; // number of lines;
	char tag_from; // letter representing village
	char tag_to;
	int nop; // num of paths for each village
	int cost; // cost of the road



	inf >> nol;

	while (nol != 0) //for each problem
	{
		v1D.clear();
		v2D.clear();
		for (int x=0; x<nol; x++)
		{
			for (int k=0; k<nol; k++)
				//arr[x][k] = -1; // init array
				v1D.push_back(-1);
			v2D.push_back(v1D);
		}
		total_cost = 0;
		v.clear();
		for (int x=0; x<nol; x++) v.push_back(-1);


		for (int i = 0; i < nol-1; i++) // for each line
		{


				inf >> tag_from;
				inf >> nop;

			for (int y=0; y<nop; y++) // for each path
			{
				inf >> tag_to;
				inf >> cost;
				v2D[int(tag_from - 65)][int(tag_to - 65)] = cost;
			}


		}
		cout << endl;
		for (int x=0; x<nol; x++)
		{
			cout << endl;
			for (int k=0; k<nol; k++)
				cout << v2D[x][k]; // print array
		}

		for (int z = 1; z < 100; z++) // just go up instead of sorting
		{
			for (int x=0; x<nol; x++)
			{
				for (int k=x+1; k<nol; k++)
					if (v2D[x][k] == z) 
					{
						unionpath (x, k);
					}
			}
		}

		cout << endl;
		for (int x=0; x<nol; x++)
		{
			cout << endl;
			for (int k=0; k<nol; k++)
				cout << v2D[x][k] << " "; // print array
		}

		cout << endl;
		for (int x=0; x<nol; x++)
			cout << v[x];

		cout << endl << "total cost: " << total_cost;

		inf >> nol;

	}	
}