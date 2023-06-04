#include "DoublyLinkedList.hpp"
#include "CardShop.cpp"
#include "YGOCard.hpp"
//#include <string>
//#include <type_traits>
#include <iostream>

int main() {
    // std::cout << "TEST 1: TEST DEFAULT CONSTRUCTOR & ACCESSORS" << std::endl;

    // // Test default constructor
    // Book my_book;

    // // Test accessor functions
    // std::cout << my_book.getTitle() << std::endl;
    // std::cout << my_book.getAuthor() << std::endl;
    // std::cout << my_book.getPageCount() << std::endl;
    // std::cout << my_book.isDigital() << std::endl;


    // std::cout << "\nTEST 2: TEST PARAMETERIZED CONSTRUCTOR & ACCESSORS" << std::endl;

    // // Test parameterized constructor
    // Book my_book1("Harry Potter and the Chamber of Secrets", "J.K Rowling", 253, 1);
    // Book my_book2("Moby Dick", "Herman Melville", 378);
    
    // // Test accessor functions
    // std::cout << my_book1.getTitle() << " By " << my_book1.getAuthor() 
    //     << " with page count " << my_book1.getPageCount() << std::endl;
    // std::cout << "Digital: " << my_book1.isDigital() << std::endl;

    // std::cout << my_book2.getTitle() << " By " << my_book2.getAuthor() 
    //     << " with page count " << my_book2.getPageCount() << std::endl;
    // std::cout << "Digital: " << my_book2.isDigital() << std::endl;

    
    // std::cout << "\nTEST 3: TEST MUTATOR FUNCTIONS" << std::endl;

    // // Test mutator functions
    // Book my_book3("Moby Dick", "Herman Melville", 378);
    // my_book3.setTitle("50 shades of gray");
    // my_book3.setAuthor("E. L. James");
    // my_book3.setPageCount(514);
    // my_book3.setPageCount(-10);
    // my_book3.setDigital();

    // // Test accessor functions
    // std::cout << my_book3.getTitle() << " By " << my_book3.getAuthor() 
    //     << " with page count " << my_book3.getPageCount() << std::endl;
    // std::cout << "Digital: " << my_book3.isDigital() << std::endl;

    DoublyLinkedList<int> new_list;
    new_list.insert(0,1);
    new_list.insert(1,2);
    new_list.insert(2,3);
    new_list.insert(3,4);
    new_list.insert(4,5);
    new_list.swap(1,2);
    new_list.display();
    CardShop new_card("cards.csv");  
    //std::cout << new_card.bubbleSort(std::greater<int>{}, "atk") << std::endl;
    //std::cout << new_card.insertionSort(std::less<int>{}, "atk") << std::endl;
    //std::cout << new_card.bubbleSort(std::greater<int>{}, "def") << std::endl;
    //std::cout << new_card.bubbleSort(std::less<int>{}, "def") << std::endl;
    //std::cout << new_card.quickSort(std::less<int>{}, "atk") << std::endl;
    std::cout << new_card.mergeSort(std::less<int>{}, "def") << std::endl;

    // std::cout << new_card.insertionSort(std::less<int>{}, "atk") << std::endl;
    new_card.display();
    
}