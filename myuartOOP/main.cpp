#include <stdio.h>
#include "McuController.h"
using android::McuController;
int main()
{
    printf("main start --->\n");
    McuController::getInstance().init();
    sleep(2);
    uint8_t datagf[1] = {10};
    uint8_t datagf2[1] = {1};
    int i = 10;
    while (i < 110)
    {
        /* code */
        sleep(2);
        if (i >= 50)
        {
            datagf[0] = i - 100; 
        }else{
            datagf[0] = 10 + i; 
        }
        
        McuController::getInstance().send(0x08, 0x04, datagf, 1);//设置屏幕亮度，0到100
        McuController::getInstance().send(0x08, 0x01, datagf2, 1);       
        i = i + 10;
    }
    while (1)
    {
        /* code */
    }
    printf("main end --->\n");
    return 0;
}