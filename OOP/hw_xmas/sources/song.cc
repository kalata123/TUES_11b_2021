#include "../headers/song.hh"

Song::Song(string title, string author, unsigned int price, unsigned int times_listened) 
    : Media(title, author, price),
      times_listened(times_listened){};

unsigned int Song::getTimesListened(){
    return this->times_listened;
}

unsigned int Song::getPrice(){
    return this->times_listened * this->price;
}