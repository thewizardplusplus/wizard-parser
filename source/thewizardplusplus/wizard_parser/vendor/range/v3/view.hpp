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

#ifndef RANGES_V3_VIEW_HPP
#define RANGES_V3_VIEW_HPP

#include "detail/config.hpp"
RANGES_DISABLE_WARNINGS

#include "view/adjacent_remove_if.hpp"
#include "view/adjacent_filter.hpp"
#include "view/all.hpp"
#include "view/any_view.hpp"
#include "view/bounded.hpp"
#include "view/c_str.hpp"
#include "view/cartesian_product.hpp"
#include "view/chunk.hpp"
#include "view/concat.hpp"
#include "view/const.hpp"
#include "view/counted.hpp"
#include "view/cycle.hpp"
#include "view/delimit.hpp"
#include "view/drop.hpp"
#include "view/drop_exactly.hpp"
#include "view/drop_while.hpp"
#include "view/empty.hpp"
#include "view/filter.hpp"
#include "view/for_each.hpp"
#include "view/generate.hpp"
#include "view/generate_n.hpp"
#include "view/group_by.hpp"
#include "view/indices.hpp"
#include "view/indirect.hpp"
#include "view/intersperse.hpp"
#include "view/iota.hpp"
#include "view/join.hpp"
#include "view/linear_distribute.hpp"
#include "view/map.hpp"
#include "view/move.hpp"
#include "view/partial_sum.hpp"
#include "view/remove_if.hpp"
#include "view/repeat.hpp"
#include "view/repeat_n.hpp"
#include "view/replace.hpp"
#include "view/replace_if.hpp"
#include "view/reverse.hpp"
#include "view/sample.hpp"
#include "view/set_algorithm.hpp"
#include "view/single.hpp"
#include "view/slice.hpp"
#include "view/sliding.hpp"
#include "view/split.hpp"
#include "view/stride.hpp"
#include "view/tail.hpp"
#include "view/take.hpp"
#include "view/take_exactly.hpp"
#include "view/take_while.hpp"
#include "view/tokenize.hpp"
#include "view/transform.hpp"
#include "view/unbounded.hpp"
#include "view/unique.hpp"
#include "view/zip.hpp"
#include "view/zip_with.hpp"

RANGES_RE_ENABLE_WARNINGS

#endif
