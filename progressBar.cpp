#include "progressBar.h"

#include <iostream>
#include <string>

ProgressBar::ProgressBar(long maxVal){
  this->maxVal = maxVal;
  this->numBars = 25;
  this->increment = (float)maxVal/(float)numBars;
  this->prevVal = 0;
}

ProgressBar::~ProgressBar(){
  std::cout << std::endl;
}

void ProgressBar::UpdateProgress(long currVal){

  if(currVal-prevVal>(long)increment)
  {
    prevVal = currVal;

    if(currVal > maxVal) currVal = maxVal;

    float percent = (float)currVal/(float)maxVal;

    for(int i = 0; i < numBars; i++){
      if( (float)i*increment < (float)currVal){
        bar.replace(i,1,"|");
      }else{
        bar.replace(i,1," ");
      }
    }

    std::cout << "\r" "Mapping Shape: [";
    std::cout << "\033[32m";
    std::cout << bar;
    std::cout << "\033[0m";
    std::cout << "] ";
    std::cout.width( 3 );
    std::cout<< percent*100 << "%     " << std::flush;
  } else if (currVal >= maxVal) {

    for(int i = 0; i < numBars; i++){
      bar.replace(i,1,"|");
    }

    std::cout << "\r" "Mapping Shape: [";
    std::cout << "\033[32m";
    std::cout << bar;
    std::cout << "\033[0m";
    std::cout << "] ";
    std::cout.width( 3 );
    std::cout<< "100" << "%     " << std::flush;
  }
}
