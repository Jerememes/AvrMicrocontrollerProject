########       AVR Project Makefile       ########
#####                                        #####
#####      Makefile produit et ecrit par     #####
#####   Simon Barrette & Jerome Collin pour  #####
#####           INF1900 - 2016               #####
#####                                        #####
#####         Inspire de Pat Deegan -        #####
#####  Psychogenic Inc (www.psychogenic.com) #####
##################################################

INSTDIR=/usr/local/bin

all:
	(cd lib; make all)
	(cd app; make all)

install:
	(cd lib; make install INSTDIR=${INSTDIR})
	(cd app; make install INSTDIR=${INSTDIR})

clean:
	(cd lib; make clean)
	(cd app; make clean)

debug:
	(cd lib; make all)
	(cd app; make debug INSTDIR=${INSTDIR})