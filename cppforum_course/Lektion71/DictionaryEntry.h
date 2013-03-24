// DictionaryEntry.h
/*
  Verwendung von const Funktionen (getkey)
//*/

#ifndef DICTIONARY_ENTRY
#define DICTIONARY_ENTRY

template< class KEY, class VALUE > 
class DictionaryEntry
{
private:
    KEY m_key;
    VALUE m_value;
    
public:
    DictionaryEntry()
    {};
    

    DictionaryEntry(const KEY &key, const VALUE &value)
        :m_key(key), m_value(value)
    {};


    const KEY &getKey() const
    {
        return m_key;
    };
    

    VALUE &getValue() const
    {
        return const_cast<VALUE&>(m_value);
    };
};

#endif
