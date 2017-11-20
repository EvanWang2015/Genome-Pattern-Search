/*
Burrows-Wheeler transform makes the input string Text well compressible, it also allows one to 
solve the pattern matching problem using the compressed strings instead of the initial string. 

Algorithm BWMatching counts the total number of matches of Patterns in Text.
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position 
//       of this character in the sorted array of 
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void PreprocessBWT(const string& bwt,
	map<char, int>& starts,
	map<char, vector<int> >& occ_count_before) {
	
	int n = bwt.size();
	map<char, int> count;
	map<char, int> ::iterator it;

	map<char, vector<int> > ::iterator itt;
	for (int i = 0; i < n; i++)
	{
		it = count.find(bwt[i]);
		if (it != count.end())
		{
			itt = occ_count_before.find(it->first);
			int j = i - itt->second.size();
			while (j >= 0)
			{
				itt->second.push_back(it->second);
				j--;
			}
			it->second++;
			itt->second.push_back(it->second);
		}
		else
		{
			count[bwt[i]] = 1;

			int j = i;
			while (j >=0)
			{
				occ_count_before[bwt[i]].push_back(0);
				j--;
			}
			occ_count_before[bwt[i]].push_back(1);
		}		
	}
	
	int i = 0;
	for (it = count.begin(); it != count.end(); it++)
	{
		starts[it->first] = i;
		i += it->second;
		itt = occ_count_before.find(it->first);
		int j = n - itt->second.size();
		while (j >= 0)
		{
			itt->second.push_back(it->second);
			j--;
		}
	}

}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences(const string& pattern,
	const string& bwt,
	const map<char, int>& starts,
	const map<char, vector<int> >& occ_count_before) {
	
	int top = 0; 
	int bottom = bwt.size() - 1;

	int n = pattern.size();
	char symbol;
	map<char, vector<int> > ::const_iterator itt;
	map<char, int>::const_iterator it;
	while (top <= bottom)
	{
		
		if (n > 0)
		{
			symbol = pattern[n - 1];
			if ((itt = occ_count_before.find(symbol)) != occ_count_before.end() && (it = starts.find(symbol))!=starts.end())
			{
				top = it->second + itt->second[top];
				bottom = it->second + itt->second[bottom + 1] - 1;
				//cout << "bottom: " << bottom << "top: " << top << endl;
			}
			else
				return 0;
		}
		else
		{
			//cout << "final-> bottom: " << bottom << "top: " << top << endl;
			return (bottom - top + 1);
		}
			
		n = n-1;		
	}

	return 0;
}

void matrix_output(map<char, int>& starts,
	map<char, vector<int> >& occ_count_before)
{
	map<char, int> ::iterator it;

	map<char, vector<int> > ::iterator itt;
	cout << "start: " << endl;
	for (it = starts.begin(); it != starts.end(); it++)
	{
		cout << it->first << " " << it->second << endl;
	}

	cout << "count matrix: " << endl;

	for (itt = occ_count_before.begin(); itt != occ_count_before.end(); itt++)
	{
		cout << itt->first << " ";
		for (int i = 0; i < itt->second.size(); i++)
			cout << itt->second[i] << " ";
		cout << endl;
	}
}

int main() {
	string bwt;
	cin >> bwt;
	int pattern_count;
	cin >> pattern_count;
	// Start of each character in the sorted list of characters of bwt,
	// see the description in the comment about function PreprocessBWT
	map<char, int> starts;
	// Occurrence counts for each character and each position in bwt,
	// see the description in the comment about function PreprocessBWT
	map<char, vector<int> > occ_count_before;
	// Preprocess the BWT once to get starts and occ_count_before.
	// For each pattern, we will then use these precomputed values and
	// spend only O(|pattern|) to find all occurrences of the pattern
	// in the text instead of O(|pattern| + |text|).
	PreprocessBWT(bwt, starts, occ_count_before);

	for (int pi = 0; pi < pattern_count; ++pi) {
		string pattern;
		cin >> pattern;
		int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
		//printf("%d ", occ_count);
		cout << occ_count << endl;
	}
	//printf("\n");

	//matrix_output(starts, occ_count_before);


	system("pause");
	return 0;
}

