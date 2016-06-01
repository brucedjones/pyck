#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

class ProgressBar {
  public:
    ProgressBar(long maxVal);
    ~ProgressBar(){};
    void UpdateProgress(long currVal);
  private:
    long currVal;
    long numBars;
    long maxVal;
    float increment;
};

#endif
