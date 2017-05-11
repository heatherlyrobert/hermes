/*===============================[[ beg-code ]]===============================*/
#include    "hermes.h"



/*====================------------------------------------====================*/
/*===----                            main                              ----===*/
/*====================------------------------------------====================*/
static void      o___MAIN____________________o (void) {;}

int
main               (int argc, char *argv[])
{
   /*---(locals)-----------+-----------+-*/
   int         rc          = 0;
   /*---(initialize)---------------------*/
   if (rc >= 0)   rc = yURG_logger  (argc, argv);
   if (rc >= 0)   rc = PROG_init    ();
   if (rc >= 0)   rc = yURG_urgs    (argc, argv);
   if (rc >= 0)   rc = PROG_args    (argc, argv);
   if (rc >= 0)   rc = PROG_begin   ();
   if (rc <  0)  {
      PROG_end     ();
      exit (-1);
   }
   /*---(main)---------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);


   PKG_world           ();
   PKG_writedb         ();

   CMD_gather          ('n');
   FILES_gather ();

   PKG_index           ();
   CMD_crack_gnome     ();

   AREA_list           ();
   LOC_list            ();
   PKG_list            ('i');
   CMD_dump            ();
   CMD_list            ('i');


   /*> CMD_world    ();                                                               <*/

   /*> CMD_writeall ();                                                               <*/




   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   PROG_end     ();
   return 0;


   CMD_readdb   ();

   CMD_gather   ('n');

   PKG_index    ();

   /*> CMD_world    ();                                                               <*/
   /*> CMD_package  ();                                                               <*/
   /*> CMD_writeall ();                                                              <*/

   if (my.list_locs == 'y')  LOC_list     ();
   if (my.list_pkgs == 'y')  PKG_list     ('s');
   if (my.list_cmds == 'y')  CMD_list     ('s');

   PKG_writedb  ();

   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   PROG_end     ();
   return 0;

   /*> PKG_write    ();                                                               <*/
   /*> CMD_writeall ();                                                               <*/


   /*---(package inventory)--------------*/
   /*> RUN_WORLD  {                                                                   <* 
    *>    DEBUG_GENTOO   printf ("reading in packages/ebuilds from world\n");          <* 
    *>    PKG_world       ();                                                         <* 
    *>    PKG_index       ();                                                         <* 
    *>    DEBUG_GENTOO   printf ("\n");                                                <* 
    *> }                                                                              <*/
   /*---(read command database)----------*/
   /*> RUN_READ  {                                                                    <* 
    *>    RUN_READ     printf ("read the command databae\n");                         <* 
    *>    database_read   ();                                                         <* 
    *>    PKG_index       ();                                                         <* 
    *>    RUN_READ     printf ("\n");                                                 <* 
    *> }                                                                              <*/
   /*---(read command database)----------*/
   /*> RUN_COMMAND  {                                                                 <* 
    *>    DEBUG_CMDS   printf ("gathering all commands on path\n");                   <* 
    *>    CMD_gather      ('y');                                                      <* 
    *>    DEBUG_CMDS   printf ("\n");                                                 <* 
    *> }                                                                              <*/
   /*---(matching)-----------------------*/
   /*> RUN_MATCH  {                                                                   <* 
    *>    DEBUG_MATCH   printf ("match commands to world packages\n");                <* 
    *>    CMD_world       ();                                                         <* 
    *>    DEBUG_MATCH   printf ("\n");                                                <* 
    *> }                                                                              <*/
   /*---(missing packages)---------------*/
   /*> RUN_PACKAGE {                                                                  <* 
    *>    printf ("locate missing packages\n");                                       <* 
    *>    CMD_package     ();                                                         <* 
    *>    PKG_index       ();                                                         <* 
    *>    printf ("\n");                                                              <* 
    *> }                                                                              <*/
   /*---(final reporting)----------------*/
   /*> RUN_WORLD    PKG_list    ('s');                                                   <*/
   /*> RUN_COMMAND  CMD_list    ('s');                                                   <*/
   /*---(matching)-----------------------*/
   /*> RUN_WRITE  {                                                                   <* 
    *>    RUN_WRITE    printf ("write the command databae\n");                        <* 
    *>    CMD_writeall    ();                                                         <* 
    *>    RUN_WRITE   printf ("\n");                                                  <* 
    *> }                                                                              <* 
    *> PKG_write       ();                                                            <* 
    *> LOC_list        ();                                                            <*/
   /*---(complete)-----------------------*/
   PROG_end     ();
   return 0;
}


/*===============================[[ end-code ]]===============================*/
