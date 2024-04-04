#########################################################################
#                                                                       #
#          Object-oriented interface to an in-memory PSF font           #
#                 Copyright (C) 2004-24, John Zaitseff                  #
#                                                                       #
#########################################################################

# Author: John Zaitseff <J.Zaitseff@zap.org.au>

# This module contains an object-oriented interface to the in-memory
# description of a PSF font.
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


"""Object-oriented interface to an in-memory PSF font.

The `psffont` module contains an object-oriented interface to the
in-memory description of a PSF font.  PSF font files are used to provide
fonts to the Linux console and contain from 1 to 4096 glyphs, each of
which may be from 1 to 32 pixels wide and from 1 to 32 pixels high.
Glyphs may have Unicode translation tables associated with them; these
tables map Unicode characters or Unicode character sequences to glyphs.
Note that currently the Linux console will not load fonts with more than
512 glyphs in it.

This module contains the following public classes:

* `Font`  - An indexable collection of `Glyph` objects.
* `Glyph` - An individual PSF glyph: glyph data and Unicode mapping.

* `InvalidFontError` - Exception raised when checking `Font` objects.

The following functions are available:

* `check()` - Check a `Font` object for correctness

The following constants are exported:

* `MIN_WIDTH`              - Minimum width of a glyph
* `MAX_WIDTH`              - Maximum width of a glyph
* `MIN_HEIGHT`             - Minimum height of a glyph
* `MAX_HEIGHT`             - Maximum height of a glyph
* `MIN_GLYPH_COUNT`        - Minimum number of glyphs in a font
* `MAX_GLYPH_COUNT`        - Maximum number of glyhps in a font
* `MAX_GLYPH_COUNT_STRICT` - Strict maximum number of glyhps in a font
"""


__version__ = '2.5'
__author__ = 'John Zaitseff <J.Zaitseff@zap.org.au>'

__all__ = [
    'Glyph',
    'Font',
    'InvalidFontError',
    'check',
    'MIN_WIDTH',
    'MAX_WIDTH',
    'MIN_HEIGHT',
    'MAX_HEIGHT',
    'MIN_GLYPH_COUNT',
    'MAX_GLYPH_COUNT',
    'MAX_GLYPH_COUNT_STRICT',
]


from collections.abc import Mapping as _Mapping


#########################################################################
# Global constants

MIN_WIDTH = 1
MAX_WIDTH = 32
MIN_HEIGHT = 1
MAX_HEIGHT = 32
MIN_GLYPH_COUNT = 1
MAX_GLYPH_COUNT = 4096
MAX_GLYPH_COUNT_STRICT = 512


#########################################################################
# InvalidFontError exception

class InvalidFontError(Exception):
    """Invalid font."""

    def __init__(self, msg, file=None, line=None):
        """Initialise the `InvalidFontError` exception.

        `msg` contains the message string to pass to the base constructor.
        `file` contains either a file-like object with a `name` attribute,
        or a string with the filename.  `line` contains the line number of
        the relevant file.
        """

        name = getattr(file, 'name', file)
        msgstr = '%s' % msg
        if name:
            msgstr += ', in file %s' % name
        if line:
            msgstr += ', on line %s' % line
        super().__init__(msgstr)


#########################################################################
# Glyph class

class Glyph:
    """An individual PSF glyph, composed of glyph data and a Unicode mapping.

    Instances of the `Glyph` class represent an individual PSF font
    glyph.  Each glyph contains glyph data of size width x height pixels,
    as well as an optional Unicode mapping table unicode_mapping.
    """

    def __init__(self, width, height, glyph_data=None, unicode_mapping=None):
        r"""Create a glyph `width` x `height` pixels in size.

        Note that `width` must be between `MIN_WIDTH` and `MAX_WIDTH`
        inclusive and `height` must be between `MIN_HEIGHT` and
        `MAX_HEIGHT` inclusive, otherwise a `ValueError` exception is
        raised.

        `glyph_data` is a two-dimensional array of 0s and 1s stored in
        [row][column] format, with the zeroth row at the bottom of the
        glyph and the zeroth column on the left hand side.

        `unicode_mapping` contains a list of Unicode strings which map to
        this glyph.  Single-character strings in that list are direct
        mappings; multi-character strings represent combining sequences.
        For example, a mapping to the glyph 0x40 might be ``['@']``, the
        single mapping for U+0040 COMMERCIAL AT, whereas glyph 0x20 might
        include ``['\u0020', '\u00A0', '\u2000', ...]``, multiple
        mappings to the same glyph.  A mapping to the glyph for 'Latin
        capital letter A with grave' might be ``['\u00C0', 'A\u0300']``,
        where the second string (of length 2) is the combining sequence
        U+0041 LATIN CAPITAL LETTER A followed by U+0300 COMBINING GRAVE
        ACCENT.  Note that Unicode sequences (ie, strings of length > 1)
        *must* appear after all direct mappings (single-character
        strings).
        """

        if not MIN_WIDTH <= width <= MAX_WIDTH:
            raise ValueError('width %d is not in range %d..%d' %
                             (width, MIN_WIDTH, MAX_WIDTH))
        if not MIN_HEIGHT <= height <= MAX_HEIGHT:
            raise ValueError('height %d is not in range %d..%d' %
                             (height, MIN_HEIGHT, MAX_HEIGHT))

        self._width = width
        self._height = height

        self._glyph_data = []
        if glyph_data:
            for y in range(height):
                self._glyph_data.append([1 if glyph_data[y][x] else 0 \
                                             for x in range(width)])
        else:
            for y in range(height):
                self._glyph_data.append([0 for x in range(width)])

        if unicode_mapping:
            self._unicode_mapping = unicode_mapping[:]
        else:
            self._unicode_mapping = None


    def __repr__(self):
        """g.__repr__() <==> repr(g)"""
        return '%s(%d, %d, %s, %s)' % (
            type(self).__name__,
            self._width,
            self._height,
            repr(self._glyph_data),
            repr(self._unicode_mapping))

    def __str__(self):
        """g.__str__() <==> str(g) <==> g.str()"""
        return self.str()

    def str(self, vals='.X'):
        r"""Return a string representation of the glyph pixel data.

        Each row of the glyph is represented by a sequence of characters
        from `vals`, a string two characters long: any pixel set to 0
        uses ``vals[0]``, any pixel set to 1 uses ``vals[1]``.  Each
        glyph row is separated from the next by ``'\n'``.  The last row
        in the string is actually the zeroth (bottom) row in the glyph
        data.
        """

        result = []
        for y in range(self._height - 1, -1, -1):
            result.append(''.join(
                [vals[self._glyph_data[y][x]] for x in range(self._width)]))
        return '\n'.join(result)

    @property
    def width(self):
        """The width of the glyph in pixels."""
        return self._width

    @property
    def height(self):
        """The height of the glyph in pixels."""
        return self._height

    def __getitem__(self, key):
        """g.__getitem__(key) <==> g[key]

        If `key` is an integer, return the corresponding glyph data for
        the `key`\-th row as a list of `g.width` 0s and 1s.  Note that
        the zeroth row is at the bottom of the glyph.

        If `key` is a tuple (`x`, `y`), return the value of the pixel,
        either 0 or 1, at row `y`, column `x`, where the zeroth row is at
        the bottom of the glyph and the zeroth column is on the left hand
        side.
        """

        if isinstance(key, int):
            # Index 'key' is a glyph row index
            if not 0 <= key < self._height:
                raise IndexError('row index out of range')

            return self._glyph_data[key][:]

        else:
            # Index 'key' should be a (column, row) tuple
            (x, y) = key

            if not 0 <= x < self._width:
                raise IndexError('x index out of range')
            if not 0 <= y < self._height:
                raise IndexError('y index out of range')

            return self._glyph_data[y][x]

    def __setitem__(self, key, value):
        """g.__setitem__(key, value) <==> g[key] = value

        If `key` is an integer, set the corresponding glyph data to
        `value`.  Note that `value` must be a list of `g.width` integers,
        either 0s or 1s.  ``value[0]`` represents the left-most pixel in
        the key-th row.

        If `key` is a tuple (`x`, `y`), set the corresponding pixel at
        row `y`, column `x` to value, which must be the integer 0 or 1.
        The zeroth row is at the bottom of the glyph and the zeroth
        column is on the left hand side.
        """

        if isinstance(key, int):
            # Index 'key' is a glyph row index
            if not 0 <= key < self._height:
                raise IndexError('row index out of range')

            for x in range(self._width):
                self._glyph_data[key][x] = 1 if value[x] else 0

        else:
            # Index 'key' should be a (column, row) tuple
            (x, y) = key

            if not 0 <= x < self._width:
                raise IndexError('x index out of range')
            if not 0 <= y < self._height:
                raise IndexError('y index out of range')

            self._glyph_data[y][x] = 1 if value else 0

    @property
    def array(self):
        """Return or set the glyph data as a two-dimensional array.

        The value to be assigned to this property must contain a
        two-dimensional array of 0s and 1s stored in [row][column]
        format, with the zeroth row at the bottom of the glyph and the
        zeroth column on the left hand side.

        Reading this property returns a *copy* of the glyph data, not the
        glyph data itself.  This means something like the following will
        *not* work: ``g.array[0][0] = 0``.  Instead, use ``g[0,0] = 0``.
        """
        return [self._glyph_data[y][:] for y in range(self._height)]

    @array.setter
    def array(self, value):
        for y in range(self._height):
            for x in range(self._width):
                self._glyph_data[y][x] = 1 if value[y][x] else 0

    @property
    def unicode_mapping(self):
        r"""Return or set the Unicode mapping table as a list of strings.

        The value to be assigned to this property must contain either
        ``None`` (to remove any Unicode mappings) or a non-empty list of
        Unicode strings that map to this glyph.  Single-character
        strings in that list are direct mappings; multi-character
        strings represent combining sequences.

        For example, a mapping to the glyph 0x40 might be ``['@']``, the
        single mapping for U+0040 COMMERCIAL AT, whereas glyph 0x20 might
        include ``['\u0020', '\u00A0', '\u2000', ...]``, multiple
        mappings to the same glyph.  A mapping to the glyph for 'Latin
        capital letter A with grave' might be ``['\u00C0', 'A\u0300']``,
        where the second string (of length 2) is the combining sequence
        U+0041 LATIN CAPITAL LETTER A followed by U+0300 COMBINING GRAVE
        ACCENT.

        Note that Unicode sequences (ie, strings of length > 1) must
        appear after all direct mappings (single-character strings),
        although this is only checked by `psffont.check()`.
        """
        return self._unicode_mapping

    @unicode_mapping.setter
    def unicode_mapping(self, value):
        if value:
            self._unicode_mapping = value
        else:
            self._unicode_mapping = None

    def has_unicode_mapping(self):
        """Return True if a Unicode mapping is present."""
        return True if self._unicode_mapping else False


#########################################################################
# Font class

class Font(dict):
    """An indexable collection of `Glyph` objects.

    Instances of the `Font` class represent a collection of PSF glyphs: a
    complete PSF font.  Each glyph is indexed by its glyph number, an
    integer from 0 to `MAX_GLYPH_COUNT` - 1.  The width and height of the
    font is set by the first glyph assigned to the Font object: all
    subsequent glyphs added must have the same width and height.

    The `Font` class is essentially a subclass of the `dict` type, with
    the following additional properties and methods:

    * `width`                     - Font width in pixels
    * `height`                    - Font height in pixels
    * `version`                   - PSF font version

    * `count`                     - The actual number of glyphs in the font
    * `highest_glyph_number`      - The highest glyph number in the font
    * `calculate_version`         - Calculate the PSF font version
    * `has_unicode_mapping`       - Return True if any glyph has a mapping
    * `get_missing_glyphs`        - Return a list of missing glyph numbers
    * `get_missing_mappings`      - Return a list of missing mappings
    * `get_all_mappings`          - Return all Unicode mappings
    * `get_overlapping_mappings`  - Return overlapping Unicode mappings
    * `get_out_of_order_mappings` - Return out-of-order mappings
    """

    def __init__(self, opt=None, **kwargs):
        """Initialise the `Font` object."""

        super().__init__()
        self._width = None
        self._height = None
        self._version = None
        self.update(opt, **kwargs)

    def __getitem__(self, key):
        """f.__getitem__(key) <==> f[key]

        `key` must be an integer between 0 and `MAX_GLYPH_COUNT` - 1.
        """

        if not isinstance(key, int):
            raise TypeError('font index must be an integer, not %s' % type(key))
        if not 0 <= key < MAX_GLYPH_COUNT:
            raise IndexError('font index must be in the range 0..%d' %
                             (MAX_GLYPH_COUNT - 1))

        return super().__getitem__(key)

    def __setitem__(self, key, value):
        """f.__setitem__(key, value) <==> f[key] = value

        `key` must be an integer between 0 and `MAX_GLYPH_COUNT` - 1.
        """

        if not isinstance(key, int):
            raise TypeError('font index must be an integer, not %s' % type(key))
        if not 0 <= key < MAX_GLYPH_COUNT:
            raise IndexError('font index must be in the range 0..%d' %
                             (MAX_GLYPH_COUNT - 1))

        if not isinstance(value, Glyph):
            raise TypeError('value must be type Glyph, not %s' % type(key))
        if not self._width:
            self._width = value.width
        else:
            if self._width != value.width:
                raise ValueError('new value has a glyph width of %d that '
                                 'differs from font width of %d' %
                                 (value.width, self._width))
        if not self._height:
            self._height = value.height
        else:
            if self._height != value.height:
                raise ValueError('new value has a glyph height of %d that '
                                 'differs from font height of %d' %
                                 (value.height, self._height))

        super().__setitem__(key, value)

    def update(self, opt=None, **kwargs):
        """f.update([f2, ]**f3) -> None.  Update f from dict/iterable f2 and f3.

        If f2 is present and has a `.keys()` method, then does::
            for key in f2: f[key] = f2[key]

        If f2 is present and lacks a `.keys()` method, then does::
            for key, val in f2: f[key] = val

        In either case, this is followed by::
            for key in f3:  f[key] = f3[key]
        """

        if opt is not None:
            for key, val in opt.items() if isinstance(opt, _Mapping) else opt:
                self[key] = val

        for key, val in kwargs.items():
            self[key] = val

    @property
    def width(self):
        """The width of the font in pixels (may be ``None``)."""
        return self._width

    @property
    def height(self):
        """The height of the font in pixels (may be ``None``)."""
        return self._height

    @property
    def version(self):
        """The PSF font version number (may be ``None``)."""
        return self._version

    @version.setter
    def version(self, font_version):
        if font_version not in [None, 1, 2]:
            raise ValueError('illegal font version: %s' % font_version)
        self._version = font_version

    def count(self):
        """Return the actual number of glyphs in the font."""
        return len(self.keys())

    def highest_glyph_number(self):
        """Return the highest glyph number in the font."""

        if self:
            return max(self.keys())
        else:
            return None

    def calculate_version(self):
        """Calculate the PSF font version.

        This method returns the integer 1 if the following conditions
        are met for the Font instance:

        * `.width` is exactly 8 (or ``None``), and
        * `.highest_glyph_number()` is either 255 or 511 (or ``None``)

        In all other cases, the integer 2 is returned.
        """

        hgn = self.highest_glyph_number()
        if ((self._width is None or self._width == 8)
                and (hgn is None or hgn == 255 or hgn == 511)):
            return 1
        else:
            return 2

    def has_unicode_mapping(self):
        """Return ``True`` if any glyph has a Unicode mapping."""
        for val in self.values():
            if val.has_unicode_mapping():
                return True
        return False

    def get_missing_glyphs(self):
        """Return a list of glyph numbers of missing glyphs.

        All glyph numbers between 0 and `.highest_glyph_number()`
        inclusive are checked; any that do not have a corresponding
        `Glyph` object are deemed missing and are returned.  If no glyphs
        are defined, ``None`` is returned.
        """

        if self:
            return [n for n in range(self.highest_glyph_number() + 1) \
                        if n not in self]
        else:
            return None

    def get_missing_mappings(self):
        """Return a list of glyphs with missing Unicode mappings.

        All defined glyphs are checked.  If any such glyph does not have
        a Unicode mapping, and at least one glyph *does* have a mapping
        (ie, `.has_unicode_mapping()` returns ``True``), then return a
        list of all glyphs that do not have a mapping.  If no glyph has a
        mapping, or if *all* glyphs have a mapping, return the empty
        list.  If no glyphs are defined, ``None`` is returned.
        """

        if not self:
            return None

        result = []
        has_mapping = False
        for (key, val) in self.items():
            if val.has_unicode_mapping():
                has_mapping = True
            else:
                result.append(key)
        if has_mapping:
            result.sort()
            return result
        else:
            return []

    def get_all_mappings(self):
        """Return all Unicode mappings.

        Return a dictionary object containing a map of Unicode strings
        to a list of glyph numbers.  If no mappings are defined, return
        the empty dictionary; if no glyphs are defined, ``None`` is
        returned.

        For example, if glyph 1 has mapping ``['a']``, glyph 2 has
        mapping ``['b']`` and glyph 3 has mapping ``['b', 'c']``, the
        result would be ``{'a': [1], 'b': [2, 3], 'c': [3]}``.
        """

        if not self:
            return None

        result = {}
        for (key, val) in self.items():
            if val.has_unicode_mapping():
                for mapping in val.unicode_mapping:
                    prev = result.get(mapping)
                    if prev:
                        prev.append(key)
                    else:
                        result[mapping] = [key]
        for val in result.values():
            val.sort()
        return result

    def get_overlapping_mappings(self):
        """Return overlapping Unicode mappings.

        All defined glyphs are checked.  If any glyph has any part of its
        Unicode mapping overlap with the Unicode mapping of another
        glyph, the relevant part of the Unicode mapping (the Unicode
        string in question) is returned as part of a dictionary object,
        along with the glyph numbers in question.  The empty dictionary
        is returned if no mappings overlap; ``None`` is returned if no
        glyphs are defined.

        For example, if glyph 1 has mapping ``['a', 'b', 'c']`` and glyph
        2 has mapping ``['d', 'e', 'b']``, the result would be ``{'b':
        [1, 2]}``.
        """

        if not self:
            return None

        result = {}
        seen = {}
        for (key, val) in self.items():
            if val.has_unicode_mapping():
                for mapping in val.unicode_mapping:
                    prev = seen.get(mapping)
                    if prev:
                        # Share the list of previously seen mappings
                        # between seen[mapping] and result[mapping]
                        prev.append(key)
                        result[mapping] = prev
                    else:
                        seen[mapping] = [key]
        for val in result.values():
            val.sort()
        return result

    def get_out_of_order_mappings(self):
        """Return all single-character mappings that appear out of order.

        All defined glyphs are checked.  If any glyph has
        single-character mappings that appear after multi-character
        sequences, those mappings are returned as part of a dictionary
        object, with the glyph number in question as the key.  If no such
        out-of-order mappings appear, an empty dictionary is returned;
        ``None`` is returned if no glyphs are defined.
        """

        if not self:
            return None

        result = {}
        for (key, val) in self.items():
            if val.has_unicode_mapping():
                out_of_order = []
                multi_seen = False
                for mapping in val.unicode_mapping:
                    if len(mapping) == 1:
                        # Single-character mapping
                        if multi_seen:
                            out_of_order.append(mapping)
                    else:
                        # Multi-character mapping
                        multi_seen = True
                if out_of_order:
                    result[key] = out_of_order
        return result


#########################################################################
# check function

def check(font, file=None, line=None,
          allow_missing_glyphs=False,
          allow_missing_mappings=False,
          allow_overlapping_mappings=False,
          allow_out_of_order_mappings=False,
          allow_gt_max_glyph_count_strict=False):
    """Check the `Font` object font for correctness.

    This function checks the `Font` object font for correctness and
    completeness and raises the `InvalidFontError` exception if any given
    check fails.  If an exception is raised, file and line are passed to
    the exception object.

    The function may be made more permissive in its checks by passing
    various ``allow`` parameters.  By default all checks are strict.
    """

    if not allow_missing_glyphs:
        if font.count() < MIN_GLYPH_COUNT:
            raise InvalidFontError('insufficient glyphs in font', file, line)
        if font.highest_glyph_number() + 1 != font.count():
            raise InvalidFontError('missing glyphs: %s'
                                   % font.get_missing_glyphs(), file, line)

    if not allow_missing_mappings:
        missing = font.get_missing_mappings()
        if missing:
            raise InvalidFontError('missing Unicode mappings: %s' % missing,
                                   file, line)

    if not allow_overlapping_mappings:
        overlapping = font.get_overlapping_mappings()
        if overlapping:
            raise InvalidFontError('overlapping Unicode mappings: %s'
                                   % overlapping, file, line)

    if not allow_out_of_order_mappings:
        out_of_order = font.get_out_of_order_mappings()
        if out_of_order:
            raise InvalidFontError('out-of-order Unicode mappings: %s'
                                   % out_of_order, file, line)

    if not allow_gt_max_glyph_count_strict:
        if font.highest_glyph_number() + 1 > MAX_GLYPH_COUNT_STRICT:
            raise InvalidFontError('too many glyphs: %d present, maximum %d'
                                   % (font.highest_glyph_number() + 1,
                                      MAX_GLYPH_COUNT_STRICT))


#########################################################################
