#########################################################################
#                                                                       #
#               Input/Output Functions for Raw Font Files               #
#                 Copyright (C) 2016-24, John Zaitseff                  #
#                                                                       #
#########################################################################

# Author: John Zaitseff <J.Zaitseff@zap.org.au>

# This module contains functions to read and write raw font files to and
# from psffont.Font objects.
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


"""Input/Output Functions for Raw Font Files.

The `rawfntio` module contains functions to read and write raw font files
to and from `psffont.Font` objects.  Raw font files are an obsolete font
format used in the ``kbd``\(8) package for Linux console fonts.  Such
files do not have any header data and consist solely of glyph data in
binary format.

This module contains the following public functions:

* `readfont()`  - Read a raw font file into a `psffont.Font` object
* `writefont()` - Write a `psffont.Font` object out to a raw font file
"""


__version__ = '1.2'
__author__ = 'John Zaitseff <J.Zaitseff@zap.org.au>'


import os

import psffont
from psffont import InvalidFontError, MIN_HEIGHT, MAX_HEIGHT


#########################################################################
# readfont function

def readfont(file, height=None):
    """Read a raw font file and return a `psffont.Font` object.

    This function reads in a font file 8 pixels wide by height pixels
    high from `file` and returns a `psffont.Font` object with its
    contents.  If height is ``None`` (the default), the font height is
    calculated from the size of the input file.  `file` must be a
    file-like object already open for binary reading (mode ``'rb'``) or a
    string containing a pathname to be opened in this mode.

    If the font file is malformed, an `InvalidFontError` exception is
    raised.
    """

    if isinstance(file, str):
        file = open(file, 'rb')

    result = psffont.Font()
    glyph_count = 256
    width = 8

    if not height:
        file_stat = os.stat(file.fileno())
        height = file_stat.st_size // glyph_count
        if height * glyph_count != file_stat.st_size:
            raise ValueError('illegal file size (not a multiple of %d)'
                             % glyph_count, file)
    if not MIN_HEIGHT <= height <= MAX_HEIGHT:
        raise ValueError('height %d is not in range %d..%d'
                         % (height, MIN_HEIGHT, MAX_HEIGHT))

    # Read glyph bitmaps

    for glyph_num in range(glyph_count):
        glyph = psffont.Glyph(width, height)

        glyph_data = file.read(height)
        if len(glyph_data) != height:
            raise InvalidFontError('could not read font glyph 0x%02X'
                                   % glyph_num, file)

        for row in range(height):
            # Glyphs are stored in the raw font file with the top row
            # first, with the left-most pixel being the most significant
            # bit of the one-byte glyph data
            row_str = '{0:08b}'.format(glyph_data[height - row - 1])
            row_list = [0 if bit == '0' else 1 for bit in row_str]
            glyph[row] = row_list

        result[glyph_num] = glyph

    return result


#########################################################################
# writefont function

def writefont(font, file):
    """Write a `psffont.Font` object out to a raw font file.

    This function writes the `font` `psffont.Font` object to `file`,
    which must be a file or file-like object already open for binary
    writing (mode ``'wb'``).

    Note that `font` must be minimally valid: all glyphs must be present
    (not missing).  In addition, the font width must be 8 pixels and
    there must be exactly 256 glyphs.  If these conditions are not met,
    the `InvalidFontError` exception is raised.
    """

    if isinstance(file, str):
        file = open(file, 'wb')

    psffont.check(font, allow_missing_glyphs=False,
                  allow_missing_mappings=True,
                  allow_overlapping_mappings=True,
                  allow_out_of_order_mappings=True)

    width = font.width
    height = font.height
    count = font.count()

    if width != 8:
        raise InvalidFontError('width must be 8 pixels, not %d' % width)
    if count != 256:
        raise InvalidFontError('font must have 256 glyphs, not %d' % count)

    # Write glyph bitmaps

    for glyph_num in range(count):
        glyph_vals = font[glyph_num]
        glyph_data = bytearray(height)

        for row in range(height):
            # Glyphs are stored in the raw font file with the top row
            # first, with the left-most pixel being the most significant
            # bit of the one-byte glyph data
            row_val = 0
            for bit in glyph_vals[row]:
                row_val = (row_val << 1) | bit

            glyph_data[height - row - 1] = row_val

        file.write(glyph_data)


#########################################################################
