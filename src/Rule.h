#ifndef RULE_H_
#define RULE_H_

#include <vector>

//描述语法规则的产生式数据结构
class Rule {
public:
    //语法规则中的非终结符部分
    static enum Symble {
        symble_1 = -1,
        symble_2 = -2,
        symble_3 = -3,
        symble_4 = -4,

        //记录枚举型数量
        num_E = -5,
    };

    Rule(int length, int left, int* right);
    int getRuleLength();
    int getLeft();
    int getRight(int index); //获取数组right_的下标为num的数据

private:
    int ruleLength_; //产生式右部的长度
    int left_; //产生式的左部
    int* right_; //产生式的右部
};

class RuleGroup {
public:
    RuleGroup();
    static Rule ruleGroup_[9];

};

#endif // !RULE_H_
