//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core/regular/if_else.hpp>

namespace eve::detail
{
  template<unsigned_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> average_(EVE_REQUIRES(sse2_),
                                      O          const & opts,
                                      wide<T, N> a,
                                      wide<T, N> b) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    if constexpr( O::contains(upper))
    {
      return average.behavior(cpu_{}, opts, a, b);
    }
    else
    {
      if constexpr( sizeof(T) == 2 )
      {
        if constexpr( std::same_as<abi_t<T, N>, x86_512_> ) return _mm512_avg_epu16(a, b);
        else if constexpr( current_api >= avx2 && std::same_as<abi_t<T, N>, x86_256_> )
          return _mm256_avg_epu16(a, b);
        else if constexpr( std::same_as<abi_t<T, N>, x86_128_> )
          return _mm_avg_epu16(a, b);
        else
          return average.behavior(cpu_{}, opts, a, b);
      }
      if constexpr( sizeof(T) == 1 )
      {
        if constexpr( std::same_as<abi_t<T, N>, x86_512_> ) return _mm512_avg_epu8(a, b);
        else if constexpr( current_api >= avx2 && std::same_as<abi_t<T, N>, x86_256_> )
          return _mm256_avg_epu8(a, b);
        else if constexpr( std::same_as<abi_t<T, N>, x86_128_> )
          return _mm_avg_epu8(a, b);
        else
          return average.behavior(cpu_{}, opts, a, b);
      }
      else return average.behavior(cpu_{}, opts, a, b);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, unsigned_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N>  average_(EVE_REQUIRES(avx512_),
                                       C          const &cx,
                                       O          const &opts,
                                       wide<T, N> const &v,
                                       wide<T, N> const &w) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    if constexpr( O::contains(upper))
      return average[opts][cx].retarget(cpu_{}, v, w);
    else
    {
      constexpr auto c = categorize<wide<T, N>>();
      auto src = alternative(cx, v, as<wide<T, N>> {});
      auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

      if constexpr( c == category::uint16x32 ) return _mm512_mask_avg_epu16(src, m, v, w);
      else if constexpr( c == category::uint16x16 ) return _mm256_mask_avg_epu16(src, m, v, w);
      else if constexpr( c == category::uint16x8 ) return _mm_mask_avg_epu16(src, m, v, w);
      else if constexpr( c == category::uint8x64 ) return _mm512_mask_avg_epu8(src, m, v, w);
      else if constexpr( c == category::uint8x32 ) return _mm256_mask_avg_epu8(src, m, v, w);
      else if constexpr( c == category::uint8x16 ) return _mm_mask_avg_epu8(src, m, v, w);
      else if constexpr( match(c, category::uint_) ) return average[opts][cx].retarget(cpu_{}, v, w);
    }
  }
}
