#pragma once
#include <memory>

namespace move_simulation {
	class Scene;

	class ISimulator
	{
	public:
		virtual ~ISimulator()
		{
		}

		virtual void simulate(const std::shared_ptr<Scene> scene, const double dt) = 0;
	};

} // namespace move_simulation