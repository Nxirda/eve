#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf           = " << pf << '\n'
            << "-> dec[pf > 0.0f](pf)       = " << eve::dec[pf > 0.0f](pf) << '\n';
  return 0;
}