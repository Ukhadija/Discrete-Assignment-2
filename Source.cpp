#include "Header.h"


int main()
{
	
	int num;
	cout << "enter number of variables: ";
	cin >> num;
	string clauseF;
	cout << "enter clause or clause formula (use brackets to separate): ";
	cin >> clauseF;
	bool** values = populateTable(num);
	
		for (int j = 0; j < pow(2, num); j++)
		{
			cout << values[0][j]<<'\t';
			cout << values[1][j]<<'\t';
			cout << values[2][j]<<endl;
		}
	

	int col =satisfiabilityProblem(clauseF,values, num);

	return 0;
}