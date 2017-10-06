#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
using std::string;

class Atom;
class Number;

class Variable{
public:
  Variable(string s);
  string symbol();
  string value();
  string match(string s);
  string match(Atom *atom);
  string match(Number *number);
  bool match(Atom& atom);
  bool match(Number& number);
  bool assignable();

private:
  string const _symbol;
  string _value;
  bool _assignable = true;
  bool assign(string s);
};

#endif
