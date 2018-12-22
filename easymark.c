
#include <stdio.h>
#if defined(__linux__)
#define MYOS 1
#elif defined(_WIN32)
#define MYOS 2
#elif defined(_WIN64)
#define MYOS 3
#elif defined(__unix__)
#define MYOS 4
#define PATH_MAX 2500
#else
#define MYOS 0
#endif
#include <string.h>
#include <stdlib.h>



#include <stdlib.h>
#include <string.h>

#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h> 
#include <fcntl.h>

#include <time.h>

///  norm
#define KRED  "\x1B[31m"
#define KGRE  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KNRM  "\x1B[0m"
///  bright
#define KBGRE  "\x1B[92m"
#define KBYEL  "\x1B[93m"

char *fbasenoext(char* mystr)
{
    char *retstr;
    char *lastdot;
    if (mystr == NULL)
         return NULL;
    if ((retstr = malloc (strlen (mystr) + 1)) == NULL)
        return NULL;
    strcpy (retstr, mystr);
    lastdot = strrchr (retstr, '.');
    if (lastdot != NULL)
        *lastdot = '\0';
    return retstr;
}





///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void fileuniprocess( char *filetarget,  char *filein )
{
  int fetchi;
  FILE *fp5;
  FILE *fp6;
  char fetchline[PATH_MAX];
  char fetchlinetmp[PATH_MAX];
  char inputfield[PATH_MAX];
  char fieldsrc[PATH_MAX];
  char fieldtrg[PATH_MAX];
  char putline[PATH_MAX];

  int linecounter = 1;
  int content_archive = 0;
  int content_export = 0;
  char file_export[PATH_MAX];
  strncpy( file_export, "", PATH_MAX );
  int pcc = 0;
  int filereader = 1;
  int foundcmd = 0;

  /////////////////////////////////////////////////
  {
    fp5 = fopen( filetarget , "wb");
    fp6 = fopen( filein , "rb");
    while( !feof(fp6) )
    {
       fgets(fetchlinetmp, PATH_MAX, fp6); 

       if ( filereader == 1 )
       if ( !feof(fp6) )
       {  
          foundcmd = 0;
          strncpy( fetchline, "" , PATH_MAX );
          for( fetchi = 0 ; ( fetchi <= strlen( fetchlinetmp ) ); fetchi++ )
            if ( fetchlinetmp[ fetchi ] != '\n' )
              fetchline[fetchi]=fetchlinetmp[fetchi];
  
         if ( !feof(fp6) )
         {
	      //printf( "\n" );
	      printf( "L%d: [%s]\n", linecounter, fetchline );

              if ( foundcmd == 0 ) 
              if ( (( fetchline[0] == '#' ) && ( fetchline[1] == ' ' )) 
              ||  (( fetchline[0] == '!' ) && ( fetchline[1] == '=' ) && ( fetchline[2] == ' ' )) )
              {
	          printf("%s", KBYEL );
	          printf( " => L%d: Detected section.\n", linecounter );
	          printf("%s", KNRM );
                  foundcmd = 1;
              }

              if ( foundcmd == 0 ) 
              if ( (( fetchline[0] == '#' ) && ( fetchline[1] == '#' ) && ( fetchline[2] == ' ' ) ) 
              ||  (( fetchline[0] == '!' ) && ( fetchline[1] == '=' ) && ( fetchline[2] == '=' ) && ( fetchline[3] == ' ' )) )
              {
	          printf("%s", KMAG );
	          printf( " => L%d: Detected subsection.\n", linecounter );
	          printf("%s", KNRM );
                  foundcmd = 1;
              }

              if ( foundcmd == 0 ) 
              if ( fetchline[0] == '/' ) 
              if ( fetchline[1] == '/' ) 
              {
	          printf("%s", KBLU );
	          printf( " => L%d: Detected a comment line.\n", linecounter );
	          printf("%s", KNRM );
                  foundcmd = 1;
              }

              if ( foundcmd == 0 ) 
              if ( fetchline[0] == '!' ) 
              if ( fetchline[1] == 'q' ) 
              if ( fetchline[2] == 'u' ) 
              if ( fetchline[3] == ' ' ) 
              {
	          printf("%s", KBGRE );
	          printf( " => L%d: Detected question.\n", linecounter );
	          printf("%s", KNRM );
                  foundcmd = 1;
              }

              if ( foundcmd == 0 ) 
              if ( fetchline[0] == '!' ) 
              if ( fetchline[1] == 'c' ) 
              if ( fetchline[2] == 'l' ) 
              if ( fetchline[3] == 'r' ) 
              {
	          printf("%s", KBGRE );
	          printf( " => L%d: Detected clearpage.\n", linecounter );
	          printf("%s", KNRM );
                  foundcmd = 1;
              }

              if ( foundcmd == 0 ) 
              if ( fetchline[0] == '!' ) 
              if ( fetchline[1] == 'f' ) 
              if ( fetchline[2] == 'i' ) 
              if ( fetchline[3] == 'g' ) 
              if ( fetchline[4] == '{' ) 
              {
	          printf("%s", KBGRE );
	          printf( " => L%d: Detected a figure.\n", linecounter );
	          printf("%s", KNRM );
                  foundcmd = 1;
              }

                  
              if ( foundcmd == 0 ) 
              {
                 fputs( fetchline   , fp5 );
                 fputs( "\n"  , fp5 );
                 foundcmd = 0;
              }

              /*
              if ( linecounter >= 60 +7  )
              {
                  pcc = 0;
                  for( fetchi = 4 ; ( fetchi <= 10 ); fetchi++ )
                      putline[pcc++]=fetchline[fetchi];
                  putline[pcc]='\0';

                  fputs( putline   , fp5 );
                  fputs( ";"   , fp5 );

                  strncpy( putline, ""  , PATH_MAX );
                  pcc = 0;
                  for( fetchi = 16 ; ( fetchi <= 22 ); fetchi++ )
                      putline[pcc++]=fetchline[fetchi];
                  putline[pcc]='\0';
                  fputs( putline   , fp5 );

                  fputs( "\n"   , fp5 );
              }
              */


              linecounter++;

	 } 
       }
      }
      fclose( fp6 ); 
      fclose( fp5 ); 
  }
}








int main( int argc, char *argv[])
{
    char cwd[PATH_MAX]; int doi ; 
    char targetfile[PATH_MAX]; 

    ////////////////////////////////////////////////////////
    if ( argc >= 2)
    {
         // less -R
         for( doi = 1 ; doi < argc ; doi++) 
         {
            strncpy( targetfile, fbasenoext( argv[ doi ] ) , PATH_MAX );
            strncat( targetfile , ".tex" , PATH_MAX - strlen( targetfile ) -1 );
            printf( "Target: %s\n" , targetfile );
	    fileuniprocess( targetfile , argv[ doi ] );
         }
         return 0;
    }

    return 0;
}



