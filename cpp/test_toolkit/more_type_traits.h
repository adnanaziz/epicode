//
// Created by metopa on 04.06.2016.
//

#ifndef SOLUTIONS_MORE_TYPE_TRAITS_H
#define SOLUTIONS_MORE_TYPE_TRAITS_H

#include <type_traits>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <memory>


#define REGISTER_TREE_TYPE(TYPE) namespace type_traits{\
    template <class T> struct is_binary_tree<TYPE> : public true_type {}; }

//@formatter::off
namespace type_traits {
  using std::true_type;
  using std::false_type;
  using std::vector;
  using std::list;
  using std::set;
  using std::map;
  using std::unique_ptr;
  using std::shared_ptr;

  template <class T>
  struct is_container : public false_type {};
  template <class T>
  struct is_container<vector<T>> : public true_type {};
  template <class T>
  struct is_container<list<T>> : public true_type {};
  template <class T>
  struct is_container<set<T>> : public true_type {};
  template <class K, class V>
  struct is_container<map<K, V>> : public true_type {};

  template <class T>
  struct is_binary_tree : public false_type {};


  template <class T>
  const T* GetRawPtr(const T* ptr) { return ptr; }
  template <class T>
  const T* GetRawPtr(const unique_ptr <T>& ptr) { return ptr.get(); }
  template <class T>
  const T* GetRawPtr(const shared_ptr <T>& ptr) { return ptr.get(); }
}

//@formatter::on

#endif //SOLUTIONS_MORE_TYPE_TRAITS_H
