//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

#include <type_traits>

namespace eve::detail
{
  template<unsigned_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> countl_zero_(EVE_REQUIRES(neon128_),
                                          O          const& ,
                                          wide<T, N> const& a0) noexcept
  requires arm_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if      constexpr( c == category::uint32x4 ) return vclzq_u32(a0);
    else if constexpr( c == category::uint32x2 ) return vclz_u32(a0);
    else if constexpr( c == category::uint16x8 ) return vclzq_u16(a0);
    else if constexpr( c == category::uint16x4 ) return vclz_u16(a0);
    else if constexpr( c == category::uint8x16 ) return vclzq_u8(a0);
    else if constexpr( c == category::uint8x8  ) return vclz_u8(a0);
    else return map(countl_zero, a0);
  }
}
