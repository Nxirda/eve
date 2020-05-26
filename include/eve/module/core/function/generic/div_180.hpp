//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_DIV_180_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_DIV_180_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/function/fma.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T div_180_(EVE_SUPPORTS(cpu_)
                                       , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      using elt_t = element_type_t<T>;
      if constexpr(std::is_same_v<elt_t, double>)
      {
        const T Ch = T(5.5555555555555557675773137304986448725685477256775e-3);
        const T Cl = T(-2.12021758174943082362265970771770243087787985109985e-19);
        T c = Cl*a;
        return fma(a, Ch, c);
      }
      else
      {
        const T Ch =  T(0.00555555569007993f);
        const T Cl =  T(-1.34524377748413e-10);
        T c = Cl*a;
        return fma(a, Ch, c);
      }
    }
    else return apply_over(div_180, a);
  }
}

#endif
