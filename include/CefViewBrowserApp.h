﻿//
//  CefViewBrowserApp.h
//  CefView
//
//  Created by Sheen Tian on 2020/6/11.
//

#ifndef CefViewBrowserApp_h
#define CefViewBrowserApp_h
#pragma once

#pragma region std_headers
#include <set>
#include <string>
#pragma endregion std_headers

#pragma region cef_headers
#include <include/cef_app.h>
#pragma endregion cef_headers

#include <CefViewBrowserAppDelegate.h>

class CefViewBrowserApp
  : public CefApp
  , public CefBrowserProcessHandler
{
public:
  CefViewBrowserApp(const std::string& bridge_name, CefViewBrowserAppDelegateInterface::RefPtr delegate);
  ~CefViewBrowserApp();

private:
  // Registers custom schemes handler factories
  static void RegisterCustomSchemesHandlerFactories();

  // Registers custom schemes. Implemented in client_app_delegates.
  static void RegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar);

#pragma region CefApp

  //////////////////////////////////////////////////////////////////////////
  // CefApp methods:
  virtual void OnBeforeCommandLineProcessing(const CefString& process_type,
                                             CefRefPtr<CefCommandLine> command_line) override;

  virtual void OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) override;

  virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;

#pragma endregion CefApp

#pragma region CefBrowserProcessHandler

  // CefBrowserProcessHandler methods:
  virtual void OnContextInitialized() override;

  virtual void OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line) override;

  virtual void OnScheduleMessagePumpWork(int64 delay_ms) override;

#pragma endregion CefBrowserProcessHandler

private:
  // The name of the bridge object
  std::string bridge_object_name_;

  // The app delegate
  CefViewBrowserAppDelegateInterface::WeakPtr app_delegate_;

  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(CefViewBrowserApp);
};

#endif
