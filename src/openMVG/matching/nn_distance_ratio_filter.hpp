#include "openMVG/matching/matching_filter_interface.hpp"

namespace openMVG{
namespace matching{

/**
  * Nearest neighbor distance ratio filtering ( a < fratio * b) :
  * Ratio between best and second best matches must be superior to
  * given threshold. It avoid matches that have similar descriptor,
  * (so it removes potential ambiguities).
  *
  * \param[in]  first    Iterator on the sequence of distance.
  * \param[in]  last     Iterator of the end of the sequence.
  * \param[in]  NN       Number of neighbor in iterator
  *   sequence (minimum required 2).
  * \param[out] vec_ratioOkIndex  Indexes that respect NN dist Ratio)
  * \param[in]  fratio            Ratio value (default value 0.6f)
  *
  * \return void.
  */

template < typename DistanceTypeT >
class NNDistanceRatioFilter : MatchingFilter < DistanceTypeT >
{
  private:
    int NN_;
    float fratio_;

  public:

  NNDistanceRatioFilter
  (
    int NN, //Number of neighbors in sequence (minimum required 2)
    float fratio = 0.6f) //ratio value
  {
    assert( NN >= 2);
    NN_ = NN;
    fratio_ = fratio;
  }

  bool Filter
  ( matching::IndMatches & vec_putative_matches,
    const std::vector<DistanceTypeT> & vec_distance,
    const std::vector<features::PointFeature> & vec_regions )
  {
    // ensure every match has a distance
    assert( vec_putative_matches.size() == vec_distance.size() );
    // ensure every feature that is matched has NN_ possible matches (since we iterate over them)
    assert( vec_putative_matches.size() % NN_ == 0 );

    const size_t n = vec_distance.size();
    matching::IndMatches vec_candidate_matches = vec_putative_matches;
    vec_putative_matches.clear();
    vec_putative_matches.reserve(n/NN_);

    for (size_t i=0; i < n/NN_; i+=NN_)
    {
      if ( vec_distance[i] < fratio_ * vec_distance[i+1] )
        vec_putative_matches.emplace_back( vec_candidate_matches[i].j_, vec_candidate_matches[i].i_);
    }

    return true;
  };

};

}
}
