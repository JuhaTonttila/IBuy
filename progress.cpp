
#include "progress.h"

#include <iostream>
#include <string>
#include <utility>
#include <memory>

void Progress::setProgress(std::unique_ptr<IProgress> prg_) {
    prg = std::move(prg_);
}
void Progress::update(double frac) {
    if (prg) prg->update(frac);
}
void Progress::finish() {
    if (prg) prg->finish();
}


void ProgressStdout::update(double frac) {
    size_t barWidth = 100;

    std::cout << "[";
    size_t current = barWidth * frac;
    std::cout << std::string(current,'|');
    std::cout << std::string(barWidth-current, ' ');
    std::cout << "] " << int(frac * 100.0) << " %\r";
    std::cout.flush();
}

void ProgressStdout::finish() {
    update(1.0);
    std::cout << "\n Done! \n\n" << std::endl;
}

