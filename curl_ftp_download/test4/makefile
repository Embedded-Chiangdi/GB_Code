all: ftp_file_get

ftp_file_get: ftp_file_get.c
	gcc $^ -o $@ -lcurl

clean:
	@echo "clean ftp_file_get"
	-rm ftp_file_get
	@echo "clean completed"
    
.PHONY:clean all
