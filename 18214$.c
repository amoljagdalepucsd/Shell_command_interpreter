#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#define FSIZE 2048

int i,j = 0,ifd,ofd,n,linecount = 0,wordcount,charcount,array[100],mode1;
ssize_t cin,cout;
char list[FSIZE],c[1],command[80],keyword[10],mode[5],fname[30],cmd;

void helpDemo()
{
        fprintf(stdout,"/***+---------------------HELP--------------------+***/\n\n");
        
	fprintf(stdout,"(mode operation) C - character W - words L -lines\n\n");
        
	fprintf(stdout,"command mode fname\n1.Count mode fname \nmode -> 1.CW 2.WL 3.CL 4.CWL\n\n");
        
	fprintf(stdout,"2. Typeline mode fname\nmode -> 1.+n 2.-n 3.a(all)\n\n");
        
	fprintf(stdout,"3.List mode dirname\nmode ->1.F 2.N 3.for current directory(type .)\n\n");
        
	fprintf(stdout,"4. h (for helpdemo)\n\n");
        
	fprintf(stdout,"5. q  (for exit)\n\n");
        
	fprintf(stdout,"//**********MY_COMMAND_INTERPRETER************//\n\n");
}

int toDirectory(char *dirname,char *mode)
{
	DIR *fd;int filecount = 0;
	struct dirent *dir;
	
	if((fd = opendir(dirname)) == NULL)
	{
		fprintf(stderr,"directory can't open\n");
		return -1;
	}
	
	if(strcmp(dirname,".") == 0)
	{	
		fprintf(stdout,"***++------------Files in Current directory----------+++**\n");
		fd = opendir(".");
		
		if(fd){
		while((dir = readdir(fd)) != NULL)
		{	
			filecount ++;
			if(strcmp(mode,"F") == 0){
				fprintf(stdout,"%s\n",dir->d_name);
			}
		}
		closedir(fd);
		}
	}
	else { 	
		while((dir = readdir(fd)) != NULL)
		{	
			if(!strcmp(dir->d_name,".") || !strcmp(dir->d_name,".."))
				continue;
			if(strcmp(mode,"F") == 0){
				fprintf(stdout,"%s\n",dir->d_name);
				filecount ++;}
			}
			closedir(fd);
		}
	
	if(strcmp(mode,"N") == 0)
	{
		fprintf(stdout,"%d",filecount);
	}
}

int toPrintFile(char *list,char *mode,int *array)
{
	if(linecount == 0)
	{
		fprintf(stdout,"Firstly count the lines");
		exit(0);
	}
	
	mode1 = atoi(mode);
	
	if(mode1 <= linecount){
	if(mode1 > 0)
	{	
		for(i = 0; i < (array[mode1 - 1]);i++)
			fprintf(stdout,"%c",list[i]);	
	}
	else if(strcmp(mode,"a") == 0)
	{
		for(i = mode1 ; i < (array[linecount-1]);i++)
			fprintf(stdout,"%c",list[i]);	
	}
	else if(mode1 < 0)
	{
		mode1 = linecount + mode1;
		mode1 = array[mode1 - 1];
		if(mode1 == 0)
		{
			for(i = mode1 ; i < (array[linecount-1]);i++)
				fprintf(stdout,"%c",list[i]);	
				return -1;
		}	
			
		for(i = mode1;i< array[linecount - 1];i++)
			fprintf(stdout,"%c",list[i]);
	}
	else if(mode1 == 0){
			fprintf(stdout,"Incorrect line number");	
		}
	}
}

void actionOnFile(char *fname,char *mode)
{
	ifd = open(fname,O_RDONLY);
	
	while(read(ifd,&c,1) != 0)
	{	
		if(i >= FSIZE)
		{
			fprintf(stdout,"File size exceeded\n");
			exit(0);
		}
		list[i++] = c[0];
		if(c[0] == '\n')
		{	linecount ++;
			array[j++] = i;
		}
		if(c[0] == '?' || c[0] =='!' || c[0] == ':' || c[0] == ',' || c[0] == ' ' || (c[0] == '\n'))
		{
			wordcount ++;
		}
	}		
	charcount = i;
	wordcount -=1; 

	if(strcmp(mode,"CW") == 0)
		fprintf(stdout,"characters count :%d words count :%d",charcount,wordcount);
	else if(strcmp(mode,"WL") == 0)
		fprintf(stdout,"words count :%d lines count :%d",wordcount,linecount);
	else if(strcmp(mode,"CL") == 0)
		fprintf(stdout,"characters count :%d lines count :%d",charcount,linecount);
	else if(strcmp(mode,"CWL") == 0)
		fprintf(stdout,"characters count :%d words count :%d lines count :%d",charcount,wordcount,linecount);
	else 				
		fprintf(stdout,"--Incorrect");
}

int main(void)
{
	while(1)
	{
		printf("\namol@18214 $");
		
		fgets(command,80,stdin);
		
		n = sscanf(command,"%s%s%s",keyword,mode,fname);
		
		if(n != 3 && n!= 1)
		{
			fprintf(stdout,"Incorrect Command\n");
			return -1;			
		}
		
		if(strcmp(keyword,"Count") == 0)
			cmd = 'C';
		else if(strcmp(keyword,"Typeline") == 0)
			cmd = 'T';
		else if(strcmp(keyword,"List") == 0)
			cmd = 'L';
		else if(strcmp(keyword,"h") == 0)
			cmd =  'H';
		else if(strcmp(keyword,"q") == 0)
			cmd = 'Q'; 
		else
		{
			fprintf(stdout,"Invalid Command\n");
			continue ;	
		}	
				
		switch(cmd)
		{
			case 'C' : actionOnFile(fname,mode);
					break;
			
			case 'T' : toPrintFile(list,mode,array);				
					break;
			
			case 'L' : toDirectory(fname,mode);
					break;
			
			case 'H' : helpDemo();
					break;
			case 'Q' : 	exit(0);
					break;
			default : fprintf(stdout,"Invalid Command parameter");
		}	
	}
	return 0;
}
