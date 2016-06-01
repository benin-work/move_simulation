#pragma once
#include "../include/ISimulator.h"

namespace phys_simulator_lib {

	class PhysSimulator :public simulation::ISimulator
	{
	public:
		PhysSimulator();
		void destroy() override;

		void simulate(const ObjectsList& objects, const double dt) override;
	};

	extern "C" inline __declspec(dllexport) simulation::ISimulator* __cdecl create_simulator()
	{
		return new PhysSimulator();
	}

} // namespace phys_simulator_lib