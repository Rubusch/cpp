// innerproxy.cpp
/*
  Provide a surrogate or placeholder for another object to control access to it.

  We will see the code for this in a moment, but first it is important to understand the 
  proxies we'll be using. There are only three things you can do with a proxy:

  - Create it, i.e., specify which string character it stands for.
  
  - Use it as the target of an assignment, in which case you are really making an 
  assignment to the string character it stands for. When used in this way, a proxy 
  represents an lvalue use of the string on which operator[] was invoked. 
  
  - Use it in any other way. When used like this, a proxy represents an rvalue use 
  of the string on which operator[] was invoked.

  Here are the class definitions for a reference-counted String class using a proxy 
  class to distinguish between lvalue and rvalue usages of operator[]


  (Gang of Four), (More Effective C++ / 30 / Meyers)
//*/

#include <iostream>
#include <cstdlib>

using namespace std;


template<class T>
class Matrix_2D
{
private:
  T **ppMatrix; // the "real" 2D array (here pointer to pointer)
  int maxx_;
  int maxy_;

  /*
    The inner class serves as proxy - the data will be accessed via the proxy    
    In this case it is necessary since there is no "operator[][]".

    The proxy implements only the interface necessary!
  //*/
  class Proxy 
  {
  private:
    int x_coord;
    const Matrix_2D<T>* pSubject;
    
  public:
    Proxy(const Matrix_2D<T>& matrix, const int x);

    // 2. call - they actually return the element stored in the "real subject"
    const T& operator[](int y_coord) const;
    T& operator[](int y_coord);
  };

public:
  /*
    some idividual exception - this is optional and can be also a catch(...)
  //*/
  class BadProxyException : public exception
  {
  private:
    string message;
  public:
    BadProxyException(string msg) : message(msg) {}
    ~BadProxyException() throw() {}
    const char* whatchamecallit() const throw()
    { return message.c_str(); }
  };

  /*
    Matrix_2D<T> stuff
  //*/
  Matrix_2D(const int max_x, const int max_y, const T& dummy)
    throw(BadProxyException);
  ~Matrix_2D();
  
  // 1. call, they return a proxy, 
  const Proxy operator[](int x) const;
  Proxy operator[](int x);
};


/*-----------------------------------------------------------------------------------*/


/* 
   proxy function definitions
//*/

template<class T>
Matrix_2D<T>::Proxy::Proxy(const Matrix_2D<T>& matrix, const int x)
  : x_coord(x)
  , pSubject(NULL)
{
  pSubject = &matrix;
}


template<class T>
const T& Matrix_2D<T>::Proxy::operator[](int y_coord) const
{
  return pSubject->ppMatrix[x_coord][y_coord];
}


template<class T>
T& Matrix_2D<T>::Proxy::operator[](int y_coord)
{
  return pSubject->ppMatrix[x_coord][y_coord];
}


/*-----------------------------------------------------------------------------------*/


/*
  "real subject's" definitions"
//*/

template<class T>
Matrix_2D<T>::Matrix_2D(const int max_x, const int max_y, const T& dummy)
  throw(Matrix_2D<T>::BadProxyException)
  :ppMatrix(NULL), maxx_(max_x), maxy_(max_y)
{

  // alloc 1. dimension
  if(NULL == (ppMatrix = new (nothrow) T*[maxx_])){
    throw BadProxyException("Allocation of first dimension failed!");
    return;
  }

  // alloc 2. dimension
  for(int idx=0; idx<maxx_; ++idx){
    if(NULL == (ppMatrix[idx] = new (nothrow) T[maxy_])){
      throw BadProxyException("Allocation of second dimension failed!");
      return;
    }     

    // init
    for(int jdx=0; jdx<maxy_; ++jdx){
      ppMatrix[idx][jdx] = dummy;
    }
  }
}


template<class T>
Matrix_2D<T>::~Matrix_2D()
{
  // delete 1. dimension
  for(int idx=0; idx<maxx_; ++idx){
    delete[] ppMatrix[idx]; ppMatrix[idx] = NULL;
  }
  
  // delete 2. dimension
  delete[] ppMatrix; ppMatrix = NULL;
}


/*
  interface to the proxy
//*/
template<class T>
const typename Matrix_2D<T>::Proxy Matrix_2D<T>::operator[](int x) const
{
  return Matrix_2D<T>::Proxy(const_cast< Matrix_2D<T>& >(*this), x);
}


template<class T> 
typename Matrix_2D<T>::Proxy Matrix_2D<T>::operator[](int x)
{
  return typename Matrix_2D<T>::Proxy(*this, x);
}


/*-----------------------------------------------------------------------------------*/


/*
  some main
//*/
int main()
{
  // init
  int maxx = 10, maxy = 20;

  cout << "init.." << endl;
  try{
    Matrix_2D<string> data(maxx, maxy, "xxx");

    /*
      This normally shouldn't be possible since "data" is instantiated only 
      as object. Through the proxy class the index usage becomes easily 
      available - returned will be only one value, here!
    //*/
    for(int idx=0; idx<maxx; ++idx){
      for(int idy=0; idy<maxy; ++idy){
        cout << "\"" << data[idx][idy] << "\" ";
      }
      cout << endl;
    }
    cout << endl;

  }catch(Matrix_2D<string>::BadProxyException exp){
    cout << exp.whatchamecallit() << endl;
    exit(-1);
  }
  cout << "READY.\n";
  return 0;
}
