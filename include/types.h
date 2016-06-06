#pragma once
#include "../include/MathTypes.h"
#include <chrono>

namespace simulation 
{
	typedef simple_math::BaseVector<2, double> Vector;
	typedef std::chrono::high_resolution_clock::time_point TimePoint;

} // namespace simulation
