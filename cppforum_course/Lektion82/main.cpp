// main.cpp
/*
//*/

#include <iostream>
#include <fstream>
using namespace std;


bool range(char a,char b,char c) 
{
    return a<=b && b<=c;
};


bool islower(char ch) 
{
    return range('a',ch,'z');
};


bool isupper(char ch) 
{
    return range('A',ch,'Z');
};


bool isalpha(char ch) 
{
    return islower(ch) || isupper(ch);
};


char dazuaddieren(char ch,char key) 
{
    if(isupper(ch))
    {
        ch+=key;
        if(ch>'Z')
            ch-=26;
    }
    else if(islower(ch))
    {
        ch+=key;
        if(ch>'z')
            ch-=26;
    }
    return ch;
};


char crypt(char ch,char key) {   //verschlüsseln
    if(isalpha(ch)) 
        return dazuaddieren(ch,key); //if ch==buchstabe dann key zu ch addieren
    else
        return ch;      //sonst ch gleichlassen
};


int main()
{
    ifstream in("encrypt.txt");  //txt-datei im selben verzeichnis
    ofstream out("decrypted.txt"); //output datei im selven verzeichnis
    int key;
    cout<<"Bitte zuerst key eingeben: ";
    cin>>key;
    
    char aktion;
    cout<<"\nwillst du (v)erschluesseln oder (e)ntschluesseln?"<<endl;
    cin>>aktion;
    cout<<endl;
    
    char ch=in.get();
    
    if(aktion=='e')   //wenn man entschluesseln wählt, wird der key umgerechnet
        key=26-key;
    
    while(!in.eof()) {
        ch=crypt(ch,key);
        out<<ch;   //output in obige datei
        cout<<ch;   //output auf bildschirm
        ch=in.get();
    };
    cout<<"\n"<<endl;

    return 0;
};
