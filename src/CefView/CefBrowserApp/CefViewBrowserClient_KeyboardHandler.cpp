#include <CefViewBrowserClient.h>

#pragma region std_headers
#include <sstream>
#include <string>
#include <algorithm>
#pragma endregion std_headers

#pragma region cef_headers
#include <include/cef_app.h>
#pragma endregion cef_headers

#include <Common/CefViewCoreLog.h>

CefRefPtr<CefKeyboardHandler>
CefViewBrowserClient::GetKeyboardHandler()
{
  return this;
}

bool
CefViewBrowserClient::OnPreKeyEvent(CefRefPtr<CefBrowser> browser,
                                    const CefKeyEvent& event,
                                    CefEventHandle os_event,
                                    bool* is_keyboard_shortcut)
{
  CEF_REQUIRE_UI_THREAD();
  // 增加按键事件，处理F5刷新和F10调用调试工具
  // TODO 禁用devtools中的F5和F10响应
  if (event.type == KEYEVENT_RAWKEYDOWN) {
    if (event.windows_key_code == VK_F5) {
      // 刷新
      browser->Reload();

      return true;
    } else if (event.windows_key_code == VK_F10) {
      // 调试控制台
      if (browser->GetHost()->HasDevTools()) {
        browser->GetHost()->CloseDevTools();
      } else {
        CefWindowInfo windowInfo;
#if defined(OS_WIN)
        windowInfo.SetAsPopup(NULL, "DevTools");
#endif
        CefBrowserSettings settings;
        browser->GetHost()->ShowDevTools(windowInfo, this, settings, CefPoint());
      }
    }
  }

  return false;
}
