
#define UNICODE

#include <Windows.h>
#include <UIAutomation.h>
#include <iostream>
#include <string>
#include <comip.h>
#include <comdef.h>
#include <vector>
#include <regex>
#include <WinUser.h>
#include <cctype>
#include <algorithm>
#include <locale>

using namespace std;


typedef _com_ptr_t<_com_IIID<IUIAutomation, &__uuidof(IUIAutomation)>> IUIAutomationPtr;
typedef _com_ptr_t<_com_IIID<IUIAutomationElement, &__uuidof(IUIAutomationElement)>> IUIAutomationElementPtr;
typedef _com_ptr_t<_com_IIID<IUIAutomationCondition, &__uuidof(IUIAutomationCondition)>> IUIAutomationConditionPtr;
typedef _com_ptr_t<_com_IIID<IUIAutomationElementArray, &__uuidof(IUIAutomationElementArray)>> IUIAutomationElementArrayPtr;
typedef _com_ptr_t<_com_IIID<IUIAutomationInvokePattern, &__uuidof(IUIAutomationInvokePattern)>> IUIAutomationInvokePatternPtr;


// command line options
struct CliOptions
{
  // no prefix
  wstring mode;
  // -k= 
  wstring switch_keys;
  // -t=
  wstring taskbar_name;
  // -i=
  wstring ime_capture_re;
  // --toolbar=
  wstring toolbar_name;
  // --toolbar_i=
  wstring toolbar_ime_capture_re;

  wregex ime_capture;
  wregex toolbar_ime_capture;
};

// ime button in taskbar
struct ImeButton
{
  wstring current_mode;
  IUIAutomationElementPtr pElement;
};

wstring get_element_name(IUIAutomationElementPtr pElement)
{
  _bstr_t name;
  pElement->get_CurrentName(name.GetAddress());
  if (name.length() > 0)
  {
    return wstring((const wchar_t*)name);
  }
  else
  {
    return L"";
  }
}

vector<wstring> split_string(const wstring & str, const wstring & delim)
{
  vector<string> result;
  wregex re(delim);
  wsregex_token_iterator first{ str.begin(), str.end(), re, -1 }, last;
  return { first, last };
}

SHORT vk_from_text(const wstring & text) {
  if (text == L"shift") {
    return VK_SHIFT;
  }
  if (text == L"ctrl") {
    return VK_CONTROL;
  }
  if (text == L"alt") {
    return VK_MENU;
  }
  if (text == L"win") {
    return VK_LWIN;
  }
  if (text == L"space") {
    return VK_SPACE;
  }
  // Check for hexadecimal format (0xhh)
  // such that 0x1F means VK_MODECHANGE
  if (text.length() == 4 && text.substr(0, 2) == L"0x") {
    try {
      return static_cast<SHORT>(std::stoi(text.substr(2), nullptr, 16));
    }
    catch (...) {
    }
  }
  return 0;
}

vector<INPUT> get_input_from_string(wstring str)
{
  vector<INPUT> result;
  transform(str.begin(), str.end(), str.begin(), ::tolower);
  auto keys = split_string(str, L"\\+");
  transform(keys.begin(), keys.end(), back_insert_iterator(result), [](const wstring & key) {
    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = vk_from_text(key);
    return input;
  });
  transform(keys.rbegin(), keys.rend(), back_insert_iterator(result), [](const wstring & key) {
    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = vk_from_text(key);
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    return input;
  });
  return result;
}




ImeButton get_ime_button(const CliOptions & options) {
  IUIAutomationPtr pAutomation;
  IUIAutomationElementPtr pDesktop;
  IUIAutomationElementPtr pTaskBar;
  IUIAutomationConditionPtr pCondition;

  auto hr = pAutomation.CreateInstance(CLSID_CUIAutomation);

  pAutomation->GetRootElement(&pDesktop);

  pAutomation->CreatePropertyCondition(UIA_NamePropertyId, _variant_t(options.taskbar_name.c_str()), &pCondition);

  hr = pDesktop->FindFirst(TreeScope_Children, pCondition, &pTaskBar);

  pAutomation->CreatePropertyCondition(UIA_ControlTypePropertyId, _variant_t(UIA_ButtonControlTypeId), &pCondition);

  IUIAutomationElementArrayPtr arrButtons;
  pTaskBar->FindAll(TreeScope_Descendants, pCondition, &arrButtons);

  int length = 0;
  arrButtons->get_Length(&length);
  for (int i = 0; i < length; i++)
  {
    IUIAutomationElementPtr pButton;
    arrButtons->GetElement(i, &pButton);
    auto name = get_element_name(pButton);

    wsmatch match;
    if (regex_search(name, match, options.ime_capture)) {
      return { match[1], pButton };
    }
  }
  return { L"", nullptr };
}

/**
 * Look for the mode switch button in the IME toolbar
 * Suitable as a fallback solution when the tray input indicator is set to auto-hide along with the taskbar
 * Requires the IME toolbar to be enabled first, and ensure the "中/英文" button is displayed in the toolbar
 */
ImeButton get_ime_button_from_toolbar(const CliOptions &options) {
  IUIAutomationPtr pAutomation;
  IUIAutomationElementPtr pDesktop;
  IUIAutomationElementPtr pInputPanel;
  IUIAutomationConditionPtr pCondition;
  IUIAutomationElementArrayPtr arrButtons;

  // UI Layout Structure:
  // Element: Windows 输入体验
  //   Element: 简体中文工具栏菜单列表
  //     Element: 中/英文, 英语模式
  //     Element: 设置

  pAutomation.CreateInstance(CLSID_CUIAutomation);
  pAutomation->GetRootElement(&pDesktop);
  pAutomation->CreatePropertyCondition(UIA_NamePropertyId, _variant_t(options.toolbar_name.c_str()), &pCondition);
  pDesktop->FindFirst(TreeScope_Descendants, pCondition, &pInputPanel);
  if (pInputPanel == nullptr)
  {
    return { L"", nullptr };
  }

  pAutomation->CreatePropertyCondition(UIA_ControlTypePropertyId, _variant_t(UIA_ListItemControlTypeId), &pCondition);
  pInputPanel->FindAll(TreeScope_Descendants, pCondition, &arrButtons);
  int length = 0;
  arrButtons->get_Length(&length);
  for (int i = 0; i < length; i++)
  {
    IUIAutomationElementPtr pButton;
    arrButtons->GetElement(i, &pButton);
    auto name = get_element_name(pButton);
    if (wsmatch match; regex_search(name, match, options.toolbar_ime_capture))
    {
      return {match[1], pButton};
    }
  }
  return {L"", nullptr};
}

// default chinese options
CliOptions chinese_options()
{
  CliOptions options;
  options.taskbar_name = L"任务栏";
  options.ime_capture_re = L"托盘输入指示器\\s+(\\w+)"; //\\s+(\\S+)\\s*.+";
  options.switch_keys = L"shift";
  options.toolbar_name = L"Windows 输入体验";
  options.toolbar_ime_capture_re = L"中/英文, (\\w+)";
  return options;
}

// parse command line options
CliOptions parse_options(int argc, wchar_t * argv[])
{
  CliOptions options = chinese_options();
  for (int i = 1; i < argc; i++)
  {
    auto arg = argv[i];
    if (arg[0] == L'-')
    {
      auto pos = wcschr(arg, L'=');
      if (pos)
      {
        auto key = wstring(arg + 1, pos);
        auto value = wstring(pos + 1);
        if (key == L"k")
        {
          options.switch_keys = value;
        }
        else if (key == L"t")
        {
          options.taskbar_name = value;
        }
        else if (key == L"i")
        {
          options.ime_capture_re = value;
        }
        else if (key == L"-toolbar")
        {
          options.toolbar_name = value;
        }
        else if (key == L"-toolbar-i")
        {
          options.toolbar_ime_capture_re = value;
        }
      }
    }
    else
    {
      options.mode = arg;
    }
  }
  if (options.ime_capture_re.length() > 0)
  {
    options.ime_capture = wregex(options.ime_capture_re);
  }
  if (options.toolbar_ime_capture_re.length() > 0)
  {
    options.toolbar_ime_capture = wregex(options.toolbar_ime_capture_re);
  }
  return options;
}

void print_options(const CliOptions & options)
{
  wcout << L"taskbar name: " << options.taskbar_name << endl;
  wcout << L"ime capture: " << options.ime_capture_re << endl;
  wcout << L"switch keys: " << options.switch_keys << endl;
  wcout << L"toolbar name(--toolbar): " << options.toolbar_name << endl;
  wcout << L"toolbar ime capture(--toolbar-i): " << options.toolbar_ime_capture_re << endl;
  wcout << L"mode: " << options.mode << endl;
}


int wmain(int argc, wchar_t * argv[])
{
  std::ios::sync_with_stdio(false);
  std::locale::global( std::locale("") );


  auto options = parse_options(argc, argv);

  //print_options(options);

  CoInitialize(NULL);

  ImeButton ime_button;

  try {
    ime_button = get_ime_button(options);
  }
  catch (_com_error&  e)
  {
    wcout << L"get ime button failed: " << e.ErrorMessage() << endl;
    return 1;
  }

  if (!ime_button.pElement) {
    // Perhaps the taskbar is hidden. Try finding the toggle button in the toolbar.
    ime_button = get_ime_button_from_toolbar(options);
  }

  if (!ime_button.pElement)
  {
    return 1;
  }


  if (options.mode.empty())
  {
    // get current mode
    wcout << ime_button.current_mode << endl;
  }
  else
  {
    // do switch
    if (options.mode != ime_button.current_mode)
    {
      auto input = get_input_from_string(options.switch_keys);
      SendInput((UINT)input.size(), input.data(), sizeof(input[0]));
    }
  }


  CoUninitialize();
  return 0;
}