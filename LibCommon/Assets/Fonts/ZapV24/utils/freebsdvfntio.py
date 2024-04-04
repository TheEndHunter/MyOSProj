#########################################################################
#                                                                       #
#             Input/Output Functions for FreeBSD VFNT Files             #
#                 Copyright (C) 2017-24, John Zaitseff                  #
#                                                                       #
#########################################################################

# Author: John Zaitseff <J.Zaitseff@zap.org.au>

# This module contains functions to read and write FreeBSD VFNT files to
# and from psffont.Font objects.  The VFNT file format is essentially not
# documented: the code in this module has been reverse-engineered from
# the following FreeBSD source code files:
#
#   base/head/sys/sys/consio.h, SVN revision 312910
#   base/head/usr.sbin/vidcontrol/vidcontrol.c, SVN revision 316462
#   base/head/usr.bin/vtfontcvt/vtfontcvt.c, SVN revision 305815
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


"""Input/Output Functions for FreeBSD VFNT Files.

The `freebsdvfntio` module contains functions to read and write FreeBSD
VFNT files to and from `psffont.Font` objects.  VFNT files are used to
provide fonts to the FreeBSD console under the ``vt``\(4) driver.

This module contains the following public functions:

* `readfont()` - Read a FreeBSD VFNT file into a `psffont.Font` object
* `writefont()` - Write a `psffont.Font` object out to a FreeBSD VFNT file
"""


__version__ = '1.2'
__author__ = 'John Zaitseff <J.Zaitseff@zap.org.au>'


import psffont
from psffont import InvalidFontError, MIN_WIDTH, MAX_WIDTH, \
     MIN_HEIGHT, MAX_HEIGHT, MIN_GLYPH_COUNT, MAX_GLYPH_COUNT


#########################################################################
# Global constants

MAX_VFNT_MAPPINGS = 4


#########################################################################
# readfont function

def readfont(file):
    """Read a FreeBSD VFNT font file and return a `psffont.Font` object.

    This function reads in a font file from `file` and returns a
    `psffont.Font` object with its contents.  `file` must be a file-like
    object already open for binary reading (mode ``'rb'``) or a string
    containing a pathname to be opened in this mode.  To read from a text
    stream (such as ``sys.stdin``), pass the underlying buffer object
    (eg, ``sys.stdin.buffer``).

    If the font file is malformed, an `InvalidFontError` exception is
    raised.
    """

    if isinstance(file, str):
        file = open(file, 'rb')

    result = psffont.Font()

    # Read VFNT header

    magic = file.read(8)
    if magic != b'VFNT0002':
        raise InvalidFontError('not a FreeBSD VFNT font file', file)

    width = int.from_bytes(file.read(1), 'big', signed=False)
    if not MIN_WIDTH <= width <= MAX_WIDTH:
        raise InvalidFontError('illegal font width %d' % width, file)

    height = int.from_bytes(file.read(1), 'big', signed=False)
    if not MIN_HEIGHT <= height <= MAX_HEIGHT:
        raise InvalidFontError('illegal font height %d' % height, file)

    file.read(2)                          # Skip padding bytes

    glyph_count = int.from_bytes(file.read(4), 'big', signed=False)
    if not MIN_GLYPH_COUNT <= glyph_count <= MAX_GLYPH_COUNT:
        raise InvalidFontError('illegal glyph count %d' % glyph_count, file)

    bytewidth = (width + 7) // 8
    bytesize = height * bytewidth

    vfnt_mappings = [0] * MAX_VFNT_MAPPINGS
    for i in range(MAX_VFNT_MAPPINGS):
        vfnt_mappings[i] = int.from_bytes(file.read(4), 'big', signed=False)

    # Read VFNT glyph bitmaps

    for glyph_num in range(glyph_count):
        glyph = psffont.Glyph(width, height)

        glyph_data = file.read(bytesize)
        if len(glyph_data) != bytesize:
            raise InvalidFontError('could not read font glyph 0x%02X'
                                   % glyph_num, file)

        for row in range(height):
            # Glyphs are stored in the VFNT font file with the top row
            # first, with the left-most pixel being the most significant
            # bit of the one- or two-byte glyph data (stored in
            # big-endian format)
            offset = (height - row - 1) * bytewidth
            row_val = int.from_bytes(glyph_data[offset : offset + bytewidth],
                                     'big', signed=False)
            row_str = '{0:0{1}b}'.format(row_val, bytewidth * 8)[0 : width]
            row_list = [0 if bit == '0' else 1 for bit in row_str]
            glyph[row] = row_list

        result[glyph_num] = glyph

    # Read VFNT Unicode mapping tables

    for mapping_num in range(MAX_VFNT_MAPPINGS):
        for mapping_count in range(vfnt_mappings[mapping_num]):
            m_src = int.from_bytes(file.read(4), 'big', signed=False)
            m_dst = int.from_bytes(file.read(2), 'big', signed=False)
            m_len = int.from_bytes(file.read(2), 'big', signed=False)

            for i in range(m_len + 1):
                glyph_num = m_dst + i
                char = chr(m_src + i)

                mappings = result[glyph_num].unicode_mapping
                if mappings:
                    mappings.append(char)
                else:
                    mappings = [char]
                result[glyph_num].unicode_mapping = mappings

    return result


#########################################################################
# VFNT Unicode mapping table entry

class VFNT_Map:
    """VFNT Unicode mapping table entry."""

    def __init__(self, start_char=None, start_glyph=None, count=None):
        """Create a Unicode mapping table entry.

        This creates a Unicode mapping table entry that maps `count`
        Unicode characters from `start_char` to `start_char` + `count` -
        1, to the glyphs `start_glyph` to `start_glyph` + `count` - 1.
        In other words, this object is essentially a run-length-encoding
        (RLE) that gives::

            chr(ord(self.start_char))     => self.start_glyph
            chr(ord(self.start_char) + 1) => self.start_glyph + 1
            chr(ord(self.start_char) + 2) => self.start_glyph + 2
            ...
            chr(ord(self.start_char) + self.count - 1) =>
                self.start_glyph + self.count - 1
        """

        self.start_char = start_char
        self.start_glyph = start_glyph
        self.count = count


#########################################################################
# writefont function

def writefont(font, file):
    """Write a `psffont.Font` object out to a FreeBSD VFNT font file.

    This function writes the `font` `psffont.Font` object to `file`,
    which must be a file or file-like object already open for binary
    writing (mode ``'wb'``).

    Note that `font` must be valid: all glyphs must be present (not
    missing) and have a Unicode mapping, no Unicode mappings may overlap
    and no multi-character mappings are allowed.  If these conditions are
    not met, the `InvalidFontError` exception is raised.
    """

    if isinstance(file, str):
        file = open(file, 'wb')

    psffont.check(font, allow_missing_glyphs=False,
                  allow_missing_mappings=False,
                  allow_overlapping_mappings=False,
                  allow_out_of_order_mappings=True,
                  allow_gt_max_glyph_count_strict=True)

    width = font.width
    height = font.height
    count = font.count()

    bytewidth = (width + 7) // 8
    bytesize = height * bytewidth

    # Calculate VFNT Unicode mapping tables

    all_mappings = font.get_all_mappings()
    if not all_mappings:
        raise InvalidFontError('missing Unicode mappings')
    for mapping in all_mappings:
        if len(mapping) > 1:
            raise InvalidFontError('illegal multi-character mappings')

    all_mappings_keys = list(all_mappings.keys())
    all_mappings_keys.sort()

    vfnt_mappings = []                    # Only vfnt_map[0] is supported

    # VFNT mapping tables are sequences of RLE mappings (VFNT_Map).  This
    # code calculates the longest such RLE sequences.

    cur_rle_seq = None
    for cur_char in all_mappings_keys:
        cur_glyph = all_mappings[cur_char][0]

        if not cur_rle_seq:
            cur_rle_seq = VFNT_Map(cur_char, cur_glyph, 1)
        else:
            prev_end = cur_rle_seq.count - 1
            prev_char = chr(ord(cur_rle_seq.start_char) + prev_end)
            prev_glyph = cur_rle_seq.start_glyph + prev_end

            # Can the current RLE sequence be extended?
            if (ord(prev_char) + 1 == ord(cur_char)
                    and prev_glyph + 1 == cur_glyph):
                # Yes: do so
                cur_rle_seq.count += 1
            else:
                # No: save current sequence and start a new one
                vfnt_mappings.append(cur_rle_seq)
                cur_rle_seq = VFNT_Map(cur_char, cur_glyph, 1)
    else:
        vfnt_mappings.append(cur_rle_seq)

    # Write VFNT header

    file.write(b'VFNT0002')               # VFNT magic bytes
    file.write(width.to_bytes(1, 'big', signed=False))
    file.write(height.to_bytes(1, 'big', signed=False))
    file.write(int(0).to_bytes(2, 'big', signed=False))   # Padding
    file.write(count.to_bytes(4, 'big', signed=False))

    file.write(len(vfnt_mappings).to_bytes(4, 'big', signed=False))
    file.write(int(0).to_bytes(4, 'big', signed=False))
    file.write(int(0).to_bytes(4, 'big', signed=False))
    file.write(int(0).to_bytes(4, 'big', signed=False))

    # Write VFNT glyph bitmaps

    for glyph_num in range(count):
        glyph_vals = font[glyph_num]
        glyph_data = bytearray(bytesize)

        for row in range(height):
            # Glyphs are stored in the VFNT font file with the top row
            # first, with the left-most pixel being the most significant
            # bit of the one- or two-byte glyph data (stored in
            # big-endian format)
            row_val = 0
            for bit in glyph_vals[row]:
                row_val = (row_val << 1) | bit
            row_val <<= bytewidth * 8 - width

            offset = (height - row - 1) * bytewidth
            glyph_data[offset : offset + bytewidth] = \
                row_val.to_bytes(bytewidth, 'big', signed=False)

        file.write(glyph_data)

    # Write VFNT Unicode mapping tables

    for vfnt_map in vfnt_mappings:
        file.write(ord(vfnt_map.start_char).to_bytes(4, 'big', signed=False))
        file.write(vfnt_map.start_glyph.to_bytes(2, 'big', signed=False))
        file.write(int(vfnt_map.count - 1).to_bytes(2, 'big', signed=False))


#########################################################################
