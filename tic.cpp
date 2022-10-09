#include "toe.cpp"
#include <iostream>

int main ()
{
  Toe window;
  
  while (window.running() && !window.xWin && !window.oWin)
  {
    window.update();
    window.render(); 
  }
  
  if (window.xWin) std::cout << "X wins\n";
  else std::cout << "O wins\n";
}