/*
 * SNIPPET
 *
 * source: https://softwareengineering.stackexchange.com/questions/255973/c-association-aggregation-and-composition
 *
 *
 *
 * Association: Foo has a pointer to Bar object as a data member
 *
 * Aggregation: Foo has a pointer to Bar object and data of Bar is deep copied in that pointer.
 *
 * Composition: Foo has a Bar object as data member.
 */



//ASSOCIATION
class Bar
{
  Baz baz;
};

class Foo
{
  Bar* bar;
  void setBar(Bar* _bar)
  {
    bar=_bar;
  }
};



//AGGREGATION
class Bar
{
  Baz baz;
};

class Foo
{
  Bar* bar;
  void setBar(Bar* _bar)
  {
    bar = new Bar;
    bar->baz=_bar->baz;
  }
};



//COMPOSTION
class Bar
{
  Baz baz;
};

class Foo
{
  Bar bar;
  Foo(Baz baz)
  {
    bar.baz=baz;
  }
};

