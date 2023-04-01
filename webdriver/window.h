#ifndef FDRIVER_WINDOW_H
#define FDRIVER_WINDOW_H

#include "types.h"
#include "conversions.h"
#include "detail/resource.h"
#include <string>
#include "webdriver_global.h"

namespace webdriver {

class WEBDRIVER_EXPORT Window { // copyable
public:
	Window(const std::string& handle, const detail::Shared<detail::Resource>& resource)
		: handle_(handle)
		, resource_(resource)
	{}

    std::string GetHandle() const;

    Size GetSize() const;

    const Window& SetSize(const Size& size) const;

    Point GetPosition() const;

    const Window& SetPosition(const Point& position) const;

    const Window& Maximize() const;

private:
	std::string handle_;
	detail::Shared<detail::Resource> resource_;
};

} // namespace webdriver

#endif
