
GCC = g++
SRCDIR = src
BUILDDIR = .build
BINDIR = bin
INCDIR = include
TARGET = $(BINDIR)/DFIRE_RNA


SRCPDB = $(SRCDIR)/PDB.cc \
         $(SRCDIR)/pdb_utils.cc
OBJ_PDB = $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SRCPDB:.cc=.o))

CFLAGS = -std=c++11 -fopenmp# -g -pg
LDFLAGS = -L/home/tc/tools/boost/lib -Llib -fopenmp

LIB = -ldl #-lboost_filesystem -lboost_system

INC = -I include #-I $(ROOT_BOOST)

all: getseq getcontacts #checkmissing

$(BUILDDIR)/%.o: $(SRCDIR)/%.cc $(INCDIR)/%.h
	@mkdir -p $(BUILDDIR)
	$(GCC) $(CFLAGS) $(INC) -c -o $@ $<

.PHONY: clean
clean:
	@echo " Cleaning..."
	rm -rf $(BINDIR)

getseq: $(OBJ_PDB) src/getseq.cc
	mkdir -p $(BINDIR)
	$(GCC) $^ $(CFLAGS)  $(INC)  $(LIB) $(LDFLAGS)  -o $(BINDIR)/getseq

getcontacts: $(OBJ_PDB) src/getcontacts.cc
	$(GCC) $^ $(CFLAGS)  $(INC)  $(LIB) $(LDFLAGS)  -o $(BINDIR)/getcontacts

# checkmissing: $(OBJ_PDB) src/checkmissing.cc
# 	$(GCC) $^ $(CFLAGS)  $(INC)  $(LIB) $(LDFLAGS)  -o $(BINDIR)/checkmissing
