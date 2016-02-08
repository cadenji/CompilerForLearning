#include "Rule.h"
#include "Lexer.h"

Rule::Rule(int length, int left, int* right) {
    ruleLength_ = length;
    left_ = left;
    right_ = right;
}
int Rule::getRuleLength() {
    return ruleLength_;
}
int Rule::getLeft() {
    return left_;
}
int Rule::getRight(int index) {
    return right_[index];
}


//!@#$%^&没有对应的delete，存在内存泄露
Rule RuleGroup::ruleGroup_[9] = {
    Rule(1, Rule::symble_1, new int[1]{ Rule::symble_2 }),
    Rule(1, Rule::symble_2, new int[1]{ Rule::symble_3 }),
    Rule(1, Rule::symble_3, new int[1]{ Token::intNum }),
    Rule(3, Rule::symble_3, new int[3]{ Token::intNum, Rule::symble_4, Rule::symble_3 }),
    Rule(1, Rule::symble_4, new int[1]{ Token::signAdd }),
    Rule(1, Rule::symble_4, new int[1]{ Token::signSub }),
    Rule(1, Rule::symble_4, new int[1]{ Token::signTimes }),
    Rule(1, Rule::symble_4, new int[1]{ Token::signDivision }),
    Rule(1, Rule::symble_4, new int[1]{ Token::signMod })
};