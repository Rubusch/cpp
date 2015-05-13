// DictionaryEntry.h
/*
//*/

#ifndef DICTIONARYENTRY
#define DICTIONARYENTRY

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


    const KEY &getKey()
    {
        return m_key;
    };
    

    VALUE &getValue()
    {
        return m_value;
    };
};

#endif
