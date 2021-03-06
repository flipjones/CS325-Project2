#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string> 
#include <ctime> 
#include <limits>

using namespace std;

void print_array(vector<int> print_array, int count, ofstream * outputFile)
{
	*outputFile << "[";
	for (int i = 0; i < print_array.size(); i++) {

		*outputFile << print_array[i];

		if (i != (print_array.size() - 1))
			*outputFile << ", ";
	}

	*outputFile << "]" << endl;

	*outputFile << count << endl;
}


vector< vector <int> > parse_input(vector<string> input_strings) {

	vector< vector<int> > input_arrays;

	string tmp_string;

	int tmp_int;

	vector<int> tmp_vector;

	int u = 0;
	int v = 0;

	for (u = 0; u < input_strings.size(); u++)
	{
		for (v = 0; v < input_strings[u].length(); v++)
		{
			if ((input_strings[u][v] == '[') || (input_strings[u][v] == ' '))
			{
				// Do nothing
			}
			else if ((isdigit(input_strings[u][v])) || (input_strings[u][v] == '-'))
			{
				tmp_string.push_back(input_strings[u][v]);
			}
			else if ((input_strings[u][v] == ',') || (input_strings[u][v] == ']'))
			{
				tmp_vector.push_back(atoi(tmp_string.c_str()));
				tmp_string = "";
			}

			if ((v == (input_strings[u].length() - 1)) && (input_strings[u][0] != '['))
			{
				tmp_vector.push_back(atoi(tmp_string.c_str()));
				tmp_string = "";
			}
		}

		input_arrays.push_back(tmp_vector);
		tmp_vector.clear();
		tmp_string = "";
	}

	return input_arrays;
}

int vectContSum(vector<int> vect)
{
	int count = 0;

	for (int i = 0; i < vect.size(); i++)
	{
		count += vect[i];
	}

	return count;
}

void changedp(vector<int> V, int A, vector<int> &change)
{
	vector< vector<int> > solutions;
	vector<int> retValue;

	vector<int> zeroSolution(V.size(), 0);
	solutions.push_back(zeroSolution);

	for (int i = 1; i <= A; i++)
	{
		vector<int> tempchange(V.size(), 0);
		int count = A;
		int j = 0;

		while (j < V.size() && V[j] <= i)
		{
			vector<int> tempChange(V.size(), 0);
			int tempCount = A;

			tempChange = solutions[i - V[j]];
			tempChange[j]++; 
			tempCount = vectContSum(tempChange);

			if (tempCount <= count)
			{
				retValue = tempChange;
				count = tempCount;
			}

			j++;
		}

		solutions.push_back(retValue);
	}

	change = solutions[A];

}

int main(int argc, char *argv[]) {

	if (argc != 2)
	{
		cout << "Usage: " << argv[0] << "[filename].txt" << endl;
		return 1;
	}
	
	clock_t t1, t2;
	double runtime;
	
	vector< vector<int> > input_arrays;
	
	vector<string> problem_set;
	
	string input_string;

	ifstream problems(argv[1], ifstream::in);

	while (problems.good()) {
		getline(problems, input_string);
		if (input_string.length() != 0) {
			problem_set.push_back(input_string);
		}
	}

	problems.close();

	input_arrays = parse_input(problem_set);

	string fileName = argv[1];
	int index = fileName.find_last_of(".");

	string outputFileName = fileName.substr(0, index) + "change.txt";

	ofstream fileOutput;
	fileOutput.open(outputFileName.c_str(), ofstream::out);

	for (int i = 0; i < input_arrays.size(); i++)
	{
		int sum = i + 1;
		vector<int> change(input_arrays[i].size(), 0);

		t1 = clock();

		changedp(input_arrays[i], input_arrays[sum][0], change);

		t2 = clock();
		runtime = (t2 - t1) / (double)CLOCKS_PER_SEC;

		cout << "The algorithm for change amount " << input_arrays[sum][0] << " ran in ";
		cout << runtime << " seconds." << endl << endl;

		int count = vectContSum(change);

		print_array(change, count, &fileOutput);

		change.clear();

		i++;
	}

	fileOutput.close();

	return 0;
}