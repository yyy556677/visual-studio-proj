#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int16 ascii_to_decimal(Uint8 c)
{
	return (c % 0x30);
}

int16 decimal_to_ascii(Uint8 val)
{
	return (val + 0x30);
}


int16 string_fliter(Uint8 *p_in_str, Uint16 in_len, Uint8 *p_chr, Uint16 chr_len,Uint8 *p_out_str,Uint16 *out_len)
{
	Uint8 *_p_str = NULL;
	Uint8 *_p_head = NULL;
	Uint8 *_p_buf = NULL;
	Uint8 *_p_buf_head = NULL;
	Uint16 _str_len = 0U;
	Uint16 head_len = 0U;
	int16 ret = 0U;
	if (NULL == p_in_str || 0 == in_len) {
		return DRV_ERR;
	}
	if (NULL == p_chr || 0 == chr_len) {
		return DRV_ERR_1;
	}
	if(NULL == p_out_str || 0 == out_len)
	memset(p_out_str, 0U, *out_len);
	*out_len = 0U;
	_str_len = in_len;
	_p_str = p_in_str;
	_p_head = (Uint8 *)malloc(sizeof(Uint8)*_str_len);
	_p_buf = (Uint8 *)malloc(sizeof(Uint8)*_str_len);
	if (NULL == _p_head || NULL == _p_buf) {
		return DRV_ERR_2;
	}
	_p_buf_head = _p_buf;

	while (1) {
		ret = string_first_detect(_p_str, _str_len, p_chr, chr_len, _p_head, &head_len);
		if (ret_err == ret) {
			free(_p_buf_head);
			free(_p_head);
			return DRV_ERR_3;
		}
		else if (ret_err_1 == ret) {
			free(_p_buf_head);
			free(_p_head);
			return DRV_ERR_4;
		}
		else if (ret_err_2 == ret) {
			free(_p_buf_head);
			free(_p_head);
			return DRV_ERR_5;
		}
		else if (ret_err_3 == ret) {
			free(_p_buf_head);
			free(_p_head);
			return DRV_ERR_6;
		}
		else if (ret_err_4 == ret) {
			free(_p_buf_head);
			free(_p_head);
			return DRV_ERR_7;
		}
		else {
			memcpy(_p_buf,_p_head,head_len);
			_p_buf += head_len;
			*out_len += head_len;
			memcpy(p_out_str, _p_buf_head, *out_len);
			if (_str_len >= (head_len + chr_len)) {
				_p_str += (head_len + chr_len);
				_str_len -= (head_len + chr_len);
			}
			else{
				free(_p_buf_head);
				free(_p_head);
				return DRV_OK;
			}	
		}
	}
}


int16 string_first_detect(Uint8 *p_in_str, Uint16 in_len,Uint8 *p_chr,Uint16 chr_len,Uint8 *p_out_str,Uint16 *out_len)
{
	Uint16 j = 0;
	Uint8 *_p_head = NULL;
	if (NULL == p_in_str || 0 == in_len) {
		return DRV_ERR;
	}
	if (NULL == p_chr || 0 == chr_len) {
		return DRV_ERR_1;
	}
	if (NULL == p_out_str || 0 == out_len) {
		return DRV_ERR_2;
	}
	if (in_len < chr_len) {
		if (0U != in_len) {
			memcpy(p_out_str, p_in_str, in_len);
			*out_len = in_len;
			return DRV_OK;
		}
		return DRV_ERR_3;
	}
	_p_head = p_in_str;
	while (1) {
		if (in_len <= j) {
			if (0U != j) {
				memcpy(p_out_str, _p_head, j);
				return DRV_OK;
			}
			return DRV_ERR_4;
		}
		if (0 == memcmp(p_in_str, p_chr, chr_len)) {
			memcpy(p_out_str, _p_head,j);
			return DRV_OK;
		}
		else {
			p_in_str += 1U;
			j += 1U;
			*out_len = j;
		}
	}
}

int16 string_cut(Uint8 *p_str, Uint16 str_len, Uint8 *p_chr, Uint16 size,Uint8 *p_buf[],Uint16 buf_len)
{
	Uint16 i = 0U;
	Uint16 j = 0U;
	Uint16 num = 0U;
	Uint8 *_p_head = NULL;
	Uint16 head_len = 0;
	Uint8 *_p_buf = NULL;
	Uint16 _buf_len = 0U;
	int16 ret = 0;
	if (NULL == p_str || 0U == str_len) {
		return DRV_ERR;
	}
	if (NULL == p_chr || 0U == size) {
		return DRV_ERR_1;
	}
	if (NULL == p_buf || 0U == buf_len) {
		return DRV_ERR_2;
	}
	_p_head = p_str;
	head_len = str_len;
	_p_buf = (Uint8 *)malloc(sizeof(Uint8)*head_len);
	if (NULL == _p_buf) {
		return DRV_ERR_3;
	}
	while (1) 
	{
		ret = string_first_detect(_p_head, head_len, p_chr, size, _p_buf, &_buf_len);
		if (ret_err == ret) {
			free(_p_buf);
			return DRV_ERR_4;
		}
		else if (ret_err_1 == ret) {
			free(_p_buf);
			return DRV_ERR_5;
		}
		else if (ret_err_2 == ret) {
			free(_p_buf);
			return DRV_ERR_6;
		}
		else if (ret_err_3 == ret) {
			free(_p_buf);
			return DRV_ERR_7;
		}
		else if (ret_err_4 == ret) {
			free(_p_buf);
			return DRV_ERR_8;
		}
		else {
			memcpy(p_buf[i], _p_buf, _buf_len);
			_p_head += (_buf_len + size);
			if(head_len > (_buf_len + size)){
				head_len -= (_buf_len + size);
			}
			else {
				head_len = 0U;
			}		
			i += 1U;
			if (i > (buf_len - 1)){
				free(_p_buf);
				return DRV_ERR_9;
			}
		}
	}
}