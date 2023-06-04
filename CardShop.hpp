/*
Name: Hanz De Guzman
Project 5 
Finished by 3/31/23 due by 4/4/23
CardShop.hpp-CardShop Interface
*/

#ifndef CARD_SHOP_HPP_
#define CARD_SHOP_HPP_
#include "DoublyLinkedList.hpp"
#include "YGOCard.hpp"
#include <iostream>
#include <fstream>
#include <sstream>


class CardShop : public DoublyLinkedList<YGOCard *>
{
public:
  CardShop() = default; //default constructor
  ~CardShop();          //destructor calls clear

  /**
  @pre  : the input file is in csv format: "name,type,level_rank,race,attribute,atk,def"
  @param: the name of the input file
  @post:  Reads the input file and adds pointers to YGOCard objects 
          instantiated with the information read from the file. 
    */
  CardShop(std::string input_file_name); //parameterized constructor

  //@post: displays information of all cards in the shop, one per line
  void display();

  //@param: the index of the first card to be displayed
  //@param: the index of the last card to be displayed
  //@post: displays the names of all cards in the shop with startRange and endRange, 
  //       inclusive, one per line
  void displayName(int startRange, int endRange);

  //@post: removes all cards from the shop
  void clear();                               

  //@return:  true if all the cards in rhs are equal to the cards in the shop, false otherwise
  bool operator==(const CardShop &rhs) const; 

  /*
  @param: the comparator for ascending or descending sort.
  @param: the key to either sort by "atk" or "def"
  @post: bubble sort function. goes through the list and swaps the indexes and sorts by ascending or descending order.
  It also counts for the amount of swaps happening and returns it.
  */
  template<typename Comparator>
  int bubbleSort(Comparator comp, std::string key);
  /*
  @param: the comparator for ascending or descending sort.
  @param: the key to either sort by "atk" or "def"
  @post: insertion sort function. goes through the list and swaps the indexes and sorts by ascending or descending order.
  It also counts for the amount of swaps happening and returns it.
  */
  template<typename Comparator>
  int insertionSort(Comparator comp, std::string key);

  /*
    @param: the comparator for ascending or descending sort.
    @param: the key to either sort by "atk" or "def"
    @param: int left takes in the new left of the list.
    @param: int right takes in the new right of the list.
    @post: merge sort function. goes through the list and cuts the list in half, then swaps the indexes and sorts by ascending or descending order.
    It also counts for the amount of swaps happening and returns it.
  */
  template<typename Comparator>
  void ambassinMergeSort(Comparator comp, int left, int right, std::string key, int &counter);

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
  void ambassinMerge(Comparator comp, int left, int middle, int right, std::string key, int &counter);

  /*
    @param: the comparator for ascending or descending sort.
    @param: the key to either sort by "atk" or "def"
    @post: merge sort function. goes through the list and cuts the list in half, then swaps the indexes and sorts by ascending or descending order.
    It also counts for the amount of swaps happening and returns it.
  */
  template<typename Comparator>
  int mergeSort(Comparator comp, std::string key);

  /*
    @param: the comparator for ascending or descending sort.
    @param: the key to either sort by "atk" or "def".
    @param: int x to keep track of your previous index.
    @param: int y to keep track of the current index.
    @post: partition function. goes through the list and swaps the indexes and sorts by ascending or descending order.
    It also counts for the amount of swaps happening and returns it.
  */
  template <typename Comparator>
  int partition(Comparator comp, std::string key, int low, int high, int &count);

/*
  @param: the comparator for ascending or descending sort.
  @param: the key to either sort by "atk" or "def".
  @post: ambassin sort. goes through the list and swaps the indexes and sorts by ascending or descending order.
  It also counts for the amount of swaps happening and returns it.
*/
  template<typename Comparator>
  int quickSort(Comparator comp, std::string key);

/*
  @param: the comparator for ascending or descending sort.
  @param: the key to either sort by "atk" or "def".
  @param: int x to keep track of your previous index.
  @param: int y to keep track of the current index.
  @post: ambassin sort. goes through the list and swaps the indexes and sorts by ascending or descending order.
  It also counts for the amount of swaps happening and returns it.
*/
  template<typename Comparator>
  void ambassinSort(Comparator comp, std::string key, int low, int high, int &count);

};

#endif