########################################################################
####################### Makefile Template ##############################
########################################################################

INC_DIRS = -I./src \
					 -I./src/data_structures \
					 -I./src/direction \
					 -I./src/engine \
					 -I./src/entities/ant \
					 -I./src/statemanager \
					 -I./src/camera \
					 -I./src/tile \

# Compiler settings - Can be customized.
CC = gcc
CXXFLAGS = -g -Wall $(INC_DIRS)
CFLAGS = -g -Wall $(INC_DIRS)
#LDFLIBS = -lncurses
LDFLAGS = -lncurses

# Makefile settings - Can be customized.
APPNAME = antspiral
EXT = .c
SRCDIR = src
OBJDIR = obj

############## Do not change anything from here downwards! #############
SRC = $(shell find $(SRCDIR) -name '*.c')
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)
# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(OBJ)
# Windows OS variables & settings
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Creates the dependecy rules
%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

#################### Cleaning rules for Windows OS #####################
# Cleans complete project
.PHONY: cleanw
cleanw:
	$(DEL) $(WDELOBJ) $(DEP) $(APPNAME)$(EXE)

# Cleans only all files with the extension .d
.PHONY: cleandepw
cleandepw:
	$(DEL) $(DEP)