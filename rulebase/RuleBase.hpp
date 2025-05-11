// === Step 1: RuleBase.hpp ===
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "../third_party/json/json.hpp"

struct Violation {
    std::string filename;
    int line;
    std::string message;
};

class RuleBase {
public:
    virtual std::string name() const = 0;
    virtual std::string description() const = 0;
    virtual std::string pattern() const = 0;
    virtual std::vector<Violation> check(const std::string& code, const std::string& filename) const = 0;
    virtual ~RuleBase() = default;
};

class RegexRule : public RuleBase {
public:
    RegexRule(const std::string& ruleName,
              const std::string& ruleDescription,
              const std::string& rulePattern);

    std::string name() const override;
    std::string description() const override;
    std::string pattern() const override;
    std::vector<Violation> check(const std::string& code, const std::string& filename) const override;

private:
    std::string ruleName;
    std::string ruleDescription;
    std::string rulePattern;
};

std::vector<std::shared_ptr<RuleBase>> loadRulesFromJson(const std::string& jsonPath);
