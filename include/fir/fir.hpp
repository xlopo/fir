#ifndef FIR_FIR_HPP
#define FIR_FIR_HPP

#include <iostream>
#include <memory>

namespace fir
{
	class Manager {
	public:
		static void print()
		{
			std::cout << "manager\n";
		}
	};

	static std::unique_ptr<Manager> manager = nullptr;

	enum class Version : unsigned int
	{
		major = 0,
		minor = 0,
		patch = 0x123
	};
}

#endif // FIR_FIR_HPP