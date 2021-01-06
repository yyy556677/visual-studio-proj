#ifndef _COMMON_H
#define _COMMON_H

enum {
	ret_err = -1,
	ret_err_1 = -2,
	ret_err_2 = -3,
	ret_err_3 = -4,
	ret_err_4 = -5,
	ret_err_5 = -6,
	ret_err_6 = -7,
	ret_err_7 = -8,
	ret_err_8 = -9
};

#define DRV_ERR   (-1)
#define DRV_ERR_1 (-2)
#define DRV_ERR_2 (-3)
#define DRV_ERR_3 (-4)
#define DRV_ERR_4 (-5)
#define DRV_ERR_5 (-6)
#define DRV_ERR_6 (-7)
#define DRV_ERR_7 (-8)
#define DRV_ERR_8 (-9)
#define DRV_ERR_9 (-10)
#define DRV_OK    (0U)

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef unsigned char Uint8;
typedef unsigned short Uint16;
typedef unsigned int Uint32;

#endif
