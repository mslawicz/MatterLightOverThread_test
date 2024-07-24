/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *    Copyright (c) 2019 Google LLC.
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
#include "sl_component_catalog.h"
#include "sl_system_init.h"
#include "sl_system_kernel.h"
#include <MatterConfig.h>
#include "cmsis_os2.h"
#include "sl_simple_led_instances.h"

constexpr uint32_t myTaskStackSize = 1024;
// Task is dynamically allocated with max priority. This task gets deleted once the inits are completed.
constexpr osThreadAttr_t myTaskAttr = { .name       = "my Task",
                                        .attr_bits  = osThreadDetached,
                                        .cb_mem     = NULL,
                                        .cb_size    = 0U,
                                        .stack_mem  = NULL,
                                        .stack_size = myTaskStackSize,
                                        .priority   = osPriorityLow };
osThreadId_t myTaskHandle;

void myApplicationStart(void * unused);

int main(void)
{
    sl_system_init();
    myTaskHandle = osThreadNew(myApplicationStart, nullptr, &myTaskAttr);

    // Initialize the application. For example, create periodic timer(s) or
    // task(s) if the kernel is present.
    SilabsMatterConfig::AppInit();
}

void myApplicationStart(void * unused)
{
    while(1)
    {
        sl_simple_led_toggle(sl_led_led0.context);
        osDelay(500);
    }
}