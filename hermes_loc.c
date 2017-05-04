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



/*===[[ location struct ]]============*/
/*---(design notes)-------------------*/
/*
 * locations are location of the compiled code
 *
 *
 * the two primary fields are...
 *
 *    source   :  c is loaded from the configuration file   ( search    )
 *                a is added as a command line argument     ( search    )
 *                # is added while reading command database ( no search )
 *
 *    path     :  fully qualified directory path
 *
 */
#define     MAX_LOCATIONS     100
#define     LEN_PATH           50
typedef     struct cLOC  tLOC;
struct      cLOC {
   /*---(base)---------------------------*/
   char        active;                 /* verify commands in this loc         */
   char        source;                 /* what method created this entry      */
   char        path        [STR_MAX];  /* directory path                      */
   char        desc        [STR_REG];  /* free-form description               */
   /*---(working)------------------------*/
   int         len;                    /* length of path string               */
   int         ncmd;                   /* number of commands in location      */
   /*---(error-flags)--------------------*/
   char        f_concern;              /* flag for path name issues           */
}; /*---(done)---------------------------*/
tLOC        s_locs      [MAX_LOCATIONS]; /* location data structure           */
int         s_nloc      = 0;             /* total number of locations         */
int         s_cloc      = -1;            /* current location in use           */



static char valid_src   [10] = "cad";    /* valid source types                */
/*  c = from configuration file /etc/themis.conf
 *  a = from command line argument
 *  d = from command database
 */



/*====================------------------------------------====================*/
/*===----                 validation/checking functions                ----===*/
/*====================------------------------------------====================*/
static void      o___CHECKERS________________o (void) {;}

char             /*-> validate a location index ----------[ ------ [ ------ ]-*/
LOC_check_index     (int a_loc)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;      /* return code for errors              */
   /*---(header)-------------------------*/
   DEBUG_DIRS   yLOG_senter  (__FUNCTION__);
   DEBUG_DIRS   yLOG_sint    (a_loc);
   /*---(defenses)-----------------------*/
   --rce;  if (a_loc  <  0) {
      DEBUG_DIRS   yLOG_snote   ("can not be negative");
      DEBUG_DIRS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_loc  >= MAX_LOCATIONS)  {
      DEBUG_DIRS   yLOG_snote   ("over maximum allowed");
      DEBUG_DIRS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_loc  >= s_nloc)  {
      DEBUG_DIRS   yLOG_snote   ("unused, open slot");
      DEBUG_DIRS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DIRS   yLOG_snote   ("validated");
   DEBUG_DIRS   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char             /*-> validate a location name -----------[ ------ [ ------ ]-*/
LOC_check_path      (char *a_path)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;      /* return code for errors              */
   int         x_len       =   0;
   DIR        *x_dir       = NULL;          /* directory pointer              */
   /*---(header)-------------------------*/
   DEBUG_DIRS   yLOG_senter  (__FUNCTION__);
   DEBUG_DIRS   yLOG_spoint  (a_path);
   /*---(defenses)-----------------------*/
   --rce;  if (a_path ==  NULL) {
      DEBUG_DIRS   yLOG_snote   ("can not be null");
      DEBUG_DIRS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DIRS   yLOG_snote   ("name real");
   x_len = strlen (a_path);
   DEBUG_DIRS   yLOG_sint    (x_len);
   --rce;  if (x_len <  4) {
      DEBUG_DIRS   yLOG_snote   ("path too short");
      DEBUG_DIRS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_len >= LEN_PATH) {
      DEBUG_DIRS   yLOG_snote   ("path too long");
      DEBUG_DIRS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DIRS   yLOG_snote   ("length good");
   --rce;  if (a_path[0] !=  '/') {
      DEBUG_DIRS   yLOG_snote   ("must be absolute path");
      DEBUG_DIRS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(test against real location)-----*/
   x_dir = opendir (a_path);
   --rce;  if (x_dir == NULL) {
      closedir (x_dir);
      DEBUG_DIRS   yLOG_snote   ("does not exist");
      DEBUG_DIRS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   closedir (x_dir);
   DEBUG_DIRS   yLOG_snote   ("dir exists");
   /*---(complete)-----------------------*/
   DEBUG_DIRS   yLOG_snote   ("validated");
   DEBUG_DIRS   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char             /*-> validate a location name -----------[ ------ [ ------ ]-*/
LOC_clean_path      (char *a_path)
{
   /*---(locals)-----------+-----------+-*/
   int         x_len       =   0;
   int         i           =   0;
   char        x_concern   = '-';
   char        x_valid     []          = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_./";
   char        x_extra     []          = "-";
   /*---(header)-------------------------*/
   DEBUG_DIRS   yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   x_len = strlen (a_path);
   /*---(test path cleaness)-------------*/
   for (i = 0; i < x_len; ++i) {
      /*---(test basic)------------------*/
      if (strchr (x_valid, a_path [i]) != NULL)  continue;
      /*---(test extra)------------------*/
      if (strchr (x_extra, a_path [i]) != NULL) {
         x_concern = '+';
         continue;
      }
      /*---(other is bad)----------------*/
      x_concern = '#';
      break;
   }
   DEBUG_DIRS   yLOG_schar   (x_concern);
   /*---(complete)-----------------------*/
   DEBUG_DIRS   yLOG_sexit   (__FUNCTION__);
   return x_concern;
}



/*====================------------------------------------====================*/
/*===----                  searching/finding functions                 ----===*/
/*====================------------------------------------====================*/
static void      o___FINDERS_________________o (void) {;}

int              /*-> locate a location by path ----------[ ------ [ ------ ]-*/
LOC_find_path           (char  *a_path)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;
   char        rc          =   0;
   int         x_len       = 0;             /* generic string length          */
   int         x_found     = -1;            /* generic locator                */
   int         i           = 0;             /* iterator -- location           */
   /*---(header)-------------------------*/
   DEBUG_DIRS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   s_cloc = -1;
   /*---(defense))-----------------------*/
   rc = LOC_check_path (a_path);
   --rce;  if (rc < 0) {
      DEBUG_DIRS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DIRS   yLOG_note    (a_path);
   x_len = strlen (a_path);
   DEBUG_DIRS   yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len  == 0   ) {
      DEBUG_DIRS   yLOG_note    ("can not be blank");
      DEBUG_DIRS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(cycle)--------------------------*/
   for (i = 0; i < s_nloc; ++i) {
      /*---(filter)----------------------*/
      if (strncmp (s_locs [i].path, a_path, s_locs [i].len) != 0    )   continue;
      if (s_locs [i].len != x_len) {
         if (a_path [s_locs [i].len] != '/') continue;
      }
      /*---(save)------------------------*/
      x_found = i;
      break;
   }
   DEBUG_DIRS   yLOG_value   ("x_found"   , x_found);
   --rce;  if (x_found < 0) {
      rce = -1;
      DEBUG_DIRS   yLOG_note    ("cound not find");
      DEBUG_DIRS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DIRS   yLOG_note    ("FOUND");
   /*---(complete)-----------------------*/
   DEBUG_DIRS   yLOG_exit    (__FUNCTION__);
   return x_found;
}

char
LOC_remove_path    (int a_loc, char *a_path)
{
   char        x_suffix    [200];
   if (a_path == NULL)  return -1;
   strlcpy (x_suffix, a_path, 200);
   LOC_curs_index (a_loc);
   strlcpy (a_path, x_suffix + s_locs [s_cloc].len + 1, 100);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                   data structure cursors                     ----===*/
/*====================------------------------------------====================*/
static void      o___CURSORS_________________o (void) {;}

char             /*-> return first directory -------------[ ------ [ ------ ]-*/
LOC_curs_index      (int a_loc)
{
   if (s_nloc < 0) {
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
   s_cloc = a_loc;
   return 0;
}

char             /*-> return first directory -------------[ ------ [ ------ ]-*/
LOC_curs_head      (void)
{
   s_cloc = 0;
   if (s_nloc == 0) {
      s_cloc = -1;
      return -1;
   }
   return 0;
}

char             /*-> return first directory -------------[ ------ [ ------ ]-*/
LOC_curs_next      (void)
{
   if (s_nloc == 0) {
      s_cloc = -1;
      return -1;
   }
   ++s_cloc;
   if (s_cloc >= s_nloc) {
      s_cloc = -1;
      return -2;
   }
   return 0;
}



/*====================------------------------------------====================*/
/*===----                information getting functions                 ----===*/
/*====================------------------------------------====================*/
static void      o___GETTERS_________________o (void) {;}

int              /*-> return count of locations ----------[ ------ [ ------ ]-*/
LOC_get_count       (void)   { return s_nloc; }

char*            /*-> return current rectory -------------[ ------ [ ------ ]-*/
LOC_get_path        (void)   { if (s_cloc <  0) return "" ; return s_locs [s_cloc].path;   }

char             /*-> return current rectory -------------[ ------ [ ------ ]-*/
LOC_get_source      (void)   { if (s_cloc <  0) return '?'; return s_locs [s_cloc].source; }

int              /*-> return current rectory -------------[ ------ [ ------ ]-*/
LOC_get_commands    (void)   { if (s_cloc <  0) return 0  ; return s_locs [s_cloc].ncmd;   }

char*            /*-> return current rectory -------------[ ------ [ ------ ]-*/
LOC_get_desc        (void)   { if (s_cloc <  0) return "" ; return s_locs [s_cloc].desc;   }



/*====================------------------------------------====================*/
/*===----                information setting functions                 ----===*/
/*====================------------------------------------====================*/
static void      o___SETTERS_________________o (void) {;}

char             /*-> return count of locations ----------[ ------ [ ------ ]-*/
LOC_addcmd         (void)   { if (s_cloc < 0)  return -1; ++s_locs[s_cloc].ncmd; return 0; }




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
   DEBUG_DIRS  yLOG_value   ("slots"     , MAX_LOCATIONS);
   /*---(cycle)--------------------------*/
   for (i = 0; i < MAX_LOCATIONS; ++i) {
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

int              /* [------] append a location to the list -------------------*/
LOC_push           (char  *a_path, char a_source, char *a_desc)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         x_found     = -1;            /* generic locator                */
   /*---(bagin)--------------------------*/
   DEBUG_DIRS  yLOG_enter   (__FUNCTION__);
   /*---(check for existing)-------------*/
   x_found = LOC_find_path (a_path);
   DEBUG_DIRS  yLOG_value   ("x_found"   , x_found);
   --rce;  if (x_found < -1) {
      DEBUG_DIRS   yLOG_note    ("bad path");
      DEBUG_DIRS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for existing)-------------*/
   --rce;  if (x_found >= 0) {
      DEBUG_DIRS   yLOG_note    ("already exists");
      DEBUG_DIRS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for too many)-------------*/
   --rce;
   if (s_nloc >= MAX_LOCATIONS) {
      DEBUG_DIRS   yLOG_note    ("location structure full");
      DEBUG_DIRS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check source)-------------------*/
   --rce;  if (strchr (valid_src, a_source) == NULL) {
      DEBUG_DIRS   yLOG_note    ("bad source type");
      DEBUG_DIRS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(append)-------------------------*/
   DEBUG_DIRS   yLOG_note    ("adding data to new record");
   if (x_found == -1)  x_found = s_nloc;
   s_locs [x_found].source   = a_source;
   strncpy (s_locs [x_found].path, a_path, STR_MAX);
   if (a_desc != NULL)  strncpy (s_locs [x_found].desc, a_desc, STR_REG);
   else                 strncpy (s_locs [x_found].desc, "n/a" , STR_REG);
   s_locs [x_found].len      = strlen (a_path);
   s_locs [x_found].ncmd     = 0;
   /*---(name concerns)------------------*/
   s_locs [x_found].f_concern  = LOC_clean_path (a_path);
   /*---(focus)--------------------------*/
   DEBUG_DIRS   yLOG_note    ("checking focus");
   if (  s_locs [x_found].len == my.focus_len &&
         strcmp (s_locs [x_found].path, my.focus) == 0) {
      s_locs [x_found].active = 'y';
   }
   /*---(update)-------------------------*/
   ++s_nloc;
   /*---(complete)-----------------------*/
   DEBUG_DIRS  yLOG_exit    (__FUNCTION__);
   return x_found;
}

char             /* [------] clear a single location entry -------------------*/
LOC_wipe           (int a_loc)
{
   /*---(defenses)-----------------------*/
   if (a_loc >= MAX_LOCATIONS)   return -1;
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
   rcc = LOC_check_index (a_loc);
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
   rcc = LOC_check_index (x_loc);
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
   printf ("HERMES-DIACTOROS -- location report                                                            %3d of %3d slots used\n", s_nloc, MAX_LOCATIONS);
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
   /*---(location cursor)----------------*/
   else if (strncmp (a_question, "location_curr"     , 20)      == 0) {
      if (s_cloc < 0)  snprintf (unit_answer, LEN_TEXT, "location curr    : %2d %s"      , s_cloc, "not set");
      else             snprintf (unit_answer, LEN_TEXT, "location curr    : %2d %-25.25s", s_cloc, s_locs [s_cloc].path);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


/*===============================[[ end-code ]]===============================*/
