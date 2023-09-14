本项目使用的主控芯片为ESP32-WROOM-32E

## 硬件资源

### 概览

- 搭载Xtensa® 双核 32位 LX6 微处理器，支持高达 240 MHz 的时钟频率。
- 片内 448 KB ROM + 520 KB SRAM + 16 KB RTC SRAM。
- 集成 802.11b/g/n，802.11n 数据速率高达 150 Mbps，支持蓝牙 V4.2 BR/EDR 和蓝牙 LE 标准。
- +19.5 dBm 天线端输出功率，确保良好的覆盖范围
- 外设包括电容式触摸传感器，霍尔传感器，SD 卡接口，以太网，高速 SPI，UART，I2S 和 I2C，CAN，ADC，DAC，PWM，IR。

### 引脚定义

![](https://picbed-1312285733.cos.ap-beijing.myqcloud.com/img/202309142032413.webp)

ESP32 共有 6 个 Strapping 引脚。
• GPIO0：内部上拉，**Flash 烧录时要拉低电平**
• GPIO2：内部下拉
• GPIO4：内部下拉
• GPIO5：内部上拉(启动必须为高)
• GPIO12：内部下拉(启动必须为低)
• GPIO15：内部上拉(启动必须为高)

数字通用IO引脚

| GPIO | 输入 | 输出 | 备注                                            |
| ---- | ---- | ---- | ----------------------------------------------- |
| 0    | OK   | OK   | 内部上拉，启动时输出PWM信号 ，FLASH烧录控制引脚 |
| 1    | OK   | OK   | UART0 TXD 串口输出                              |
| 2    | OK   | OK   | 内部下拉                                        |
| 3    | OK   | OK   | UART0 RXD 串口输入，且启动时为高电平            |
| 4    | OK   | OK   | 内部下拉                                        |
| 5    | OK   | OK   | 内部上拉，启动时输出PWM信号                     |
| 12   | OK   | OK   | MTDI 可用于JTAG调试、内部下拉                   |
| 13   | OK   | OK   | MTCK 可用于JTAG调试                             |
| 14   | OK   | OK   | MTMS 可用于JTAG调试，启动时输出PWM信号          |
| 15   | OK   | OK   | MTDO 可用于JTAG调试、内部上拉                   |
| 16   | OK   | OK   | UART2_RXD                                       |
| 17   | OK   | OK   | UART2_TXD                                       |
| 18   | OK   | OK   |                                                 |
| 19   | OK   | OK   |                                                 |
| 20   | OK   | OK   |                                                 |
| 21   | OK   | OK   | IIC_SDA                                         |
| 22   | OK   | OK   | IIC_SCL                                         |
| 23   | OK   | OK   |                                                 |
| 24   | OK   | OK   |                                                 |
| 25   | OK   | OK   |                                                 |
| 26   | OK   | OK   |                                                 |
| 27   | OK   | OK   |                                                 |
| 28   | OK   | OK   |                                                 |
| 29   | OK   | OK   |                                                 |
| 30   | OK   | OK   |                                                 |
| 31   | OK   | OK   |                                                 |
| 32   | OK   | OK   | 32K_XP                                          |
| 33   | OK   | OK   | 32K_XN                                          |

**GPIO 6-GPIO 11连接到ESP32模块上的集成SPI闪存，不建议用于其他用途**

| GPIO | 输入 | 输出 | 备注                     |
| ---- | ---- | ---- | ------------------------ |
| 6    | OK   | OK   | SD_CLK                   |
| 7    | OK   | OK   | SD_DATA_0                |
| 8    | OK   | OK   | SD_DATA_1                |
| 9    | OK   | OK   | SD_DATA_2、**UART1_RXD** |
| 10   | OK   | OK   | SD_DATA_3、**UART1_TXD** |
| 11   | OK   | OK   | SD_CMD                   |

可以直接调用官方的API来操作片上闪存。

仅输入引脚

GPIO 34-39是GPIO仅输入引脚。这些引脚没有内部上拉或下拉电阻。它们不能用作输出，因此只能将这些引脚用作输入，常用于ADC输入通道。

### 时钟

时钟树

![](https://picbed-1312285733.cos.ap-beijing.myqcloud.com/img/202309142127308.webp)