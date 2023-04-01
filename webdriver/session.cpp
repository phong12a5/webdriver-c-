#include "conversions.h"
#include "detail/error_handling.h"
#include "detail/types.h"
#include <algorithm>
#include "session.h"

namespace webdriver {

Session::Session(const detail::Shared<detail::Resource>& resource)
    : resource_(resource)
    , factory_(new detail::SessionFactory(resource))
{}

void Session::DeleteSession() const {
	resource_->Delete();
}

Capabilities Session::GetCapabilities() const {
	return Capabilities(resource_->Get().get<picojson::object>());
}

std::string Session::GetSource() const {
	return resource_->GetString("source");
}

std::string Session::GetTitle() const {
	return resource_->GetString("title");
}

std::string Session::GetUrl() const {
	return resource_->GetString("url");
}

std::string Session::GetScreenshot() const {
	return resource_->GetString("screenshot");
}

const Session& Session::SetTimeoutMs(timeout::Type type, int milliseconds) {
	resource_->Post("timeouts",
		JsonObject()
			.Set("type", type)
			.Set("ms", milliseconds)
		);
	return *this;
}

const Session& Session::SetImplicitTimeoutMs(int milliseconds) {
	resource_->Post("timeouts/implicit_wait",
		JsonObject().Set("ms", milliseconds));
	return *this;
}

const Session& Session::SetAsyncScriptTimeoutMs(int milliseconds) {
	resource_->Post("timeouts/async_script",
		JsonObject().Set("ms", milliseconds));
	return *this;
}

Window Session::GetCurrentWindow() const {
	FDRIVER_FUNCTION_CONTEXT_BEGIN()
	return MakeWindow(resource_->GetString("window_handle"));
	FDRIVER_FUNCTION_CONTEXT_END()
}

const Session& Session::CloseCurrentWindow() const {
	resource_->Delete("window");
	return *this;
}

const Session& Session::Navigate(const std::string& url) const {
	resource_->Post("url", "url", url);
	return *this;
}

const Session& Session::Get(const std::string& url) const {
	return Navigate(url);
}

const Session& Session::Forward() const {
	resource_->Post("forward");
	return *this;
}

const Session& Session::Back() const {
	resource_->Post("back");
	return *this;
}

const Session& Session::Refresh() const {
	resource_->Post("refresh");
	return *this;
}

const Session& Session::Execute(const std::string& script, const JsArgs& args) const {
	InternalEvalJsonValue("execute", script, args);
	return *this;
}

template<typename T>
T Session::Eval(const std::string& script, const JsArgs& args) const {
	FDRIVER_FUNCTION_CONTEXT_BEGIN()
	T result = T();
	InternalEval("execute", script, args, result);
	return result;
	FDRIVER_FUNCTION_CONTEXT_END_EX(detail::Fmt()
		<< "script: " << script
		)
}

const Session& Session::ExecuteAsync(const std::string& script, const JsArgs& args) const {
	InternalEvalJsonValue("execute_async", script, args);
	return *this;
}

template<typename T>
T Session::EvalAsync(const std::string& script, const JsArgs& args) const {
	FDRIVER_FUNCTION_CONTEXT_BEGIN()
	T result;
	InternalEval("execute_async", script, args, result);
	return result;
	FDRIVER_FUNCTION_CONTEXT_END_EX(detail::Fmt()
		<< "script: " << script
		)
}

const Session& Session::SetFocusToWindow(const std::string& window_name_or_handle) const {
	resource_->Post("window", "name", window_name_or_handle);
	return *this;
}

const Session& Session::SetFocusToWindow(const Window& window) const {
	SetFocusToWindow(window.GetHandle());
	return *this;
}

const Session& Session::SetFocusToFrame(const Element& frame) const {
	return InternalSetFocusToFrame(ToJson(frame));
}

const Session& Session::SetFocusToFrame(const std::string& id) const {
	return InternalSetFocusToFrame(ToJson(id));
}

const Session& Session::SetFocusToFrame(int number) const {
	return InternalSetFocusToFrame(ToJson(number));
}

const Session& Session::SetFocusToDefaultFrame() const {
	return InternalSetFocusToFrame(picojson::value());
}

const Session& Session::SetFocusToParentFrame() const {
	resource_->Post("frame/parent");
	return *this;
}

const Session& Session::InternalSetFocusToFrame(const picojson::value& id) const {
	resource_->Post("frame", JsonObject().Set("id", id));
	return *this;
}

std::vector<Window> Session::GetWindows() const {
	FDRIVER_FUNCTION_CONTEXT_BEGIN()
	const auto handles =
		FromJson<std::vector<std::string>>(
			resource_->Get("window_handles")
			);
	std::vector<Window> result;
	result.reserve(handles.size());
	std::transform(handles.begin(), handles.end(), std::back_inserter(result),
		[this](const std::string& window_handle){
			return MakeWindow(window_handle);
		});
	return result;
	FDRIVER_FUNCTION_CONTEXT_END()
}

Element Session::GetActiveElement() const {
	FDRIVER_FUNCTION_CONTEXT_BEGIN()
	return factory_->MakeElement(FromJson<detail::ElementRef>(resource_->Post("element/active")).ref);
	FDRIVER_FUNCTION_CONTEXT_END()
}

Element Session::FindElement(const By& by) const {
	return factory_->MakeFinder(resource_).FindElement(by);
}

std::vector<Element> Session::FindElements(const By& by) const {
	return factory_->MakeFinder(resource_).FindElements(by);
}

std::vector<Cookie> Session::GetCookies() const {
	FDRIVER_FUNCTION_CONTEXT_BEGIN()
	return FromJson<std::vector<Cookie>>(resource_->Get("cookie"));
	FDRIVER_FUNCTION_CONTEXT_END()
}

const Session& Session::SetCookie(const Cookie& cookie) const {
	resource_->Post("cookie", JsonObject()
		.Set("cookie", ToJson(cookie)));
	return *this;
}

const Session& Session::DeleteCookies() const {
	resource_->Delete("cookie");
	return *this;
}

const Session& Session::DeleteCookie(const std::string& name) const {
	resource_->Delete(std::string("cookie/") + name);
	return *this;
}

std::string Session::GetAlertText() const {
	return resource_->GetString("alert_text");
}

const Session& Session::SendKeysToAlert(const std::string& text) const {
	resource_->Post("alert_text", "text", text);
	return *this;
}

const Session& Session::AcceptAlert() const {
	resource_->Post("accept_alert");
	return *this;
}

const Session& Session::DismissAlert() const {
	resource_->Post("dismiss_alert");
	return *this;
}

const Session& Session::SendKeys(const std::string& keys) const {
	GetKeyboard().SendKeys(keys);
	return *this;
}

const Session& Session::SendKeys(const Shortcut& shortcut) const {
	GetKeyboard().SendKeys(shortcut);
	return *this;
}

const Session& Session::MoveToTopLeftOf(const Element& element, const Offset& offset) const {
	return InternalMoveTo(&element, &offset);
}

const Session& Session::MoveToCenterOf(const Element& element) const {
	return InternalMoveTo(&element, nullptr);
}

const Session& Session::MoveTo(const Offset& offset) const {
	return InternalMoveTo(nullptr, &offset);
}

const Session& Session::InternalMoveTo(
	const Element* element,
	const Offset* offset
	) const {
	JsonObject args;
	if (element)
		args.Set("element", element->GetRef());
	if (offset) {
		args.Set("xoffset", offset->x);
		args.Set("yoffset", offset->y);
	}
	resource_->Post("moveto", args);
	return *this;
}

const Session& Session::Click(mouse::Button button) const {
	return InternalMouseButtonCommand("click", button);
}

const Session& Session::DoubleClick() const {
	resource_->Post("doubleclick");
	return *this;
}

const Session& Session::ButtonDown(mouse::Button button) const {
	return InternalMouseButtonCommand("buttondown", button);
}

const Session& Session::ButtonUp(mouse::Button button) const {
	return InternalMouseButtonCommand("buttonup", button);
}

const Session& Session::InternalMouseButtonCommand(const char* command, mouse::Button button) const {
	resource_->Post(command, "button", static_cast<int>(button));
	return *this;
}

Window Session::MakeWindow(const std::string& handle) const {
	return Window(handle,
		detail::MakeSubResource(resource_, "window", handle)
		);
}

detail::Keyboard Session::GetKeyboard() const
{
	return detail::Keyboard(resource_, "keys");
}

template<typename T>
void Session::InternalEval(const std::string& fdriver_command,
	const std::string& script, const JsArgs& args,
	T& result) const {
    result = FromJson<T>(InternalEvalJsonValue(fdriver_command, script, args));
}

void Session::InternalEval(const std::string& fdriver_command,
	const std::string& script, const JsArgs& args,
	Element& result) const {
	detail::ElementRef element_ref;
    InternalEval(fdriver_command, script, args, element_ref);
	result = factory_->MakeElement(element_ref.ref);
}

picojson::value Session::InternalEvalJsonValue(
    const std::string& fdriver_command,
	const std::string& script,
	const JsArgs& args
	) const {
    return resource_->Post(fdriver_command,
		JsonObject()
			.Set("script", script)
			.Set("args", args.args_)
		);
}

} // namespace webdriver
