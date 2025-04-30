# Introduction
[VsCodeVim](https://github.com/VSCodeVim) supports automatic input method switching, which is implemented through an external input method switching tool. Currently, the recommended tool is[im-select](https://github.com/daipeihust/im-select).

However, starting from Windows 10, the system no longer installs an English keyboard by default and instead relies on the input method to provide English input. but im-select for Windows requires an English keyboard, making it impossible to switch input methods using im-select when using VsCodeVim on Windows 10 or later.

To address this issue, if one continues to use im-select, an English keyboard must be installed, which can complicate the switching logic. im-select-mspy is an input method switching tool specifically designed for Microsoft Pinyin input method. It can obtain and switch input method information needed by VsCodeVim without the need to install an English keyboard.

The tool works by using [UIAutomation](https://learn.microsoft.com/en-us/windows/win32/winauto/entry-uiauto-win32)  to obtain information about the current input method and then using [SendInput](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendinput)  to simulate keystrokes to switch input methods.

Although this project is mainly designed for Microsoft Pinyin input method, it can theoretically be used for other input methods by modifying the configuration as follows.

The current configuration is as follows:

- `-t=任务栏`: the tool uses this parameter to find the taskbar. For non-Simplified Chinese systems, it can be set to the name of the corresponding language.
- `-i=托盘输入指示器\s+(\w+):` this regular expression is used to obtain the current input method status. Other input methods can try to modify this regular expression to adapt.
- `-k=shift`: this parameter sets the shortcut key for switching input methods. Other input methods or using other shortcut keys can try to modify this parameter to adapt, such as -k=ctrl+space. \
  If special keys that are difficult to input are required for switching input methods, you can specify the hexadecimal representation of [Virtual Keys codes], such as -k=ctrl+0x7C which represents ctrl+F13.

However, if the taskbar auto-hide function is enabled, the program may fail to obtain the tray input indicator button.
In this case, one solution is to enable the Microsoft Pinyin *Input Method Toolbar* (note that this is not the Windows system's *Desktop Language Bar*). 
You can refer to [Microsoft Simplified Chinese IME] to learn how to enable it.

When the button cannot be obtained from the taskbar, the program will try to obtain the input method status from the input method toolbar, with the following additional configurations:

- `--toolbar="Windows 输入体验"`: the tool uses this parameter to find the input method toolbar. For non-Simplified Chinese systems, it can be set to the name of the corresponding language.
- `--toolbar-i="中/英文, (\\w+)"`: this regular expression is used to obtain the current input method status from the toolbar. Other input methods can try to modify this regular expression to adapt.

The above `-t`, `-i`, `--toolbar`, and `--toolbar-i` parameters can be obtained using the [Accessibility Insights](https://accessibilityinsights.io/docs/windows/overview/) .

[Virtual Keys codes]: https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
[Microsoft Simplified Chinese IME]: https://support.microsoft.com/en-us/windows/microsoft-simplified-chinese-ime-9b962a3b-2fa4-4f37-811c-b1886320dd72

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

Example of usage in the command line:

```shell
# Check current status
$ im-select-mspy.exe
# Switch to Chinese mode
$ im-select-mspy.exe -k="ctrl+shift+space" "中文模式"
# English UI
$ im-select-mspy.exe -t="Taskbar" -i="Tray Input Indicator (.+)" --toolbar="Windows Input Experience" --toolbar-i="Chinese/English \(Shift\), (.+)" "Chinese mode"
```

# Compilation

```
md build
cd build
cmake .. 
cmake --build . --config Release
```


