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
   /*---(startup)------------------------*/
   if (rc == 0)   rc = PROG_urgs    (argc, argv);
   if (rc == 0)   rc = PROG_init    ();
   if (rc == 0)   rc = PROG_args    (argc, argv);
   if (rc == 0)   rc = PROG_begin   ();
   if (rc != 0)   return -1;
   /*---(main)---------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   AREA_list    ();
   PKG_world    ();
   /*> PKG_readdb   ();                                                               <*/
   PKG_list     ();

   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   PROG_end     ();
   return 0;


   CMD_readdb   ();

   CMD_gather   ('n');

   PKG_index    ();
   CMD_index    ();

   /*> CMD_world    ();                                                               <*/
   /*> CMD_package  ();                                                               <*/
   /*> CMD_writeall ();                                                              <*/

   if (my.list_locs == 'y')  LOC_list     ();
   if (my.list_pkgs == 'y')  PKG_list     ();
   if (my.list_cmds == 'y')  CMD_list     ();

   PKG_writedb  ();

   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   PROG_end     ();
   return 0;

   /*> PKG_write    ();                                                               <*/
   /*> CMD_writeall ();                                                               <*/


   /*---(package inventory)--------------*/
   /*> RUN_WORLD  {                                                                   <* 
    *>    DEBUG_WORLD   printf ("reading in packages/ebuilds from world\n");          <* 
    *>    PKG_world       ();                                                         <* 
    *>    PKG_index       ();                                                         <* 
    *>    DEBUG_WORLD   printf ("\n");                                                <* 
    *> }                                                                              <*/
   /*---(read command database)----------*/
   /*> RUN_READ  {                                                                    <* 
    *>    RUN_READ     printf ("read the command databae\n");                         <* 
    *>    database_read   ();                                                         <* 
    *>    PKG_index       ();                                                         <* 
    *>    CMD_index       ();                                                         <* 
    *>    RUN_READ     printf ("\n");                                                 <* 
    *> }                                                                              <*/
   /*---(read command database)----------*/
   /*> RUN_COMMAND  {                                                                 <* 
    *>    DEBUG_CMDS   printf ("gathering all commands on path\n");                   <* 
    *>    CMD_gather      ('y');                                                      <* 
    *>    CMD_index       ();                                                         <* 
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
   /*> RUN_WORLD    PKG_list    ();                                                   <*/
   /*> RUN_COMMAND  CMD_list    ();                                                   <*/
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