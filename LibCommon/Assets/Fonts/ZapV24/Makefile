#########################################################################
#                                                                       #
#           Linux Console Fonts from The ZAP Group Australia            #
#                 Copyright (C) 2004-24, John Zaitseff                  #
#                                                                       #
#########################################################################

# Author:  John Zaitseff <J.Zaitseff@zap.org.au>
# Version: 2.4

# This Makefile creates the Linux console fonts from The ZAP Group
# Australia.
#
#
# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation, either version 3 of the License, or (at your
# option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program.  If not, see <https://www.gnu.org/licenses/>.


# Names of font files to create

fontfiles := $(strip	\
	zap-vga09	\
	zap-vga16	\
	zap-vga32	\
	zap-light16	\
	zap-light18	\
	zap-light20	\
	zap-light24	\
	zap-light32	\
	zap-ext-vga09	\
	zap-ext-vga16	\
	zap-ext-vga32	\
	zap-ext-light16	\
	zap-ext-light18	\
	zap-ext-light20	\
	zap-ext-light24	\
	zap-ext-light32	\
)


# Main targets: "make fonts" (the default) makes the fonts, "make pdfs"
# makes PDF codecharts of various sizes, "make images" makes screenshot
# images and "make all" makes all three targets.

fonts::  all-fonts
pdfs::   all-pdfs
images:: all-images
all::    all-fonts all-pdfs all-images

all-fonts::  $(addsuffix .psf, $(fontfiles))

all-pdfs::   $(addsuffix .pdf,        $(fontfiles)) \
	     $(addsuffix --large.pdf, $(fontfiles)) \
	     $(addsuffix --huge.pdf,  $(fontfiles))

all-images:: $(addsuffix .png, $(fontfiles))


# Create Makefile rules based on the variable $(fontfiles)

define make_template
    $(1).psf:        $(1).psftx
    $(1).pdf:        $(1).psftx
    $(1)--large.pdf: $(1).psftx
    $(1)--huge.pdf:  $(1).psftx
    $(1).png:        $(1).psftx
endef

$(foreach fontfile,$(fontfiles),$(eval $(call make_template,$(fontfile))))


# Check integrity of font files

check:: all-fonts
	sha1sum -c sha1sum

sha1sum: $(addsuffix .psf, $(fontfiles))
	sha1sum $(addsuffix .psf,$(fontfiles)) >sha1sum


# Remove superfluous files as required

clean::
	-rm -f $(addsuffix .pdf,        $(fontfiles)) \
	       $(addsuffix --large.pdf, $(fontfiles)) \
	       $(addsuffix --huge.pdf,  $(fontfiles)) \
	       $(addsuffix .png,        $(fontfiles))

distclean:: clean
	-rm -f $(addsuffix .psf, $(fontfiles))
	-rm -f sha1sum


# The actual build rules

%.psf: %.psftx
	./utils/psftx2psf $^ $@

%.pdf: %.psftx
	./utils/psftx-codechart --size normal $^ $@

%--large.pdf: %.psftx
	./utils/psftx-codechart --size large $^ $@

%--huge.pdf: %.psftx
	./utils/psftx-codechart --size huge $^ $@

%.png: %.psftx
	./utils/psftx-sampler $^ | ./utils/psftx-screenshot $^ - $@


.PHONY: fonts pdfs images all all-fonts all-pdfs all-images check clean distclean
.DELETE_ON_ERROR:
.DEFAULT:
.SUFFIXES:
