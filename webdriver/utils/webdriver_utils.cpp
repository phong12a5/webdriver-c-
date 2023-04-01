#include "webdriver_utils.h"
#include <CkCrypt2.h>

std::string webdriver::WebdriverUtils::tOTP(const char * secretkey)
{
    std::string result;
    if(secretkey) {
        // Do the following to calculate the 6-digit decimal Google authenticator token for a base32 secret,
        // given the current system date/time.
        CkCrypt2 crypt;
        result = crypt.totp(secretkey,"base32","0","",30,6,-1,"sha1");
    }
    return result;
}
