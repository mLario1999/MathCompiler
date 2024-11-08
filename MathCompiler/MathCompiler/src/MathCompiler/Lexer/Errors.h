#pragma once

namespace MathCompiler {
#define LEXER_THROW_UNRECOGNIZED(currChar, line, pos ) throw std::runtime_error("Unrecognized character '" + std::string(1, currChar) + " encountered at line " + std::to_string(line) + " position " + std::to_string(pos));

}