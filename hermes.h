/*===============================[[ beg-code ]]===============================*/

/*===[[ HEADER ]]=============================================================*/
/*
 *   focus         : SYS, system administration
 *   niche         : CM,  configuration management
 *   application   : hermes-diactoros  (god of boundaries and transitions)
 *   purpose       : assure executable file integrity, sourcing, and versioning
 *
 *   base_system   : gnu/linux   (powerful, ubiquitous, technical, and hackable)
 *   lang_name     : ansi-c      (wicked, limitless, universal, and everlasting)
 *   dependencies  : none
 *   size          : small       (approximately 1,000 slocL)
 * 
 *   author        : rsheatherly
 *   created       : 2013-08
 *   priorities    : direct, simple, brief, vigorous, and lucid (h.w. fowler)
 */


/*===[[ REASONING ]]==========================================================*/
/*
 *
 *   problem statement (p) ---------------------------------
 *
 *   any working system can be subverted by altering programs, misdirecting
 *   command requests, or causing different code to execute.  given the
 *   complexity of and continuous changes to an average system, it is an
 *   impossible task to prevent or forstall these attacks without targeted
 *   tools, vigilence, and clear rules.
 */
/*
 *   requirement and reward (rr)---------------------------
 *
 *   file integrity monitoring (fim) is the process of validating the integrity
 *   of operating system and application software files against a known, good
 *   baseline.  the comparison often involves calculating a cryptographic
 *   checksum, reviewing permissions and credentials, attributes, and
 *   other configuration elements, then comparing those against a baseline.
 *   benefits are expected to be...
 *
 *      -- rapid identification of file alteration
 *      -- reduce opportunity for malicious system alteration
 *      -- reduce exposure window if a malicious change happens
 *      -- reduce chances that the alteration spreads to other systems
 *      -- make integrity monitoring a lights-out activity
 */
/*
 *   objectives (o) ---------------------------------------
 *
 *   file integrity management objectives accepted...
 *      -- keep a baseline of authoritative file statistics
 *      -- audit current system status regularly to identify changes
 *      -- report back the findings from those audits
 *      -- allow for updating baseline, log only, immediate notification
 *      -- compare files based on a crytographic hash of the contents
 *      -- extend the comparison to permissions and attributes also
 * 
 *   file integrity management objectives rejected...
 *      -- not allow general purpose scripting to address additional needs
 *      -- not use ticketing system for change tracking (change control is out)
 *      -- not work on any non-heatherly systems (why would i care)
 *      -- not maintain anything other than gentoo-linux systems (enough said)
 *      -- not alter users or groups on a system (user management is separate)
 *      -- not update software versions (package management is separate)
 *
 *   hermes will add the following capabilities to its monitoring...
 *      -- idenfity the source of each executable on the system
 *      -- monitor executable sources for version updates
 *      -- report back versioning information from the review
 *      -- coordinate with portage updates to avoid false warnings
 *
 *   above all, it is all about...
 *      -- learning the key niches in computer and system work
 *      -- expanding my knowledge base in useful ways
 *      -- becoming a more masterful and stronger system programmer
 * 
 *   as always, applications running on my systems must...
 *      -- forgo sloppy, kitchen-sink languages, like python, java, or perl
 *      -- stay focused, small, tight, reliable, and secure
 *      -- only use human maintainable, 7-bit safe, ascii input/output files
 *      -- have dedicated, maintained, automated unit testing
 *      -- provide either detailed reporting or logging for debugging
 *      -- use secure communications between systems where required
 *      -- clean, clean code so i can maintain after long absences
 *      -- no international, multi-language, multi-byte support (freaking ever)
 */
/*
 *   alternatives (a) -------------------------------------
 *
 *   there are four main camps of software i could use for configuration
 *   managements on my systems.
 *
 *   1) top-rated, commercial-grade packages
 *       -- tripwire
 *       -- aide
 *       -- qualys
 *       -- verisys
 *
 *   2) open-source alternative packages
 *
 *   3) custom integration of multiple existing tools
 *
 *   4) custom built software
 */
/*
 *   consequences (c) -------------------------------------
 *
 *   1) top-rated, commercial-grade packages
 *      ++ full capabilities built in
 *      ++ learn a system that would likely be used on the job
 *      ++ few basic execution headaches
 *      -- way over-built and huge
 *      -- no access to source code to learn (or too much to learn from)
 *      -- would only be a user and never learn to do it
 *      -- require interpretive languages and tons of libraries
 *
 *   2) open-source alternative packages
 *      ++ full capabilities built in
 *      ++ few basic execution headaches
 *      ++ supported and maintained
 *      -- way over-built and huge
 *      -- no access to source code to learn (or too much to learn from)
 *      -- would only be a user and never learn to do it
 *      -- more libraries, harnesses, and support software
 *
 *   3) smaller open-source tools
 *      ++ smaller size applications
 *      ++ learn a great deal more by integrating
 *      -- have to piece it together and integrate myself
 *      -- version inconsistency issues between tools
 *      -- much harder to maintain
 *
 *   4) custom
 *      ++ learn the core requirements and implementation
 *      ++ further my understanding of the linux system
 *      ++ further my programming skills and learning
 *      ++ does exactly what i want
 *      -- no automatic access to the latest best practices and thinking
 *      -- much more work
 */
/*
 *   trade-offs and decision (td)--------------------------
 *
 *   this is a very important systems niche and one i will have to grapple with
 *   personnally as well as expand to robotics and electronics.  that, though,
 *   still leaves all four options open if the niche is nicely covered.  but,
 *   a system administrator focuses on learning the latest commercial
 *   applications and concepts in order to compete for jobs.  i will never
 *   be able to complete with those folks or stand the work they do.
 *
 *   so, since the packaged applications are over-built and written in
 *   interpretive, fat, hoggish interpretive languages prone to version and
 *   library hell, they are out.
 *
 *   this is too important to take lightly and an area that i will have to
 *   master to keep my vision alive.  custom it is.
 */
/*
 *   epilogue ---------------------------------------------
 *
 *   so, as always, there are many, stable, accepted, existing programs and
 *   utilities written by better programmers which are likely superior in
 *   speed, size, capability, and reliability; BUT, i would not have learned
 *   nearly as much just using them, so i follow the adage..
 *
 *   i don't want to just use the system, i want to *own* it; so that means
 *   i have to fundmentally understand the critical services which only tearing
 *   down and rebuilding can really teach -- even if its more basic in the end.
 *
 *   TO TRULY LEARN> do not seek to follow in the footsteps of the men of old;
 *   seek what they sought ~ Matsuo Basho
 *
 */



/*===[[ PUBLIC HEADERS ]]=====================================================*/

/*---(big standards)------------*/
#include    <stdio.h>
#include    <stdlib.h>            /* exit, system, ...                        */
#include    <string.h>            /* strcat, strcpy, strlen, ...              */
#include    <unistd.h>            /* readlink, ...                            */


/*---(filesystems)--------------*/
#include    <fcntl.h>             /* open                                     */
#include    <sys/stat.h>          /* fstat, umask                             */
#include    <dirent.h>
#include    <openssl/sha.h>       /* openssl implementation of sha1           */

/*---(other standard)-----------*/
#include    <time.h>              /* time, localtime                          */

/*===[[ CUSTOM LIBRARIES ]]===================================================*/
#include    <yLOG.h>         /* CUSTOM : heatherly program logging            */
#include    <yURG.h>         /* CUSTOM : heatherly urgent processing          */
#include    <ySTR.h>         /* CUSTOM : heatherly string handling            */
#include    <yVAR.h>         /* CUSTOM : heatherly variable testing           */



#define     FILE_CONF   "/etc/hermes.conf"
#define     MAX_RECD    1000

#define     STR_MAX     500
#define     STR_REG     100



/* rapidly evolving version number to aid with visual change confirmation     */
#define     VER_NUM   "0.7s"
#define     VER_TXT   "updated to studly, short, shared make_program makefile"


/*---(struct typedefs)-------------------*/
typedef struct dirent    tDIRENT;
typedef struct FILE      tFILE;
typedef struct stat      tSTAT;



/*---(var typedefs)----------------------*/
typedef unsigned char    uchar;
typedef long long        llong;



/*---(command database)------------------*/



/*---(package struct)--------------------*/
#define     FILE_WORLD  "/var/lib/portage/world"
#define     PKG_MAX     1000
#define     LPCAT         25
#define     LPNAME        35
#define     LPFULL        60
typedef     struct cPKG   tPKG;
struct      cPKG {
   /*---(database fields)----------------*/
   char        active;                 /* verify commands in the package      */
   char        source;                 /* what method created this entry      */
   char        portage;                /* is it in the portage directory      */
   char        world;                  /* is it in the world file             */
   char        full        [LPFULL];
   char        desc        [LPFULL];   /* package description                 */
   int         area;                   /* index for area in data structure    */
   char        priority;
   char        update;
   /*---(working fields)-----------------*/
   int         len;                              /* speeds searches           */
   char        cat         [LPCAT ];             /* for reporting ease        */
   char        name        [LPNAME];             /* for reporting ease        */
   int         ncmd;                             /* for reporting ease        */
   /*---(done)---------------------------*/
};
extern      tPKG        pkgs        [PKG_MAX];   /* package data structure  */
extern      int         ipkg        [PKG_MAX];   /* package index           */
extern      int         npkg;                    /* package count           */
#define     PKG_NEGATIVE    -20
#define     PKG_OVERMAX     -21
#define     PKG_ATNEXT      -22
#define     PKG_TOOHIGH     -23
#define     PKG_FULL        -24



/*---(command struct)--------------------*/
#define     CMD_MAX    100000
#define     LCNAME         50
#define     LCFULL        200
#define     LCMODE          5
#define     LCHASH        100
#define     LEN_LINK      500
typedef     struct cCOMMAND  tCMD;
struct      cCOMMAND {
   /*---(base)------------------------*/
   char        active;
   char        source;
   char        full        [LCFULL];
   long        lastchg;
   /*---(characteristics)-------------*/
   char        ftype;
   long        filetime;
   int         size;
   int         uid;
   char        suid;
   int         gid;
   char        sgid;
   char        mode        [LCMODE];
   /*---(contents)--------------------*/
   int         bytes;
   int         smiss;
   char        hash        [LCHASH];
   char        sym_name    [LEN_LINK];
   char        sym_note;
   /*---(update)----------------------*/
   int         i_loc;
   int         i_pkg;
   /*---(working)---------------------*/
   char        subdir      [LCNAME];
   char        name        [LCNAME];
   char        concern;
   int         toolong;
   int         len;
   int         flen;
   int         ftoolong;
   /*---(done)------------------------*/
};
extern      tCMD        s_cmds      [CMD_MAX];   /* command data structure    */
extern      int         icmd        [CMD_MAX];   /* command index             */
extern      int         ncmd;                    /* command count             */
#define     CMD_NEGATIVE    -30
#define     CMD_OVERMAX     -31
#define     CMD_ATNEXT      -32
#define     CMD_TOOHIGH     -33
#define     CMD_FULL        -34


#define     URG_MAX     100
typedef     struct cURGS   tURG;
struct cURGS {
   char        abbr;
   char        full        [STR_REG];
   char        flag;
   char        desc        [STR_REG];
};
extern      tURG        urgs [URG_MAX];
extern      int         nurg;
extern      int         curg;





typedef  struct cGLOBAL  tGLOBAL;
struct cGLOBAL {
   /*---(argument flags)-----------------*/
   char        def_loc;                /* (-)  default active status of locs  */
   char        def_pkg;                /* (-)  default active status of pkgs  */
   char        def_cmd;                /* (-)  default active status of cmds  */
   char        conf;                   /* (y)  process conifiguration file    */
   char        focus       [STR_REG];  /*      specific object to verify      */
   char        focus_type;
   int         focus_len;              /*      length of focus string         */


   char        db_read;
   char        db_write;

   char        command;
   char        match;
   char        matchall;
   char        package; 
   char        packageall;             /* processing of packages (force)      */
   /*---(strout reports)-----------------*/
   char        locs_list;
   char        locs_dump;
   char        locs_tree;
   char        list_pkgs;
   char        list_cmds;
   char        show_gather;
   char        show_check;
   /*---(file names)---------------------*/
   char        cmd_db   [500];
   char        pkg_db   [500];
   /*---(other)--------------------------*/
   long        runtime;
   /*---(done)---------------------------*/
};
extern      tGLOBAL     my;

#define     LOCS_LIST        if (my.locs_list == 'y')
#define     LOCS_DUMP        if (my.locs_dump == 'y')
#define     LOCS_TREE        if (my.locs_tree == 'y')

#define     RUN_CONF         my.conf
#define     RUN_READ         my.db_read
#define     RUN_WRITE        my.db_write

#define     RUN_WORLD        my.world

#define     RUN_PACKAGE      if (my.package      == 'y')
#define     RUN_COMMAND      if (my.command      == 'y')
#define     RUN_MATCH        if (my.match        == 'y')
#define     SHOW_GATHER      if (my.show_gather  == 'y')

#define     PKG_DATABASE     my.pkg_db
#define     CMD_DATABASE     my.cmd_db


#define     LEN_TEXT  2000
char        unit_answer [ LEN_TEXT ];



/*---(hermes_main)----------------------------------------*/
int         main               (int argc, char *argv[]);



/*---(hermes_prog)----------------------------------------*/
char*       PROG_version       (void);
char        PROG_init          (void);
char        PROG_args          (int argc, char *argv[]);
char        PROG_begin         (void);
char        PROG_testquiet     (void);
char        PROG_testloud      (void);
char        PROG_end           (void);



/*===[[ HERMES_UTIL.C   ]]=====================================*/
/*---(strings)---------*/
char*       str_ttrim          (char *a_cstring);
char*       str_trim           (char *a_cstring);
char        str_wtrim          (char *a_cstring, char *a_white);
char        UTIL_parse_full    (char *a_full, char *a_path, char *a_name);
/*---(records)---------*/
int         recd_valid         (char *a_recd, int   *a_len);
/*---(parsing)---------*/
char        parse_string       (char *a_recd, char **a_place, int a_min, int a_max, char *a_string);
char        parse_flag         (char *a_recd, char **a_place, char *a_valid, char *a_value);
char        parse_integer      (char *a_recd, char **a_place, int a_min, int a_max, int *a_value);
char        parse_long         (char *a_recd, char **a_place, long a_min, long a_max, long *a_value);



/*---(hermes_loc)-----------------------------------------*/
/*---(program)----------------*/
char        LOC_init           (void);
char        LOC__purge         (void);
char        LOC_wrap           (void);
int         LOC_count          (void);
/*---(ordering)---------------*/
char        LOC_sort           (void);
/*---(single)-----------------*/
int         LOC_create         (char  *a_name, char a_type, char *a_desc);
char        LOC__wipe          (int    a_loc);
/*---(accessors)--------------*/
char*       LOC_get_path       (int    a_loc);
char        LOC_add_cmd        (int    a_loc, long a_size);
char        LOC_set_type       (int    a_loc);
char        LOC_set_cat        (int    a_loc, int a_save);
/*---(helpers)----------------*/
char        LOC_check_path     (char  *a_path);
char        LOC_clean_path     (char  *a_path);
char        LOC_valid          (int    a_loc);
/*---(filtering)--------------*/
int         LOC_find_path      (char  *a_name, char a_type);
/*---(cursors)----------------*/
char        LOC_curs_index     (int    a_loc);
char        LOC_curs_head      (void);
char        LOC_curs_next      (void);
char*       LOC_curr_path      (void);
char        LOC_curr_source    (void);
int         LOC_curr_commands  (void);
char*       LOC_curr_desc      (void);
/*---(structure)--------------*/
char        LOC_treeify        (void);
char        LOC_link           (int    a_loc, int a_cmd);
char        LOC_unlink         (int    a_cmd);
/*---(reporting)--------------*/
char        LOC_list           (void);
char        LOC_hyleoroi       (void);
/*---(unit testing)-----------*/
char*       LOC_unit           (char  *a_question, int a_num);
/*---(done)-------------------*/






/*---(hermes_pkg)-----------------------------------------*/
/*---helpers-----------*/
char        PKG_valid          (int     a_pkg);
/*---fulltable---------*/
char        PKG_purge          (void);
char        PKG_index          (void);
/*---updates-----------*/
int         PKG_push           (char  *a_name, char  a_type, char a_priority, char *a_desc);
int         PKG_find           (char  *a_name);
char        AREA_wipe          (int    a_curr);
char        PKG_wipe           (int    a_curr);
/*---linking-----------*/
char        PKG_link           (int    a_pkg , int a_cmd);
char        PKG_unlink         (int    a_cmd);
/*---reporting---------*/
char        PKG_list           (char   a_order);
/*---gathering---------*/
char        PKG_world          (void);
char        PKG_cmd_add        (int a_pkg);
/*---database----------*/
char        PKG_readdb         (void);
char        PKG_writedb        (void);
/*---unittest----------*/
char*       PKG_unit           (char *a_question, int a_num);



/*===[[ HERMES_CMD.C    ]]=====================================*/
/*---fulltable---------*/
char        CMD_purge          (void);
/*> char        CMD_index          (void);                                            <*/
/*---updates-----------*/
char        CMD_checkname      (char   *a_name);
int         CMD_push           (char   *a_name, char a_source);
char        CMD_subdir         (int a_curr, char *a_subdir);
int         CMD_append         (int     a_num, int a_loc, char *a_name);
int         CMD_find           (char    *a_name);
char        CMD_wipe           (tCMD   *a_cmd);
/*---helpers-----------*/
char        CMD_valid          (int     a_cmd);
char        CMD_stat           (tCMD   *a_cmd);
char        CMD_hash           (tCMD   *a_cmd);
char        CMD_chars          (tCMD   *a_cmd);
/*---reporting---------*/
char        CMD_header         (int     a_page , int  a_loc, char a_order);
char        CMD_footer         (int     a_page , int  a_lines);
char        CMD_show           (int     a_count, int  a_index, int  a_num,  tCMD *a_cmd);
char        CMD_list           (char    a_order);
char        CMD_list_NEW       (void);
char        CMD_dump           (void);
/*---gathering---------*/
char        CMD_gather         (char    a_check);
int         CMD_files          (char *a_path, char *a_name);
char        CMD_pkgref         (int a_cmd, int a_pkg);
char        CMD_world          (void);
char        CMD_package        (void);
/*---reporting---------*/
char        CMD_readdb         (void);
char        CMD_writeall       (void);
char        CMD_savelinks      (void);
/*---unittest----------*/
char*       CMD_unit           (char *a_question, int a_num);



char        FILES_gather       (void);

char     *ySTR_trim          (char *a_source, char a_mode);
#define    ySTR_NONE      'n'
#define    ySTR_HEAD      'h'
#define    ySTR_TAIL      't'
#define    ySTR_BOTH      'b'
#define    ySTR_SINGLE    's'
#define    ySTR_EVERY     'e'
#define    ySTR_MAX       'm'


/*===============================[[ end-code ]]===============================*/
