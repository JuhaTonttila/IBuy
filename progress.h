#ifndef PROGRESS_H
#define PROGRESS_H

#include <memory>

class IProgress{

    public:
        virtual ~IProgress(){};
        virtual void update(double frac) = 0;
        virtual void finish() = 0;
};

class ProgressStdout : public IProgress {

    public:
        void update(double frac) override;
        void finish() override;
};


class Progress {
    std::unique_ptr<IProgress> prg{};     
    public:
        void setProgress(std::unique_ptr<IProgress> prg_);
        void update(double frac);
        void finish();
};


#endif