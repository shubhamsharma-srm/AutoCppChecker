#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include "rulebase/RuleBase.hpp"


namespace fs = std::filesystem;

std::string readFile(const std::string& path) {
    std::ifstream in(path);
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

int main() {
    std::vector<std::shared_ptr<RuleBase>> rules;
    try {
        rules = loadRulesFromJson("../../rulebase/Rules.json");
    } catch (const std::exception& e) {
        std::cerr << "Error loading rules: " << e.what() << std::endl;
        return 1;
    }
    std::vector<Violation> allViolations;
    for (const auto& entry : fs::recursive_directory_iterator("../../input_code")) {
        if (entry.path().extension() == ".cpp" || entry.path().extension() == ".hpp") {
            std::string code = readFile(entry.path().string());
            std::cout << "[DEBUG] Calling check() for file: " <<  entry.path().filename().string() << std::endl;
            for (const auto& rule : rules) {
                auto violations = rule->check(code, entry.path().filename().string());
                allViolations.insert(allViolations.end(), violations.begin(), violations.end());
            }
        }
    }

    std::ofstream report("../../reports/report.txt");
    for (const auto& v : allViolations) {
        report << v.filename << ":" << v.line << " - " << v.message << "\n";
    }

    std::cout << "Analysis complete. Report generated in 'reports/report.txt'.\n";
    return 0;
}
