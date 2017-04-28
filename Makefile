#*============================---(source-start)---============================*#

BASE    = hermes

#*---(standard variables)-------------*#
# must have "-x c" on gcc line so stripped files work with alternate extensions
COMP    = gcc -c -std=gnu89 -x c -g -pg -Wall -Wextra
INC     = -I/usr/include/openssl
LINK    = gcc 
LIBS    = -L/usr/local/lib -L/usr/lib64/ -lcrypto -lssl -lyLOG
LIBSS   = -L/usr/local/lib -L/usr/lib64/ -lcrypto -lssl
OBJS    = hermes_prog.o  hermes_util.o  hermes_loc.o  hermes_pkg.o  hermes_cmd.o
OBJSS   = hermes_prog.So hermes_util.So hermes_loc.So hermes_pkg.So hermes_cmd.So
#*---(make variables)-----------------*#
COPY    = cp -f  
CLEAN   = rm -f
ECHO    = @echo
PRINTF  = @printf
STRIP   = @grep -v -e " DEBUG_" -e " yLOG_" 



#*---(MAIN)---------------------------*#
#all                : hermes hermes_strip hermes_unit
all                : hermes hermes_strip



#*---(executables)--------------------*#
hermes             :         hermes_main.o   ${OBJS}
	${LINK}  -o hermes        hermes_main.o   ${OBJS}    ${LIBS}

hermes_strip       :         hermes_main.So  ${OBJSS}
	${LINK}  -o hermes_strip  hermes_main.So  ${OBJSS}   ${LIBSS}

hermes_unit        :         hermes_unit.o   ${OBJS}
	${LINK}  -o hermes_unit   hermes_unit.o   ${OBJS}    ${LIBS} -lyUNIT -lyVAR 



#*---(objects)------------------------*#
hermes_main.o      : hermes.h hermes_main.c
	${COMP}    hermes_main.c                     ${INC}
	${STRIP}   hermes_main.c   > hermes_main.Sc
	${COMP}    hermes_main.Sc -o hermes_main.So  ${INC}

hermes_prog.o      : hermes.h hermes_prog.c
	${COMP}    hermes_prog.c                     ${INC}
	${STRIP}   hermes_prog.c   > hermes_prog.Sc
	${COMP}    hermes_prog.Sc -o hermes_prog.So  ${INC}

hermes_util.o      : hermes.h hermes_util.c
	${COMP}    hermes_util.c                     ${INC}
	${STRIP}   hermes_util.c   > hermes_util.Sc
	${COMP}    hermes_util.Sc -o hermes_util.So  ${INC}

hermes_loc.o       : hermes.h hermes_loc.c
	${COMP}    hermes_loc.c                      ${INC}
	${STRIP}   hermes_loc.c    > hermes_loc.Sc  
	${COMP}    hermes_loc.Sc  -o hermes_loc.So   ${INC}

hermes_pkg.o       : hermes.h hermes_pkg.c
	${COMP}    hermes_pkg.c                      ${INC}
	${STRIP}   hermes_pkg.c    > hermes_pkg.Sc  
	${COMP}    hermes_pkg.Sc  -o hermes_pkg.So   ${INC}

hermes_cmd.o       : hermes.h hermes_cmd.c
	${COMP}    hermes_cmd.c                      ${INC}
	${STRIP}   hermes_cmd.c    > hermes_cmd.Sc  
	${COMP}    hermes_cmd.Sc  -o hermes_cmd.So   ${INC}

hermes_unit.o      : hermes.unit
	uUNIT      hermes
	${COMP}    -x c hermes_unit.code
	mv         hermes_unit.code hermes_unit.c
	${COMP}    hermes_unit.c


#*---(housecleaning)------------------*#
clean              :
	${PRINTF} "\n---cleaning------------------------------\n"
	${CLEAN}  *.o
	${CLEAN}  *~
	${CLEAN}  temp*
	${CLEAN}  hermes
	${CLEAN}  hermes*.zc
	${CLEAN}  hermes*.zo
	${CLEAN}  hermes_unit
	${CLEAN}  hermes_unit.c

bigclean           :
	${CLEAN}  .*.swp

install            : 
	${PRINTF} "\n---installing----------------------------\n"
	${COPY}   hermes     /usr/sbin/
	chmod     0700       /usr/sbin/hermes
	chown     root:root  /usr/sbin/hermes
	sha1sum   hermes
	rm -f       /usr/share/man/man8/${BASE}.8.bz2
	cp -f       ${BASE}.8    /usr/share/man/man8/
	bzip2       /usr/share/man/man8/${BASE}.8
	chmod 0644  /usr/share/man/man8/${BASE}.8.bz2

remove             :
	${CLEAN}  /usr/sbin/hermes


#*============================----(source-end)----============================*#
