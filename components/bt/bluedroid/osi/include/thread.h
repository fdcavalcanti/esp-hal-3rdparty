#ifndef __THREAD_H__
#define __THREAD_H__

#include "freertos/xtensa_api.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"

#define portBASE_TYPE int

struct task_evt {
    uint32_t sig;
    uint32_t par;
};
typedef struct task_evt TaskEvt_t;

enum {
    SIG_PRF_START_UP = 0xfc,
    SIG_PRF_WORK = 0xfd,
    SIG_BTU_START_UP = 0xfe,
    SIG_BTU_WORK = 0xff,
    SIG_BTIF_WORK = 0xff
};

void btu_task_post(uint32_t sig);
void hci_host_task_post(void);
void hci_hal_h4_task_post(void);
void hci_drv_task_post(void);
void bt_alarm_task_post(void);


#endif /* __THREAD_H__ */
