#ifndef PARSER_H_
#define PARSER_H_
#include <stack>
#include "Lexer.h"
#include "ParsingTable.h"

//语法分析器
class Parser {
public:
    Parser(Lexer* lexer);
    ~Parser();

private:
    ParsingTable* tab_; //LR分析表
    Lexer* lexer_;

    Token* token_buf_;
    int state_buf_;

    bool parse_Start(); //返回false表示文本分析完毕 返回true表示接受一条语句

};

#endif // !PARSER_H_
