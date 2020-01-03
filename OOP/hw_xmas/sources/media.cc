#include "../headers/media.hh"

Media::Media(string title, string author, unsigned int price) 
    : title(title), author(author), price(price) {};

string Media::getTitle(){
    return this->title;
}

string Media::getAuthor(){
    return this->author;
}

unsigned int Media::getPrice(){
    return this->price;
}

void Media::raiseErrorNoSuchMedia(){
    throw this->ErrorNoSuchMedia();
}