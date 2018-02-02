#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <utility>
#include <string>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
namespace qi = boost::spirit::qi;
namespace karma = boost::spirit::karma;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;
using namespace std;

template <typename C, typename V>
struct SymbolTable : qi::symbols<C, V> {
  //
};

template <typename Iterator>
struct CalculatorParser : qi::grammar<Iterator, double(), qi::space_type>
{
  CalculatorParser() : CalculatorParser::base_type(expression)
  {
    using qi::eps;
    using qi::lit;
    using qi::_val;
    using qi::_1;
    using qi::char_;

    // variable    = qi::lexeme [ qi::alpha >> *qi::alnum ];
    expression =
      term                         [_val = _1]
      >> *(('+' >> term            [_val += _1])
              |('-' >> term        [_val -= _1])
              );

    term =
      factor                          [_val = _1]
      >> *(   ('*' >> factor          [_val *= _1])
              |   ('/' >> factor      [_val /= _1])
              )
      ;

    factor =
      qi::double_                     [_val = _1]
      |   '(' >> expression           [_val = _1] >> ')'
      |   ('-' >> factor              [_val = -_1])
      |   ('+' >> factor              [_val = _1])
      ;
  }
  qi::rule<Iterator, double(), qi::space_type> term;
  qi::rule<Iterator, double(), qi::space_type> factor;
  qi::rule<Iterator, double(), qi::space_type> expression;
};

#endif // PARSER_H
