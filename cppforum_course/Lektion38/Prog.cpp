// Prog.cpp
/*
  const-Referenzen
  pass-by-reference, der Geschwindigkeitsvorteile bringt, da nicht jedes
  mal pro Funktion eine neue Kopie erstellt werden muss. Damit diese dann
  nicht veraendert werden kann, wie bei call-by-value gibt es die const 
  Referenzen.
//*/

#include <iostream>
using namespace std;

class Student
{
private:
    string vorname;
    string name;
    string strasse;
    string hausnummer;
    string postleitzahl;
    string ort;
    string hochschulort;
    string hochschule;
    string matrikelnummer;
    string semesteranzahl;
// ...

public:
    string getName()
        {
            return name;
        };
    string getVorname()
        {
            return vorname;
        };
// ...
};

void printStudent(const Student &student)
{
    cout << student.getVorname() << ' ' << student.getName() << endl;
};

