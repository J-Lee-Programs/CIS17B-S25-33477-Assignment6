#include "exceptions.h"
#include <iostream>
#include <stdexcept>
const char* DuplicateItemException::what() const throw() { //Derived class of Exception
    return message.c_str(); //Return the input of constructor
}

const char* ItemNotFoundException::what() const throw(){
    return message.c_str();
}
