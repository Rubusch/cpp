// complex.cpp
/*
  complex numbers example

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <complex>
#include <iomanip>


/*
  solves an equation and presents the - in case - complex result
//*/
void solve_equation(double val_a, double val_b, double val_c, double val_d)
{
  std::cout << "solve equation:\n"
            << val_a << "*x*x "
            << std::setiosflags(std::ios::showpos)
            << val_b << "*x "
            << val_c << " = " << std::resetiosflags(std::ios::showpos)
            << val_d;

  // temp values
  const double tmp_p = val_b / val_a;
  const double tmp_q = (val_c - val_d) / val_a;

  // solving
  const std::complex< double > cmx_r = (tmp_p * tmp_p / 4) - tmp_q;
  const std::complex< double > cmx_x1 = sqrt(cmx_r) - (tmp_p / 2);
  const std::complex< double > cmx_x2 = - (sqrt(cmx_r) + (tmp_p / 2));

  // result
  if(cmx_x1 != cmx_x2){
    std::cout << "\nresults: x1 = " << cmx_x1 << " [real, imaginative] and x2 = "
              << cmx_x2 << " [real, imaginative]" << std::endl;
  }else{
    std::cout << "\nresult: x = " << cmx_x1 << " [real, imaginative]" << std::endl;
  }
  std::cout << std::endl;
}

/*
  main..
//*/
int main()
{
  using namespace std;

  solve_equation(2, 2, -3, 1);
  solve_equation(1, -2, 1, 0);
  solve_equation(1, 2, 2, 0);

  cout << "READY.\n";
  return 0;
}
