#include "../headers/movie.hh"

Movie::Movie(string title, string author, unsigned int price, unsigned int duration, unsigned int watched_minutes) 
    : Media(title, author, price),
      duration(duration),
      watched_minutes(watched_minutes) {};

unsigned int Movie::getDuration(){
    return this->duration;
}

unsigned int Movie::getWatchedTime(){
    return this->watched_minutes;
}

unsigned int Movie::getPrice(){
    return this->watched_minutes * this->price;
}