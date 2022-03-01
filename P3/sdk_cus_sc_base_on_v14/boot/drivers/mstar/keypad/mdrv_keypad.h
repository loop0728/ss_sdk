/*
* mdrv_keypad.h- Sigmastar
*
* Copyright (C) 2018 Sigmastar Technology Corp.
*
* Author: ken.chang <ken-ms.chang@sigmastar.com.tw>
*
* This software is licensed under the terms of the GNU General Public
* License version 2, as published by the Free Software Foundation, and
* may be copied, distributed, and modified under those terms.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
*/
#include <common.h>

typedef enum
{
    /* keypad standard 7*7  */
    KP_E_STANDARD_MODE1 = 1,
    /* keypad standard 4*4  */
    KP_E_STANDARD_MODE2 = 2,
    /* keypad standard 3*3  */
    KP_E_STANDARD_MODE3 = 3,
}KEYPAD_STANDARD_E;



u32 mdrv_keypad_Scan(void);
void mdrv_keypad_init(KEYPAD_STANDARD_E standard);



