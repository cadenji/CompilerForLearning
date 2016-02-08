#include "Parser.h"

int main() {
    Lexer* lexer = new Lexer();
    Parser par = Parser(lexer);



    //Token* t;//+_+
    //int counter = 0;//+_+
    //int type;//+_+
    //do{//+_+
    //		t = lexer->getToken();//+_+
    //		type = t->getType();//+_+
    //
    //		switch (type){//+_+
    //		case Token::intNum://+_+
    //			std::cout << ((IntNum*)t)->getValue() << std::endl;//+_+
    //			break;//+_+
    //		case Token::signAdd://+_+
    //			std::cout << ((Sign*)t)->getValue() << std::endl;//+_+
    //			break;//+_+
    //		case Token::floatNum://+_+
    //			std::cout << ((FloatNum*)t)->getValue() << std::endl;//+_+
    //			break;//+_+
    //		case Token::signAssign://+_+
    //			std::cout << "=" << std::endl;//+_+
    //			break;//+_+
    //		case Token::signSub://+_+
    //			std::cout << ((Sign*)t)->getValue() << std::endl;//+_+
    //			break;//+_+
    //		case Token::signTimes://+_+
    //			std::cout << ((Sign*)t)->getValue() << std::endl;//+_+
    //			break;//+_+
    //		case Token::signDivision://+_+
    //			std::cout << ((Sign*)t)->getValue() << std::endl;//+_+
    //			break;//+_+
    //		case Token::signMod://+_+
    //			std::cout << ((Sign*)t)->getValue() << std::endl;//+_+
    //			break;//+_+
    //		case Token::signEqual://+_+
    //			std::cout << ((Sign*)t)->getValue() << std::endl;//+_+
    //			break;//+_+
    //		case Token::signUnequal://+_+
    //			std::cout << ((Sign*)t)->getValue() << std::endl;//+_+
    //			break;//+_+
    //		case Token::signLess://+_+
    //			std::cout << ((Sign*)t)->getValue() << std::endl;//+_+
    //			break;//+_+
    //		case Token::signMore://+_+
    //			std::cout << ((Sign*)t)->getValue() << std::endl;//+_+
    //			break;//+_+
    //		case Token::signLessOrEqual://+_+
    //			std::cout << ((Sign*)t)->getValue() << std::endl;//+_+
    //			break;//+_+
    //		case Token::signMoreOrEqual://+_+
    //			std::cout << ((Sign*)t)->getValue() << std::endl;//+_+
    //			break;//+_+
    //		case Token::signAnd://+_+
    //			std::cout << ((Sign*)t)->getValue() << std::endl;//+_+
    //			break;//+_+
    //		case Token::signOr://+_+
    //			std::cout << ((Sign*)t)->getValue() << std::endl;//+_+
    //			break;//+_+
    //		case Token::signNot://+_+
    //			std::cout << ((Sign*)t)->getValue() << std::endl;//+_+
    //			break;//+_+
    //		default://+_+
    //			break;//+_+
    //		}//+_+
    //		counter++;//+_+
    //	} while (type != Token::endSymbol);//+_+



    system("pause");
    return 0;
}