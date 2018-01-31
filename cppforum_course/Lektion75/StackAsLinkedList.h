// StackAsLinkedList.h
/*
//*/

#ifndef STACK_AS_LINKED_LIST
#define STACK_AS_LINKED_LIST

#include <iostream>
using namespace std;

#include <assert.h>

template<class T>
class StackAsLinkedList
{
    template<class T>
    class Element
    {
    public:
        T m_wert;
        Element *m_pNaechstesElement;
    };

private:
    Element<T> *m_pStart;

public:
    StackAsLinkedList()
    {
        m_pStart = 0;
    };


    void push(int wert)
    {
        Element *pNeuesElement = new Element;
        pNeuesElement->m_wert = wert;
        pNeuesElement->m_pNaechstesElement = m_pStart;
        m_pStart = pNeuesElement;
    };


    void pop()
    {
        Element *pZuLoeschendesElement = m_pStart;
        m_pStart = m_pStart->m_pNaechstesElement;
        delete pZuLoeschendesElement;
    };


    int top()
    {
        return m_pStart->m_wert;
    };


    bool empty()
    {
        return m_pStart == 0;
    };
};

#endif
