#ifndef __HEXDUMP_H__
#define __HEXDUMP_H__

/**
 * This function prints to stdout the contents of a buffer in hexadecimal
 * and in its ASCII representation. The output is similar to what you would
 * get by running the Linux utility xxd on a file.
 *
 * @param buffer pointer to a memory buffer
 * @param length number of bytes in the buffer
 */
extern void hexdump(unsigned char* buffer, unsigned int length);

#endif /* __HEXDUMP_H__ */
