#include "csv_parsing.h"
#include "progress.h"

#include <iostream>
#include <string>
#include <fstream>

// CSLine: Extract items from a comma separated line into a vector "buff". 
// For more specific applications add some other functions...
// Constructor
CSLine::CSLine(std::string& line) {
    splitLine(line);
}
// Copy constructor
CSLine::CSLine(const CSLine& p1) {
    buff = p1.buff;            
}
void CSLine::splitLine(std::string& line) {
    // Splits the comma separated line to vector of tokens.
    std::string delim = ",";
    size_t start = 0;
    size_t end = line.find(delim);
    while (end != std::string::npos) {
        buff.push_back( line.substr(start,end-start) );
        start = end + delim.length();
        end = line.find(delim,start);
    }
    buff.push_back( line.substr(start,end));  // The final token
}



// CSVFile:
CSVFile::CSVFile(std::string& file_name){
    fs.open(file_name, std::ios::in);
    // Get the total filesize and go back to beginning
    fs.seekg(0,std::ios::end);
    filesize = double(fs.tellg());
    fs.seekg(0,std::ios::beg);
}

void CSVFile::Attach(Progress* tracker_) {
    tracker = tracker_;
}

void CSVFile::Notify() {
    if (tracker) tracker->update(input_state);
}

void CSVFile::Finalize() {
    if (tracker) tracker->finish();
}

void CSVFile::readLines() {
    std::string line;
    input_state = 0.;
    int i = 0; // for debugging
    skipLine();
    while (std::getline(fs,line) && i < 15000) {
        CSLine entry = getEntry(line); 
        processUnit(entry);     
        if(filterLine(line)) {    
            data.push_back(entry);  
        }
        input_state += line.size()/filesize;
        Notify();
        ++i;
    }
    // Finalize the indicator// Check that everything was succesfull
    Finalize();
}

bool CSVFile::filterLine(CSLine line) {
    // Implement this
    return true;
}

void CSVFile::skipLine() {
    // Implement this
}

void CSVFile::close() {
    fs.close();
}

void CSVFile::processUnit(const CSLine& entry) {
    // Implement this
}

CSLine CSVFile::getEntry(std::string& line) {
    CSLine entry(line);
    return entry;

}