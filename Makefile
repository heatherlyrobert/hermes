#================================[[ beg-code ]]================================#



#===(user defined)=========================================#
# basename of executable, header, and all code files
NAME_BASE  = hermes
# additional standard and outside libraries
LIB_STD    = -lcrypto -lssl
# all heatherly libraries used, debug versions whenever available
LIB_MINE   = -lySTR_debug
# directory for production code, no trailing slash
INST_DIR   = /usr/sbin



#===(master template)======================================#
include /usr/local/sbin/make_program



#================================[[ end-code ]]================================#



#===[[ VARABLES ]]======================================================================================================================================================#

#===(current variables)=================================================================================================================================================#
#BASE    = hermes
#DEBUG   = ${BASE}_debug
#UNIT    = ${BASE}_unit
#HDIR    = /home/system/hermes.command_verification
#IDIR    = /usr/sbin
#MDIR    = /usr/share/man/man8

#===(compilier variables)===============================================================================================================================================#
# must have "-x c" on gcc line so stripped files work with alternate extensions
#COMP    = gcc -c -std=gnu89 -x c -g -pg -Wall -Wextra
#INCS    = -I/usr/local/include -I/usr/include/openssl

#===(linker options)========================================================================================================================================================================#
#------   (0)-------------- (1)-------------- (2)-------------- (3)-------------- (4)-------------- (5)-------------- (6)-------------- (7)-------------- (8)-------------- (9)--------------
#LINK    = gcc
#LIBDIR  = -L/usr/local/lib -L/usr/lib64 
#LIBS    = ${LIBDIR}         -lcrypto          -lssl             -lySTR            -lyURG
#LIBD    = ${LIBDIR}         -lcrypto          -lssl             -lySTR_debug      -lyURG_debug      -lyLOG
#LIBU    = ${LIBD}           -lyUNIT           -lyVAR         

#===(file lists)============================================================================================================================================================================#
#------   (0)-------------- (1)-------------- (2)-------------- (3)-------------- (4)-------------- (5)-------------- (6)-------------- (7)-------------- (8)-------------- (9)-------------- (A)-------------- (B)-------------- (C)-------------- (D)-------------- (5)--------------
#HEADS   = ${BASE}.h
#OBJS    = ${BASE}_main.os   ${BASE}_prog.os   ${BASE}_util.os   ${BASE}_loc.os    ${BASE}_pkg.os    ${BASE}_cmd.os    ${BASE}_files.os
#OBJD    = ${BASE}_main.o    ${BASE}_prog.o    ${BASE}_util.o    ${BASE}_loc.o     ${BASE}_pkg.o     ${BASE}_cmd.o     ${BASE}_files.o 
#OBJU    = ${BASE}_unit.o    ${BASE}_prog.o    ${BASE}_util.o    ${BASE}_loc.o     ${BASE}_pkg.o     ${BASE}_cmd.o     ${BASE}_files.o 

#===(make variables)====================================================================================================================================================#
#COPY    = cp -f
#CLEAN   = rm -f
#PRINT   = @printf
#STRIP   = @grep -v -e " DEBUG_" -e " yLOG_" 



#===[[ EXECUTABLES ]]===================================================================================================================================================#

#all                : ${DEBUG} ${BASE} ${UNIT}

#${BASE}            : ${OBJD}
#	${LINK}  -o ${BASE}        ${OBJS}   ${LIBS}

#${DEBUG}           : ${OBJD}
#	${LINK}  -o ${DEBUG}       ${OBJD}   ${LIBD}

#${UNIT}            : ${OBJU}
#	${LINK}  -o ${UNIT}        ${OBJU}   ${LIBU}



#===[[ OBJECT FILES ]]==================================================================================================================================================#

#${BASE}_main.o     : ${HEADS}       ${BASE}_main.c
#	${COMP}    ${BASE}_main.c                           ${INC}
#	${STRIP}   ${BASE}_main.c      > ${BASE}_main.cs
#	${COMP}    ${BASE}_main.cs    -o ${BASE}_main.os    ${INC}

#${BASE}_prog.o     : ${HEADS}       ${BASE}_prog.c
#	${COMP}    ${BASE}_prog.c                           ${INC}
#	${STRIP}   ${BASE}_prog.c      > ${BASE}_prog.cs
#	${COMP}    ${BASE}_prog.cs    -o ${BASE}_prog.os    ${INC}

#${BASE}_util.o     : ${HEADS}       ${BASE}_util.c
#	${COMP}    ${BASE}_util.c                           ${INC}
#	${STRIP}   ${BASE}_util.c      > ${BASE}_util.cs
#	${COMP}    ${BASE}_util.cs    -o ${BASE}_util.os    ${INC}

#${BASE}_loc.o      : ${HEADS}       ${BASE}_loc.c 
#	${COMP}    ${BASE}_loc.c                            ${INC}
#	${STRIP}   ${BASE}_loc.c       > ${BASE}_loc.cs 
#	${COMP}    ${BASE}_loc.cs     -o ${BASE}_loc.os     ${INC}

#${BASE}_pkg.o      : ${HEADS}       ${BASE}_pkg.c 
#	${COMP}    ${BASE}_pkg.c                            ${INC}
#	${STRIP}   ${BASE}_pkg.c       > ${BASE}_pkg.cs 
#	${COMP}    ${BASE}_pkg.cs     -o ${BASE}_pkg.os     ${INC}

#${BASE}_cmd.o      : ${HEADS}       ${BASE}_cmd.c 
#	${COMP}    ${BASE}_cmd.c                            ${INC}
#	${STRIP}   ${BASE}_cmd.c       > ${BASE}_cmd.cs 
#	${COMP}    ${BASE}_cmd.cs     -o ${BASE}_cmd.os     ${INC}

#${BASE}_files.o    : ${HEADS}       ${BASE}_files.c
#	${COMP}    ${BASE}_files.c                          ${INC}
#	${STRIP}   ${BASE}_files.c     > ${BASE}_files.cs
#	${COMP}    ${BASE}_files.cs   -o ${BASE}_files.os   ${INC}

#${BASE}_unit.o     : ${BASE}.unit
#	koios    ${BASE}
#	${COMP}  ${BASE}_unit.c



#===[[ HOUSEKEPPING ]]==================================================================================================================================================#

#clean              :
#	#---(all versions)--------------------#
#	${CLEAN} ${BASE}
#	${CLEAN} ${DEBUG}
#	${CLEAN} ${UNIT}
#	#---(object and stripped files)-------#
#	${CLEAN} ${BASE}*.o
#	${CLEAN} ${BASE}*.cs
#	${CLEAN} ${BASE}*.os
#	${CLEAN} ${BASE}*.Sc
#	${CLEAN} ${BASE}*.So
#	#---(created unit code)---------------#
#	${CLEAN} ${UNIT}.code
#	${CLEAN} ${UNIT}.c
#	#---(junk files)----------------------#
#	${CLEAN} *~
#	${CLEAN} temp*

#bigclean           :
#	${CLEAN} .*.swp

#install            : ${BASE}
#	#---(production version)--------------#
#	${COPY}   ${BASE}    ${IDIR}/
#	chown     root:root  ${IDIR}/${BASE}
#	chmod     0755       ${IDIR}/${BASE}
#	@sha1sum  ${BASE}
#	#---(debug version)-------------------#
#	${COPY}  ${DEBUG}    ${IDIR}/
#	chown     root:root  ${IDIR}/${DEBUG}
#	chmod     0755       ${IDIR}/${DEBUG}
#	@sha1sum  ${DEBUG}
#	#---(man page)------------------------#
#	rm -f       ${MDIR}/${BASE}.8.bz2
#	cp -f       ${BASE}.8  ${MDIR}/
#	bzip2       ${MDIR}/${BASE}.8
#	chmod 0644  ${MDIR}/${BASE}.8.bz2

#remove             :
#	#---(all versions)--------------------#
#	${CLEAN}  ${IDIR}/${BASE}
#	${CLEAN}  ${IDIR}/${DEBUG}
#	#---(documentation)-------------------#
#	${CLEAN}  ${MDIR}/${BASE}.8.bz2



#*============================----(source-end)----============================*#
