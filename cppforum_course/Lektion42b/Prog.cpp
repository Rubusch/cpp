// Prog.cpp
/*
  Stack as vector - mit einigen dynamischen Funktionsanwendungen.
//*/

#include <iostream>
#include <assert.h>
using namespace std;

class StackAsVector
{
private:
    int *data;
    int topIndex;
    int max;
    // um wieviel soll das Array vergroessert werden
    static const int ERHOEHEN_UM = 10;

public:
    StackAsVector(int startgroesse)
    {
        max = startgroesse;
        data = new int[max];
        topIndex = -1;
    };
    

    ~StackAsVector()
    {
        delete [] data;
    };

    
    void push(int wert)
    {
        // Pruefen ob die Obergrenze erreicht wurde
        ++topIndex;
        if(topIndex == max)
        {
            // wenn ja dann alte Daten zwischenspeichern
            int *tmp = data;
            
            // Obergrenze um ERHOEHEN_UM erhoehen
            max += ERHOEHEN_UM;
            
            // neues um ERHOEHEN_UM groesseres Array anlegen
            data = new int[max];
            
            // alte Daten ins groessere Array einlesen
            for(int i=0;i<topIndex; ++i)
                data[i] = tmp[i];

            // alte Daten loeschen
            delete [] tmp;
        }

        data[topIndex] = wert;
    };
    

    // das oberste Element lesen
    int top()
    {
        assert(topIndex!=-1);
        return data[topIndex];
    };
    

    // das oberste Element entfernen
    void pop()
    {
        assert(topIndex != -1);
        --topIndex;
    };
    

    // ist der Stack leer?
    bool isEmpty()
    {
        return topIndex == -1;
    };
    

    // Stack leeren
    void empty()
    {
        delete [] data;
        topIndex = -1;
        max = ERHOEHEN_UM;
        data = new int[max];
    };
    

    // wieviele Elemente liegen auf dem Stack
    int size()
    {
        return topIndex +1;
    };
    

    // Element an einer bestimmten Stelle zurueckgeben (kein klassischer heap)
    int elementAt(int nr)
    {
        assert(nr <= topIndex);
        return data[nr];
    };
    

    // Element an einer bestimmten Stelle setzen (kein klassischer heap)
    void setElementAt(int nr, int wert)
    {
        if(nr > topIndex)
        {
            // wenn ja, dann alte Daten zwischenspeichern
            int *tmp = data;
            
            max = nr + ERHOEHEN_UM;
            
            // neues groesseres Array anlegen
            data = new int[max];
            
            // alte Daten ins groessere Array einlesen
            for(int i=0;i<topIndex;++i)
                data[i]=tmp[i];
            
            // alte Daten loeschen
            delete [] tmp;
        }
        
        data[nr] = wert;
        topIndex = nr;
    };
    

    // Element an einer bestimmten Stelle loeschen
    void remove(int nr)
    {
        assert(nr <= topIndex);
        
        // Daten ohne das zu loeschende Element zwischenspeichern
        int tmp[topIndex];
        for(int i=0; i<nr; ++i)
            tmp[i]=data[i];
        for(int i=nr+1; i<topIndex; ++i)
            tmp[i-1]=data[i];
        
        // ein Element wurde geloescht
        --topIndex;
        
        // das alte Array loeschen
        delete [] data;
        
        // neues Array anlegen, dass um ERHOEHEN_UM groesser ist als benoetigt
        max = topIndex + ERHOEHEN_UM;
        data = new int[max];
        
        // neue Daten einlesen
        for(int i=0; i<=topIndex; ++i)
            data[i]=tmp[i];
    };
};


void printDaten(StackAsVector& stack, int anfang, int ende)
{
    cout << "Inhalt des Stacks von " << anfang << " bis " << ende-1 << ": ";
    for(int i=anfang; i<ende; ++i)
        cout << stack.elementAt(i) << ", ";
    cout << endl;
};


int main()
{
    StackAsVector stack(5);
    
    for(int i=0; i<9; ++i)
        stack.push(i*3);
    
    printDaten(stack, 0, stack.size());
    
    stack.empty();
    
    for(int i=0; i<20; ++i)
        stack.push(i*i);
    
    printDaten(stack, 0, stack.size());
    
    cout << endl << "Element an der Stelle 15: " << stack.elementAt(15) << 
        ", Groesse des Stacks: " << stack.size() << endl;
    
    stack.remove(15);
    
    cout << "Neues Element an der Stelle 15: " << stack.elementAt(15) << 
        ", Groesse des Stacks: " << stack.size() << endl;
    cout << "Letztes Element: " << stack.top() << endl;
    printDaten(stack, 0, stack.size());
    
    for(int i=0; i<2000; ++i)
        stack.push(i);
    
    cout << "Neue Groesse des Stacks: " << stack.size() << endl;
    printDaten(stack, 0, 40);
    
    stack.setElementAt(4000, 87);
    cout << "Element bei Stelle 4000: " << stack.elementAt(4000) << endl;
    cout << "Groesse: " << stack.size() << endl;
    
    printDaten(stack, 10, 60);

    cout << "Element zu weit draussen: " << stack.elementAt(4005) << endl;
};

    

