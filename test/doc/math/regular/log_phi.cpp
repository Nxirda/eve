#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_log_phi() { return eve::log_phi(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> log_phi(as<wide_ft>())                 = " << eve::log_phi(eve::as<wide_ft>())                << std::endl
            << "-> log_phi(as(wxf))                       = " << eve::log_phi(eve::as(wxf))                      << std::endl
            << "-> log_phi[upward](as<wide_ft>())         = " << eve::log_phi[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> log_phi[upward](as(wxf))               = " << eve::log_phi[eve::upward](eve::as(wxf))         << std::endl
            << "-> log_phi[downward](as<wide_ft>())       = " << eve::log_phi[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> log_phi[downward](as(wxf))             = " << eve::log_phi[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> log_phi(as<wide_dt>())           = " << eve::log_phi(eve::as<wide_dt>())                << std::endl
            << "-> log_phi(as(wxd))                 = " << eve::log_phi(eve::as(wxd))                      << std::endl
            << "-> log_phi[upward](as<wide_dt>())   = " << eve::log_phi[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> log_phi[upward](as(wxd))         = " << eve::log_phi[eve::upward](eve::as(wxd))         << std::endl
            << "-> log_phi[downward](as<wide_dt>()) = " << eve::log_phi[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> log_phi[downward](as(wxd))       = " << eve::log_phi[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> log_phi(as<float>())             = " << eve::log_phi(eve::as(float())) << std::endl
            << "-> log_phi(as<xf))                  = " << eve::log_phi(eve::as(xf))      << std::endl
            << "-> log_phi(as<double>())            = " << eve::log_phi(eve::as(double()))<< std::endl
            << "-> log_phi(as<xd))                  = " << eve::log_phi(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr log_phi            = " << constexpr_log_phi<float>() << std::endl;

  return 0;
}
