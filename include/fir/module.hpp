#ifndef FIR_MODULE_HPP
#define FIR_MODULE_HPP

#include <memory>
#include <string>
#include <vector>

namespace fir
{

	class Module
	{
	public:
		virtual const char * description() { return ""; }
	};

	using module_ptr = std::shared_ptr<Module>;
    using register_module_t = module_ptr (*)();
} // namespace fir

#endif // FIR_MODULE_HPP
