#ifndef WEBDRIVER_UTILS_H
#define WEBDRIVER_UTILS_H

#include "../webdriver_global.h"
#include <iostream>

namespace webdriver {

class WEBDRIVER_EXPORT WebdriverUtils
{
public:
    static std::string tOTP(const char * secretkey);

};
}

#endif // WEBDRIVER_UTILS_H
