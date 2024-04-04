#########################################################################
#                                                                       #
#              Input/Output Functions for PSFTX Text Files              #
#                 Copyright (C) 2004-24, John Zaitseff                  #
#                                                                       #
#########################################################################

# Author: John Zaitseff <J.Zaitseff@zap.org.au>

# This module contains functions to read and write PSFTX text files to
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


"""Input/Output Functions for PSFTX Text Files.

The `psftxio` module contains functions to read and write PSFTX text
files to and from `psffont.Font` objects.  PSFTX files are used as text
representations of Linux console fonts, both version 1 and 2.

This module contains the following public functions:

* `readfont()`  - Read a PSF font file into a `psffont.Font` object
* `writefont()` - Write a `psffont.Font` object out to a PSF font file


Format of PSFTX text files
==========================

The PSFTX text file representation allows you to create Linux console
fonts using nothing more than a simple text editor.  The format is quite
simple.

1.  A font must contain between 1 and 4096 glyphs.  Glyphs are numbered
    starting from zero.

2.  Anything following a ``#`` is ignored to the end of that line.  This
    allows you to document your text file with comments.  For example::

        # This is a comment

3.  Spaces and tabs at the start or end of lines are ignored, as are
    blank lines.  This allows you to indent glyph representations as you
    like.

4.  All keywords may appear in either uppercase or lowercase.

5.  Non-comment/non-blank lines that appear before any glyphs are defined
    are called header lines.  Two such header lines exist: ``PSFTX FONT
    VERSION`` and ``VGAFONT``; both are optional.

6.  The optional ``PSFTX FONT VERSION`` header line specifies the desired
    font version, either 1 or 2.  For example::

        PSFTX FONT VERSION 1

    Version 1 fonts must contain either 256 or 512 glyphs and must be 8
    pixels wide.  Version 2 fonts may contain between 1 and 4096 glyphs
    inclusive and may have a font width that is not 8 pixels wide.  Note
    that the Linux console will not load fonts with more than 512 glyphs
    in it, whichever font version is specified.

    If this line is not present, version 1 fonts will be generated if
    possible, otherwise version 2 fonts will be generated.

7.  The optional ``VGAFONT`` header line specifies a font 8 pixels wide
    that is to be displayed on a VGA text console with cell width 9.  See
    item 15 for additional details.

8.  Each glyph must begin with ``GLYPH`` followed by its glyph number in
    decimal or hexadecimal, and must end with ``ENDGLYPH``.  For
    example::

        GLYPH 0x20
        ...
        ENDGLYPH

9.  Although glyphs do not have to be listed in glyph number order, no
    glyph may be missing (not present) in a valid font.  For example, it
    is illegal to have a font with glyphs 0x00 to 0x1F and 0x21 to 0xFF,
    but miss out glyph 0x20.

10. The glyph itself is represented by consecutive lines of characters
    containing ``.`` for unlit (unset) pixels and ``X`` for lit (set)
    pixels.  For example::

        ..XX....
        .XXXX...
        XX..XX..
        XX..XX..
        XXXXXX..
        XX..XX..
        XX..XX..
        ........

11. The width of the font is determined by the number of ``.`` and ``X``
    characters in the first line of the first glyph's representation.
    The above example shows a font 8 pixels wide.

12. The height of the font is determined by the number of lines in the
    first glyph's representation.  The above example shows a font 8
    pixels high.

13. Each glyph must be between 1 and 32 pixels (inclusive) wide and
    between 1 and 32 pixels (inclusive) high.  Version 1 fonts must be 8
    pixels wide.

14. All glyphs in the font must have the same width and height.

15. If the ``VGAFONT`` keyword is given (see item 7), an optional ninth
    column may be present in the glyph representation of an 8-pixel-wide
    font.  This makes it easier to design VGA text mode fonts, which
    display a font 8 pixels wide in a 9-pixel character cell.

    In such cases, the ninth column must be ``.`` for glyphs 0x00 to
    0xBF, 0xE0 to 0xFF, 0x100 to 0x1BF and 0x1E0 to 0x1FF.  For glyphs
    0xC0 to 0xDF and 0x1C0 to 0x1DF, the ninth column must be the same as
    the eighth column.  This restriction is due to the way VGA adapters
    treat text mode fonts.

    When designing your font, please note that non-text-mode consoles
    (using framebuffer drivers) ignore the ninth column entirely.  In
    other words, you should design your font to display correctly in both
    VGA text mode and in console framebuffers.  Hence, an 8x16 pixel font
    is displayed in a 9x16 character cell in VGA text mode and in an 8x16
    character cell in console framebuffers.

16. The Unicode character mapping for a glyph can be specified by listing
    the Unicode codepoints in the hexadecimal format ``U+xxxx`` within a
    glyph's ``GLYPH`` and ``ENDGLYPH``.  Multiple codepoints may be
    specified, each on its own line.  The mappings may appear anywhere
    within the ``GLYPH``/\ ``ENDGLYPH`` pair, but are usually listed
    before the glyph representation.  For example::

        GLYPH 0x4B
            U+004B
            U+212A
            ...
        ENDGLYPH

    Note that the glyph number (0x4B in this example) does not need to
    match the first Unicode mapping (U+004B in this example).

17. A mapping may contain sequences of Unicode characters, particularly
    for combining sequences.  Each such sequence must start with ``SEQ``
    followed by the relevant Unicode codepoints on the same line.
    Sequences must appear after all single-character mappings.  For
    example::

        GLYPH 0x10
            U+00C4             # LATIN CAPITAL LETTER A WITH DIAERESIS
            SEQ U+0041 U+0308  # LATIN CAPITAL LETTER A + COMBINING DIAERESIS
            ...
        ENDGLYPH

    Multiple Unicode sequences may appear in the glyph, one after the
    other.

18. If even one glyph has a Unicode character mapping associated with it,
    then every glyph must have a mapping for the font to be valid.

19. Unicode mappings may not overlap.  For example, if glyph 0x10 is
    mapped to U+00C4, no other glyph may list U+00C4 in its mapping.

A complete example of an 8x8 glyph as it might appear in the text file
representation::

    GLYPH 0x41

        U+0041     # LATIN CAPITAL LETTER A

            ..XX....
            .XXXX...
            XX..XX..
            XX..XX..
            XXXXXX..
            XX..XX..
            XX..XX..
            ........

    ENDGLYPH
"""


__version__ = '2.4'
__author__ = 'John Zaitseff <J.Zaitseff@zap.org.au>'


import sys

import psffont
from psffont import InvalidFontError, MIN_WIDTH, MAX_WIDTH, \
     MIN_HEIGHT, MAX_HEIGHT, MIN_GLYPH_COUNT, MAX_GLYPH_COUNT
import unicustom


#########################################################################
# readfont function

def readfont(file, strict=True):
    """Read a PSFTX text representation and return a `psffont.Font` object.

    This function reads the contents of `file`, a file or file-like
    object already open for text reading (mode ``'r'``), and returns a
    `psffont.Font` object.

    Note that the PSFTX file must be minimally valid: the file must be
    syntactically correct, and all glyphs must have the same width and
    height.

    If `strict` is ``True`` (the default), all glyphs must be present
    (not missing), and if any glyph has a Unicode mapping, then all
    glyphs must have a Unicode mapping.  In addition, no Unicode mappings
    may overlap, and all single-character mappings must appear before
    multi-character sequences.  If these conditions are not met, the
    `InvalidFontError` exception is raised.  If `strict` is ``False``,
    these particular errors are not checked and the `psffont.Font` object
    returned may not be a valid PSF font.
    """

    result = psffont.Font()

    width = None                          # width is 8 for a VGA font
    height = None
    vga = False

    # PSFTX readfont state machine variables

    line_num = 0
    in_header = True
    in_glyph = False
    tokens = None

    glyph_num = None
    scanlines = []
    mappings = []

    # PSFTX readfont state machine functions

    def parse_version():
        """Parse ``PSFTX FONT VERSION`` *num* statement."""
        nonlocal file, result
        nonlocal line_num, in_header, tokens

        if not in_header:
            raise InvalidFontError('PSFTX FONT VERSION must appear before '
                                   'glyph definitions', file, line_num)
        if result.version:
            raise InvalidFontError('redefinition of font version', file, line_num)

        if tokens[3] == '1':
            result.version = 1
        elif tokens[3] == '2':
            result.version = 2
        else:
            raise InvalidFontError('unknown font version %s' % tokens[3],
                                   file, line_num)

    def parse_vga():
        """Parse ``VGAFONT`` statement."""
        nonlocal file, vga
        nonlocal line_num, in_header, tokens

        if len(tokens) != 1:
            raise InvalidFontError('VGAFONT has no arguments', file, line_num)
        if not in_header:
            raise InvalidFontError('VGAFONT must appear before glyph '
                                   'definitions', file, line_num)

        vga = True

    def parse_glyph():
        """Parse ``GLYPH`` *num* statement."""
        nonlocal file, result
        nonlocal line_num, in_header, in_glyph, tokens
        nonlocal glyph_num, scanlines, mappings

        if len(tokens) != 2:
            raise InvalidFontError('GLYPH must be followed by a number only',
                                   file, line_num)
        if in_glyph:
            raise InvalidFontError('missing ENDGLYPH', file, line_num)

        try:
            glyph_num = int(tokens[1], base=0)
        except ValueError:
            raise InvalidFontError('malformed glyph number: %s' % tokens[1],
                                   file, line_num)

        if not MIN_GLYPH_COUNT - 1 <= glyph_num <= MAX_GLYPH_COUNT - 1:
            raise InvalidFontError('glyph number %d is not in range %d..%d'
                                   % (glyph_num, MIN_GLYPH_COUNT - 1,
                                      MAX_GLYPH_COUNT - 1), file, line_num)

        if result.get(glyph_num):
            raise InvalidFontError('glyph 0x%02X already defined' % glyph_num,
                                   file, line_num)

        # Prepare for the new glyph; glyph_num contains the glyph number

        in_header = False
        in_glyph = True
        scanlines = []
        mappings = []

    def parse_endglyph():
        """Parse ``ENDGLYPH`` statement."""
        nonlocal file, result, width, height, vga
        nonlocal line_num, in_glyph, tokens
        nonlocal glyph_num, scanlines, mappings

        if len(tokens) != 1:
            raise InvalidFontError('ENDGLYPH has no arguments', file, line_num)
        if not in_glyph:
            raise InvalidFontError('missing GLYPH', file, line_num)

        if not height:
            # Font height is only set at the end of the first glyph
            height = len(scanlines)
            if not MIN_HEIGHT <= height <= MAX_HEIGHT:
                raise InvalidFontError('glyph height of %d is not in range %d..%d'
                                       % (height, MIN_HEIGHT, MAX_HEIGHT),
                                       file, line_num)
        elif len(scanlines) != height:
            raise InvalidFontError('glyph height should be %d, not %d'
                                   % (height, len(scanlines)), file, line_num)

        # Store the glyph

        glyph = psffont.Glyph(width, height)
        for scan_row in range(height):
            # Convert the stored scanlines into a glyph
            offset = height - scan_row - 1
            glyph[offset] = [0 if scanlines[scan_row][x] == '.' else 1 \
                             for x in range(width)]
        glyph.unicode_mapping = mappings

        result[glyph_num] = glyph
        in_glyph = False

    def parse_scanline():
        """Parse a glyph representation scanline (a line of ``.``s and ``X``s)."""
        nonlocal file, width, vga
        nonlocal line_num, in_glyph, tokens
        nonlocal glyph_num, scanlines

        if not in_glyph:
            raise InvalidFontError('missing GLYPH', file, line_num)

        tok_len = len(tokens[0])

        if not width:
            # Font width is only set on first scanline
            width = tok_len
            if not MIN_WIDTH <= width <= MAX_WIDTH:
                raise InvalidFontError('glyph width of %d is not in range %d..%d'
                                       % (width, MIN_WIDTH, MAX_WIDTH),
                                       file, line_num)
            if vga:
                if width != 8 and width != 9:
                    raise InvalidFontError('glyph width must be 8 or 9, not '
                                           '%d, for a VGA font' % width,
                                           file, line_num)
                else:
                    width = 8
        elif not vga and tok_len != width \
                or vga and tok_len != 8 and tok_len != 9:
            raise InvalidFontError('glyph width should be %d, not %d'
                                   % (width, tok_len), file, line_num)

        if vga and tok_len == 9:
            # Handle the optional ninth column
            if 0xC0 <= glyph_num <= 0xDF \
                    or 0x1C0 <= glyph_num <= 0x1DF:
                if tokens[0][7] != tokens[0][8]:
                    raise InvalidFontError("9th column value of '%s' must be "
                                           'the same as the 8th column'
                                           % tokens[0][8], file, line_num)
            else:
                if tokens[0][8] != '.':
                    raise InvalidFontError("9th column value must be '.'",
                                           file, line_num)
            tokens[0] = tokens[0][0:8]

        # Store the scanline until ENDGLYPH
        scanlines.append(tokens[0])

    def unicode_val(val):
        """Check that Unicode code point `val` is valid and return as an int."""
        nonlocal file, line_num

        if not val.startswith('U+'):
            raise InvalidFontError("Unicode code point '%s' must start with U+"
                                   % val, file, line_num)

        try:
            result = int(val[2:], base=16)
        except ValueError:
            raise InvalidFontError('malformed Unicode code point %s' % val,
                                   file, line_num)

        if result < 0 or result > 0x10FFFF \
                or result & 0xFFFF == 0xFFFE or result & 0xFFFF == 0xFFFF \
                or 0xD800 <= result <= 0xDFFF:
            raise InvalidFontError('illegal Unicode code point %s' % val,
                                   file, line_num)

        return result

    def parse_mapping():
        """Parse ``U+``\ *nnnn* statement."""
        nonlocal file
        nonlocal line_num, in_glyph, tokens
        nonlocal glyph_num, mappings

        if len(tokens) != 1:
            raise InvalidFontError('Unicode mapping has no arguments',
                                   file, line_num)
        if not in_glyph:
            raise InvalidFontError('missing GLYPH', file, line_num)

        uni_val = unicode_val(tokens[0])
        mappings.append(chr(uni_val))

    def parse_seq():
        """Parse ``SEQ U+``\ *nnnn* [\ ``U+``\ *nnnn* ...] statement."""
        nonlocal file
        nonlocal line_num, in_glyph, tokens
        nonlocal glyph_num, mappings

        if len(tokens) < 2:
            raise InvalidFontError('SEQ must have at least one argument',
                                   file, line_num)
        if not in_glyph:
            raise InvalidFontError('missing GLYPH', file, line_num)

        uni_str = ''
        for val in tokens[1:]:
            uni_str += chr(unicode_val(val))
        mappings.append(uni_str)


    # Process the PSFTX file line by line

    for (line_num, line) in enumerate(file, 1):
        # Tokenise the line: remove comments, skip blank lines, make uppercase
        line = line.partition('#')[0]
        tokens = line.upper().split()
        if not tokens:
            continue

        if tokens[0:3] == ['PSFTX', 'FONT', 'VERSION']:
            parse_version()
        elif tokens[0] == 'VGAFONT':
            parse_vga()
        elif tokens[0] == 'GLYPH':
            parse_glyph()
        elif tokens[0] == 'ENDGLYPH':
            parse_endglyph()
        elif len(tokens) == 1 and set(tokens[0]) <= {'.', 'X'}:
            parse_scanline()
        elif tokens[0].startswith('U+'):
            parse_mapping()
        elif tokens[0] == 'SEQ':
            parse_seq()
        else:
            raise InvalidFontError('unknown token %s' % tokens[0], file, line_num)

    if result.version:
        if result.version == 1 and result.calculate_version() != 1:
            raise InvalidFontError('cannot be a version 1 font', file)

    if strict:
        psffont.check(result)
    return result


#########################################################################
# writefont function

def writefont(font, file=sys.stdout, strict=True, vga=False,
              title=None, name=None):
    """Write a `psffont.Font` object out to a PSFTX text file.

    This function writes the `font` `psffont.Font` object to `file`,
    which must be a file or file-like object already open for text
    writing (mode ``'w'``), by default ``sys.stdout``.

    If `strict` is ``True`` (the default), the `psffont.Font` object must
    be a valid PSF font: all glyphs must be present (not missing) in the
    font, and if any glyph has a Unicode mapping, then all glyphs must
    have a Unicode mapping; any such mappings may not overlap, and all
    single-character mappings must appear before multi-character
    sequences.  If these conditions are not met, the `InvalidFontError`
    exception is raised.  If `strict` is ``False``, no errors are raised,
    and the output file may be invalid.

    If `vga` is True, and the font is 8 pixels wide, a ninth column is
    printed for every glyph to help with the design of VGA text-mode
    fonts.  VGA text modes display 8-pixel wide fonts in a 9-pixel wide
    cell: the ninth column is blank except for glyphs 0xC0 to 0xDF and
    0x1C0 to 0x1DF, in which case the ninth column replicates the eighth.

    `title` is written out as a comment on the first line of file.
    `name` is written out as a comment on the second line.
    """

    width = font.width
    height = font.height
    count = font.count()
    hgn = font.highest_glyph_number()

    version = font.version if font.version else font.calculate_version()

    if width != 8:
        vga = False

    if strict:
        psffont.check(font)

    # Print out the PSFTX header

    if title:
        print('# %s' % title, '#', sep='\n', file=file)
    if name:
        print('# Name:   %s' % name, file=file)

    print('# Size:   %d x %d pixels' % (width, height),
          ' (VGA font)' if vga else '', sep='', file=file)
    print('# Glyphs: %d' % (hgn + 1),
          ' (%d missing)' % (hgn + 1 - count) if count != hgn + 1 else '',
          sep='', file=file)

    print('\n\n', 'PSFTX FONT VERSION %d' % version, sep='', file=file)
    if vga:
        print('VGAFONT', file=file)

    # Print out each glyph

    glyph_format = '0x%02X' if hgn < 256 else '0x%03X'

    for glyph_num in range(hgn + 1):
        glyph = font.get(glyph_num)
        if glyph:
            print('\n\n', 'GLYPH ', glyph_format % glyph_num, '\n', sep='',
                  file=file)

            mappings = glyph.unicode_mapping
            if mappings:
                for mapping in mappings:
                    if len(mapping) == 1:
                        print('    U+%04X\t\t# %s' %
                              (ord(mapping), unicustom.name(mapping)), file=file)
                    else:
                        print('    SEQ', *['U+%04X' % ord(c) for c in mapping],
                              sep=' ', file=file)
                        print(*['\t\t\t# %s' % unicustom.name(c)
                                for c in mapping], sep='\n', file=file)
                print('', file=file)

            glyph_strs = glyph.str('.X').split('\n')
            for line in glyph_strs:
                if vga:
                    if 0xC0 <= glyph_num <= 0xDF \
                            or 0x1C0 <= glyph_num <= 0x1DF:
                        # In VGA fonts, glyphs in this range repeat the
                        # 8th bit
                        line += line[width - 1]
                    else:
                        # Outside the designated range, the 9th bit is
                        # always unset
                        line += '.'
                print('\t%s' % line, file=file)

            print('\n', 'ENDGLYPH', sep='', file=file)


#########################################################################
