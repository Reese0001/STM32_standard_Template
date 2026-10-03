@echo off
REM ============================================================
REM  Keil 工程清理脚本
REM  清理所有编译中间文件, 保持工程目录干净
REM  使用方法: 双击运行或命令行执行 keilkill.bat
REM ============================================================
echo [KeilKill] Cleaning build artifacts...

REM -- 通用编译中间文件 --
del /s /q *.bak       2>nul
del /s /q *.dep       2>nul
del /s /q *.crf       2>nul
del /s /q *.d         2>nul
del /s /q *.o         2>nul
del /s /q *.axf       2>nul
del /s /q *.lst       2>nul
del /s /q *.lnp       2>nul
del /s /q *.mpf       2>nul
del /s /q *.mpj       2>nul
del /s /q *.obj       2>nul
del /s /q *.omf       2>nul
del /s /q *.plg       2>nul
del /s /q *.rpt       2>nul
del /s /q *.tmp       2>nul
del /s /q *.__i       2>nul
del /s /q *.tra       2>nul
del /s /q *.iex       2>nul

REM -- 链接/列表输出 --
del /s /q *.htm       2>nul
del /s /q *.sct       2>nul
del /s /q *.map       2>nul
del /s /q *.hex       2>nul
del /s /q *.bin       2>nul
del /s /q *.elf       2>nul

REM -- Keil 专用 --
del /s /q *.ddk       2>nul
del /s /q *.edk       2>nul

REM -- J-Link 日志 --
del /s /q JLinkLog.txt 2>nul

REM -- UV4 用户布局备份 (按需打开) --
REM del /s /q *.uvguix.* 2>nul

echo [KeilKill] Done.
exit /b 0
