#include <iostream>
#include <fstream>
#include <string>

#include <vector>

#include <cerrno>
#include <cstring>
#include <cstdlib>

#include <sys/stat.h>
#include <dlfcn.h>

#include <fir/fir.hpp>
#include <fir/module.hpp>

std::string operator"" _str (const char * cstr, size_t sz)
{
    return std::string(cstr);
}

std::string operator"" _expand (const char * cstr, size_t sz)
{
    return std::string(cstr);
}

std::string operator"" _env (const char * cstr, size_t sz)
{
    if (auto str = std::getenv(cstr))
        return str;

    return "";
}

// void operator"" _error (const char * cstr, size_t sz)
// {
//     std::cerr << cstr;
// }

void exit_with_error(int error_number, std::string error_string)
{
    std::cerr << "fir: "
              << error_number << ": "
              << error_string << std::endl;
    exit(EXIT_FAILURE);
}

std::string get_fir_home(std::string directory)
{
    struct stat info;

    if (directory.length() == 0) {
        if (auto home = std::getenv("HOME")) {
            directory = home;
        }
        else {
            std::cerr << "fir: no directory specified and cannot find home directory\n";
            exit(EXIT_FAILURE);
        }
    }

    auto fir_home = directory + "/.fir";

    errno = 0;
    if (stat((fir_home + "/.").c_str(), &info) != 0) {
        if (errno == ENOENT) {
            errno = 0;

            mode_t mode = S_IRWXU;
            mkdir(fir_home.c_str(), mode);
        }

        if (errno != 0)
            exit_with_error(errno, fir_home + ": "_str + strerror(errno));
    }

    return fir_home;
}

void load_module(const char * name, std::vector<const char*> &&fir_path, bool verbose)
{
    for (auto suffix : std::vector<const char *>{u8".o", u8".dylib"})
    {
        auto module_path = fir_path[0] + "/fir_"_str + name + suffix;

        if (verbose) {
            std::cout << "fir: info: trying \"" << module_path << "\"\n";
        }

        dlerror();
        if(auto dl_handle = dlopen(module_path.c_str(), RTLD_LAZY | RTLD_LOCAL)) {
            if (auto register_module = (fir::register_module_t)dlsym(dl_handle, "fir_register_module")) {

                register_module();
            }
            else if (verbose) {
                std::cerr << "fir: error: " << dlerror() << std::endl;
            }
            
            dlclose(dl_handle);
            return;
        }

        std::cerr << "fir: error: " << dlerror() << std::endl;
    }
}

int main (int argc, char *argv[])
{
    auto fir_path = "FIR_PATH"_env;

    if (fir_path == "")
        fir_path = "~/.fir/modules"_expand;

    load_module("init", std::vector<const char*>{fir_path.c_str()}, true);

    return 0;
}
