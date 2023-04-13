//********************************************************************
// ASU CSE310 Fall 2022 Assignment #7
// Name of Author:Atharva Gupta
// ASU ID:1222682656
// Description: //---- is where you should add your own code
//********************************************************************

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#ifndef ARRIVALCITYLIST_H_
#define ARRIVALCITYLIST_H_
//struct ArrCity represents an arrival city information with
//distance info. from a specific departure city
struct ArrCity
{
    string arrCityName;
    int distance;
    struct ArrCity* next;
};

//class ArrivalCityList is a linked list of ArrCity
//class ArrivalCityList will contains a linked list of ArrCity
class ArrivalCityList
{
    private:
        struct ArrCity* head;

    public:
        ArrivalCityList();
        ~ArrivalCityList();
        ArrCity* getHead();
        ArrCity* findArrCity(string oneCity);
        bool addArrCity(string oneCity, int distance);
        void printArrCityList();
};
ArrivalCityList::ArrivalCityList(){
    head = NULL;
}
ArrivalCityList::~ArrivalCityList(){
    //----
     int carCount  = 0;
	//add your own code
    struct ArrCity *temp;
    while(head != NULL){
        temp = head;
        carCount++;
        head = head->next;
        delete temp;
    }
    //----
    //cout<< "The number of deleted Car is: " << carCount ;
    //---

}
ArrCity* ArrivalCityList::getHead(){
    return head;
}
//*******************************************************************
//ArrCity* findArrCity(string oneCity);
//A function to find whether the parameterized city is inside the LinkedList or not.
//returns a pointer that points to the city if it exist, otherwise return NULL
ArrCity* ArrivalCityList::findArrCity(string oneCity){
    
    ArrCity* current = head;
    while(current!=NULL){
        if(current->arrCityName.compare(oneCity)==0){
            return current;
        }
        current = current->next;
    }
    return current;
}
//*******************************************************************
//bool addArrCity(string oneCity, int distance);
//Creates a new ArrCity and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of the ArrCities while inserting
//it into the list. Note: you cannot insert duplicated ArrCity
//Return value: true if it is successfully inserted and false in case of failures.
bool ArrivalCityList::addArrCity(string oneCity, int distance){
    
    
    if(findArrCity(oneCity)!=NULL){
        
        return false;
    }
    
    ArrCity* addCar = new ArrCity;
    addCar->arrCityName = oneCity;
    addCar->distance = distance;
   // cout<<"ADDING CAR : "<<oneCity<<endl;
    if(head == NULL){
       
        head = addCar;
        return true;

    }
    else if(head->arrCityName.compare(oneCity)>0){
      
        addCar->next = head;
        head = addCar;
        return true;
    }
    else{

    
    ArrCity* current  = head;
    ArrCity* prev = NULL;
    while (current !=NULL){
        if(current->arrCityName.compare(oneCity)>0){
            prev->next = addCar;
            addCar->next = current;
            return true;
        }
        prev = current;
        current = current->next;
        }
    
    prev->next = addCar;
    return true;
    }
    

    }

//According to above class definition, define all functions accordingly
void ArrivalCityList::printArrCityList()
{
  
   if(head == NULL)
   {
   	cout<<"Arrival city list is empty"<<endl;
   }
   else
   {
    
      ArrCity *temp = head;
      while(temp != NULL)
      {
         cout  
              << temp->arrCityName<<"("
              << temp->distance<<"),";
         temp = temp->next;
      }
      cout<<endl;
      
   }
}
//----
//----
#endif
