::::::::::::::::::::::::::::::::::::::::::ISP_SCRIPT_START::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
@echo off
::Rem
::::::::::::: Set the Project Directory :::::::::::::::::::
@set PROJECT_DIR=%CWD%

::::::::::::: Get the Project Name from the Project Directory :::::::::::::::::::
SETLOCAL ENABLEDELAYEDEXPANSION

FOR %%a IN ("%PROJECT_DIR%") DO FOR %%b IN ("%%~dpa.") DO set PROJECT_NAME=%%~nxb

::::::::::::::: Copy the bin file from workspace to ISP build script path :::::::::::::::::::::::::::::::::::::

copy /y "%PROJECT_DIR%"\%PROJECT_NAME%.bin %~dp0\%PROJECT_NAME%.bin

::::::::::::::: Rename the studio generated hex with "%PROJECT_DIR%"\%PROJECT_NAME%_studio.hex :::::::::::::::::::::::::::::::::::::

move /y "%PROJECT_DIR%"\%PROJECT_NAME%.hex "%PROJECT_DIR%"\%PROJECT_NAME%_studio.hex

:::::::::::::::::::set current directory to ISP generation script path:::::::::::::::::::::::::::
cd "%~dp0"
:::::::::::::::::::::::::calculating and adding CRC to the project.bin::::::::::::::::::::::::::::::
srec_cat.exe %PROJECT_NAME%.bin -Binary -byte-swap 4 -o demo_image_hex -MEM 32

ssed.exe "s/.*/0x&,/" demo_image_hex > new.txt

ssed.exe "1,10d" new.txt > demo_image_hex

gcc.exe -DM4_CRC -I ./ ./gen_isp/prepare_image_header.c ./gen_isp/crc_calc.c -o crc_header

"crc_header.exe" > header.h

gcc.exe -I ./ -c ./gen_isp/image_header.c -o header 
objcopy.exe -O binary header -j .data crc.bin
move /y "crc.bin" "%PROJECT_NAME%.bin" >nul
del header.h
@echo "M4 CRC IMAGE READY"

:::::::::::::::taking the rom starting address from the linker file generated by Simplicity Studio ::::::::::::::::::::
cd %CWD%
PUSHD %CD%
CD ..\autogen
FOR /F "tokens=*" %%g IN ('dir *.ld /b') do (SET VAR=%%g)

@set p=%CD%\
FOR /f "tokens= 6 delims=, " %%i in ('findstr /R "\<rom" %p%\%VAR%') do set address=%%i
@echo Generating .RPS format from address %address%

POPD
cd "%~dp0"
:::::::::::::creating the ISP header with starting address magic no and IVT offset::::::::::::::::::
gcc.exe gen_isp/foperation.c -o F_operation
"F_operation.exe" 1 offset.h %address% 0x0
gcc.exe -I ./ gen_isp/boot_desc.c -o desc
objcopy.exe  -O binary desc.exe -j .secondboot_ds_mem desc.bin
"F_operation.exe" 0 desc.bin 4032
type desc.bin %PROJECT_NAME%.bin > m4_image.bin
srec_cat.exe m4_image.bin -Binary -byte-swap 4 -o pmemdata_qspi_hex -MEM 32

ssed.exe "s/.*/0x&,/" pmemdata_qspi_hex > new.txt
ssed.exe "1,10d" new.txt > pmemdata_qspi_hex

::::::::::::calculating CRC for the whole image (ISP header + project.bin with crc):::::::::::::::::
gcc.exe -I ./ -I./gen_isp/ ./gen_isp/prepare_image_header.c ./gen_isp/crc_calc.c  -o prepare_header
set /a offset = %address% - 4096
set /a head_address = %address% - 134221824
"prepare_header.exe" %head_address% 1 0 9 > header.h
gcc.exe -I ./ -c ./gen_isp/image_header.c -o header 
objcopy.exe  -O binary header -j .data %PROJECT_NAME%_isp.bin
@echo ISP format Generated successfully
srec_cat.exe %PROJECT_NAME%_isp.bin -Binary -offset %offset% -o %PROJECT_NAME%.hex -Intel

:::::::::::::::::copy the generated binaries current project:::::::::::::::

xcopy /s/y/I %PROJECT_NAME%.hex "%PROJECT_DIR%"\
xcopy /s/y/I %PROJECT_NAME%.bin "%PROJECT_DIR%"\
xcopy /s/y 	 %PROJECT_NAME%_isp.bin "%PROJECT_DIR%"\

::::::::::::::::::delete the intermediate files generated by the script:::::::::::::::::::::::::::::
del /f %PROJECT_NAME%.hex, %PROJECT_NAME%.bin,%PROJECT_NAME%_isp.bin, desc.exe
del /f header, header.h, desc.bin, m4_image.bin, append_hex, pmemdata_qspi_hex,  prepare_header.exe
del /f pmemdata_append_hex, F_operation.exe, offset.h, demo_image_hex, crc_header.exe, new.txt
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::::::::::::::::::::ISP_SCRIPT_END:::::::::::::::::::::::::::::::::::::::::::

