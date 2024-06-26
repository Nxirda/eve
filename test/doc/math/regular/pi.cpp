#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_pi() { return eve::pi(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> pi(as<wide_ft>())        = " << eve::pi(eve::as<wide_ft>())            << std::endl
            << "-> pi(as(wxf))              = " << eve::pi(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> pi(as<float>())         = " << eve::pi(eve::as(float())) << std::endl
            << "-> pi(as<xf))              = " << eve::pi(eve::as(xf))      << std::endl;


  std::cout << "-> constexpr pi            = " << constexpr_pi<float>() << std::endl;

  return 0;
}
