/*===============================[[ beg-code ]]===============================*/
#include    "hermes.h"

/*> tDEBUG      debug;                                                                <*/
tGLOBAL     my;


FILE       *f_conf      = NULL;



/*====================------------------------------------====================*/
/*===----                            utilities                         ----===*/
/*====================------------------------------------====================*/
void  o___UTILITIES_______o () { return; }

char        s_string    [STR_MAX];

char*        /*--> clean whitespace from a string --------[--------[--------]-*/
ySTR_trim          (char *a_source, char a_mode)
{
   /*---(design notes)-------------------*/
   /*
    *   n = none   (string untouched)
    *   h = head   (all leading spaces gone)
    *   t = tail   (all ending spaces gone)
    *   b = both   (head and tail)
    *   s = single (both plus internal not-in-strings compressed to one space)
    *   e = every  (both plus internal not-in-strings taken out)
    *   m = max    (both plus all internal taken fully out)
    *
    */
   /*---(locals)-----------+-----------+-*/
   int         i, j;                             /* iterators -- characters   */
   int         x_len       = 0;                  /* source string length      */
   int         x_count     = 0;                  /* whitespace counter        */
   int         x_limit     = 0;
   char        in_str      = '-';
   /*---(defense: bad source)------------*/
   strcpy (s_string, "(null)");
   if (a_source == NULL)   return NULL;
   x_len = strlen(a_source);
   strcpy (s_string, "(empty)");
   if (x_len    <= 0   )   return NULL;
   /*---(prepare)------------------------*/
   if (a_mode == 's')   x_limit = 1;
   /*---(leading whitespace)-------------*/
   if (strchr("hbsem", a_mode) != 0) {
      for (i = 0; i <= x_len; ++i) {
         if (a_source[0] != ' ') break;
         for (j = 0; j <= x_len; ++j)
            a_source[j] = a_source[j + 1];
         --x_len;
      }
   }
   /*---(trailing whitespace)------------*/
   if (strchr("tbsem", a_mode) != 0) {
      for (i = x_len - 1; i >= 0; --i) {
         if (a_source[i] != ' ') break;
         a_source[i] = '\0';
         --x_len;
      }
   }
   /*---(internal whitespace)------------*/
   if (strchr("esm" , a_mode) != 0) {
      for (i = 0; i <= x_len; ++i) {
         /*---(check for strings)--------*/
         if (a_mode != 'm') {
            if (in_str == 'y') {
               if (a_source[i] == '"') {
                  /*> if (i > 0 && a_source[i-1] == '\\')  continue;                  <*/
                  in_str = '-';
                  continue;
               }
               continue;
            } else {
               if (a_source[i] == '"') {
                  /*> if (i > 0 && a_source[i-1] == '\\')  continue;                  <*/
                  in_str = 'y';
                  continue;
               }
            }
         }
         /*---(check limit)--------------*/
         if (a_source[i] != ' '    )  { x_count = 0; continue; }
         if (x_count   <  x_limit)  { ++x_count;   continue; }
         /*---(compress)-----------------*/
         for (j = i; j <= x_len; ++j)
            a_source[j] = a_source[j + 1];
         --x_len;
         --i;
         /*---(done)---------------------*/
      }
   }
   /*---(prepare for return)-------------*/
   strncpy (s_string, a_source, STR_MAX);
   /*---(complete)-----------------------*/
   return a_source;
}

/*====================------------------------------------====================*/
/*===----                   standard program functions                 ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char      verstring    [500];

char*        /*--: return versioning information ---------[ ------ [ ------ ]-*/
PROG_version       (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc  ]", 15);
#elif  __CBANG__  > 0
   strncpy (t, "[cbang    ]", 15);
#else
   strncpy (t, "[unknown  ]", 15);
#endif
   snprintf (verstring, 100, "%s   %s : %s", t, VER_NUM, VER_TXT);
   return verstring;
}

char             /* [------] minimal pre-argument program initialization -----*/
PROG_init          (void)
{
   /*---(log header)---------------------*/
   DEBUG_TOPS   yLOG_info     ("purpose" , "light, clean, vim-ish, technical, and wicked spreadsheet");
   DEBUG_TOPS   yLOG_info     ("namesake", "ugly, impossibly powerful, one-hundred handed, fifty headed, primeval giant");
   DEBUG_TOPS   yLOG_info     ("hermes"  , PROG_version    ());
   DEBUG_TOPS   yLOG_info     ("yURG"    , yURG_version    ());
   DEBUG_TOPS   yLOG_info     ("ySTR"    , ySTR_version    ());
   DEBUG_TOPS   yLOG_info     ("yLOG"    , yLOG_version    ());
   /*---(begin)--------------------------*/
   DEBUG_ARGS   yLOG_enter   (__FUNCTION__);
   /*---(default run-time options)-------*/
   my.conf         = 'y';
   my.def_loc      = '-';
   my.def_pkg      = '-';
   my.def_cmd      = '-';
   /*---(focus)--------------------------*/
   strncpy (my.focus, "", STR_REG);
   my.focus_type   = '-';
   my.focus_len    =  0;
   my.runtime      = time (NULL);
   /*---(stdout reports)-----------------*/
   my.list_locs    = '-';
   my.dump_locs    = '-';
   my.list_pkgs    = '-';
   my.list_cmds    = '-';
   my.show_gather  = '-';
   my.show_check   = '-';
   /*---(file names)---------------------*/
   strcpy (my.pkg_db, "/var/lib/hermes/hermes.packages");
   strcpy (my.cmd_db, "/var/lib/hermes/hermes.commands");
   /*---(initialize data structures)-----*/
   LOC_init        ();
   PKG_purge       ();
   CMD_purge       ();
   /*---(complete)-----------------------*/
   DEBUG_ARGS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char             /* [------] process the command line arguments --------------*/
PROG_args          (int argc, char *argv[])
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* loop iterator -- arguments     */
   char       *a           = NULL;          /* current argument               */
   int         len         = 0;             /* argument length                */
   int         x_total     = 0;
   int         x_args      = 0;
   /*---(begin)--------------------------*/
   DEBUG_ARGS   yLOG_enter   (__FUNCTION__);
   /*---(process)------------------------*/
   for (i = 1; i < argc; ++i) {
      /*---(read)------------------------*/
      a   = argv [i];
      len = strlen(a);
      ++x_total;
      /*---(filter)----------------------*/
      if (a[0] == '@')  continue;
      ++x_args;
      DEBUG_ARGS  yLOG_info  ("argument"  , a);
      /*---(startup/shutdown)------------*/
      if      (strcmp (a, "--conf"              ) == 0)    my.conf           = 'y';
      else if (strcmp (a, "--noconf"            ) == 0)    my.conf           = 'n';
      /*---(----------------)------------*/
      else if (strcmp (a, "--read"              ) == 0)    my.db_read        = 'y';
      else if (strcmp (a, "--noread"            ) == 0)    my.db_read        = 'n';
      else if (strcmp (a, "--write"             ) == 0)    my.db_write       = 'y';
      else if (strcmp (a, "--nowrite"           ) == 0)    my.db_write       = 'n';
      /*---(----------------)------------*/
      else if (strcmp (a, "--locs-list"         ) == 0)    my.list_locs      = 'y';
      else if (strcmp (a, "--locs-dump"         ) == 0)    my.dump_locs      = 'y';
      else if (strcmp (a, "--pkgs"              ) == 0)    my.list_pkgs      = 'y';
      else if (strcmp (a, "--cmds"              ) == 0)    my.list_cmds      = 'y';
      else if (strcmp (a, "--show-gather"       ) == 0)    my.show_gather    = 'y';
      else if (strcmp (a, "--show-check"        ) == 0)    my.show_check     = 'y';
      /*---(----------------)------------*/
      else if (strcmp (a, "--command"           ) == 0)    my.command        = 'y';
      /*> else if (strcmp (a, "--match"             ) == 0)    my.match          = my.world          = my.command        = 'y';   <*/
      /*> else if (strcmp (a, "--matchall"          ) == 0)    my.match          = my.matchall       = my.world          = my.command        = 'y';   <*/
      else if (strcmp (a, "--package"           ) == 0)    my.package        = 'y';
      else if (strcmp (a, "--packageall"        ) == 0)    my.package        = my.packageall     = 'y';
      /*---(----------------)------------*/
      else if (strcmp (a, "--focus"             ) == 0) {
         if (i + 1 < argc) {
            strncpy (my.focus, argv[++i], STR_REG);
            my.focus_len = strlen (my.focus);
            if (my.focus_len == 0)                    my.focus_type = '-';
            else if (my.focus[0] == '/')              my.focus_type = 'l';
            else if (strchr (my.focus, '/') != NULL)  my.focus_type = 'p';
            else                                      my.focus_type = 'c';
         }
      }
      /*---(----------------)------------*/
      /*> else if (strcmp (a, "--loc"               ) == 0) {                         <* 
       *>    if (i + 1 < argc)  LOC_create (argv[++i], 'a', "");                        <* 
       *> }                                                                           <* 
       *> else if (strcmp (a, "--alt_cmd"           ) == 0) {                         <* 
       *>    if (i + 1 < argc)  strcpy (my.cmd_db, argv[++i]);                        <* 
       *> }                                                                           <* 
       *> else if (strcmp (a, "--alt_pkg"           ) == 0) {                         <* 
       *>    if (i + 1 < argc)  strcpy (my.pkg_db, argv[++i]);                        <* 
       *> }                                                                           <*/
      /*---(unknown)--------------------*/
      else {
         DEBUG_ARGS  yLOG_note    ("argument not understood");
      }
   }
   /*---(display urgents)----------------*/
   DEBUG_ARGS  yLOG_note    ("summarization of argument processing");
   DEBUG_ARGS  yLOG_value   ("entries"   , x_total);
   DEBUG_ARGS  yLOG_value   ("arguments" , x_args);
   DEBUG_ARGS  yLOG_note    ("standard arguments");
   DEBUG_ARGS  yLOG_char    ("conf"      , my.conf);
   DEBUG_ARGS  yLOG_char    ("def_loc"   , my.def_loc);
   DEBUG_ARGS  yLOG_char    ("def_pkg"   , my.def_pkg);
   DEBUG_ARGS  yLOG_char    ("def_cmd"   , my.def_cmd);
   DEBUG_ARGS  yLOG_info    ("focus"     , my.focus);
   DEBUG_ARGS  yLOG_char    ("focus_type", my.focus_type);
   DEBUG_ARGS  yLOG_value   ("focus_len" , my.focus_len);
   /*---(complete)-----------------------*/
   DEBUG_ARGS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char             /* [------] processing the configuration file ---------------*/
PROG_conf          (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   char        rce         = -10;
   char        x_recd      [MAX_RECD];           /* input record              */
   int         x_len       = 0;                  /* string length             */
   char       *p;
   char       *q           = "\x1F";
   char       *r           = NULL;
   char        x_temp      [20];
   char        x_verbs     [1000] = " loc area pkg ";
   char        x_verb      [20];
   int         i           = 0;
   char        x_field     [ 20][100];
   /*---(begin)--------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(check for option)---------------*/
   if (my.conf != 'y') {
      DEBUG_CONF   yLOG_note    ("elected not to process configuration file");
      DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(open detail report)-------------*/
   DEBUG_CONF   yLOG_info    ("conf_file" , FILE_CONF);
   f_conf = fopen (FILE_CONF, "r");
   DEBUG_CONF   yLOG_point   ("file point", f_conf);
   --rce;  if (f_conf == NULL) {
      DEBUG_CONF   yLOG_note    ("failed to open file");
      DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   DEBUG_CONF   yLOG_note    ("successfully openned");
   /*---(read)---------------------------*/
   while (1) {
      fgets (x_recd, MAX_RECD, f_conf);
      if (feof(f_conf))                     break;
      /*---(filter)----------------------*/
      x_len = strlen (x_recd);
      if (x_len <= 0)                       continue;
      x_recd [--x_len] = '\0';
      if (x_len <= 0)                       continue;
      if (x_recd [0] == '#')                continue;
      DEBUG_TOPS  printf ("   -- read   ::%s::\n", x_recd);
      /*---(get recd type)---------------*/
      p = strtok_r (x_recd, q, &r);
      if (p == NULL)                        continue;
      ySTR_trim (p, ySTR_BOTH);
      x_len = strlen (p);
      if (x_len <= 2)                       continue;
      sprintf (x_temp, " %s ", p);
      if (strstr (x_verbs, p) == NULL)      continue;
      strcpy (x_verb, p);
      DEBUG_TOPS  printf ("      verb   ::%s::\n", x_verb);
      /*---(get fields)------------------*/
      for (i = 0; i < 20; ++i) {
         p = strtok_r (NULL  , q, &r);
         if (p == NULL)                        continue;
         ySTR_trim (p, ySTR_BOTH);
         strncpy (x_field [i], p, 100);
      }
      /*---(act)-------------------------*/
      rc = 0;
      switch (x_verb[0]) {
      case 'l' : rc = LOC_create  (x_field [0], 'c', x_field [2]);    break;
      case 'a' : rc = AREA_push   (x_field [0]);                      break;
      case 'p' : rc = PKG_push    (x_field [0], 'c', x_field [1][0], x_field [2]);    break;
      default  : break;
      }
      /*---(done)------------------------*/
   }
   /*---(close configuration)------------*/
   DEBUG_CONF   yLOG_note    ("closing configuration file");
   rc = fclose (f_conf);
   DEBUG_CONF   yLOG_value   ("close rc"  , rc);
   --rce;  if (rc != 0) {
      DEBUG_CONF   yLOG_note    ("failed to close file");
      DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   DEBUG_CONF   yLOG_note    ("successfully closed configuration file");
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char             /* [------] post-argument program initialization ------------*/
PROG_begin         (void)
{
   FILE       *f           = NULL;          /* file pointer - commands        */
   DEBUG_TOPS  yLOG_enter   (__FUNCTION__);
   PROG_conf    ();
   /*> f = fopen (PKG_DATABASE, "r");                                                 <* 
    *> if (f == NULL) {                                                               <* 
    *>    printf ("PROG_init : can not open package file <<%s>>\n", PKG_DATABASE);    <* 
    *>    return -1;                                                                  <* 
    *> } else {                                                                       <* 
    *>    fclose (f);                                                                 <* 
    *> }                                                                              <*/
   /*> f = fopen (CMD_DATABASE, "r");                                                 <* 
    *> if (f == NULL) {                                                               <* 
    *>    printf ("PROG_init : can not open command file <<%s>>\n", CMD_DATABASE);    <* 
    *>    return -2;                                                                  <* 
    *> } else {                                                                       <* 
    *>    fclose (f);                                                                 <* 
    *> }                                                                              <*/
   DEBUG_TOPS  yLOG_exit    (__FUNCTION__);
   DEBUG_TOPS  yLOG_break   ();
   /*---(complete)-----------------------*/
   return 0;
}

char       /*----: set up programgents/debugging -----------------------------*/
PROG_testquiet     (void)
{
   char       *x_args [1]  = { "hermes" };
   yURG_logger (1, x_args);
   PROG_init   ();
   yURG_urgs   (1, x_args);
   PROG_args   (1, x_args);
   PROG_begin  ();
   return 0;
}

char       /*----: set up programgents/debugging -----------------------------*/
PROG_testloud      (void)
{
   char       *x_args [2]  = { "hermes_unit", "@@kitchen"    };
   yURG_logger (2, x_args);
   PROG_init   ();
   yURG_urgs   (2, x_args);
   PROG_args   (2, x_args);
   PROG_begin  ();
   return 0;
}


char                /* PURPOSE : shutdown program and free memory ------------*/
PROG_end           (void)
{
   DEBUG_TOPS  yLOG_break   ();
   DEBUG_TOPS  yLOG_enter   (__FUNCTION__);
   DEBUG_TOPS  yLOG_exit    (__FUNCTION__);
   DEBUG_TOPS  yLOG_end     ();
   return 0;
}


/*===============================[[ end-code ]]===============================*/
