/*
  C++11 - prefer scoped enums to unscoped enums (Meyers / item 10)

  ---

  lvalue    - has an address, e.g. a user maintained variable or memory with
              accessible address

  rvalue    - has no accessible address, e.g. a plain number value (stored only
              temporarlily)

  scoped enums - C++11-style enums, e.g. 'enum class {}'

  unscoped enums - C++98-style enums, e.g. 'enum {}'


  conclusion:

  - C++98-style enums are now known as unscoped enums

  - enumerators of scoped enums are visible only within the enum, they convert
    to other types only with a cast

  - both scoped an unscoped enums support specification of the underlying type;
    the default underlying type for scoped enums is int; unscoped enums have no
    default underlying type

  - scoped enums may always be forward-declared; unscoped enums may be
    forward-declared only if their declaration specifies an underlying type

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>

using namespace std;


// C++11 solution
template<typename T>
constexpr typename std::underlying_type<T>::type toUType(T enumerator) noexcept
{
  return static_cast<typename std::underlying_type<T>::type>(enumerator);
}
// */

/*
// C++14, the '_t' aliases are available
template<typename T>
constexpr std::underlying_type_t<T> toUType(T enumerator) noexcept
{
  return static_cast<std::underlying_type_t<T> >(enumerator);
}
// */

/*
// C++14, improved
template<typename T>
constexpr auto
toUType(T enumerator) noexcept
{
  return static_cast<std::underlying_type_t<T> >(enumerator);
}
// */


int main(void)
{
/*
  cout << "C++98-style enum" << endl;
  enum Color { black, white, green };
  auto white = false; // does not compile
/*/
  cout << "C++11-style enum" << endl;
  enum class Color { black, white, green };
  auto white = false; // works
// */

  cout << "some enum operations" << endl;
  Color clr1 = Color::white; // works
  auto clr2 = Color::white; // works
  cout << endl;

  cout << "enum class with specific type" << endl;
  enum class Status: std::uint32_t { good = 0
                                     , failed = 1
                                     , incomplete = 100
                                     , corrupt = 200
                                     , audited = 500
                                     , indeterminate = 0xffffffff
  };


// userinfo and typed example
  using UserInfo = std::tuple<std::string, std::string, std::size_t>;
/*
  enum UserInfoFields { uiName, uiEmail, uiReputation };
  UserInfo uInfo;
//  auto val = std::get<uiEmail>(uInfo); // uses implicit conversion, may work
/*/
  enum class UserInfoFields { uiName, uiEmail, uiReputation };
  UserInfo uInfo;
//  auto val = std::get<static_cast<std::size_t>(UserInfoFields::uiEmail)>(uInfo); // not nice, using static_cast here
// */

  // generic access
  auto val = std::get<toUType(UserInfoFields::uiEmail)>(uInfo);


  cout << "READY." << endl;
}
