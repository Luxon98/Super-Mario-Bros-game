#ifndef FileNotLoadedException_H
#define FileNotLoadedException_H

#include <stdexcept>


class FileNotLoadedException : public std::runtime_error
{
private:
    std::string exceptionMessage;

public:
    FileNotLoadedException(const std::string &message);
    const char* what() const noexcept override;
};

#endif //FileNotLoadedException_H