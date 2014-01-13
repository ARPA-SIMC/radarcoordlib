#include <generic.hpp>

float generic::getMissing(){
  if (numeric_limits<float>::has_quiet_NaN) return numeric_limits<float>::quiet_NaN();
  return numeric_limits<float>::max();
}

bool generic::isMissing(float value){
  if (getMissing() != getMissing())  {
    if (value != value ) return true;
  }
  else if (value == getMissing()) return true;
  return false;
}

bool generic::checkLongitude(float value) {
 	  if (value < -360. || value > 360.) return false;
  return true;
}

bool generic::checkLatitude(float value) {
  if (value < -90. || value > 90. ) return false;
  return true;
}

bool generic::checkElevation(float value) {
  if (value < -5. || value > 90. ) return false;
  return true;
}


bool generic::checkBeamDistance(float value) {
  if (value < 0.) return false;
  return true;
}
