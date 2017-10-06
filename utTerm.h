#ifndef UTTERM_H
#define UTTERM_H
#include "number.h"
#include "atom.h"
#include "variable.h"

//test Number.value()
TEST (Number,ctor) {
  Number one("one", 1);
  ASSERT_EQ("1", one.value());
}
//test Number.symbol()
TEST (Number, symbol) {
  Number one("one", 1);
  ASSERT_EQ("one", one.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
  Number twentyfive1(25);
  Number twentyfive2("twentyfive", 25);
  ASSERT_TRUE(twentyfive1.match(&twentyfive2));
  //EXPECT_TRUE(twentyfive1.match(twentyfive2));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
  Number twentyfive("twentyfive", 25);
  Number zero("zero", 0);
  ASSERT_FALSE(twentyfive.match(&zero));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
  Number twentyfive("twentyfive", 25);
  Atom tom("tom");
  ASSERT_FALSE(twentyfive.match(&tom));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
  Number twentyfive("twentyfive", 25);
  Variable X("X");
  ASSERT_TRUE(twentyfive.match(&X));
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
  Atom tom("tom");
  Number twentyfive("twentyfive", 25);
  ASSERT_FALSE(tom.match(&twentyfive));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
  Atom tom("tom");
  Variable X("X");
  ASSERT_TRUE(tom.match(&X));
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
  Variable X("X");
  Atom tom("tom");
  EXPECT_EQ("X = tom", X.match(&tom));
  ASSERT_TRUE(tom.match(&X));
  //EXPECT_TRUE(tom.match(X));
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
  Variable X("X");
  Atom jerry("jerry");
  Atom tom("tom");
  EXPECT_EQ("X = jerry", X.match(&jerry));
  ASSERT_FALSE(tom.match(&X));
  EXPECT_FALSE(tom.match(jerry));
}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
  Variable X("X");
  Number five("five", 5);
  ASSERT_EQ("X = 5", X.match(&five));
  EXPECT_TRUE(five.match(X));
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
  Variable X("X");
  Number twentyfive("twentyfive", 25);
  Number onehundred("onehundred", 100);
  EXPECT_EQ("X = 25", X.match(&twentyfive));
  ASSERT_EQ("false", X.match(&onehundred));
  ASSERT_TRUE(X.match(twentyfive));
  ASSERT_FALSE(X.match(onehundred));
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
  Variable X("X");
  Atom tom("tom");
  Number twentyfive("twentyfive", 25);
  EXPECT_EQ("X = tom", X.match(&tom));
  ASSERT_EQ("false", X.match(&twentyfive));
}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
  Atom tom("tom");
  Variable X("X");
  Number twentyfive("twentyfive", 25);
  EXPECT_TRUE(tom.match(&X));
  EXPECT_EQ("false", X.match(&twentyfive));
  ASSERT_FALSE(twentyfive.match(&X));
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
  Variable X("X");
  Atom tom("tom");
  EXPECT_EQ("X = tom", X.match(&tom));
  //ASSERT_EQ("X = tom", X.match(&tom));
}
#endif
