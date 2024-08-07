/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
//DOC TODO
//================================================================================================
//! @addtogroup core_reduction
//! @{
//!   @var minimum
//!   @brief Computes the minimal value in a simd vector
//!
//!   @groupheader{Header file}
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
//!      template< eve::value T >
//!      eve::element_type_t<T> minimum(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameter**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!    The scalar minimal value.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/minimum.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::minimum[mask](x)` provides a masked
//!     version of `minimum` which is
//!     equivalent to : ``minimum(if_else(mask, x, valmax(as(x))))`.
//!
//! @}
//================================================================================================
  EVE_MAKE_CALLABLE(minimum_, minimum);
}

#include <eve/module/core/regular/impl/minimum.hpp>

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/minimum.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/minimum.hpp>
#endif
