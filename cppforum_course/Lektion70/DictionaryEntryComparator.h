// DictionaryEntryComparator.h
/*
//*/

#ifndef DICTIONARYENTRYCOMPARATOR
#define DICTIONARYENTRYCOMPARATOR

#include "DictionaryEntry.h"

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

#endif
