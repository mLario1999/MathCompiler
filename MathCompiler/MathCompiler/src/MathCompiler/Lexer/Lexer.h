#pragma once

#include "MathCompiler/Core.h"
#include "MathCompiler/Lexer/Token.h"
#include "MathCompiler/Lexer/Dfa.h"
#include "MathCompiler/Lexer/Errors.h"

namespace MathCompiler {

	class Lexer
	{
	public:
		Lexer(std::string input, DFA::DFA* dfa) 
			: m_Input(input), m_Pos(0), m_Tokens(), m_Dfa(dfa), m_Curr(), m_lastAcceptingState(), m_inputSize(static_cast<int>(input.size())), m_Line(1), m_LinePos(1) {}
		void tokenize();
	private:
		int m_Pos;
		int m_LinePos;
		char m_Curr;
		int m_inputSize;
		int m_lastAcceptingState;
		int m_Line;
		std::string m_Input;
		std::vector<Token*> m_Tokens;
		DFA::DFA* m_Dfa;
		char peek() const;
		char advance();
		void checkAndSkip();
		int getNextState(int currState);
		void lookAhead(int& currState, std::string& token);
		bool isAccepting(int state);
		Token* createToken(std::string val, TokenType type);
	};
}





