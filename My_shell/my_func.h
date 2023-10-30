#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define N 12
#define M 1024



int len(char **argv) 
{
	int i = 0;
	while (argv[i] != NULL) {
		//printf("argv: %s\n", argv[i]);
		i++;
	}
	return i;
}

int fun_cat(char **argv){
	int fd;
	char buf[N];
	int i, j, n;
	int size = len(argv);
	if (argv[1] == 0)  {
		printf("no arg\n");
		return -1;
	}
	if (size > 1){
		for (i = 1; i < size; ++i){
			if ((argv[i] != NULL)) {
				if ((fd = open(argv[i], O_RDONLY)) == 0) {
					perror("cat");
					return 1;
				}
				while ((n = read(fd, buf, N)) > 0)
		    			write(1, buf, n);

				close(fd);
			}
			else
				return -1;

       		 }
	}
    return 0;
}


int fun_cp(char **argv)
{
	if (len(argv) != 3){
		printf("Not enough arguments.\n");
		exit (1);
    }
	struct stat buf1, buf2;
	if (stat(argv[1], &buf1) == -1) {
		perror("stat1");
		exit (1);
	}
	if (stat(argv[2], &buf2) != -1) {
		if ((buf1.st_ino == buf2.st_ino) && (buf1.st_dev == buf2.st_dev)){
			fprintf(stderr, "cp: '%s' and '%s' - the same file\n", argv[1], argv[2]);
			exit (1);
		}
	}
    char buf[N];
	int fd1, fd2, n;
    if((fd1 = open(argv[1], O_RDONLY)) == -1){
        printf("error opening the file1.\n");
       return -1; 
    }
    if((fd2 = creat(argv[2], buf1.st_mode)) == -1){
        printf("error creating the file2.\n");
        return -1; 
    }
    if ((fd2 = open(argv[2], buf1.st_mode)) != -1){ 
        fd2 = open(argv[2], O_TRUNC | O_WRONLY);
        while ((n = read(fd1, buf, N)) > 0){
		    write(fd2,buf, n);
        }
        close(fd1);
	close(fd2);
        chmod(argv[2], buf1.st_mode); //изменяем права доступа
    }
    else 
        printf("Permission denained.\n");
    return 0;
} 

int create(int fd, char p[M][M]) {
    char c;
    int i=0, j=0;
    while (read(fd, &c, 1) != 0) {
        p[i][j++] = c;
        if (c=='\n') {
            p[i][j] = '\0';
            i++;
            j = 0;
        }
    }
    return i;
}

int bigger(char *s, char *p) {
        int i=0;
        while (s[i]!='\0' && p[i]!='\0' && s[i]>=p[i]) i++;
        return s[i]>=p[i];
}

void sort_bubble(char lst[M][M], int sizelist) {
        int i;
        int j;
        char temp[M];
        int flag;
        if (sizelist <= 2) return;
        for (i=1; i<sizelist-1; i++) {
            flag = 1;
            for (j=0; j<sizelist-i-1; j++) {
                if (bigger(lst[j], lst[j+1])) {
                    strcpy(temp, lst[j+1]);
                    strcpy(lst[j+1], lst[j]);
                    strcpy(lst[j], temp);
                    flag = 0;
                }
            }
            if (flag) return;
        }
}

void print_lst(int fd, char p[M][M], int len) {
    int i;
    for (i=0; i<len; i++)
        write(fd, p[i], strlen(p[i]));
    return;
}

int fun_sort(char **argv)
{
    int fd;
    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        printf("error with open file\n");
        return -1;
    }
    char p[M][M];
    int len = create(fd, p);
    //printf("created\n");
    close(fd);
    sort_bubble(p, len);
    //printf("sorted\n");
    if ((fd = open(argv[1], O_WRONLY|O_TRUNC)) == -1) {
        printf("error with open file\n");
        return -1;
    }
    print_lst(fd, p, len);
    //printf("writed\n");
    return 0;
}



