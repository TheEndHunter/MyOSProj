#########################################################################
#                                                                       #
#              Input/Output Functions for Binary PSF Files              #
#                 Copyright (C) 2004-24, John Zaitseff                  #
#                                                                       #
#########################################################################

# Author: John Zaitseff <J.Zaitseff@zap.org.au>

# This module contains functions to read and write binary PSF files to
# and from psffont.Font objects.
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


"""Input/Output Functions for Binary PSF Files.

The `psfio` module contains functions to read and write binary PSF files
to and from `psffont.Font` objects.  PSF font files are used to provide
fonts to the Linux console and come in two main formats, v1 and v2.  This
module can read and write both versions, depending on the file format
itself (for input) or on the `psffont.Font.version` field (for output).

This module contains the following public functions:

* `readfont()`  - Read a PSF font file into a `psffont.Font` object
* `writefont()` - Write a `psffont.Font` object out to a PSF font file
"""


__version__ = '2.3'
__author__ = 'John Zaitseff <J.Zaitseff@zap.org.au>'


import psffont
from psffont import InvalidFontError, MIN_WIDTH, MAX_WIDTH, \
     MIN_HEIGHT, MAX_HEIGHT, MIN_GLYPH_COUNT, MAX_GLYPH_COUNT


#########################################################################
# readfont function

def readfont(file):
    """Read a binary PSF font file and return a `psffont.Font` object.

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

    # Read PSF header

    magic = file.read(2)
    if magic == b'\x36\x04':
        # Process PSF v1 header
        result.version = 1

        font_mode = int.from_bytes(file.read(1), 'little', signed=False)
        if font_mode & ~0x07 != 0:
            raise InvalidFontError('unknown font mode 0x%02X' % font_mode, file)

        glyph_count = 512 if font_mode & 0x01 != 0 else 256
        has_unicode = font_mode & 0x02 != 0
        has_unicode_seq = font_mode & 0x04 != 0

        if has_unicode_seq and not has_unicode:
            # The PSF v1 specification is not clear on this point: it
            # may be that these two flags are exclusive (ie, one OR the
            # other set but not both)
            raise InvalidFontError('font specifies sequences without '
                                   'Unicode table', file)

        glyph_bytesize = int.from_bytes(file.read(1), 'little', signed=False)
        if not MIN_HEIGHT <= glyph_bytesize <= MAX_HEIGHT:
            raise InvalidFontError('illegal font charsize %d' % glyph_bytesize,
                                   file)

        width = 8
        height = glyph_bytesize
        bytewidth = 1

    elif magic == b'\x72\xB5':
        # Process PSF v2 header
        result.version = 2

        if file.read(2) != b'\x4A\x86':
            raise InvalidFontError('not a PSF font file', file)

        font_version = int.from_bytes(file.read(4), 'little', signed=False)
        if font_version != 0:
            raise InvalidFontError('unknown font version %d' % font_version,
                                   file)

        header_size = int.from_bytes(file.read(4), 'little', signed=False)
        if header_size < 32:
            raise InvalidFontError('illegal font header size %d' % header_size,
                                   file)

        font_flags = int.from_bytes(file.read(4), 'little', signed=False)
        if font_flags & ~0x01 != 0:
            raise InvalidFontError('unknown font flags 0x%04X' % font_flags,
                                   file)

        has_unicode = font_flags & 0x01 != 0
        has_unicode_seq = True

        glyph_count = int.from_bytes(file.read(4), 'little', signed=False)
        if not MIN_GLYPH_COUNT <= glyph_count <= MAX_GLYPH_COUNT:
            raise InvalidFontError('illegal glyph count %d' % glyph_count, file)

        glyph_bytesize = int.from_bytes(file.read(4), 'little', signed=False)
        if not MIN_HEIGHT <= glyph_bytesize <= MAX_HEIGHT * (MAX_WIDTH + 7) // 8:
            raise InvalidFontError('illegal font charsize %d' % glyph_bytesize,
                                   file)

        height = int.from_bytes(file.read(4), 'little', signed=False)
        if not MIN_HEIGHT <= height <= MAX_HEIGHT:
            raise InvalidFontError('illegal font height %d' % height, file)

        width = int.from_bytes(file.read(4), 'little', signed=False)
        if not MIN_WIDTH <= width <= MAX_WIDTH:
            raise InvalidFontError('illegal font width %d' % width, file)

        bytewidth = (width + 7) // 8
        if not (MIN_WIDTH + 7) // 8 <= bytewidth <= (MAX_WIDTH + 7) // 8:
            raise InvalidFontError('illegal font width %d' % width, file)

        # Skip padding bytes in the header
        if header_size > 32:
            file.read(header_size - 32)

    else:
        raise InvalidFontError('not a PSF font file', file)

    # Read PSF glyph bitmaps

    for glyph_num in range(glyph_count):
        glyph = psffont.Glyph(width, height)

        glyph_data = file.read(glyph_bytesize)
        if len(glyph_data) != glyph_bytesize:
            raise InvalidFontError('could not read font glyph 0x%02X'
                                   % glyph_num, file)

        for row in range(height):
            # Glyphs are stored in the PSF font file with the top row
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

    # Read PSF Unicode mappings

    if has_unicode:
        for glyph_num in range(glyph_count):
            mappings = []
            in_seq = False
            new_seq = True

            if result.version == 1:
                # PSF v1 Unicode tables consist of two-byte integers
                while True:
                    val = int.from_bytes(file.read(2), 'little', signed=False)
                    if val == 0xFFFF:
                        # End of the Unicode table for this glyph
                        break
                    elif val == 0xFFFE:
                        # Start of a Unicode sequence
                        if has_unicode_seq:
                            in_seq = True
                            new_seq = True
                        else:
                            raise InvalidFontError('illegal start of Unicode '
                                                   'sequence in glyph 0x%02X'
                                                   % glyph_num, file)
                    else:
                        # val contains the start of a UTF-16 character
                        if 0x0000 <= val <= 0xD7FF \
                                or 0xE000 <= val <= 0xFFFD:
                            # BMP character: no more bytes need to be read
                            uni_val = val
                        elif 0xD800 <= val <= 0xDBFF:
                            # High surrogate character: read two more bytes
                            uni_val = 0x010000 + (val & 0x03FF) << 10
                            val2 = int.from_bytes(file.read(2), 'little',
                                                  signed=False)
                            if 0xDC00 <= val2 <= 0xDFFF:
                                uni_val += val2 & 0x03FF
                            else:
                                raise InvalidFontError('missing low surrogate '
                                                       'character in glyph '
                                                       '0x%02X' % glyph_num,
                                                       file)
                        elif 0xDC00 <= val <= 0xDFFF:
                            # Low surrogate character
                            raise InvalidFontError('illegal low surrogate '
                                                   'character in glyph 0x%02X'
                                                   % glyph_num, file)
                        else:
                            raise InvalidFontError('illegal character in glyph '
                                                   '0x%02X' % glyph_num, file)

                        # uni_val now contains a full Unicode code point
                        if not in_seq or new_seq:
                            mappings.append(chr(uni_val))
                            new_seq = False
                        else:
                            mappings[len(mappings) - 1] += chr(uni_val)

            elif result.version == 2:
                # PSF v2 Unicode tables consist of UTF-8 strings
                while True:
                    val = int.from_bytes(file.read(1), 'little', signed=False)
                    if val == 0xFF:
                        # End of the Unicode table for this glyph
                        break
                    elif val == 0xFE:
                        # Start of a Unicode sequence
                        if has_unicode_seq:
                            in_seq = True
                            new_seq = True
                        else:
                            raise InvalidFontError('illegal start of Unicode '
                                                   'sequence in glyph 0x%02X'
                                                   % glyph_num, file)
                    else:
                        # val contains the start of an ordinary UTF-8 character
                        if 0x00 <= val <= 0x7F:
                            # ASCII character: no more bytes need to be read
                            uni_bytes = bytearray([val])
                        elif 0xC2 <= val <= 0xDF:
                            # Start of two-byte UTF-8 character: read one more byte
                            uni_bytes = bytearray([val])
                            uni_bytes.extend(file.read(1))
                        elif 0xE0 <= val <= 0xEF:
                            # Start of three-byte UTF-8 character: read two bytes
                            uni_bytes = bytearray([val])
                            uni_bytes.extend(file.read(2))
                        elif 0xF0 <= val <= 0xF4:
                            # Start of four-byte UTF-8 character: read three bytes
                            uni_bytes = bytearray([val])
                            uni_bytes.extend(file.read(3))
                        elif 0x80 <= val <= 0xBF:
                            # UTF-8 continuation byte
                            raise UnicodeDecodeError('utf-8', bytes([val]), 0, 1,
                                                     'illegal UTF-8 continuation byte')
                        else:
                            # Illegal UTF-8 initial byte
                            raise UnicodeDecodeError('utf-8', bytes([val]), 0, 1,
                                                     'illegal UTF-8 initial byte')

                        # uni_bytes now contains a full UTF-8 character
                        uni_str = uni_bytes.decode(encoding='utf-8')
                        if not in_seq or new_seq:
                            mappings.append(uni_str)
                            new_seq = False
                        else:
                            mappings[len(mappings) - 1] += uni_str

            else:
                raise InvalidFontError('unknown font version %d'
                                       % result.version, file)

            result[glyph_num].unicode_mapping = mappings

    return result


#########################################################################
# writefont function

def writefont(font, file, strict=True):
    """Write a `psffont.Font` object out to a binary PSF font file.

    This function writes the `font` `psffont.Font` object to `file`,
    which must be a file or file-like object already open for binary
    writing (mode ``'wb'``).

    Note that `font` must be minimally valid: all glyphs must be present
    (not missing).  In addition, if `strict` is ``True`` (the default),
    if any glyph has a Unicode mapping, then all glyphs must have a
    Unicode mapping, no Unicode mapping may overlap, and all
    single-character mappings must appear before multi-character
    sequences.  If these conditions are not met, the `InvalidFontError`
    exception is raised.
    """

    if isinstance(file, str):
        file = open(file, 'wb')

    allow = not strict
    psffont.check(font, allow_missing_glyphs=False,
                  allow_missing_mappings=allow,
                  allow_overlapping_mappings=allow,
                  allow_out_of_order_mappings=allow,
                  allow_gt_max_glyph_count_strict=allow)

    width = font.width
    height = font.height
    count = font.count()

    if font.version:
        version = font.version
        if version == 1 and font.calculate_version() != 1:
            raise InvalidFontError('cannot be a version 1 font')
    else:
        version = font.calculate_version()

    all_mappings = font.get_all_mappings()
    if all_mappings:
        has_unicode = True

        # Check if any Unicode mapping is a multi-character sequence
        has_unicode_seq = False
        for mapping in all_mappings:
            if len(mapping) > 1:
                has_unicode_seq = True
                break
    else:
        has_unicode = False
        has_unicode_seq = False

    # Write PSF header

    if version == 1:
        file.write(b'\x36\x04')            # PSF v1 magic bytes

        font_mode = 0x00
        if count == 512:
            font_mode |= 0x01
        if has_unicode:
            font_mode |= 0x02
        if has_unicode_seq:
            # The PSF v1 specification is not clear on this point: it
            # may be that the has_unicode and has_unicode_seq flags are
            # exclusive (ie, one OR the other set but not both)
            font_mode |= 0x04

        bytewidth = 1
        bytesize = height

        file.write(font_mode.to_bytes(1, 'little', signed=False))
        file.write(bytesize.to_bytes(1, 'little', signed=False))

    elif version == 2:
        file.write(b'\x72\xB5\x4A\x86')    # PSF v2 magic bytes
        file.write(int(0).to_bytes(4, 'little', signed=False))   # v2 version
        file.write(int(32).to_bytes(4, 'little', signed=False))  # headersize

        font_flags = 0x00000000
        if has_unicode:
            font_flags |= 0x00000001

        bytewidth = (width + 7) // 8
        bytesize = height * bytewidth

        file.write(font_flags.to_bytes(4, 'little', signed=False))
        file.write(count.to_bytes(4, 'little', signed=False))
        file.write(bytesize.to_bytes(4, 'little', signed=False))
        file.write(height.to_bytes(4, 'little', signed=False))
        file.write(width.to_bytes(4, 'little', signed=False))

    else:
        raise InvalidFontError('unknown font version %d' % version)

    # Write PSF glyph bitmaps

    for glyph_num in range(count):
        glyph_vals = font[glyph_num]
        glyph_data = bytearray(bytesize)

        for row in range(height):
            # Glyphs are stored in the PSF font file with the top row
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

    # Write PSF Unicode mappings

    if has_unicode:
        for glyph_num in range(count):
            mappings = font[glyph_num].unicode_mapping
            in_seq = False

            if version == 1:
                if mappings:
                    for mapping in mappings:
                        if in_seq or len(mapping) != 1:
                            file.write(int(0xFFFE).to_bytes(2, 'little',
                                                            signed=False))
                            in_seq = True
                        file.write(mapping.encode('utf-16le'))
                file.write(int(0xFFFF).to_bytes(2, 'little', signed=False))

            elif version == 2:
                if mappings:
                    for mapping in mappings:
                        if in_seq or len(mapping) != 1:
                            file.write(b'\xFE')
                            in_seq = True
                        file.write(mapping.encode('utf-8'))
                file.write(b'\xFF')

            else:
                raise InvalidFontError('unknown font version %d' % version)


#########################################################################
