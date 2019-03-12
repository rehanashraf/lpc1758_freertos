/*
 * Print.h
 *
 *  Created on: Aug 28, 2018
 *      Author: rehanashraf
 */

#ifndef LIB_L2_DRIVERS_PRINT_H_
#define LIB_L2_DRIVERS_PRINT_H_

#include <stdlib.h>
#include <cstring>
#include <string>

#define DEC 10
#define HEX 16
#define OCT 8
#ifdef BIN // Prevent warnings if BIN is previously defined in "iotnx4.h" or similar
#undef BIN
#endif
#define BIN 2

//#define WSTRING_IMPLEMENTED
//TODO need to check what is WSTRING and then implement that solution in here.

class Printable;

class Print
{
  private:
    int write_error;
    size_t printNumber(unsigned long, uint8_t);
    size_t printFloat(double, uint8_t);
  protected:
    void setWriteError(int err = 1) { write_error = err; }
  public:
    Print() : write_error(0) {}

    int getWriteError() { return write_error; }
    void clearWriteError() { setWriteError(0); }

    virtual size_t write(uint8_t) = 0;
    size_t write(const char *str) {
      if (str == NULL) return 0;
      return write((const uint8_t *)str, strlen(str));
    }
    virtual size_t write(const uint8_t *buffer, size_t size);
    size_t write(const char *buffer, size_t size) {
      return write((const uint8_t *)buffer, size);
    }

    // default to zero, meaning "a single write may block"
    // should be overriden by subclasses with buffering
    virtual int availableForWrite() { return 0; }

#ifdef WSTRING_IMPLEMENTED
    size_t print(const __FlashStringHelper *);
    size_t print(const String &);
#endif
    size_t print(const char[]);
    size_t print(char);
    size_t print(unsigned char, int = DEC);
    size_t print(int, int = DEC);
    size_t print(unsigned int, int = DEC);
    size_t print(long, int = DEC);
    size_t print(unsigned long, int = DEC);
    size_t print(double, int = 2);
    size_t print(const Printable&);
#ifdef WSTRING_IMPLEMENTED
    size_t println(const __FlashStringHelper *);
    size_t println(const String &s);
#endif
    size_t println(const char[]);
    size_t println(char);
    size_t println(unsigned char, int = DEC);
    size_t println(int, int = DEC);
    size_t println(unsigned int, int = DEC);
    size_t println(long, int = DEC);
    size_t println(unsigned long, int = DEC);
    size_t println(double, int = 2);
    size_t println(const Printable&);
    size_t println(void);

    virtual void flush() { /* Empty implementation for backward compatibility */ }
};

class Printable
{
  public:
    virtual size_t printTo(Print& p) const = 0;
};
#endif /* LIB_L2_DRIVERS_PRINT_H_ */
