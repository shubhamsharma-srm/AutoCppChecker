#include "RuleBase.hpp"
#include <regex>
#include <fstream>
#include <sstream>

RegexRule::RegexRule(const std::string& ruleName,
                     const std::string& ruleDescription,
                     const std::string& rulePattern)
    : ruleName(ruleName), ruleDescription(ruleDescription), rulePattern(rulePattern) {}

std::string RegexRule::name() const {
    return ruleName;
}

std::string RegexRule::description() const {
    return ruleDescription;
}

std::string RegexRule::pattern() const {
    return rulePattern;
}

// std::vector<Violation> RegexRule::check(const std::string& code, const std::string& filename) const {
//     std::vector<Violation> violations;
//     try{
//     std::regex expr(rulePattern);
//     std::istringstream iss(code);
//     std::string line;
//     int lineNum = 1;
//     while (std::getline(iss, line)) {
//         if (std::regex_search(line, expr)) {
//             violations.push_back({filename, lineNum, ruleDescription});
//         }
//         lineNum++;
//     }
// } catch (const std::regex_error& e) {
//     std::cerr << "[RegexRule ERROR] Invalid regex: " << rulePattern << " | " << e.what() << "\n";
// }
//     return violations;
// }

std::vector<Violation> RegexRule::check(const std::string& code, const std::string& filename) const {
    std::vector<Violation> violations;
    std::cout << "[DEBUG] Applying rule pattern: " << rulePattern << std::endl;
    std::regex expr;
    try {
        expr = std::regex(rulePattern, std::regex_constants::ECMAScript);  // safer
    } catch (const std::regex_error& e) {
        std::cerr << "[RegexRule ERROR] Invalid regex pattern: \"" << rulePattern 
                  << "\" | " << e.what() << std::endl;
        return violations;  // skip rule if pattern is invalid
    }

    std::istringstream iss(code);
    std::string line;
    int lineNum = 1;

    while (std::getline(iss, line)) {
        if (std::regex_search(line, expr)) {
            violations.push_back({filename, lineNum, ruleDescription});
        }
        lineNum++;
    }

    return violations;
}


std::vector<std::shared_ptr<RuleBase>> loadRulesFromJson(const std::string& jsonPath) {
    std::cout << "[INFO] loadRulesFromJson started with path: " << jsonPath << std::endl;

    std::ifstream file(jsonPath);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Failed to open JSON file at path: " << jsonPath << std::endl;
        std::abort();
    }

    nlohmann::json data;
    try {
        std::cout << "[INFO] Attempting to parse JSON..." << std::endl;
        file >> data;
        std::cout << "[INFO] JSON parsing successful." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] JSON parsing failed: " << e.what() << std::endl;
        std::abort();
    }

    std::vector<std::shared_ptr<RuleBase>> rules;

    try {
        for (const auto& rule : data) {
            std::string name = rule.at("name").get<std::string>();
            std::string description = rule.at("description").get<std::string>();
            std::string pattern = rule.at("pattern").get<std::string>();
            rules.push_back(std::make_shared<RegexRule>(name, description, pattern));
        }
        std::cout << "[INFO] Successfully loaded " << rules.size() << " rules." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] While building rule objects: " << e.what() << std::endl;
        std::abort();
    }

    return rules;
}
