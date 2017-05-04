#include    "hermes.h"


#define     DIR_PORTAGE    "/var/db/pkg"
#define     FILE_CONTENTS  "/var/lib/hermes/hermes.contents"
#define     LEN_LABEL      20


static FILE       *s_file      = NULL;          /* file pointer                   */
static char        s_dirs      [2000] = "";


typedef    struct cFILES  tFILES;
struct cFILES {
   int         loc;
   int         pkg;
   char        cmd         [100];
};
tFILES      s_files     [10000];
int         s_nfile     = 0;


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
FILES_package           (char *a_full, char *a_name, char *a_ver)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         i           =    0;
   int         x_len       =    0;
   /*---(defense)------------------------*/
   --rce;  if (a_full == NULL)  return rce;
   --rce;  if (a_name == NULL)  return rce;
   --rce;  if (a_ver  == NULL)  return rce;
   /*---(find beg of ver)----------------*/
   strlcpy (a_name, a_full, 100);
   x_len = strlen (a_name);
   for (i = 0; i < x_len; ++i) {
      if (a_name [i] != '-')     continue;
      if (strchr ("0123456789", a_name [i + 1]) == NULL)   continue;
      a_name [i] = '\0';
      /*> strcpy (a_ver, a_name [i + 1]);                                             <*/
      return 1;
   }
   return 0;
}

char
FILES_commands          (char *a_path, int a_pkg)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *x_file      = NULL;
   char        x_recd      [2000];
   char       *p           = NULL;          /* strtok_r current pointer       */
   char       *q           = " ";           /* strtok_r delimeters            */
   char       *r           = NULL;          /* strtok_r context variable      */
   int         x_loc       =    0;
   char        x_path      [200];
   char        x_subdir    [200];
   char        x_cmd       [200];
   x_file = fopen (a_path, "r");
   --rce;  if (x_file == NULL) {
      return rce;
   }
   while (1) {
      /*---(read)---------------------*/
      if (NULL == fgets (x_recd, 1000, x_file)) break;
      if (feof (x_file)) break;
      p = strtok_r  (x_recd, q, &r);
      if (strcmp ("obj", p) != 0) continue;
      p = strtok_r  (NULL  , q, &r);
      if (p == NULL)              continue;
      UTIL_parse_full (p, x_path, NULL);
      x_loc = LOC_find_path (x_path);
      if (x_loc < 0)  {
         /*> printf ("      %s, location %s returned %2d, SKIPPING\n", p, x_path, x_loc);   <*/
         continue;
      }
      strlcpy (x_subdir, x_path, 200);
      rc    = LOC_remove_path (x_loc, x_subdir);
      if (rc    < 0)  {
         /*> printf ("      location %s remove path returned %2d, SKIPPING\n", x_cmd, x_loc);   <*/
         continue;
      }
      printf ("      %-50.50s   %-50.50s\n", p, LOC_get_path ());
      CMD_push (p, 'i');
   }
   fclose (x_file);
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
   char        x_pkgdir    [200];
   int         x_npkg      =    0;          /* count of packages              */
   int         x_cpkg      =    0;          /* current package                */
   int         x_count     =    0;
   char        x_name      [100] = "";
   char        x_ver       [100] = "";
   char        s           [200];
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
         FILES_package (x_pkg->d_name, x_name, x_ver);
         sprintf (s, "%s/%s", x_cat->d_name, x_name);
         sprintf (x_pkgdir, "%s/%s/%s", x_catdir, x_pkg->d_name, "CONTENTS");
         PKG_push (s, 'i', ' ', "(base install)");
         x_cpkg = PKG_find (s);
         printf  ("   %02d.%-30.30s   %3d %-50.50s   %-100.100s\n", x_npkg, x_pkg->d_name, x_cpkg, s, x_pkgdir);
         if (x_cpkg < 0) continue;
         FILES_commands  (x_pkgdir, x_cpkg);
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




