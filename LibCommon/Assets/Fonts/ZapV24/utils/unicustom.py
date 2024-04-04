#########################################################################
#                                                                       #
#                   Custom Unicode Mapping Functions                    #
#                 Copyright (C) 2016-19, John Zaitseff                  #
#                                                                       #
#########################################################################

# Author: John Zaitseff <J.Zaitseff@zap.org.au>

# This module contains functions to perform custom mapping of Unicode
# names and code point values.  It is based on the standard unicodedata
# module with appropriate additions.
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


"""Custom Unicode mapping functions.

The `unicustom` module contains functions to map Unicode names and code
point values.  It is based on the standard `unicodedata` module with
appropriate additions.

The following functions are exported:

* `lookup()` - Look up a character by name.
* `name()`   - Return the name assigned to a Unicode character.
"""


__version__ = '1.4'
__author__ = 'John Zaitseff <J.Zaitseff@zap.org.au>'


import unicodedata


#########################################################################
# Global variables

UNICODE_ADDITIONS = {
    # ASCII control characters
    '\u0000': '(NULL)',
    '\u0001': '(START OF HEADING)',
    '\u0002': '(START OF TEXT)',
    '\u0003': '(END OF TEXT)',
    '\u0004': '(END OF TRANSMISSION)',
    '\u0005': '(ENQUIRY)',
    '\u0006': '(ACKNOWLEDGE)',
    '\u0007': '(BELL)',
    '\u0008': '(BACKSPACE)',
    '\u0009': '(CHARACTER TABULATION)',
    '\u000A': '(LINE FEED)',
    '\u000B': '(LINE TABULATION)',
    '\u000C': '(FORM FEED)',
    '\u000D': '(CARRIAGE RETURN)',
    '\u000E': '(SHIFT OUT)',
    '\u000F': '(SHIFT IN)',
    '\u0010': '(DATA LINK ESCAPE)',
    '\u0011': '(DEVICE CONTROL ONE)',
    '\u0012': '(DEVICE CONTROL TWO)',
    '\u0013': '(DEVICE CONTROL THREE)',
    '\u0014': '(DEVICE CONTROL FOUR)',
    '\u0015': '(NEGATIVE ACKNOWLEDGE)',
    '\u0016': '(SYNCHRONOUS IDLE)',
    '\u0017': '(END OF TRANSMISSION BLOCK)',
    '\u0018': '(CANCEL)',
    '\u0019': '(END OF MEDIUM)',
    '\u001A': '(SUBSTITUTE)',
    '\u001B': '(ESCAPE)',
    '\u001C': '(INFORMATION SEPARATOR FOUR)',
    '\u001D': '(INFORMATION SEPARATOR THREE)',
    '\u001E': '(INFORMATION SEPARATOR TWO)',
    '\u001F': '(INFORMATION SEPARATOR ONE)',
    '\u007F': '(DELETE)',

    # Additional control characters
    '\u0080': '(Control)',
    '\u0081': '(Control)',
    '\u0082': '(BREAK PERMITTED HERE)',
    '\u0083': '(NO BREAK HERE)',
    '\u0084': '(Control)',
    '\u0085': '(NEXT LINE)',
    '\u0086': '(START OF SELECTED AREA)',
    '\u0087': '(END OF SELECTED AREA)',
    '\u0088': '(CHARACTER TABULATION SET)',
    '\u0089': '(CHARACTER TABULATION WITH JUSTIFICATION)',
    '\u008A': '(LINE TABULATION SET)',
    '\u008B': '(PARTIAL LINE FORWARD)',
    '\u008C': '(PARTIAL LINE BACKWARD)',
    '\u008D': '(REVERSE LINE FEED)',
    '\u008E': '(SINGLE SHIFT TWO)',
    '\u008F': '(SINGLE SHIFT THREE)',
    '\u0090': '(DEVICE CONTROL STRING)',
    '\u0091': '(PRIVATE USE ONE)',
    '\u0092': '(PRIVATE USE TWO)',
    '\u0093': '(SET TRANSMIT STATE)',
    '\u0094': '(CANCEL CHARACTER)',
    '\u0095': '(MESSAGE WAITING)',
    '\u0096': '(START OF GUARDED AREA)',
    '\u0097': '(END OF GUARDED AREA)',
    '\u0098': '(START OF STRING)',
    '\u0099': '(Control)',
    '\u009A': '(SINGLE CHARACTER INTRODUCER)',
    '\u009B': '(CONTROL SEQUENCE INTRODUCER)',
    '\u009C': '(STRING TERMINATOR)',
    '\u009D': '(OPERATING SYSTEM COMMAND)',
    '\u009E': '(PRIVACY MESSAGE)',
    '\u009F': '(APPLICATION PROGRAM COMMAND)',

    # Unicode corrections
    '\u0709': 'SYRIAC SUBLINEAR COLON SKEWED LEFT',
    '\u0CDE': 'KANNADA LETTER LLLA',
    '\u0E9D': 'LAO LETTER FO FON',
    '\u0E9F': 'LAO LETTER FO FAY',
    '\u0EA3': 'LAO LETTER RO',
    '\u0EA5': 'LAO LETTER LO',
    '\u2118': 'WEIERSTRASS ELLIPTIC FUNCTION',
    '\uA015': 'YI SYLLABLE ITERATION MARK',
    '\uFE18': 'PRESENTATION FORM FOR VERTICAL RIGHT WHITE LENTICULAR BRACKET',
    '\u1D0C5': 'BYZANTINE MUSICAL SYMBOL FTHORA SKLIRON CHROMA VASIS',

    # Additional characters
    '\uF800': 'LINUX DEC VT HORIZONTAL LINE SCAN-1',
    '\uF801': 'LINUX DEC VT HORIZONTAL LINE SCAN-3',
    '\uF803': 'LINUX DEC VT HORIZONTAL LINE SCAN-7',
    '\uF804': 'LINUX DEC VT HORIZONTAL LINE SCAN-9',
    '\uF810': 'LINUX KEYBOARD SYMBOL FLYING FLAG',
    '\uF811': 'LINUX KEYBOARD SYMBOL PULLDOWN MENU',
    '\uF812': 'LINUX KEYBOARD SYMBOL OPEN APPLE',
    '\uF813': 'LINUX KEYBOARD SYMBOL SOLID APPLE',
}


#########################################################################
# lookup function

def lookup(uni_name):
    """Look up a character by name.

    If a character with the given name is found, return the corresponding
    character.  If not found, `KeyError` is raised.
    """

    uni_name = uni_name.upper()
    for (char, additional_name) in UNICODE_ADDITIONS.items():
        if uni_name == additional_name:
            return char

    return unicodedata.lookup(uni_name)


#########################################################################
# name function

def name(char):
    """Return the name assigned to a Unicode character.

    Return a string containing the name assigned to the character `char`.
    If not found, '``(Undefined)``' is returned.
    """

    if char in UNICODE_ADDITIONS:
        return UNICODE_ADDITIONS[char]
    else:
        return unicodedata.name(char, '(Undefined)')


#########################################################################
