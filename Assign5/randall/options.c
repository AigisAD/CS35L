#include "options.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
bool ProcessOptions (int argc, char **argv, struct OptStruct *ptr_opts){
    int c;
    if(argc % 2 ==1||argc>6){
        fprintf (stderr, "invalid arguments\n");
        exit(1);
    }
    int icount=0;
    int ocount=0;
    while((c=getopt(argc, argv, "i:o:"))!= -1){
       
        switch(c){
        case 'i':
            icount++;
            if (icount>1){
                fprintf (stderr, "invalid arguments\n");
                exit(1);
            }   
            if (strcmp(optarg,"rdrand")==0){
                ptr_opts->input_type=0;
            }else if (strcmp(optarg,"mrand48_r")==0){
                ptr_opts->input_type=1;
            }else if (strncmp("/",optarg,1)==0){
                char subbuff[strlen(optarg)];
                strncpy( subbuff, &optarg[1] , strlen(optarg)-1 );
                subbuff[strlen(optarg)-1] = '\0';  
                if (access(optarg,F_OK)==-1&&access(subbuff,F_OK)==-1){
                    fprintf (stderr, "%s DNE\n", optarg);
                    exit(1);
                }
                ptr_opts->file_path= (char *)malloc(strlen(optarg)+1);
                strcpy(ptr_opts->file_path,optarg);
                ptr_opts->file_path[strlen(optarg)]='\0';
            }else{
                fprintf (stderr, "%s not recognized\n", optarg);
                exit(1);
            }
            break;
        case 'o':
            ocount++;
            if (ocount>1){
                fprintf (stderr, "invalid arguments\n");
                exit(1);
            }
            if(strcmp(optarg,"stdio")==0){
                ptr_opts->output_type=0;
            }else {
                for (int i = 0; optarg[i]!= '\0'; i++)
                {
                    if (isdigit(optarg[i]) == 0){
                        fprintf (stderr, "%s not recognized\n", optarg);
                        exit(1);
                    }
                }
                ptr_opts->output_type=1;
                ptr_opts->block_size=atoi(optarg);
            }
            break;
        }

    }
    for (int i = 0;argv[optind][i]!= '\0'; i++)
    {
        
        if (isdigit(argv[optind][i]) == 0){
            fprintf (stderr, "%s not recognized\n", argv[optind]);
            exit(1);
        }
    }
    if (optind!=argc-1){
        fprintf (stderr, "invalid arguments\n");
        exit(1);
    }
    ptr_opts->nbytes=atoi(argv[optind]);
    return true;
}