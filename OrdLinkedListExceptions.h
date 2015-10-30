#include <iostream>
#include <exception>

using namespace std;

class OrdLinkedListOutOfBoundsException: public exception
{
  virtual const char* what() const throw(){
    return "OrdLinkedListOutOfBoundsException thrown";
  }
};
