/*===============================[[ beg-code ]]===============================*/
#include    "hermes.h"



/*====================------------------------------------====================*/
/*===----                      string handling                         ----===*/
/*====================------------------------------------====================*/
static void      o___STRINGS_________________o (void) {;}

char        str_white   [20] = " \t\n\r";

char*            /* [#-----] clean whitespace from string head ---------------*/
str_htrim          (char *a_cstring)
{
   /*---(locals)-----------+-----------+-*/
   int         i, j;                        /* interator -- string position   */
   int         len         = 0;             /* string length                  */
   /*---(defenses)-----------------------*/
   if (a_cstring == NULL)               return NULL;
   /*---(leading whitespace)-------------*/
   len = strlen(a_cstring);
   for (i = 0; i <= len; ++i) {
      if (strchr (str_white, a_cstring[0]) == NULL) break;
      for (j = 0; j <= len; ++j)
         a_cstring[j] = a_cstring[j + 1];
      --len;
   }
   /*---(complete)-----------------------*/
   return a_cstring;
}

char*            /* [#-----] clean whitespace from string tail ---------------*/
str_ttrim          (char *a_cstring)
{
   /*---(locals)-----------+-----------+-*/
   int         i;                           /* interator -- string position   */
   int         len         = 0;             /* string length                  */
   /*---(defenses)-----------------------*/
   if (a_cstring == NULL)               return NULL;
   /*---(trailing whitespace)------------*/
   len = strlen(a_cstring);
   for (i = len - 1; i >= 0; --i) {
      if (strchr (str_white, a_cstring[i]) == NULL) break;
      a_cstring[i] = '\0';
   }
   /*---(complete)-----------------------*/
   return a_cstring;
}

char*            /* [#-----] clean whitespace from both sides of a string ----*/
str_trim           (char *a_cstring)
{
   /*---(trim)---------------------------*/
   str_htrim (a_cstring);
   str_ttrim (a_cstring);
   /*---(complete)-----------------------*/
   return a_cstring;
}

char             /* [#-----] clean custom whitespace from both sides ---------*/
str_wtrim          (char *a_cstring, char *a_white)
{
   /*---(locals)-----------+-----------+-*/
   char        x_white     [20]        = " /t/n/r";
   /*---(defenses)-----------------------*/
   if (a_white == NULL       )  return -1;     // null string
   if (strlen (a_white) >  19)  return -2;     // too long
   /*---(trim)---------------------------*/
   strcpy (str_white, a_white);
   str_htrim (a_cstring);
   str_ttrim (a_cstring);
   strcpy (str_white, x_white);
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      record testing                          ----===*/
/*====================------------------------------------====================*/
static void      o___RECORDS_________________o (void) {;}

int
recd_valid         (char  *a_recd, int  *a_len)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         l           = 0;             /* string length                  */
   /*---(null pointer)-------------------*/
   --rce;
   if (a_recd == NULL ) {
      DEBUG_CACHE   printf ("skip, null recd pointer, SKIPPING\n");
      return rce;
   }
   /*---(blank line)---------------------*/
   --rce;
   if (a_recd[0] == '\0')  {
      DEBUG_CACHE   printf ("skip, blank line, SKIPPING\n");
      return -2;
   }
   /*---(comment line)-------------------*/
   --rce;
   if (a_recd[0] == '#' ) {
      DEBUG_CACHE   printf ("skip, comment line, SKIPPING\n");
      return rce;
   }
   /*---(space prefixed)-----------------*/
   --rce;
   if (a_recd[0] == ' ')  {
      DEBUG_CACHE   printf ("skip, prefixed with space, SKIPPING\n");
      return rce;
   }
   /*---(clean up)-----------------------*/
   l = strlen (a_recd);
   a_recd [--l] = '\0';
   *a_len = l;
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      database parsing                        ----===*/
/*====================------------------------------------====================*/
static void      o___PARSING_________________o (void) {;}

char
parse_string       (char *a_recd, char **a_place, int a_min, int a_max, char *a_value)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   char       *p           = NULL;
   char       *q           = "";
   int         l           = 0;
   /*---(no placeholder)-----------------*/
   --rce;
   if (a_recd != NULL && *a_place != NULL)   {
      DEBUG_CACHE   printf ("recd not NULL and placeholder has value, SKIPPING\n");
      return rce;
   }
   /*---(no placeholder)-----------------*/
   --rce;
   if (a_recd == NULL && *a_place == NULL)   {
      DEBUG_CACHE   printf ("recd is NULL and placeholder has no value, SKIPPING\n");
      return rce;
   }
   /*---(no string)----------------------*/
   --rce;
   if (a_value == NULL)   {
      DEBUG_CACHE   printf ("string pointer null, SKIPPING\n");
      return rce;
   }
   /*---(parse)--------------------------*/
   p = strtok_r (a_recd, q, a_place);
   --rce;
   if (p        == NULL)   {
      DEBUG_CACHE   printf ("field value null, SKIPPING\n");
      return rce;
   }
   /*---(clean)--------------------------*/
   str_trim (p);
   l = strlen (p);
   /*---(too short)----------------------*/
   --rce;
   if (l <  a_min && p [0] != '-')   {
      DEBUG_CACHE   printf ("field <<%s>> too short %d vs %d, SKIPPING\n", p, l, a_min);
      return rce;
   }
   /*---(too long)-----------------------*/
   --rce;
   if (l >= a_max)   {
      DEBUG_CACHE   printf ("field <<%s>> too long %d vs %d, SKIPPING\n", p, l, a_max);
      return rce;
   }
   /*---(string)-------------------------*/
   strcpy (a_value, p);
   /*---(complete)-----------------------*/
   return 0;
}

char
parse_flag         (char *a_recd, char **a_place, char *a_valid, char *a_value)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   char       *p           = NULL;
   char       *q           = "";
   int         l           = 0;
   /*---(no placeholder)-----------------*/
   --rce;
   if (a_recd != NULL && a_place != NULL)   {
      DEBUG_CACHE   printf ("recd not NULL and placeholder has value, SKIPPING\n");
      return rce;
   }
   /*---(no placeholder)-----------------*/
   --rce;
   if (a_recd == NULL && a_place == NULL)   {
      DEBUG_CACHE   printf ("recd is NULL and placeholder has no value, SKIPPING\n");
      return rce;
   }
   /*---(no string)----------------------*/
   --rce;
   if (a_value  == NULL)   {
      DEBUG_CACHE   printf ("string pointer null, SKIPPING\n");
      return rce;
   }
   /*---(parse)--------------------------*/
   p = strtok_r (a_recd, q, a_place);
   --rce;
   if (p        == NULL)   {
      DEBUG_CACHE   printf ("field value null, SKIPPING\n");
      return rce;
   }
   /*---(clean)--------------------------*/
   str_trim (p);
   l = strlen (p);
   /*---(too short)----------------------*/
   --rce;
   if (l <  1)   {
      DEBUG_CACHE   printf ("field <<%s>> too short %d vs %d, SKIPPING\n", p, l, 1);
      return rce;
   }
   /*---(too long)-----------------------*/
   --rce;
   if (l >  1)   {
      DEBUG_CACHE   printf ("field <<%s>> too long %d vs %d, SKIPPING\n", p, l, 1);
      return rce;
   }
   /*---(too long)-----------------------*/
   --rce;
   if (strchr (a_valid, p[0]) == NULL)   {
      DEBUG_CACHE   printf ("field value %c not in %s, SKIPPING\n", p [0], a_valid);
      return rce;
   }
   /*---(string)-------------------------*/
   *a_value = p [0];
   /*---(complete)-----------------------*/
   return 0;
}

char
parse_integer      (char *a_recd, char **a_place, int a_min, int a_max, int *a_value)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   char       *p           = NULL;
   char       *q           = "";
   int         v           = 0;
   /*---(no placeholder)-----------------*/
   --rce;
   if (a_recd != NULL && *a_place != NULL)   {
      DEBUG_CACHE   printf ("recd not NULL and placeholder has value, SKIPPING\n");
      return rce;
   }
   /*---(no placeholder)-----------------*/
   --rce;
   if (a_recd == NULL && *a_place == NULL)   {
      DEBUG_CACHE   printf ("recd is NULL and placeholder has no value, SKIPPING\n");
      return rce;
   }
   /*---(no string)----------------------*/
   --rce;
   if (a_value == NULL)   {
      DEBUG_CACHE   printf ("string pointer null, SKIPPING\n");
      return rce;
   }
   /*---(parse)--------------------------*/
   p = strtok_r (a_recd, q, a_place);
   --rce;
   if (p        == NULL)   {
      DEBUG_CACHE   printf ("field value null, SKIPPING\n");
      return rce;
   }
   /*---(clean)--------------------------*/
   str_trim (p);
   v = atoi (p);
   /*---(too short)----------------------*/
   --rce;
   if (v <  a_min) {
      DEBUG_CACHE   printf ("value too low %d vs %d, SKIPPING\n", v, a_min);
      return rce;
   }
   /*---(too long)-----------------------*/
   --rce;
   if (a_max > 0 && v >= a_max)   {
      DEBUG_CACHE   printf ("value too high %d vs %d, SKIPPING\n", v, a_max);
      return rce;
   }
   /*---(string)-------------------------*/
   *a_value = v;
   /*---(complete)-----------------------*/
   return 0;
}

char
parse_long         (char *a_recd, char **a_place, long a_min, long a_max, long *a_value)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   char       *p           = NULL;
   char       *q           = "";
   long        v           = 0;
   /*---(no placeholder)-----------------*/
   --rce;
   if (a_recd != NULL && *a_place != NULL)   {
      DEBUG_CACHE   printf ("recd not NULL and placeholder has value, SKIPPING\n");
      return rce;
   }
   /*---(no placeholder)-----------------*/
   --rce;
   if (a_recd == NULL && *a_place == NULL)   {
      DEBUG_CACHE   printf ("recd is NULL and placeholder has no value, SKIPPING\n");
      return rce;
   }
   /*---(no string)----------------------*/
   --rce;
   if (a_value == NULL)   {
      DEBUG_CACHE   printf ("string pointer null, SKIPPING\n");
      return rce;
   }
   /*---(parse)--------------------------*/
   p = strtok_r (a_recd, q, a_place);
   --rce;
   if (p        == NULL)   {
      DEBUG_CACHE   printf ("field value null, SKIPPING\n");
      return rce;
   }
   /*---(clean)--------------------------*/
   str_trim (p);
   v = atol (p);
   /*---(too short)----------------------*/
   --rce;
   if (v <  a_min) {
      DEBUG_CACHE   printf ("value too low %ld vs %ld, SKIPPING\n", v, a_min);
      return rce;
   }
   /*---(too long)-----------------------*/
   --rce;
   if (a_max > 0 && v >= a_max)   {
      DEBUG_CACHE   printf ("value too high %ld vs %ld, SKIPPING\n", v, a_max);
      return rce;
   }
   /*---(string)-------------------------*/
   *a_value = v;
   /*---(complete)-----------------------*/
   return 0;
}

char             /*-> parse full into path/name ----------[ ------ [ ------ ]-*/
UTIL_parse_full    (char *a_full, char *a_path, char *a_name)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;
   char        rc          =   0;
   int         x_len       = 0;             /* generic string length          */
   char        s           [1000];
   char       *p           = NULL;
   /*---(prepare)---------------------*/
   if (a_path != NULL)  strlcpy (a_path, "", 1000);
   if (a_name != NULL)  strlcpy (a_name, "", 1000);
   /*---(defense)---------------------*/
   --rce;  if (a_full == NULL) {
      return rce;
   }
   x_len = strlen (a_full);
   --rce;  if (x_len <= 4) {
      return rce;
   }
   /*---(full)------------------------*/
   strlcpy (s, a_full, 1000);
   p = strrchr (s, '/');
   --rce;  if (p == NULL)  {
      return rce;
   }
   /*---(location)--------------------*/
   *p = '\0';
   rc  = LOC_find_path (s, 's');
   --rce;  if (rc < 0)  {
      return rce;
   }
   /*---(save it)---------------------*/
   if (a_name != NULL)  strlcpy (a_name, p + 1, 1000);
   if (a_path != NULL)  strlcpy (a_path, s    , 1000);
   /*---(complete)-----------------------*/
   return 0;
}



/*===============================[[ end-code ]]===============================*/
