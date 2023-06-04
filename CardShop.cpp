/*
Name: Hanz De Guzman
Project 5 
Finished by 3/31/23 due by 4/4/23
CardShop.cpp-CardShop Implementation
*/

#include "CardShop.hpp"
#include "DoublyLinkedList.hpp"
#include "Node.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>


/**
  @pre  : the input file is in csv format: "name,type,level_rank,race,attribute,atk,def"
  @param: the name of the input file
  @post:  Reads the input file and adds pointers to YGOCard objects 
          instantiated with the information read from the file. 
    */
CardShop::CardShop(std::string input_file_name) 
{
  std::ifstream fin(input_file_name);
  if (fin.fail())
  {
    std::cerr << "File cannot be opened for reading. \n";
    exit(1); // exit if failed to open the file
  }
  //we don't use the first line
  std::string ignore;
  getline(fin, ignore);

  //the columns of the csv associated with the data members
  std::string name, type, race, attribute;
  int level_rank, atk, def;

  std::string temp_string;
  int temp_int;
  int item_counter = 0;
  while (getline(fin, temp_string, ','))
  {
    name = temp_string;

    getline(fin, type, ',');
  
    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    level_rank = temp_int;

    getline(fin, race, ',');

    getline(fin, attribute, ',');

    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    atk = temp_int;

    getline(fin, temp_string);
    std::istringstream(temp_string) >> temp_int;
    def = temp_int;

    //create new card
    YGOCard *card_ptr = new YGOCard(name, type, level_rank, race, attribute, atk, def);

    //add to linked list and increment counter
    insert(item_counter++, card_ptr);
  }
}

//@post: removes all cards from the shop
//Deallocate and delete items
void CardShop::clear()
{
  for (int i = 0; i < item_count_; i++)
  {
    YGOCard *ptr = getItem(i);
    delete ptr;
    ptr = nullptr;
  }
  DoublyLinkedList::clear();
}

//destructor
CardShop::~CardShop()
{
  clear();
}

//@post: displays information of all cards in the shop, one per line
void CardShop::display()
{
  for (int i = 0; i < item_count_; i++)
  {
    getItem(i)->display();
  }
}

  //@param: the index of the first card to be displayed
  //@param: the index of the last card to be displayed
  //@post: displays the names of all cards in the shop with startRange and endRange, 
  //       inclusive, one per line
void CardShop::displayName(int startRange, int endRange)
{
  for (int i = startRange; i <= endRange; i++)
  {
    getItem(i)->displayName();
    if (i != endRange)
    {
      std::cout << ", ";
    }
    else
    {
      std::cout << std::endl;
    }
  }
}


//@return:  true if all the cards in rhs are equal to the cards in the shop, false otherwise
bool CardShop::operator==(const CardShop &rhs) const
{
  if (getLength() != rhs.getLength())
  {
    return false;
  }
  for (int i = 0; i < getLength(); i++)
  {
    if (*(getPointerTo(i)->getItem()) == *(rhs.getPointerTo(i)->getItem()))
    {
    }
    else
    {
      return false;
    }
  }
  return true;
}

/*
  @param: the comparator for ascending or descending sort.
  @param: the key to either sort by "atk" or "def"
  @post: bubble sort function. goes through the list and swaps the indexes and sorts by ascending or descending order.
  It also counts for the amount of swaps happening and returns it.
  */
template<typename Comparator>
int CardShop::bubbleSort(Comparator comp, std::string key) {
  int numOfSwap = 0;
  bool swapped = true;
  while(swapped){
    swapped = false;
    for(int j = 0; j < getLength() - 1; j++) {
      if(key == "atk"){
        if (comp(getItem(j+1)->getAtk(),getItem(j)->getAtk())) {
          swap(j, j+1);    
          swapped = true;
          numOfSwap++;
        }
      }
      else if(key == "def") {
        if(comp(getItem(j+1)->getDef(),getItem(j)->getDef())) {
          swap(j + 1, j);
          swapped = true;
          numOfSwap++;
        }
      }
    }
  }
  return numOfSwap;
}


/*
  @param: the comparator for ascending or descending sort.
  @param: the key to either sort by "atk" or "def"
  @post: insertion sort function. goes through the list and swaps the indexes and sorts by ascending or descending order.
  It also counts for the amount of swaps happening and returns it.
*/
template<typename Comparator>
int CardShop::insertionSort(Comparator comp, std::string key) {//swap(i, i-1) 
  int counter = 0;
  for(int i = 1; i < getLength(); i++) {
    int current = i;
    if(key == "atk") {
      while((current > 0) && comp(getPointerTo(current)->getItem()->getAtk(), getPointerTo(current-1)->getItem()->getAtk())){
        swap(current, current-1);
        current--;
        counter++;
      }
    }
    else if(key == "def") {
      while((current > 0) && comp(getPointerTo(current)->getItem()->getDef(), getPointerTo(current-1)->getItem()->getDef())){
        swap(current, current-1);
        current--;
        counter++;
      }
    }
  }
  return counter;
}

/*
  @param: the comparator for ascending or descending sort.
  @param: the key to either sort by "atk" or "def"
  @param: int left takes in the new left of the list.
  @param: int right takes in the new right of the list.
  @post: merge sort function. goes through the list and cuts the list in half, then swaps the indexes and sorts by ascending or descending order.
  It also counts for the amount of swaps happening and returns it.
*/
template<typename Comparator>
void CardShop::ambassinMergeSort(Comparator comp, int left, int right, std::string key, int &counter)  
{
    int middle;
    if (left < right)
    {
        middle = left + (right-left)/2;
        ambassinMergeSort(comp, left, middle, key, counter);
        ambassinMergeSort(comp, middle+1, right, key, counter);
        ambassinMerge(comp, left, middle, right, key, counter);
    }
}

/*
  @param: the comparator for ascending or descending sort.
  @param: the key to either sort by "atk" or "def"
  @param: int left takes in the new left of the list.
  @param: int right takes in the new right of the list.
  @param: int middle finds the middle of the list and splits it in the middle.
  @post: merge sort function. goes through the list and cuts the list in half, then swaps the indexes and sorts by ascending or descending order.
  It also counts for the amount of swaps happening and returns it.
*/
template<typename Comparator>
void CardShop::ambassinMerge(Comparator comp, int left, int middle, int right, std::string key, int &counter)
{
    std::vector<YGOCard*> leftVec;
    std::vector<YGOCard*> rightVec;
    if (key == "atk")
    {
        for (int i = 0; i < middle - left + 1; i++){
            leftVec.push_back(getPointerTo(left + i)->getItem());
        }
        for (int i = 0; i < right - middle; i++){
            rightVec.push_back(getPointerTo(middle + 1 + i)->getItem());
        }
        int itr = left;
        int leftIndex = 0; 
        int rightIndex = 0;
        while (leftIndex < leftVec.size() && rightIndex < rightVec.size())
        {
            if (comp(leftVec[leftIndex]->getAtk(), rightVec[rightIndex]->getAtk()))
            {
                getPointerTo(itr)->setItem(leftVec[leftIndex]);
                leftIndex++;
                
                
            }
            else
            {
                getPointerTo(itr)->setItem(rightVec[rightIndex]);
                rightIndex++;
                
            }
            itr++;
        }
        while (leftIndex < leftVec.size())
        {
            getPointerTo(itr)->setItem(leftVec[leftIndex]);
            leftIndex++;
            itr++;
            
        }
        while (rightIndex < rightVec.size())
        {
            getPointerTo(itr)->setItem(rightVec[rightIndex]);
            rightIndex++;
            itr++;
            
        }
        counter++;
    }
    else if (key == "def")
    {
        for (int i = 0; i < middle - left + 1; i++){
            leftVec.push_back(getPointerTo(left + i)->getItem());
        }
        for (int i = 0; i < right - middle; i++){
            rightVec.push_back(getPointerTo(middle + 1 + i)->getItem());
        }
        int itr = left;
        int leftIndex = 0; 
        int rightIndex = 0;
        while (leftIndex < leftVec.size() && rightIndex < rightVec.size())
        {
            if (comp(leftVec[leftIndex]->getDef(), rightVec[rightIndex]->getDef()))
            {
                getPointerTo(itr)->setItem(leftVec[leftIndex]);
                leftIndex++;
            }
            else
            {
                getPointerTo(itr)->setItem(rightVec[rightIndex]);
                rightIndex++;
            }
            itr++;
        }
        while (leftIndex < leftVec.size())
        {
            getPointerTo(itr)->setItem(leftVec[leftIndex]);
            leftIndex++;
            itr++;
        }
        while (rightIndex < rightVec.size())
        {
            getPointerTo(itr)->setItem(rightVec[rightIndex]);
            rightIndex++;
            itr++;
        }
        counter++;
    }
}




/*
  @param: the comparator for ascending or descending sort.
  @param: the key to either sort by "atk" or "def"
  @post: merge sort function. goes through the list and cuts the list in half, then swaps the indexes and sorts by ascending or descending order.
  It also counts for the amount of swaps happening and returns it.
*/
template<typename Comparator>
int CardShop::mergeSort(Comparator comp, std::string key) {
  int left = 0;
  int right = getLength() - 1;
  int counter = 0;
  ambassinMergeSort(comp, left, right, key, counter);
  return counter;
}

/*
  @param: the comparator for ascending or descending sort.
  @param: the key to either sort by "atk" or "def".
  @param: int x to keep track of your previous index.
  @param: int y to keep track of the current index.
  @post: partition function. goes through the list and swaps the indexes and sorts by ascending or descending order.
  It also counts for the amount of swaps happening and returns it.
*/
template<typename Comparator>
int CardShop::partition(Comparator comp, std::string key, int x, int y, int &counter) {
  Node<YGOCard*>* pivot = getPointerTo(y);
  int i = x - 1;

  for (int j = x; j <= y; j++) {
    if (key == "atk") {
      if (comp(getPointerTo(j)->getItem()->getAtk(), pivot->getItem()->getAtk())) {
        i++;
        swap(i, j);
        counter++;
      }
    }
    else {
      if (comp(getPointerTo(j)->getItem()->getDef(), pivot->getItem()->getDef()))  {
        i++;
        swap(i, j);
        counter++;
      }
    }
  }
  swap(i+1, y);
  counter++;
  return i+1;
}

/*
  @param: the comparator for ascending or descending sort.
  @param: the key to either sort by "atk" or "def".
  @param: int x to keep track of your previous index.
  @param: int y to keep track of the current index.
  @param: reference to a counter that counts the amount of swaps.
  @post: ambassin sort. goes through the list and swaps the indexes and sorts by ascending or descending order.
  It also counts for the amount of swaps happening and returns it.
*/
template<typename Comparator>
void CardShop::ambassinSort(Comparator comp, std::string key, int x, int y, int &counter) {
  if (x < y) {
    int pivot = partition(comp, key, x, y, counter);
    ambassinSort(comp, key, x, pivot - 1, counter);
    ambassinSort(comp, key, pivot + 1, y, counter);
  }
}

/*
  @param: the comparator for ascending or descending sort.
  @param: the key to either sort by "atk" or "def".
  @post: ambassin sort. goes through the list and swaps the indexes and sorts by ascending or descending order.
  It also counts for the amount of swaps happening and returns it.
*/
template<typename Comparator>
int CardShop::quickSort(Comparator comp, std::string key){
  int size = getLength() - 1;
  int counter = 0;
  ambassinSort(comp, key, 0, size, counter);
  return counter;
}