#include "../headers/book.hh"

Book::Book(string title, string author, unsigned int price)
    : Media::Media(title, author, price) {};


unsigned int Book::getPrice(){
    return this->price;
}