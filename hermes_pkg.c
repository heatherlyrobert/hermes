/*===============================[[ beg-code ]]===============================*/
#include    "hermes.h"

tPKG        pkgs        [PKG_MAX];        /* main package data structure         */
int         ipkg        [PKG_MAX];        /* index for packages                  */
int         npkg        = 0;
static char valid_src   [10] = "-cw+#";   /* valid source types                */



/*====================------------------------------------====================*/
/*===----                            areas                             ----===*/
/*====================------------------------------------====================*/
static void      o___AREAS___________________o (void) {;}
/*
 *   areas are a simple, non-critical grouping mechanism for packages to be
 *   used in reporting.  areas are less detailed than gentoo categories.
 *   areas will always be read from the configuration file.
 *
 */
#define     AREA_MAX    100
typedef     struct cAREA  tAREA;
struct      cAREA {
   char        name        [STR_REG];  /* unique name                         */
   int         npackages;              /* number of packages in area          */
   int         ncommands;              /* number of commands in area          */
};
tAREA       s_areas       [AREA_MAX];    /* area data structure                 */
int         s_narea;                     /* area count                          */

char             /* [------] clear a single area entry -----------------------*/
AREA_wipe          (int a_curr)
{
   /*---(database fields)-------------*/
   s_areas [a_curr].name [0]       = '\0';
   s_areas [a_curr].npackages      = 0;
   s_areas [a_curr].ncommands      = 0;
   /*---(complete)-----------------------*/
   return 0;
}

int              /* [------] append a package --------------------------------*/
AREA_push          (char  *a_name)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* loop iterator -- location      */
   int         found       = -1;            /* generic locator                */
   int         len         = 0;             /* generic string length          */
   char        s           [200];           /* generic string                 */
   char       *p           = NULL;          /* strtok current pointer         */
   char       *q           = "/";           /* strtok delimeters              */
   char       *r           = NULL;          /* strtok_r context variable      */
   char        rce         = -10;           /* return code for errors         */
   DIR        *dir         = NULL;          /* directory pointer              */
   /*---(defenses)-----------------------*/
   --rce;     /* too many packages ------*/
   if (s_narea >= AREA_MAX) {
      return rce;
   }
   --rce;     /* null name --------------*/
   if (a_name   == NULL) {
      return rce;
   }
   --rce;     /* bad name ---------------*/
   found = AREA_find     (a_name);
   if (found < -1) {
      return rce;
   }
   --rce;     /* already appended -------*/
   if (found >= 0) {
      return found;
   }
   len = strlen (a_name);
   --rce;     /* name too long ----------*/
   if (len >= STR_REG) {
      return rce;
   }
   --rce;     /* name too short ---------*/
   if (len <  4) {
      return rce;
   }
   /*---(append)-------------------------*/
   if (found == -1)  found = s_narea;
   strncpy (s_areas [found].name, a_name, LPFULL);
   ++s_narea;
   /*---(complete)-----------------------*/
   return found;
}

int              /* [------] find a particular package entry -----------------*/
AREA_find          (char *a_name)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* iterator -- package            */
   int         found       = -1;            /* generic intex holder           */
   int         len         = 0;             /* string length                  */
   /*---(defense)------------------------*/
   if (a_name == NULL)      return -2;
   /*---(locate)-------------------------*/
   for (i = 0; i < s_narea; ++i) {
      /*---(filter)----------------------*/
      if (strcmp (s_areas [i].name, a_name) != 0  )   continue;
      /*---(save)------------------------*/
      found = i;
      break;
   }
   /*---(complete)-----------------------*/
   return found;
}

char             /* [------] display the package inventory -------------------*/
AREA_list          (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* iterator -- package            */
   /*---(output)-------------------------*/
   printf ("areas\n");
   for (i = 0; i < s_narea; ++i) {
      printf ("%2d  %-40.40s  %3d\n", i, s_areas [i].name, s_areas [i].npackages);
   }
   printf ("\n\n");
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] increment packages ------------------------------*/
AREA_addpkg        (int a_area)
{
   ++s_areas [a_area].npackages;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      helper functions                        ----===*/
/*====================------------------------------------====================*/
static void      o___HELPERS_________________o (void) {;}

char             /* [------] validate a package index ------------------------*/
PKG_valid          (int a_pkg)
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
   if (a_pkg  <  0) {
      DEBUG_PKGS    printf ("package index (%d) negative"      , a_pkg);
      return PKG_NEGATIVE;
   }
   if (a_pkg  >= PKG_MAX)  {
      DEBUG_PKGS    printf ("package index (%d vs %d) over max", a_pkg, PKG_MAX);
      return PKG_OVERMAX;
   }
   if (a_pkg  == npkg)  {
      DEBUG_PKGS    printf ("package index (%d == %d) at next" , a_pkg, npkg);
      return PKG_ATNEXT;
   }
   if (a_pkg  >  npkg)  {
      DEBUG_PKGS    printf ("package index (%d vs %d) too high", a_pkg, npkg);
      return PKG_TOOHIGH;
   }
   if (npkg  >= PKG_MAX) {
      DEBUG_PKGS    printf ("package structure full");
      return PKG_FULL;
   }
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     full table operations                    ----===*/
/*====================------------------------------------====================*/
static void      o___FULLTABLE_______________o (void) {;}

char             /* [------] identify the population of packages -------------*/
PKG_purge          (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* iterator -- location           */
   /*---(output)-------------------------*/
   DEBUG_GENTOO   printf ("\n");
   DEBUG_GENTOO   printf ("   begin initializing package data structure\n");
   /*---(clear all)----------------------*/
   for (i = 0; i < PKG_MAX;  ++i)  PKG_wipe  (i);
   npkg  = 0;
   for (i = 0; i < AREA_MAX; ++i)  AREA_wipe (i);
   s_narea = 0;
   /*---(cycle)--------------------------*/
   DEBUG_GENTOO   printf ("   done initializing %d elemeets\n", PKG_MAX);
   DEBUG_GENTOO   printf ("\n");
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] teleporting gnome sort --------------------------*/
PKG_index          (void)
{
   DEBUG_SORT   printf("sorting package records (indexed teleporting gnome)...\n");
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
   DEBUG_SORT   printf("   start : %d packages\n", npkg);
   while (i < npkg) {
      one = ipkg [i - 1];
      two = ipkg [i    ];
      /*---(header)--------------------------------*/
      DEBUG_SORT   printf("   %-4d  %-4d  <%-40.40s>    %-4d  %-4d  <%-40.40s>    ", i - 1, one, pkgs [one].full, i    , two, pkgs [two].full);
      /*---(compare)-------------------------------*/
      ++comps;
      rci = strcmp (pkgs [one].full, pkgs [two].full);
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
      temp         = ipkg [i];
      ipkg [i]     = ipkg [i - 1];
      ipkg [i - 1] = temp;
      /*---(update)--------------------------------*/
      if (tele < 0)  tele = i;              /* only update on first move      */
      if (i > 1) --i;
      DEBUG_SORT   printf("%-4d    %-4d    swapped\n");
   }
   long      n2     = (long)   npkg * npkg;
   float     ratio  = ((float) moves / n2) * 100;
   float     action = ((float) moves / comps) * 100;
   DEBUG_SORT   printf("   moves : %d items, %d comp(s), %d move(s)\n", npkg, comps, moves);
   DEBUG_SORT   printf("   stats : N2 = %ld, action (move/N2) = %2.0f%%, efficiency (move/comp) = %2.0f%%\n", n2, ratio, action);
   DEBUG_SORT   printf("\n");
   /*---(report out)----------------------------*/
   for (i = 0; i < npkg; ++i) {
      one = ipkg [i];
      DEBUG_CMDS   printf ("   %-4d  %-4d   %-40.40s\n", one, i, pkgs [one].full);
   }
   /*---(complete)------------------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    single entry updates                      ----===*/
/*====================------------------------------------====================*/
static void      o___UPDATES_________________o (void) {;}

int              /* [------] append a package --------------------------------*/
PKG_push           (char  *a_full, char  a_source, char a_priority, char *a_desc)
{
   DEBUG_PKGS   printf ("   appending package: ");
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* loop iterator -- location      */
   int         found       = -1;            /* generic locator                */
   int         len         = 0;             /* generic string length          */
   char        s           [200];           /* generic string                 */
   char       *p           = NULL;          /* strtok current pointer         */
   char       *q           = "/";           /* strtok delimeters              */
   char       *r           = NULL;          /* strtok_r context variable      */
   char        rce         = -10;           /* return code for errors         */
   DIR        *dir         = NULL;          /* directory pointer              */
   /*---(defenses)-----------------------*/
   --rce;     /* too many packages ------*/
   if (npkg >= PKG_MAX) {
      DEBUG_PKGS   printf ("package structure full, SKIPPING\n");
      return rce;
   }
   --rce;     /* null name --------------*/
   if (a_full   == NULL) {
      DEBUG_PKGS   printf ("package name is null, SKIPPING\n");
      return rce;
   }
   --rce;     /* bad name ---------------*/
   found = PKG_find     (a_full);
   if (found < -1) {
      DEBUG_PKGS   printf ("bad name or length, SKIPPING\n");
      return rce;
   }
   DEBUG_PKGS   printf ("%s, ", a_full);
   --rce;     /* already appended -------*/
   if (found >= 0) {
      DEBUG_PKGS   printf ("already exists as %d, done\n", found);
      if (a_source == 'w')   pkgs [found].world  = 'y';
      return found;
   }
   --rce;     /* bad source type --------*/
   if (strchr (valid_src, a_source) == NULL) {
      DEBUG_PKGS   printf ("can't understand source type (%c vs %s), SKIPPING\n", a_source, valid_src);
      return rce;
   }
   len = strlen (a_full);
   --rce;     /* name too long ----------*/
   if (len >= STR_REG) {
      DEBUG_DIRS   printf ("name too long (%d vs. %d)\n", len, STR_REG);
      return rce;
   }
   --rce;     /* name too short ---------*/
   if (len < 10) {
      DEBUG_DIRS   printf ("name too short (%d vs. %d)\n", len, 10);
      return rce;
   }
   /*---(append)-------------------------*/
   if (found == -1)  found = npkg;
   strncpy (pkgs [found].full, a_full, LPFULL);
   strcpy  (s, a_full);
   if (a_source == 'c' || a_source == 'w' || a_source == '+') {
      p = strtok_r  (s, q, &r);
      --rce;     /* ---------------------*/
      if (p == NULL)  {
         DEBUG_PKGS   printf ("can not parse category part, SKIPPING\n");
         return rce;
      }
      strncpy (pkgs [found].cat , p, LPCAT );
      p = strtok_r  (NULL, q, &r);
      --rce;     /* ---------------------*/
      if (p == NULL)  {
         DEBUG_PKGS   printf ("can not parse name part, SKIPPING\n");
         return rce;
      }
      strncpy (pkgs [found].name, p       , LPNAME);
      strncpy (pkgs [found].desc, a_desc  , LPNAME);
   } else {
      strncpy (pkgs [found].cat , "-", LPCAT );
      strncpy (pkgs [found].name, "-", LPNAME);
   }
   pkgs [found].len     = len;
   pkgs [found].source  = a_source;
   /*---(test against real location)-----*/
   if (a_source == 'c' || a_source == 'w' || a_source == '+') {
      sprintf (s, "/usr/portage/%s/%s", pkgs [found].cat, pkgs [found].name);
   } else {
      strcpy  (s, a_full);
   }
   dir = opendir(s);
   --rce;     /* not a real package -----*/
   pkgs [found].portage = 'y';
   if (dir == NULL) {
      dir = opendir (a_full);
      if (dir == NULL) {
         DEBUG_PKGS   printf ("skipping (%s), not portage or local package\n", s);
         pkgs [found].portage = '-';
         /*> return rce;                                                              <*/
      }
   }
   closedir (dir);
   /*---(priority)-----------------------*/
   if (a_source == 'c') {
      if (a_priority == '\0')  pkgs [found].priority = ' ';
      else                     pkgs [found].priority = a_priority;
   }
   /*---(focus)--------------------------*/
   if (  pkgs [found].len == my.focus_len &&
         strcmp (pkgs [found].full, my.focus) == 0) {
      pkgs [found].active = 'y';
   }
   /*---(index)--------------------------*/
   ipkg [found]        = found;
   /*---(point to area)------------------*/
   if (a_source == 'c' && s_narea > 0) {
      pkgs [found].area = s_narea - 1;
   }
   if (a_source == 'w')   pkgs [found].world  = 'y';
   /*---(update)-------------------------*/
   DEBUG_PKGS   printf ("added as %d with source=%c, done\n", found, a_source);
   AREA_addpkg (pkgs [found].area);
   ++npkg;
   /*---(complete)-----------------------*/
   return found;
}

int              /* [------] find a particular package entry -----------------*/
PKG_find           (char *a_name)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* iterator -- package            */
   int         found       = -1;            /* generic intex holder           */
   int         len         = 0;             /* string length                  */
   /*---(defense)------------------------*/
   if (a_name == NULL)      return -2;
   len = strlen (a_name);
   if (len    == 0   )      return -3;
   /*---(locate)-------------------------*/
   for (i = 0; i < npkg; ++i) {
      /*---(filter)----------------------*/
      if (pkgs [i].len                   != len)   continue;
      if (strcmp (pkgs [i].full, a_name) != 0  )   continue;
      /*---(save)------------------------*/
      found = i;
      break;
   }
   /*---(complete)-----------------------*/
   return found;
}

char             /* [------] clear a single package entry --------------------*/
PKG_wipe           (int a_curr)
{
   /*---(database fields)-------------*/
   pkgs [a_curr].active         = my.def_pkg;
   pkgs [a_curr].source         = '-';
   pkgs [a_curr].portage        = '-';
   pkgs [a_curr].world          = '-';
   pkgs [a_curr].full [0]       = '\0';
   pkgs [a_curr].desc [0]       = '\0';
   pkgs [a_curr].area           = -1;
   pkgs [a_curr].priority       = '-';
   pkgs [a_curr].update         = '-';
   /*---(working fields)--------------*/
   pkgs [a_curr].cat  [0]       = '\0';
   pkgs [a_curr].name [0]       = '\0';
   pkgs [a_curr].len            = 0;
   pkgs [a_curr].ncmd           = 0;
   /*---(index)-----------------------*/
   ipkg [a_curr]               = a_curr;
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          linking                             ----===*/
/*====================------------------------------------====================*/
static void      o___LINKING_________________o (void) {;}

char             /* [------] link a command to a package ---------------------*/
PKG_link           (int a_pkg, int a_cmd)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   char        rcc         = 0;             /* return code as char            */
   /*---(header)-------------------------*/
   DEBUG_PKGS   printf ("   linking package/command  : ");
   /*---(defense))-----------------------*/
   rcc = PKG_valid (a_pkg);
   if (rcc < 0)  {
      DEBUG_PKGS    printf ("package not valid, SKIPPING\n");
      return rcc;
   }
   rcc = CMD_valid (a_cmd);
   if (rcc < 0 && rcc != CMD_ATNEXT)  {
      DEBUG_PKGS    printf ("command not valid, SKIPPING\n");
      return rcc;
   }
   --rce;  /*=== command already linked =*/
   if (s_cmds [a_cmd].i_pkg >= 0) {
      DEBUG_PKGS   printf ("command already linked to package (%d), SKIPPING\n", s_cmds [a_cmd].i_pkg);
      return rce;
   }
   /*---(link)---------------------------*/
   s_cmds [a_cmd].i_pkg = a_pkg;
   ++pkgs [a_pkg].ncmd;
   DEBUG_PKGS   printf ("linked %s to %s, done\n", s_cmds [a_cmd].name, pkgs [a_pkg].full);
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] unlink a command from a package -----------------*/
PKG_unlink         (int a_cmd)
{
   DEBUG_PKGS   printf ("   unlinking package/command: ");
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* iterator -- location           */
   int         found       = -1;            /* generic locator                */
   int         len         = 0;             /* generic string length          */
   char        s           [200];           /* generic string                 */
   char       *p           = NULL;
   char       *q           = "/";
   int         x_pkg       = -1;
   char        rcc         = 0;             /* return code as char            */
   /*---(defense))-----------------------*/
   if (a_cmd < 0) {
      DEBUG_PKGS   printf ("aommand index negative, SKIPPING\n");
      return -3;
   }
   if (a_cmd >  ncmd) {
      DEBUG_PKGS   printf ("command index too high, SKIPPING\n");
      return -4;
   }
   x_pkg = s_cmds [a_cmd].i_pkg;
   // location index
   rcc = PKG_valid (x_pkg);
   if (rcc < 0)  {
      DEBUG_PKGS    printf (", SKIPPING\n");
      return rcc;
   }
   /*---(link)---------------------------*/
   s_cmds [a_cmd].i_pkg = -1;
   --pkgs [x_pkg].ncmd;
   DEBUG_PKGS   printf ("unlinked %s from %s, done\n", s_cmds [a_cmd].name, pkgs [x_pkg].full);
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                           reporting                          ----===*/
/*====================------------------------------------====================*/
static void      o___REPORTING_______________o (void) {;}

char             /* [------] display the package inventory -------------------*/
PKG_header         (int a_page, char a_order)
{
   printf ("\n\n");
   printf ("HERMES-DIACTOROS (messenger) integrity assurance for executables and shared libraries\n");
   printf ("package reporting %s\n", (a_order == 's') ? "in original sequence" : "sorted by cat/name");
   printf ("\n");
   /*> printf ("HERMES-DIACTOROS -- ebuild package report, page %3d                                                                                              %4d of %4d slots used\n\n", a_page, npkg, PKG_MAX);   <*/
   printf ("  seq# indx  s p w a  cat                  name                           desc                                       cmd   pri   upd   area           \n");
   printf ("  ---- ----  - - - -  -------------------- ------------------------------ ----------------------------------------   ---   ---   ---   -----------------------------------\n");
   return 0;
}

char             /* [------] display the package inventory -------------------*/
PKG_footer         (void)
{
   printf ("\n");
   printf ("  ---- ----  - - - -  -------------------- ------------------------------ ----------------------------------------   ---   ---   ---   -----------------------------------\n");
   printf ("  source   = where the package comes from, i.e., c=conf file, w=world-ebuild file, +=pre-loaded, #=local, -=unknown\n");
   printf ("  command  = number of actual commands installed/updated by this package\n");
   printf ("  priority = criticality for updates, i.e., T=top, +=watch, other means as possible\n");
   printf ("  updated  = \n");
   return 0;
}

char             /* [------] display the package inventory -------------------*/
PKG_list           (char a_order)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* iterator -- package            */
   int         j           = 0;             /* iterator -- package            */
   int         curr        = 0;             /* current package                */
   int         x_seq       = 0;
   int         x_index     = 0;
   char        s           [200];           /* generic string                 */
   char        t           [200];           /* generic string                 */
   int         x_page      = 1;
   int         x_line      = 1;
   int         x_area      = -1;
   /*---(output)-------------------------*/
   for (i = 0; i < npkg; ++i) {
      switch (a_order) {
      case  's' :
         x_seq    = i;
         for (j = 0; j < npkg; ++j)  if (ipkg[j] == i)  x_index = j;
         break;
      case  'i' :
      default   :
         x_index  = i;
         x_seq    = ipkg [i];
         break;
      }
      curr     = x_seq;
      if (i % 45 == 0) {
         if (i > 0) PKG_footer ();
         PKG_header (x_page, a_order);
         ++x_page;
         x_line = 1;
      }
      if (i %  5 == 0) {
         printf ("\n");
         ++x_line;
      }
      if (pkgs [curr].ncmd < 1)      strcpy  (s, "  -");
      else                           sprintf (s, "%3d", pkgs [curr].ncmd);
      x_area = pkgs [curr].area;
      if (x_area <  0)               sprintf  (t, "%s",     "99.unassigned");
      else                           sprintf  (t, "%02d.%s", x_area, s_areas [x_area].name);
      printf ("  %4d %4d  %c %c %c %c  %-20.20s %-30.30s %-40.40s   %3.3s    %c     %c    %-40.40s\n",
            x_seq, x_index, pkgs [curr].source, pkgs [curr].portage ,
            pkgs [curr].world , pkgs [curr].active,
            pkgs [curr].cat     , pkgs [curr].name    , pkgs [curr].desc    ,
            s                      ,
            pkgs [curr].priority, pkgs [curr].update  ,
            t);
      ++x_line;
   }
   /*---(footer)-------------------------*/
   for (i = x_line; i < 53; ++i)  printf ("\n");
   PKG_footer ();
   printf ("\n");
   printf ("  GRAND TOTAL %d packages registered as installed\n", npkg);
   printf ("\n");
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         gathering                            ----===*/
/*====================------------------------------------====================*/
static void      o___GATHERING_______________o (void) {;}

char             /* [------] identify the population of packages -------------*/
PKG_world          (void)
{
   /*---(locals)-----------+-----------+-*/
   FILE       *fp          = NULL;          /* generic file pointer           */
   char        x_recd      [1000];          /* generic record buffer          */
   int         x_len       = 0;             /* string length                  */
   int         i           = 0;             /* iterator -- record number      */
   /*> char        s          [200];            /+ generic string                 +/   <* 
    *> char       *p           = NULL;                                                 <* 
    *> char       *q           = "/";                                                 <*/
   char        rc          = 0;
   char        rce         = -10;
   /*---(begin)--------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(open world file)----------------*/
   DEBUG_GENTOO  yLOG_info    ("world_file", FILE_WORLD);
   fp = fopen (FILE_WORLD, "r");
   DEBUG_GENTOO  yLOG_point   ("file point", fp);
   --rce;  if (fp == NULL) {
      DEBUG_GENTOO  yLOG_note    ("failed to open file");
      DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   DEBUG_GENTOO  yLOG_note    ("successfully openned");
   while (1) {
      /*---(read)---------------------*/
      fgets(x_recd, 1000, fp);
      if (feof (fp)) break;
      ++i;
      x_len = strlen (x_recd);
      x_recd [--x_len] = '\0';
      DEBUG_GENTOO  yLOG_info    ("line"      , x_recd);
      /*---(filter)-------------------*/
      if (x_recd[0] == '#' ) {
         DEBUG_GENTOO  yLOG_note    ("comment skipping");
         continue;
      }
      if (x_recd[0] == '\0')  {
         DEBUG_GENTOO  yLOG_note    ("emty skipping");
         continue;
      }
      /*---(save)---------------------*/
      DEBUG_GENTOO  yLOG_note    ("accepted");
      PKG_push (x_recd, 'w', ' ', "");
      /*---(done----------------------*/
   }
   /*---(close the file)-----------------*/
   DEBUG_GENTOO  yLOG_note    ("closing world file");
   rc = fclose(fp);
   DEBUG_GENTOO  yLOG_value   ("close rc"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_GENTOO  yLOG_note    ("failed to close file");
      DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   DEBUG_GENTOO  yLOG_note    ("successfully closed world file");
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         reporting                            ----===*/
/*====================------------------------------------====================*/
static void      o___DATABASE________________o (void) {;}

char             /* [------] read packages from database ---------------------*/
PKG_readdb         (void)
{
   /*---(locals)-----------+-----------+-*/
   FILE       *f           = NULL;          /* file pointer                   */
   char        recd        [1000];          /* generic record buffer          */
   int         len         = 0;             /* string length                  */
   char        s           [200];           /* generic string                 */
   char        a           [200];           /* generic string                 */
   char        c           = ' ';           /* generic character              */
   char       *r           = NULL;          /* strtok reference point         */
   int         nread       = 0;             /* number records read            */
   int         nproc       = 0;             /* number records processed       */
   int         rci         = 0;             /* return code as int             */
   char        rcc         = 0;             /* return code as char            */
   int         x_value     = 0;
   char        x_type      [20];
   char        x_ver       [20];
   /*---(haeder)-------------------------*/
   DEBUG_CACHE   printf ("package database read\n");
   /*---(open)---------------------------*/
   DEBUG_CACHE   printf ("   openning input file <<%s>>\n", PKG_DATABASE);
   f = fopen (PKG_DATABASE, "r");
   if (f == NULL) {
      DEBUG_CACHE   printf ("               can not open package file\n");
      return -1;
   }
   DEBUG_CACHE   printf ("   package database open\n");
   /*---(process entries)----------------*/
   DEBUG_CACHE   printf ("   reading entries\n");
   DEBUG_CACHE   printf ("   line seq    eval    len category------------ name---------------- full-------------------------- len    s p u\n");
   while (1) {
      /*---(read)------------------------*/
      fgets(recd, 1000, f);
      if (feof (f)) break;
      /*---(output)----------------------*/
      ++nread;
      DEBUG_CACHE  if (nread % 3 == 1)   printf ("\n");
      DEBUG_CACHE  printf ("   %4d %3d    ", nread, nproc);
      /*---(filter)----------------------*/
      rcc = recd_valid (recd, &len);
      if (rcc < 0)  continue;
      DEBUG_CACHE   printf ("----    %3d ", len);
      r = NULL;
      /*---(type)------------------------*/
      rcc = parse_string  (recd, &r, 1, LCFULL, x_type);
      if (strcmp ("pkg", x_type) != 0) {
         DEBUG_CACHE   printf ("not a command record, SKIPPING\n");
         continue;
      }
      /*---(type)------------------------*/
      rcc = parse_string  (NULL, &r, 1, LCFULL, x_ver);
      if (strcmp ("-B-", x_ver) != 0) {
         DEBUG_CACHE   printf ("version not -B-, SKIPPING\n");
         continue;
      }
      /*---(name)------------------------*/
      rcc = parse_string  (NULL, &r, 5, LCFULL, s);
      if (rcc < 0)   continue;
      /*---(area)------------------------*/
      rcc = parse_string  (NULL, &r, 0, LCFULL, a);
      if (rcc < 0)   continue;
      /*---(source)----------------------*/
      rcc = parse_flag  (NULL, &r, valid_src, &c);
      if (rcc < 0)   continue;
      /*---(append)----------------------*/
      rci = PKG_push (s, c, ' ', "");
      if (rci < 0) {
         DEBUG_CACHE   printf ("can not append %s, type %c, SKIPPING\n", s, c);
         continue;
      }
      DEBUG_CACHE   printf ("%-20.20s %-20.20s %-30.30s %3d    %c ", pkgs [rci].cat, pkgs [rci].name, pkgs [rci].full, pkgs [rci].len, pkgs [rci].source);
      /*---(area)------------------------*/
      strcpy (pkgs [rci].area, a);
      /*---(priority)--------------------*/
      rcc = parse_flag  (NULL, &r, "-+#", &c);
      if (rcc < 0)   continue;
      pkgs [rci].priority = c;
      DEBUG_CACHE   printf ("%c "      , pkgs [rci].priority);
      /*---(command count)---------------*/
      rcc = parse_integer (NULL, &r, 0, 500, &x_value);
      if (rcc < 0)   continue;
      /*---(update)----------------------*/
      rcc = parse_flag  (NULL, &r, "-URB*?", &c);
      if (rcc < 0)   continue;
      pkgs [rci].update   = c;
      DEBUG_CACHE   printf ("%c "      , pkgs [rci].update);
      /*---(done)------------------------*/
      DEBUG_CACHE   printf ("\n");
      ++nproc;
   }
   /*---(wrapup)-------------------------*/
   fclose (f);
   /*---(complete)-----------------------*/
   return 0;
}


char             /* [------] write packages to database ----------------------*/
PKG_writedb        (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* iterator -- package            */
   FILE       *f           = NULL;          /* file pointer - commands        */
   int         curr        = 0;
   /*---(open)---------------------------*/
   DEBUG_CACHE   printf ("\n\npackage database write\n");
   f = fopen (PKG_DATABASE, "w");
   if (f == NULL) {
      printf ("               can not open package file <<%s>>\n", PKG_DATABASE);
      return -1;
   }
   DEBUG_CACHE   printf ("    package database open\n");
   /*---(header)-------------------------*/
   DEBUG_CACHE   printf ("    writing header\n");
   fprintf (f, "# hermes package database written at %ld\n", my.runtime);
   fprintf (f, "#    -A- recreated simple listing to file\n");
   fprintf (f, "#    -B- added record types and versions\n");
   /*---(output)-------------------------*/
   for (i = 0; i < npkg; ++i) {
      if ((i % 45) == 0)   fprintf (f, "\n#type  ver  package/ebuild----------------------------------------------  ---area--------  s  p  ncmd  u \n");
      if ((i %  5) == 0)   fprintf (f, "\n");
      curr = ipkg [i];
      fprintf (f, "pkg    -B-  %-60.60s  %-35.35s  %c  %c  %-4d  %c \n",
            pkgs [curr].full    , s_areas [pkgs [curr].area].name,
            pkgs [curr].source  , pkgs [curr].priority,
            pkgs [curr].ncmd    , pkgs [curr].update);
   }
   /*---(wrapup)-------------------------*/
   fprintf  (f, "\n# end-of-records\n");
   fclose (f);
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char*
PKG_unit           (char *a_question, int a_num)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* loop iterator                  */
   int         m           = 0;             /* maximum count                  */
   int         s           [100];           /* generic string                 */
   /*---(prepare)------------------------*/
   strcpy  (unit_answer, "package unit     : question not understood");
   /*---(defenses)-----------------------*/
   if      (npkg < 1) {
      snprintf (unit_answer, LEN_TEXT, "package empty    : no packages exist");
   }
   else if (a_num < 0) {
      snprintf (unit_answer, LEN_TEXT, "package error    : package ref (%d) is negative", a_num);
   }
   else if (a_num != 0 && a_num >= npkg) {
      snprintf (unit_answer, LEN_TEXT, "package error    : package ref (%d vs %d) is too high", a_num, npkg);
   }
   /*---(package name)-------------------*/
   else if (strncmp (a_question, "package_name"      , 20)      == 0) {
      snprintf (unit_answer, LEN_TEXT, "package name     : %3d, %c, %-.35s", a_num, pkgs [a_num].source, pkgs [a_num].full);
   }
   /*---(package count)------------------*/
   else if (strncmp (a_question, "package_count"     , 20)      == 0) {
      snprintf (unit_answer, LEN_TEXT, "package count    : %d", npkg);
   }
   /*---(last package)-------------------*/
   else if (strncmp (a_question, "package_last"      , 20)      == 0) {
      snprintf (unit_answer, LEN_TEXT, "package last     : (%2d) %c, %-25.25s (%2d)", npkg - 1, pkgs [npkg - 1].source, pkgs [npkg - 1].full, pkgs [npkg - 1].len);
   }
   /*---(location command count)---------*/
   else if (strncmp (a_question, "package_parse"     , 20)      == 0) {
      snprintf (unit_answer, LEN_TEXT, "package parsed   : %-10.10s, %-.25s", pkgs [a_num].cat, pkgs [a_num].name);
   }
   /*---(package links)------------------*/
   else if (strncmp (a_question, "package_ncmd"      , 20)      == 0) {
      snprintf (unit_answer, LEN_TEXT, "package links    : %d", pkgs [a_num].ncmd);
   }
   /*---(location command count)---------*/
   else if (strncmp (a_question, "package_sorted"    , 20)      == 0) {
      strcpy (unit_answer, "package sorted   :");
      m = npkg;
      if (m > 10)   m = 10;
      for (i = 0; i < m; ++i) {
         sprintf (s, " %d", ipkg [i]);
         strcat (unit_answer, s);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}

/*===============================[[ end-code ]]===============================*/
