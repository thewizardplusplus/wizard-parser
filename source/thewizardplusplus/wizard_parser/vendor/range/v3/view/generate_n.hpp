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

#ifndef RANGES_V3_VIEW_GENERATE_N_HPP
#define RANGES_V3_VIEW_GENERATE_N_HPP

#include <type_traits>
#include <utility>
#include "../../../meta/meta.hpp"
#include "../detail/satisfy_boost_range.hpp"
#include "../range_fwd.hpp"
#include "../range_traits.hpp"
#include "../size.hpp"
#include "../view_facade.hpp"
#include "../utility/functional.hpp"
#include "../utility/semiregular.hpp"
#include "../utility/static_const.hpp"
#include "../view/generate.hpp"

namespace ranges
{
    inline namespace v3
    {
        /// \addtogroup group-views
        /// @{
        template<typename G>
        struct generate_n_view
          : view_facade<generate_n_view<G>, finite>
        {
        private:
            friend range_access;
            using result_t = invoke_result_t<G &>;
            movesemiregular_t<G> gen_;
            detail::non_propagating_cache<result_t> val_;
            std::size_t n_;
            struct cursor
            {
            private:
                generate_n_view *rng_;
            public:
                cursor() = default;
                explicit cursor(generate_n_view &rng)
                  : rng_(&rng)
                {}
                bool equal(default_sentinel) const
                {
                    return 0 == rng_->n_;
                }
                result_t &&read() const
                {
                    if (!rng_->val_)
                        rng_->val_ = rng_->gen_();
                    return static_cast<result_t &&>(
                        static_cast<result_t &>(*rng_->val_));
                }
                void next()
                {
                    RANGES_EXPECT(0 != rng_->n_);
                    --rng_->n_;
                    rng_->val_.reset();
                }
            };
            cursor begin_cursor()
            {
                return cursor{*this};
            }
        public:
            generate_n_view() = default;
            explicit generate_n_view(G g, std::size_t n)
              : gen_(std::move(g)), n_(n)
            {}
            result_t &cached()
            {
                return *val_;
            }
            std::size_t size() const
            {
                return n_;
            }
        };

        namespace view
        {
            struct generate_n_fn
            {
                template<typename G,
                    CONCEPT_REQUIRES_(generate_fn::Concept<G>())>
                generate_n_view<G> operator()(G g, std::size_t n) const
                {
                    return generate_n_view<G>{std::move(g), n};
                }
            #ifndef RANGES_DOXYGEN_INVOKED
                template<typename G,
                    CONCEPT_REQUIRES_(!generate_fn::Concept<G>())>
                void operator()(G, std::size_t) const
                {
                    generate_fn::check<G>();
                }
            #endif
            };

            /// \relates generate_n_fn
            /// \ingroup group-views
            RANGES_INLINE_VARIABLE(generate_n_fn, generate_n)
        }
        /// @}
    }
}

RANGES_SATISFY_BOOST_RANGE(::ranges::v3::generate_n_view)

#endif
