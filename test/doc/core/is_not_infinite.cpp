#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.5f, -2.0f, -123.345f,
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                          = " << pf << '\n'
            << "-> is_not_infinite(pf)         = " << eve::is_not_infinite(pf) << '\n'
            << "-> is_not_infinite[pf > 0](pf) = " << eve::is_not_infinite[pf > 0](pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                  = " << xf << '\n'
            << "-> is_not_infinite(xf) = " << eve::is_not_infinite(xf) << '\n';
  return 0;
}
