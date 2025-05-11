#pragma once
#include <string>

class Analyzer {
public:
    explicit Analyzer(const std::string& filepath);
    void runAnalysis();
private:
    std::string m_filepath;
    void checkForGoto();
};
