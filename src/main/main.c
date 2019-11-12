#include "mcu_support_package/inc/stm32f10x.h"
#include "eval.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
int32_t num;



int main(void)
{
	num = eval("2+1");
    return 0;
}
