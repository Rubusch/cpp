/*
  C++11 - type deduction (Meyers / item 1)

  template< typename T >
  void func(ParmType param);

  func(expr)

  ---
  T        - template type
  ParamType - parameter type, basically the template type with certain adornments, e.g. const, reference, pointer, etc.
  expr      - expression type, the deducted type from the ParamType in the expression


  resources: Effective Modern C++, Scott Meyers, 2015
 */

// TODO
