#ifndef FDRIVER_DETAIL_HTTP_CLIENT_H
#define FDRIVER_DETAIL_HTTP_CLIENT_H

#include <string>

namespace fdriver {
namespace detail {

struct HttpResponse {
	long http_code;
	std::string body;

	HttpResponse()
		: http_code(0)
	{}
};

struct IHttpClient {
	virtual HttpResponse Get(const std::string& url) const = 0;
	virtual HttpResponse Delete(const std::string& url) const = 0;
	virtual HttpResponse Post(const std::string& url, const std::string& data) const = 0;
	virtual ~IHttpClient() {}
};

} // namespace detail
} // namespace fdriver

#endif
