#pragma once

#include "MathCompiler/Core.h"

namespace MathCompiler {

	enum class TokenType {
		NUMBER,
		OPERATOR,
	};

	struct Token {
		TokenType type;
		std::string value;
		int line;
		int pos;
	};
}