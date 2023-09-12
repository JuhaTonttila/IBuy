#ifndef CSV_PARSING_H
#define CSV_PARSING_H

#include "progress.h"
#include <string>
#include <vector>
#include <fstream>

class CSLine {
    protected:
        void splitLine(std::string& line);
    public:
        std::vector<std::string> buff;
        CSLine(std::string & line);
        CSLine(const CSLine& p1);
        virtual ~CSLine() = default;
};

class CSVFile {
    protected:
        std::fstream fs;
        std::vector<CSLine> data;  // Container for the input data
        double filesize;
        double input_state;  // cumulative percentage of input data scanned
        Progress* tracker = nullptr;  // tracker class for displaying input progress

    public:
        CSVFile(std::string& file_name);                // Open file stream and get size etc.
 
        void Attach(Progress* tracker_);               // Attach a tracker to display input progress
        void Notify();                                  // Notify tracker for the input state
        void Finalize();                                // finalize the input tracking procedure

        void readLines();                               // Scan over the input CSV file
        void close();                                   // Close file stream

        // The following are not implemented for this base class. Write implementations for derived applications
        virtual void skipLine();                        // skip input lines
        virtual bool filterLine(CSLine line);     // filter data
        virtual void processUnit(const CSLine& entry);  // process data further
        virtual CSLine getEntry(std::string& line);     // For processing data

};


#endif