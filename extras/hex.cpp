#include <iostream>
#include "colors.h" // Libreria de github https://github.com/Alfonzzoj/ColorsCCPP-Library

using namespace std;

int main () {
  cout << RED     <<BG_YELLOW << "This text is RED!      " << RESET << endl;
  cout << LGREEN  <<BG_CYAN   << "This text is LGREEN!   " << RESET << endl;
  cout << GREEN   <<BG_RED    << "This text is GREEN!    " << RESET << endl;
  cout << YELLOW  <<BG_GREEN  << "This text is YELLOW!   " << RESET << endl;
  cout << CYAN    <<BG_MAGENTA<< "This text is CYAN!     " << RESET << endl;
  cout << BLUE    <<BG_LGREEN << "This text is BLUE!     " << RESET << endl;
  cout << ORANGE  <<BG_BLUE   << "This text is ORANGE!   " << RESET << endl;
  cout << MAGENTA <<BG_ORANGE << "This text is MAGENTA!  " << RESET << endl;
 
  return 0;
}