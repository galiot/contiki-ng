CONTIKI_PROJECT = oar
all: $(CONTIKI_PROJECT)

PROJECT_SOURCEFILES += oar-debug.c

PROJECT_SOURCEFILES += oar-json.c
PROJECT_SOURCEFILES += oar-json-extended.c
PROJECT_SOURCEFILES += oar-json-compact.c
PROJECT_SOURCEFILES += oar-json-micro.c
PROJECT_SOURCEFILES += oar-json-tiny.c

PROJECT_SOURCEFILES += oar-crypt.c
PROJECT_SOURCEFILES += oar-base64.c
PROJECT_SOURCEFILES += oar-hash.c

PROJECT_SOURCEFILES += httpd-simple.c

PLATFORMS_ONLY = cc26x0-cc13x0 cc2538dk openmote-cc2538 zoul native simplelink

CONTIKI = ../..
include $(CONTIKI)/Makefile.include