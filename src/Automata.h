#ifndef AUTOMATA_H
#define AUTOMATA_H
#include <vector>
#include "Lexer.h"
#include "Rule.h"


class Item;

//由Item类使用,用于指向下一个项目集
class Next {
public:
    Next();

    void setNext(int mark, Item* nextItem);

    //修改对应mark,的Item*指针值
    void resetNext(int mark, Item* nextItem);

    bool haveMark(int mark);

    Item* getNextItem(int mark);

    std::vector<int>* getMarkList() {
        return &marklist_;
    }

private:
    bool type_mark_[Token::num_E];
    Item* type_nextItem_[Token::num_E];

    bool symble_mark_[-Rule::num_E];
    Item* symble_nextItem_[-Rule::num_E];

    std::vector<int> marklist_;
};

//项目集数据结构
class Item {
public:
    //将合并过的item得mark记录下来
    std::vector<int> resetNotes_;

    Item(int num);

    ~Item();

    Next* getNext();

    std::vector<int>* getRule() {
        return &rules_;
    }

    std::vector<int>* getIndex() {
        return &ruleIndex_;
    }

    std::vector<std::vector<int>*>* getForwards() {
        return &forwards_;
    }

    int getNum() {
        return num_;
    }

    //检查以该mark的nextItem是否合并了的
    bool isResetMark(int mark);

private:
    int num_;//项目集序号(从 1 开始)

    Next next_;//指向下一个项目集

    std::vector<int> rules_;
    std::vector<int> ruleIndex_;

    //产生式规约的搜索符，空搜索符用-1表示
    std::vector<std::vector<int>*> forwards_;
};

//////////////////////////////////////////////////
//根据来自RuleGroup中的语法规则构造一个自动机：项目集规范组，根据自动机生成LR分析表
class Automata {
public:
    Automata() {};

    void start();

    Item* getFirstItem() {
        return firstItem_;
    }

    int getItemNum() {
        return numCounter_;
    }

private:
    int numCounter_ = 1; //项目集序号计数器

                         //以mark作为索引，记录构造过程中生成的全部item
    std::vector<Item*> type_itemlist_[Token::num_E];
    std::vector<Item*> symble_itemlist_[-Rule::num_E];

    //!@#$%^&没有对应的delete，存在内存泄露
    Item* firstItem_ = new Item(numCounter_);//自动机的起点，起始项目集


                                             ////////////////////////////////////////////////////////////////////
                                             //比较两个项目集是否等价
    bool equalItem(Item* item_1, Item* item_2);

    //检查以特定mark作为索引的item是否至少生成了一个
    bool haveMark(int mark);

    //根据已有Item生成新Item
    void growthNewItem(Item* item);

    //根据item的next对象的marklist集进行遍历
    void traversal(Item* item);

    //向项目集中添加新的项目
    //步骤：
    //1.根据clo队列，向项目集中加入新项目
    //2.完成全部的添加后 检查项目是否需要进行闭包运算。如果没有
    //  则函数结束，否则进行第3步
    //3.进行闭包运算，递归调用此方法。直到整个项目集添加完成
    void pushRules(Item *item, std::vector<int> &clo, std::vector<int>* forward);
    void pushRules(Item *item, int grule, int gindex, std::vector<int>* forward);

    //检查项目集中的某一项是否需要进行闭包运算
    //如果需要，返回返回需要进行运算的闭包的值
    //如果不需要，返回 0
    int checkSymble(int rule, int index);

    //闭包运算!@#$%^&效率低下有待改进
    std::vector<int> closure(int s);

    //求首符号集
    std::vector<int>* first(int rule, int at, std::vector<int>* forward);
};

#endif // !AUTOMATA_H
