#include "Lexer.h"

IntNum::IntNum(std::string str) : Token(intNum, str) {
    int length = str.length();
    value_ = 0;

    //将string型转换成int型
    for (int i = 0; i < length; i++) {
        value_ += ((int)str[i] - '0') * pow(10, length - 1 - i);
    }
}

Sign::Sign(Type type, std::string str) : Token(type, str) {
    value_ = str;
}

FloatNum::FloatNum(std::string str) : Token(floatNum, str) {
    int length = str.length();
    int point_position = 0;
    value_ = 0.0;

    //将string型转换成float型
    for (int i = 0; i < length; i++) {
        if (str[i] == '.') {
            point_position = i;
        }
    }
    for (int i = 0; i < length; i++) {
        if (i != point_position) {
            if (i < point_position) {
                value_ += ((int)str[i] - '0') * pow(10, point_position - i - 1);
            }
            else {
                value_ += ((int)str[i] - '0') * pow(10, point_position - i);
            }
        }
    }
}

///////////////////////////////

Lexer::Lexer() {
    lexerConfig();
}

Token* Lexer::getToken() {
    setState();
    while (state_ != back) {
        readChar();

        switch (state_) {
        case start:
            if (c_ == '0') {
                setState(int_zero);
            }
            else if (c_ == '1' || c_ == '2' || c_ == '3' || c_ == '4' ||
                c_ == '5' || c_ == '6' || c_ == '7' || c_ == '8' ||
                c_ == '9') {
                setState(int_num);
            }
            else if (c_ == '+' || c_ == '-' || c_ == '*' || c_ == '/' ||
                c_ == '%') {
                setState(sign_0);
            }
            else if (c_ == '>' || c_ == '<' || c_ == '!' || c_ == '=') {
                setState(sign_1);
            }
            else if (c_ == '|') {
                setState(sign_3);
            }
            else if (c_ == '&') {
                setState(sign_5);
            }
            else {
                setState(back);
            }
            break;
        case int_zero:
            if (c_ == '.') {
                setState(float_0);
            }
            else {
                setState(back);
            }
            break;
        case int_num:
            if (c_ == '0' || c_ == '1' || c_ == '2' || c_ == '3' ||
                c_ == '4' || c_ == '5' || c_ == '6' || c_ == '7' ||
                c_ == '8' || c_ == '9') {
                setState(int_num);
            }
            else if (c_ == '.') {
                setState(float_0);
            }
            else {
                setState(back);
            }
            break;
        case sign_0:
            setState(back);
            break;
        case sign_1:
            if (c_ == '=') {
                setState(sign_2);
            }
            else {
                setState(back);
            }
            break;
        case sign_2:
            setState(back);
            break;
        case sign_3:
            if (c_ == '|') {
                setState(sign_4);
            }
            else {
                setState(back);
            }
            break;
        case sign_4:
            setState(back);
            break;
        case sign_5:
            if (c_ == '&') {
                setState(sign_6);
            }
            else {
                setState(back);
            }
            break;
        case sign_6:
            setState(back);
            break;
        case float_0:
            if (c_ == '0' || c_ == '1' || c_ == '2' || c_ == '3' ||
                c_ == '4' || c_ == '5' || c_ == '6' || c_ == '7' ||
                c_ == '8' || c_ == '9') {
                setState(float_1);
            }
            else {
                setState(back);
            }
            break;
        case float_1:
            if (c_ == '0' || c_ == '1' || c_ == '2' || c_ == '3' ||
                c_ == '4' || c_ == '5' || c_ == '6' || c_ == '7' ||
                c_ == '8' || c_ == '9') {
                setState(float_1);
            }
            else {
                setState(back);
            }
            break;
        }
    }

    file_in_.clear();
    file_in_.seekg(-1, std::ios::cur);

    if (old_state_ == int_zero || old_state_ == int_num) {
        return new IntNum(str_);
    }
    else if (old_state_ == sign_0 || old_state_ == sign_1 ||
        old_state_ == sign_2 || old_state_ == sign_4 ||
        old_state_ == sign_6) {
        if (str_ == "=") {
            return new Sign(Token::signAssign, str_);
        }
        else if (str_ == "+") {
            return new Sign(Token::signAdd, str_);
        }
        else if (str_ == "-") {
            return new Sign(Token::signSub, str_);
        }
        else if (str_ == "*") {
            return new Sign(Token::signTimes, str_);
        }
        else if (str_ == "/") {
            return new Sign(Token::signDivision, str_);
        }
        else if (str_ == "%") {
            return new Sign(Token::signMod, str_);
        }
        else if (str_ == "==") {
            return new Sign(Token::signEqual, str_);
        }
        else if (str_ == "!=") {
            return new Sign(Token::signUnequal, str_);
        }
        else if (str_ == "<") {
            return new Sign(Token::signLess, str_);
        }
        else if (str_ == ">") {
            return new Sign(Token::signMore, str_);
        }
        else if (str_ == "<=") {
            return new Sign(Token::signLessOrEqual, str_);
        }
        else if (str_ == ">=") {
            return new Sign(Token::signMoreOrEqual, str_);
        }
        else if (str_ == "&&") {
            return new Sign(Token::signAnd, str_);
        }
        else if (str_ == "||") {
            return new Sign(Token::signOr, str_);
        }
        else {  //str_ == "!"
            return new Sign(Token::signNot, str_);
        }
    }
    else if (old_state_ == float_1) {
        return new FloatNum(str_);
    }
    else if (old_state_ == sign_3 || old_state_ == sign_5 ||
        old_state_ == float_0) {
        //非接受状态错误
        std::cerr << "State choose error!" << std::endl;
        system("pause");
        exit(0);
    }
    else {
        return new Token(Token::endSymbol, "\0");
    }
}

void Lexer::lexerConfig() {
    std::cout << "Compiler start:" << std::endl;
    std::cout << "Please enter the source file name: ";
    getline(std::cin, file_name_, '\n');

    //文件读取操作
    file_in_.open(file_name_);
    if (!file_in_) {
        std::cerr << "File open error!" << std::endl;
        system("pause");
        exit(0);
    }
}

void Lexer::readChar() {
    if (!file_in_.get(c_)) {
        file_in_.close();
        c_ = '\0';
    }
}

void Lexer::setState() {
    state_ = start;
    old_state_ = start;
    str_.clear();
}
void Lexer::setState(State state) {
    old_state_ = state_;
    state_ = state;
    if (!(state == back)) {
        str_ += c_;
    }
}