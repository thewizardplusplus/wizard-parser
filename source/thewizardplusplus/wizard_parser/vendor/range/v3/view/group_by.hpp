/// \file
// Range v3 library
//
//  Copyright Eric Niebler 2013-present
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//

#ifndef RANGES_V3_VIEW_GROUP_BY_HPP
#define RANGES_V3_VIEW_GROUP_BY_HPP

#include <utility>
#include <type_traits>
#include "../../../meta/meta.hpp"
#include "../detail/satisfy_boost_range.hpp"
#include "../range_fwd.hpp"
#include "../begin_end.hpp"
#include "../iterator_range.hpp"
#include "../range_traits.hpp"
#include "../range_concepts.hpp"
#include "../view_facade.hpp"
#include "../utility/functional.hpp"
#include "../utility/semiregular.hpp"
#include "../utility/static_const.hpp"
#include "../algorithm/find_if_not.hpp"
#include "../view/view.hpp"
#include "../view/take_while.hpp"

namespace ranges
{
    inline namespace v3
    {
        // TODO group_by could support Input ranges by keeping mutable state in
        // the range itself. The group_by view would then be mutable-only and
        // Input.

        /// \addtogroup group-views
        /// @{
        template<typename Rng, typename Fun>
        struct group_by_view
          : view_facade<
                group_by_view<Rng, Fun>,
                is_finite<Rng>::value ? finite : range_cardinality<Rng>::value>
        {
        private:
            friend range_access;
            Rng rng_;
            semiregular_t<Fun> fun_;

            template<bool IsConst>
            struct cursor
            {
            private:
                friend struct cursor<!IsConst>;
                friend range_access;
                friend group_by_view;
                using CRng = meta::const_if_c<IsConst, Rng>;
                iterator_t<CRng> cur_;
                sentinel_t<CRng> last_;
                semiregular_ref_or_val_t<Fun, IsConst> fun_;

                struct pred
                {
                    iterator_t<CRng> first_;
                    semiregular_ref_or_val_t<Fun, IsConst> fun_;
                    bool operator()(range_reference_t<CRng> ref) const
                    {
                        return invoke(fun_, *first_, ref);
                    }
                };
                auto read() const ->
                    take_while_view<iterator_range<iterator_t<CRng>, sentinel_t<CRng>>, pred>
                {
                    return {{cur_, last_}, {cur_, fun_}};
                }
                void next()
                {
                    cur_ = find_if_not(cur_, last_, pred{cur_, fun_});
                }
                bool equal(default_sentinel) const
                {
                    return cur_ == last_;
                }
                bool equal(cursor const &that) const
                {
                    return cur_ == that.cur_;
                }
                cursor(semiregular_ref_or_val_t<Fun, IsConst> fun, iterator_t<CRng> first,
                    sentinel_t<CRng> last)
                  : cur_(first), last_(last), fun_(fun)
                {}
            public:
                cursor() = default;
                template<bool Other,
                    CONCEPT_REQUIRES_(IsConst && !Other)>
                cursor(cursor<Other> that)
                  : cur_(std::move(that.cur_)), last_(std::move(last_)), fun_(std::move(that.fun_))
                {}
            };
            cursor<false> begin_cursor()
            {
                return {fun_, ranges::begin(rng_), ranges::end(rng_)};
            }
            template<typename CRng = Rng const,
                CONCEPT_REQUIRES_(Range<CRng>() &&
                    Invocable<
                        Fun const &,
                        range_common_reference_t<CRng>,
                        range_common_reference_t<CRng>>())>
            cursor<true> begin_cursor() const
            {
                return {fun_, ranges::begin(rng_), ranges::end(rng_)};
            }
        public:
            group_by_view() = default;
            group_by_view(Rng rng, Fun fun)
              : rng_(std::move(rng))
              , fun_(std::move(fun))
            {}
        };

        namespace view
        {
            struct group_by_fn
            {
            private:
                friend view_access;
                template<typename Fun>
                static auto bind(group_by_fn group_by, Fun fun)
                RANGES_DECLTYPE_AUTO_RETURN
                (
                    make_pipeable(std::bind(group_by, std::placeholders::_1, std::move(fun)))
                )
            public:
                template<typename Rng, typename Fun>
                using Concept = meta::and_<
                    ForwardRange<Rng>,
                    IndirectRelation<Fun, iterator_t<Rng>>>;

                template<typename Rng, typename Fun,
                    CONCEPT_REQUIRES_(Concept<Rng, Fun>())>
                group_by_view<all_t<Rng>, Fun> operator()(Rng && rng, Fun fun) const
                {
                    return {all(static_cast<Rng&&>(rng)), std::move(fun)};
                }

            #ifndef RANGES_DOXYGEN_INVOKED
                template<typename Rng, typename Fun,
                    CONCEPT_REQUIRES_(!Concept<Rng, Fun>())>
                void operator()(Rng &&, Fun) const
                {
                    CONCEPT_ASSERT_MSG(ForwardRange<Rng>(),
                        "The object on which view::group_by operates must be a model of the "
                        "ForwardRange concept.");
                    CONCEPT_ASSERT_MSG(IndirectRelation<Fun, iterator_t<Rng>>(),
                        "The function passed to view::group_by must be callable with two arguments "
                        "of the range's common reference type, and its return type must be "
                        "convertible to bool.");
                }
            #endif
            };

            /// \relates group_by_fn
            /// \ingroup group-views
            RANGES_INLINE_VARIABLE(view<group_by_fn>, group_by)
        }
        /// @}
    }
}

RANGES_SATISFY_BOOST_RANGE(::ranges::v3::group_by_view)

#endif