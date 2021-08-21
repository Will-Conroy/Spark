@ECHO on

SET bin_dir=bin
SET code_dir=code
SET source_files=%code_dir%\magicVWAP.cpp %code_dir%\input.cpp %code_dir%\stocks.cpp %code_dir%\stock.cpp
SET main_file=%code_dir%\main.cpp
SET executable=%bin_dir%\magicVWAP.exe

COPY bin\magicVWAP2.exe bin\magicVWAP.exe

:compile
IF NOT EXIST %bin_dir% MKDIR %bin_dir%
IF EXIST %executable% DEL %executable%
g++ --std=c++14 -Wall %source_files% %main_file% -o %executable%

:end