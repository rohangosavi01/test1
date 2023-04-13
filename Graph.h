//********************************************************************
// ASU CSE310 Fall 2022 Assignment #7
// Name of Author: Atharva Gupta
// ASU ID: 1222682656
// Description: This is the header file that defines a weighted directed graph
//********************************************************************

//include necessary header file here
#include "MinPriorityQueue.h"
#include "ArrivalCityList.h"
//----

using namespace std;

class Graph
{
   private:
   int numOfNode;                 //number of nodes in the graph
   MinPriorityQueue* cityHeap;    //adjacency list of the graph, it is a min-heap
                                  //of departure city objects
   MinPriorityQueue* completedPath;
   public:
   Graph(int numOfNode, MinPriorityQueue* cityHeap);//
   ~Graph();//
   void printGraph();//
   void initialize_single_source(string sourceCityName);//
   void relax(DepCity u, DepCity v);//
   int findOneCity(string aCityName);//
   void dijkstra(string sourceCityName);//
   void printDijkstraPath(string sourceCityName);//
   void printPath(string sourceCityName, DepCity* aCity);//

   //add any auxiliary functions here in case you need them
   //----
};

//*******************************************************************
//Constructor
Graph::Graph(int numOfNode, MinPriorityQueue* cityHeap)
{
   this->numOfNode = numOfNode;
   this->cityHeap = cityHeap;
   completedPath = new MinPriorityQueue(numOfNode);
}

//*******************************************************************
//Destructor
Graph::~Graph()
{
   delete [] cityHeap;
   cityHeap = NULL;
   numOfNode = 0;
}

//*******************************************************************
//void printGraph();
//This function prints the graph. It traverse through the vertex list,
//then for each vertex, it print its adjacent list from head to tail.


//According to above class definition, define all functions accordingly
//----
//----
void Graph::printGraph(){
   cityHeap->printHeap();
   }


void Graph::initialize_single_source(string sourceCityName){

   int size = cityHeap->getSize();
   //initialising all nodes.
   for (int i = 0;i<size;i++){
      DepCity curr = cityHeap->getDepCityArr()[i];
      cityHeap->getDepCityArr()[i].d = 10000+i;
      cityHeap->getDepCityArr()[i].pi = NULL;
      DepCity newDvalue;
      if(curr.depCityName.compare(sourceCityName)==0){
         DepCity newDvalue;
         newDvalue.d = 0;
         cityHeap->decreaseKey(i,newDvalue);
      }
      
   }

}
void Graph::relax(DepCity u,DepCity v){
   int weight = u.arrCityList->findArrCity(v.depCityName)->distance;
   //cout<<"WEIGHT - "<< weight<<endl; 
   if(v.d>u.d+weight){
      DepCity newD;
      newD.d= u.d + weight;
      cityHeap->decreaseKey(findOneCity(v.depCityName),newD);
      cityHeap->getDepCityArr()[findOneCity(v.depCityName)].pi = &completedPath->getDepCityArr()[completedPath->isFound(u.depCityName)];
       
   }
}


int Graph::findOneCity(string aCityName){
   return cityHeap->isFound(aCityName);
}



void Graph::dijkstra(string sourceCityName){
   //cout<<"pre initialisation"<<endl;
   //printGraph();
   initialize_single_source(sourceCityName);
  // cout<<"post initialisation"<<endl;
   //printGraph();
   completedPath = new MinPriorityQueue(numOfNode);
   while (cityHeap->getSize()>0)
   {
      //cout<<"completed path"<<endl;
      //completedPath->printHeap();
      DepCity curr = cityHeap->getHeapMin(); // gets the minimum city distance
      cityHeap->extractHeapMin();            // removes the minimum city from the heap
      completedPath->insert(curr);           //adds completed path to a new min heap
      ArrCity *arrcity = curr.arrCityList->getHead(); // gets all the adjacent cities to the dep city
      //cout<<"relaxing for "<<curr.depCityName<<endl;
      while(arrcity!=NULL){
         if(findOneCity(arrcity->arrCityName)!=-1){
         DepCity adj= cityHeap->getDepCityArr()[findOneCity(arrcity->arrCityName)];        
         relax(curr,adj);
         }
         arrcity = arrcity->next;
      }          // removes the minimum city from the heap
   }
   

   cityHeap = completedPath;
  
}
void Graph::printPath(string sourceCityName, DepCity* aCity){
   string qu = "";
   while (aCity->depCityName.compare(sourceCityName)!=0){
      qu = "->"+aCity->depCityName+qu;
      aCity = aCity->pi;
   }
   qu = sourceCityName+qu;
   cout<<qu<<endl;
}

void Graph::printDijkstraPath(string sourceCityName){
   dijkstra(sourceCityName);
   //cityHeap->build_min_heap();
   cout<<"\n\nPrint the Dijkstra algorithm running result\n"<<endl;
   cout<<"Source City: "<<sourceCityName<<"\n"<<endl;
   cout << left;
   cout 
     << setw(14) << "Arrival City"
     << setw(15) << "Shortest Dist."
     << setw(15) << "Shortest Path"<<endl;
   for (int i = 0;i<numOfNode;i++){
      if(cityHeap->getDepCityArr()[i].d<10000){
     cout << left;
     cout 
     << setw(15) << cityHeap->getDepCityArr()[i].depCityName
     << setw(15) << cityHeap->getDepCityArr()[i].d;
     printPath(sourceCityName,&cityHeap->getDepCityArr()[i]);
      }else{
      cout << left;
     cout 
     << setw(15) << cityHeap->getDepCityArr()[i].depCityName
     << setw(15) << "None exist"
     <<setw(15)<<"None exist"<<endl;;
      }
   }

}
