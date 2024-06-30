#pragma once
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

bool** populateTable(int vars)
{
	int cols = pow(2, vars);
	int x = cols, counter =0;
	bool check = true;
	bool** table = new bool* [vars];
	for (int i = 0; i < vars; i++)
	{
		table[i] = new bool[cols];
	}
	for (int i = 0; i < vars; i++)
	{
		x /= 2;
		counter = 0;
		check = true;
		for (int j = 0; j < cols; j++)
		{
			if (counter == x)
			{
				check = !check;
				counter = 0;
			}

			if (check == true)
			{
				table[i][j] = 1;
			}
			else {
				table[i][j] = 0;
			}
			counter++;
		}
	}
	return table;
}

int numOfClauses(string clauses)
{
	int NumOfClauses=0;
	int i = 0;
	bool check = false;
	while (clauses[i] != '\0')
	{
		if (clauses[i] == 41)
		{
			check = true;
		}
		if (check == true)
		{
			NumOfClauses++;
		}
	}
	return NumOfClauses;
}

int satisfiabilityProblem(string clause, bool** table, int numOfVars)
{
	int i = 0, j=0;
	char characters[5] = { 40,41,124,126,38 };
	bool check=true;
	char *vars =new char[numOfVars]; 
	
	while (clause[i] != '\0')
	{
		for (int i = 0; i < 5; i++)
		{
			if (clause[i] == characters[i])
			{
				check = false;
			}
			
		}
		for (int i = 0; i < numOfVars; j++)
		{
			if (clause[i] == vars[i])
			{
				check = false;
			}
		}
		if (check == true)
		{
			vars[j] = clause[i];
			j++;
		}
		i++;
	}
	int NumOfClauses = numOfClauses(clause);

	bool** clauses = new bool*[NumOfClauses];
	for (int i = 0; i < NumOfClauses; i++)
	{
		clauses[i] = new bool[pow(2, numOfVars)];
	}

	int counter = 0, index=0;
	bool AND = false, OR = false;
	bool flag = true,flag2=true, second= false;

	while (index < pow(2, numOfVars))
	{
		for (int i = 0; i < NumOfClauses; i++)
		{
			while (clause[counter] != ')')
			{
				if (second == true && OR == true)
				{
					for (int j = 0; j < numOfVars;j++)
					{

						if (clause[counter] == vars[j])
						{
							flag2 = table[i][index];
						}
						if (clause[counter - 1] == 126)
						{
							flag2 = !flag2;
						}
						if (AND == true)
						{
							flag = flag2 && flag;;
							AND = false;
						}
						else if (OR == true)
						{
							flag = flag || flag2;
							OR = false;
						}
					}
				}
				if (clause[counter] == '|')
				{
					OR = true;
				}
				else if (clause[counter] == '&')
				{
					AND = true;
				}
				for (int j = 0; j < numOfVars; j++)
				{

					if (clause[counter] == vars[j])
					{
						flag = table[i][index];
						second = true;
					}
					if (clause[counter - 1] == 126)
					{
						flag = !flag;
					}

				}
				counter++;
			}
			clauses[i][index] = flag;
			
		}
		index ++ ;
	}
	counter = 0;
	bool* finalClause = new bool[pow(2, numOfVars)];
	index = 0;
	while (index != pow(2, numOfVars))
	{
		flag = clauses[0][index];
		for (int i = 0; i < NumOfClauses; i++)
		{
			if (clause[counter + 1] == '&')
			{
				flag = flag && clauses[i+1][index] ;
			}
			if (clause[counter + 1] == '&')
			{
				flag = flag && clauses[i+1][index];
			}
		}
		finalClause[index] = flag;
		index++;
	}
	index = -1;

	for (int k = 0; k < pow(2, numOfVars); i++)
	{
		if (finalClause[k] == true)
		{
			index = k;
		}
	}
	return index;
}