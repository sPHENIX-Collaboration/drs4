#include <iostream>
#include "DRS.h"

using namespace std;

int main()
{

  DRSBoard *b;

  DRS *_drs  = new DRS();

  cout << "Number of boards: " <<  _drs->GetNumberOfBoards() << endl;

  for ( int i = 0; i < _drs->GetNumberOfBoards(); i++)
    {
      b = _drs->GetBoard(i);
      cout << " found DRS4 board with S/N " << b->GetBoardSerialNumber() << endl;
    }

  delete _drs;
  return 0;
}
