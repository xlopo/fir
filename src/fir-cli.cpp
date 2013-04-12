#include <iostream>
#include <fstream>
#include <string>

#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <sys/stat.h>

std::string operator"" _str (const char * cstr, size_t sz)
{
    return std::string(cstr);
}

std::string operator"" _expand (const char * cstr, size_t sz)
{
    return std::string(cstr);
}

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

    if (directory.length() == 0)
        if (auto home = std::getenv("HOME")) {
            directory = home;
        }
        else {
            std::cerr << "fir: no directory specified and cannot find home directory\n";
            exit(EXIT_FAILURE);
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

void initialize_fir_home(std::string fir_home)
{

}

int main (int argc, char *argv[])
{   
    std::string fir_home;
    if (argc > 1 && strcmp(argv[1], "init") == 0)
        fir_home = get_fir_home(".");
    else
        fir_home = get_fir_home("");

    return 0;
}