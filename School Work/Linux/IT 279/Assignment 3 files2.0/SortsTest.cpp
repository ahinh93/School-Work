#include "Sorts.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <time.h>
#include <cstdlib>

using namespace std;

int main(int argc,char *argv[])
{
	for(int q = 1; q < 2; q++)//1 to 11 for 100k to 1M
	{
		cout<<endl<<"----------------size of " << q*100<< "k----------------";
		for(int trial = 1; trial < 2; trial++)//1 to 4 for three trials
		{		 
			if (argc!=3)
		  { 
			cout <<"Please enter file name."<<endl;
			return -1;
		  }
		  double *array;
		  int length;

		 // if (strcmp(argv[1],"-o")==0)
		 // {
	
		//length = 700000;//onehundred thousand instead of 1mil
		length = q*100000;//q is constant
		array = new double[length];
		srand(time(NULL));
		for (int i=0;i<length;i++)
		  //array[i] =(double) (-50 + rand()%100)/2.5;    
			array[i] =(double) (rand()/900000);
		ofstream fout;
		fout.open(argv[2]);
		fout << length<<endl;
		for (int i=0;i<length;i++)
		  fout << array[i] << endl;
	
		fout.close();
	  //}
	 // else
	  //{
		fstream fin;

		fin.open(argv[2]);
		if (!fin.is_open())
		{
		  cout <<"Could not open file"<<endl;
		  return -1;
		}
	
		fin >>length;
		array = new double[length];
		for (int i=0;i<length;i++)
		  fin >> array[i];

		double time_taken=0;
		clock_t tinitial = clock();

		//if (strcmp(argv[1],"-i")==0)
			//Sorts::insertion_sort(array,1,length);
		//if (strcmp(argv[1],"-h")==0)
		//	Sorts::heapsort(array,length);
		//if (strcmp(argv[1],"-m")==0)
			//Sorts::mergesort(array,0,length);
		if (strcmp(argv[1],"-q")==0)
			Sorts::quickSort(array,0,length);

		clock_t tfinal = clock();
		time_taken = tfinal-tinitial;
	   
		time_taken = 1000.0*time_taken/CLOCKS_PER_SEC;

		for (int i=0;i<length;i++)
		{
		  cout <<array[i]<<"\t";
		}
		cout<<"\nTrial " << trial << ": ";
		cout <<"The sorting took an average of "<<time_taken<<" ms. ";

		//cout << endl;
	 // }
		delete []array;
		}
	}
	cout<<endl;
}
