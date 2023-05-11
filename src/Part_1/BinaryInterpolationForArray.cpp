#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include "csvExtractor.h"

using namespace std;


  int date_to_int(string date, char del)       // function that takes the dates as string and outputs the "reversed" int (helps with comparisons later)
  {
      stringstream ss(date);
      string word;

      vector <int> Date;

      while (!ss.eof()) {
        for(int i=0; i<3; i++)
        {
              getline(ss, word, del);
              Date.push_back(stoi(word));

        }

        return (10000 * Date[2] + 100 * Date[1] + Date[0]);           //here the date is output as a "reversed" integer.


      }
  }



int binary_interpolation(int numsarray[], int left, int right, int key){


    int next;

    int size = right-left+1;
    next = (int)round((double)(size*(key - numsarray[left]) / (numsarray[right] - numsarray[left]))) + 1;

    while(key != numsarray[next])
    {
        int size = right-left+1;
        int i=0;
        if(size<=3)
        {
            cout << "Direct Search." <<endl;

        }
        if(key >= numsarray[next])
        {
          while(key > numsarray[next + i * (int)round((double)(sqrt(size) - 1))])
          {
                  i = i+1;
          }
          right = next + i * round((double)sqrt(size));
          left = next + (i-1) * round((double)sqrt(size));

        }
        else if(key < numsarray[next])
        {

          while(key < numsarray[next - i * (int)round((double)sqrt(size)) + 1])
          {
            i = i+1;
          }
          right = next - (i-1) * round((double)sqrt(size));
          left = next - i * round((double)sqrt(size));
        }

        next = left + round((double)((right-left+1) * (key - numsarray[left])  / (numsarray[right] - numsarray[left])));

      }
      if(key == numsarray[next])
          return next;

      else return -1;

}





int main()
{
    int key;
    int numsarray[] = {100, 101, 102, 103, 104, 132, 150, 157, 234, 235, 236};
    cout << "Enter key value: " << endl;
    cin >> key;
    int index = binary_interpolation(numsarray, 0, (sizeof(numsarray) / sizeof(int)) - 1, key);
    cout << "The index of the element is: " << index;

    return 0;
}
