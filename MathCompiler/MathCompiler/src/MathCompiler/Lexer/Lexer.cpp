#include "Lexer.h"

namespace MathCompiler {

	void Lexer::tokenize()
	{
		int currState = DFA::States::INIT;
		m_lastAcceptingState = DFA::States::ERROR;
		std::string currToken("");
		while (m_Pos < m_inputSize) {
			checkAndSkip();
			m_Curr = peek();
			currState = getNextState(currState);
			if (currState == DFA::States::ERROR) {
				if (m_lastAcceptingState == DFA::States::ERROR) {
					LEXER_THROW_UNRECOGNIZED(m_Curr, m_Line, m_LinePos)
				}
				TokenType t = m_Dfa->acceptStates[m_lastAcceptingState];
				m_Tokens.push_back(createToken(currToken, t));
				currToken.clear();
				currState = DFA::States::INIT;
				m_lastAcceptingState = DFA::States::ERROR;
				continue;
			}
			if (!isAccepting(currState)) {
				lookAhead(currState, currToken);
			}
			else {
				currToken.push_back(m_Curr);
				m_lastAcceptingState = currState;
				advance();
			}
		}
		if (m_lastAcceptingState != DFA::States::ERROR) {
			TokenType t = m_Dfa->acceptStates[m_lastAcceptingState];
			m_Tokens.push_back(createToken(currToken, t));
			return;
		}
		else {
			LEXER_THROW_UNRECOGNIZED(m_Curr, m_Line, m_LinePos)
		}
	}
	char Lexer::peek() const {
		if (m_Pos < m_inputSize) {
			return m_Input[m_Pos];
		}
		return '\0';
	}

	char Lexer::advance()
	{
		if (m_Pos < m_inputSize) {
			char temp = m_Curr;
			m_Pos++; m_LinePos++;
			m_Curr = (m_Pos < m_inputSize) ? m_Input[m_Pos] : '\0';
			return m_Curr;
		}
		else {
			return '\0';
		}
	}



	void Lexer::checkAndSkip()
	{
		while (m_Curr == ' ' || m_Curr == '\n') {
			if (m_Curr == '\n') {
				m_Line++;
				m_LinePos = 1;
			}
			advance();
		}
	}

	int Lexer::getNextState(int currState)
	{
		if (m_Dfa->alphabetToIndex.find(m_Curr) != m_Dfa->alphabetToIndex.end()) {
			int trans = m_Dfa->alphabetToIndex[m_Curr];
			return m_Dfa->tTable[currState][trans];
		}
		LEXER_THROW_UNRECOGNIZED(m_Curr, m_Line, m_LinePos);
		
	}

	void Lexer::lookAhead(int& currState, std::string& token)
	{
		std::string buff("");
		char c = m_Curr;
		int lookaheadPos = m_Curr;
		while (!isAccepting(currState) || currState != DFA::States::ERROR) {
			buff.append(std::to_string(c));
			currState = getNextState(currState);
			lookaheadPos++;
			if (lookaheadPos >= m_inputSize) {
				break;
			}
	   }
		if (isAccepting(currState)) {
			m_Curr = lookaheadPos;
			token.append(buff);
		}
		else {
			currState = m_lastAcceptingState;
		}
	}
	bool Lexer::isAccepting(int state) {
		return m_Dfa->acceptStates.find(state) != m_Dfa->acceptStates.end();
	}

	Token* Lexer::createToken(std::string val, TokenType type) {
		Token* t = new Token{
			type,
			val,
			m_Line,
			m_LinePos
		};
		return t;
	}
}

