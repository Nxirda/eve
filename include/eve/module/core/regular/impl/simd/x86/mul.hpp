//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::detail
{
  template<conditional_expr C, typename T, typename N, callable_options O>
  EVE_FORCEINLINE
  wide<T, N> mul_(EVE_REQUIRES(avx512_), C cx, O const& opts, wide<T, N> v, wide<T, N> w) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    auto src = alternative(cx, v, as<wide<T, N>> {});
    auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

    if constexpr(O::contains(saturated2) && integral_value<T>)
    {
      return mul.behavior(cpu_{}, opts, v, w);
    }
    else
    {
      if      constexpr( c == category::float32x16) return _mm512_mask_mul_ps   (src, m, v, w);
      else if constexpr( c == category::float32x8 ) return _mm256_mask_mul_ps   (src, m, v, w);
      else if constexpr( c == category::float32x4 ) return _mm_mask_mul_ps      (src, m, v, w);
      else if constexpr( c == category::float64x8 ) return _mm512_mask_mul_pd   (src, m, v, w);
      else if constexpr( c == category::float64x4 ) return _mm256_mask_mul_pd   (src, m, v, w);
      else if constexpr( c == category::float64x2 ) return _mm_mask_mul_pd      (src, m, v, w);
      else                                          return mul.behavior(cpu_{}, opts, v, w);
    }
  }
}
