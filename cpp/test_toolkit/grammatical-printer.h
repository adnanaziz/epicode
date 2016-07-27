// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_GRAMMATICAL_PRINTER_H
#define SOLUTIONS_GRAMMATICAL_PRINTER_H

//FIXME Better name

template<class Value, class String1, class String2>
class GrammaticalPrinter {
 public:
  GrammaticalPrinter( const Value& value, const String1& singular, const String2& plural ) :
      value_( value ), singular_( singular ), plural_( plural ) { }

  friend ostream& operator <<( ostream& out, const GrammaticalPrinter& p ) {
    if ( p.value_ == 1 )
      return out << p.value_ << p.singular_;
    else
      return out << p.value_ << p.plural_;
  }
 private:
  const Value& value_;
  const String1& singular_;
  const String2& plural_;
};

template<class Value, class String1, class String2>
GrammaticalPrinter<Value, String1, String2>
grammaticalPrinter( const Value& value, const String1& singular, const String2& plural ) {
  return GrammaticalPrinter<Value, String1, String2>( value, singular, plural );
}

#endif //SOLUTIONS_GRAMMATICAL_PRINTER_H
