/////////////////////////////////////////////////////////////////////////////
//	file		:	stricmp.h
//  copyright	:	(C) 2002 by Benjamin Kaufmann
//  email		:	hume@c-plusplus.de
//	internet	:	http://bens.c-plusplus.info/
//
//	header for case-insensitive string comparison
//
//	define the macros NO_CASE_COMPARE_HAS_LOCALE and
//	NO_CASE_COMPARE_HAS_FACETS if your compiler supports locales and facets.
//	define the macro NO_CASE_COMPARE_HAS_CHAR_TRAITS
//	if your compiler has std::char_traits and if you are interested in
//	case-insensitive std::strings.
/////////////////////////////////////////////////////////////////////////////
//
#ifndef STRINGICMP__H__INCLUDED
#define STRINGICMP__H__INCLUDED

#include <string>
#include <cctype>
#include <algorithm>
#include <functional>

#ifdef _MSC_VER
#    define for if(0);else for
#    pragma warning(disable:4786)
#    define NO_CASE_COMPARE_HAS_LOCALE
#    define NO_CASE_COMPARE_HAS_FACETS
#    define NO_CASE_COMPARE_HAS_CHAR_TRAITS
namespace std
{
  inline int toupper( int c )
  {
    return ::toupper(c);
  }
  typedef size_t size_t;
}
#endif

#ifdef NO_CASE_COMPARE_HAS_LOCALE
#include <locale>
#endif

#ifdef NO_CASE_COMPARE_HAS_FACETS
const std::ctype<char>& My_Use_Facet(const std::locale& loc)
{
#ifdef _MSC_VER
  return std::use_facet(loc, (std::ctype<char>*)0, true);
#else
  return std::use_facet<std::ctype<char> >(loc);
#endif
}
#endif

// Typen und Funktionen für den case-insensitiven Stringvergleich.
// Die Namen Typen/Funktionen die ein locale-Objekt erwarten
// besitzen das Präfix Loc.
//
// Für jeden Vergleichstyp existiert zusätzlich eine Vergleichsfunktion.
namespace IgnoreCase
{
  struct CharCmp_t : std::binary_function<char, char, bool>
    {
      int operator() (char ch1, char ch2) const
      {
        int Left = tolower(static_cast<unsigned char>(ch1));
        int Right = tolower(static_cast<unsigned char>(ch2));
        if (Left < Right) return -1;
        return Left > Right ? 1 : 0;
      }
    };

  struct CharLess_t : std::binary_function<char, char, bool>
    {
      bool operator() (char ch1, char ch2) const
      {
        return  tolower(static_cast<unsigned char>(ch1)) <
          tolower(static_cast<unsigned char>(ch2));
      }
    };

  struct CharEq_t : std::binary_function<char, char, bool>
    {
      bool operator() (char ch1, char ch2) const
      {
        return  tolower(static_cast<unsigned char>(ch1)) ==
          tolower(static_cast<unsigned char>(ch2));
      }
    };

  // Liefert true, falls Str1 == Str2
  struct NoCaseEqual_t : std::binary_function<std::string, std::string, bool>
    {
      bool operator () ( const std::string& Str1, const std::string& Str2) const
      {
        if (Str1.length() != Str2.length())
          return false;
        return std::equal(Str1.begin(), Str1.end(), Str2.begin(), CharEq_t());
      }
    };

  bool NoCaseEqual(const std::string& Str1, const std::string& Str2)
  {
    return NoCaseEqual_t()(Str1, Str2);
  }

  // Liefert true, falls Str1 lexikographisch kleiner als Str2 ist.
  struct NoCaseLess_t : std::binary_function<std::string, std::string, bool>
    {
      bool operator () (const std::string& Str1, const std::string& Str2) const
      {
        return std::lexicographical_compare(    Str1.begin(), Str1.end(),
                                                Str2.begin(), Str2.end(),
                                                CharLess_t());
      }
    };

  bool NoCaseLess(const std::string& Str1, const std::string& Str2)
  {
    return NoCaseLess_t()(Str1, Str2);
  }

  // Liefert -1, falls Str1 lexikographisch kleiner als Str2 ist,
  // 0 falls die Strings gleich sind und 1 sonst.
  struct NoCaseCmp_t : std::binary_function<std::string, std::string, bool>
    {
      int operator () (const std::string& Str1, const std::string& Str2) const
      {
        // Sicherstellen, dass der längere String als zweiter Parameter
        // an mismatch übergeben wird.
        // Falls Str1 und Str2 vertauscht werden, muss das Ergebnis mit
        // -1 malgenommen werden.
        const std::string* Shorter = &Str1;
        const std::string* Longer = &Str2;
        int Faktor = 1;
        if (Str1.length() > Str2.length())
          {
            Shorter = &Str2;
            Longer = &Str1;
            Faktor = -1;
          }
        typedef std::pair< std::string::const_iterator,
          std::string::const_iterator> PairStrCi;

        PairStrCi Result = std::mismatch(Shorter->begin(), Shorter->end(),
                                         Longer->begin(), std::not2(CharCmp_t()));


        // Mismatch liefert ein Iteratorpaar welches die ersten beiden
        // Zeichen markiert, die sich unterscheiden.
        // Falls es kein solches Zeichen gibt, liefert mismatch jeweils
        // die End-Iteratoren.
        if (Result.first == Shorter->end())
          {
            if (Result.second == Longer->end())
              { // Strings sind gleich
                return 0;
              }
            else
              { // Der erste String war kürzer als der zweite.
                // Falls wir die Eingabestrings nicht vertauscht haben,
                // liefern wir -1, sonst 1, da der erste String dann
                // ja länger war als der Zweite.
                return -Faktor;
              }
          }
        return Faktor * CharCmp_t()(*Result.first, *Result.second);
      }
    };

  int NoCaseCmp(const std::string& Str1, const std::string& Str2)
  {
    return NoCaseCmp_t()(Str1, Str2);
  }

#ifdef NO_CASE_COMPARE_HAS_LOCALE
  const char* CreateCharTable(const std::locale& loc)
  {
    static char CHAR_TABLE[CHAR_MAX - CHAR_MIN + 1];
    static bool Init = false;
    if (!Init)
      {

#ifdef NO_CASE_COMPARE_USE_FACETS
        for (int i = CHAR_MIN; i <= CHAR_MAX ; ++i)
          CHAR_TABLE[i - CHAR_MIN] = char(i);

        static const std::ctype<char>& Fac = My_Use_Facet(loc);
        Fac.tolower(CHAR_TABLE, CHAR_TABLE + (CHAR_MAX - CHAR_MIN + 1));
#else
        for (int i = CHAR_MIN; i <= CHAR_MAX ; ++i)
          CHAR_TABLE[i - CHAR_MIN] = std::tolower(char(i), loc);
#endif
      }
    return CHAR_TABLE;
  }

  struct LocTableCharLess_t : std::binary_function<char, char, bool>
    {
    LocTableCharLess_t(const std::locale& loc = std::locale::classic())
      : m_Loc(loc)
      {}
      bool operator() (char ch1, char ch2) const
      {
        const char* Tab = CreateCharTable(m_Loc);
        return Tab[ch1 - CHAR_MIN] < Tab[ch2 - CHAR_MIN];
      }
    private:
      const std::locale& m_Loc;
    };

  struct LocTableCharEq_t : std::binary_function<char, char, bool>
    {
    LocTableCharEq_t(const std::locale& loc = std::locale::classic())
      : m_Loc(loc)
      {}
      bool operator() (char ch1, char ch2) const
      {
        const char* Tab = CreateCharTable(m_Loc);
        return Tab[ch1 - CHAR_MIN] == Tab[ch2 - CHAR_MIN];
      }
    private:
      const std::locale& m_Loc;
    };

  struct LocCharLess_t : std::binary_function<char, char, bool>
    {
    LocCharLess_t(const std::locale& loc = std::locale::classic())
      : m_Loc(loc)
#ifdef NO_CASE_COMPARE_HAS_FACETS
        , m_Ct(My_Use_Facet(m_Loc))
#endif
        {}
      bool operator() (char ch1, char ch2) const
      {
#ifdef NO_CASE_COMPARE_HAS_FACETS
        return m_Ct.tolower(ch1) < m_Ct.tolower(ch2);
#else
        return std::tolower(ch1, m_Loc) <
          std::tolower(ch2, m_Loc);
#endif
      }
    private:
      const std::locale& m_Loc;
#ifdef NO_CASE_COMPARE_HAS_FACETS
      const std::ctype<char>& m_Ct;
#endif

    };

  struct LocCharEq_t : std::binary_function<char, char, bool>
    {
    LocCharEq_t(const std::locale& loc = std::locale::classic())
      : m_Loc(loc)
#ifdef NO_CASE_COMPARE_HAS_FACETS
        , m_Ct(My_Use_Facet(m_Loc))
#endif
        {}

      bool operator() (char ch1, char ch2) const
      {
#ifdef NO_CASE_COMPARE_HAS_FACETS
        return m_Ct.tolower(ch1) == m_Ct.tolower(ch2);
#else
        return std::tolower(ch1, m_Loc) ==
          std::tolower(ch2, m_Loc);
#endif
      }
    private:
      const std::locale& m_Loc;
#ifdef NO_CASE_COMPARE_HAS_FACETS
      const std::ctype<char>& m_Ct;
#endif
    };

  struct LocNoCaseEqual_t : std::binary_function<std::string, std::string, bool>
    {
    LocNoCaseEqual_t(const std::locale& loc = std::locale::classic()) : m_Loc(loc) {}

      bool operator () (const std::string& Str1, const std::string& Str2) const
      {
        if (Str1.length() != Str2.length())
          return false;
        return std::equal( Str1.begin(),
                                Str1.end(), Str2.begin(),
                                LocCharEq_t(m_Loc));
      }
    private:
      const std::locale& m_Loc;
    };

  bool LocNoCaseEqual(const std::string& Str1, const std::string& Str2, const std::locale& loc)
  {
    return LocNoCaseEqual_t(loc)(Str1, Str2);
  }

  struct LocNoCaseLess_t : std::binary_function<std::string, std::string, bool>
    {
    LocNoCaseLess_t(const std::locale& loc = std::locale::classic()) : m_Loc(loc) {}

      bool operator () (const std::string& Str1, const std::string& Str2) const
      {
        return std::lexicographical_compare( Str1.begin(), Str1.end(),
                                                Str2.begin(), Str2.end(),
                                                LocCharLess_t(m_Loc));
      }
    private:
      const std::locale& m_Loc;
    };

  bool LocNoCaseLess(const std::string& Str1, const std::string& Str2, const std::locale& loc)
  {
    return LocNoCaseLess_t(loc)(Str1, Str2);
  }

  struct LocNoCaseCmp_t : std::binary_function<std::string, std::string, bool>
    {
    LocNoCaseCmp_t(const std::locale& loc = std::locale::classic()) : m_Loc(loc) {}

      int operator () (const std::string& Str1, const std::string& Str2) const
      {
        if (LocNoCaseLess_t(m_Loc)(Str1, Str2))
          return -1;
        return LocNoCaseEqual_t(m_Loc)(Str1, Str2) == true ? 0 : 1;
      }

    private:
      const std::locale& m_Loc;
    };

  int LocNoCaseCmp(const std::string& Str1, const std::string& Str2, const std::locale& loc)
  {
    return LocNoCaseCmp_t(loc)(Str1, Str2);
  }

  struct LocTableNoCaseEqual_t : std::binary_function<std::string, std::string, bool>
    {
    LocTableNoCaseEqual_t(const std::locale& loc = std::locale::classic()) : m_Loc(loc) {}

      bool operator () (const std::string& Str1, const std::string& Str2) const
      {
        if (Str1.length() != Str2.length())
          return false;
        return std::equal( Str1.begin(), Str1.end(),
                                Str2.begin(), LocTableCharEq_t(m_Loc));
      }
    private:
      const std::locale& m_Loc;
    };

  bool LocTableNoCaseEqual(const std::string& Str1, const std::string& Str2, const std::locale& loc)
  {
    return LocTableNoCaseEqual_t(loc)(Str1, Str2);
  }

  struct LocTableNoCaseLess_t : std::binary_function<std::string, std::string, bool>
    {
    LocTableNoCaseLess_t(const std::locale& loc = std::locale::classic()) : m_Loc(loc) {}

      bool operator () (const std::string& Str1, const std::string& Str2) const
      {
        return std::lexicographical_compare( Str1.begin(), Str1.end(),
                                                Str2.begin(), Str2.end(),
                                                LocTableCharLess_t(m_Loc));
      }
    private:
      const std::locale& m_Loc;
    };

  bool LocTableNoCaseLess(const std::string& Str1, const std::string& Str2, const std::locale& loc)
  {
    return LocTableNoCaseLess_t(loc)(Str1, Str2);
  }

  struct LocTableNoCaseCmp_t : std::binary_function<std::string, std::string, bool>
    {
    LocTableNoCaseCmp_t(const std::locale& loc = std::locale::classic()) : m_Loc(loc) {}

      int operator () (const std::string& Str1, const std::string& Str2) const
      {
        if (LocTableNoCaseLess_t(m_Loc)(Str1, Str2))
          return -1;
        return LocTableNoCaseEqual_t(m_Loc)(Str1, Str2) == true ? 0 : 1;
      }

    private:
      const std::locale& m_Loc;
    };

  int LocTableNoCaseCmp(const std::string& Str1, const std::string& Str2, const std::locale& loc)
  {
    return LocTableNoCaseCmp_t(loc)(Str1, Str2);
  }
#endif

#ifdef NO_CASE_COMPARE_HAS_CHAR_TRAITS
  // Eine neuer char-traits Typ für basic_string
  // Diese char-traits ignorieren Unterschiede bezüglich Groß-/Kleinschreibung

  struct NoCaseCharTraits : public std::char_traits<char>
  {
    // Prüfe zwei Zeichen auf Gleichheit
    static bool eq (char ch1, char ch2)
    {
      return std::toupper(ch1) == std::toupper(ch2);
    }

    // less then - kleiner als
    static bool lt (char ch1, char ch2)
    {
      return std::toupper(ch1) < std::toupper(ch2);
    }

    // liefert -1, wenn str1 lexicographisch kleiner als str2 ist.
    // 0, wenn str1 und str2 lexicographisch gleich sind und
    // 1, wenn str1 lexicographisch größer als str2 ist.
    static int compare (const char* str1, const char* str2, std::size_t n)
    {
      for (std::size_t i = 0 ; i < n ; i++)
        {
          if (!eq(str1[i], str2[i]))
            {
              return lt (str1[i], str2[i]) ? -1 : 1;
            }
        }
      return 0;
    }

    // sucht ch in str
    static const char* find(const char* str, std::size_t n, char ch)
    {
      for (std::size_t i = 0; i < n ; i++)
        {
          if (eq(str[i], ch))
            {
              return &str[i];
            }
        }
      return 0;
    }
  };

  typedef std::basic_string<char, IgnoreCase::NoCaseCharTraits> CIString;
#endif
}

#endif
