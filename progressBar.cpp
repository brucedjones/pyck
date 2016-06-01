#include "progressBar.h"

#include <iostream>
#include <string>

ProgressBar::ProgressBar(long maxVal){
  this->maxVal = maxVal;
  this->numBars = 25;
  this->increment = (float)maxVal/(float)numBars;
}

void ProgressBar::UpdateProgress(long currVal){
  std::string bar;

  if(currVal > maxVal) currVal = maxVal;

  float percent = (float)currVal/(float)maxVal;

  for(int i = 0; i < numBars; i++){
    if( (float)i*increment < (float)currVal){
      bar.replace(i,1,"|");
    }else{
      bar.replace(i,1," ");
    }
  }

  std::cout<< "\r" "Mapping Shape: [" << bar << "] ";
  std::cout.width( 3 );
  std::cout<< percent*100 << "%     " << std::flush;
}
