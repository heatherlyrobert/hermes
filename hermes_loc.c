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



tLOC        locs        [LOC_MAX];
int         nloc        = 0;

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
   if (a_loc  <  0) {
      DEBUG_LOCS   yLOG_note    ("warning, location index is negative");
      return LOC_NEGATIVE;
   }
   if (a_loc  >= LOC_MAX)  {
      DEBUG_LOCS   yLOG_note    ("warning, location index is greater than max");
      return LOC_OVERMAX;
   }
   if (a_loc  == nloc)  {
      DEBUG_LOCS   yLOG_note    ("warning, location index is at next");
      return LOC_ATNEXT;
   }
   if (a_loc  >  nloc)  {
      DEBUG_LOCS   yLOG_note    ("warning, location index is too high");
      return LOC_TOOHIGH;
   }
   if (nloc >= LOC_MAX) {
      DEBUG_LOCS   yLOG_note    ("warning, location structure is full");
      return LOC_FULL;
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
   DEBUG_LOCS  yLOG_enter   (__FUNCTION__);
   DEBUG_LOCS  yLOG_value   ("slots"     , LOC_MAX);
   /*---(cycle)--------------------------*/
   for (i = 0; i < LOC_MAX; ++i) {
      LOC_wipe (i);
   }
   DEBUG_LOCS  yLOG_note    ("initialized all slots");
   /*---(counter)------------------------*/
   nloc = 0;
   DEBUG_LOCS  yLOG_value   ("nloc"      , nloc);
   /*---(complete)-----------------------*/
   DEBUG_LOCS  yLOG_exit    (__FUNCTION__);
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
   int         i           = 0;             /* iterator -- location           */
   int         found       = -1;            /* generic locator                */
   int         len         = 0;             /* generic string length          */
   /*---(defense))-----------------------*/
   if (a_name == NULL)      return -2;
   len = strlen (a_name);
   if (len    == 0   )      return -3;
   /*---(cycle)--------------------------*/
   for (i = 0; i < nloc; ++i) {
      /*---(filter)----------------------*/
      if (locs [i].len                   != len)   continue;
      if (strcmp (locs [i].path, a_name) != 0  )   continue;
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
   DEBUG_LOCATIONS   printf ("   appending location: ");
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
   if (nloc >= LOC_MAX) {
      DEBUG_LOCATIONS   printf ("location structure full, SKIPPING\n");
      return rce;
   }
   --rce;
   if (a_path == NULL) {
      DEBUG_LOCATIONS   printf ("location name is null, SKIPPING\n");
      return -7;
   }
   found = LOC_find (a_path);
   --rce;
   if (found < -1) {
      DEBUG_LOCATIONS   printf ("bad name or length, SKIPPING\n");
      return rce;
   }
   DEBUG_LOCATIONS   printf ("%-20.20s, ", a_path);
   if (found >= 0 && locs [found].source != '#')  {
      DEBUG_LOCATIONS   printf ("already exists as %d, done\n", found);
      return found;
   }
   len = strlen (a_path);
   --rce;
   if (len >= STR_MAX) {
      DEBUG_LOCATIONS   printf ("name too long (%d vs. %d)\n", len, STR_MAX);
      return rce;
   }
   --rce;
   if (len <  4) {
      DEBUG_LOCATIONS   printf ("name too short (%d vs. %d)\n", len, 4);
      return rce;
   }
   --rce;
   if (strchr (valid_src, a_source) == NULL) {
      DEBUG_LOCATIONS   printf ("bad location type (%c vs %s), SKIPPING\n", a_source, valid_src);
      return rce;
   }
   /*---(test against real location)-----*/
   dir = opendir(a_path);
   --rce;
   if (dir == NULL) {
      DEBUG_LOCATIONS    printf ("skipping, not a real directory\n");
      closedir (dir);
      return rce;
   }
   closedir (dir);
   /*---(append)-------------------------*/
   if (found == -1)  found = nloc;
   locs [found].source   = a_source;
   strncpy (locs [found].path, a_path, STR_MAX);
   if (a_desc != NULL)  strncpy (locs [found].desc, a_desc, STR_REG);
   else                 strncpy (locs [found].desc, "n/a" , STR_REG);
   locs [found].len      = len;
   locs [found].ncmd     = 0;
   /*---(error-flags)--------------------*/
   locs [found].f_concern  = '-';
   for (i = 0; i < len; ++i) {
      /*---(test basic)------------------*/
      if (strchr (x_valid, locs [found].path [i]) != NULL)  continue;
      /*---(test extra)------------------*/
      if (strchr (x_extra, locs [found].path [i]) != NULL) {
         locs [found].f_concern = '+';
         continue;
      }
      /*---(othre is bad)----------------*/
      locs [found].f_concern = '#';
      break;
   }  /*---(done)------------------------*/
   /*---(focus)--------------------------*/
   if (  locs [found].len == my.focus_len &&
         strcmp (locs [found].path, my.focus) == 0) {
      locs [found].active = 'y';
   }
   /*---(update)-------------------------*/
   DEBUG_LOCATIONS   printf ("added as %d, done\n", found);
   ++nloc;
   /*---(complete)-----------------------*/
   return found;
}

char             /* [------] clear a single location entry -------------------*/
LOC_wipe           (int a_loc)
{
   /*---(defenses)-----------------------*/
   if (a_loc >= LOC_MAX)   return -1;
   /*---(database)-----------------------*/
   locs [a_loc].active         = my.def_loc;
   locs [a_loc].source         = '?';
   locs [a_loc].path [0]       = '\0';
   locs [a_loc].desc [0]       = '\0';
   /*---(working)------------------------*/
   locs [a_loc].len            =  0;
   locs [a_loc].ncmd           =  0;
   /*---(error-flags)--------------------*/
   locs [a_loc].f_concern      = '-';
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
   DEBUG_LOCATIONS   printf ("   linking location/command  : ");
   /*---(defenses)-----------------------*/
   // location index
   rcc = LOC_valid (a_loc);
   if (rcc < 0)  {
      DEBUG_LOCATIONS   printf (", SKIPPING\n");
      return rcc;
   }
   // command index


   --rce;  /*=== cmd index negative ====*/
   if (a_cmd < 0) {
      DEBUG_LOCATIONS   printf ("ommand index negative (%d), SKIPPING\n", a_cmd);
      return rce;
   }
   --rce;  /*=== loc index too high ====*/
   if (a_cmd >  ncmd) {
      DEBUG_LOCATIONS   printf ("command index too high (%d >  %d), SKIPPING\n", a_cmd, ncmd);
      return rce;
   }
   --rce;  /*=== command already linked =*/
   if (cmds [a_cmd].i_loc >= 0) {
      DEBUG_LOCATIONS   printf ("command already linked to location (%d), SKIPPING\n", cmds [a_cmd].i_loc);
      return rce;
   }
   /*---(link)---------------------------*/
   cmds [a_cmd].i_loc = a_loc;
   ++locs [a_loc].ncmd;
   DEBUG_LOCATIONS   printf ("linked %s to %s, done\n", cmds [a_cmd].name, locs [a_loc].path);
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] unlink a command from a location ----------------*/
LOC_unlink         (int a_cmd)
{
   DEBUG_LOCATIONS   printf ("   unlinking package/command: ");
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* iterator -- location           */
   int         found       = -1;            /* generic locator                */
   int         x_loc       = -1;
   char        rce         = -10;           /* return code for errors         */
   char        rcc         = 0;             /* return code as char            */
   /*---(defense))-----------------------*/
   if (a_cmd < 0) {
      DEBUG_LOCATIONS   printf ("aommand index negative, SKIPPING\n");
      return -3;
   }
   if (a_cmd >  ncmd) {
      DEBUG_LOCATIONS   printf ("command index too high, SKIPPING\n");
      return -4;
   }
   x_loc = cmds [a_cmd].i_loc;
   // location index
   rcc = LOC_valid (x_loc);
   if (rcc < 0)  {
      DEBUG_LOCATIONS   printf (", SKIPPING\n");
      return rcc;
   }
   /*---(link)---------------------------*/
   cmds [a_cmd].i_loc = -1;
   --locs [x_loc].ncmd;
   DEBUG_PACKAGES   printf ("unlinked %s from %s, done\n", cmds [a_cmd].name, locs [x_loc].path);
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
   printf ("HERMES-DIACTOROS -- location report                                                            %3d of %3d slots used\n", nloc, LOC_MAX);
   printf ("\n");
   printf ("  seq# indx  s a  ---path--------------------------------- len  -c-  ncmd   ---dsec---------------------------------\n");
   /*---(cycle location)-----------------*/
   for (i = 0; i < nloc; ++i) {
      /*> if ((i % 5) == 0)   printf ("\n");                                          <*/
      printf ("  %4d %4d  %c %c  %-40.40s %3d   %c   %4d   %-40.40s\n", i, i,
            locs [i].source , locs [i].active   , locs [i].path,
            locs [i].len    , locs [i].f_concern, 
            locs [i].ncmd   , locs [i].desc);
      x_cmds += locs [i].ncmd;
   }
   /*---(footer)-------------------------*/
   printf ("\n");
   printf ("   end of locations ------------------------------------------------------------------------------------------------\n");
   printf ("      key :: s/sources   are  'c' = from config file  ,  'a' = command line add  ,  'd' = from command db         ::\n");
   printf ("          :: c/concerns  are  '-' = path is great     ,  '+' = extra chars used  ,  '#' = bad chars used          ::\n");
   printf ("\n");
   printf ("   GRAND TOTAL of %d commands stored in %d directory locations\n", x_cmds, nloc);
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
   if      (nloc < 1) {
      snprintf (unit_answer, LEN_TEXT, "location empty   : no locations exist");
   }
   else if (a_num < 0) {
      snprintf (unit_answer, LEN_TEXT, "location error   : location ref (%d) is negative", a_num);
   }
   else if (a_num != 0 && a_num >= nloc) {
      snprintf (unit_answer, LEN_TEXT, "location error   : location ref (%d vs %d) is too high", a_num, nloc);
   }
   /*---(location name)------------------*/
   else if (strncmp (a_question, "location_name"     , 20)      == 0) {
      snprintf (unit_answer, LEN_TEXT, "location name    : %3d, %c, %-.35s", a_num, locs [a_num].source, locs [a_num].path);
   }
   /*---(location count)-----------------*/
   else if (strncmp (a_question, "location_count"    , 20)      == 0) {
      snprintf (unit_answer, LEN_TEXT, "location count   : %d", nloc);
   }
   /*---(last location)------------------*/
   else if (strncmp (a_question, "location_last"     , 20)      == 0) {
      snprintf (unit_answer, LEN_TEXT, "location last    : (%2d) %s", nloc - 1, locs [nloc - 1].path);
   }
   /*---(location command count)---------*/
   else if (strncmp (a_question, "location_ncmd"     , 20)      == 0) {
      snprintf (unit_answer, LEN_TEXT, "location links   : %2d %-25.25s %3d", a_num, locs [a_num].path, locs [a_num].ncmd);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


/*===============================[[ end-code ]]===============================*/
