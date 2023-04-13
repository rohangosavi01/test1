//********************************************************************
// ASU CSE310 Fall 2022 Assignment #7
// Name of Author: Atharva Gupta
// ASU ID:1222682656
// Description: implementation for the min priority queue.
//********************************************************************

//include necessary header file here
//----
#include "ArrivalCityList.h"
using namespace std;
#ifndef MINPRIORITYQUEUE_H_
#define MINPRIORITYQUEUE_H_
//represent each node of the graph which is a departure City
struct DepCity
{
    string depCityName;
    int d;
    struct DepCity* pi;
    ArrivalCityList* arrCityList;
};

//class MinPriorityQueue represents a Min-heap that contains DepCity objects.
//The key of each DepCity is its d value.
class MinPriorityQueue
{
    private:
        struct DepCity* depCityArr;	        //a DepCity array
        int capacity, size;

	public:
        MinPriorityQueue(int capacity);//
        ~MinPriorityQueue();//

        DepCity* getDepCityArr();//
        int getSize();//
		string getDepCityName(int index);
        int getCapacity();//
        int isFound(string oneDepCityName);//
        bool decreaseKey(int index, DepCity oneDepCityWithNewDValue);//
        bool insert(DepCity oneDepCity);//
        void heapify(int index);//
        DepCity getHeapMin();//
		void setParent(DepCity u, DepCity v);
        void extractHeapMin();//
        int leftChild(int parentIndex);//
        int rightChild(int parentIndex);//
        int parent(int childIndex);//
        void printHeap();
        void build_min_heap();
		void swap(int i,int j);
};


//*********************************************************

//Constructor to dynamically allocate memory for a heap with the specified capacity
MinPriorityQueue::MinPriorityQueue(int capacity)
{
    depCityArr= new DepCity[capacity];
	this->capacity = capacity;
	this->size = 0;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the heap.
//and prints the number of nodes deleted by it.
MinPriorityQueue::~MinPriorityQueue()
{
	int size1 = size;
	delete[] depCityArr;
	cout << "\nThe number of deleted cars is: " << size1 << endl;
}
DepCity* MinPriorityQueue::getDepCityArr(){
    return depCityArr;
}
int MinPriorityQueue:: parent (int childIndex){
	return (childIndex-1)/2;
}
int MinPriorityQueue:: leftChild (int parent){
	return parent*2+1;
}
int MinPriorityQueue:: rightChild (int parent){
	return parent*2+2;
}
int MinPriorityQueue:: getCapacity(){
	return capacity;
}
int MinPriorityQueue :: getSize(){
	return size;
}
//prone to error
DepCity MinPriorityQueue:: getHeapMin(){
	return depCityArr[0];
}
string MinPriorityQueue:: getDepCityName(int index){
	return depCityArr->depCityName;
}

void MinPriorityQueue::extractHeapMin(){

	depCityArr[0] = depCityArr[size-1]; //depCityArr[0] = &depCityArr[size];
	size--;
	heapify(0);
 }

bool MinPriorityQueue::insert(DepCity oneDepCity){
    if(isFound(oneDepCity.depCityName)!=-1){
		return false;
	}
	if(size>=capacity){
		cout << "\nReach the capacity limit, double the capacity now.\n";
		DepCity* newArray = new DepCity[2*capacity];
		for(int i =0;i<capacity;i++){
			newArray[i] = depCityArr[i];
		}
		DepCity *temp = depCityArr;
		depCityArr = newArray;
		delete[] temp;
		capacity = 2*capacity;
		//cout<<"The new capacity now is "<<capacity<<"\n";
	}
	DepCity newD;
	newD.d =30000;
	newD.arrCityList = oneDepCity.arrCityList;
	newD.pi = oneDepCity.pi;
	newD.depCityName = oneDepCity.depCityName;
	depCityArr[size] = newD;
	size++;

	bool success = decreaseKey(size-1,oneDepCity);
	
	return true;


}
bool MinPriorityQueue::decreaseKey(int index, DepCity oneDepCityWithNewDValue){
    if (index>size||depCityArr[index].d<oneDepCityWithNewDValue.d)
    {
        return false;
    }
	depCityArr[index].d= oneDepCityWithNewDValue.d;
	while (index>0&& depCityArr[parent(index)].d>depCityArr[index].d){
		DepCity temp = depCityArr[index];
		depCityArr[index]=depCityArr[parent(index)];
		depCityArr[parent(index)] = temp; //swap parent and child;
		index = parent(index);

	}
	return true;

}
int MinPriorityQueue:: isFound(string oneDepCityName  ){
	int index = 0;
	while(index<size){
		if(depCityArr[index].depCityName.compare(oneDepCityName)==0){
		return index;
			}
		index++;
		
		}
	return -1;
	}
void MinPriorityQueue:: heapify(int index){
	int shorty = index;
	if(leftChild(index)<size && depCityArr[leftChild(index)].d<depCityArr[shorty].d){
		shorty = leftChild(index);
	}
	if(rightChild(index)<size && depCityArr[rightChild(index)].d<depCityArr[shorty].d){
		shorty = rightChild(index);
	}
	if(shorty!=index){
		DepCity temp  = depCityArr[index];
		depCityArr[index] = depCityArr[shorty];
		depCityArr[shorty] = temp;
		heapify(shorty);
	}

}
/*
void MinPriorityQueue:: printHeap(){
	if(size ==0){
		cout<< "Empty heap, no elements\n";
	}
	cout<<"\nHeap capacity = "<<capacity<<endl;
	cout<<"\nHeap size = "<<size<<endl;
	DepCity oneCity;
	for (int i =0; i<size;i++){
		oneCity = depCityArr[i];
		cout << left;
		cout << setw(8) << oneCity.d
			<< setw(12) << oneCity.depCityName;
		if(oneCity.pi==NULL){
            cout<< "No parent";
        }
        else{
            cout<< setw(12) << oneCity.pi->depCityName;
        }
        oneCity.arrCityList->printArrCityList();
        cout<<endl;

	}
}
*/
void MinPriorityQueue::build_min_heap(){
	for (int i= size/2;i>=0;i--){
		heapify(i);
	}
}

//According to above class definition, define all other functions accordingly

void MinPriorityQueue::printHeap(){

	if(size ==0){
		cout<< "Empty heap, no elements\n";
	}
	else{
	cout<<"Heap size = "<<size<<"\n"<<endl;
	   cout << left;
   cout << setw(15) << "Dep. City"
     << setw(12) << "d Value"
     << setw(15) << "PI"
     << "Arrival City List" << endl;
    for (int i = 0;i<size;i++){
     cout << left;
     cout 
     << setw(15) << depCityArr[i].depCityName
     << setw(12) << depCityArr[i].d;
	 if(depCityArr[i].pi!=NULL){
     cout<< setw(15) << depCityArr[i].pi->depCityName;
	 }
	 else{
		cout<<setw(15) << "No Parent";
	 }
     depCityArr[i].arrCityList->printArrCityList();
}
}
}
void MinPriorityQueue::swap(int i, int j){
	DepCity temp = depCityArr[i];
	depCityArr[i] = depCityArr[j];
	depCityArr[j] = temp;
}
//----
//----
#endif
