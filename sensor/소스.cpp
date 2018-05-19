#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

struct list {
	list* Prev;
	list* Next;

	int blockLabel;
	int Distance;
	double Angle;
};

list* First;

void input();
void process();
void output();

int main()
{
	input();

	process();

	output();
}

void input()
{
	ifstream in;
	in.open("sensor3.txt");

	First = new list;
	First->Prev = NULL;
	list* p = First;

	int count = 0;

	// dummy data
	double x, y;

	while (!in.eof())
	{
		in >> p->Distance;
		in >> p->Angle;
		in >> x >> y;

		if (p->Prev != NULL && abs((p->Distance)-(p->Prev->Distance)) >=800)
		{
			count++;
		}
		p->blockLabel = count;

		p->Next = new list;
		p->Next->Prev = p;
		p = p->Next;
	}
	p = p->Prev;
	delete p->Next;
	p = p->Prev;
	delete p->Next;
	p->Next = NULL;
}

void process()
{
	list* p = First;

	bool Change = false;
	int Label;

	while (p != NULL)
	{
		if (Change)
		{
			if (p->blockLabel == Label)
				p->blockLabel = p->Prev->blockLabel;

			else
				Change = false;
		}

		if (p->Prev != NULL && p->Prev->blockLabel != p->blockLabel && !Change)
		{
			list* tmp = p;
			int count = 0;
			Label = p->blockLabel;

			while (tmp != NULL)
			{
				if (tmp->blockLabel == Label)
					count++;
				else
				{
					if (count < 5)
					{
						Change = true;
						p->blockLabel = p->Prev->blockLabel;
					}

					break;
				}

				tmp = tmp->Next;
			}
		}
		p = p->Next;
	}
}

void output()
{
	list* p = First;

	ofstream out;

	out.open("output.txt");

	out << p->Angle << " " << p->blockLabel << endl;
	cout << p->Angle << " " << p->blockLabel << endl;
	p = p->Next;

	while (p != NULL)
	{
		if (p->blockLabel != p->Prev->blockLabel)
		{
			out << p->Angle << " " << p->blockLabel << endl;
			cout << p->Angle << " " << p->blockLabel << endl;
		}
		p = p->Next;
	}
}