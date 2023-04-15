```c++
#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "DelayX.h"

static void Test()
{
    static CDelayX delayx(1000);
    if(delayx.Huh()) return;

    printf("Kept you waiting, huh?\n");
}
```
