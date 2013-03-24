// Start.cpp
#include "Start.h"

class Start
{
public:
    void startme() 
    {
        cout<<"class Start"<<endl;
    };
};

// main method
int main()
{
    cout << "main()" << endl;
    
    Start a;
    a.startme();
    
    return 0; 
};
