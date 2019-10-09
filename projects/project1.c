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

static long     nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int
main(int argc, char *argv[])
{
        int             ret;

        if (argc != 2)
                exit(-1);

        ret = myftw(argv[1], myfunc);           /* does it all */

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
static int                                      /* we return whatever func() returns */
myftw(char *pathname, Myfunc *func)
{
        fullpath = malloc(sizeof(PATH_MAX) + 1);        /* malloc PATH_MAX+1 bytes */
                                                                                /* ({Prog pathalloc}) */
        if (pathlen <= strlen(pathname)) {
                pathlen = strlen(pathname) * 2;
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
static int                                      /* we return whatever func() returns */
dopath(Myfunc* func)
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
                if (strcmp(dirp->d_name, ".") == 0  ||
                    strcmp(dirp->d_name, "..") == 0)
                                continue;               /* ignore dot and dot-dot */
                strcpy(&fullpath[n], dirp->d_name);     /* append name after "/" */
                if ((ret = dopath(func)) != 0)          /* recursive */
                        break;  /* time to leave */
        }
        fullpath[n-1] = 0;      /* erase everything from slash onward */

        if (closedir(dp) < 0)
                exit(-1);
        return(ret);
}

static int
myfunc(const char *pathname, const struct stat *statptr, int type)
{
        switch (type) {
        case FTW_F:
                switch (statptr->st_mode & S_IFMT) {
                case S_IFREG:   nreg++;         break;
                case S_IFBLK:   nblk++;         break;
                case S_IFCHR:   nchr++;         break;
                case S_IFIFO:   nfifo++;        break;
                case S_IFLNK:   nslink++;       break;
                case S_IFSOCK:  nsock++;        break;
                case S_IFDIR:   /* directories should have type = FTW_D */
                        exit(-1);
                }
                break;
        case FTW_D:
                printf("%s %ld \n", pathname, statptr->st_size);
                break;
        case FTW_DNR:
                exit(-1);
                break;
        case FTW_NS:
                exit(-1);
                break;
        default:
                exit(-1);
        }
        return(0);
}
