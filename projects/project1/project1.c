/*
 * Chris Brown
 * sevrc
 * Project: 1
 */

// I used the code from the book and modified it to fit the requirements
// the only thing online I looked at was .h files

#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* function type that is called for each filename */
typedef int     Myfunc(const char *, const struct stat *, int);

static Myfunc   myfunc;
static int              myftw(char *, Myfunc *);
static int              dopath(Myfunc *);
void reg(char *);
void sandf(char *, size_t);
void f(char *);
void s(char *, size_t);

int fi = 0, si = 0; //global variables to decide if i should print via -s or -f or both
char size[10000];
char find[200];

int main(int argc, char *argv[])
{
	        int             ret;

		if (argc < 2){
			ret = myftw(".", myfunc);
		}

		else if(argc == 3){
			if ( strcmp(argv[1], "-f") == 0){
				fi = 1;
				strcpy(find,argv[2]);
				ret = myftw(".", myfunc);
			}
			else if (strcmp(argv[1],"-s") == 0){
				si =1;
				strcpy(size, argv[2]);
				printf("looking for file size of %s\n", size);
				ret = myftw(".", myfunc);
			}
		}
		else
			ret = myftw(argv[1], myfunc);           
	return 0;
}

/*
 * Descend through the hierarchy, starting at "pathname".
 * The caller's func() is called for every file.
 */
#define FTW_F   1               /* file other than directory */
#define FTW_D   2               /* directory */
#define FTW_DNR 3               /* directory that can't be read */
#define FTW_NS  4               /* file that we can't stat */

static char     *fullpath;              /* contains full pathname for every file */
static size_t pathlen;

static int myftw(char *pathname, Myfunc *func)
{
	        fullpath = malloc(sizeof(PATH_MAX) * 2000);        /* malloc PATH_MAX+1 bytes */
		                                                           /* ({Prog pathalloc}) */
		        if (pathlen <= strlen(pathname)) {
				pathlen = strlen(pathname) * 200;
				if ((fullpath = realloc(fullpath, pathlen)) == NULL)
					exit(-1);
			}
			strcpy(fullpath, pathname);
			return(dopath(func));
}


/*
 * Descend through the hierarchy, starting at "fullpath".
 * If "fullpath" is anything other than a directory, we lstat() it,
 * call func(), and return.  For a directory, we call ourself
 * recursively for each name in the directory.
 */
static int dopath(Myfunc* func)
{
	        struct stat             statbuf;
		struct dirent   *dirp;
		DIR                             *dp;
		int                             ret, n;

		if (lstat(fullpath, &statbuf) < 0)      /* stat error */
			return(func(fullpath, &statbuf, FTW_NS));
		if (S_ISDIR(statbuf.st_mode) == 0)      /* not a directory */
		        return(func(fullpath, &statbuf, FTW_F));
 /*
 * It's a directory.  First call func() for the directory,
 * then process each filename in the directory.
 */
	if ((ret = func(fullpath, &statbuf, FTW_D)) != 0)
		return(ret);
	n = strlen(fullpath);
	if (n + PATH_MAX + 2 > pathlen) {       /* expand path buffer */
		pathlen *= 2;
		if ((fullpath = realloc(fullpath, pathlen)) == NULL)
			exit(-1);
	}
	fullpath[n++] = '/';
	fullpath[n] = 0;

	if ((dp = opendir(fullpath)) == NULL)   /* can't read directory */
		return(func(fullpath, &statbuf, FTW_DNR));
	while ((dirp = readdir(dp)) != NULL) {
		if (strcmp(dirp->d_name, ".") == 0  || strcmp(dirp->d_name, "..") == 0)
			continue;                        /* ignore dot and dot-dot */
		strcpy(&fullpath[n], dirp->d_name);     /* append name after "/" */
		if ((ret = dopath(func)) != 0)         /* recursive */
			break;  /* time to leave */
	}
	fullpath[n-1] = 0;      /* erase everything from slash onward */
	if (closedir(dp) < 0)
		exit(-1);
	return(ret);
}

int tabover = 0;

static int
myfunc(const char *pathname, const struct stat *statptr, int type)
{
	        char str[100];
		strcpy(str,pathname);
		switch (type) {
			case FTW_F:
				switch (statptr->st_mode & S_IFMT) {
					case S_IFREG: 
						if (si == 1 && fi == 1 ){
							sandf(str, statptr->st_size); 
						}
						else if (fi ==1){
							f(str);
						}
						else if(si == 1){
							s(str, statptr->st_size);
						}																										                             else reg(str);
						break;
					case S_IFLNK:   break; //should do links here...not going to
					case S_IFDIR:  //directories under something else
						exit(-1);
				}
				break;
			case FTW_D:
				if (tabover > 0)
					printf("\t%s:\n", pathname);
				else
					printf("%s:\n", pathname); tabover++;
				break;
			default:  exit (-1);
		}
	return(0);
}

/*
 * token prints the files out
 * by taking the fullpath name and parsing through it
 * printing out only after "/"
 */

void reg(char* path){
	int len = strlen(path);
	int i, j;
	for(i=0;i<len;i++){
		if ( path[i] == 47)
			j = i;
	}
	printf("\t\t");
	for(i=j+1;i<len;i++){
		printf("%c",path[i]);
	}
	printf("\n");
}

void s(char* path, size_t check){
	int size_compare = atoi(size);
	if(check >= size_compare){
		reg(path);
	}
}

void f(char* path){
	if ( strstr(path, find) != NULL)
		reg(find);
}

void sandf(char *path, size_t check){
	int compare_this = atoi(size);
	if (strstr(path, find) != NULL && compare_this >= check )
		reg(find);
}
