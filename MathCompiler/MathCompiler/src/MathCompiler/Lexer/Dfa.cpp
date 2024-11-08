#include "Dfa.h"

namespace MathCompiler {
	namespace DFA {
		DFA* MathCompiler::DFA::buildNumberDFA()
		{
			enum states {
				S0 = INIT,
				S1,
				S2,
				S3,
				S4
			};
			std::set<char> alphabet{
				'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '+','/','*'
			};
			std::vector<std::vector<int>> table{
			   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2},
			   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, -1, -1},
			   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
			};
			std::unordered_map<int, TokenType> acceptStates{
				{1, TokenType::NUMBER},
				{2, TokenType::OPERATOR}
			};
			std::unordered_map<char, int> alphabetToIndex {
				{'0', 0}, {'1', 1}, {'2', 2}, {'3',3}, {'4',4}, {'5',5}, {'6',6}, {'7',7}, {'8',8}, {'9',9}, {'-',10}, {'+',11}, {'/',12},{'*',13}
			};
			DFA* dfa = new DFA{
				alphabet,     
				table,        
				acceptStates,
				alphabetToIndex
			};
			return dfa;
		}
	}
	
}

