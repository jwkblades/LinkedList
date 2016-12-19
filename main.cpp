#include <iostream>
using namespace std;

#include "LinkedList.h"

int main(void)
{
	LinkedList<int> myList;

	for (int i = 0; i < 10; i++)
	{
		myList.append(i);
	}

	cout << endl << "Initial list: " << endl;
	for (int& myInt : myList)
	{
		cout << "List item: " << myInt << endl;
	}

	LinkedList<int>::iterator first = myList.begin();
	for (int i = 0; i < 3; i++, first++);

	LinkedList<int>::iterator second = first;
	for (int i = 0; i < 3; i++, second++);

	myList.erase(first, second);

	cout << endl << "After removing items: " << endl;
	for (int& myInt : myList)
	{
		cout << "List item: " << myInt << endl;
	}

	return 0;
}
