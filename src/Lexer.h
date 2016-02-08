#ifndef LEXER_H_
#define LEXER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

//词法分析器输出的单词的数据结构基类
class Token {
public:
    //定义单词的类型
    static enum Type {
        intNum = 1, //无符号整型数
        floatNum, //浮点数
        signAssign, //赋值号'='
        signAdd, //加号'+'
        signSub, //减号'-'
        signTimes, //乘号'*'
        signDivision, //除号'/'
        signMod, //取余号'%'
        signEqual, //等于号'=='
        signUnequal, //不等于号'!='
        signLess, // 小于号'<'
        signMore, //大于号'>'
        signLessOrEqual, //小于等于号'<='
        signMoreOrEqual, //大于等于号'>='
        signAnd, //与'&&'
        signOr, //或'||'
        signNot, //非'!'
        keyword, //关键字
        identifier, //标识符
        space, //空格
        newLine, //换行
        endSymbol, //单词流终止标志

                   //记录枚举型数量
        num_E,
    };

    //Token类的构造函数
    Token(Type type, std::string str) {
        type_ = type;
        str_ = str;
    }

    int getType() {
        return type_;
    }

    std::string getStr() {
        return str_;
    }
private:
    Type type_;
    std::string str_;
};


//用于处理无符号整型数
//正规式：[1-9][0-9]*|0
class IntNum : public Token {
public:
    IntNum(std::string str);

    int getValue() {
        return value_;
    }
private:
    int value_;
};


//用于处理浮点数
class FloatNum : public Token {
public:
    FloatNum(std::string str);

    float getValue() {
        return value_;
    }
private:
    float value_;
};


//用于处理运算符包括算数运算符，包括 + - * / %
//                  关系运算符，包括 == <= >= != > <
//                  逻辑运算符，包括 && || !
//以及              赋值运算符 =
class Sign : public Token {
public:
    Sign(Type type, std::string str);

    std::string getValue() {
        return value_;
    }
private:
    std::string value_;
};


//用于处理标识符
//class identifier :public Token {
//public:
//    identifier(std::string value):Token(identifier)
//
//};

//用于处理关键字
//class Keyword : public Token{
//public:
//	Keyword(std::string value) : Token(keyword){
//		value_ = value;
//	}
//
//	std::string getValue(){
//		return value_;
//	}
//private:
//	std::string value_;
//};


//////////////////////////////////////////////
//词法分析器
class Lexer {
public:
    //定义状态机状态
    //无符号整型数有两个接受状态int_zero和int_num
    static enum State {
        start = 0,
        int_zero,
        int_num,
        sign_0,
        sign_1,
        sign_2,
        sign_3, //非接受状态
        sign_4,
        sign_5, //非接受状态
        sign_6,
        float_0, //非接受状态
        float_1,
        back, //后退状体，状态机循环结束的标志
    };

    Lexer();


    //由词法分析器在需要的时候调用，每次返回一个单词
    //内部实际是一个手工构造的有限自动机
    //循环调用readChar()，默认转换多余字符
    //具体指：一个或一个以上的空格字符' '、一个或一个以上的换行字符'\n'
    //这两种情况在调用此函数时只返还一个空格' '或换行'\n'
    //一个或一个以上的制表符'\t'只返回一个空格' '
    //换行'\n'后的空格' '被全部忽略
    Token *getToken();

private:
    void lexerConfig(); //由构造函数Lexer()调用，在命令行中提示用户输入用于初始化Lexer对象
                        //为成员变量file_name_赋值

    void readChar(); //由getToken()调用，每次返回一个字符	 

    void setState(); //自动机的状态转换函数,更新state_和old_state_
    void setState(State state);

    std::string file_name_; //存放当前读取的文件名
    std::fstream file_in_;
    char c_; //存储当前从文件中读入的字符

    State state_; //记录状态机当前状态
    State old_state_;
    std::string str_;
};

#endif // !LEXER_H_