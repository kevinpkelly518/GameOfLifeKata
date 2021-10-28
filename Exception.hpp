#pragma once

#include <exception>


namespace Life {


class InvalidIndexException : public std::exception {};
class ParseGenerationException : public std::exception {};
class ParseSizeException : public std::exception {};
class ParseGridException : public std::exception {};


} // end namespace