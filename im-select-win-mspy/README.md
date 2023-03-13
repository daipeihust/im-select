# 简介

[VsCodeVim](https://github.com/VSCodeVim) 支持输入法的自动切换, 它通过一个外部的[输入法切换工具来实现](https://github.com/VSCodeVim/Vim/blob/f3f9850739e93fe5cc95827a64180fbf67fd377d/README.md#input-method), 目前这个工具推荐的是 [im-select](https://github.com/daipeihust/im-select).

由于从 Windows 10 开始, 系统默认不再安装英文键盘, 而是由输入法来提供英文输入, 而 im-select windows 版需要英文键盘, 所以在 Windows 10 上使用 VsCodeVim 时, 无法通过 im-select 来切换输入法, 也就无法通过 VsCodeVim 来切换输入法.

对于这个问题, 如果继续使用 im-select, 那么就必须安装英文键盘, 但英文键盘安装后, 切换逻辑会变得复杂.

im-select-mspy 是一个针对微软拼音输入法的输入法切换工具, 它可以在不安装英文键盘的情况下, 完成 VsCodeVim 所需要的输入法信息获取和切换.

它的原理是通过 [UIAutomation](https://learn.microsoft.com/en-us/windows/win32/winauto/entry-uiauto-win32) 来获取当前输入法的信息, 然后通过 [SendInput](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendinput) 来模拟按键来切换输入法.

尽管本项目是主要为微软拼音输入法设计的, 但是理论上也可以用于其他输入法, 可以尝试通过如下的配置来进行适配.

目前的配置如下

- `-t=任务栏` 程序通过该参数来寻找任务栏, 非简体中文系统可以设置为相应语言的名称
- `-i=托盘输入指示器\s+(\w+)` 通过该正则表达式来获取当前输入法的状态, 其他输入法可以尝试修改该正则表达式来适配
- `-k=shift` 通过该参数来设置切换输入法的快捷键, 其他输入法或使用其他快捷键可以尝试修改该参数来适配,如 `-k=ctrl+space`

上述 `-t`, `-i` 可以通过 [Accessibility Insights](https://accessibilityinsights.io/docs/windows/overview/) 工具来获取.

# 使用

使用方法参考 [VsCodeVim](https://github.com/VSCodeVim/Vim/blob/f3f9850739e93fe5cc95827a64180fbf67fd377d/README.md#input-method) 的说明.

以下是我的配置

```json
{
    "vim.autoSwitchInputMethod.enable": true,
    "vim.autoSwitchInputMethod.defaultIM": "英语模式",
    "vim.autoSwitchInputMethod.obtainIMCmd": "D:\\workspace\\im-select-mspy\\build\\Release\\im-select-mspy.exe",
    "vim.autoSwitchInputMethod.switchIMCmd": "D:\\workspace\\im-select-mspy\\build\\Release\\im-select-mspy.exe {im}",
}
```

# 编译

```
md build
cd build
cmake .. 
cmake --build . --config Release
```


