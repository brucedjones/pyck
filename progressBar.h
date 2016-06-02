#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <string>

class ProgressBar {
  public:
    ProgressBar(long maxVal);
    ~ProgressBar();
    void UpdateProgress(long currVal);
  private:
    long currVal;
    long prevVal;
    long numBars;
    long maxVal;
    float increment;
    std::string bar;
};

#endif
