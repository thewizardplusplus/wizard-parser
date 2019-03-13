/// \file
// Range v3 library
//
//  Copyright Eric Niebler 2014-present
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//

#ifndef RANGES_V3_FRONT_HPP
#define RANGES_V3_FRONT_HPP

#include "range_fwd.hpp"
#include "begin_end.hpp"
#include "range_concepts.hpp"
#include "range_traits.hpp"
#include "utility/static_const.hpp"

namespace ranges
{
    inline namespace v3
    {
        /// \ingroup group-core
        struct front_fn
        {
            /// \return `*begin(rng)`
            template<typename Rng,
                CONCEPT_REQUIRES_(ForwardRange<Rng>())>
            constexpr range_reference_t<Rng> operator()(Rng &&rng) const
            {
                return *begin(rng);
            }
        };

        /// \ingroup group-core
        /// \sa `front_fn`
        RANGES_INLINE_VARIABLE(front_fn, front)
    }
}

#endif
