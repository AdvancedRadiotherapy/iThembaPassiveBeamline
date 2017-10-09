# $Id: GNUmakefile,v 1.6 2010/12/09 14:27:04 mazzaglia Exp $
# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------

name := Protontherapy
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

include $(G4INSTALL)/config/architecture.gmk

# This warning generated too much noise in a regular build.
CFLAGS += $(call cc-option, -Wno-unused-but-set-variable)
#KBUILD_CFLAGS += $(call cc-option, -Wno-unused-but-set-variable)

# for ROOT
#CPPFLAGS  += -I$(ROOTSYS)/include
#EXTRALIBS  = $(shell root-config --glibs)
# for ROOT
#  trying to fix TFile error on Ubuntu 11.10
#  worked! -> found on Geant4 Hypernews
ROOTCONFIG := root-config
EXTRALIBS += $(shell $(ROOTCONFIG) --libs)
CPPFLAGS += $(shell $(ROOTCONFIG) --cflags)

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/binmake.gmk

visclean:
	rm -f g4*.prim g4*.eps g4*.wrl
	rm -f .DAWN_*










