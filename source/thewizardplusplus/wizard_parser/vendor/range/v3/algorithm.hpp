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

#ifndef RANGES_V3_ALGORITHM_HPP
#define RANGES_V3_ALGORITHM_HPP

#include "detail/config.hpp"
RANGES_DISABLE_WARNINGS

#include "algorithm/adjacent_find.hpp"
#include "algorithm/all_of.hpp"
#include "algorithm/any_of.hpp"
#include "algorithm/binary_search.hpp"
#include "algorithm/copy.hpp"
#include "algorithm/copy_backward.hpp"
#include "algorithm/copy_if.hpp"
#include "algorithm/copy_n.hpp"
#include "algorithm/count.hpp"
#include "algorithm/count_if.hpp"
#include "algorithm/equal.hpp"
#include "algorithm/equal_range.hpp"
#include "algorithm/fill.hpp"
#include "algorithm/fill_n.hpp"
#include "algorithm/find.hpp"
#include "algorithm/find_end.hpp"
#include "algorithm/find_first_of.hpp"
#include "algorithm/find_if.hpp"
#include "algorithm/find_if_not.hpp"
#include "algorithm/for_each.hpp"
#include "algorithm/for_each_n.hpp"
#include "algorithm/generate.hpp"
#include "algorithm/generate_n.hpp"
#include "algorithm/heap_algorithm.hpp"
#include "algorithm/inplace_merge.hpp"
#include "algorithm/is_partitioned.hpp"
#include "algorithm/is_sorted.hpp"
#include "algorithm/is_sorted_until.hpp"
#include "algorithm/lexicographical_compare.hpp"
#include "algorithm/lower_bound.hpp"
#include "algorithm/max.hpp"
#include "algorithm/max_element.hpp"
#include "algorithm/merge.hpp"
#include "algorithm/min.hpp"
#include "algorithm/min_element.hpp"
#include "algorithm/minmax.hpp"
#include "algorithm/minmax_element.hpp"
#include "algorithm/mismatch.hpp"
#include "algorithm/move.hpp"
#include "algorithm/move_backward.hpp"
#include "algorithm/none_of.hpp"
#include "algorithm/nth_element.hpp"
#include "algorithm/partial_sort.hpp"
#include "algorithm/partial_sort_copy.hpp"
#include "algorithm/partition.hpp"
#include "algorithm/partition_copy.hpp"
#include "algorithm/partition_point.hpp"
#include "algorithm/permutation.hpp"
#include "algorithm/remove.hpp"
#include "algorithm/remove_copy.hpp"
#include "algorithm/remove_copy_if.hpp"
#include "algorithm/remove_if.hpp"
#include "algorithm/replace.hpp"
#include "algorithm/replace_copy.hpp"
#include "algorithm/replace_copy_if.hpp"
#include "algorithm/replace_if.hpp"
#include "algorithm/reverse.hpp"
#include "algorithm/reverse_copy.hpp"
#include "algorithm/rotate.hpp"
#include "algorithm/rotate_copy.hpp"
#include "algorithm/sample.hpp"
#include "algorithm/search.hpp"
#include "algorithm/search_n.hpp"
#include "algorithm/set_algorithm.hpp"
#include "algorithm/shuffle.hpp"
#include "algorithm/sort.hpp"
#include "algorithm/stable_partition.hpp"
#include "algorithm/stable_sort.hpp"
#include "algorithm/swap_ranges.hpp"
#include "algorithm/transform.hpp"
#include "algorithm/unique.hpp"
#include "algorithm/unique_copy.hpp"
#include "algorithm/upper_bound.hpp"

// BUGBUG
#include "algorithm/aux_/equal_range_n.hpp"
#include "algorithm/aux_/lower_bound_n.hpp"
#include "algorithm/aux_/merge_n.hpp"
#include "algorithm/aux_/merge_n_with_buffer.hpp"
#include "algorithm/aux_/sort_n_with_buffer.hpp"
#include "algorithm/aux_/upper_bound_n.hpp"

RANGES_RE_ENABLE_WARNINGS

#endif
