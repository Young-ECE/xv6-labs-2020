#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *path,char *target){
    char buf[512];
    char *p;
    int fd;
    struct dirent de;
    struct stat st;

    fd=open(path,0);
    if(fd<0){
        fprintf(2,"find: cannot open %s\n",path);
        return;
    }
    if(fstat(fd,&st)<0){
        fprintf(2,"find: aannot stat %s\n",path);
        close(fd);
        return;
    }

    switch(st.type){
    case T_FILE:
        if(strcmp(path+strlen(path)-strlen(target),target)==0){
            printf("%s\n",path);
        }
    break;
    case T_DIR:
    if((strlen(path)+1+DIRSIZ+1)>sizeof(buf)){
        printf("find: path too long\n");
        break;
    }

    strcpy(buf,path);
    p=buf+strlen(buf);
    *p++='/';
    while(read(fd,&de,sizeof(de))==sizeof(de)){
        if(de.inum==0){
            continue;
        }
        memmove(p,de.name,DIRSIZ);
        if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0){
            continue;
        }
        if (stat(buf, &st) < 0) {
            printf("find: cannot stat %s\n", buf);
            continue;
        }
        if (st.type == T_DIR) {
            // 目录则递归
            find(buf, target);
        } else if (st.type == T_FILE) {
            // 文件则比较名字，匹配则输出
            if (strcmp(de.name, target) == 0)
                printf("%s\n", buf);
        }
    }
    break;  
    }
    close(fd);

}


int main(int argc,char **argv){
    if(argc!=3){
        printf("usage: find <path> <name>\n");
        exit(1);
    }
    find(argv[1],argv[2]);
    exit(0);
}