#ifndef _FUNC_H
#define _FUNC_H
#include "common.h"

extern int16 ascii_to_decimal(Uint8 c);
extern int16 decimal_to_ascii(Uint8 val);

extern int16 string_fliter(Uint8 *p_in_str, Uint16 in_len, Uint8 *p_chr, Uint16 chr_len, Uint8 *p_out_str, Uint16 *out_len);
extern int16 string_first_detect(Uint8 *p_in_str, Uint16 in_len, Uint8 *p_chr, Uint16 chr_len, Uint8 *p_out_str, Uint16 *out_len);
extern int16 string_cut(Uint8 *str, Uint16 str_len, Uint8 *c, Uint16 size, Uint8 *buf[], Uint16 buf_len);

#endif