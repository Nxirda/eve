//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of eve::is_denormal(simd)"
              , eve::test::simd::ieee_reals
              )
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_denormal(T())    , logical<T>   );
  TTS_EXPR_IS( eve::is_denormal(v_t())  , logical<v_t> );
};

//==================================================================================================
// Tests for eve::is_denormal
//==================================================================================================
auto mini = []<typename T>(eve::as<T> const & tgt)
{
  return 2*eve::smallestposval(tgt);
};

auto lastdenormal = []<typename T>(eve::as<T> const & tgt)
{
  return eve::prev(eve::smallestposval(tgt));
};

TTS_CASE_WITH ( "Check behavior of eve::is_denormal(simd)"
              , eve::test::simd::ieee_reals
              , tts::generate ( tts::randoms(eve::smallestposval, tts::constant(mini))
                              , tts::randoms(eve::mindenormal, tts::constant(lastdenormal))
                              , tts::randoms(eve::zero, tts::constant(mini))
                              , tts::logicals(0, 3)
                              )
              )
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const & t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_denormal(a0), eve::false_(eve::as(a0)));
  TTS_EQUAL(eve::is_denormal[t](a0), eve::if_else(t, eve::is_denormal(a0), eve::false_(eve::as(a0))));
  TTS_EQUAL(eve::is_denormal(a1), eve::logical<T>{eve::platform::supports_denormals});

  if constexpr(eve::platform::supports_denormals)
  {
    TTS_EQUAL(eve::is_denormal(a2), map([](auto e) -> eve::logical<v_t> { return  std::fpclassify(e) == FP_SUBNORMAL; }, a2));
  }
  else
  {
    TTS_EQUAL(eve::is_denormal(a2), eve::false_(eve::as(a2)));
  }
};