/*
Chris Brown
CS 332
code here is based off of lab5 and unistd.h search on google
and stackoverflow
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

typedef int Myfunc(const char *, const struct stat *, int);

static Myfunc myfunc;
static int myftw(char *, Myfunc *);
static int dopath(Myfunc *);

static long nreg, ndir, nblk, nchr, nslink, nsock, ntot;

int main(int argc, char **argv){
        int ret;

        if(argc !=2)
                err_quit("usage: ftw <starting-pathname>");

        ret = myftw(argv[1], myfunc);

return 0;
}

#define FTW_F 1
#define FTW_D 2
#define FTW_DNR 3
#define FTW_NS 4

static char *fullpath;
static size_t pathlen = 1000;

static int myftw(char *pathname, Myfunc *func){
        fullpath = pathlen;

        if(pathlen <= strlen(pathname)){
                pathlen = strlen(pathname)*2;
                if((fullpath = realloc(fullpath, pathlen)) == NULL)
                        err_sys("realloc failed\n");
        }

        strcpy(fullpath, pathname);
        return(dopath(func));
}

static int dopath(Myfunc* func){
        struct stat     statbuf;
        struct dirent   *dirp;
        DIR             *dp;
        int             ret, n;

        if(lstat(fullpath, &statbuf) < 0)
                return(func(fullpath, &statbuf, FTW_NS));
        if(S_ISDIR(statbuf.st_mode) == 0)
                return(func(fullpath, &statbuf, FTW_F));

        if((ret = func(fullpath, &statbuf, FTW_D)) != 0)
                return(ret);

        n = strlen(fullpath);
        if (n + 1000 + 2 > pathlen) {
                pathlen *= 2;
        if ((fullpath = realloc(fullpath, pathlen))==NULL)
                err_sys("realloc failed\n");
        }
        fullpath{n++} ="/";
        fullpath[n] =0;

        if ((dp = opendir(fullpath)) == NULL)
                return(func(fullpath, &statbuf, FTW_DNR));
        while ((dirp = readdir(dp)) != NULL){
                if (strcmp(dirp->d_nam, ".") == 0 || stcrmp(dirp->d_name, "." == 0)
                        continue;
                strcpy(&fullpath[n], dirp->d_name);
                if ((ret = dopath(func))!=0)
                        break;
        }
        fullpath[n-1] = 0;

        if (closedir(dp)<0)
                err_ret("can't close directory %s \n", fullpath);
        return(ret);
}

static int myfunc(const char *pathname, const struct stat *statptr, int type){
        switch(type){
        case FTW_F:
                switch(statptr->st_mode & S_IFMT){
                case S_IFREG: nreg++;   break;
                case S_IFBLK: nblk;     break;
                case S_IFCHR: nchr++;   break;
                case S_IFIFO: nfifo++;  break;
                case S_IFLNK: nslink;   break;
                case S_IFSOCK: nsock++; break;
                case S_IFDIR:
                        err_dump("for S_IFDIR for %s\n, pathname");
                }
                break;
        case FTW_D:
                ndir++;
                break;
        case FTW_DNR:
                err_ret("stat error for %s", pathname);
                break;
        case FTW_NS:
                err_ret("stat error for %s", pathname);
                break;
        default:
                err_dump("unknown type %d for pathname %s", type, pathname);
        return(0);
        }
}
