/*===============================[[ beg-code ]]===============================*/
/*
 *
 *   source
 *      ?   unused/empty
 *      -   loaded from hermes.commands
 *      +   gathered from location search
 *      #   temporary working entry
 *
 *
 *   volume expectations : 2000 to 5000 (small dataset)
 *
 *      less than hundred      micro         lookup tables and small sets
 *      hundreds               tiny
 *      thousands              small
 *      tens of thousands      medium
 *      hundreds of thousands  large         population of fresno, ca
 *      millions               huge          population of la or usa
 *      billions               enormous      population of world
 *      trillions              gigantic      freaking nsa database
 *
 *
 *
 *
 *
 *
 *
 */
#include    "hermes.h"

tCMD        s_cmds      [CMD_MAX];       /* main command structure (unsorted) */
int         icmd        [CMD_MAX];       /* index for commands                */
int         ncmd        = 0;             /* count of commands                 */
static char valid_src   [10] = "-+#ig";   /* valid source types                */
/*  command sources
 *     g = gathered by walking locations
 *     i = installed, gentoo package directories /var/db/pkg/...
 *
 *
 *
 *
 */


/*====================------------------------------------====================*/
/*===----                     full table operations                    ----===*/
/*====================------------------------------------====================*/
static void      o___FULLTABLE_______________o (void) {;}

char             /* [------] destroy all command entries ---------------------*/
CMD_purge          (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* iterator -- locations          */
   /*---(header)-------------------------*/
   DEBUG_CMDS   printf ("\n");
   DEBUG_CMDS   printf ("     begin initializing command data structure\n");
   /*---(clear all)----------------------*/
   for (i = 0; i < CMD_MAX; ++i)  {
      CMD_wipe (&s_cmds[i]);
      icmd [i]            = -1;
   }
   /*---(index)-----------------------*/
   ncmd = 0;
   /*---(footer)-------------------------*/
   DEBUG_CMDS   printf ("     done initializing %d elemeets\n", PKG_MAX);
   DEBUG_CMDS   printf ("\n");
   /*---(complete)-----------------------*/
   return 0;
}

char
CMD_gnome_hop      (int a_size, int *a_cur, int *a_comps, int *a_moves, int a_tele)
{
   /*---(locals)-----------+-----------+-*/
   int         x_bot       = *a_cur - a_size;
   int         x_one       =  1;            /* position one                   */
   int         x_two       =  1;            /* position two                   */
   int         rc          = 0;
   int         i           = 0;
   int         x_temp      = 0;
   /*---(defense)------------------------*/
   if (x_bot < 0) return -1;
   /*---(compare)------------------------*/
   if ((*a_comps % 5) == 0)  DEBUG_SORT   printf ("-comps- --moves-- -tele-    size    -one- -seq- ---entry-one---------------------------------    -two- -seq- ---entry-two---------------------------------\n");
   ++(*a_comps);
   x_one = icmd [ x_bot];
   x_two = icmd [*a_cur];
   rc = strcmp (s_cmds [x_one].name, s_cmds [x_two].name);
   DEBUG_SORT   printf("%7d %9d %6d    %4d    %-5d %-5d %-45.45s    %-5d %-5d %-45.45s    %3d ", *a_comps, *a_moves, a_tele, a_size, x_bot, x_one, s_cmds [x_one].name, *a_cur, x_two, s_cmds [x_two].name, rc);
   /*---(too low)------------------------*/
   if (rc <= 0) {
      DEBUG_SORT   printf("good,        right order\n");
      return -2;
   }
   /*---(moves)--------------------------*/
   x_temp = icmd [*a_cur];
   for (i = *a_cur; i > x_bot; --i) {
      /*> DEBUG_SORT   printf(".");                                                   <*/
      icmd [i] = icmd [i - 1];
   }
   icmd [x_bot] = x_temp;
   DEBUG_SORT   printf("swap,        move backward\n");
   /*---(update vars)--------------------*/
   *a_moves += a_size;
   *a_cur    = x_bot;
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] teleporting crack gnome sort --------------------*/
CMD_crack_gnome    (void)
{
   DEBUG_SORT   printf("sorting command records (teleporting crack gnome)...\n");
   /*---(locals)-----------+-----------+-*/
   int         i           =  0;
   /*---(cursors)----------*/
   int         x_gnome     =  1;            /* current position               */
   int         x_tele      = -1;            /* teleportation point            */
   /*---(counters)---------*/
   int         x_comps     =  0;            /* number of comparisons          */
   int         x_moves     =  0;            /* number of moves                */
   /*---(clear index)--------------------*/
   /*> for (i = 0; i < ncmd; ++i)  icmd [i] = i;                                      <*/
   /*---(sort)---------------------------*/
   DEBUG_SORT   printf("   start : %d commands\n", ncmd);
   while (x_gnome < ncmd) {
      /*---(prepare)---------------------*/
      if (x_gnome > x_tele)  x_tele = x_gnome;
      /*---(hopping)---------------------*/
      while (CMD_gnome_hop (5000 , &x_gnome, &x_comps, &x_moves, x_tele) >= 0);
      while (CMD_gnome_hop (1000 , &x_gnome, &x_comps, &x_moves, x_tele) >= 0);
      while (CMD_gnome_hop (500  , &x_gnome, &x_comps, &x_moves, x_tele) >= 0);
      while (CMD_gnome_hop (100  , &x_gnome, &x_comps, &x_moves, x_tele) >= 0);
      while (CMD_gnome_hop (50   , &x_gnome, &x_comps, &x_moves, x_tele) >= 0);
      while (CMD_gnome_hop (10   , &x_gnome, &x_comps, &x_moves, x_tele) >= 0);
      while (CMD_gnome_hop (1    , &x_gnome, &x_comps, &x_moves, x_tele) >= 0);
      /*---(correct, teleport)-----------*/
      x_gnome = x_tele + 1;
      /*---(done)------------------------*/
   }
   /*---(complete)------------------------------*/
   return 0;
}

/*> char             /+ [------] hopping teleporting gnome sort ------------------+/                                                                                                                         <* 
 *> CMD_gnome          (void)                                                                                                                                                                                <* 
 *> {                                                                                                                                                                                                        <* 
 *>    DEBUG_SORT   printf("sorting command records (hopping teleporting gnome)...\n");                                                                                                                      <* 
 *>    /+---(locals)-----------+-----------+-+/                                                                                                                                                              <* 
 *>    /+---(cursors)----------+/                                                                                                                                                                            <* 
 *>    int         i           =  1;            /+ current position               +/                                                                                                                         <* 
 *>    int         x_one       =  1;            /+ position one                   +/                                                                                                                         <* 
 *>    int         x_two       =  1;            /+ position two                   +/                                                                                                                         <* 
 *>    int         x_tele      = -1;            /+ teleportation point            +/                                                                                                                         <* 
 *>    int         x_temp      =  0;            /+ temp storage for moves         +/                                                                                                                         <* 
 *>    /+---(comparing)--------+/                                                                                                                                                                            <* 
 *>    int         rci         =  0;            /+ integer return code            +/                                                                                                                         <* 
 *>    /+---(counters)---------+/                                                                                                                                                                            <* 
 *>    int         x_comps     =  0;            /+ number of comparisons          +/                                                                                                                         <* 
 *>    int         x_moves     =  0;            /+ number of moves                +/                                                                                                                         <* 
 *>    /+---(sort)---------------------------+/                                                                                                                                                              <* 
 *>    DEBUG_SORT   printf("   start : %d commands\n", ncmd);                                                                                                                                                <* 
 *>    while (i < ncmd) {                                                                                                                                                                                    <* 
 *>       if ((x_comps % 5) == 0)  printf ("-comps- -moves- -tele-    -#1- seqn ---entry-one-----------------------------------    -#2- seqn ---entry-two-----------------------------------\n");            <* 
 *>       /+---(prepare)---------------------+/                                                                                                                                                              <* 
 *>       if (i > x_tele)  x_tele = i;                                                                                                                                                                       <* 
 *>       x_one = icmd [i - 1];                                                                                                                                                                              <* 
 *>       x_two = icmd [i    ];                                                                                                                                                                              <* 
 *>       /+---(compare)---------------------+/                                                                                                                                                              <* 
 *>       ++x_comps;                                                                                                                                                                                         <* 
 *>       rci = strcmp (s_cmds [x_one].name, s_cmds [x_two].name);                                                                                                                                           <* 
 *>       DEBUG_SORT   printf("%7d %7d %6d    %-4d %-4d <%-45.45s>    %-4d %-4d <%-45.45s>    %3d ", x_comps, x_moves, x_tele, i - 1, x_one, s_cmds [x_one].name, i    , x_two, s_cmds [x_two].name, rci);   <* 
 *>       /+---(correct, teleport)-----------+/                                                                                                                                                              <* 
 *>       if (rci <= 0) {                                                                                                                                                                                    <* 
 *>          i = x_tele + 1;                                                                                                                                                                                 <* 
 *>          DEBUG_SORT   printf("good,        TELEPORT\n");                                                                                                                                                 <* 
 *>          continue;                                                                                                                                                                                       <* 
 *>       }                                                                                                                                                                                                  <* 
 *>       /+---(swap)------------------------+/                                                                                                                                                              <* 
 *>       DEBUG_SORT   printf("swap         ");                                                                                                                                                              <* 
 *>       ++x_moves;                                                                                                                                                                                         <* 
 *>       x_temp       = icmd [i];                                                                                                                                                                           <* 
 *>       icmd [i]     = icmd [i - 1];                                                                                                                                                                       <* 
 *>       icmd [i - 1] = x_temp;                                                                                                                                                                             <* 
 *>       /+---(check for bottom)------------+/                                                                                                                                                              <* 
 *>       if (i <= 1) {                                                                                                                                                                                      <* 
 *>          DEBUG_SORT   printf("TELEPORT (bounce off bottom)\n");                                                                                                                                          <* 
 *>          i = x_tele + 1;                                                                                                                                                                                 <* 
 *>          continue;                                                                                                                                                                                       <* 
 *>       }                                                                                                                                                                                                  <* 
 *>       /+---(prepare for next)------------+/                                                                                                                                                              <* 
 *>       DEBUG_SORT   printf("move backward\n");                                                                                                                                                            <* 
 *>       --i;                                                                                                                                                                                               <* 
 *>       /+---(done)------------------------+/                                                                                                                                                              <* 
 *>    }                                                                                                                                                                                                     <* 
 *>    long      n2     = (long)   ncmd * ncmd;                                                                                                                                                              <* 
 *>    float     ratio  = ((float) x_moves / n2) * 100;                                                                                                                                                      <* 
 *>    float     action = ((float) x_moves / x_comps) * 100;                                                                                                                                                 <* 
 *>    DEBUG_SORT   printf("   moves : %d items, %d comp(s), %d move(s)\n", ncmd, x_comps, x_moves);                                                                                                         <* 
 *>    DEBUG_SORT   printf("   stats : N2 = %ld, action (move/N2) = %2.0f%%, efficiency (move/comp) = %2.0f%%\n", n2, ratio, action);                                                                        <* 
 *>    DEBUG_SORT   printf("\n");                                                                                                                                                                            <* 
 *>    /+---(complete)------------------------------+/                                                                                                                                                       <* 
 *>    return 0;                                                                                                                                                                                             <* 
 *> }                                                                                                                                                                                                        <*/

/*> char             /+ [------] teleporting gnome sort --------------------------+/                                                                              <* 
 *> CMD_index          (void)                                                                                                                                     <* 
 *> {                                                                                                                                                             <* 
 *>    DEBUG_SORT   printf("sorting command records (indexed teleporting gnome)...\n");                                                                           <* 
 *>    /+---(locals)-----------+-----------+-+/                                                                                                                   <* 
 *>    /+---(cursors)----------+/                                                                                                                                 <* 
 *>    int         i           =  1;            /+ current position               +/                                                                              <* 
 *>    int         x_one       =  1;            /+ position one                   +/                                                                              <* 
 *>    int         x_two       =  1;            /+ position two                   +/                                                                              <* 
 *>    int         x_tele      = -1;            /+ teleportation point            +/                                                                              <* 
 *>    int         x_temp      =  0;            /+ temp storage for moves         +/                                                                              <* 
 *>    /+---(comparing)--------+/                                                                                                                                 <* 
 *>    char        s           [200];                                                                                                                             <* 
 *>    char        t           [200];                                                                                                                             <* 
 *>    int         rci         =  0;            /+ integer return code            +/                                                                              <* 
 *>    /+---(counters)---------+/                                                                                                                                 <* 
 *>    int         comps       =  0;            /+ number of comparisons          +/                                                                              <* 
 *>    int         moves       =  0;            /+ number of moves                +/                                                                              <* 
 *>    /+---(sort)---------------------------+/                                                                                                                   <* 
 *>    DEBUG_SORT   printf("   start : %d commands\n", ncmd);                                                                                                     <* 
 *>    while (i < ncmd) {                                                                                                                                         <* 
 *>       x_one = icmd [i - 1];                                                                                                                                   <* 
 *>       x_two = icmd [i    ];                                                                                                                                   <* 
 *>       /+---(header)----------------------+/                                                                                                                   <* 
 *>       DEBUG_SORT   printf("   %-4d  %-4d  <%-45.45s>    %-4d  %-4d  <%-45.45s>    ", i - 1, x_one, s_cmds [x_one].name, i    , x_two, s_cmds [x_two].name);   <* 
 *>       /+---(compare)---------------------+/                                                                                                                   <* 
 *>       ++comps;                                                                                                                                                <* 
 *>       sprintf (s, "%-45.45s", s_cmds [x_one].name);                                                                                                           <* 
 *>       sprintf (t, "%-45.45s", s_cmds [x_two].name);                                                                                                           <* 
 *>       rci = strcmp (s, t);                                                                                                                                    <* 
 *>       DEBUG_SORT   printf("%2d    ", rci);                                                                                                                    <* 
 *>       /+---(correct order)---------------+/                                                                                                                   <* 
 *>       if ((i == 0) || (rci <= 0)) {                                                                                                                           <* 
 *>          if (x_tele >= 0)  { i = x_tele; x_tele = -1; }                                                                                                       <* 
 *>          else            ++i;                                                                                                                                 <* 
 *>          DEBUG_SORT   printf("good    %-4d    %-4d    SKIPPING\n");                                                                                           <* 
 *>          continue;                                                                                                                                            <* 
 *>       }                                                                                                                                                       <* 
 *>       /+---(swap)------------------------+/                                                                                                                   <* 
 *>       DEBUG_SORT   printf("swap    ");                                                                                                                        <* 
 *>       ++moves;                                                                                                                                                <* 
 *>       x_temp       = icmd [i];                                                                                                                                <* 
 *>       icmd [i]     = icmd [i - 1];                                                                                                                            <* 
 *>       icmd [i - 1] = x_temp;                                                                                                                                  <* 
 *>       /+---(teleport)--------------------+/                                                                                                                   <* 
 *>       if (x_tele < 0)  x_tele = i;              /+ only update on first move      +/                                                                          <* 
 *>       if (i > 1) --i;                                                                                                                                         <* 
 *>       DEBUG_SORT   printf("%-4d    %-4d    swapped\n");                                                                                                       <* 
 *>       /+---(done)------------------------+/                                                                                                                   <* 
 *>    }                                                                                                                                                          <* 
 *>    long      n2     = (long)   ncmd * ncmd;                                                                                                                   <* 
 *>    float     ratio  = ((float) moves / n2) * 100;                                                                                                             <* 
 *>    float     action = ((float) moves / comps) * 100;                                                                                                          <* 
 *>    DEBUG_SORT   printf("   moves : %d items, %d comp(s), %d move(s)\n", ncmd, comps, moves);                                                                  <* 
 *>    DEBUG_SORT   printf("   stats : N2 = %ld, action (move/N2) = %2.0f%%, efficiency (move/comp) = %2.0f%%\n", n2, ratio, action);                             <* 
 *>    DEBUG_SORT   printf("\n");                                                                                                                                 <* 
 *>    /+---(complete)------------------------------+/                                                                                                            <* 
 *>    return 0;                                                                                                                                                  <* 
 *> }                                                                                                                                                             <*/



/*====================------------------------------------====================*/
/*===----                    single entry updates                      ----===*/
/*====================------------------------------------====================*/
static void      o___UPDATES_________________o (void) {;}

char             /*-> check file name to standards -------[ ------ [ ------ ]-*/
CMD_checkname      (char *a_name)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         x_len       = 0;             /* generic string length          */
   int         x_curr      = -1;            /* generic locator                */
   /*---(header)-------------------------*/
   DEBUG_CMDS   yLOG_senter  (__FUNCTION__);
   /*---(check for room)-----------------*/
   DEBUG_CMDS   yLOG_sint    (ncmd);
   --rce;  if (ncmd >= CMD_MAX) {
      DEBUG_CMDS   yLOG_snote   ("no room in command structure");
      DEBUG_CMDS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for null)-----------------*/
   DEBUG_CMDS   yLOG_spoint  (a_name);
   --rce;  if (a_name   == NULL) {
      DEBUG_CMDS   yLOG_snote   ("name can not be null");
      DEBUG_CMDS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check length)-------------------*/
   x_len = strlen (a_name);
   DEBUG_CMDS   yLOG_sint    (x_len);
   --rce;  if (x_len >= LCFULL) {
      DEBUG_CMDS   yLOG_snote   ("name too long");
      DEBUG_CMDS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_len <  5) {
      DEBUG_CMDS   yLOG_snote   ("name too short");
      DEBUG_CMDS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check existing)-----------------*/
   x_curr = CMD_find     (a_name);
   DEBUG_CMDS   yLOG_sint    (x_curr);
   --rce;  if (x_curr < -1) {
      DEBUG_CMDS   yLOG_snote   ("find failed");
      DEBUG_CMDS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CMDS   printf ("%s, ", a_name);
   --rce;  if (x_curr >= 0)  {
      DEBUG_CMDS   yLOG_snote   ("already exists");
      DEBUG_CMDS   yLOG_sexitr  (__FUNCTION__, rce);
      return x_curr;
   }
   /*---(complete)------------------------------*/
   DEBUG_CMDS   yLOG_sexit   (__FUNCTION__);
   return 0;
}

int              /* [------] add a new command to the list -------------------*/
CMD_push           (char *a_name, char a_src)
{
   /*---(locals)-----------+-----------+-*/
   int         curr        = -1;            /* generic locator                */
   int         x_len       = 0;             /* generic string length          */
   char        s           [200];           /* generic string                 */
   char       *p           = NULL;          /* strtok current pointer         */
   FILE       *f           = NULL;          /* file pointer                   */
   char        rce         = -10;           /* return code for errors         */
   char        rc          =   0;           /* generic return code            */
   int         rci         = 0;             /* return code as integer         */
   /*---(header)-------------------------*/
   DEBUG_CMDS   yLOG_enter   (__FUNCTION__);
   /*---(name defense)-------------------*/
   rc = CMD_checkname (a_name);
   DEBUG_CMDS   yLOG_value   ("checkname" , rc);
   --rce;  if (rc <  0) {
      DEBUG_CMDS   yLOG_note    ("check name failed");
      DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(source defense)-----------------*/
   DEBUG_CMDS   yLOG_char    ("a_src"     , a_src);
   DEBUG_CMDS   yLOG_info    ("valid"     , valid_src);
   --rce;  if (strchr (valid_src, a_src) == NULL) {
      DEBUG_CMDS   yLOG_note    ("source not valid");
      DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(test against real file)---------*/
   strcpy  (s, a_name);
   f = fopen (s, "rb");
   --rce;     /* not a real file)--------*/
   if (f == NULL) {
      DEBUG_CMDS   printf ("skipping, not a real object\n");
      return rce;
   }
   fclose (f);
   /*---(append)-------------------------*/
   curr = ncmd;
   /*---(full)---------------------------*/
   strncpy (s_cmds [curr].full, a_name, LCFULL);
   s_cmds [curr].flen = strlen (s_cmds [curr].full);
   /*---(name)---------------------------*/
   strcpy  (s, a_name);
   p = strrchr (s, '/');
   --rce;     /* no location ------------*/
   if (p == NULL)  {
      DEBUG_CACHE   printf ("location not found in %s, SKIPPING\n", s);
      return rce;
   }
   strcpy (s_cmds [curr].name, p + 1);
   s_cmds [curr].len  = strlen (s_cmds [curr].name);
   *p = '\0';
   /*---(location)--------------------*/
   rci = LOC_find_path (s, 'a');
   --rce;     /* bad location -----------*/
   if (rci < 0)  {
      DEBUG_CACHE   printf ("location %s not found, SKIPPING\n", p);
      return rce;
   }
   LOC_link (rci, curr);
   /*---(source)-------------------------*/
   s_cmds [curr].source   = a_src;
   /*---(focus)--------------------------*/
   if (  s_cmds [curr].len == my.focus_len &&
         strcmp (s_cmds [curr].name, my.focus) == 0) {
      s_cmds [curr].active = 'y';
   }
   /*---(index)--------------------------*/
   icmd [curr]         = curr;
   /*---(update)-------------------------*/
   DEBUG_CMDS   printf ("added as %d, done\n", curr);
   ++ncmd;
   /*---(complete)-----------------------*/
   return curr;
}

char             /* [------] assign a sub-dir to a command -------------------*/
CMD_subdir         (int a_curr, char *a_subdir)
{
   if (a_subdir == NULL)  return -1;
   strlcpy (s_cmds [a_curr].subdir, a_subdir, 200);
   return 0;
}

/*> int              /+ [------] save the command name ---------------------------+/   <* 
 *> CMD_append         (                                                               <* 
 *>       int         a_num,                    /+ command index number           +/   <* 
 *>       int         a_loc,                    /+ location index number          +/   <* 
 *>       char       *a_name)                   /+ command name string            +/   <* 
 *> {                                                                                  <* 
 *>    /+---(locals)-----------+-----------+-+/                                        <* 
 *>    char        s           [200];           /+ generic string                 +/   <* 
 *>    int         rcc         = 0;             /+ return code as character       +/   <* 
 *>    int         rci         = 0;             /+ return code as integer         +/   <* 
 *>    int         len         = 0;             /+ generic string length          +/   <* 
 *>    /+---(defense)------------------------+/                                        <* 
 *>    if (a_num   < 0        )   return -101;                                         <* 
 *>    if (a_num   > ncmd     )   return -102;                                         <* 
 *>    if (a_loc   < 0        )   return -103;                                         <* 
 *>    if (a_loc   > nloc     )   return -104;                                         <* 
 *>    if (a_name == NULL     )   return -105;                                         <* 
 *>    /+---(save name)----------------------+/                                        <* 
 *>    len = strlen (a_name);                                                          <* 
 *>    s_cmds [a_num].len        = len;                                                <* 
 *>    if (len >= LCNAME)  {                                                           <* 
 *>       s_cmds [a_num].toolong = '*';                                                <* 
 *>       rcc = -1;                                                                    <* 
 *>    }                                                                               <* 
 *>    strncpy (s_cmds [a_num].name, a_name, LCNAME);                                  <* 
 *>    /+---(save full)----------------------+/                                        <* 
 *>    snprintf (s, 200, "%s/%s", LOC_path (), a_name);                             <* 
 *>    len = strlen (s);                                                               <* 
 *>    s_cmds [a_num].flen       = len;                                                <* 
 *>    if (len >= LCFULL)  {                                                           <* 
 *>       s_cmds [a_num].ftoolong = '*';                                               <* 
 *>       rcc = -2;                                                                    <* 
 *>    }                                                                               <* 
 *>    strncpy (s_cmds [a_num].full, s     , LCFULL);                                  <* 
 *>    /+---(complete)-----------------------+/                                        <* 
 *>    return rcc;                                                                     <* 
 *> }                                                                                  <*/

int              /* [------] find a particular command entry -----------------*/
CMD_find           (char *a_full)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* iterator -- package            */
   int         found       = -1;            /* generic intex holder           */
   int         len         = 0;             /* string length                  */
   char        rce         = -10;           /* return code for errors         */
   /*---(defenses)-----------------------*/
   --rce;  /*=== name null ==============*/
   if (a_full == NULL)      return rce;
   len = strlen (a_full);
   --rce;  /*=== name empty =============*/
   if (len    <= 0   )      return rce;
   /*---(locate)-------------------------*/
   for (i = 0; i < ncmd; ++i) {
      /*---(filter)----------------------*/
      if (s_cmds [i].flen     != len                   )   continue;
      if (s_cmds [i].full [0] != a_full [0]            )   continue;
      if (strchr (valid_src, s_cmds [i].source) == NULL)   continue;
      if (strcmp (s_cmds [i].full, a_full) != 0        )   continue;
      /*---(save)------------------------*/
      found = i;
      break;
   }
   /*---(complete)-----------------------*/
   return found;
}

char             /* [------] clear a single command entry --------------------*/
CMD_wipe           (tCMD *a_cmd)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   /*---(defenses)-----------------------*/
   --rce;  if (a_cmd == NULL) {
      DEBUG_CMDS   printf ("command structure NULL, SKIPPING\n");
      return rce;
   }
   /*---(database fields)-------------*/
   a_cmd->active      = my.def_cmd;
   a_cmd->source      = '?';
   a_cmd->full [0]    = '\0';
   a_cmd->lastchg     =  0;
   /*---(characteristics)-------------*/
   a_cmd->ftype       = '?';
   a_cmd->filetime    =  0;
   a_cmd->uid         =  0;
   a_cmd->suid        = '-';
   a_cmd->gid         =  0;
   a_cmd->sgid        = '-';
   a_cmd->mode   [0]  = '\0';
   a_cmd->size        =  0;
   /*---(contents)--------------------*/
   a_cmd->bytes       =  0;
   a_cmd->smiss       = '-';
   a_cmd->hash   [0]  = '\0';
   a_cmd->sym_name [0]= '\0';
   a_cmd->sym_note    = '-';
   /*---(linking)---------------------*/
   a_cmd->i_loc       = -1;
   a_cmd->i_pkg       = -1;
   /*---(working)---------------------*/
   a_cmd->subdir [0]  = '\0';
   a_cmd->name   [0]  = '\0';
   a_cmd->concern     = '-';
   a_cmd->toolong     = '-';
   a_cmd->len         =  0;
   a_cmd->flen        =  0;
   a_cmd->ftoolong    = '-';
   /*---(complete)--------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      helper functions                        ----===*/
/*====================------------------------------------====================*/
static void      o___HELPERS_________________o (void) {;}

char             /* [------] validate a command index ------------------------*/
CMD_valid          (int a_cmd)
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
   if (a_cmd <  0) {
      /*> DEBUG_CMDS    printf ("command index (%d) negative", a_cmd);                <*/
      return CMD_NEGATIVE;
   }
   if (a_cmd >= CMD_MAX)  {
      /*> DEBUG_CMDS    printf ("command index (%d vs %d) over max", a_cmd, CMD_MAX);   <*/
      return CMD_OVERMAX;
   }
   if (a_cmd == ncmd)  {
      /*> DEBUG_CMDS    printf ("command index (%d == %d) at next" , a_cmd, ncmd);    <*/
      return CMD_ATNEXT;
   }
   if (a_cmd >  ncmd)  {
      /*> DEBUG_CMDS    printf ("command index (%d vs %d) too high", a_cmd, ncmd);    <*/
      return CMD_TOOHIGH;
   }
   if (ncmd >= CMD_MAX) {
      /*> DEBUG_CMDS    printf ("command structure full");                            <*/
      return CMD_FULL;
   }
   /*---(complete)-----------------------*/
   return 0;
}

/*> char             /+ [------] gather command file statistics ------------------+/              <* 
 *> CMD_stat           (int a_curr, tCMD *a_cmd)                                                  <* 
 *> {                                                                                             <* 
 *>    /+---(locals)-----------+-----------+-+/                                                   <* 
 *>    tSTAT       st;                          /+ file stats                     +/              <* 
 *>    char        c           = ' ';           /+ generic char                   +/              <* 
 *>    char        s           [200];           /+ generic string                 +/              <* 
 *>    char        rce         = -100;          /+ return code for errors         +/              <* 
 *>    char        rcc         = 0;             /+ return code as character       +/              <* 
 *>    int         rci         = 0;             /+ return code as integer         +/              <* 
 *>    /+---(defenses)-----------------------+/                                                   <* 
 *>    /+=========== index is invalid =======+/                                                   <* 
 *>    rcc = CMD_valid (a_cmd);                                                                   <* 
 *>    if (rcc < 0)  {                                                                            <* 
 *>       if (rcc != CMD_ATNEXT) {                                                                <* 
 *>          DEBUG_CMDS    printf (", SKIPPING\n");                                           <* 
 *>          return rcc;                                                                          <* 
 *>       }                                                                                       <* 
 *>       DEBUG_CMDS    printf (", perfect\n");                                               <* 
 *>    }                                                                                          <* 
 *>    --rce;  /+=== name is null ===========+/                                                   <* 
 *>    if (s_cmds [a_cmd].full == NULL) {                                                        <* 
 *>       DEBUG_CMDS   printf ("command index (%d) name is null, SKIPPING\n", a_cmd);         <* 
 *>       return rce;                                                                             <* 
 *>    }                                                                                          <* 
 *>    --rce;  /+=== name is empty ==========+/                                                   <* 
 *>    if (s_cmds [a_cmd].full [0] == '\0') {                                                    <* 
 *>       DEBUG_CMDS   printf ("command index (%d) name is empty, SKIPPING\n", a_cmd);        <* 
 *>       return rce;                                                                             <* 
 *>    }                                                                                          <* 
 *>    --rce;  /+=== file does not exist ====+/                                                   <* 
 *>    rci = lstat (s_cmds [a_cmd].full, &st);                                                   <* 
 *>    if (rci < 0) {                                                                             <* 
 *>       DEBUG_CMDS   printf ("can not stat command file (%s)\n", s_cmds [a_cmd].full);     <* 
 *>       return rce;                                                                             <* 
 *>    }                                                                                          <* 
 *>    /+---(uid and gid)--------------------+/                                                   <* 
 *>    s_cmds [a_cmd].uid = st.st_uid;                                                           <* 
 *>    if (st.st_mode & S_ISUID)   s_cmds [a_cmd].suid = '*';                                    <* 
 *>    s_cmds [a_cmd].gid = st.st_gid;                                                           <* 
 *>    if (st.st_mode & S_ISGID)   s_cmds [a_cmd].sgid = '*';                                    <* 
 *>    /+---(type)---------------------------+/                                                   <* 
 *>    if      (S_ISDIR (st.st_mode))  c = 'd';                                                   <* 
 *>    else if (S_ISCHR (st.st_mode))  c = 'c';                                                   <* 
 *>    else if (S_ISBLK (st.st_mode))  c = 'b';                                                   <* 
 *>    else if (S_ISFIFO(st.st_mode))  c = 'f';                                                   <* 
 *>    else if (S_ISSOCK(st.st_mode))  c = 's';                                                   <* 
 *>    else if (S_ISREG (st.st_mode))  c = '-';                                                   <* 
 *>    else if (S_ISLNK (st.st_mode))  c = 'l';                                                   <* 
 *>    else                            c = '?';                                                   <* 
 *>    s_cmds [a_cmd].ftype = c;                                                                 <* 
 *>    /+---(execute)------------------------+/                                                   <* 
 *>    --rce;  /+=== not executable =========+/                                                   <* 
 *>    if   ((! (st.st_mode & S_IXUSR))  &&                                                       <* 
 *>          (! (st.st_mode & S_IXGRP))  &&                                                       <* 
 *>          (! (st.st_mode & S_IXOTH))) {                                                        <* 
 *>       DEBUG_CMDS   printf ("command file (%s) not executable\n", s_cmds [a_cmd].full);   <* 
 *>       return rce;                                                                             <* 
 *>    }                                                                                          <* 
 *>    /+---(mode)---------------------------+/                                                   <* 
 *>    sprintf (s, "%-10.10o", st.st_mode);                                                       <* 
 *>    strncpy (s_cmds [a_cmd].mode, s + 7, LCMODE);                                             <* 
 *>    /+---(timestamp)----------------------+/                                                   <* 
 *>    s_cmds [a_cmd].filetime   = st.st_mtime;                                                  <* 
 *>    /+---(size)---------------------------+/                                                   <* 
 *>    s_cmds [a_cmd].size       = st.st_size;                                                   <* 
 *>    /+---(complete)------------------------+/                                                  <* 
 *>    return 0;                                                                                  <* 
 *> }                                                                                             <*/

char             /* [------] gather command file statistics ------------------*/
CMD_stat           (tCMD *a_cmd)
{
   /*---(locals)-----------+-----------+-*/
   tSTAT       st;                          /* file stats                     */
   char        c           = ' ';           /* generic char                   */
   char        s           [200];           /* generic string                 */
   char        rce         = -100;          /* return code for errors         */
   char        rcc         = 0;             /* return code as character       */
   int         rci         = 0;             /* return code as integer         */
   /*---(header)-------------------------*/
   DEBUG_CMDS   yLOG_enter   (__FUNCTION__);
   DEBUG_CMDS   yLOG_point   ("a_cmd"     , a_cmd);
   /*---(defense : null command)---------*/
   --rce; if (a_cmd == NULL) {
      DEBUG_CMDS   yLOG_note    ("called with null pointer, exiting");
      DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(defense : null name)------------*/
   --rce; if (a_cmd->full == NULL) {
      DEBUG_CMDS   yLOG_note    ("called with null command name, exiting");
      DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   DEBUG_CMDS   yLOG_info    ("full_name" , a_cmd->full);
   /*---(defense : empty name)-----------*/
   --rce; if (strlen (a_cmd->full) <= 0) {
      DEBUG_CMDS   yLOG_note    ("called with empty command name, exiting");
      DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(get the file information)-------*/
   rci = lstat (a_cmd->full, &st);
   DEBUG_CMDS   yLOG_value   ("lstat_rc"  , rci);
   /*---(defense : real file)------------*/
   --rce; if (rci < 0) {
      DEBUG_CMDS   yLOG_note    ("lstat can not find file, exiting");
      DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(uid and gid)--------------------*/
   a_cmd->uid = st.st_uid;
   if (st.st_mode & S_ISUID)   a_cmd->suid = '*';
   a_cmd->gid = st.st_gid;
   if (st.st_mode & S_ISGID)   a_cmd->sgid = '*';
   /*---(type)---------------------------*/
   if      (S_ISDIR (st.st_mode))  c = 'd';
   else if (S_ISCHR (st.st_mode))  c = 'c';
   else if (S_ISBLK (st.st_mode))  c = 'b';
   else if (S_ISFIFO(st.st_mode))  c = 'f';
   else if (S_ISSOCK(st.st_mode))  c = 's';
   else if (S_ISREG (st.st_mode))  c = '-';
   else if (S_ISLNK (st.st_mode))  c = 'l';
   else                            c = '?';
   a_cmd->ftype = c;
   DEBUG_CMDS   yLOG_value   ("file_type" , a_cmd->ftype);
   /*---(defense : not executable)-------*/
   --rce; if   ((! (st.st_mode & S_IXUSR))  &&
         (! (st.st_mode & S_IXGRP))  &&
         (! (st.st_mode & S_IXOTH))) {
      DEBUG_CMDS   yLOG_note    ("no executable flag set on file");
      DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(mode)---------------------------*/
   sprintf (s, "%-10.10o", st.st_mode);
   strncpy (a_cmd->mode, s + 7, LCMODE);
   /*---(timestamp)----------------------*/
   a_cmd->filetime   = st.st_mtime;
   DEBUG_CMDS   yLOG_value   ("timestamp" , a_cmd->filetime);
   /*---(size)---------------------------*/
   a_cmd->size       = st.st_size;
   DEBUG_CMDS   yLOG_value   ("size"      , a_cmd->size);
   /*---(complete)------------------------*/
   DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
   return 0;
}

/*> char             /+ [------] calculate the command file hash -----------------+/                 <* 
 *> CMD_hash           (int   a_cmd)                                                                 <* 
 *> {                                                                                                <* 
 *>    /+---(locals)-----------+-----------+-+/                                                      <* 
 *>    char        rce         = -10;           /+ return code for errors         +/                 <* 
 *>    int         rci         = 0;             /+ return code as int             +/                 <* 
 *>    int         rcc         = 0;             /+ return code as char            +/                 <* 
 *>    FILE       *f           = NULL;          /+ file pointer                   +/                 <* 
 *>    SHA_CTX     ctx;                                                                              <* 
 *>    int         fsize       = 0;                                                                  <* 
 *>    uchar       buf         [2000];                                                               <* 
 *>    uchar       md          [2000];                                                               <* 
 *>    int         k           = 0;             /+ iterator -- hash segments      +/                 <* 
 *>    char        s           [200];           /+ generic string                 +/                 <* 
 *>    /+---(defenses)-----------------------+/                                                      <* 
 *>    /+=========== index is invalid =======+/                                                      <* 
 *>    rcc = CMD_valid (a_cmd);                                                                      <* 
 *>    if (rcc < 0)  {                                                                               <* 
 *>       if (rcc != CMD_ATNEXT) {                                                                   <* 
 *>          DEBUG_CMDS    printf (", SKIPPING\n");                                                  <* 
 *>          return rcc;                                                                             <* 
 *>       }                                                                                          <* 
 *>       DEBUG_CMDS    printf (", perfect\n");                                                      <* 
 *>    }                                                                                             <* 
 *>    --rce;  /+=== name is null ===========+/                                                      <* 
 *>    if (s_cmds [a_cmd].full == NULL) {                                                              <* 
 *>       DEBUG_CMDS   printf ("command index (%d) name is null, SKIPPING\n", a_cmd);                <* 
 *>       return rce;                                                                                <* 
 *>    }                                                                                             <* 
 *>    --rce;  /+=== name is empty ==========+/                                                      <* 
 *>    if (s_cmds [a_cmd].full [0] == '\0') {                                                          <* 
 *>       DEBUG_CMDS   printf ("command index (%d) name is empty, SKIPPING\n", a_cmd);               <* 
 *>       return rce;                                                                                <* 
 *>    }                                                                                             <* 
 *>    --rce;  /+=== file type not regular ==+/                                                      <* 
 *>    if (strchr ("-l", s_cmds [a_cmd].ftype) == 0) {                                                 <* 
 *>       DEBUG_CMDS   printf ("command index (%d) not regular file, SKIPPING\n", a_cmd);            <* 
 *>       return rce;                                                                                <* 
 *>    }                                                                                             <* 
 *>    --rce;  /+=== file does not exist ====+/                                                      <* 
 *>    f = fopen (s_cmds [a_cmd].full, "rb");                                                          <* 
 *>    if (f == NULL) {                                                                              <* 
 *>       DEBUG_CMDS   printf ("can not open command file (%s)\n", s_cmds [a_cmd].full);               <* 
 *>       return rce;                                                                                <* 
 *>    }                                                                                             <* 
 *>    /+---(initialize)---------------------+/                                                      <* 
 *>    strcpy (s_cmds [a_cmd].hash, "-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- ");   <* 
 *>    s_cmds [a_cmd].bytes = 0;                                                                       <* 
 *>    /+---(start hash)---------------------+/                                                      <* 
 *>    --rce;  /+=== hash not possible ======+/                                                      <* 
 *>    rcc = SHA1_Init (&ctx);                                                                       <* 
 *>    if (rcc != 1) {                                                                               <* 
 *>       DEBUG_CMDS   printf ("can not start SHA1\n");                                              <* 
 *>       return rce;                                                                                <* 
 *>    }                                                                                             <* 
 *>    /+---(process hash)-------------------+/                                                      <* 
 *>    --rce;  /+=== can not continue hash ==+/                                                      <* 
 *>    while (1) {                                                                                   <* 
 *>       rcc = fread (buf, 1, sizeof (buf), f);                                                     <* 
 *>       if (rcc <  0) {                                                                            <* 
 *>          DEBUG_CMDS   printf ("command file read failure\n");                                    <* 
 *>          fclose (f);                                                                             <* 
 *>          return rce;                                                                             <* 
 *>       }                                                                                          <* 
 *>       fsize += rcc;                                                                              <* 
 *>       if (rcc == 0) {                                                                            <* 
 *>          break;                                                                                  <* 
 *>       }                                                                                          <* 
 *>       rcc = SHA1_Update (&ctx, buf, rcc);                                                        <* 
 *>       if (rcc != 1) {                                                                            <* 
 *>          DEBUG_CMDS   printf ("can not update SHA1\n");                                          <* 
*>          fclose (f);                                                                             <* 
*>          return rce - 1;                                                                         <* 
*>       }                                                                                          <* 
*>    }                                                                                             <* 
*>    /+---(close)--------------------------+/                                                      <* 
*>    fclose (f);                                                                                   <* 
*>    /+---(finalize hash)------------------+/                                                      <* 
*>    --rce;  /+=== can not finalize hash ==+/                                                      <* 
*>    rcc = SHA1_Final (md, &ctx);                                                                  <* 
*>    if (rcc != 1) {                                                                               <* 
   *>       DEBUG_CMDS   printf ("can not finalize SHA1\n");                                           <* 
      *>       return rce;                                                                                <* 
      *>    }                                                                                             <* 
      *>    strcpy (s_cmds [a_cmd].hash, "");                                                               <* 
      *>    for (k = 0; k < 20; ++k) {                                                                    <* 
         *>       sprintf (s, "%02x ", md [k]);                                                              <* 
            *>       strncat (s_cmds [a_cmd].hash, s, LCHASH);                                                    <* 
            *>    }                                                                                             <* 
            *>    /+---(sizes)--------------------------+/                                                      <* 
            *>    s_cmds [a_cmd].bytes  = fsize;                                                                  <* 
            *>    /+---(complete)-----------------------+/                                                      <* 
            *>    return 0;                                                                                     <* 
            *> }                                                                                                <*/

char             /* [------] calculate the command file hash -----------------*/
CMD_hash           (tCMD *a_cmd)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rci         = 0;             /* return code as int             */
   int         rcc         = 0;             /* return code as char            */
   FILE       *f           = NULL;          /* file pointer                   */
   SHA_CTX     ctx;
   int         fsize       = 0;
   uchar       buf         [2000];
   uchar       md          [2000];
   int         k           = 0;             /* iterator -- hash segments      */
   char        s           [200];           /* generic string                 */
   /*---(header)-------------------------*/
   DEBUG_CMDS   yLOG_enter   (__FUNCTION__);
   DEBUG_CMDS   yLOG_point   ("a_cmd"     , a_cmd);
   /*---(defense : null command)---------*/
   --rce; if (a_cmd == NULL) {
      DEBUG_CMDS   yLOG_note    ("called with null pointer, exiting");
      DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(defense : null name)------------*/
   --rce; if (a_cmd->full == NULL) {
      DEBUG_CMDS   yLOG_note    ("called with null command name, exiting");
      DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   DEBUG_CMDS   yLOG_info    ("full_name" , a_cmd->full);
   /*---(defense : empty name)-----------*/
   --rce; if (strlen (a_cmd->full) <= 0) {
      DEBUG_CMDS   yLOG_note    ("called with empty command name, exiting");
      DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(defense : file type)------------*/
   --rce;  if (strchr ("-l", a_cmd->ftype) == 0) {
      DEBUG_CMDS   yLOG_note    ("file type not regular or symlink");
      DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(open the file for reading)------*/
   f = fopen (a_cmd->full, "rb");
   /*---(defense : real file)------------*/
   --rce;  if (f == NULL) {
      DEBUG_CMDS   yLOG_note    ("can not open the file for reading");
      DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(initialize)---------------------*/
   strcpy (a_cmd->hash, "-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- ");
   a_cmd->bytes = 0;
   /*---(start hash)---------------------*/
   --rce;  /*=== hash not possible ======*/
   rcc = SHA1_Init (&ctx);
   if (rcc != 1) {
      DEBUG_CMDS   printf ("can not start SHA1\n");
      return rce;
   }
   /*---(process hash)-------------------*/
   --rce;  /*=== can not continue hash ==*/
   while (1) {
      rcc = fread (buf, 1, sizeof (buf), f);
      if (rcc <  0) {
         DEBUG_CMDS   printf ("command file read failure\n");
         fclose (f);
         return rce;
      }
      fsize += rcc;
      if (rcc == 0) {
         break;
      }
      rcc = SHA1_Update (&ctx, buf, rcc);
      if (rcc != 1) {
         DEBUG_CMDS   printf ("can not update SHA1\n");
         fclose (f);
         return rce - 1;
      }
   }
   /*---(close)--------------------------*/
   fclose (f);
   /*---(finalize hash)------------------*/
   --rce;  /*=== can not finalize hash ==*/
   rcc = SHA1_Final (md, &ctx);
   if (rcc != 1) {
      DEBUG_CMDS   printf ("can not finalize SHA1\n");
      return rce;
   }
   strcpy (a_cmd->hash, "");
   for (k = 0; k < 20; ++k) {
      sprintf (s, "%02x ", md [k]);
      strncat (a_cmd->hash, s, LCHASH);
   }
   /*---(sizes)--------------------------*/
   a_cmd->bytes  = fsize;
   /*---(complete)-----------------------*/
   DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char             /* [------] check the quality of a command name -------------*/
CMD_chars          (tCMD *a_cmd)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* iterator -- character          */
   int         len         = 0;             /* generic string length          */
   char        valid       []          = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_.";
   char        extra       []          = "-";
   char        rcc         = 0;
   char        rce         = -10;           /* return code for errors         */
   /*---(header)-------------------------*/
   DEBUG_CMDS   yLOG_senter  (__FUNCTION__);
   DEBUG_CMDS   yLOG_spoint  (a_cmd);
   /*---(defense : null command)---------*/
   --rce; if (a_cmd == NULL) {
      DEBUG_CMDS   yLOG_snote   ("called with null pointer, exiting");
      DEBUG_CMDS   yLOG_sexit   (__FUNCTION__);
      return rce;
   }
   /*---(prepare)------------------------*/
   len = a_cmd->len;
   /*---(cycle characters)---------------*/
   for (i = 0; i < len; ++i) {
      /*---(test basic)------------------*/
      if (strchr (valid, a_cmd->name [i]) != NULL)  continue;
      /*---(test extra)------------------*/
      if (strchr (extra, a_cmd->name [i]) != NULL) {
         a_cmd->concern = '+';
         /*> rcc = -3;                                                                <*/
         continue;
      }
      /*---(othre is bad)----------------*/
      a_cmd->concern = '#';
      /*> rcc = -4;                                                                   <*/
      break;
   }  /*---(done)------------------------*/
   DEBUG_CMDS   yLOG_snote   ("concern");
   DEBUG_CMDS   yLOG_schar   (a_cmd->concern);
   /*---(complete)-----------------------*/
   DEBUG_CMDS   yLOG_sexit   (__FUNCTION__);
   return rcc;
}



/*====================------------------------------------====================*/
/*===----                        reporsting                            ----===*/
/*====================------------------------------------====================*/
static void      o___REPORTING_______________o (void) {;}

char             /* [------] show list header --------------------------------*/
CMD_header         (int  a_page, int  a_loc, char a_order)
{
   char        s           [500];           /* generic string                 */
   printf  ("\n\n");
   sprintf (s, "%-150.150s %42.42spage %3d", "HERMES-DIACTOROS (messenger) integrity assurance for executables and shared libraries", " ", a_page);
   printf  ("%s\n", s);
   sprintf (s, "executable reporting %-129.129s %50.50s", (a_order == 's') ? "in original sequence" : "sorted by location/name", " ");
   printf  ("%s\n", s);
   printf  ("%s\n", LOC_curr_path ());
   printf  ("\n");
   /*> sprintf (s, "HERMES-DIACTOROS -- command executable report, page %3d, location %2d, %s ==========================================================================================================================================================================================================================================================================================================================================================================================================================", a_page, a_loc, locs [a_loc].path );   <*/
   /*> printf  ("%-273.273s\n\n", s);                                                 <*/
   printf  ("  seqno index  s a  name                   len   t filetime   uid    gid    ugo m size      bytes     sha1 hash                                                     package   location\n");
   printf  ("  ----- -----  - -  - -------------------- - --- - ---------- - ---- - ---- --- - --------- --------- -----------------------------------------------------------  ---------  ---------\n");
   return 0;
}

char             /* [------] show list footer --------------------------------*/
CMD_footer         (int  a_page, int  a_lines)
{
   int         i           = 0;             /* iterator -- package            */
   if (a_page == 1)  return 0;
   for (i = a_lines; i <= (9 * 6); ++i)   printf ("\n");
   /*> printf  ("  ---- ----  - -  - -------------------- - --- ----------------------------------- - --- - ---------- - ---- - ---- --- - --------- --------- ----------------------------------------------------------- ---- --- ---------------------------------------------\n");   <*/
   printf  ("  ----- -----  - -  - -------------------- - --- - ---------- - ---- - ---- --- - --------- --------- -----------------------------------------------------------  ---------  ---------\n");
   printf  ("             - database    - only good chars      - good                                          - reg file   - norm - norm     - size match                     - unchecked        \n");
   printf  ("             + new entry   + extended chars       + long name                                     l symlink    * suid * sgid     # size diff                      w world file       \n");
   printf  ("             # conflict    # bad chars                                                                                                                            + non-world ebuild \n");
   printf  ("                                                                                                                                                                                     \n");
   printf  ("                                                                                                                                                                                     \n");
   return 0;
}

char             /* [------] display a single command entry ------------------*/
CMD_show           (int a_seq, int a_index, int a_num, tCMD *a_cmd)
{
   /*---(locals)-----------+-----------+-*/
   char        r           [500];           /* generic string                 */
   char        s           [500];           /* generic string                 */
   char        t           [500];           /* generic string                 */
   char        p           [500];           /* generic string                 */
   char        l           [500];           /* generic string                 */
   /*---(name formatting)----------*/
   sprintf (s, "%-40.40s", a_cmd->name);
   if (a_cmd->len  > 40)   s [39] = '>';
   sprintf (t, "%-35.35s", a_cmd->full);
   if (a_cmd->flen > 35)   t [34] = '>';
   if (a_cmd->filetime <= time (NULL))   sprintf (r, "%-10d", a_cmd->filetime);
   else                                  strcpy  (r, "(bad-time)");
   if (a_cmd->i_pkg >= 0)                sprintf (p, "pkg%04d", a_cmd->i_pkg);
   else                                  strcpy  (p, "pkg----");
   if (a_cmd->i_loc >= 0)                sprintf (l, "loc%04d", a_cmd->i_loc);
   else                                  strcpy  (l, "loc----");
   /*---(output line)--------------*/
   /*---(output line)--------------*/
   printf ("  %5d %5d  %c %c  %c %-40.40s %c %3d %c %-10.10s %c %4d %c %4d %-3.3s %c %9d %9d %-60.60s %c %-100.100s  [%-7.7s]  [%-7.7s]\n" ,
         a_seq           , a_index        , a_cmd->source  , a_cmd->active  , a_cmd->concern ,
         s               , a_cmd->toolong , a_cmd->len     ,
         a_cmd->ftype    ,
         r               ,
         a_cmd->suid     , a_cmd->uid     , a_cmd->sgid    , a_cmd->gid     , a_cmd->mode    ,
         a_cmd->smiss    , a_cmd->size    , a_cmd->bytes   , a_cmd->hash    ,
         a_cmd->sym_note , a_cmd->sym_name,
         p               , l              );
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] output a sorted list ----------------------------*/
CMD_list           (char a_order)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* iterator -- package            */
   int         j           = 0;             /* iterator -- locations          */
   int         k           = 0;             /* iterator -- locations          */
   int         curr        = 0;
   int         x_npage     = 0;             /* page count                     */
   int         count       = 0;             /* record count                   */
   int         lines       = 0;             /* line count                     */
   int         x_loc       = 1;
   int         x_seq       = 0;
   int         x_index     = 0;
   /*---(output)-------------------------*/
   if (a_order != 'a') x_loc = LOC_count ();
   for (j = 0; j < x_loc; ++j) {
      /*---(prepare)---------------------*/
      count = 0;
      lines = 0;
      LOC_curs_index (j);
      /*---(cycle commands)--------------*/
      for (i = 0; i < ncmd; ++i) {
         switch (a_order) {
         case  's' :
            x_seq    = i;
            for (k = 0; k < ncmd; ++k)  if (icmd[k] == i)  x_index = k;
            break;
         case  'i' :
         case  'a' :
         default   :
            x_index  = i;
            x_seq    = icmd [i];
            break;
         }
         curr     = x_seq;
         /*---(filter for location)------*/
         if (a_order != 'a') { 
            if (s_cmds [curr].i_loc != j)  continue;
         }
         /*---(filter for empty/unused)--*/
         if (strchr (valid_src, s_cmds [curr].source) == NULL)   continue;
         /*---(check for page break)-----*/
         if ((lines % (9 * 6)) == 0) {
            ++x_npage;
            if (count > 0)  CMD_footer (x_npage, lines);
            lines = 0;
            CMD_header (x_npage, j, a_order);
         }
         /*---(line grouping)------------*/
         if ((count % 5) == 0) {
            printf ("\n");
            ++lines;
         }
         /*---(name formatting)----------*/
         CMD_show (x_seq, x_index, curr, s_cmds + curr);
         /*---(done)---------------------*/
         ++count;
         ++lines;
      }
      /*---(check for empty)-------------*/
      if (count == 0) {
         CMD_header (x_npage, j, a_order);
         printf ("\n");
         printf ("  no commands identified\n");
         count = lines += 2;
      }
      CMD_footer  (x_npage, lines);
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
CMD_dump           (void)
{
   int i = 0;
   int k = 0;
   int x_index;
   printf ("HERMES command dump, %d total commands\n", ncmd);
   for (i = 0; i < ncmd; ++i) {
      for (k = 0; k < ncmd; ++k)  if (icmd[k] == i)  x_index = k;
      CMD_show (i, x_index, i, s_cmds + i);
   }
   return 0;
}


/*====================------------------------------------====================*/
/*===----                          gathering                           ----===*/
/*====================------------------------------------====================*/
static void      o___GATHERING_______________o (void) {;}

char
CMD_compare        (tCMD *a_found, tCMD *a_exist)
{
   /*---(header)-------------------------*/
   DEBUG_CMDS   yLOG_senter  (__FUNCTION__);
   /*---(timestamp)----------------------*/
   if (a_found->filetime  != a_exist->filetime)  DEBUG_CMDS   yLOG_snote   ("time miss");
   /*---(premissions)--------------------*/
   if (a_found->ftype != a_exist->ftype)  DEBUG_CMDS   yLOG_snote   ("ftype miss");
   if (a_found->suid  != a_exist->suid )  DEBUG_CMDS   yLOG_snote   ("suid miss");
   if (a_found->uid   != a_exist->uid  )  DEBUG_CMDS   yLOG_snote   ("uid miss");
   if (a_found->sgid  != a_exist->sgid )  DEBUG_CMDS   yLOG_snote   ("sgid miss");
   if (a_found->gid   != a_exist->gid  )  DEBUG_CMDS   yLOG_snote   ("gid miss");
   if (strcmp (a_found->mode, a_exist->mode) != 0)  DEBUG_CMDS   yLOG_snote   ("mode miss");
   /*---(contents)-----------------------*/
   if (a_found->size  != a_exist->size )  DEBUG_CMDS   yLOG_snote   ("size miss");
   if (a_found->bytes != a_exist->bytes)  DEBUG_CMDS   yLOG_snote   ("bytes miss");
   if (strcmp (a_found->hash, a_exist->hash) != 0)  DEBUG_CMDS   yLOG_snote   ("hash miss");
   /*---(footer)-------------------------*/
   DEBUG_CMDS   yLOG_sexit   (__FUNCTION__);
   /*---(complete)-----------------------*/
   return 0;
}

char
CMD_analyze        (int a_count, char *a_path, char *a_name, tCMD *a_cmd, char a_source, char a_check)
{
   /*---(locals)-----------+-----------+-*/
   int         x_curr      = 0;                  /* index of existing entry   */
   char        rce         = -10;                /* return code for errors    */
   char        rc          = 0;
   /*---(header)-------------------------*/
   DEBUG_CMDS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (a_path == NULL) {
      DEBUG_CMDS   yLOG_note    ("a_path is NULL");
      DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   --rce;  if (a_name == NULL) {
      DEBUG_CMDS   yLOG_note    ("a_name is NULL");
      DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(prepare)------------------------*/
   CMD_wipe (a_cmd);
   /*---(create names)-------------------*/
   strncpy (a_cmd->name, a_name, LCNAME);
   DEBUG_CMDS   yLOG_info    ("name"      , a_cmd->name);
   a_cmd->len  = strlen (a_name);
   --rce;  if (a_cmd->len >= LCNAME) {
      DEBUG_CMDS   yLOG_note    ("a_name too long");
      DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   snprintf (a_cmd->full, LCFULL, "%s/%s", a_path, a_name);
   DEBUG_CMDS   yLOG_info    ("full"      , a_cmd->full);
   a_cmd->flen = strlen (a_cmd->full);
   --rce;  if ((a_cmd->len + strlen (a_path) + 1) >= LCFULL) {
      DEBUG_CMDS   yLOG_note    ("full name too long");
      DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(check name quality)-------------*/
   rc = CMD_chars (a_cmd);
   if (rc < 0) {
      DEBUG_CMDS   yLOG_note    ("characters in name failed");
      DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(stats)--------------------*/
   rc = CMD_stat  (a_cmd);
   if (rc < 0)  {
      DEBUG_CMDS   yLOG_note    ("getting statistics failed");
      DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(contents)-----------------*/
   rc = CMD_hash  (a_cmd);
   if (rc < 0)  {
      DEBUG_CMDS   yLOG_note    ("getting hash failed");
      DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(size)---------------------*/
   if (a_cmd->size != a_cmd->bytes)  a_cmd->smiss = '#';
   /*---(final touches)------------*/
   a_cmd->i_loc  = LOC_find_path (a_path, 'a');
   if (a_cmd->i_loc < 0) {
      DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
      return a_cmd->i_loc;
   }
   /*> ++locs [a_cmd->i_loc].ncmd;                                                    <*/
   LOC_add_cmd    (a_cmd->i_loc, a_cmd->bytes);
   DEBUG_CMDS   yLOG_value   ("loc_num"   , a_cmd->i_loc);
   a_cmd->source = a_source; 
   DEBUG_CMDS   yLOG_char    ("source"    , a_cmd->source);
   /*---(report)-------------------*/
   DEBUG_CMDS   CMD_show (a_count, 0, 0, a_cmd);
   /*---(handle checking)----------*/
   if (a_check == 'y') {
      x_curr = CMD_find (a_cmd->full);
      if (x_curr < 0) {
         DEBUG_CMDS   yLOG_note    ("new entry, can not check");
      } else {
         DEBUG_CMDS   yLOG_note    ("existing, will check");
         CMD_compare (a_cmd, s_cmds + x_curr);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char             /* [------] identify the population of commands -------------*/
CMD_gather         (char a_check)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* iterator -- locations          */
   DIR        *dir         = NULL;          /* directory pointer              */
   tDIRENT    *den         = NULL;          /* directory entry                */
   int         rcc         = 0;             /* generic return code            */
   int         x_total     = 0;
   char        x_path      [200];
   char        s           [200];
   int         rci         = 0;
   char        rc          = 0;
   tCMD        x_cmd;                            /* holder for results        */
   /*---(header)-------------------------*/
   DEBUG_CMDS   yLOG_enter   (__FUNCTION__);
   SHOW_GATHER  printf ("HERMES-DIACTOROS -- gather process reporting... focus on %s\n", my.focus);
   /*---(locations)----------------------*/
   for (i = 0; i < LOC_count (); ++i) {
      LOC_curs_index (i);
      strlcpy (x_path, LOC_curr_path (), 200);
      DEBUG_CMDS   yLOG_info    ("loc"       , x_path);
      /*---(check location filter)----*/
      if (my.focus_type == 'l') {
         if (strlen (x_path) != my.focus_len) {
            DEBUG_CMDS   yLOG_note    ("loc filter on, length wrong, skipping");
            continue;
         }
         if (strcmp (x_path, my.focus) != 0) {
            DEBUG_CMDS   yLOG_note    ("loc filter on, name wrong, skipping");
            continue;
         }
         DEBUG_CMDS   yLOG_note    ("loc filter on and matched");
      }
      /*---(open directory)--------------*/
      dir = opendir (x_path);
      if (dir == NULL) {
         DEBUG_CMDS   yLOG_note    ("could not open the location, next loc");
         closedir (dir);
         continue;
      }
      DEBUG_CMDS   yLOG_note    ("location open");
      /*---(cycle through the entries)---*/
      while ((den = readdir(dir)) != NULL) {
         if (den->d_name   == NULL)                   continue;
         DEBUG_CMDS   yLOG_info    ("entry"     , den->d_name);
         /*---(filter)-------------------*/
         if (den->d_type == DT_DIR) {
            DEBUG_CMDS   yLOG_note    ("directory, skipping");
            continue;
         }
         /*---(check command filter)-----*/
         if (my.focus_type == 'c') {
            if (strlen (den->d_name) != my.focus_len) {
               DEBUG_CMDS   yLOG_note    ("cmd filter on, length wrong, skipping");
               continue;
            }
            if (strcmp (den->d_name, my.focus) != 0) {
               DEBUG_CMDS   yLOG_note    ("cmd filter on, name wrong, skipping");
               continue;
            }
            DEBUG_CMDS   yLOG_note    ("cmd filter on and matched");
         }
         /*---(check for existing)-------*/
         snprintf (s, 200, "%s/%s", x_path, den->d_name);
         rci = CMD_find (s);
         /*---(check package filter)-----*/
         if (my.focus_type == 'p') {
            if (rci < 0) {
               DEBUG_CMDS   yLOG_note    ("pkg filter on, new command, skipping");
               continue;
            }
            if (strlen (pkgs [s_cmds [rci].i_pkg].full) != my.focus_len) {
               DEBUG_CMDS   yLOG_note    ("pkg filter on, length wrong, skipping");
               continue;
            }
            if (strcmp (pkgs [s_cmds [rci].i_pkg].full, my.focus) != 0) {
               DEBUG_CMDS   yLOG_note    ("pkg filter on, name wrong, skipping");
               continue;
            }
            DEBUG_CMDS   yLOG_note    ("pkg filter on and matched");
         }
         /*---(display)------------------*/
         ++x_total;
         SHOW_GATHER  printf ("   %4d %-60.60s", x_total, s);
         /*---(existing wo/check)--------*/
         if (rci >=  0 && a_check != 'y') {
            SHOW_GATHER  printf ("found, no check requested\n");
            DEBUG_CMDS   yLOG_note    ("command already exists, checking turned off");
         }
         /*---(existing w/check)---------*/
         else if (rci >=  0) {
            SHOW_GATHER  printf ("found, check requested\n");
            DEBUG_CMDS   yLOG_note    ("command already exists, checking on");
            CMD_analyze (x_total, x_path, den->d_name, &x_cmd, 'g', 'y');
         }
         /*---(new command)--------------*/
         else {
            SHOW_GATHER  printf ("new command\n");
            DEBUG_CMDS   yLOG_note    ("new command");
            DEBUG_CMDS   yLOG_point   ("pointer"   , s_cmds + ncmd);
            DEBUG_CMDS   yLOG_info    ("name"      , (s_cmds + ncmd)->name);
            rc = CMD_analyze (x_total, x_path, den->d_name, s_cmds + ncmd, 'g',  '-');
            DEBUG_CMDS   yLOG_info    ("name"      , (s_cmds + ncmd)->name);
            DEBUG_CMDS   yLOG_value   ("rc"        , rc);
            DEBUG_CMDS   yLOG_value   ("ncmd"      , ncmd);
            if (rc < 0)  continue;
            icmd [ncmd] = ncmd;
            ++ncmd;
         }
         /*---(done)---------------------*/
      }
      closedir (dir);
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   SHOW_GATHER  printf ("   ---complete---------------------");
   DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
   return 0;
}

int
CMD_files          (char *a_path, char *a_name)
{
   char  rc = 0;
   rc = CMD_analyze (0, a_path, a_name, s_cmds + ncmd, 'i', '-');
   if (rc < 0) return -1; 
   icmd [ncmd] = ncmd;
   ++ncmd;
   return ncmd - 1;
}

char
CMD_pkgref         (int a_cmd, int a_pkg)
{
   s_cmds [a_cmd].i_pkg = a_pkg;
   PKG_cmd_add (a_pkg);
   return 0;
}

char             /* [------] match commands to world ebuilds -----------------*/
CMD_world          (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* iterator -- package            */
   int         j           = 0;             /* iterator -- record             */
   int         k           = 0;             /* iterator -- location           */
   char        cmd         [500];           /* generic system () command      */
   FILE       *fp          = NULL;          /* generic file pointer           */
   char        recd        [1000];          /* generic record buffer          */
   char        x_path      [200];
   int         len         = 0;             /* string length                  */
   int         found       = 0;
   /*---(header)-------------------------*/
   DEBUG_CMDS   printf ("\n");
   DEBUG_CMDS   printf ("MATRIX MATCHING\n");
   DEBUG_CMDS   printf ("\n");
   /*---(cycle packages)-----------------*/
   system ("rm -f /tmp/hermes.txt");
   for (i = 0; i < npkg; ++i) {
      /*---(header)----------------------*/
      DEBUG_CMDS   printf ("      %03d of %03d, %-45.45s   ", i, npkg, pkgs [i].name);
      /*---(get commands)----------------*/
      sprintf (cmd, "equery --no-color files %s > /tmp/hermes.txt", pkgs [i].name);
      system  (cmd);
      /*---(open)------------------------*/
      fp = fopen ("/tmp/hermes.txt", "r");
      if (fp == NULL) {
         DEBUG_CMDS   printf ("\n");
         DEBUG_CMDS   printf ("          can not open hermes package file, SKIPPING\n");
         DEBUG_CMDS   printf ("\n");
         fclose (fp);
         continue;
      }
      j = 0;
      while (1) {
         /*---(read)---------------------*/
         fgets(recd, 1000, fp);
         if (feof (fp)) break;
         ++j;
         recd [strlen (recd) - 1] = '\0';
         /*---(filter)-------------------*/
         if (recd[0] == '#' )  continue;
         if (recd[0] == '\0')  continue;
         /*> printf ("          %4d   %-45.45s", j, recd);                            <*/
         /*---(match to location)--------*/
         found = -1;
         for (k = 0; k < LOC_count (); ++k) {
            LOC_curs_index (k);
            strlcpy (x_path, LOC_curr_path (), 200);
            if (strcmp (x_path, recd)  != 0)   continue;
            found = k;
         }
         if (found < 0)  {
            DEBUG_CMDS   printf (".");
            /*> printf (", can not be matched to an executable location, SKIPPING\n");   <*/
            continue;
         }
         /*---(find command)-------------*/
         len = strlen (recd);
         found = -1;
         for (k = 0; k < ncmd; ++k) {
            if (s_cmds [k].flen                != len)  continue;
            if (strcmp (s_cmds [k].full, recd) != 0  )  continue;
            if (s_cmds [k].i_pkg >= 0 && my.matchall != 'y') {
               found = -2;
               break;
            }
            s_cmds [k].i_pkg = i;
            found = k;
            /*> printf (", %d (%s)", found, s_cmds [k].full);                        <*/
         }
         if (found == -1) {
            DEBUG_CMDS   printf ("x");
            /*> printf (", installation package cound not be found, SKIPPING\n");     <*/
            continue;
         }
         if (found == -2) {
            DEBUG_CMDS   printf ("f");
            /*> printf (", installation package already assigned, SKIPPING\n");     <*/
            continue;
         }
         DEBUG_CMDS   printf ("F");
         ++pkgs [i].ncmd;
         /*> printf ("\n");                                                           <*/
         /*---(done----------------------*/
      }
      fclose(fp);
      DEBUG_CMDS   printf ("\n");
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
CMD_package        (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* iterator -- package            */
   int         j           = 0;             /* iterator -- record             */
   int         k           = 0;             /* iterator -- location           */
   char        cmd         [500];           /* generic system () command      */
   FILE       *fp          = NULL;          /* generic file pointer           */
   char        recd        [1000];          /* generic record buffer          */
   int         len         = 0;             /* string length                  */
   int         found       = 0;
   /*---(header)-------------------------*/
   DEBUG_CMDS   printf ("\n");
   DEBUG_CMDS   printf ("FIND MISSING PACKAGES, likely part of base distribution\n");
   DEBUG_CMDS   printf ("\n");
   /*---(cycle packages)-----------------*/
   system ("rm -f /tmp/hermes.txt");
   for (i = 0; i < ncmd; ++i) {
      /*---(prefix)----------------------*/
      DEBUG_CMDS   printf ("      %03d of %03d, %-45.45s      ", i, ncmd, s_cmds [i].full);
      /*---(filter)----------------------*/
      if (s_cmds [i].i_pkg >= 0) {
         DEBUG_CMDS   printf ("      %-4d = (%c) %-45.45s      ", s_cmds [i].i_pkg, pkgs [s_cmds [i].i_pkg].source, pkgs [s_cmds [i].i_pkg].name);
         if (pkgs [s_cmds [i].i_pkg].source == 'w') {
            DEBUG_CMDS   printf ("assigned to world ebulid, done\n");
            continue;
         }
         if (pkgs [s_cmds [i].i_pkg].source == '#') {
            DEBUG_CMDS   printf ("assigned to local package, done\n");
            continue;
         }
         if (pkgs [s_cmds [i].i_pkg].source == '+' && my.packageall != 'y') {
            DEBUG_CMDS   printf ("assigned to non-world ebulid and no force, done\n");
            continue;
         }
         DEBUG_CMDS   printf ("force      ");
      } else {
         DEBUG_CMDS   printf ("empty      ");
      }
      /*---(get commands)----------------*/
      sprintf (cmd, "equery --no-color belongs --early-out --name-only %s > /tmp/hermes.txt", s_cmds [i].full);
      system  (cmd);
      /*---(open)------------------------*/
      fp = fopen ("/tmp/hermes.txt", "r");
      if (fp == NULL) {
         DEBUG_CMDS   printf ("can not open hermes package file, SKIPPING\n");
         fclose (fp);
         continue;
      }
      j = 0;
      while (1) {
         /*---(read)---------------------*/
         fgets(recd, 1000, fp);
         if (feof (fp)) {
            DEBUG_CMDS   printf ("no package found, SKIPPING\n");
            break;
         }
         ++j;
         recd [strlen (recd) - 1] = '\0';
         /*---(filter)-------------------*/
         if (recd[0] == '#' )  continue;
         if (recd[0] == '\0')  continue;
         if (recd[0] == ' ' )  continue;
         found = PKG_find (recd);
         if (found == -1) {
            found = PKG_push (recd, '+', ' ', "");
            DEBUG_CMDS   printf ("++++  %-4d = %-45.45s", found, recd);
         } else {
            DEBUG_CMDS   printf ("   +  %-4d = %-45.45s", found, recd);
         }
         DEBUG_CMDS   printf ("\n");
         DEBUG_CMDS   printf ("      ");
         PKG_unlink (i);
         DEBUG_CMDS   printf ("      ");
         PKG_link   (found, i);
         /*---(done----------------------*/
         break;
      }
      fclose (fp);
   }
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                           database                           ----===*/
/*====================------------------------------------====================*/
static void      o___DATABASE________________o (void) {;}

char         /*--> write a title line --------------s-----[ leaf-- [ ------ ]-*/
FILE_title         (FILE *a_file)
{
   fprintf (a_file, "#type  ver  full name --------------------------------------------------  t  lastchg-----  timestamp---  uid   s  gid   s  ugo  bytes----  sha1 hash -------------------------------------------------  package ---------------------------------------------------- \n\n");
   return 0;
}

char         /*--> write a single command record ---------[ ------ [ ------ ]-*/
FILE_write         (
      /*----------+-----------+-----------------------------------------------*/
      FILE       *a_file,     /* destination file                             */
      tCMD       *a_cmd,      /* pointer to command structure                 */
      char       *a_prefix)   /* record prefix                                */
{
   /*---(write single line)--------------*/
   fprintf (a_file, "%-5.5s  -E-  %-60.60s  %c  %-12ld  %-12ld  %-4d  %c  %-4d  %c  %-3.3s  %9d  %-59.59s  %-60.60s \n" ,
         a_prefix       ,
         a_cmd->full    , a_cmd->ftype   , a_cmd->lastchg , a_cmd->filetime,
         a_cmd->uid     , a_cmd->suid    , a_cmd->gid     , a_cmd->sgid    ,
         a_cmd->mode    , a_cmd->bytes   , a_cmd->hash    ,
         (a_cmd->i_pkg >= 0) ? pkgs [a_cmd->i_pkg].full : "-");
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] write commands to database ----------------------*/
CMD_writeall       (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* iterator -- package            */
   int         j           = 0;             /* iterator -- location           */
   FILE       *f           = NULL;          /* file pointer - commands        */
   int         curr        = 0;
   char        s           [1000];
   int         x_count     = 0;
   /*---(open)---------------------------*/
   DEBUG_CACHE   printf ("\n\ndatabase write\n");
   f = fopen (CMD_DATABASE, "w");
   if (f == NULL) {
      printf ("               can not open command file\n");
      return -1;
   }
   DEBUG_CACHE   printf ("    database open\n");
   /*---(header)-------------------------*/
   DEBUG_CACHE   printf ("    writing header\n");
   fprintf (f, "# hermes command database written at %ld\n", my.runtime);
   fprintf (f, "#    -D- added last update time to records");
   fprintf (f, "#    -E- added record types and versions\n");
   /*---(output)-------------------------*/
   for (i = 0; i < ncmd; ++i) {
      /*---(prepare)---------------------*/
      curr = icmd [i];
      j = s_cmds [curr].i_loc;
      /*---(filter)----------------------*/
      if (strchr (valid_src, s_cmds [curr].source) == NULL)   continue;
      /*---(output)----------------------*/
      if ((x_count % 5)     == 0)  fprintf (f, "\n");
      if (x_count % (9 * 5) == 0)  FILE_title (f);
      FILE_write (f, &s_cmds [curr], "cmd");
      ++x_count;
      /*---(done)------------------------*/
   }
   fprintf (f, "\n");
   FILE_title (f);
   /*---(wrapup)-------------------------*/
   fclose (f);
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] write commands to database ----------------------*/
CMD_readdb         (void)
{
   /*---(locals)-----------+-----------+-*/
   FILE       *f           = NULL;          /* file pointer                   */
   char        recd        [1000];          /* generic record buffer          */
   int         len         = 0;             /* string length                  */
   char        s          [200];            /* generic string                 */
   int         v           = 0;
   char        c           = ' ';
   char       *p           = NULL;
   char       *q           = "";
   char       *r           = NULL;
   int         sloc        = -1;
   int         rci         = 0;             /* return code as int             */
   char        rcc         = 0;             /* return code as char            */
   int         x_loc       = -1;
   int         nread       = 0;             /* number records read            */
   int         nproc       = 0;             /* number records processed       */
   char        x_type      [20];
   char        x_ver       [20];
   /*---(open)---------------------------*/
   f = fopen (CMD_DATABASE, "r");
   if (f == NULL) {
      DEBUG_CACHE   printf ("               can not open command file\n");
      return -1;
   }
   /*---(prepare)------------------------*/
   CMD_purge ();
   DEBUG_CACHE   printf ("   database read\n");
   DEBUG_CACHE   printf ("   -seq cnt len    - location-------    name-----------    full-------------------------- t    t u s g s m    s    h    ---- f a ---- pkg----------------------\n");
   /*---(process entries)----------------*/
   while (1) {
      /*---(read)------------------------*/
      fgets(recd, 1000, f);
      if (feof (f)) break;
      /*---(output)----------------------*/
      ++nread;
      DEBUG_CACHE  if (nread % 3 == 1)   printf ("\n");
      DEBUG_CACHE  printf ("   %4d %3d ", nread, nproc);
      /*---(filter)----------------------*/
      rcc = recd_valid (recd, &len);
      if (rcc < 0)  continue;
      DEBUG_CACHE   printf ("%3d    ", len);
      r = NULL;
      /*---(type)------------------------*/
      rcc = parse_string  (recd, &r, 1, LCFULL, x_type);
      if (strcmp ("cmd", x_type) != 0) {
         DEBUG_CACHE   printf ("not a command record, SKIPPING\n");
         continue;
      }
      /*---(type)------------------------*/
      rcc = parse_string  (NULL, &r, 1, LCFULL, x_ver);
      if (strcmp ("-E-", x_ver) != 0) {
         DEBUG_CACHE   printf ("version not -E-, SKIPPING\n");
         continue;
      }
      /*---(full)------------------------*/
      rcc = parse_string  (NULL, &r, 1, LCFULL, s_cmds  [ncmd].full);
      if (rcc < 0)   continue;
      s_cmds [ncmd].flen = strlen (s_cmds [ncmd].full);
      strcpy (s, s_cmds [ncmd].full);
      p = strrchr (s, '/');
      if (p == NULL)  {
         DEBUG_CACHE   printf ("location not found in %s, SKIPPING\n", s);
         continue;
      }
      strcpy (s_cmds [ncmd].name, p + 1);
      s_cmds [ncmd].len  = strlen (s_cmds [ncmd].name);
      *p = '\0';
      /*---(location)--------------------*/
      rci = LOC_find_path (s, 'a');
      if (rci < 0)  {
         rci = LOC_create (s, 'd', "");
         /*> DEBUG_CACHE   printf ("location %s not found, SKIPPING\n", s);        <*/
         /*> continue;                                                                <*/
      }
      LOC_link (rci, ncmd);
      x_loc = rci;
      s_cmds [ncmd].source = '-';
      LOC_curs_index (x_loc);
      DEBUG_CACHE   printf ("%c "          , LOC_curr_source ());
      DEBUG_CACHE   printf ("%-15.15s    " , LOC_curr_path   ());
      DEBUG_CACHE   printf ("%-15.15s    " , s_cmds  [ncmd].name);
      DEBUG_CACHE   printf ("%-30.30s "    , s_cmds  [ncmd].full);
      /*---(type)------------------------*/
      rcc = parse_flag  (NULL, &r, "l-"       , &s_cmds [ncmd].ftype);
      if (rcc < 0)   continue;
      DEBUG_CACHE   printf ("%c    "       , s_cmds  [ncmd].ftype);
      /*---(record update time)----------*/
      rcc = parse_long    (NULL, &r, 0, -1    , &s_cmds [ncmd].lastchg);
      if (rcc < 0)   continue;
      if (s_cmds [ncmd].lastchg == 0)  s_cmds [ncmd].lastchg = my.runtime;
      /*---(timestamp)-------------------*/
      rcc = parse_long    (NULL, &r, 1, -1    , &s_cmds [ncmd].filetime);
      if (rcc < 0)   continue;
      DEBUG_CACHE   printf ("- ");
      /*---(security)--------------------*/
      rcc = parse_integer (NULL, &r, 0, 100000, &s_cmds [ncmd].uid);
      if (rcc < 0)   continue;
      DEBUG_CACHE   printf ("- ");
      rcc = parse_flag  (NULL, &r, "*-"       , &s_cmds [ncmd].suid);
      if (rcc < 0)   continue;
      DEBUG_CACHE   printf ("%c "          , s_cmds  [ncmd].suid);
      rcc = parse_integer (NULL, &r, 0, 100000, &s_cmds [ncmd].gid);
      if (rcc < 0)   continue;
      DEBUG_CACHE   printf ("- ");
      rcc = parse_flag  (NULL, &r, "*-"       , &s_cmds [ncmd].sgid);
      if (rcc < 0)   continue;
      DEBUG_CACHE   printf ("%c "          , s_cmds  [ncmd].sgid);
      rcc = parse_string  (NULL, &r, 1, LCMODE, s_cmds  [ncmd].mode);
      if (rcc < 0)   continue;
      DEBUG_CACHE   printf ("- ");
      /*---(size)------------------------*/
      DEBUG_CACHE   printf ("   ");
      rcc = parse_integer (NULL, &r, 0, -1    , &s_cmds [ncmd].bytes);
      if (rcc < 0)   continue;
      DEBUG_CACHE   printf ("- ");
      s_cmds  [ncmd].size = s_cmds  [ncmd].bytes;
      DEBUG_CACHE   printf ("   ");
      rcc = parse_string  (NULL, &r, 1, LCHASH, s_cmds  [ncmd].hash);
      if (rcc < 0)   continue;
      DEBUG_CACHE   printf ("- ");
      /*---(package)---------------------*/
      DEBUG_CACHE   printf ("   ");
      rcc = parse_string  (NULL, &r, 1, LCHASH, s);
      if (rcc < 0)   continue;
      rci = -1;
      if (strcmp (s, "-") == 0)  {
         DEBUG_CACHE   printf ("---- ");
         s_cmds [ncmd].i_pkg = -1;
         DEBUG_CACHE   printf ("x x ---- %-25.25s ", s);
      } else {
         rci = PKG_find (s);
         DEBUG_CACHE   printf ("%4d ", rci);
         if (rci < 0)  {
            rci = PKG_push (s, '+', ' ', "");
            DEBUG_CACHE   printf ("+ %c %4d ", s_cmds [ncmd].source, rci);
            DEBUG_CACHE   printf ("%-25.25s ", pkgs [rci].full);
         } else {
            DEBUG_CACHE   printf ("- %c %4d ", s_cmds [ncmd].source, rci);
            DEBUG_CACHE   printf ("%-25.25s ", pkgs [rci].full);
         }
         PKG_link     (rci, ncmd);
      }
      /*---(focus)--------------------------*/
      if (  s_cmds [ncmd].len == my.focus_len &&
            strcmp (s_cmds [ncmd].name, my.focus) == 0) {
         s_cmds [ncmd].active = 'y';
      }
      /*---(done-------------------------*/
      DEBUG_CACHE   printf ("\n");
      icmd [ncmd] = ncmd;
      LOC_link     (x_loc, ncmd);
      ++ncmd;
      ++nproc;
   }
   /*---(wrapup)-------------------------*/
   fclose (f);
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] output a sorted list ----------------------------*/
CMD_savelinks      (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           = 0;             /* iterator -- package            */
   tSTAT       st;                          /* file stats                     */
   char        x_link      [LEN_LINK];      /* link to real file              */
   int         x_real      =   1;
   /*---(cycle commands)--------------*/
   for (i = 0; i < ncmd; ++i) {
      /*---(filter)-------------------*/
      if (s_cmds [i].ftype != 'l')   continue;
      /*---(get link)-----------------*/
      rc = readlink (s_cmds [i].full, x_link, 500);
      if (rc < 0) {
         s_cmds [i].sym_note = '?';
         continue;
      }
      x_link [rc] = '\0';
      if (strlen (x_link) <= 0) {
         s_cmds [i].sym_note = '0';
         continue;
      }
      strlcpy (s_cmds [i].sym_name, x_link, LEN_LINK);
      /*---(find real cmd)------------*/
      x_real = CMD_find (x_link);
      if (x_real < 0) {
         s_cmds [i].sym_note = '#';
         continue;
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
CMD_unit           (char *a_question, int a_num)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* loop iterator                  */
   int         m           = 0;             /* maximum count                  */
   int         s           [100];           /* generic string                 */
   /*---(prepare)------------------------*/
   strcpy  (unit_answer, "command unit     : question not understood");
   /*---(defenses)-----------------------*/
   if      (ncmd < 1) {
      snprintf (unit_answer, LEN_TEXT, "command empty    : no commands exist");
   }
   else if (a_num < 0) {
      snprintf (unit_answer, LEN_TEXT, "command error    : command ref (%d) is negative", a_num);
   }
   else if (a_num != 0 && a_num >= ncmd) {
      snprintf (unit_answer, LEN_TEXT, "command error    : command ref (%d vs %d) is too high", a_num, ncmd);
   }
   /*---(command name)-------------------*/
   else if (strncmp (a_question, "command_name"      , 20)      == 0) {
      snprintf (unit_answer, LEN_TEXT, "command name     : %3d, %-.35s", a_num, s_cmds [a_num].full);
   }
   /*---(command count)------------------*/
   else if (strncmp (a_question, "command_count"     , 20)      == 0) {
      snprintf (unit_answer, LEN_TEXT, "command count    : %d", ncmd);
   }
   /*---(last command)-------------------*/
   else if (strncmp (a_question, "command_last"      , 20)      == 0) {
      snprintf (unit_answer, LEN_TEXT, "command last     : (%2d) %c, %-25.25s (%2d)", ncmd - 1, s_cmds [ncmd - 1].source, s_cmds [ncmd - 1].full, s_cmds [ncmd - 1].flen);
   }
   /*---(parsed command)-----------------*/
   else if (strncmp (a_question, "command_parse"     , 20)      == 0) {
      LOC_curs_index (s_cmds [a_num].i_loc);
      snprintf (unit_answer, LEN_TEXT, "command parsed   : %-10.10s, %-.25s", LOC_curr_path (), s_cmds [a_num].name);
   }
   /*---(command link)-------------------*/
   else if (strncmp (a_question, "command_link"      , 20)      == 0) {
      if (s_cmds [a_num].i_pkg < 0) {
         snprintf (unit_answer, LEN_TEXT, "command link     : not linked");
      } else {
         snprintf (unit_answer, LEN_TEXT, "command link     : (%3d) %-.25s", s_cmds [a_num].i_pkg, pkgs [s_cmds [a_num].i_pkg].full);
      }
   }
   /*---(location command count)---------*/
   else if (strncmp (a_question, "command_sorted"    , 20)      == 0) {
      strcpy (unit_answer, "command sorted   :");
      m = ncmd;
      if (m > 10)   m = 10;
      for (i = 0; i < m; ++i) {
         sprintf (s, " %d", icmd [i]);
         strcat (unit_answer, s);
      }
   }
   /*---(command security)---------------*/
   else if (strncmp (a_question, "command_sec"       , 20)      == 0) {
      snprintf (unit_answer, LEN_TEXT, "command security : %3d, %3.3s, %4d, %c, %4d, %c", a_num, s_cmds [a_num].mode, s_cmds [a_num].uid, s_cmds [a_num].suid, s_cmds [a_num].gid, s_cmds [a_num].sgid);
   }
   /*---(command size)-------------------*/
   else if (strncmp (a_question, "command_size"      , 20)      == 0) {
      snprintf (unit_answer, LEN_TEXT, "command size     : %3d, %9d, %9d, %c", a_num, s_cmds [a_num].size, s_cmds [a_num].bytes, s_cmds [a_num].smiss);
   }
   /*---(command hash)-------------------*/
   else if (strncmp (a_question, "command_hash"      , 20)      == 0) {
      snprintf (unit_answer, LEN_TEXT, "command hash     : %3d, %-35.35s", a_num, s_cmds [a_num].hash);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}

/*===============================[[ end-code ]]===============================*/
