#ifndef PARSING_TABLE_H
#define PARSING_TABLE_H
#include <stack>
#include "Automata.h"

class OperationMark {
public:
    static enum Oper {
        shift,
        reduce,
        gotoo, //goto
        acc,
        nil, //表示不接受

             //记录枚举型数量
        num_E,
    };
    OperationMark();
    OperationMark(int operation, int number);

    void setOperation(int oper) {
        operation_ = oper;
    }

    int getOperation() {
        return operation_;
    }

    void setNumber(int num) {
        number_ = num;
    }

    int getNumber() {
        return number_;
    }
private:
    int operation_;
    int number_;
};

//LR文法分析表
class ParsingTable {
public:
    ParsingTable(Item* firstItem, int item_num);
    ~ParsingTable();

    int lookUpOperInAction(int token, int state);
    int lookUpNumInAction(int token, int state);
    int lookUpNumInGoto(int token, int state);
private:
    int item_num_;
    //第一维表示接受项，第二维表示状态
    OperationMark** action_;//ACTION表 Token::num_E行，item_num列,
                            //action_[0][..]表示无接受向（实际上与action[Token::endSymble][..]等价）
    OperationMark** gotoo_;//GOTO表 （-Rule::num_E） - 1行，item_num列

    void travel(Item* item);//对自动机进行遍历
};


#endif // !PARSING_TABLE_H
