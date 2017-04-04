#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>
#include <time.h>
#include <algorithm>
#include <math.h> //for round(), sqrt(), pow()
using namespace std;

int calcDist(vector<vector<int> > coords, int from, int to)
{
	int x1, x2, y1, y2;
	x1 = coords[from][1];
	y1 = coords[from][2];
	x2 = coords[to][1];
	y2 = coords[to][2];
	
	return round(sqrt(pow((x1 - x2), 2)+pow((y1 - y2), 2)));
}

vector<int> tsp(vector<vector<int> > coords, ofstream& outFile)
{
	
	clock_t start, end;
    float elapsed_time;
    start = clock();
    
	// Variables
	vector<int> visited;
	int dist, bestNear, curIdx, bestIdx, tempDist;
	bool found;
	
	bestNear = INT_MAX;
	dist = curIdx = bestIdx = 0;
	visited.push_back(coords[0][0]);
	
	// For every city besides the last
	for (int i = 0; i < coords.size() - 2; i++)
	{
		for (int j = 1; j < coords.size() - 1; j++)
		{
			found = false;
			
			// Check every visited node
			for (int x = 0; x < visited.size(); x++)
			{
				// If this one is visited -> mark to skip
				if (visited[x] == coords[j][0])
				{
					found = true;
					break;
				}
			}
			
			// If this one isn't visited
			if (!found)
			{
				tempDist = calcDist(coords, curIdx, j);
				
				// Update if the new best
				if (tempDist < bestNear)
				{
					bestNear = tempDist;
					bestIdx = j;
				}
			}
		}
		visited.push_back(coords[bestIdx][0]);
		dist += bestNear;
		bestNear = INT_MAX;
		curIdx = bestIdx;
	}
	
	dist += calcDist(coords, 0, curIdx);
	
	end = clock();
    elapsed_time = (float)(end - start) / (float)CLOCKS_PER_SEC;
    printf("%f\n", elapsed_time);
    
	outFile << dist << endl;
	
	return visited;
}

int main(int argc, char* argv[])
{   
	// Variables
	string inName, outName, num;
	vector<int> temp, visited;
	vector<vector<int> > coords;
	ifstream inFile;
	ofstream outFile;
	
	// Get file names
	if (argc != 2)
	{
		cout << "Invalid command line arguments." << endl;
		cout << "Input file name: ";
		cin >> inName;
	}
	else inName = argv[1];
	outName = inName + ".tour";
	
	// Until the end of the file
	inFile.open(inName.c_str());
	while (inFile)
	{
		// Read 3 numbers into a row
		for (int i = 0; i < 3; i++)
		{
			inFile >> num;
			temp.push_back(atoi(num.c_str()));
		}
		coords.push_back(temp);
		temp.clear();
	}
	
	outFile.open(outName.c_str());
	
	// Replace this with file output
	visited = tsp(coords, outFile);

	for (int i = 0; i < visited.size(); i++)
		outFile << visited[i] << endl;
	
	return 0;
}