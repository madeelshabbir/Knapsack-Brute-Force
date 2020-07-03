#include<iostream>
using namespace std;
class LinkedSet
{
private:
	class SetNode
	{
	public:
		double data;
		SetNode *next;
		SetNode(double d)
		{
			data = d;
			next = NULL;
		}
	};

	SetNode *head;

public:
	LinkedSet()
	{
		head = NULL;
	}

	~LinkedSet()
	{
		SetNode *tmp = head;
		while (tmp != NULL)
		{
			SetNode *junk = tmp;
			tmp = tmp->next;
			delete junk;
		}
	}

	void append(double d)
	{
		if (head == NULL)
		{
			head = new SetNode(d);
			return;
		}

		SetNode *tmp = head;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new SetNode(d);
	}

	void display()
	{
		SetNode *tmp = head;
		cout << "{ ";
		while (tmp != NULL)
		{
			if (tmp->next == NULL)
				cout << tmp->data << " ";
			else
				cout << tmp->data << ", ";
			tmp = tmp->next;
		}
		cout << "}" << endl;
	}
};
namespace MaxProfit
{
	double knapSack(int n, double W, double *v, double *w)
	{
		bool *arr = new bool[n];
		double maxV = 0, tempV, tempW;
		for (int i = 0; i < pow(2, n); i++)
		{
			int j = n - 1;
			tempW = 0;
			tempV = 0;
			while (j >= 0 && arr[j] != 0)
				arr[j--] = 0;
			arr[j] = 1;
			for (j = 0; j < n; j++)
				if (arr[j] == 1)
				{
					tempV += v[j];
					tempW += w[j];
				}
			if (tempW <= W && tempV > maxV)
				maxV = tempV;
		}
		return maxV;
	}
}
namespace ProfitSet
{
	LinkedSet knapSack(int n, double W, double *v, double *w)
	{
		bool *arr = new bool[n];
		double maxW = 0, maxV = 0, tempV, tempW;
		for (bool b = 0; b <= 1; b++)
			for (int i = 0; i < pow(2, n); i++)
			{
				LinkedSet *l = NULL;
				if (b == 1)
					l = new LinkedSet;
				int j = n - 1;
				tempW = 0;
				tempV = 0;
				while (j >= 0 && arr[j] != 0)
					arr[j--] = 0;
				arr[j] = 1;
				for (j = 0; j < n; j++)
				{
					if (arr[j] == 1)
					{
						tempV += v[j];
						tempW += w[j];
						if (b == 1)
							l->append(j + 1);
					}
				}
				if (tempW <= W && tempV > maxV && b == 0)
				{
					maxV = tempV;
					maxW = tempW;
				}
				if (tempW == maxW && tempV == maxV && b == 1)
					return *l;
				if (b == 1)
					delete l;
			}
	}
}
int main()
{
	const int n = 9;
	double W = 15;
	double v[n] = { 2,3,3,4,4,5,7,8,8 };
	double w[n] = { 3,5,7,4,3,9,2,11,5 };
	cout << "Maximum Profit = " << MaxProfit::knapSack(n, W, v, w) << endl;
	cout << "Maximum Profit Set = ";
	ProfitSet::knapSack(n, W, v, w).display();
	system("pause");
	return 0;
}