#pragma once

namespace simulation {
	class PhysObject;

	class ISimulator
	{
	public:
		typedef std::vector<std::shared_ptr<PhysObject>> ObjectsList;

	public:
		virtual ~ISimulator()
		{
		}

		virtual void destroy() = 0;

		virtual void simulate(const ObjectsList& objects, const double dt) = 0;
	};

} // namespace simulation