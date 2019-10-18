// ACM 3387 - Job Scheduling by Open Bidding
// Dec 2006

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;

ifstream inf;
ofstream outf;

struct Job
{
	int time;
	double cost;


	bool operator< (Job &y)
	{ 
		if (time < y.time)
			return true;
		else
			return false;
	}
};



vector<Job> job;
int ttl_time;

void Process(int n, int t)
{
	vector<Job> max_cost;
	int max_time = 0;
	int indx = 0;

	max_cost.resize(t, 0);
	max_cost[job[0]].cost = job[0].cost;
	max_cost[job[0]].time = job[0].time;
	max_cost[job[1]].cost = job[1].cost;
	max_cost[job[1]].time = job[1].time;

	int bck = 1; // last used index of the max_cost vector

    for (int i=1; i<n, i++) // from first to last item of the job vector
	{
		 currTime = job[i].time;
		 currCost = job[i].cost;

		for (int y=bck; y>=0; y--)
		{
			if (max_cost[y].time != 0)
			{

		int indx = 0;
		for (int y=0; y< i; y++)
		{
			indx = job[i].time + job[y].time;
			max_cost[indx] = max(max_cost[indx], job[i].cost + job[y].cost);
		}
	}


}

void main()
{

	int nopr = 0;// num of problem sets in file
	int n = 0; // number of jobs in each problem set
	inf.open("in.txt");
	assert(!inf.fail());
	outf.open("out.txt");
	
	inf >> nopr;
	for (int i=0; i<nopr; i++) //problems
	{
		inf >> n; //jobs
		job.resize(n);
		for (int y=0; y<n; y++)
			inf >> job[y].time >> job[y].cost;
		inf >> ttl_time;
		sort(job.begin(), job.end());

		//Process (n, ttl_time);
		
		
		for (int y=0; y<n; y++)
			cout << job[y].time << " " << job[y].cost << endl;
	}

	cout << endl << ttl_time;
}



