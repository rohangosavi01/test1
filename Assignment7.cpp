//********************************************************************
// ASU CSE310 Fall 2022 Assignment #7
// Name:Atharva Gupta
// ASU ID:1222682656
// Description: //---- is where you should add your own code
//********************************************************************

//include necessary header file here
#include "MinPriorityQueue.h"
#include "ArrivalCityList.h"
#include "Graph.h"
//----

using namespace std;

void getCityInfo(string oneLine, string& depCityName, ArrivalCityList* arrCityList);
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, int& distance);     //**optional

int main()
{
   int count;       //a variable for number of nodes
   string oneLine, sourceCityName;
   string answer = "yes";       //a variable to decide whether to run Dijkstra multiple times
   string depCityName;
   ArrivalCityList *array;

   //cout << "Enter number of cities: ";
   cin >> count;
   cin.ignore(20, '\n');

   //For each line of the file, we will create an ArrivalCityList(which is a linked list)
   //for a specific departure city. It represents all its reachable arrival cities with distance info.
   //Here we use an array of DepCity to store them
   DepCity* depCityArr = new DepCity[count];

   //Initialize depCityArr. Set each node's d value to be very large 30000
   //initialize each arrival city list
   for(int i = 0; i< count; i++)
   {
      depCityArr[i].d = 10000+i;
      depCityArr[i].arrCityList = new ArrivalCityList();
      //----
      //----
   }

   //get input line by line and create the depCityArr
   for(int i = 0; i<count; i++)
   {
        
         getline(cin, oneLine);
         string delimiter = ",";

         int pos=oneLine.find(delimiter);
         string token = oneLine.substr(0,pos);
         depCityName = token;
         depCityArr[i].depCityName = depCityName;
         oneLine.erase(0, pos+delimiter.length());
         
         while(oneLine.length()>1){
         pos=oneLine.find("(");
         string name = oneLine.substr(0,pos);
         oneLine.erase(0, pos+1);
         pos=oneLine.find(",");
         token = oneLine.substr(0,pos-1);
         int dist = stoi(token);
         //cout<<dist<<endl;
         oneLine.erase(0, pos+1);
         depCityArr[i].arrCityList->addArrCity(name,dist);
         }
        
   }

  //create a Graph object
  MinPriorityQueue *list = new MinPriorityQueue(count);

  for (int i=0;i<count; i++){
      list->insert(depCityArr[i]);
  }
   Graph *path = new Graph(count,list);
  //----

   //print the graph adjacency list before running Dijkstra algorithm
   cout << "\nPrint the graph adjacency list before running Dijkstra algorithm\n" << endl;
  //----
   path->printGraph();
   //Next you need to design a sentinel value controlled while loop base on answer
   //If user answer is 'yes', get source city name, run Dijkstra algorithm, print
   //shortest path, then ask whether user want to continue or not...


do
{

   cout<<"\nEnter source city name: "<<endl;
   getline(cin, sourceCityName);

   if(path->findOneCity(sourceCityName)>=0){
   path->printDijkstraPath(sourceCityName);

   }
   else{
      cout<<sourceCityName<<" does NOT exist"<<endl;
   }
   cout<<"\nFind shortest path for another departure city(yes or no): "<<endl;
   getline(cin, answer);
   
} while (answer.compare("yes")==0);
cout<<"\nProgram terminate"<<endl;
}
//************************************************************************
//Give one line in input file, this function extract tokens and get departure city
//name and its arrival cities info.
void getCityInfo(string oneLine, string& depCityName, ArrivalCityList* arrCityList)
{
 
          string delimiter = ",";

         int pos=oneLine.find(delimiter);
         string token = oneLine.substr(0,pos);
         depCityName = token;
         cout<< depCityName<<endl;
         oneLine.erase(0, pos+delimiter.length());

         while(oneLine.length()>1){
         pos=oneLine.find("(");
         string name = oneLine.substr(0,pos);
         cout<<name<<endl;
         oneLine.erase(0, pos+1);
         pos=oneLine.find(")");
         token = oneLine.substr(0,pos);
         int dist = stoi(token);
         cout<<dist<<endl;
         oneLine.erase(0, pos+2);
         
         }
}
