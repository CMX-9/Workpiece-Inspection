dir .\sdk /ad /b > sdk.txt

rem for /r %%a in (debug release) do @echo %%a

attrib .\*.suo -h 

del /f /s /q .\*.ncb 
del /f /s /q .\*.opt 
del /f /s /q .\*.plg
del /f /s /q .\*.obj 
del /f /s /q .\*.pdb
del /f /s /q .\*.suo
del /f /s /q .\*.user
del /f /s /q .\*.aps
del /f /s /q .\*.old
del /f /s /q .\Debug
del /f /s /q .\Release
del /f /s /q .\*.bak

for /r %%a in (debug release obj objchk objfre plg) do  rd /s /q %%a

del sdk.txt
