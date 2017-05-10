#include "PQueue.h"
#include <map>
#include <string>
#include <iostream>


using namespace std;
class T;
PQueue::PQueue()
{
	
}

PQueue::~PQueue()
{

}

//this method must place into queue
void PQueue::push(int priority, string item)
{
	if(priority < 1)
	{
		cout<<"Priority was less than 1," << priority << " will not be added." << endl;
	}
	else
	{
		myMap[priority] = item;
		cout<<priority << " was successfully added to the queue." << endl;
	}
}
	
//this method must return the next highest priority in queue
string PQueue::pop()
{
	//handle popping empty stack
	if(myMap.empty())
		{
			return "STACK_IS_EMPTY";
		}
	//stack has at least 1 element
	int currentNum = -1;
	int temp = 0;
	string toReturn;

	map<int,string>::iterator it;
	for(map<int,string>::iterator it = myMap.begin(); it!= myMap.end(); ++it)
	{	
		temp = it->first;

		if (temp > currentNum)
		{
			currentNum = temp;
		}
	}
	
	cout<<"Current largest number in queue is: " << currentNum<<endl;	
	toReturn = myMap[currentNum];

	cout<<"Now popping largest number of: " << currentNum << endl;

	myMap.erase(currentNum);

	int newLargeNum = -1;
	int holder = 0;


	for(map<int,string>::iterator it = myMap.begin(); it!= myMap.end(); ++it)
	{	
		holder = it->first;

		if (holder > newLargeNum)
		{
			newLargeNum = holder;
		}
	}

	cout<<"Largest number in queue is: " << newLargeNum << endl;

	return toReturn;

}

void PQueue::changePriority(string item, int new_p)
{
	if (new_p < 1)
	{
		cout<<"Error, priority change request is less than 1, please re-enter valid entry" << endl;
	}
	else
	{
		map<int,string>::iterator it;
		int oldPriority=0;
	
		cout<<"List of queue BEFORE priority change" << endl << endl<<"Priority, Item" << endl;

		for(map<int,string>::iterator it = myMap.begin(); it!= myMap.end(); ++it)
		{	
			cout<< it-> first << " , " << it->second << endl;
		}
	
		cout << "Priority being changed" << endl << endl;
		for(map<int,string>::iterator it = myMap.begin(); it!= myMap.end(); ++it)
		{	
			if (it->second == item)
			{
				int oldPriority = it->first;
				myMap.erase(oldPriority);
				myMap[new_p] = item;			
			}
		}

		cout<<"List of queue AFTER priority change" << endl << endl<<"Priority, Item" << endl;

		for(map<int,string>::iterator it = myMap.begin(); it!= myMap.end(); ++it)
		{	
			cout<< it-> first << " , " << it->second << endl;
		}

		cout<<endl;
	}
}

