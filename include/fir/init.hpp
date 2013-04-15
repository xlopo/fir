#include <iostream>

#include <fir/module.hpp>

namespace fir 
{
class ModuleInit : public Module
{
public:
	ModuleInit() = default;
	const char * description();
};	
} // namespace fir

namespace {
	
class RegisterModule
{
public:
	RegisterModule() {
		std::cout << "Testing\n";
	}

} Register;

}
extern "C"  fir::module_ptr fir_register_module()
{
	std::cout << u8"it worked!\n";

	return std::make_shared<fir::ModuleInit>();
}
