#include <stdio.h>
#include <stdlib.h>
int girintile(char c);
int is_enabled=0;
int is_paused=0;
int is_paused2=0;
int tapcount=0;
int is_newline=0;
int is_full=0;
int is_ignore=0;
int is_esc=0;
char tab='\t';
char cc=0;
char ccc=0;
FILE *input;
FILE *output;
int main(int argc, char* argv[]){
	char c = 0;
	if(argc>=2){
		input=fopen(argv[1],"r");
	}else{
		input=stdin;
	}
	if(argc>=3){
		output=fopen(argv[2],"w");
	}else{
		output=stdout;
	}
	if(argc>=4){
		tab=argv[3][0];
	}
	c=getc(input);
	while(c != -1){
		girintile(c);
		ccc=cc;
		cc=c;
		c=getc(input);
	}
}
int girintile(char c){
	if(is_paused==0 && is_paused2==0 && is_full==1){
		if(c == '{'){
			tapcount++;
		}
		if(c == '}'){
			tapcount--;
		}
	}
	if(is_newline==0 && is_full==1){
		if(c==' ' || c == '\t'){
			is_ignore=1;
			is_newline=0;
		}else{
			is_newline=1;
			is_ignore=0;
			for(int i=0;i<tapcount;i++){
				putc(tab,output);
			}
		}
	}
	if(cc == '\\' && ccc != '\\'){
		if(is_esc==0 && c != '\\'){
			is_esc=1;		
		}
	}
	if(is_esc==0){
		if(c == '*' && is_paused==0 && is_paused2==0){
			if(cc=='/'){
				is_full=1;
			}
		}
		if(is_enabled==0 && is_paused==0 && is_paused2==0){
			if(c == '/'){
				if(cc=='/' && is_full==0){
					is_enabled=1;
				}
				if(cc=='*'){
					is_full=0;
				}
			}
		}
		if(c == '\'' && cc != '\\' && is_paused2==0){
			if(is_paused==1){
				is_paused=0;
			}else{
				is_paused=1;
			}
		}
		if(c == '\"' && cc != '\\' && is_paused==0){
			if(is_paused2==1){
				is_paused2=0;
			}else{
				is_paused2=1;
			}
		}
		if(c == '\n'){
			is_newline=0;
			is_enabled=0;
		}
	}
	if(is_ignore==0 || is_full==1){
		is_esc=0;
		putc(c,output);
	}
	return 0;
}