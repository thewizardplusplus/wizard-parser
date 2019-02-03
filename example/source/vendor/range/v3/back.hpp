/// \file
// Range v3 library
//
//  Copyright Eric Niebler 2014-present
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//

#ifndef RANGES_V3_BACK_HPP
#define RANGES_V3_BACK_HPP

#include "range_fwd.hpp"
#include "begin_end.hpp"
#include "range_concepts.hpp"
#include "range_traits.hpp"
#include "utility/iterator.hpp"
#include "utility/static_const.hpp"

namespace ranges
{
    inline namespace v3
    {
        /// \ingroup group-core
        struct back_fn
        {
            /// \return `*prev(end(rng))`
            template<typename Rng,
                CONCEPT_REQUIRES_(BoundedRange<Rng>() && BidirectionalRange<Rng>())>
            RANGES_CXX14_CONSTEXPR
            range_reference_t<Rng> operator()(Rng &&rng) const
            {
                return *prev(end(rng));
            }
        };

        /// \ingroup group-core
        /// \sa `back_fn`
        RANGES_INLINE_VARIABLE(back_fn, back)
    }
}

#endif
