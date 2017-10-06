#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "variable.h"

using std::string;

class Number;

class Atom {
public:
  Atom (string str):_symbol(str) {}
  string symbol(){
    return _symbol;
  }
  bool match(int const i){
    return MATCH_FAILURE_DIFF_CONSTANT;
  }
  bool match(string const s){

    return MATCH_FAILURE_DIFF_CONSTANT;
  }
  bool match(Number *number){
    return MATCH_FAILURE_DIFF_CONSTANT;
  }
  bool match(Atom *atom){
    return (_symbol == atom->symbol());
  }
  bool match(Variable *variable){
    bool ret = false;
    if(variable->assignable()){
      variable->match(_symbol);
      ret = true;
    }
    else{
      ret = (_symbol == variable->value());
    }
    return ret;
  }
  bool match(Number &number){
    return MATCH_FAILURE_DIFF_CONSTANT;
  }
  bool match(Atom& atom){
    return (_symbol == atom._symbol);
  }
  bool match(Variable& variable){
    bool ret = false;
    if(variable.assignable()){
      variable.match(_symbol);
      ret = true;
    }
    else{
      ret = (_symbol == variable.value());
    }
    return ret;
  }
private:
  bool MATCH_FAILURE_DIFF_CONSTANT = false;
  //bool MATCH_SUCCESS_TO_VAR = true;
  string _symbol;
};

#endif
