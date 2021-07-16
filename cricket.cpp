#include <iostream>
#include "functions.h"
#include "class.h"

int main()
{
      int choice, cont = 1;

      while (cont)
      {
            system("clear");
            cout << "[1] Start Match     [2] Create team  [3]Previous match details\nEnter choice :  ";
            cin >> choice;

            if (choice == 1)
            {
                  matchSummary match;
                  match.startMatch();
                  match.summary();
                  storeMatchDetails(match);
                  cout << "\n\nPlay again [1]yes [0]No :";
                  cin >> cont;
            }
            else if (choice == 2)
            {
                  createTeam();
                  sleep(2);
                  system("clear");
            }
            else if (choice == 3)
            {
                  showPreviousMatchDetails();
            }
      }
      return 0;
}
