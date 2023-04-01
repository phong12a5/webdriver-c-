#ifndef FDRIVER_ELEMENT_H
#define FDRIVER_ELEMENT_H

#include "by.h"
#include "types.h"
#include "keys.h"
#include "detail/shared.h"
#include "detail/keyboard.h"
#include "detail/resource.h"
#include "detail/factories.h"
#include "detail/types.h"
#include <string>
#include <vector>
#include "fdriver_global.h"

namespace fdriver {

FDRIVER_EXPORT picojson::value CustomToJson(const Element& element);

// An element from DOM
class FDRIVER_EXPORT Element { // copyable
public:
    Element();
	
    Element(
		const std::string& ref,
		const detail::Shared<detail::Resource>& resource,
		const detail::Shared<detail::IFinderFactory>& factory
		);

    std::string GetRef() const; // Returns ID that is used by Webdriver to identify elements

    bool IsDisplayed() const;
    bool IsEnabled() const;
    bool IsSelected() const;
    Point GetLocation() const;
    Point GetLocationInView() const;
    Size GetSize() const;
    std::string GetAttribute(const std::string& name) const;
    std::string GetCssProperty(const std::string& name) const;
    std::string GetTagName() const;
    std::string GetText() const;

    Element FindElement(const By& by) const;
    std::vector<Element> FindElements(const By& by) const;

    const Element& Clear() const;
    const Element& Click() const;
    const Element& Submit() const;

    const Element& SendKeys(const std::string& keys) const;
    const Element& SendKeys(const Shortcut& shortcut) const;

    bool Equals(const Element& other) const;
    bool operator != (const Element& other) const;
    bool operator == (const Element& other) const;
    bool operator < (const Element& other) const;

private:
	detail::Resource& GetResource() const;
	detail::Keyboard GetKeyboard() const;

private:
	std::string ref_;
	detail::Shared<detail::Resource> resource_;
	detail::Shared<detail::IFinderFactory> factory_;
};

} // namespace fdriver

//#include "element.inl"

#endif
