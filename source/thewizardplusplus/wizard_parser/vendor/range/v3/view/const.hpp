/// \file
// Range v3 library
//
//  Copyright Eric Niebler 2013-present
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//

#ifndef RANGES_V3_VIEW_CONST_HPP
#define RANGES_V3_VIEW_CONST_HPP

#include <utility>
#include <type_traits>
#include "../detail/satisfy_boost_range.hpp"
#include "../range_fwd.hpp"
#include "../size.hpp"
#include "../begin_end.hpp"
#include "../range_concepts.hpp"
#include "../view_adaptor.hpp"
#include "../utility/move.hpp"
#include "../utility/common_type.hpp"
#include "../utility/functional.hpp"
#include "../utility/static_const.hpp"
#include "../view/view.hpp"
#include "../view/all.hpp"

namespace ranges
{
    inline namespace v3
    {
        /// \addtogroup group-views
        /// @{
        template<typename Rng>
        struct const_view
          : view_adaptor<const_view<Rng>, Rng>
        {
        private:
            friend range_access;
            template<bool Const>
            struct adaptor
              : adaptor_base
            {
                using CRng = meta::const_if_c<Const, Rng>;
                using value_ =
                    range_value_type_t<CRng>;
                using reference_ =
                    common_reference_t<value_ const &&, range_reference_t<CRng>>;
                using rvalue_reference_ =
                    common_reference_t<value_ const &&, range_rvalue_reference_t<CRng>>;
                adaptor() = default;
                template<bool Other,
                    CONCEPT_REQUIRES_(Const && !Other)>
                constexpr adaptor(adaptor<Other>)
                {}
                reference_ read(iterator_t<CRng> const &it) const
                {
                    return *it;
                }
                rvalue_reference_ iter_move(iterator_t<CRng> const &it) const
                RANGES_AUTO_RETURN_NOEXCEPT
                (
                    ranges::iter_move(it)
                )
            };
            adaptor<simple_view<Rng>()> begin_adaptor()
            {
                return {};
            }
            adaptor<simple_view<Rng>()> end_adaptor()
            {
                return {};
            }
            CONCEPT_REQUIRES(Range<Rng const>())
            adaptor<true> begin_adaptor() const
            {
                return {};
            }
            CONCEPT_REQUIRES(Range<Rng const>())
            adaptor<true> end_adaptor() const
            {
                return {};
            }
        public:
            const_view() = default;
            explicit const_view(Rng rng)
              : const_view::view_adaptor{std::move(rng)}
            {}
            CONCEPT_REQUIRES(SizedRange<Rng>())
            range_size_type_t<Rng> size()
            {
                return ranges::size(this->base());
            }
            CONCEPT_REQUIRES(SizedRange<Rng const>())
            range_size_type_t<Rng> size() const
            {
                return ranges::size(this->base());
            }
        };

        namespace view
        {
            struct const_fn
            {
                template<typename Rng>
                const_view<all_t<Rng>> operator()(Rng &&rng) const
                {
                    CONCEPT_ASSERT_MSG(Range<Rng>(),
                        "Rng must be a model of the Range concept");
                    return const_view<all_t<Rng>>{all(static_cast<Rng&&>(rng))};
                }
            };

            /// \relates const_fn
            /// \ingroup group-views
            RANGES_INLINE_VARIABLE(view<const_fn>, const_)
        }
        /// @}
    }
}

RANGES_SATISFY_BOOST_RANGE(::ranges::v3::const_view)

#endif
