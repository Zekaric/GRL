# Groot's Organized Data File Format (GOD File)<!-- omit in toc -->

```
Author:             Robbert de Groot
Date:               2025-12-20
Copyright:          2025, Robbert de Groot
License (Library):  MIT License.
License (Document): Creative Commons Attribution-NoDerivs.
                    CC BY-ND
                    https://creativecommons.org/licenses/by-nd:4.0
```

## Table of Contents <!-- omit in toc -->

- [1. G.O.D.](#1-god)
  - [1.1. Discussion](#11-discussion)
  - [1.2. Goals](#12-goals)
  - [1.3. Design Decisions:](#13-design-decisions)
  - [1.4. Disclosure](#14-disclosure)
- [2. Format](#2-format)
  - [2.1 So what are the differences with JSON?](#21-so-what-are-the-differences-with-json)
  - [2.2 Is GOD better?](#22-is-god-better)
- [3 Acronyms](#3-acronyms)


# 1. G.O.D.

## 1.1. Discussion

**What is the purpose of G.O.D. (GOD)?**

GOD is intended to be a better JSON file format for storing data.  Any data.  And large amounts of
data without the problems that JSON has.

## 1.2. Goals

* **Restrictions Removed**    JSON has restrictions because JavaScript has those restrictions.  This is
frustrating as a developer when using JSON.  You have to build into the load and store hacks for
dealing with large signed and unsigned integers.  JSON is designed to store JavaScript objects.  It
is perfect for that.  However GOD is not designed for JavaScript.  It is designed to store real
unbounded data.  It is data focused not JavaScript focused.

* **Simplified**              JSON is designed to store objects.  GOD is designed to store data.  It
is not as restricted as JSON is.

* **Accurrate**               JSON doesn't deal with NAN, +/- INF and there is no standard in the
format for handling them.

## 1.3. Design Decisions:

**Why not JSON?**

I have a few issues with JSON.  JSON format doesn't specify any limits on numbers.  Which is great.
However implementations can do what they like when it comes to numbers they can't handle.  I.E.
Javascript can't handle full 64 bit integers and unsigned integers.  So it tends to write those
values out as strings which is a hack.  The JSON format has no problems but Javascript does.
JSON format doesn't have NAN, Infinity defined for any of the numbers.  So those too are written
out as strings and more worryingly, there is no standard on how to write that information out.

I always found it weird that that 'key' in a JSON file required the quotes.  You could save a bunch
of bytes doing away with them.  I get why they did that, makes the code simpler but as a format that
is used for data exchange, size matters.  So GOD does not have quotes around keys.

I do not claim God is better, but I would argue it is better.  There should not be any 'hacks' to
get around a languages' limitations.  Implementation should not be optional.

## 1.4. Disclosure

I, Robbert de Groot, have been a professional Software Developer since 1995.

This format is currently not sanctioned by any software vendor.  This was an attempt on developing
something in place of existing or developing options which I find lacking or distasteful in some
fashion.

I can be reached at the following email address.

zekaric@gmail.com

# 2. Format

A **GOD File is a UTF8 text file**.

For the most part a GOD file will look very similar to a JSON file (See json.org).  The format in BNF like form.

```
GOD_File:
   members

ws:
   ""
   '0009' ws                                                // tab
   '000A' ws                                                // line feed/new line
   '000D' ws                                                // cursor return
   ' ' ws

members:
   member
   member ',' member

member:
   ws key ws
   ws key ws ':' element

key:
   keyCharacter keyCharacters

keyCharacters:
   ""
   keyCharacter keyCharacters

keyCharacter:
   [any utf8 character not ':' ]

elements:
   element ',' elements

element:
   ws value ws

value:
   array
   object
   number
   binary
   string
   'T'                                                      // True value
   'F'                                                      // False value
   'N'                                                      // Null value
   '?'                                                      // Not a Number value
   'I'                                                      // Infinity
   'i'                                                      // -Infinity
   'L'                                                      // Largest positive value for number type
   'l'                                                      // Largest negative value for number type
   'S'                                                      // Smallest positive value for number type
   's'                                                      // Smallest negative value for number type

array:
   '[' ws ']'
   '[' elements ']'

object:
   '{' ws '}'
   '{' members '}'

number:
   integer fraction exponent

integer:
   digit
   oneToNineDigit digits
   '-' digits

fraction:
   ""
   '.' digits

exponent:
   ""
   'e' sign digits
   'E' sign digits

sign:
   ""
   "+"
   "-"

digits:
   digit
   digit digits

digit:
   '0'
   oneToNineDigit

oneToNineDigit:
   '1' . '9'

binary:
   '*' hexs

hexs:
   hex
   hex hexs

hex:
   '0' . '9'
   'a' . 'f'
   'A' . 'F'

string:
   '"' characters '"'

characters:
   ""
   character characters

character:
   [any utf8 charcter not '"' or '\']
   '\' '"'                                                  // " escape required
   '\' '\'                                                  // \ escape required
   '\' 'b'                                                  // backspace but not required
   '\' 'n'                                                  // new line but not required
   '\' 'r'                                                  // cursor return but not required
   '\' 't'                                                  // tab but not required
   '\' 'f'                                                  // form feed but not required

hex:
   digit
   'a' . 'f'
   'A' . 'F'
```

## 2.1 So what are the differences with JSON?

1. GOD starts out assuming we are in an object.  So the first things are members instead of an
element like in JSON.  Most often than not, a JSON file will be an object.  So why not just start with that.

2. The change of 'true' to 'T', 'false' to 'F', and 'null' to 'N'.  Saves 3 to 4 bytes for these values.

3. The addition of '?' for Not a Number, 'I' for Infinity and 'i' for -Infinity, 'L' largest
positive number and 'l' for largest negative number(integer or real), 'S' for the smallest positive
and 's' for smallest negative number (reals only).  Something JSON doesn't specify and is not
standardized over implementations.

4. The key values are not enclosed in quotes.  This saves 2 bytes per key when compared to JSON.
Leading and trailing ws characters will be trimmed, internal ws characters will be significant.
Keys should be well formed so there should not be significant leading or trailing ws.  Also they can
not have ':' or ',' characters inside the key since that separates the key and value or a key with no value
from the next key value pair.

5. A key does not require a value.  The existance of a key may be enough for the format that a value is
unnecessary.  In short, a key that exists is a true value.  A key that is missing is a false value.

6. Integers larger than what JavaScript can handle, MUST NOT be written as a string.  Any integer
regardless of bit depth (64 bit, 128 bit, etc.) must be written as a number.  This is a data format
and not a JavaScript restricted format.

7. Keys can repreat.  They do not need to be unique within an "object".  This puts the onus on the
user of the format what a repeated key will mean.

8. A binary blob is defined as a value that starts with '\*' and followed by a number of hexidecimal
digits.  Unlike a string, I does not need a terminating character.  It is understood to be terminated 
when a }, ], comma, or whitespace is seen.

## 2.2 Is GOD better?

I would say yes, but probably not for JavaScript.

The header makes it obvious what type of file this is.  JSON has no such thing other than the file
extension giving you some hint as to what is contained in the file.  OR you structured the JSON to have
a small layer to provide a key to the overall object that the file contains.  At least with GOD, the
header tells you it is a GOD file.  I would suggest that users provide a second key value pair to
define a subformat and subformat version for the data.  This will make it obvious what data is
stored in the file not just how (GOD like) it is stored in the file.

EG:  fmt:"Contact Information",

JSON doesn't handle numbers quite right.  But this is because JavaScript doesn't handle numbers
quite right.  Encoding some special values is not standard.  You can't encode all 64 bit integers or
unsigned integers.  Often, for JSON, if a number can't be represented, it is turned into a string.
This adds complication for the importer and exporter of JSON data.  This is where GOD does it right.

JSON assumes the data is in JS object form.  GOD does not restrict you to that.  In other words, you
can have duplicate keys in an object if that makes sence for your data.  Arguably, this might be a
negative for GOD files as JSON did that for a reason.

The GOD file will be smaller than the JSON file depending on what you are writing.  But 2 bytes per
key, 3-4 bytes for contants and more for special number values.  I would say if any JSON file that
is storing an object with more than 2 keys, the GOD file will be smaller.

# 3 Acronyms

I am not religious so do not read too much into the GOD acronym.  I just like playing around with
thinks like that.  This is by no means meaning this is the be-all end-all format of all formats.  It
is just made up like everything else.