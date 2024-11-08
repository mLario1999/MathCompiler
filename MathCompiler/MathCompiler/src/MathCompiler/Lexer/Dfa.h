#pragma once

#include "MathCompiler/Core.h"
#include "MathCompiler/Lexer/Token.h"

namespace MathCompiler {

	namespace DFA {

		enum States {
			INIT = 0,
			ERROR = -1,
		};

		const struct DFA {
			std::set<char> alphabet;
			std::vector<std::vector<int>> tTable;
			std::unordered_map<int, TokenType> acceptStates;
			std::unordered_map<char, int> alphabetToIndex;
		};

		DFA* buildNumberDFA();
	}
}

