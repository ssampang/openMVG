// This file is part of OpenMVG, an Open Multiple View Geometry C++ library.

// Copyright (c) 2012, 2013 Pierre MOULON.

// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPENMVG_MATCHING_MATCHING_FILTER_INTERFACE_HPP
#define OPENMVG_MATCHING_MATCHING_FILTER_INTERFACE_HPP

#include <vector>

#include "openMVG/matching/indMatch.hpp"
#include "openMVG/features/feature.hpp"

namespace openMVG {
namespace matching {

template < typename DistanceType >
class MatchingFilter
{
  public:

  MatchingFilter() = default;
  virtual ~MatchingFilter() = default;

  /**
   * Filter the matches
   *
   * \param[in,out] vec_putative_matches   Input matches.
   * \param[in] vec_distance               Match distances.
   * \param[in] vec_regions                Locations of features.
   *
   * \return True if success.
   */
  virtual bool Filter( matching::IndMatches & vec_putative_matches,
                       const std::vector<DistanceType> & vec_distance,
                       const std::vector<features::PointFeature> & vec_regions )=0;

};

}  // namespace matching
}  // namespace openMVG

#endif  // OPENMVG_MATCHING_MATCHING_FILTER_INTERFACE_HPP
