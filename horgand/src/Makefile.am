datadir = $(prefix)/share/${PACKAGE}
helpdir = $(prefix)/share/doc/${PACKAGE}
website = "horgand.berlios.de"
package = "horgand"
version = "1.10"
DEFS = -DPACKAGE=\"$(package)\" -DVERSION=\"$(version)\" -DHELPDIR=\"$(helpdir)\" -DDATADIR=\"$(datadir)\" -DWEBSITE=\"$(website)\"  @DEFS@
bin_PROGRAMS = horgand
horgand_SOURCES = main.C \
        organ.C \
	organDSPEffects.C \
	organAudioOut.C \
	organMIDIIn.C \
	organAccompaniment.C \
	organvarios.C \
	organFileIO.C \
	jackoutput.C \
        HORGAN.cxx \
        Holrgan.h \
        jackoutput.h \
        HORGAN.h 

