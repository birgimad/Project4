// Copyright (C) 2010-2015 Conrad Sanderson
// Copyright (C) 2010-2015 NICTA (www.nicta.com.au)
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.


//! \addtogroup fn_cumsum
//! @{



template<typename T1>
arma_inline
typename
enable_if2
  <
  is_arma_type<T1>::value,
  const Op<T1, op_cumsum_simple>
  >::result
cumsum(const T1& X)
  {
  arma_extra_debug_sigprint();
  
  const uword dim = resolves_to_rowvector<T1>::value ? 1 : 0;
  
  return Op<T1, op_cumsum_simple>(X, dim, 0);
  }



template<typename T1>
arma_inline
typename
enable_if2
  <
  is_arma_type<T1>::value,
  const Op<T1, op_cumsum>
  >::result
cumsum(const T1& X, const uword dim)
  {
  arma_extra_debug_sigprint();
  
  return Op<T1, op_cumsum>(X, dim, 0);
  }



template<typename T>
arma_inline
arma_warn_unused
const typename arma_scalar_only<T>::result &
cumsum(const T& x)
  {
  return x;
  }



//! @}