#include <iostream>
#include "PQueue.h"
#include <map>
#include <vector>

using namespace std;

int main()
{

	PQueue a;
	cout<< "Test empty queue: " << a.pop() <<endl;
	cout<<endl;	

	cout<< "Test adding strings into queue: " << endl << endl;
	a.push(3, "string 3");
	a.push(1, "string 1");
	a.push(2, "string 2");
	a.push(-27, "string -27");
	a.push(144, "string 144");
	a.push(20, "string 20");
	a.push(1900, "string 1900");
	a.push(0, "string 0");

	cout<<endl;

	cout<<"Test popping from queue: " << endl;
	cout<<"Popping largest value from queue: " << a.pop() << endl << endl;

	cout<<"Attempt to change 'string 1' to be priority 13" << endl;
	a.changePriority("string 1",13);

	cout<<"Attempt to change 'string 1' to be priority -1" << endl;
	a.changePriority("string 1",-1);
	//a.changePriority("String that does not exist", 1);



}