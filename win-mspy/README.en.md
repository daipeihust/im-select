# Introduction
[VsCodeVim](https://github.com/VSCodeVim) supports automatic input method switching, which is implemented through an external input method switching tool. Currently, the recommended tool is[im-select](https://github.com/daipeihust/im-select).

However, starting from Windows 10, the system no longer installs an English keyboard by default and instead relies on the input method to provide English input. but im-select for Windows requires an English keyboard, making it impossible to switch input methods using im-select when using VsCodeVim on Windows 10 or later.

To address this issue, if one continues to use im-select, an English keyboard must be installed, which can complicate the switching logic. im-select-mspy is an input method switching tool specifically designed for Microsoft Pinyin input method. It can obtain and switch input method information needed by VsCodeVim without the need to install an English keyboard.

The tool works by using [UIAutomation](https://learn.microsoft.com/en-us/windows/win32/winauto/entry-uiauto-win32)  to obtain information about the current input method and then using [SendInput](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendinput)  to simulate keystrokes to switch input methods.

Although this project is mainly designed for Microsoft Pinyin input method, it can theoretically be used for other input methods by modifying the configuration as follows.

The current configuration is as follows:

-t=任务栏: the tool uses this parameter to find the taskbar. For non-Simplified Chinese systems, it can be set to the name of the corresponding language.
-i=托盘输入指示器\s+(\w+): this regular expression is used to obtain the current input method status. Other input methods can try to modify this regular expression to adapt.
-k=shift: this parameter sets the shortcut key for switching input methods. Other input methods or using other shortcut keys can try to modify this parameter to adapt, such as -k=ctrl+space.

The -t and -i parameters can be obtained using the [Accessibility Insights](https://accessibilityinsights.io/docs/windows/overview/) .

# Usage
Refer to the instructions in [VsCodeVim](https://github.com/VSCodeVim/Vim/blob/f3f9850739e93fe5cc95827a64180fbf67fd377d/README.md#input-method).

Here is my configuration:

```json
{
    "vim.autoSwitchInputMethod.enable": true,
    "vim.autoSwitchInputMethod.defaultIM": "英语模式",
    "vim.autoSwitchInputMethod.obtainIMCmd": "D:\\workspace\\im-select-mspy\\build\\Release\\im-select-mspy.exe",
    "vim.autoSwitchInputMethod.switchIMCmd": "D:\\workspace\\im-select-mspy\\build\\Release\\im-select-mspy.exe {im}",
}
```

# Compilation

```
md build
cd build
cmake .. 
cmake --build . --config Release
```


