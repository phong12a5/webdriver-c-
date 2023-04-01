#include "../conversions.h"
#include "../element.h"
#include "types.h"
#include <algorithm>
#include "finder.h"

namespace webdriver {
namespace detail {

Element Finder::FindElement(const By& by) const {
	FDRIVER_FUNCTION_CONTEXT_BEGIN()
	return factory_->MakeElement(FromJson<ElementRef>(
		context_->Post("element", JsonObject()
			.Set("using", by.GetStrategy())
			.Set("value", by.GetValue())
		)).ref);
	FDRIVER_FUNCTION_CONTEXT_END_EX(Fmt()
		<< "context: " << context_->GetUrl()
		<< ", strategy: " << by.GetStrategy()
		<< ", value: " << by.GetValue()
		)
}

std::vector<Element> Finder::FindElements(const By& by) const {
	FDRIVER_FUNCTION_CONTEXT_BEGIN()
	const auto ids =
		FromJson<std::vector<ElementRef>>(
			context_->Post("elements", JsonObject()
				.Set("using", by.GetStrategy())
				.Set("value", by.GetValue())
			));
	std::vector<Element> result;
	result.reserve(ids.size());
	std::transform(ids.begin(), ids.end(), std::back_inserter(result),
		[this](const ElementRef& element_ref) {
			return factory_->MakeElement(element_ref.ref);
		});
	return result;
	FDRIVER_FUNCTION_CONTEXT_END_EX(Fmt()
		<< "context: " << context_->GetUrl()
		<< ", strategy: " << by.GetStrategy()
		<< ", value: " << by.GetValue()
		)
}

} // namespace detail
} // namespace webdriver
