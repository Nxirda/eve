//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_AVERAGE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_AVERAGE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/half.hpp>
#include <eve/function/fma.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> average_( EVE_SUPPORTS(neon128_),
                                                wide<T, N, neon64_> const &v0,
                                                wide<T, N, neon64_> const &v1
                                              ) noexcept
  {
    using in_t = typename wide<T, N, neon64_>::storage_type;

    if constexpr(std::is_floating_point_v<T>)
    {
      return fma(v0,Half(as(v0)),v1*Half(as(v1)));
    }
    else
    {
      if constexpr(sizeof(T) == 8) return map(eve::average,v0,v1);
      if constexpr(std::is_same_v<in_t, int32x2_t>) return vhadd_s32(v0, v1);
      if constexpr(std::is_same_v<in_t, int16x4_t>) return vhadd_s16(v0, v1);
      if constexpr(std::is_same_v<in_t, int8x8_t>) return vhadd_s8(v0, v1);
      if constexpr(std::is_same_v<in_t, uint32x2_t>) return vhadd_u32(v0, v1);
      if constexpr(std::is_same_v<in_t, uint16x4_t>) return vhadd_u16(v0, v1);
      if constexpr(std::is_same_v<in_t, uint8x8_t>) return vhadd_u8(v0, v1);
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> average_ ( EVE_SUPPORTS(neon128_),
                                                  wide<T, N, neon128_> const &v0,
                                                  wide<T, N, neon128_> const &v1
                                                  ) noexcept
  {
    using in_t = typename wide<T, N, neon128_>::storage_type;

    if constexpr(std::is_floating_point_v<T>)
    {
      return fma(v0,Half(as(v0)),v1*Half(as(v1)));
    }
    else
    {
      if constexpr(sizeof(T) == 8) return map(eve::average,v0,v1);
      if constexpr(std::is_same_v<in_t, int32x4_t>) return vhaddq_s32(v0, v1);
      if constexpr(std::is_same_v<in_t, int16x8_t>) return vhaddq_s16(v0, v1);
      if constexpr(std::is_same_v<in_t, int8x16_t>) return vhaddq_s8(v0, v1);
      if constexpr(std::is_same_v<in_t, uint32x4_t>) return vhaddq_u32(v0, v1);
      if constexpr(std::is_same_v<in_t, uint16x8_t>) return vhaddq_u16(v0, v1);
      if constexpr(std::is_same_v<in_t, uint8x16_t>) return vhaddq_u8(v0, v1);
    }
  }
}

#endif
