#pragma once

#include "BaseCouplingScheme.hpp"
#include "tarch/logging/Log.h"


namespace precice {
namespace cplscheme {

class ParallelCouplingScheme : public BaseCouplingScheme
{
public:
  ParallelCouplingScheme (
    double                maxTime,
    int                   maxTimesteps,
    double                timestepLength,
    int                   validDigits,
    const std::string&    firstParticipant,
    const std::string&    secondParticipant,
    const std::string&    localParticipant,
    com::PtrCommunication communication,
    int                   maxIterations,
    constants::TimesteppingMethod dtMethod);
  
  /// @brief Logging device.
  static tarch::logging::Log _log;

  virtual void initialize(double startTime, int startTimestep);

  virtual void initializeData();

  
protected:
  /// @brief merges send and receive data into one map (for parallel post-processing)
  virtual void mergeData();

  /// @brief Returns all data (receive and send)
  DataMap& getAllData()
    {
      assertion1(!doesFirstStep(), "Only the second participant should do the post processing." );
      return _allData;
    }

  
private:
  /// @brief Map from data ID -> all data (receive and send) with that ID
  DataMap _allData;

};

}}
