#include "../headers/salmon.hh"
#include "iostream"

bool Salmon::tasty(){
    return getAge() <= 1;
}