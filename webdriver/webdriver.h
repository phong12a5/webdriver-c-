#ifndef FDRIVER_FDRIVER_H
#define FDRIVER_FDRIVER_H

#include "client.h"
#include "session.h"

namespace webdriver {

// The main class for interactions with a server. Automatically connects to a server,
// creates and deletes a session and gives access to session's API.
class WEBDRIVER_EXPORT WebDriver // copyable
        : public Client
        , public Session {
public:
    explicit WebDriver(
            const Capabilities& desired = Capabilities(),
            const Capabilities& required = Capabilities(),
            const std::string& url = kDefaultWebDriverUrl
            );

    static WebDriver Start(
            const Capabilities& desired,
            const Capabilities& required = Capabilities(),
            const std::string& url = kDefaultWebDriverUrl
            );

    static WebDriver Start(const Capabilities& desired,
                         const std::string& url);
};
} // namespace webdriver

#endif
