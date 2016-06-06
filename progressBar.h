#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <string>

class ProgressBar {
  public:
    /**
     * ProgressBar Constructor
     * @param maxVal The value (Which would be passed to UpdateProgress) which indicates completion
     * @param label Label to be printed with the progress bar
     */
    ProgressBar(long maxVal, std::string label);
    ~ProgressBar(){};

    /**
     * Updates the progress bard
     * @param currVal Current progress value
     */
    void UpdateProgress(long currVal);

    /**
     * Finalizes the progressBar, does a final draw at 100% and flushes cout
     */
    void Finish();
  private:

    /**
     * Handles output for the progressBar
     * @param percent The current percentage value to display
     */
    void Draw(int percent);

    long currVal; /**< Current progress value */
    long prevVal; /**< Previous progress value */
    long numBars; /**< Number of progress bars to use */
    long maxVal; /**< Maximum progress value */
    float increment; /**< Progress represented by a single bar */
    std::string bar; /**< String containing the progress bar for output */
    std::string label; /**< String containing the label to be output with the progress bar */
};

#endif
