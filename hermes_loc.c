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
 * locations are directories for compiled code
 *
 */
#define     MAX_LOC          2000
#define     LEN_PATH          200
typedef     struct cLOC     tLOC;
struct      cLOC {
   /*---(base)---------------------------*/
   char        active;                 /* verify commands in this loc         */
   char        source;                 /* what method created this entry      */
   char        path        [STR_MAX];  /* directory path                      */
   char        desc        [STR_REG];  /* free-form description               */
   char        type;                   /* executable vs library               */
   char        cat;                    /* category of location                */
   /*---(working)------------------------*/
   int         len;                    /* length of path string               */
   int         ncmd;                   /* number of commands in location      */
   long        size;                   /* size of commands in location        */
   int         owner;                  /* connected to which main location    */
   long        total;                  /* size of all commands under loc      */
   /*---(error-flags)--------------------*/
   char        f_concern;              /* flag for path name issues           */
}; /*---(done)---------------------------*/
static tLOC s_locs      [MAX_LOC];     /* location data structure           */
static int  s_iloc      [MAX_LOC];     /* index for locations                 */
static int  s_nloc      = 0;             /* total number of locations         */
static int  s_cloc      = -1;            /* current location in use           */



static char s_sources   [10] = "cadi";    /* valid source types                */
/*  c = from configuration file /etc/themis.conf
 *  a = from command line argument
 *  d = from command database
 *  i = from /var/db/pkg as used for installations
 */



/*====================------------------------------------====================*/
/*===----                    system-wide operations                    ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char             /*-> prepare for system use -------------[ ------ [ ------ ]-*/
LOC_init           (void)
{
   LOC__purge ();
   return 0;
}

char             /*-> initialize all entries -------------[ ------ [ ------ ]-*/
LOC__purge         (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* iterator -- location           */
   /*---(bagin)--------------------------*/
   DEBUG_DIRS  yLOG_enter   (__FUNCTION__);
   DEBUG_DIRS  yLOG_value   ("slots"     , MAX_LOC);
   /*---(cycle)--------------------------*/
   for (i = 0; i < MAX_LOC; ++i) {
      LOC__wipe (i);
   }
   DEBUG_DIRS  yLOG_note    ("initialized all slots");
   /*---(counter)------------------------*/
   s_nloc = 0;
   DEBUG_DIRS  yLOG_value   ("s_nloc"      , s_nloc);
   /*---(complete)-----------------------*/
   DEBUG_DIRS  yLOG_exit    (__FUNCTION__);
   return 0;
}

char             /*-> wrap up during system shutdown -----[ ------ [ ------ ]-*/
LOC_wrap           (void)
{
   LOC__purge ();
   return 0;
}

int              /*-> return count of locations ----------[ ------ [ ------ ]-*/
LOC_count      (void)        { return s_nloc; }



/*====================------------------------------------====================*/
/*===----                      ordering and sorting                    ----===*/
/*====================------------------------------------====================*/
static void      o___ORDERING________________o (void) {;}

char             /* [------] teleporting gnome sort --------------------------*/
LOC_sort           (void)
{
   DEBUG_SORT   printf("sorting location records (indexed teleporting gnome)...\n");
   /*---(locals)-----------+-----------+-*/
   int         i           =  1;            /* current position               */
   int         one         =  1;            /* position one                   */
   int         two         =  1;            /* position two                   */
   char        s           [200];
   char        t           [200];
   int         rci         =  0;            /* integer return code            */
   int         temp        =  0;            /* temp storage for moves         */
   int         tele        = -1;            /* teleportation point            */
   int         comps       =  0;            /* number of comparisons          */
   int         moves       =  0;            /* number of moves                */
   /*---(sort)---------------------------*/
   DEBUG_SORT   printf("   start : %d packages\n", s_nloc);
   /*---(clear)--------------------------*/
   for (i = 0; i < s_nloc; ++i)  s_iloc [i] = i;
   /*---(sort)---------------------------*/
   i = 1;
   while (i < s_nloc) {
      one = s_iloc [i - 1];
      two = s_iloc [i    ];
      /*---(header)--------------------------------*/
      DEBUG_SORT   printf("   %-4d  %-4d  <%-40.40s>    %-4d  %-4d  <%-40.40s>    ", i - 1, one, s_locs [one].path, i    , two, s_locs [two].path);
      /*---(compare)-------------------------------*/
      ++comps;
      rci = strcmp (s_locs [one].path, s_locs [two].path);
      DEBUG_SORT   printf("%2d    ", rci);
      if ((i == 0) || (rci <= 0)) {
         if (tele >= 0)  { i = tele; tele = -1; }
         else            ++i;
         DEBUG_SORT   printf("good    %-4d    %-4d    SKIPPING\n");
         continue;
      }
      /*---(sorted order)--------------------------*/
      DEBUG_SORT   printf("swap    ");
      /*---(swap)----------------------------------*/
      ++moves;
      temp           = s_iloc [i];
      s_iloc [i]     = s_iloc [i - 1];
      s_iloc [i - 1] = temp;
      /*---(update)--------------------------------*/
      if (tele < 0)  tele = i;              /* only update on first move      */
      if (i > 1) --i;
      DEBUG_SORT   printf("%-4d    %-4d    swapped\n");
   }
   long      n2     = (long)   s_nloc * s_nloc;
   float     ratio  = ((float) moves / n2) * 100;
   float     action = ((float) moves / comps) * 100;
   DEBUG_SORT   printf("   moves : %d items, %d comp(s), %d move(s)\n", s_nloc, comps, moves);
   DEBUG_SORT   printf("   stats : N2 = %ld, action (move/N2) = %2.0f%%, efficiency (move/comp) = %2.0f%%\n", n2, ratio, action);
   DEBUG_SORT   printf("\n");
   /*---(complete)------------------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      single entry actions                    ----===*/
/*====================------------------------------------====================*/
static void      o___SINGLE__________________o (void) {;}

int              /* [------] append a location to the list -------------------*/
LOC_create         (char  *a_path, char a_source, char *a_desc)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         x_found     = -1;            /* generic locator                */
   /*---(bagin)--------------------------*/
   DEBUG_DIRS  yLOG_enter   (__FUNCTION__);
   /*---(check for existing)-------------*/
   x_found = LOC_find_path (a_path, 'a');
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
   if (s_nloc >= MAX_LOC) {
      DEBUG_DIRS   yLOG_note    ("location structure full");
      DEBUG_DIRS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check source)-------------------*/
   --rce;  if (strchr (s_sources, a_source) == NULL) {
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
   LOC_set_type (s_nloc);
   ++s_nloc;
   /*---(complete)-----------------------*/
   DEBUG_DIRS  yLOG_exit    (__FUNCTION__);
   return x_found;
}

char             /* [------] clear a single location entry -------------------*/
LOC__wipe          (int a_loc)
{
   /*---(defenses)-----------------------*/
   if (a_loc >= MAX_LOC)   return -1;
   /*---(database)-----------------------*/
   s_locs [a_loc].active         = my.def_loc;
   s_locs [a_loc].source         = '?';
   s_locs [a_loc].path [0]       = '\0';
   s_locs [a_loc].desc [0]       = '\0';
   s_locs [a_loc].type           = '-';
   s_locs [a_loc].cat            = '-';
   /*---(working)------------------------*/
   s_locs [a_loc].len            =  0;
   s_locs [a_loc].ncmd           =  0;
   s_locs [a_loc].size           =  0;
   s_locs [a_loc].owner          = -1;
   s_locs [a_loc].total          =  0;
   /*---(error-flags)--------------------*/
   s_locs [a_loc].f_concern      = '-';
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                information getting functions                 ----===*/
/*====================------------------------------------====================*/
static void      o___ACCESSORS_______________o (void) {;}

char*            /*-> return current rectory -------------[ ------ [ ------ ]-*/
LOC_get_path       (int a_loc)
{
   if (a_loc < 0 || a_loc >= s_nloc) return "" ;
   return s_locs [a_loc].path;
}

char             /*-> return count of locations ----------[ ------ [ ------ ]-*/
LOC_add_cmd        (int a_loc, long a_size)
{
   if (a_loc < 0 || a_loc >= s_nloc) return -1;
   ++s_locs [a_loc].ncmd;
   s_locs [a_loc].size += a_size;
   return 0;
}

char             /*-> identify the type ------------------[ ------ [ ------ ]-*/
LOC_set_type       (int a_loc)
{
   /*---(locals)-----------+-----------+-*/
   int         x_len       = 0;
   /*---(defense)------------------------*/
   if (a_loc  < 0 || a_loc  >  s_nloc) return -1;
   /*---(interpretive langs)-------------*/
   if      (strstr  (s_locs [a_loc].path, "/lib"  ) != NULL)
      s_locs [a_loc].type = 'l';
   else
      s_locs [a_loc].type = 'e';
   /*---(complete)-----------------------*/
   return 0;
}

char             /*-> identify the category --------------[ ------ [ ------ ]-*/
LOC_set_cat        (int a_loc, int a_save)
{
   /*---(locals)-----------+-----------+-*/
   int         x_len       = 0;
   /*---(defense)------------------------*/
   if (a_loc  < 0 || a_loc  >= s_nloc) return -1;
   if (a_save < 0 || a_save >= s_nloc) return -2;
   /*---(prepare)------------------------*/
   x_len = s_locs [a_save].len;
   s_locs [a_loc].cat     = 's';
   /*---(interpretive langs)-------------*/
   if      (strncmp (s_locs [a_loc].path + x_len, "/python", 7) == 0)
      s_locs [a_loc].cat  = 'p';
   else if (strncmp (s_locs [a_loc].path + x_len, "/perl"  , 5) == 0)
      s_locs [a_loc].cat  = 'e';
   else if (strncmp (s_locs [a_loc].path + x_len, "/ruby"  , 5) == 0)
      s_locs [a_loc].cat  = 'r';
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                 validation/checking functions                ----===*/
/*====================------------------------------------====================*/
static void      o___HELPERS_________________o (void) {;}

char             /*-> validate a location index ----------[ ------ [ ------ ]-*/
LOC_valid           (int a_loc)
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
   --rce;  if (a_loc  >= MAX_LOC)  {
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
   char        rce         =  -10;      /* return code for errors              */
   int         rci         =    0;
   int         x_len       =    0;
   DIR        *x_dir       = NULL;          /* directory pointer              */
   tSTAT       st;                          /* file stats                     */
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
      printf ("LOC TOO LONG <%s>\n", a_path);
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
   /*---(get the file information)-------*/
   rci = lstat (a_path, &st);
   DEBUG_DIRS   yLOG_value   ("lstat_rc"  , rci);
   /*---(defense : real file)------------*/
   --rce; if (rci < 0) {
      DEBUG_DIRS   yLOG_note    ("lstat can not find file, exiting");
      DEBUG_DIRS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(type)---------------------------*/
   --rce;  if (! S_ISDIR (st.st_mode)) {
      DEBUG_DIRS   yLOG_note    ("not a real dir");
      DEBUG_DIRS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
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
static void      o___FILTERING_______________o (void) {;}

int              /*-> locate a location by path ----------[ ------ [ ------ ]-*/
LOC_find_path           (char  *a_path, char a_type)
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
   DEBUG_DIRS   yLOG_char    ("a_type"    , a_type);
   --rce;  if (strchr ("sa", a_type) == NULL) {
      DEBUG_DIRS   yLOG_note    ("incorrect search type");
      DEBUG_DIRS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(cycle)--------------------------*/
   for (i = 0; i < s_nloc; ++i) {
      /*---(filter absolutes)------------*/
      if (a_type == 'a' && strcmp  (s_locs [i].path, a_path) != 0    )   continue;
      /*---(filter subdirs)--------------*/
      if (a_type == 's') {
         if (s_locs [i].source != 'c')                                   continue;
         if (strncmp (s_locs [i].path, a_path, s_locs [i].len) != 0    ) continue;
         if (s_locs [i].len != x_len) {
            if (a_path [s_locs [i].len] != '/') continue;
         }
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

char*            /*-> return current rectory -------------[ ------ [ ------ ]-*/
LOC_curr_path      (void)        { if (s_cloc <  0) return "" ; return s_locs [s_cloc].path;   }

char             /*-> return current rectory -------------[ ------ [ ------ ]-*/
LOC_curr_source    (void)        { if (s_cloc <  0) return '?'; return s_locs [s_cloc].source; }

int              /*-> return current rectory -------------[ ------ [ ------ ]-*/
LOC_curr_commands  (void)        { if (s_cloc <  0) return 0  ; return s_locs [s_cloc].ncmd;   }

char*            /*-> return current rectory -------------[ ------ [ ------ ]-*/
LOC_curr_desc      (void)        { if (s_cloc <  0) return "" ; return s_locs [s_cloc].desc;   }



/*====================------------------------------------====================*/
/*===----                     linking and hooking                      ----===*/
/*====================------------------------------------====================*/
static void      o___STRUCTURE_______________o (void) {;}

char             /* [------] link a command to a location --------------------*/
LOC_treeify        (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           =   0;           /* iterator for locations         */
   int         x_curr      =   0;           /* indexed order                  */
   int         x_owner     =   0;
   int         x_len       =   0;
   /*---(walk)---------------------------*/
   for (i = 0; i < s_nloc; ++i) {
      /*---(indexed)---------------------*/
      x_curr = s_iloc [i];
      /*---(new owner)-------------------*/
      if (s_locs [x_curr].source == 'c') {
         x_owner = x_curr;
         s_locs [x_curr].owner = -1;
         continue;
      }
      s_locs [x_curr].owner = x_owner;
   }
   /*---(complete)-----------------------*/
   return 0;
}

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
   int         x_pass      = 0;             /* iterator -- location           */
   int         i           = 0;             /* iterator -- location           */
   int         c           = 0;             /* count of lines shown           */
   int         x_page      = 0;
   int         x_pages     = 0;
   int         x_max       = 0;
   int         x_maxwith   = 0;
   int         x_curr      = 0;
   int         x_skip      = 0;
   char        x_long      = ' ';
   char       *x_header    = "  seq# indx  s a  ---path------------------------------------------------------ len  -c-  typ  cat  ncmd  ---size---   ---desc---------------------------------  lookupkey";
   int         x_cats      [26];
   int         x_totals    [26];
   long        x_sizes     [26];
   char        s           [300];
   int         x_oth       = 0;
   int         x_othcmd    = 0;
   long        x_othsize   = 0;
   int         x_lib       = 0;
   int         x_libcmd    = 0;
   long        x_libsize   = 0;
   int         x_exe       = 0;
   int         x_execmd    = 0;
   long        x_exesize   = 0;
   int         x_cmds      = 0;
   long        x_size      = 0;
   /*---(header)-------------------------*/
   printf ("\n");
   /*---(cycle location)-----------------*/
   for (x_pass = 0; x_pass < 2; ++x_pass) {
      x_page = 0;
      c      = 0;
      x_skip = 0;
      for (i = 0; i < 26; ++i)  { x_cats [i] = 0; x_totals [i] = 0; x_sizes [i] = 0; }
      for (i = 0; i < s_nloc; ++i) {
         x_curr = s_iloc [i];
         if (s_locs [x_curr].len > x_max)  x_max = s_locs [x_curr].len;
         if (s_locs [x_curr].ncmd <= 0) {
            ++x_skip;
            continue;
         }
         if ((c % 45) == 0) {
            ++x_page;
            if (x_pass > 0) {
               if (c > 0) {
                  printf ("\n%s\n", x_header);
                  printf ("\n");
                  printf ("      key :: s/sources   are  'c' = from config file  ,  'i' = /var/db/pkg       ,  'd' = from command db   ::\n");
                  printf ("          :: c/concerns  are  '-' = path is great     ,  '+' = extra chars used  ,  '#' = bad chars used    ::\n");
                  printf  ("\n\n");
               }
               printf  ("\n");
               sprintf (s, "%-153.153s  version  [%4s]" , "HERMES-DIACTOROS (messenger) integrity assurance for executables and shared libraries", VER_NUM);
               printf  ("%s\n", s);
               sprintf (s, "%-153.153s  page %3d of %3d", "location reporting sorted by location/name", x_page, x_pages);
               printf  ("%s\n", s);
               printf ("\n%s\n", x_header);
            }
         }
         if (x_pass > 0 && (c %  5) == 0)  printf ("\n");
         if (x_pass > 0) {
            if (s_locs [x_curr].len > 60) x_long = '>';
            else                          x_long = ' ';
            printf ("  %4d %4d %4d  %c %c  %-60.60s%c %3d   %c    %c    %c   %4d  %10d   %-40.40s  [loc%04d]\n",
                  x_curr, i, s_locs [x_curr].owner,
                  s_locs [x_curr].source , s_locs [x_curr].active   ,
                  s_locs [x_curr].path   , x_long                   ,
                  s_locs [x_curr].len    , s_locs [x_curr].f_concern, 
                  s_locs [x_curr].type   , s_locs [x_curr].cat      ,
                  s_locs [x_curr].ncmd   , s_locs [x_curr].size     ,
                  s_locs [x_curr].desc   , x_curr                   );
            if (s_locs [x_curr].len > x_maxwith)  x_maxwith = s_locs [x_curr].len;
            x_cmds += s_locs [x_curr].ncmd;
            x_size += s_locs [x_curr].size;
            if (s_locs [x_curr].cat >= 'a' && s_locs [x_curr].cat <= 'z') {
               ++x_cats [s_locs [x_curr].cat - 'a'];
               x_totals [s_locs [x_curr].cat - 'a'] += s_locs [x_curr].ncmd;
               x_sizes  [s_locs [x_curr].cat - 'a'] += s_locs [x_curr].size;
            } else {
               ++x_oth;
               x_othcmd   += s_locs [x_curr].ncmd;
               x_othsize += s_locs [x_curr].size;
            }
            if (s_locs [x_curr].type == 'l') {
               ++x_lib;
               x_libcmd += s_locs [x_curr].ncmd;
               x_libsize += s_locs [x_curr].size;
            } else {
               ++x_exe;
               x_execmd  += s_locs [x_curr].ncmd;
               x_exesize += s_locs [x_curr].size;
            }
         }
         ++c;
      }
      x_pages = x_page;
   }
   /*---(footer)-------------------------*/
   printf ("\n%s\n", x_header);
   printf ("\n");
   printf ("   GRAND TOTAL of %d commands stored in %d directory locations\n", x_cmds, c);
   printf ("\n");
   printf ("ncmd                  = %d\n", ncmd);
   printf ("x_cmds                = %d\n", x_cmds);
   printf ("x_size                = %d\n", x_size);
   printf ("\n");
   printf ("total locations       = %d\n", s_nloc);
   printf ("skipped               = %d\n", x_skip);
   printf ("\n");
   printf ("max len               = %d\n", x_max);
   printf ("max len with commands = %d\n", x_maxwith);
   printf ("\n");
   printf ("shown = %3d (------)   %4d (------)   %12d (------)\n", c, x_cmds, x_size);
   printf ("\n");
   for (i = 0; i < 26; ++i) {
      if (x_cats [i] > 0) {
         printf ("cat %c = %3d (%6.2f)   %4d (%6.2f)   %12d (%6.2f)\n", i + 'a',
               x_cats   [i], ((float) x_cats   [i]) / ((float) c   ),
               x_totals [i], ((float) x_totals [i]) / ((float) x_cmds),
               x_sizes  [i], ((float) x_sizes  [i]) / ((float) x_size));
      }
   }
   printf ("other = %3d (%6.2f)   %4d (%6.2f)   %12d (%6.2f)\n",
         x_oth     , ((float) x_oth     ) / ((float) c   ),
         x_othcmd  , ((float) x_othcmd  ) / ((float) x_cmds),
         x_othsize , ((float) x_othsize ) / ((float) x_size));
   printf ("\n");
   printf ("exes  = %3d (%6.2f)   %4d (%6.2f)   %12d (%6.2f)\n",
         x_exe     , ((float) x_exe     ) / ((float) c   ),
         x_execmd  , ((float) x_execmd  ) / ((float) x_cmds),
         x_exesize , ((float) x_exesize ) / ((float) x_size));
   printf ("libs  = %3d (%6.2f)   %4d (%6.2f)   %12d (%6.2f)\n",
         x_lib     , ((float) x_lib     ) / ((float) c   ),
         x_libcmd  , ((float) x_libcmd  ) / ((float) x_cmds),
         x_libsize , ((float) x_libsize ) / ((float) x_size));
   printf ("\n\n");
   /*---(complete)-----------------------*/
   return 0;
}


char             /* [------] create a hyleoroi file --------------------------*/
LOC_hyleoroi       (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           =    0;
   int         x_curr      =    0;
   int         x_owner     =    0;
   long        x_total     =    0;
   char        x_base      [LEN_PATH];
   int         x_len       =    0;
   /*---(initialize totals)--------------*/
   for (i = 0; i < s_nloc; ++i) {
      x_curr  = s_iloc [i];
      s_locs [x_curr].total = 0;
   }
   /*---(summarize)----------------------*/
   for (i = s_nloc - 1; i >= 0; --i) {
      x_curr  = s_iloc [i];
      x_owner = s_locs [x_curr].owner;
      if (x_owner == -1) {
         s_locs [x_curr ].total += s_locs [x_curr].size;
         x_total                += s_locs [x_curr].total;
      } else {
         s_locs [x_curr ].total  = s_locs [x_curr].size;
         s_locs [x_owner].total += s_locs [x_curr].total;
      }
   }
   /*---(output table)-------------------*/
   printf ("#!/usr/local/bin/hyleoroi\n");
   printf ("#   hyleoroi -- tree visualization input file\n");
   printf ("\n\n\n");
   printf ("FULL\n");
   printf ("\n\n\n");
   printf ("#--context  ---values------------------------------- \n");
   printf ("source      hermes-diactoros                         \n");
   printf ("label       executable files and libraries by size   \n");
   printf ("format      exelocs                                  \n");
   printf ("\n\n\n");
   printf ("#--nodes--  lvl  ---name-----------------------------------------------------  ----size----  ---count----  ---description--------------------------------------------------------------------------------------  \n");
   printf ("node          1  root                                                          %12d  %12d  %-100.100s  \n", x_total, x_total, " ");
   for (i = 0; i < s_nloc; ++i) {
      x_curr  = s_iloc [i];
      if (s_locs [x_curr].total <= 0)  continue;
      x_owner = s_locs [x_curr].owner;
      if (x_owner == -1) {
         printf ("\n");
         printf ("node          2     %-50.50s         %12d  %12d  %-100.100s  \n", s_locs [x_curr].path, s_locs [x_curr].total, s_locs [x_curr].total, s_locs [x_curr].path);
      } else {
         x_len  = s_locs [x_owner].len + 1;
         printf ("node          3        %-50.50s      %12d  %12d  %-100.100s  \n", s_locs [x_curr].path + x_len, s_locs [x_curr].total, s_locs [x_curr].total, s_locs [x_curr].path);
      }
   }
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
