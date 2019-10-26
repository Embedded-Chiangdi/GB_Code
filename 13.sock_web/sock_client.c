int main(){
    int fd;
    fd=connect_to_server(host,port);
    if(fd ==-1)
        exit(1);
    talk_wirh_server(fd);
    close(fd);
    return 0;

}
void talk_wirh_server(int fd){
    char buf[LEN];
    int n;
    n=read(fd,buf,LEN);
    write(1,buf,n);
}