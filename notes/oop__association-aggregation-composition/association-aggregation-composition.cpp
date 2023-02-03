/*
 * SNIPPET
 *
 * REFERENCES:
 * https://www.visual-paradigm.com/guide/uml-unified-modeling-language/uml-aggregation-vs-composition/
 * https://softwareengineering.stackexchange.com/questions/255973/c-association-aggregation-and-composition
 *
 *
 *
 * +---------+    association               +---------+
 * | class 1 |----------------------------->| class 2 |
 * +---------+                              +---------+
 * |         |                              |         |
 * +---------+                              +---------+
 *
 * Association: Foo has a pointer to Bar object as a data member
 * -> "owners feed pets, pets please owners"
 *
 *
 *
 * +---------+    aggregation               +---------+
 * | class 1 |< >-------------------------->| class 2 |
 * +---------+                              +---------+
 * |         |                              |         |
 * +---------+                              +---------+
 *
 * Aggregation: Foo has a pointer to Bar object and data of Bar is deep copied
 * in that pointer.
 * -> "a tail is a part of both dogs and cats" (aggregation or composition)
 *
 *
 * +---------+    composition               +---------+
 * | class 1 |<X>-------------------------->| class 2 |
 * +---------+                              +---------+
 * |         |                              |         |
 * +---------+                              +---------+
 *
 * Composition: Foo has a Bar object as data member.
 *
 *
 * +---------+
 * | class 1 |
 * +---------+
 * |         |
 * +---------+
 *     /_\
 *      |
 *      |
 * +---------+
 * | class 1 |
 * +---------+
 * |         |
 * +---------+
 *
 * Inheritance:
 * -> "a cat is a kind of pet" (inheritance / generalization)
 */


// ASSOCIATION
class Bar
{
  Baz baz;
};

class Foo
{
  Bar *bar;
  void setBar(Bar *_bar) { bar = _bar; }
};


// AGGREGATION
class Bar
{
  Baz baz;
};

class Foo
{
  Bar *bar;
  void setBar(Bar *_bar)
  {
    bar = new Bar;
    bar->baz = _bar->baz;
  }
};


// COMPOSTION
class Bar
{
  Baz baz;
};

class Foo
{
  Bar bar;
  Foo(Baz baz) { bar.baz = baz; }
};
