#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <iostream>
#include <stdexcept>

class DuplicateItemException : public std::exception {
private:
    std::string message;
public:
    DuplicateItemException(const std::string& msg) : message(msg) {}
    const char* what() const throw();
};

class ItemNotFoundException : public std::exception {
private:
    std::string message;
public:
    ItemNotFoundException(const std::string& msg) : message(msg) {}
    const char* what() const throw();
};

#endif // EXCEPTIONS_H
