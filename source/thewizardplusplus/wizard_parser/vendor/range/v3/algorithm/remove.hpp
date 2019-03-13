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
#ifndef RANGES_V3_ALGORITHM_REMOVE_HPP
#define RANGES_V3_ALGORITHM_REMOVE_HPP

#include "../../../meta/meta.hpp"
#include "../range_fwd.hpp"
#include "../begin_end.hpp"
#include "../range_concepts.hpp"
#include "../range_traits.hpp"
#include "../utility/iterator.hpp"
#include "../utility/iterator_concepts.hpp"
#include "../utility/iterator_traits.hpp"
#include "../utility/functional.hpp"
#include "../algorithm/find.hpp"
#include "../utility/static_const.hpp"

namespace ranges
{
    inline namespace v3
    {
        /// \ingroup group-concepts
        template<typename I, typename T, typename P = ident>
        using Removable = meta::strict_and<
            ForwardIterator<I>,
            IndirectRelation<equal_to, projected<I, P>, T const *>,
            Permutable<I>>;

        /// \addtogroup group-algorithms
        /// @{
        struct remove_fn
        {
            template<typename I, typename S, typename T, typename P = ident,
                CONCEPT_REQUIRES_(Removable<I, T, P>() && Sentinel<S, I>())>
            I operator()(I begin, S end, T const &val, P proj = P{}) const
            {
                begin = find(std::move(begin), end, val, std::ref(proj));
                if(begin != end)
                {
                    for(I i = next(begin); i != end; ++i)
                    {
                        if(!(invoke(proj, *i) == val))
                        {
                            *begin = iter_move(i);
                            ++begin;
                        }
                    }
                }
                return begin;
            }

            template<typename Rng, typename T, typename P = ident,
                typename I = iterator_t<Rng>,
                CONCEPT_REQUIRES_(Removable<I, T, P>() && ForwardRange<Rng>())>
            safe_iterator_t<Rng> operator()(Rng &&rng, T const &val, P proj = P{}) const
            {
                return (*this)(begin(rng), end(rng), val, std::move(proj));
            }
        };

        /// \sa `remove_fn`
        /// \ingroup group-algorithms
        RANGES_INLINE_VARIABLE(with_braced_init_args<remove_fn>, remove)

        /// @}
    } // namespace v3
} // namespace ranges

#endif // include guard
