/*===============================[[ beg-code ]]===============================*/

/*===[[ OVERVIEW ]]===========================================================*/

/*   locations are directories where executables are stored for general use
 *   across the system.
 *
 *   unlike packages and commands, the locations are not sorted as their order
 *   follows the PATH set on the system.
 *
 *
 *
 */
/*============================================================================*/



#include    "hermes.h"



tLOC        s_locs      [LOC_MAX];       /* location data structure           */
int         s_nloc      = 0;             /* total number of locations         */
int         s_cloc      = -1;            /* current location in use           */

static char valid_src   [10] = "cad";    /* valid source types                */
/*  c = from configuration file /etc/themis.conf
 *  a = from command line argument
 *  d = from command database
 */



/*====================------------------------------------====================*/
/*===----                      helper functions                        ----===*/
/*====================------------------------------------====================*/
static void      o___HELPERS_________________o (void) {;}

char             /* [------] validate a location index -----------------------*/
LOC_valid          (int a_loc)
{
   /*---(design notes)-------------------*/
   /*
    * return code must deferentiate fairly precisely to aid rapid debugging and
    * tracing back to a specific failure reason.  also, some callers may choose
    * to ignore one or more of the return values which helps with reuse, i.e.,
    * ATNEXT which may not actually be an error in the case of an append/push.
    *
    */
   /*---(defenses)-----------------------*/
   char        rce         = -10;
   --rce;  if (a_loc  <  0) {
      DEBUG_DIRS   yLOG_note    ("warning, location index is negative");
      return rce;
   }
   --rce;  if (a_loc  >= LOC_MAX)  {
      DEBUG_DIRS   yLOG_note    ("warning, location index is greater than max");
      return rce;
   }
   --rce;  if (a_loc  == s_nloc)  {
      DEBUG_DIRS   yLOG_note    ("warning, location index is at next");
      return rce;
   }
   --rce;  if (a_loc  >  s_nloc)  {
      DEBUG_DIRS   yLOG_note    ("warning, location index is too high");
      return rce;
   }
   --rce;  if (s_nloc >= LOC_MAX) {
      DEBUG_DIRS   yLOG_note    ("warning, location structure is full");
      return rce;
   }
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     full table operations                    ----===*/
/*====================------------------------------------====================*/
static void      o___FULLTABLE_______________o (void) {;}

char             /* [------] initialize the location structure ---------------*/
LOC_purge          (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* iterator -- location           */
   /*---(bagin)--------------------------*/
   DEBUG_DIRS  yLOG_enter   (__FUNCTION__);
   DEBUG_DIRS  yLOG_value   ("slots"     , LOC_MAX);
   /*---(cycle)--------------------------*/
   for (i = 0; i < LOC_MAX; ++i) {
      LOC_wipe (i);
   }
   DEBUG_DIRS  yLOG_note    ("initialized all slots");
   /*---(counter)------------------------*/
   s_nloc = 0;
   DEBUG_DIRS  yLOG_value   ("s_nloc"      , s_nloc);
   /*---(complete)-----------------------*/
   DEBUG_DIRS  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    single entry updates                      ----===*/
/*====================------------------------------------====================*/
static void      o___UPDATES_________________o (void) {;}

int              /* [------] verify a location by name -----------------------*/
LOC_find           (char  *a_name)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;
   int         i           = 0;             /* iterator -- location           */
   int         found       = -1;            /* generic locator                */
   int         x_len       = 0;             /* generic string length          */
   /*---(prepare)------------------------*/
   s_cloc = -1;
   /*---(defense))-----------------------*/
   --rce;  if (a_name == NULL)      return rce;
   x_len = strlen (a_name);
   --rce;  if (x_len  == 0   )      return rce;
   /*---(cycle)--------------------------*/
   for (i = 0; i < s_nloc; ++i) {
      /*---(filter)----------------------*/
      if (s_locs [i].len                   != x_len)   continue;
      if (strcmp (s_locs [i].path, a_name) != 0    )   continue;
      /*---(save)------------------------*/
      found = i;
      break;
   }
   /*---(complete)-----------------------*/
   return found;
}

int              /* [------] append a location to the list -------------------*/
LOC_push           (char  *a_path, char a_source, char *a_desc)
{
   DEBUG_DIRS   printf ("   appending location: ");
   /*---(locals)-----------+-----------+-*/
   int         found       = -1;            /* generic locator                */
   int         len         = 0;             /* generic string length          */
   DIR        *dir         = NULL;          /* directory pointer              */
   char        rce         = -10;           /* return code for errors         */
   char        x_valid     []          = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_./";
   char        x_extra     []          = "-";
   int         i           = 0;             /* iterator -- location           */
   /*---(defenses)-----------------------*/
   --rce;
   if (s_nloc >= LOC_MAX) {
      DEBUG_DIRS   printf ("location structure full, SKIPPING\n");
      return rce;
   }
   --rce;
   if (a_path == NULL) {
      DEBUG_DIRS   printf ("location name is null, SKIPPING\n");
      return -7;
   }
   found = LOC_find (a_path);
   --rce;
   if (found < -1) {
      DEBUG_DIRS   printf ("bad name or length, SKIPPING\n");
      return rce;
   }
   DEBUG_DIRS   printf ("%-20.20s, ", a_path);
   if (found >= 0 && s_locs [found].source != '#')  {
      DEBUG_DIRS   printf ("already exists as %d, done\n", found);
      return found;
   }
   len = strlen (a_path);
   --rce;
   if (len >= STR_MAX) {
      DEBUG_DIRS   printf ("name too long (%d vs. %d)\n", len, STR_MAX);
      return rce;
   }
   --rce;
   if (len <  4) {
      DEBUG_DIRS   printf ("name too short (%d vs. %d)\n", len, 4);
      return rce;
   }
   --rce;
   if (strchr (valid_src, a_source) == NULL) {
      DEBUG_DIRS   printf ("bad location type (%c vs %s), SKIPPING\n", a_source, valid_src);
      return rce;
   }
   /*---(test against real location)-----*/
   dir = opendir(a_path);
   --rce;
   if (dir == NULL) {
      DEBUG_DIRS    printf ("skipping, not a real directory\n");
      closedir (dir);
      return rce;
   }
   closedir (dir);
   /*---(append)-------------------------*/
   if (found == -1)  found = s_nloc;
   s_locs [found].source   = a_source;
   strncpy (s_locs [found].path, a_path, STR_MAX);
   if (a_desc != NULL)  strncpy (s_locs [found].desc, a_desc, STR_REG);
   else                 strncpy (s_locs [found].desc, "n/a" , STR_REG);
   s_locs [found].len      = len;
   s_locs [found].ncmd     = 0;
   /*---(error-flags)--------------------*/
   s_locs [found].f_concern  = '-';
   for (i = 0; i < len; ++i) {
      /*---(test basic)------------------*/
      if (strchr (x_valid, s_locs [found].path [i]) != NULL)  continue;
      /*---(test extra)------------------*/
      if (strchr (x_extra, s_locs [found].path [i]) != NULL) {
         s_locs [found].f_concern = '+';
         continue;
      }
      /*---(othre is bad)----------------*/
      s_locs [found].f_concern = '#';
      break;
   }  /*---(done)------------------------*/
   /*---(focus)--------------------------*/
   if (  s_locs [found].len == my.focus_len &&
         strcmp (s_locs [found].path, my.focus) == 0) {
      s_locs [found].active = 'y';
   }
   /*---(update)-------------------------*/
   DEBUG_DIRS   printf ("added as %d, done\n", found);
   ++s_nloc;
   /*---(complete)-----------------------*/
   return found;
}

char             /* [------] clear a single location entry -------------------*/
LOC_wipe           (int a_loc)
{
   /*---(defenses)-----------------------*/
   if (a_loc >= LOC_MAX)   return -1;
   /*---(database)-----------------------*/
   s_locs [a_loc].active         = my.def_loc;
   s_locs [a_loc].source         = '?';
   s_locs [a_loc].path [0]       = '\0';
   s_locs [a_loc].desc [0]       = '\0';
   /*---(working)------------------------*/
   s_locs [a_loc].len            =  0;
   s_locs [a_loc].ncmd           =  0;
   /*---(error-flags)--------------------*/
   s_locs [a_loc].f_concern      = '-';
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          linking                             ----===*/
/*====================------------------------------------====================*/
static void      o___LINKING_________________o (void) {;}

char             /* [------] link a command to a location --------------------*/
LOC_link           (int a_loc, int a_cmd)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   char        rcc         = 0;             /* return code as char            */
   /*---(header)-------------------------*/
   DEBUG_DIRS   printf ("   linking location/command  : ");
   /*---(defenses)-----------------------*/
   // location index
   rcc = LOC_valid (a_loc);
   if (rcc < 0)  {
      DEBUG_DIRS   printf (", SKIPPING\n");
      return rcc;
   }
   // command index


   --rce;  /*=== cmd index negative ====*/
   if (a_cmd < 0) {
      DEBUG_DIRS   printf ("ommand index negative (%d), SKIPPING\n", a_cmd);
      return rce;
   }
   --rce;  /*=== loc index too high ====*/
   if (a_cmd >  ncmd) {
      DEBUG_DIRS   printf ("command index too high (%d >  %d), SKIPPING\n", a_cmd, ncmd);
      return rce;
   }
   --rce;  /*=== command already linked =*/
   if (s_cmds [a_cmd].i_loc >= 0) {
      DEBUG_DIRS   printf ("command already linked to location (%d), SKIPPING\n", s_cmds [a_cmd].i_loc);
      return rce;
   }
   /*---(link)---------------------------*/
   s_cmds [a_cmd].i_loc = a_loc;
   ++s_locs [a_loc].ncmd;
   DEBUG_DIRS   printf ("linked %s to %s, done\n", s_cmds [a_cmd].name, s_locs [a_loc].path);
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] unlink a command from a location ----------------*/
LOC_unlink         (int a_cmd)
{
   DEBUG_DIRS   printf ("   unlinking package/command: ");
   /*---(locals)-----------+-----------+-*/
   int         x_loc       = -1;
   char        rce         = -10;           /* return code for errors         */
   char        rcc         = 0;             /* return code as char            */
   /*---(defense))-----------------------*/
   --rce;  if (a_cmd < 0) {
      DEBUG_DIRS   printf ("aommand index negative, SKIPPING\n");
      return rce;
   }
   --rce;  if (a_cmd >  ncmd) {
      DEBUG_DIRS   printf ("command index too high, SKIPPING\n");
      return rce;
   }
   x_loc = s_cmds [a_cmd].i_loc;
   // location index
   rcc = LOC_valid (x_loc);
   if (rcc < 0)  {
      DEBUG_DIRS   printf (", SKIPPING\n");
      return rcc;
   }
   /*---(link)---------------------------*/
   s_cmds [a_cmd].i_loc = -1;
   --s_locs [x_loc].ncmd;
   DEBUG_PKGS   printf ("unlinked %s from %s, done\n", s_cmds [a_cmd].name, s_locs [x_loc].path);
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         user reporting                       ----===*/
/*====================------------------------------------====================*/
static void      o___REPORTING_______________o (void) {;}

char             /* [------] report location results -------------------------*/
LOC_list           (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* iterator -- location           */
   int         x_cmds      = 0;
   /*---(header)-------------------------*/
   printf ("\n");
   printf ("HERMES-DIACTOROS -- location report                                                            %3d of %3d slots used\n", s_nloc, LOC_MAX);
   printf ("\n");
   printf ("  seq# indx  s a  ---path--------------------------------- len  -c-  ncmd   ---dsec---------------------------------\n");
   /*---(cycle location)-----------------*/
   for (i = 0; i < s_nloc; ++i) {
      /*> if ((i % 5) == 0)   printf ("\n");                                          <*/
      printf ("  %4d %4d  %c %c  %-40.40s %3d   %c   %4d   %-40.40s\n", i, i,
            s_locs [i].source , s_locs [i].active   , s_locs [i].path,
            s_locs [i].len    , s_locs [i].f_concern, 
            s_locs [i].ncmd   , s_locs [i].desc);
      x_cmds += s_locs [i].ncmd;
   }
   /*---(footer)-------------------------*/
   printf ("\n");
   printf ("   end of locations ------------------------------------------------------------------------------------------------\n");
   printf ("      key :: s/sources   are  'c' = from config file  ,  'a' = command line add  ,  'd' = from command db         ::\n");
   printf ("          :: c/concerns  are  '-' = path is great     ,  '+' = extra chars used  ,  '#' = bad chars used          ::\n");
   printf ("\n");
   printf ("   GRAND TOTAL of %d commands stored in %d directory locations\n", x_cmds, s_nloc);
   printf ("\n\n");
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        accessors                             ----===*/
/*====================------------------------------------====================*/
static void      o___ACCESSORS_______________o (void) {;}

char             /*-> return first directory -------------[ ------ [ ------ ]-*/
LOC_change         (int a_loc)
{
   s_cloc = 0;
   if (s_nloc == 0) {
      s_cloc = -1;
      return -1;
   }
   if (a_loc < 0) {
      s_cloc = -1;
      return -2;
   }
   if (a_loc >= s_nloc) {
      s_cloc = -1;
      return -3;
   }
   return 0;
}

char             /*-> return first directory -------------[ ------ [ ------ ]-*/
LOC_head           (void)
{
   s_cloc = 0;
   if (s_nloc == 0) {
      s_cloc = -1;
      return -1;
   }
   return 0;
}

char             /*-> return first directory -------------[ ------ [ ------ ]-*/
LOC_next           (void)
{
   if (s_nloc == 0) {
      s_cloc = -1;
      return -1;
   }
   ++s_cloc;
   if (s_cloc >= s_nloc) {
      s_cloc = 0;
      return -2;
   }
   return 0;
}

char*            /*-> return current rectory -------------[ ------ [ ------ ]-*/
LOC_getpath        (void)   { if (s_cloc <  0) return ""; return s_locs [s_cloc].path; }

char             /*-> return current rectory -------------[ ------ [ ------ ]-*/
LOC_getsource      (void)   { if (s_cloc <  0) return '?'; return s_locs [s_cloc].source; }

int              /*-> return count of locations ----------[ ------ [ ------ ]-*/
LOC_getcount       (void)   { return s_nloc; }

char             /*-> return count of locations ----------[ ------ [ ------ ]-*/
LOC_addcmd         (void)   { if (s_cloc < 0)  return -1; ++s_locs[s_cloc].ncmd; return 0; }



/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char*
LOC_unit           (char *a_question, int a_num)
{
   /*---(prepare)------------------------*/
   strcpy  (unit_answer, "location unit    : question not understood");
   /*---(defenses)-----------------------*/
   if      (s_nloc < 1) {
      snprintf (unit_answer, LEN_TEXT, "location empty   : no locations exist");
   }
   else if (a_num < 0) {
      snprintf (unit_answer, LEN_TEXT, "location error   : location ref (%d) is negative", a_num);
   }
   else if (a_num != 0 && a_num >= s_nloc) {
      snprintf (unit_answer, LEN_TEXT, "location error   : location ref (%d vs %d) is too high", a_num, s_nloc);
   }
   /*---(location name)------------------*/
   else if (strncmp (a_question, "location_name"     , 20)      == 0) {
      snprintf (unit_answer, LEN_TEXT, "location name    : %3d, %c, %-.35s", a_num, s_locs [a_num].source, s_locs [a_num].path);
   }
   /*---(location count)-----------------*/
   else if (strncmp (a_question, "location_count"    , 20)      == 0) {
      snprintf (unit_answer, LEN_TEXT, "location count   : %d", s_nloc);
   }
   /*---(last location)------------------*/
   else if (strncmp (a_question, "location_last"     , 20)      == 0) {
      snprintf (unit_answer, LEN_TEXT, "location last    : (%2d) %s", s_nloc - 1, s_locs [s_nloc - 1].path);
   }
   /*---(location command count)---------*/
   else if (strncmp (a_question, "location_ncmd"     , 20)      == 0) {
      snprintf (unit_answer, LEN_TEXT, "location links   : %2d %-25.25s %3d", a_num, s_locs [a_num].path, s_locs [a_num].ncmd);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


/*===============================[[ end-code ]]===============================*/
