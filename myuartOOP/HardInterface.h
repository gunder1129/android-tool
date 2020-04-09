#ifndef MYUART_HARDINTERFACE_H
#define MYUART_HARDINTERFACE_H

#include <fcntl.h>
#include <utils/threads.h>
#define INVALID_IO_TYPE -1

class HardInterface
{
private:
    /* data */
public:
    
    enum MCUIOTYPE { INVALIDIOTYPE = -1, EUARTIO, I2CIO };
    HardInterface(/* args */) : miotype(MCUIOTYPE::INVALIDIOTYPE), fd(INVALIDIOTYPE)
    {
        fd = init_dev();
    }
    virtual ~HardInterface(){}

    virtual int init_dev()
    {
        return INVALID_IO_TYPE;
    }
    virtual int txdata(unsigned char* txbuf, unsigned int txcount) = 0;
    virtual int rxdata(unsigned char* rxbuf, unsigned int rxcount) = 0;
    MCUIOTYPE miotype;
    int fd;    
};

#endif