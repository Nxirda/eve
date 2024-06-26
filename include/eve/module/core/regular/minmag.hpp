//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
  template<typename Options>
  struct minmag_t : tuple_callable<minmag_t, Options, numeric_option, pedantic_option, saturated_option>
  {
    template<eve::value T0, value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0,  t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup t) const noexcept { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(minmag_t, minmag_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var minmag
//!   @brief Computes the value for which the minimum of the absolute value of its arguments is obtained.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::value T, eve::value... Ts >
//!      eve::common_value_t<T, Ts...> minmag(T x, Ts ... xs) noexcept;
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `xs...` :  [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!      The [elementwise](@ref glossary_elementwise) element of greatest absolute value is
//!      returned.
//!
//!      For instance for two elements:
//!
//!        * If `|x| <   |y|`,  `x` is returned.
//!        * If `|x| >   |y|`,  `y` is returned.
//!        * Otherwise `max(x, y)` is returned.
//!
//!      For n parameters the result is computed as if this scheme was recursively used.
//!
//!   @note
//!     * If any element of the inputs is a `Nan`, the corresponding output element
//!       is system-dependent.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/minmag.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::minmag[mask](x, ...)` provides a masked
//!     version of `minmag` which is
//!     equivalent to `if_else(mask, minmag(x, ...), x)`
//!
//!   * eve::pedantic, eve::numeric
//!
//!     The behaviour of d(eve::minmag)(x, y) (where d is one of these two decorators
//!     is identical except that if  `|x| == |y|`, `d(max)` is used.
//!
//! @}
//================================================================================================
inline constexpr auto minmag = functor<minmag_t>;
}

#include <eve/module/core/regular/impl/minmag.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/minmag.hpp>
#endif
