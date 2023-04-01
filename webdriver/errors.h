#ifndef FDRIVER_ERRORS_H
#define FDRIVER_ERRORS_H

#include <stdexcept>
#include <string>

namespace webdriver {

struct FDriverException : std::runtime_error {
        explicit FDriverException(const std::string& message)
		: std::runtime_error(message) {}
};

} // namespace webdriver

#endif
