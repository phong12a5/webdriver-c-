#include "window.h"

namespace webdriver {
std::string Window::GetHandle() const {
    return handle_;
}

Size Window::GetSize() const {
    return resource_->GetValue<Size>("size");
}

const Window& Window::SetSize(const Size& size) const {
    resource_->PostValue("size", size);
    return *this;
}

Point Window::GetPosition() const {
    return resource_->GetValue<Point>("position");
}

const Window& Window::SetPosition(const Point& position) const {
    resource_->PostValue("position", position);
    return *this;
}

const Window& Window::Maximize() const {
    resource_->Post("maximize");
    return *this;
}

} // namespace webdriver
