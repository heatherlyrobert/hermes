#include    "hermes.h"


#define     DIR_PORTAGE    "/var/db/pkg"
#define     FILE_CONTENTS  "/var/lib/hermes/hermes.contents"
#define     LEN_LABEL      20


static FILE       *s_file      = NULL;          /* file pointer                   */
static char        s_dirs      [2000] = "";



char             /*-> open files database ----------------[ ------ [ ------ ]-*/
FILES_dirstr       (void)
{
   strlcpy (s_dirs, "", 2000);
}

char             /*-> open files database ----------------[ ------ [ ------ ]-*/
FILES_db_open      (char a_dir)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          =   0;
   char        rce         = -10;
   char        x_option    [LEN_LABEL];
   /*---(check direction)----------------*/
   --rce;  switch (a_dir) {
   case  'w' : strlcpy (x_option, "w", LEN_LABEL);   break;
   case  'r' : strlcpy (x_option, "r", LEN_LABEL);   break;
   default   : return rce;
   }
   /*---(open for write)-----------------*/
   s_file = fopen (FILE_CONTENTS, x_option);
   --rce;  if (s_file == NULL) {
      return rce;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char             /*-> close files database ---------------[ ------ [ ------ ]-*/
FILES_db_close     (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          =   0;
   char        rce         = -10;
   /*---(open for write)-----------------*/
   rc = fclose (s_file);
   --rce;  if (rc < 0) {
      return rce;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
FILES_contents          (char *a_dir)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          =    0;
   char        rce         =  -10;
   FILE       *x_contents  = NULL;
   /*---(complete)-----------------------*/
   return 0;
}

char
FILES_gather            (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          =   0;
   char        rce         = -10;
   DIR        *x_root      = NULL;          /* directory pointer              */
   tDIRENT    *x_cat       = NULL;          /* directory entry                */
   char        x_catdir    [100];
   int         x_ncat      =    0;          /* count of categories            */
   DIR        *x_packages  = NULL;          /* directory pointer              */
   tDIRENT    *x_pkg       = NULL;          /* directory entry                */
   int         x_npkg      =    0;          /* count of packages              */
   int         x_count     =    0;
   /*---(header)-------------------------*/
   DEBUG_DIRS   yLOG_enter   (__FUNCTION__);
   /*---(open root dir)------------------*/
   DEBUG_DIRS   yLOG_info    ("root"      , DIR_PORTAGE);
   x_root = opendir (DIR_PORTAGE);
   DEBUG_DIRS   yLOG_point   ("x_root"    , x_root);
   --rce;  if (x_root == NULL) {
      closedir (x_root);
      DEBUG_DIRS   yLOG_note    ("does not exist");
      DEBUG_DIRS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DIRS   yLOG_note    ("root dir successfully openned");
   /*---(cycle through categories)-------*/
   while ((x_cat = readdir (x_root)) != NULL) {
      /*---(filter)----------------------*/
      if (x_cat->d_name     == NULL)                 continue;
      if (x_cat->d_name [0] == '.')                  continue;
      /*---(open root dir)------------------*/
      DEBUG_DIRS   yLOG_info    ("category"  , x_cat->d_name);
      printf ("%02d.%s\n", x_ncat, x_cat->d_name);
      sprintf (x_catdir, "%s/%s", DIR_PORTAGE, x_cat->d_name);
      x_packages = opendir (x_catdir);
      DEBUG_DIRS   yLOG_point   ("x_packages", x_packages);
      --rce;  if (x_packages == NULL) {
         closedir (x_packages);
         DEBUG_DIRS   yLOG_note    ("does not exist");
         DEBUG_DIRS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_DIRS   yLOG_note    ("packages dir successfully openned");
      ++x_ncat;
      x_npkg = 0;
      /*---(cycle through categories)-------*/
      while ((x_pkg = readdir (x_packages)) != NULL) {
         /*---(filter)----------------------*/
         if (x_pkg->d_name   == NULL)                   continue;
         if (x_pkg->d_name [0] == '.')                  continue;
         /*---(handle)----------------------*/
         ++x_npkg;
         ++x_count;
         printf ("   %02d.%s\n", x_npkg, x_pkg->d_name);
      }
      closedir (x_packages);
   }
   printf ("read %d packages\n", x_count);
   /*---(close root dir)-----------------*/
   DEBUG_DIRS   yLOG_note    ("closing root dir");
   closedir (x_root);
   /*---(complete)-----------------------*/
   DEBUG_DIRS   yLOG_exit    (__FUNCTION__);
   return 0;
}




