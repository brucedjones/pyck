#include "progressBar.h"

#include <iostream>
#include <string>

ProgressBar::ProgressBar(long maxVal, std::string label){
  this->maxVal = maxVal;
  this->numBars = 25;
  this->increment = (float)maxVal/(float)numBars;
  this->prevVal = 0;
  this->label = label;
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

    Draw((int)(percent*100.0));
  }

  if (currVal >= maxVal) {

    for(int i = 0; i < numBars; i++){
      bar.replace(i,1,"|");
    }

    Draw((int)(100));
  }
}

void ProgressBar::Finish()
{
  UpdateProgress(maxVal);
  std::cout << std::endl;
}

void ProgressBar::Draw(int percent)
{
  std::string labelOut = "\r" + label + ":";
  std::string barOut = "[\033[32m"+bar+"\033[0m] ";

  std::cout.width( 30 );
  std::cout << std::left << labelOut;
  std::cout.width(numBars+3);
  std::cout << std::left << barOut;
  std::cout.width( 3 );
  std::cout << std::left << percent << "%" << std::flush;
}
