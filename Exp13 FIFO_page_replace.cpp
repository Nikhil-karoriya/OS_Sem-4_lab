#include<iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	vector<int> pageReferences = {1, 2, 3, 1, 4, 1, 3, 2, 4,
								  2};
	int numFrames = 3;
	vector<int> frames(numFrames, -1);

	unordered_map<int, int> frequency;
	for (int i = 0; i < pageReferences.size(); i++)
	{
		int page = pageReferences[i];
		if (find(frames.begin(), frames.end(), page) !=
			frames.end())
		{
			frequency[page]++;
		}
		else if (find(frames.begin(), frames.end(), -1) !=
				 frames.end())
		{
			int index = find(frames.begin(), frames.end(), -1) - frames.begin();
			frames[index] = page;
			frequency[page] = 1;
		}
		else
		{
			int maxFreq = 0;
			int evictPage;
			for (int j = 0; j < numFrames; j++)
			{
				if (frequency[frames[j]] > maxFreq)
				{
					maxFreq = frequency[frames[j]];
					evictPage = frames[j];
				}
			}
			int index = find(frames.begin(), frames.end(),
							 evictPage) -
						frames.begin();
			frames[index] = page;
			frequency.erase(evictPage);
			frequency[page] = 1;
		}
		cout << "Reference " << page << ": ";
		for (int j = 0; j < numFrames; j++)
		{
			cout << frames[j] << " ";
		}
		cout << endl;
	}
	return 0;
}