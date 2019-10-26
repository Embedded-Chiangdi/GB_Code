int main()
{
    int sock,fd;
    sock=make_server_socket(port);
    if(sock == -1)
        exit(1);
    while(1)
    {
        fd = accept(sock,NULL,NULL)
        if(fd == -1)
            break;
        process_request(fd);
        close(fd);

    }
    return 0;

}
void process_request(int fd){
    int pid =fork();
    switch(pid){
        case -1:return;
        case 0:
            dup2(fd,1);
            close(fd);
            execl("/bin/date","date",NULL);
            oops("execlp");

        default:wait(NULL);
        
    }
}