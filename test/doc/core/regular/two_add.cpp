#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using wf_t = eve::wide<float, eve::fixed<4>>;
  wf_t pf = {3, 2.5, -32.7, 1.0}, qf = {4.2, 1.5, -100.834, eve::eps(eve::as<float>())/2};
  auto [s, eps] = eve::two_add(pf, qf);
  std::cout << "---- simd" << '\n'
            << " <- pf          = " << pf << '\n'
            << " <- qf          = " << qf << '\n'
            << " -> {s, eps] = two_add(pf, qf)\n"
            << " -> s           = " << s << '\n'
            << " -> eps         = " << eps << '\n';
  return 0;
}
