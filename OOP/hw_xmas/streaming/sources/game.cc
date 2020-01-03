#include "../headers/game.hh"

Game::Game(string title, string author, unsigned int price, unsigned int played_hours) 
    : Media(title, author, price),
      played_hours(played_hours) {};

unsigned int Game::getPlayedHours(){
    return this->played_hours;
}

unsigned int Game::getPrice(){
    return this->played_hours * this->price;
}