#include "MathCompiler/Lexer/Lexer.h"

int main() {
    try {
        MathCompiler::DFA::DFA* dfa = MathCompiler::DFA::buildNumberDFA();
        std::string input = "99+22* 2 2  -   50000\nh";
        MathCompiler::Lexer* lexer = new MathCompiler::Lexer(input, dfa);

        lexer->tokenize();
    }
    catch (const std::exception& e) {
        std::cerr << "An error occurred during tokenization: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "An unknown error occurred during tokenization." << std::endl;
    }

    return 0;
}