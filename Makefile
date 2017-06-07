CXX          ?= g++
CC           ?= gcc
QDP_DIR      ?= $(HOME)/.usr/qdp_debug
OPENQCD_DIR  ?= openqcd
MPI_DIR      ?= /usr/lib/openmpi

CXXFLAGS     := -std=c++14 -g -Iinclude -I$(OPENQCD_DIR)/include\
								-I$(MPI_DIR)/include\
								$(shell $(QDP_DIR)/bin/qdp++-config --cxxflags)

CCFLAGS      := -g -I$(OPENQCD_DIR)/include -I$(MPI_DIR)/include

QDP_LIBFLAGS := $(shell $(QDP_DIR)/bin/qdp++-config --libs)\
								$(shell $(QDP_DIR)/bin/qdp++-config --ldflags)

SRCDIR    := programs
LIBDIR    := library
BINDIR    := bin
OBJDIR    := obj
DEPDIR    := .dep
OBJDEPDIR := $(DEPDIR)/obj

SRCS     := $(wildcard $(SRCDIR)/*.cpp)
EXECS    := $(SRCS:$(SRCDIR)/%.cpp=$(BINDIR)/%)
DEPS     := $(SRCS:$(SRCDIR)/%.cpp=$(DEPDIR)/%.d)
LIBSRCS  := $(wildcard $(LIBDIR)/*.cpp)
LIBOBJS  := $(LIBSRCS:$(LIBDIR)/%.cpp=$(OBJDIR)/%.o)
LIBDEPS  := $(LIBSRCS:$(LIBDIR)/%.cpp=$(OBJDEPDIR)/%.d)

OPENQCD_FILES  := flags/flags flags/lat_parms flags/dfl_parms\
	                lattice/bcnds lattice/uidx lattice/geometry\
							  	uflds/uflds uflds/plaq_sum uflds/udcom\
									su3fcts/su3prod su3fcts/su3ren su3fcts/cm3x3 su3fcts/random_su3\
									random/ranlux random/ranlxs random/ranlxd random/gauss\
									utils/endian utils/mutils utils/utils utils/wspace\
									archive/archive

OPENQCD_OBJDIRS := flags lattice uflds su3fcts random utils archive
OPENQCD_SRCS    := $(OPENQCD_FILES:%=$(OPENQCD_DIR)/modules/%.c)
OPENQCD_OBJS    := $(OPENQCD_FILES:%=$(OBJDIR)/openqcd/%.o)

all: $(EXECS) $(OPENQCD_DIR)
.PHONY: clean all

bin/qdp_to_openqcd : \
		$(SRCDIR)/qdp_to_openqcd.cpp\
		$(LIBOBJS) $(OPENQCD_OBJS)\
		$(DEPDIR)/qdp_to_openqcd.d\
		| $(BINDIR)
	@echo "CXX $@"
	@$(CXX) $(CXXFLAGS) $< $(LIBOBJS) $(OPENQCD_OBJS) -o $@ $(QDP_LIBFLAGS)

$(LIBOBJS): $(OBJDIR)/%.o : $(LIBDIR)/%.cpp $(OBJDEPDIR)/%.d | $(OBJDIR)
	@echo "CXX $@"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OPENQCD_OBJS): $(OBJDIR)/openqcd/%.o : $(OPENQCD_DIR)/modules/%.c | $(OPENQCD_OBJDIRS)
	@echo "CC $@"
	@$(CC) $(CCFLAGS) -c $< -o $@

$(DEPS): $(DEPDIR)/%.d: $(SRCDIR)/%.cpp | $(DEPDIR)
	@$(CXX) $(CXXFLAGS) -MM -MP -MT $(BINDIR)/$(patsubst $(SRCDIR)/%.cpp,%,$<) -MF $@ $<

$(LIBDEPS): $(OBJDEPDIR)/%.d: $(LIBDIR)/%.cpp | $(OBJDEPDIR)
	@$(CXX) $(CXXFLAGS) -MM -MP -MT $(OBJDIR)/$(patsubst $(LIBDIR)/%.cpp,%.o,$<) -MF $@ $<

-include $(DEPS) $(LIBDEPS)

clean:
	rm -rf $(BINDIR) $(DEPDIR) $(OBJDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

$(DEPDIR):
	@mkdir -p $(DEPDIR)

$(OBJDEPDIR):
	@mkdir -p $(OBJDEPDIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OPENQCD_OBJDIRS): | $(OBJDIR)
	@mkdir -p $(OPENQCD_OBJDIRS:%=$(OBJDIR)/openqcd/%)

$(OPENQCD_DIR):
	$(error The openqcd folder does not exist, please link it in. Expected location "$(OPENQCD_DIR)")
