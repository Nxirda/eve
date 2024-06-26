#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_log10_e() { return eve::log10_e(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> log10_e(as<wide_ft>())       = " << eve::log10_e(eve::as<wide_ft>())            << std::endl
            << "-> log10_e(as(wxf))             = " << eve::log10_e(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> log10_e(as<float>())         = " << eve::log10_e(eve::as(float())) << std::endl
            << "-> log10_e(as<xf))              = " << eve::log10_e(eve::as(xf))      << std::endl;


  std::cout << "-> constexpr log10_e            = " << constexpr_log10_e<float>() << std::endl;

  return 0;
}
