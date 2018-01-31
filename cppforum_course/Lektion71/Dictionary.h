// Dictionary.h
/*
//*/

#ifndef DICTIONARY
#define DICTIONARY

#include "SortedArray.h"
#include "DictionaryEntry.h"
#include "DictionaryEntryComparator.h"

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
