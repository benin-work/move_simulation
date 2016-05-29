#pragma once
#include "ISimulator.h"

namespace move_simulation {

	class PhysSimulator :public ISimulator
	{
	public:
		PhysSimulator();
		virtual ~PhysSimulator();

		void simulate(const std::shared_ptr<Scene> scene, const double dt) override;
	};

} // namespace move_simulation