#include "Analyzer.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>

Analyzer::Analyzer(const std::string& filepath) : m_filepath(filepath) {}

void Analyzer::runAnalysis() {
    checkForGoto();
}

void Analyzer::checkForGoto() {
    std::ifstream infile(m_filepath);
    std::string line;
    int line_number = 0;
    std::ofstream report("reports/report.txt");
    report << "Report for file: " << m_filepath << "\n";

    while (std::getline(infile, line)) {
        ++line_number;
        if (line.find("goto") != std::string::npos) {
            report << "Violation: 'goto' found at line " << line_number << "\n";
        }
    }

    report.close();
    std::cout << "Analysis complete. Report generated in 'reports/report.txt'.\n";
}
