//#include <iostream>

//using namespace std;

class Hello
{
private:
	int var;

public:
	Hello()
	{
		var = 7;
	}

	void print_var()
	{
		var += 99;
	//	cout << var << "\n";
	}
};

int main( int argc, char**argv){
	Hello hello;
	hello.print_var();
	return 0;
}

