// Dictionary.h
/*
//*/

#ifndef DICTIONARY
#define DICTIONARY

#include "SortedArray.h"

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


template< class KEY, class VALUE, class KEY_COMPARATOR >
class DictionaryEntryComparator
{
private:
    KEY_COMPARATOR m_comp;
    
public:
    bool lessThan(const DictionaryEntry< KEY, VALUE > &a, const DictionaryEntry< KEY, VALUE > &b)
    {
        return m_comp.lessThan(a.getKey(), b.getKey());
    };
    

    bool isEqual(const DictionaryEntry< KEY, VALUE > &a, const DictionaryEntry< KEY, VALUE > &b)
    {
        return m_comp.isEqual(a.getKey(), b.getKey());
    };
};


template< class KEY, class VALUE, class KEY_COMPARATOR = DefaultComparator<KEY> >
class Dictionary
{
private:
    SortedArray< DictionaryEntry< KEY, VALUE >
                 , DictionaryEntryComparator< KEY, VALUE, KEY_COMPARATOR > > m_data;  

public:
    void insert(const KEY &key, const VALUE &value)
    {
        m_data.insert(DictionaryEntry< KEY, VALUE >(key, value));
    };
    

    int getSize()
    {
        return m_data.getSize();
    };
    

    const DictionaryEntry< KEY, VALUE > &operator[](int index)
    {
        return m_data[index];
    };
};

#endif
