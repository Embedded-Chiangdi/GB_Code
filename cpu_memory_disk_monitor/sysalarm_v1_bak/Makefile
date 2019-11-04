ifndef CC
CC=gcc
endif

ifeq ($(BOARD_TYPE),GW_X86)
CFLAGS  += -I$(APP_INCLUDE) $(AP_FLAG) -I$(NET_INCLUDE)
else
CFLAGS  = -I$(APP_INCLUDE) $(AP_FLAG)
CFLAGS += -L$(TOPDIR)/app/common -lcommon -L$(TOPDIR)/wifi/wlan/os/linux/tools -lwifi_pal
endif

CFLAGS += $(EXT_APP_CFLAGS)

LDFLAGS = -Wall
LDLIBS = -lcrypt

DEST_PATH = $(BIN_PATH)/app/bin
ETC_PATH = $(TOPDIR)/build/fsbase/rootfs/etc


ifeq ($(BOARD_TYPE),GW_X86)
statmonitor-dep=statmonitor.o
mailalarm-dep=mailalarm.o
else
statmonitor-dep=statmonitor.o
mailalarm-dep=mailalarm.o
endif


build: statmonitor mailalarm

install:
	@echo "INSTALL       statmonitor mailalarm"

ifeq ($(BOARD_TYPE), GW_X86)
	@cp -f statmonitor $(DEST_SBIN_PATH)
	@cp -f mailalarm $(DEST_SBIN_PATH)
else
	@cp -f statmonitor $(DEST_PATH)/statmonitor
	@cp -f mailalarm $(DEST_PATH)/mailalarm
endif

clean:
	@echo "CLEAN         statmonitor mailalarm"
	@rm -f *.o statmonitor mailalarm
	
statmonitor: $(statmonitor-dep)
	@echo "BUILD         statmonitor"
	$(CC) $(CFLAGS) $(LDFLAGS) -o statmonitor $(statmonitor-dep) $(LDLIBS) -L$(DEST_LIB_PATH) 
	@$(STRIP) -d statmonitor
	
mailalarm: $(mailalarm-dep)
	@echo "BUILD         mailalarm"
	$(CC) $(CFLAGS) $(LDFLAGS) -o mailalarm $(mailalarm-dep) $(LDLIBS) -L$(DEST_LIB_PATH) 
	@$(STRIP) -d mailalarm


