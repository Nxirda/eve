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
  struct cyl_bessel_i0_t : elementwise_callable<cyl_bessel_i0_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr
    T operator()(T a) const noexcept { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(cyl_bessel_i0_t, cyl_bessel_i0_);
  };

  //================================================================================================
  //! @addtogroup bessel
  //! @{
  //!   @var cyl_bessel_i0
  //!   @brief Computes the modified Bessel function of the first kind,
  //!   \f$ I_0(x)=\frac1{\pi}\int_{0}^{\pi}e^{x\cos\tau}\,\mathrm{d}\tau\f$.
  //!
  //!   It is the solution of \f$ x^{2}y''+xy'-x^2y=0\f$ for which \f$ y(0) = 0\f$.
  //!
  //!   **Defined in header**
  //!
  //!   @code
  //!   #include <eve/module/bessel.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!     template<eve::floating_value T> constexpr T cyl_bessel_i0(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`: positive [floating argument](@ref eve::floating_value).
  //!
  //!    **Return value**
  //!
  //!    The value of \f$ \displaystyle I_0(x)=\frac1{\pi}\int_{0}^{\pi}e^{x\cos\tau}
  //!    \,\mathrm{d}\tau\f$ is returned.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/bessel/regular/cyl_bessel_i0.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto cyl_bessel_i0 = functor<cyl_bessel_i0_t>;
}

#include <eve/module/bessel/regular/impl/cyl_bessel_i0.hpp>
