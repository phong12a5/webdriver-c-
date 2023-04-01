#include "conversions.h"
#include "detail/finder.h"
#include "detail/error_handling.h"
#include "element.h"

namespace webdriver {

picojson::value CustomToJson(const Element& element) {
	detail::ElementRef ref = { element.GetRef() };
	return ToJson(ref);
}

Element::Element() {}

Element::Element(
	const std::string& ref,
	const detail::Shared<detail::Resource>& resource,
	const detail::Shared<detail::IFinderFactory>& factory
	)
	: ref_(ref)
	, resource_(resource)
	, factory_(factory)
{}

std::string Element::GetRef() const {
	return ref_;
}

bool Element::IsDisplayed() const {
	return GetResource().GetBool("displayed");
}

bool Element::IsEnabled() const {
	return GetResource().GetBool("enabled");
}

bool Element::IsSelected() const {
	return GetResource().GetBool("selected");
}

Point Element::GetLocation() const {
	return GetResource().GetValue<Point>("location");
}

Point Element::GetLocationInView() const {
	return GetResource().GetValue<Point>("location_in_view");
}

Size Element::GetSize() const {
	return GetResource().GetValue<Size>("size");
}

std::string Element::GetAttribute(const std::string& name) const {
	return GetResource().GetString(std::string("attribute/") + name);
}

std::string Element::GetCssProperty(const std::string& name) const {
	return GetResource().GetString(std::string("css/") + name);
}

std::string Element::GetTagName() const {
	return GetResource().GetString("name");
}

std::string Element::GetText() const {
	return GetResource().GetString("text");
}

Element Element::FindElement(const By& by) const {
	return factory_->MakeFinder(&GetResource()).FindElement(by);
}

std::vector<Element> Element::FindElements(const By& by) const {
	return factory_->MakeFinder(&GetResource()).FindElements(by);
}

const Element& Element::Clear() const {
	GetResource().Post("clear");
	return *this;
}

const Element& Element::Click() const {
	GetResource().Post("click");
	return *this;
}

const Element& Element::Submit() const {
	GetResource().Post("submit");
	return *this;
}

const Element& Element::SendKeys(const std::string& keys) const {
	GetKeyboard().SendKeys(keys);
	return *this;
}

const Element& Element::SendKeys(const Shortcut& shortcut) const {
	GetKeyboard().SendKeys(shortcut);
	return *this;
}

bool Element::Equals(const Element& other) const {
	return GetResource().GetBool(std::string("equals/") + other.ref_);
}

bool Element::operator != (const Element& other) const {
	return ref_ != other.ref_;
}

bool Element::operator == (const Element& other) const {
	return ref_ == other.ref_;
}

bool Element::operator < (const Element& other) const {
	return ref_ < other.ref_;
}

detail::Resource& Element::GetResource() const {
	FDRIVER_CHECK(resource_, "Attempt to use empty element");
	return *resource_;
}

detail::Keyboard Element::GetKeyboard() const
{
	return detail::Keyboard(&GetResource(), "value");
}

} // namespace webdriver
