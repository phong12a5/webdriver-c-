#include "webdriver.h"
#include <CkCert.h>
#include <CkPrivateKey.h>
#include <CkJsonObject.h>
#include <CkBinData.h>
#include <CkHttp.h>
#include <CkHttpResponse.h>
#include <CkGlobal.h>
namespace webdriver {

static CkGlobal glob;

bool unlockChilkat() {
    bool success_global = glob.UnlockBundle("VONGTH.CB4082020_9kru5rnD5R2h");
    if (success_global != true) {
        std::cout << "Error: " << glob.lastErrorText() << std::endl;
        return false;
    }

    int status = glob.get_UnlockStatus();
    if (status == 2) {
        return true;
    } else {
        return false;
    }
}

WebDriver::WebDriver(
        const Capabilities& desired,
        const Capabilities& required,
        const std::string& url
        )
    : Client(url)
    , Session(CreateSession(desired, required))
{
    if(!unlockChilkat()) {
        throw std::runtime_error("unlock FDriver failed");
    }
}

WebDriver WebDriver::Start(
        const Capabilities& desired,
        const Capabilities& required,
        const std::string& url
        )
{
    return WebDriver(desired, required, url);
}

WebDriver WebDriver::Start(const Capabilities& desired, const std::string& url)
{
    return Start(desired, Capabilities(), url);
}
} // namespace webdriver

