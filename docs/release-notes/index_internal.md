# WiSeConnect3\_SDK\_3.1.1-ifc1 Release Notes
This SDK package supports SoC Mode and NCP Mode for A0 and B0:

- In SoC Mode: Customer applications can run on Cortex M4. Wireless, network, and security stacks run on the wireless subsystem.
- In NCP mode: Wireless, network, and security stacks run on the Wireless subsystem. Customer applications run on the external host MCU.
- Silicon Labs' SiWx917 includes an ultra-low power Wi-Fi 6 plus Bluetooth Low Energy (BLE) 5.1 wireless subsystem and an integrated micro-controller application subsystem.

**Note**: Use Simplicity Studio version SV5.7.0.1 onwards
## **SoC Highlights**
- **Operating Modes** : Wi-Fi STA (802.11ax, 802.11n), Wi-Fi 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + BLE
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n, 802.11ax, BLE 5.1
- **Multiple Ultra Low Power Modes** : Support ultra low power Wi-Fi standby associated current in Wi-Fi 4 mode, Ultra low power Wi-Fi Standby associated current in Wi-Fi 6 mode leveraging TWT, Always on Cloud connected power, BLE connected power, and, deep sleep ULP mode
- **MCU examples** : GPIO, I2C, Calendar,  SPI, SSI, SIO, Micro DMA, UART/USART, Watchdog Timer, Timers, Config Timers, ULP (Ultra Low Power) Timers, Sleeptimer, IOSTREAM, NVM3, MEMLCD, SDIO Secondary, PWM, ADC, EFUSE, I2S, PSRAM, ML Blinky, Sensorhub
- **Wi-Fi** : 2.4GHz Wi-Fi Support - WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and reduces latency
- **Cloud** : Amazon Cloud Connectivity Support, Amazon FreeRTOS
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support), Advertising extensions, Data length extensions, LL privacy, BLE whitelisting, and BLE long Range. 
- **Integrated Stacks and Profiles** : Wi-Fi Stack, BLE Stack, All GAP and GATT based Profiles & Services are Supported, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, DNS client
- **IDE** : Simplicity Studio with Windows 10(64-bit), Linux, Mac OS
- **TA/M4 Firmware Update Tool** : Simplicity Commander
- **Hardware kits to evaluate SoC Mode** :
  - Si-MB4002A Main board
  - SiWx917 Radio boards

|**RadioBoard Type**|**SiWx917A0 with Board Version**|**SiWx917B0 with Board Version**|
| :-: | :-: | :-: |
|Common flash|Si917-BRD4325A(1.0 /1.1 /1.2)|-|
|Common flash|-|Si917-BRD4338A(2.0)|
|Dual flash|Si917-BRD4325B(1.0 /1.1 /1.2)|-|
|External PSRAM|-|Si917-BRD4340A(2.0)|

## **NCP Highlights**
- **Host Interface** : SPI
- **Operating Modes** : Wi-Fi STA (802.11ax, 802.11n), Wi-Fi 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + BLE
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n, 802.11ax, BLE 5.1
- **Multiple Ultra Low Power Modes** : Support Ultra low power Wi-Fi Standby associated current in Wi-Fi 4 mode, Ultra low power Wi-Fi Standby associated current in Wi-Fi 6 mode leveraging TWT, Always on Cloud connected power, BLE connected power, and, deep sleep ULP mode.
- **Wi-Fi** : 2.4GHz Wi-Fi Support, WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and reduces latency
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support), Advertising extensions, Data length extensions, LL privacy, BLE Whitelisting and BLE long Range. 
- **Integrated Stacks and Profiles** : Wi-Fi Stack , BLE Stack , All GAP and GATT based Profiles & Services are Supported, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, DNS Client.
- **IDE** : Simplicity Studio with Windows 10(64-bit)
- **Hardware kits to evaluate NCP Mode**
  - Si917 B0 1.2 expansion board BRD8036B 
  - Wireless Pro kit Mainboard BRD4002A Rev A06
  - EFR32xG21 2.4 GHz 20 dBm Radio Board (BRD4180B Rev A02)
## **Release Details**

|**Item**|**Details**|
| :-: | :-: |
|Release date|Oct 11th, 2023|
|SDK Version|3\.1.1|
|Firmware Version|1711\.2.9.0.0.23|
|Package Name|WiSeConnect3\_SDK\_3.1.1-ifc1|
|Supported RTOS|FreeRTOS|
|Operating Modes Supported|Wi-Fi STA, Wi-Fi AP, Wi-Fi STA+BLE, Wi-Fi STA+AP|
|Build Quality|GA|

- SiWx917 release consists of two components
  - Wireless Firmware - SiWx917 Firmware Binaries
  - Wiseconnect3 Library - Wiseconnect3 SDK library runs on the external host in NCP mode and internal Cortex M4 in SoC Mode.
- This release is meant only for use with designs based on SiWx917 Silicon
- The firmware to load in your design are available in the following format:
  - SiWG917-A.2.9.0.0.x.rps - A0 Full-featured firmware binary
  - SiWG917-B.2.9.0.0.x.rps - B0 Full-featured firmware binary
## **Features Supported**
**Sensorhub service**

  - Support for ADC, SPI and I2C based sensors
  - Support for PS2 and sleep wakeups
- SoC OPN based project support in SSv5
  - List of OPN's supported
    si917-sb00, siwg917m111mgtba, siwg917m100mgtba, siwg917m111xgtba, siwg917m100xntba, siwg917m121xgtba, siwg917m110lgtba and siwg917m141xgtba
- ML blink and Model Profiler support

**MCU**

- ADC Single Channel, ADC Static Mode, Analog Comparator, Blinky, Bod, CTS, DAC FIFO, DAC Static, GPIO, I2C, I2S, NVM3, OPAMP, PSRAM, PWM, QEI, RTC, SDIO Secondary, SPI Master and Slave, UART, Micro DMA, USART, Watchdog Timer, USART Master and Slave
- UC Supported Peripherals - GPIO, I2C, Calendar,  SPI, SSI, SIO, Micro DMA, UART/USART, Watchdog Timer, Timers , Config Timers, ULP (Ultra Low Power) Timers, SDIO Secondary, PWM, ADC, EFUSE, I2S, PSRAM, Sleeptimer, IOSTREAM, MEMLCD.
- ULP (Ultra Low Power) Peripherals - ulp\_gpio, ulp\_adc ulp\_i2c, ulp\_i2s, ulp\_ir\_decoder, ulp\_spi, ulp\_timer, ulp\_uart, ulp\_udma

**Wi-Fi**

- WPA2/WPA3 Personal, WPS and WPA2-EAP Support for Station Mode
- TCP/IP stack with IPv4, IPv6, TCP, UDP, TLS, HTTP/HTTPS, DHCPv4, DHCPv6, MQTT Client, DNS Client, SNTP client.
- Support for SSL client versions TLSV1.0, TLSV1.2, TLSV1.3 and SSL server versions TLSV1.0 and TLSV1.2
- Wi-Fi STA (802.11n/802.11ax) + 802.11n AP Support
- HE (802.11ax) and Individual TWT Feature Support
- Multiple BSSID feature support as an STA
- Secure OTA support on B0 radio boards.
- Support for LWIP network stack
- Support for AWS MQTT library
- Support for BSD and IoT sockets application programming interface(API)

**Bluetooth Low Energy**

- BLE central & peripheral connections are supported.
- Ultra-low power save is supported.

**Power Save**

- The power save profiles supported are Max PSP, enhanced MAX PSP, Fast PSP, and 802.11ax TWT. 

**Crypto Support**

- AES, SHA, AES-CCM, HMAC, and TRNG FW Crypto API support added.
- PSA enabled Mbed TLS support added
- NVM support is added for key storage
- Symmetric key storage support added for Volatile and transparent key.
- TRNG, AES, SHA, and AES-CCM hardware crypto engine is integrated with PSA crypto.
## **Changes and Fixes**
**MCU**

- Optimization for SoC Deepsleep
- Platform Bugs - SI91X-14202, SI91X-13544, SI91X-14095, SI91X-14126, SI91X-13719, SI91X-13456, SI91X-13530, SI91X-13887, SI91X-14064, SI91X-14187, SI91X-14175, SI91X-13938, SI91X-14134, SI91X-14098, SI91X-14133, SI91X-14099

**Wi-Fi**

- Added mem.alloc, mem.free, and mem.write commands
- Verifed and free the dynamic allocated memory when sl si91x driver send command fails
- Added TA buffer configuration in wifi_init
- Added support for Segger sysview
- Adding documentation for apis in sl_i91x_host_interface.h and sl_rsi_utility.h
- Padding reference in aes example
- Improving code readability with adding comments
- Added support for SL_SI91X_SO_MSS
- Replace sl_tls with sl_net credential API
- Update TWT use case demo and Wlan_RF test example
- Update wlan soc feedback from apps team development
- Update certificate handling
- New readme changes
- Wiseconnect3 featured examples readme updated
- Update wiseconnect3.yakka with project description
- Updated slc files
- Public template xml
- Changing the Monitor Interval
- Updated Calibration app for SoC and NCP
- Added new example - aws logging stats, Master application, async select app
- Added NCP Support for examples - HTTP client, wlan throughput v6 
- SQA Bugs - SI91X-13870, SI91X-13308, SI91X-13997, SI91X-14122, SI91X-14150, SI91X-14125, SI91X-13486, SI91X-14185

**BLE**

- Socket async feature for TCP TX RX
- Port wlan https v6 ble dual role application 
- Fixed the issue with continuous tx/rx in BLE 917 NCP ble_heart_rate application
- Added NCP support for Wlan station ble provisioning with aws cloud, ble_powersave
- SQA Bugs - SI91X-14027

**CoEx** 

- None

**System**

- None
## **Recommendations**
**System**

- The current revision of SiWx917 B0 has:
  - RAM memory of 672k bytes which can be shared between TA and M4 processors in NCP/SoC mode. The following memory configuration modes are supported.
    - EXT\_FEAT\_672K\_M4SS\_0K- This mode configures TA with 672k and M4 with 0K bytes of memory which is applicable only in the case of NCP mode
  - The below configurations are applicable in SoC mode and can be configured based on the application requirement By default EXT\_FEAT\_352K\_M4SS\_320K configuration will be selected in SoC mode
    - EXT\_FEAT\_480K\_M4SS\_192K - This mode configures TA with 480k and M4 with 192K bytes of memory
    - EXT\_FEAT\_416K\_M4SS\_256K - This mode configures TA with 416k and M4 with 256K bytes of memory
    - EXT\_FEAT\_352K\_M4SS\_320K - This mode configures TA with 352k and M4 with 320K bytes of memory
  - The currently supported memory configuration for NCP mode is 672K\_M4SS\_0K.
  - SoC mode should not use 672k\_M4SS\_0k memory configuration.
- Set the recommended Power Save Profile (PSP) type to Enhanced Max PSP.

**IDE**

- Download the latest Simplicity Studio (SV5.7.0.1)
- Refer to the latest version of the SoC/NCP "Getting-Started-with-SiWx917" guide for more details

**Network Stack**

- The recommended embedded MQTT Publish payload is 1 kBytes.

**Wi-Fi**

- It is recommended to enable bit 16 of the 'Extended TCP IP Feature' bit map in the opermode command for all Wi-Fi Socket operations from the host to ensure graceful handling during asynchronous closures from the peer.
- Aggregation (bit 2 of feature\_bit\_map) is recommended to be enabled in opermode. This enables software to aggregate multiple packets to achieve better throughput
- TCP retransmission count value is recommended to be 30 or higher so that the TCP does not disconnect while the rejoin happens.
- To restart the module, the application needs to call sl\_wifi\_deinit() followed by sl\_wifi\_init().
- Register 'Join Fail Callback' function every time when join is called, as in the rejoin failure path the callback is deregistered. If not done, this might result in a scan not functioning on rejoin failure.
- User can enable SL\_SI91X\_EXT\_TCP\_IP\_SSL\_16K\_RECORD in 'Extended TCP IP Feature'bit map in opermode, if HTTPS download is failing after receiving HTTP headers..
- iTWT setup is recommended after IP assignment/TCP connection/application specific socket connections.
- When using sl\_wifi\_enable\_target\_wakeup\_time API, increase TCP / ARP Timeouts at the remote side depending upon the configured TWT interval configured.
- In case of TWT+coex, when using sl\_wifi\_enable\_target\_wakeup\_time API, use TWT wake duration <= 16 ms and TWT wake interval >= 1 sec. If wake duration > 16 ms or TWT wake interval < 1sec, there might be performance issues.
- For iTWT GTK Interval Should be kept max possible value or zero. If GTK interval is not configurable, recommended TWT interval (in case of sl\_wifi\_enable\_target\_wakeup\_time API) or RX Latency (in case of sl\_wifi\_target\_wake\_time\_auto\_selection API) is less than 4sec.
- Disable Power Save for High Throughput Applications.
- The application needs to ensure that it sets RTC with the correct timestamp when the feature is enabled before establishing the SSL connection.
- The timeout value should not be less than 1 second for socket select and socket receive calls. Timeout value of less than 1 second is not currently supported.
- When sl\_wifi\_enable\_target\_wakeup\_time API is used, configuring TWT Wake interval beyond 1 min might lead to disconnections from the AP. Recommended to use TWT wakeup interval of less than or equal to 1 min.
- Embedded MQTT keep alive interval should be either 0 or a value greater than 35 seconds.
- When using sl\_wifi\_enable\_target\_wakeup\_time API, it is recommended to set missed\_beacon\_count of sl\_wifi\_set\_advanced\_client\_configuration API greater than 2 times of the configured TWT Interval.

**BLE**

- In BLE, the recommended range of Connection Interval in
  - Power Save (BLE Only) - 100 ms to 1.28 s.
- In BLE, during Connection, the configuration of Scan Interval and Scan Window with the same value is not recommended. The suggested ratio of Scan Window to Scan Interval is 3:4.
- In BLE, if a device is acting as Central, the scan window (in set\_scan\_params and create\_connection commands) must be less than the existing Connection Interval. The suggested ratio of Scan Window to Connection Interval is 2:3.
- In BLE mode, if scanning and advertising are in progress on the SiWx91x module and it subsequently gets connected and moves to the central role, scanning stops else if it moves to the peripheral role, advertising stops. To further establish a connection to another peripheral device or to a central device, the application should give a command for starting advertising and scanning again.

**Co-Existence**

- For concurrent Wi-Fi + BLE, and while a Wi-Fi connection is active, we recommend setting the ratio of the BLE scan window to BLE scan interval to 1:3 or 1:4.
- Wi-Fi + BLE Advertising
  - All standard advertising intervals are supported. As Wi-Fi throughput is increased, a slight difference in on-air advertisements compared to configured intervals may be observed.
  - BLE advertising is skipped if the advertising interval collides with Wi-Fi activity.
- Wi-Fi + BLE scanning
  - All standard scan intervals are supported. For better scan results, we recommend setting the ratio of the BLE scan window to BLE scan interval to 1:3 or 1:4.
  - BLE scanning will be stopped for intervals that collide with Wi-Fi activity.
- Wi-Fi + BLE Central/Peripheral Connections
  - All standard connection intervals are supported.
  - For a stable connection, use optimal connection intervals and max supervision timeout in the presence of Wi-Fi activity.
- Wi-Fi + BLE Central/Peripheral Data Transfer
  - To achieve higher throughput for both Wi-Fi and BLE, use medium connection intervals, such as 45 to 80 ms with maximum supervision timeout.
  - Ensure Wi-Fi activity consumes lower intervals.
## **Known Issues**
**Sensorhub**

  - Support for ADC FIFO Mode and Multi channel is open
  - Support for ADC Powersave is open
  
**Network Stack**

- Sometimes during SSL Handshake, ECC curve parameters generated are wrong, resulting in connection failure with BBD2 error. However, this recovers in the next attempt.
- Randomize the client port if using rapid connect/disconnect of the MQTT session on the same client port with the power save.
- Secure SSL renegotiation not supported in Embedded Networking Stack.

**Wi-Fi**

- TWT device (STA) may not go to sleep in between TWT intervals in case of burst data traffics with data size more than the configured 'average tx throughput', until completion of data transfer. 
- There are performance and IOP issues with MU MIMO.
- WPA3 Connection with the Hunting and Pecking algorithm takes about 3-4 seconds.
- Issue observed with WPA2 Enterprise Connectivity using Microsoft RADIUS Server.
- Low Wi-Fi+BLE throughput
- TCP/UDP TX/RX Data stall observed in CoEx scenarios
- Observed HTTPS Continuous download fails with TA Power save
- Performance improvements are in progress for lower performance metrics.
- Observed interop issue (connectivity failure) with few AP's when device reset/reboot happens on active connection.
- In concurrent mode, AP restart fails after stopping it with ap\_stop command. 
- DUT deep sleep will not work after stopping AP with ap\_stop command.
- Unable to get SNTP async events when coex mode and Power save is enabled
- Fine Tuning 802.11ax Spectral mask in Progress
- Fine Tuning 11b mask in Ch11 in progress
- DUT is unable to connect to the AP with WPA3 security when we enable coex mode (WLAN+BLE) in opermode
- Socket listen API is failing from the second iteration
- Disconnections observed with Netgear RAX120 AP in WPA3 security 
- Observed connection failures with some AP's in more channel congestion open lab environment

**BLE**

- M4 Power save with RTOS is not supported for BLE scan and data transfer in SoC Mode.
- BLE anchor points will experience a miss rate of approximately 10%, when the slave latency is enabled.
- When power save is enabled, the device stops sending BLE scan requests after 20 seconds.
- DUT hangs when transmitting BLE notification with codded PHY rates of 125kbps and 500kbps, when DLE is enabled. 
- DUT is not transmitting packets continuously over the air in BLE test modes.
- After connecting to the remote device using gatt\_test applications, GATT APIs could not be triggered. 
- DUT hangs during multiple iterations of BLE connect and disconnect tests with TA and M4 power enabled.

**Co-Existence**

- Observed HTTP continuous download is not happening in Powersave mode after BLE connection established using wifi\_https\_ble\_dual\_role application
- Observed DUT hang while Wi-Fi UDP Tx and BLE continuous scan run for long time.

**System**

- None
### **MCU**
- Refer to the respective Radio board user guides for specific pinout details. Examples are targeted to a specific version mentioned in the respective readme.
- Few peripherals like WDT when configured with RO clock is not working as expected. No impact on the feature but the clocks are not accurate.
## **Limitations and Unsupported Features**
**Wi-Fi/Network Stack**

- TLS 1.3 Server is not supported
- In AP mode, IPv6 Router Advertisements are not supported. Although STA connected to the APUT can transfer IPv6 data to the peers by using SLAAC for address configuration.
- When sl\_wifi\_enable\_target\_wake\_time() API is used, observed occasional MQTT disconnections with longer TWT intervals (>30secs) with embedded MQTT + TWT.
- AMSDU TX is not supported.
- Fragmentation is not supported.
- AMSDUs within AMPDU is not supported.
- Currently, the module does not support Radio Measurement Requests feature of CCX V2
- 802.11k is not supported
- 40 MHz bandwidth for 2.4 GHz band is not supported.
- 802.11J channel 14 is not supported.
- MQTT versions 3 and 4 are supported.
- Maximum of 3 SSL connections are supported in Wi-Fi alone mode.
- In SSL ECC Curve ID supported is 23. SSL handshake with 3rd party clients depends on the SSL ECC Curve ID.
- LP mode is not supported.
- In iTWT mode, downlink data traffic should be limited. Disconnections may be observed if AP fails to send all the buffered data in the next TWT Service Period.
- Number of MBSSIDs processed is limited by the beacon length that can be processed by the stack (which is limited to 1024 bytes). Beacons greater than 1024 Bytes in length will not be processed.
- In A0 SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations
- CoEx + EAP Security in 352K/320k is not feasible. This issue is observed due to a lack of memory in the 352k/320k Memory Configuration. It is supported with other EXT\_FEAT\_416K\_M4SS\_256K and EXT\_FEAT\_480K\_M4SS\_192K memory configurations.
- UL MUMIMO is not supported.
- The embedded HTTP server is not supported.
- Baremetal is not supported
- Compared to SoC mode, NCP mode has fewer examples, but more will be enabled in upcoming releases.

**BLE**

- For BLE, if the connection is established with a small connection interval (less than 15 ms), simultaneous roles (i.e., Central + Scanning and Peripheral + Advertising) are not supported.
- BLE maximum two concurrent connections are supported, which can be either a connection to two peripheral devices, to one central and one peripheral device or two central devices.
- BLE Slave latency value is valid up to 32 only.
- BLE TX/RX throughput is less when tested with EFM as compared to EFR
- Maximum supported AE data length is 200 bytes.
- Supports only two ADV\_EXT sets.
- Supports only two BLE connections (1 Central and 1 Peripheral) with AE.
- Advertising Extension feature is not supported in Coexistence.
- The demo's ae\_central & ae\_peripheral are not supported with TA\_352K\_M4\_320K RAM configuration. 

**MCU**

- ULP Peripherals examples configurations are for RAM-based execution, as flash is powered off in ULP Mode.
- On 4338a board, two I2C instances(I2C1 and I2C2) are using same GPIOs, so support is not there for using two I2C instances simultaneously.
- I2C High speed mode not supported.
- Manual chip select option is not supported when using GSPI and SSI.

**Simplicity Studio and Commander**

- Default GDB debug configuration is not supported for SoC projects, work around details provided in "Getting-Started-with-SiWx917"
- Observing flash download failures(ERROR 108) for a few image sizes
- While creating project through Simplicity Studio, "copy contents" option not supported.
- Simplicity commander does not support options under "Debug Lock tools" . 
## **Terminology**

|**Term**|**Description**|
| :-: | :-: |
|**New Features**|These items are new to this release|
|**Changes/Issues Fixed**|Changes made to existing features found in previous software releases.|
||Enhancements to existing product flow and feature set.|
||Bug fixes done in the release|
|**Deprecated Items**|Features or functions or APIs that are removed from the distributed release to align with the software roadmap|
|**Known Issues**|Features or functions that do not work as planned at the time of release. Workarounds may be offered to meet short-term development goals, but longer-term solutions will be added in future software releases|
|**Limitations/Recommendations**|Describes the limitations on product usage and recommendations for optimal use cases|
## **Note**
- Change SPI frequency to 12.5Mhz while measuring BLE throughput with EFR32

<br>

**WiSeConnect3\_SDK\_3.1.0-rc4 Release Notes**

This SDK package supports SoC Mode and NCP Mode for SiWx917:

- In SoC Mode: Customer Applications can run on Cortex M4. Wireless, network, and security stacks run on the Wireless subsystem.
- In NCP mode: Wireless, network, and security stacks run on the Wireless subsystem. Customer applications run on the external host MCU.
- Silicon Labs' SiWx917 includes an ultra-low power Wi-Fi 6 plus Bluetooth Low Energy (BLE) 5.1 wireless subsystem and an integrated micro-controller application subsystem.

Note: Use Simplicity Studio version SV5.7.0.1 onwards

**SoC Highlights**

- **Operating Modes** : Wi-Fi STA (802.11ax, 802.11n), Wi-Fi 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + BLE
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n, 802.11ax, BLE 5.1
- **Multiple Ultra Low Power Modes** : Support Ultra low power Wi-Fi Standby associated current in Wi-Fi 4 mode, Ultra low power Wi-Fi Standby associated current in Wi-Fi 6 mode leveraging TWT, Always on Cloud connected power, BLE connected power, and, deep sleep ULP mode
- **MCU examples** :  GPIO, I2C, Calendar,  SPI, SSI, SIO, UDMA, UART/USART, WDT, Timers, Config Timers, ULP (Ultra Low Power) Timers, Sleeptimer, IOSTREAM, NVM3, MEMLCD, SDIO, PWM, ADC, EFUSE, I2S, PSRAM
- **Wi-Fi** : 2.4GHz Wi-Fi Support - WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and reduces latency
- **Cloud** : Amazon Cloud Connectivity Support, Amazon FreeRTOS
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack, BLE Stack, and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, DNS client
- **IDE** : Simplicity Studio with Windows 10(64-bit), Linux, Mac OS
- **TA/M4 Firmware Update Tool** : Simplicity Commander
- **Hardware kits to evaluate SoC Mode** :
  - Si-MB4002A Main board
  - SiWx917 Radio boards

|**RadioBoard Type**|**SiWx917A0 with Board Version**|**SiWx917B0 with Board Version**|
| :-: | :-: | :-: |
|Common flash|Si917-BRD4325A(1.0 /1.1 /1.2)|-|
|Common flash|-|Si917-BRD4338A(2.0)|
|Dual flash|Si917-BRD4325B(1.0 /1.1 /1.2)|-|
|External PSRAM|-|Si917-BRD4340A(2.0)|

**NCP Highlights**

- **Host Interface** : SPI
- **Operating Modes** : Wi-Fi STA (802.11ax, 802.11n), Wi-Fi 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + BLE
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n, 802.11ax, BLE 5.1
- **Multiple Ultra Low Power Modes** : Support Ultra low power Wi-Fi Standby associated current in Wi-Fi 4 mode, Ultra low power Wi-Fi Standby associated current in Wi-Fi 6 mode leveraging TWT, Always on Cloud connected power, BLE connected power, and, deep sleep ULP mode.
- **Wi-Fi** : 2.4GHz Wi-Fi Support, WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and reduces latency
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack , BLE Stack and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, DNS Client.
- **IDE** : Simplicity Studio with Windows 10(64-bit)
- **Hardware kits to evaluate NCP Mode**
  - Si917 B0 Single Band Radio Board (BRD4338A)
  - Wireless Pro kit Mainboard BRD4002A Rev A06
  - EFR32xG21 2.4 GHz 20 dBm Radio Board (BRD4180B Rev A02)

**Release Details**

|**Item**|**Details**|
| :-: | :-: |
|Release date|5th Oct, 2023|
|SDK Version|3\.1.0-rc4|
|Firmware Version|1711\.2.9.0.0.21|
|Package Name|WiSeConnect3\_SDK\_3.1.0|
|Supported RTOS|FreeRTOS|
|Operating Modes Supported|Wi-Fi STA, Wi-Fi AP, Wi-Fi STA+BLE, Wi-Fi STA+AP|
|Build Quality|Pre-certification|

**Updating to this Release**

- SiWx917 release consists of two components
  - Wireless Firmware - SiWx917 Firmware Binaries
  - Wiseconnect3 Library - Wiseconnect3 SDK Library runs on the external host in NCP mode and internal Cortex M4 in SoC Mode.
- This release is meant only for use with designs based on SiWx917 Silicon
- The firmware to load in your design are available in the following format:
  - SiWG917-A.2.9.0.0.x.rps - A0 Full-featured firmware binary
  - SiWG917-B.2.9.0.0.x.rps - B0 Full-featured firmware binary

**Features Supported**

**MCU**

- ADC Single Channel, ADC Static Mode, Analog Comparator, Blinky, Bod, CTS, DAC FIFO, DAC Static, GPIO, I2C, I2S, NVM3, OPAMP, PSRAM, PWM, QEI, RTC, SDIO Slave, SPI Master and Slave, UART, UDMA, USART, WDT, USART Master and Slave
- UC Supported Peripherals - GPIO, I2C, Calendar,  SPI, SSI, SIO, UDMA, UART/USART, WDT, Timers , Config Timers, ULP (Ultra Low Power) Timers, SDIO, PWM, ADC, EFUSE, I2S, PSRAM, Sleeptimer, IOSTREAM, MEMLCD.
- ULP (Ultra Low Power) Peripherals - ulp\_gpio, ulp\_adc ulp\_i2c, ulp\_i2s, ulp\_ir\_decoder, ulp\_spi, ulp\_timer, ulp\_uart, ulp\_udma

**Wi-Fi**

- WPA2/WPA3 Personal, WPS and WPA2-EAP Support for Station Mode
- TCP/IP stack with IPv4, IPv6, TCP, UDP, TLS, HTTP/HTTPS, DHCPv4, DHCPv6, MQTT Client, DNS Client, SNTP client.
- Support for SSL client versions TLSV1.0, TLSV1.2, TLSV1.3 and SSL server versions TLSV1.0 and TLSV1.2
- Wi-Fi STA (802.11n/802.11ax) + 802.11n AP Support
- HE (802.11ax) and Individual TWT Feature Support
- Multiple BSSID feature support as an STA
- Secure OTA support on B0 radio boards.
- Support for LWIP network stack
- Support for AWS MQTT library
- Support for BSD and IoT sockets application programming interface(API)

**Bluetooth Low Energy**

- BLE central & peripheral connections are supported.
- Ultra-low power save is supported in Test Mode to support Tx/Rx performance testing

**Power Save**

- The power save profiles supported are Max PSP, enhanced MAX PSP, and 802.11ax TWT.

**Crypto Support**

- AES, SHA, AES-CCM, HMAC and TRNG FW Crypto API support added.
- PSA enabled Mbed TLS support added
  - NVM support is added for key storage
  - Symmetric key storage support added for Volatile and transparent key.
  - TRNG, AES, SHA, ChachaPoly and AES-CCM hardware crypto engine is integrated with PSA crypto.

**Changes and Fixes**

**MCU**

- None

**Wi-Fi**

- Added documentation for the examples - tcp_tx_on_periodic_wakeup, memlcd, m4_firmware_update, sl_si91x_gspi, sl_si91x_i2s_primary and sl_si91x_i2s_secondary
- Bugs resolved: SI91X-13911, SI91X-13955

**BLE**

- None

**System**

- None

**Recommendations**

**System**

- The current revision of SiWx917 A0 has:
  - RAM memory of 704k bytes which can be shared between TA and M4 processors in NCP/SoC mode. The following memory configuration modes are supported.
    - EXT\_FEAT\_704K\_M4SS\_0K- This mode configures TA with 704k and M4 with 0K bytes of memory which is applicable only in the case of NCP mode
  - The below configurations are applicable in SoC mode and can be configured based on the application requirement By Default EXT\_FEAT\_384K\_M4SS\_320K configuration will be selected in SoC mode
    - EXT\_FEAT\_512K\_M4SS\_192K - This mode configures TA with 512k and M4 with 192K bytes of memory
    - EXT\_FEAT\_448K\_M4SS\_256K - This mode configures TA with 448k and M4 with 256K bytes of memory
    - EXT\_FEAT\_384K\_M4SS\_320K - This mode configures TA with 384k and M4 with 320K bytes of memory
  - The currently supported memory configuration for NCP mode is 704K\_M4SS\_0K.
  - SoC mode should not use 704k\_M4SS\_0k Memory configuration.
  - In SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations.
- The current revision of SiWx917 B0 has:
  - RAM memory of 672k bytes which can be shared between TA and M4 processors in NCP/SoC mode. The following memory configuration modes are supported.
    - EXT\_FEAT\_672K\_M4SS\_0K- This mode configures TA with 672k and M4 with 0K bytes of memory which is applicable only in the case of NCP mode
  - The below configurations are applicable in SoC mode and can be configured based on the application requirement By Default EXT\_FEAT\_352K\_M4SS\_320K configuration will be selected in SoC mode
    - EXT\_FEAT\_480K\_M4SS\_192K - This mode configures TA with 480k and M4 with 192K bytes of memory
    - EXT\_FEAT\_416K\_M4SS\_256K - This mode configures TA with 416k and M4 with 256K bytes of memory
    - EXT\_FEAT\_352K\_M4SS\_320K - This mode configures TA with 352k and M4 with 320K bytes of memory
  - The currently supported memory configuration for NCP mode is 672K\_M4SS\_0K.
  - SoC mode should not use 672k\_M4SS\_0k Memory configuration.
  - In SoC mode, M4 power save will work with any memory configuration.
- Set the recommended Power Save Profile (PSP) type to Enhanced Max PSP.

**IDE**

- Download the latest Simplicity Studio (SV5.7.0.1)
- Refer to the latest version of the SoC/NCP "Getting-Started-with-SiWx917" guide for more details

**Wi-Fi**

- It is recommended to enable bit 16 of the 'Extended TCP IP Feature' bit map in the opermode command for all Wi-Fi Socket Operations from the host to ensure graceful handling during asynchronous closures from the peer.
- Aggregation (bit 2 of feature\_bit\_map) is recommended to be enabled in opermode. This enables sw to aggregate multiple packets to achieve better throughput
- TCP retransmission count value is recommended to be 30 or higher so that the TCP does not disconnect while the rejoin happens.
- To restart the module, the application needs to call sl\_wifi\_deinit() followed by sl\_wifi\_init().
- Register 'Join Fail Callback' function every time when join is called, as in the rejoin failure path the callback is deregistered. If not done, this might result in a scan not functioning on rejoin failure.
- User can enable SL\_SI91X\_EXT\_TCP\_IP\_SSL\_16K\_RECORD in 'Extended TCP IP Feature'bit map in opermode, if HTTPS download is failing after receiving HTTP headers..
- iTWT setup is recommended after IP assignment/TCP connection/application connection.
- When using sl\_wifi\_enable\_target\_wakeup\_time API, increase TCP / ARP Timeouts at the remote side depending upon the configured TWT interval configured.
- In case of TWT+coex, when using sl\_wifi\_enable\_target\_wakeup\_time API, use TWT wake duration <= 16 ms and TWT wake interval >= 1 sec. If wake duration > 16 ms or TWT wake interval < 1sec, there might be performance issues.
- For iTWT GTK Interval Should be kept max possible value or zero. If GTK interval is not configurable, recommended TWT interval (in case of sl\_wifi\_enable\_target\_wakeup\_time API)
- Disable Power Save for High Throughput Applications.
- The application needs to ensure that it sets RTC with the correct timestamp when the feature is enabled before establishing the SSL connection.
- Timeout value should be minimum 1 second for socket select and socket receive calls. Timeout value of less than 1 second is not currently supported.
- When sl\_wifi\_enable\_target\_wakeup\_time API is used, configuring TWT Wake interval beyond 1 min might lead to disconnections from the AP. Recommended to use TWT wakeup interval of less than or equal to 1 min.
- MQTT keep alive interval should be either 0 or a value greater than 35 seconds.
- When using sl\_wifi\_enable\_target\_wakeup\_time API, it is recommended to set missed\_beacon\_count of sl\_wifi\_set\_advanced\_client\_configuration API greater than 2 times of the configured TWT Interval.
- Secure OTA: Keys need to be programmed before validating Secure OTA

**BLE**

- In BLE, recommended range of Connection Interval in
  - Power Save (BLE Only) - 100 ms to 1.28 s.
- In BLE, during Connection, the configuration of Scan Interval and Scan Window with the same value is not recommended. The suggested ratio of Scan Window to Scan Interval is 3:4.
- In BLE, if a device is acting as Central, the scan window (in set\_scan\_params and create\_connection commands) must be less than the existing Connection Interval. The suggested ratio of Scan Window to Connection Interval is 2:3.
- In BLE mode, if scanning and advertising are in progress on the SiWx91x module and it subsequently gets connected and moves to the central role, scanning stops else if it moves to the peripheral role, advertising stops. To further establish a connection to another peripheral device or to a central device, the application should give a command for starting advertising and scanning again.

**Co-Existence**

- For concurrent Wi-Fi + BLE, and while a Wi-Fi connection is active, we recommend setting the ratio of the BLE scan window to BLE scan interval to 1:3 or 1:4.
- Wi-Fi + BLE Advertising
  - All standard advertising intervals are supported. As Wi-Fi throughput is increased, a slight difference in on-air advertisements compared to configured intervals may be observed.
  - BLE advertising is skipped if the advertising interval collides with Wi-Fi activity.
- Wi-Fi + BLE scanning
  - All standard scan intervals are supported. For better scan results, we recommend setting the ratio of the BLE scan window to BLE scan interval to 1:3 or 1:4.
  - BLE scanning will be stopped for intervals that collide with Wi-Fi activity.
- Wi-Fi + BLE Central/Peripheral Connections
  - All standard connection intervals are supported.
  - For a stable connection, use optimal connection intervals and max supervision timeout in the presence of Wi-Fi activity.
- Wi-Fi + BLE Central/Peripheral Data Transfer
  - To achieve higher throughput for both Wi-Fi and BLE, use medium connection intervals, such as 45 to 80 ms with maximum supervision timeout.
  - Ensure Wi-Fi activity consumes lower intervals.

**Known Issues**

**Network Stack**

- Sometimes during SSL Handshake, ECC curve parameters generated are wrong, resulting in connection failure with BBD2 error. However, this recovers in the next attempt.
- Recommended MQTT Publish payload is 1 kBytes.
- Randomize the client port if using rapid connect/disconnect of the MQTT session on the same client port with the power save.
- Secure SSL Renegotiation not supported in Embedded Networking Stack.

**Wi-Fi**

- Device with active TWT will not go to sleep when the buffer is full.
- There are performance and IOP issues with MU MIMO.
- WPA3 connection takes 2.5 seconds.
- Issue observed with WPA2 Enterprise Connectivity using Microsoft RADIUS Server.
- EAP connection with certificates of 4096-bit key length is not supported.
- Low Wi-Fi+BLE throughput
- Data stall and disconnection with TCP Tx data transfer when TA power save is enabled
- TCP/UDP TX/RX Data stall observed in CoEx scenarios
- HTTPS Continuous download fails with TA Power save
- Low-performance metrics.
- Data stall when WLAN TCP data transfer, BLE scanning, BLE advertising, and BLE notification are enabled

**BLE**

- BLE Range is less with A0/B0 dual flash Radio boards when compared to A0/B0 common flash Radio boards.

**System**

- None

**MCU**

- Refer the respective Radio board user guides for specific pinout details. Examples are targetted to a specific version mentioned in the respective readme.
- when using SL DMA, UDMA1 is not working as expected
- Few peripherals like WDT when configured with RO clock is not working as expected. No impact on the feature but the clocks are not accurate.

**Co-Existence**

- sl_wifi_init throws insufficient memory(0x2C) error, when low_power_mode feature is enabled in CoEx application with "TA_352K_M4SS_320K" Memory configuration.


**Limitations and Unsupported Features**

**Wi-Fi/Network Stack**

- TLS 1.3 Server is not supported
- In AP mode, IPv6 Router Advertisements are not supported. Although STA connected to the APUT can transfer IPv6 data to the peers by using SLAAC for address configuration.
- When sl\_wifi\_enable\_target\_wakeup\_time() API is used, observed occasional MQTT disconnections with longer TWT intervals (>30secs) with embedded MQTT + TWT.
- AMSDU TX is not supported.
- Fragmentation is not supported.
- AMSDUs within AMPDU is not supported.
- Currently, the module does not support Radio Measurement Requests feature of CCX V2
- 802.11k is not supported
- Short GI is not supported
- 40 MHz bandwidth for 2.4 GHz band is not supported.
- 802.11J channel 14 is not supported.
- MQTT versions 3 and 4 are supported.
- Maximum of 3 SSL connections are supported in Wi-Fi alone mode.
- In SSL ECC Curve ID supported is 23. SSL handshake with 3rd party clients depends on the SSL ECC Curve ID.
- LP mode is not supported.
- Fine Tuning 802.11ax Spectral mask in Progress
- Fine Tuning 11b mask in Ch11 in progress
- In iTWT mode, downlink data traffic should be limited. Disconnections may be observed if AP fails to send all the buffered data in the next TWT Service Period.
- Number of MBSSIDs processed is limited by the beacon length that can be processed by the stack (which is limited to 1024 bytes). Beacons greater than 1024 Bytes in length will not be processed.
- In A0 SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations
- Timeout value should be a minimum 1 second for socket select and socket receive calls. Timeout value less than 1 second is not currently supported.
- M4 OTA update on dual flash will work for same flash sizes only (internal and External).
- CoEx + EAP Security in 352K/320k is not feasible. This issue is observed due to a lack of memory in the 352k/320k Memory Configuration. It is supported with other EXT\_FEAT\_416K\_M4SS\_256K and EXT\_FEAT\_480K\_M4SS\_192K memory configurations.
- UL MUMIMO is not supported.
- The embedded HTTP server is not supported.
- Baremetal is not supported

**BLE**

- For BLE, if the connection is established with a small connection interval (less than 15 ms), simultaneous roles (i.e., Central + Scanning and Peripheral + Advertising) are not supported.
- BLE maximum two concurrent connections are supported, which can be either a connection to two peripheral devices, to one central and one peripheral device or two central devices.
- BLE Slave latency value is valid up to 32 only.
- BLE TX/RX throughput is less when tested with EFM as compared to EFR
- Maximum supported AE data length is 200 bytes.
- Supports only two ADV\_EXT sets.
- Supports only two BLE connections( 1 Central and 1 Peripheral) with AE.
- Advertising Extension feature is not supported in Coexistence.

**MCU**

- ULP Peripherals examples configurations are for RAM-based execution, as flash is powered off in ULP Mode
- On 4338a board, two I2C instances(I2C1 and I2C2) are using same GPIOs ,so support is not there for using two I2C instances simultaneously
- I2C Fast and High speed mode not supported
- when using GSPI and SSI, manual chip select option not supported

**Simplicity Studio and Commander**

- Default GDB debug configuration is not supported for SoC projects, work around details provided in "Getting-Started-with-SiWx917"
- Observing flash download failures(ERROR 108) for a few image sizes
- While creating project through Simplicity Studio, "copy contents" option not supported.
- Simplicity commander does not support options under "Debug Lock tools" .

**Terminology**

|**Term**|**Description**|
| :-: | :-: |
|**New Features**|These items are new to this release|
|**Changes/Issues Fixed**|Changes made to existing features found in previous software releases.|
||Enhancements to existing product flow and feature set.|
||Bug fixes done in the Release|
|**Deprecated Items**|Features or functions or APIs that are removed from the distributed release to align with the software roadmap|
|**Known Issues**|Features or functions that do not work as planned at the time of release. Workarounds may be offered to meet short-term development goals, but longer-term solutions will be added in future software releases|
|**Limitations/Recommendations**|Describes the limitations on product usage and recommendations for optimal use cases|

**Note**

- NA

<br>


**WiSeConnect3\_SDK\_3.1.0-rc3 Release Notes**

This SDK package supports SoC Mode and NCP Mode for SiWx917:

- In SoC Mode: Customer Applications can run on Cortex M4. Wireless, network, and security stacks run on the Wireless subsystem.
- In NCP mode: Wireless, network, and security stacks run on the Wireless subsystem. Customer applications run on the external host MCU.
- Silicon Labs' SiWx917 includes an ultra-low power Wi-Fi 6 plus Bluetooth Low Energy (BLE) 5.1 wireless subsystem and an integrated micro-controller application subsystem.

Note: Use Simplicity Studio version SV5.7.0.1 onwards

**SoC Highlights**

- **Operating Modes** : Wi-Fi STA (802.11ax, 802.11n), Wi-Fi 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + BLE
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n, 802.11ax, BLE 5.1
- **Multiple Ultra Low Power Modes** : Support Ultra low power Wi-Fi Standby associated current in Wi-Fi 4 mode, Ultra low power Wi-Fi Standby associated current in Wi-Fi 6 mode leveraging TWT, Always on Cloud connected power, BLE connected power, and, deep sleep ULP mode
- **MCU examples** :  GPIO, I2C, Calendar,  SPI, SSI, SIO, UDMA, UART/USART, WDT, Timers, Config Timers, ULP (Ultra Low Power) Timers, Sleeptimer, IOSTREAM, NVM3, MEMLCD, SDIO, PWM, ADC, EFUSE, I2S, PSRAM
- **Wi-Fi** : 2.4GHz Wi-Fi Support - WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and reduces latency
- **Cloud** : Amazon Cloud Connectivity Support, Amazon FreeRTOS
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack, BLE Stack, and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, DNS client
- **IDE** : Simplicity Studio with Windows 10(64-bit), Linux, Mac OS
- **TA/M4 Firmware Update Tool** : Simplicity Commander
- **Hardware kits to evaluate SoC Mode** :
  - Si-MB4002A Main board
  - SiWx917 Radio boards

|**RadioBoard Type**|**SiWx917A0 with Board Version**|**SiWx917B0 with Board Version**|
| :-: | :-: | :-: |
|Common flash|Si917-BRD4325A(1.0 /1.1 /1.2)|-|
|Common flash|-|Si917-BRD4338A(2.0)|
|Dual flash|Si917-BRD4325B(1.0 /1.1 /1.2)|-|
|External PSRAM|-|Si917-BRD4340A(2.0)|

**NCP Highlights**

- **Host Interface** : SPI
- **Operating Modes** : Wi-Fi STA (802.11ax, 802.11n), Wi-Fi 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + BLE
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n, 802.11ax, BLE 5.1
- **Multiple Ultra Low Power Modes** : Support Ultra low power Wi-Fi Standby associated current in Wi-Fi 4 mode, Ultra low power Wi-Fi Standby associated current in Wi-Fi 6 mode leveraging TWT, Always on Cloud connected power, BLE connected power, and, deep sleep ULP mode.
- **Wi-Fi** : 2.4GHz Wi-Fi Support, WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and reduces latency
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack , BLE Stack and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, DNS Client.
- **IDE** : Simplicity Studio with Windows 10(64-bit)
- **Hardware kits to evaluate NCP Mode**
  - Si917 B0 Single Band Radio Board (BRD4338A)
  - Wireless Pro kit Mainboard BRD4002A Rev A06
  - EFR32xG21 2.4 GHz 20 dBm Radio Board (BRD4180B Rev A02)

**Release Details**

|**Item**|**Details**|
| :-: | :-: |
|Release date|3rd Oct, 2023|
|SDK Version|3\.1.0-rc3|
|Firmware Version|1711\.2.9.0.0.21|
|Package Name|WiSeConnect3\_SDK\_3.1.0|
|Supported RTOS|FreeRTOS|
|Operating Modes Supported|Wi-Fi STA, Wi-Fi AP, Wi-Fi STA+BLE, Wi-Fi STA+AP|
|Build Quality|Pre-certification|

**Updating to this Release**

- SiWx917 release consists of two components
  - Wireless Firmware - SiWx917 Firmware Binaries
  - Wiseconnect3 Library - Wiseconnect3 SDK Library runs on the external host in NCP mode and internal Cortex M4 in SoC Mode.
- This release is meant only for use with designs based on SiWx917 Silicon
- The firmware to load in your design are available in the following format:
  - SiWG917-A.2.9.0.0.x.rps - A0 Full-featured firmware binary
  - SiWG917-B.2.9.0.0.x.rps - B0 Full-featured firmware binary

**Features Supported**

**MCU**

- ADC Single Channel, ADC Static Mode, Analog Comparator, Blinky, Bod, CTS, DAC FIFO, DAC Static, GPIO, I2C, I2S, NVM3, OPAMP, PSRAM, PWM, QEI, RTC, SDIO Slave, SPI Master and Slave, UART, UDMA, USART, WDT, USART Master and Slave
- UC Supported Peripherals - GPIO, I2C, Calendar,  SPI, SSI, SIO, UDMA, UART/USART, WDT, Timers , Config Timers, ULP (Ultra Low Power) Timers, SDIO, PWM, ADC, EFUSE, I2S, PSRAM, Sleeptimer, IOSTREAM, MEMLCD.
- ULP (Ultra Low Power) Peripherals - ulp\_gpio, ulp\_adc ulp\_i2c, ulp\_i2s, ulp\_ir\_decoder, ulp\_spi, ulp\_timer, ulp\_uart, ulp\_udma

**Wi-Fi**

- WPA2/WPA3 Personal, WPS and WPA2-EAP Support for Station Mode
- TCP/IP stack with IPv4, IPv6, TCP, UDP, TLS, HTTP/HTTPS, DHCPv4, DHCPv6, MQTT Client, DNS Client, SNTP client.
- Support for SSL client versions TLSV1.0, TLSV1.2, TLSV1.3 and SSL server versions TLSV1.0 and TLSV1.2
- Wi-Fi STA (802.11n/802.11ax) + 802.11n AP Support
- HE (802.11ax) and Individual TWT Feature Support
- Multiple BSSID feature support as an STA
- Secure OTA support on B0 radio boards.
- Support for LWIP network stack
- Support for AWS MQTT library
- Support for BSD and IoT sockets application programming interface(API)

**Bluetooth Low Energy**

- BLE central & peripheral connections are supported.
- Ultra-low power save is supported in Test Mode to support Tx/Rx performance testing

**Power Save**

- The power save profiles supported are Max PSP, enhanced MAX PSP, and 802.11ax TWT.

**Crypto Support**

- AES, SHA, AES-CCM, HMAC and TRNG FW Crypto API support added.
- PSA enabled Mbed TLS support added
  - NVM support is added for key storage
  - Symmetric key storage support added for Volatile and transparent key.
  - TRNG, AES, SHA, ChachaPoly and AES-CCM hardware crypto engine is integrated with PSA crypto.

**Changes and Fixes**

**MCU**

- Added crypto examples - PSA ChachaPoly
- Fixed matter warnings in led and button drivers
- SI91X bugs covered: SI91X-14104, SI91X-14118

**Wi-Fi**

- Fixed Cli demo issue with Interrupt based data reception
- Added NCP Support for Powersave Deep sleep and Enterprise client examples
- Added documentation for the Crypto APIs
- Moved the crypto examples to snippets folder from _internal
- Bugs resolved: SI91X-13883

**BLE**

- Added Support for command rsi_ble_req_hci_raw
- Bugs resolved: SI91X-14114, SI91X-13686, RSCDEV-21271

**System**

- None

**Recommendations**

**System**

- The current revision of SiWx917 A0 has:
  - RAM memory of 704k bytes which can be shared between TA and M4 processors in NCP/SoC mode. The following memory configuration modes are supported.
    - EXT\_FEAT\_704K\_M4SS\_0K- This mode configures TA with 704k and M4 with 0K bytes of memory which is applicable only in the case of NCP mode
  - The below configurations are applicable in SoC mode and can be configured based on the application requirement By Default EXT\_FEAT\_384K\_M4SS\_320K configuration will be selected in SoC mode
    - EXT\_FEAT\_512K\_M4SS\_192K - This mode configures TA with 512k and M4 with 192K bytes of memory
    - EXT\_FEAT\_448K\_M4SS\_256K - This mode configures TA with 448k and M4 with 256K bytes of memory
    - EXT\_FEAT\_384K\_M4SS\_320K - This mode configures TA with 384k and M4 with 320K bytes of memory
  - The currently supported memory configuration for NCP mode is 704K\_M4SS\_0K.
  - SoC mode should not use 704k\_M4SS\_0k Memory configuration.
  - In SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations.
- The current revision of SiWx917 B0 has:
  - RAM memory of 672k bytes which can be shared between TA and M4 processors in NCP/SoC mode. The following memory configuration modes are supported.
    - EXT\_FEAT\_672K\_M4SS\_0K- This mode configures TA with 672k and M4 with 0K bytes of memory which is applicable only in the case of NCP mode
  - The below configurations are applicable in SoC mode and can be configured based on the application requirement By Default EXT\_FEAT\_352K\_M4SS\_320K configuration will be selected in SoC mode
    - EXT\_FEAT\_480K\_M4SS\_192K - This mode configures TA with 480k and M4 with 192K bytes of memory
    - EXT\_FEAT\_416K\_M4SS\_256K - This mode configures TA with 416k and M4 with 256K bytes of memory
    - EXT\_FEAT\_352K\_M4SS\_320K - This mode configures TA with 352k and M4 with 320K bytes of memory
  - The currently supported memory configuration for NCP mode is 672K\_M4SS\_0K.
  - SoC mode should not use 672k\_M4SS\_0k Memory configuration.
  - In SoC mode, M4 power save will work with any memory configuration.
- Set the recommended Power Save Profile (PSP) type to Enhanced Max PSP.

**IDE**

- Download the latest Simplicity Studio (SV5.7.0.1)
- Refer to the latest version of the SoC/NCP "Getting-Started-with-SiWx917" guide for more details

**Wi-Fi**

- It is recommended to enable bit 16 of the 'Extended TCP IP Feature' bit map in the opermode command for all Wi-Fi Socket Operations from the host to ensure graceful handling during asynchronous closures from the peer.
- Aggregation (bit 2 of feature\_bit\_map) is recommended to be enabled in opermode. This enables sw to aggregate multiple packets to achieve better throughput
- TCP retransmission count value is recommended to be 30 or higher so that the TCP does not disconnect while the rejoin happens.
- To restart the module, the application needs to call sl\_wifi\_deinit() followed by sl\_wifi\_init().
- Register 'Join Fail Callback' function every time when join is called, as in the rejoin failure path the callback is deregistered. If not done, this might result in a scan not functioning on rejoin failure.
- User can enable SL\_SI91X\_EXT\_TCP\_IP\_SSL\_16K\_RECORD in 'Extended TCP IP Feature'bit map in opermode, if HTTPS download is failing after receiving HTTP headers..
- iTWT setup is recommended after IP assignment/TCP connection/application connection.
- When using sl\_wifi\_enable\_target\_wakeup\_time API, increase TCP / ARP Timeouts at the remote side depending upon the configured TWT interval configured.
- In case of TWT+coex, when using sl\_wifi\_enable\_target\_wakeup\_time API, use TWT wake duration <= 16 ms and TWT wake interval >= 1 sec. If wake duration > 16 ms or TWT wake interval < 1sec, there might be performance issues.
- For iTWT GTK Interval Should be kept max possible value or zero. If GTK interval is not configurable, recommended TWT interval (in case of sl\_wifi\_enable\_target\_wakeup\_time API)
- Disable Power Save for High Throughput Applications.
- The application needs to ensure that it sets RTC with the correct timestamp when the feature is enabled before establishing the SSL connection.
- Timeout value should be minimum 1 second for socket select and socket receive calls. Timeout value of less than 1 second is not currently supported.
- When sl\_wifi\_enable\_target\_wakeup\_time API is used, configuring TWT Wake interval beyond 1 min might lead to disconnections from the AP. Recommended to use TWT wakeup interval of less than or equal to 1 min.
- MQTT keep alive interval should be either 0 or a value greater than 35 seconds.
- When using sl\_wifi\_enable\_target\_wakeup\_time API, it is recommended to set missed\_beacon\_count of sl\_wifi\_set\_advanced\_client\_configuration API greater than 2 times of the configured TWT Interval.
- Secure OTA: Keys need to be programmed before validating Secure OTA

**BLE**

- In BLE, recommended range of Connection Interval in
  - Power Save (BLE Only) - 100 ms to 1.28 s.
- In BLE, during Connection, the configuration of Scan Interval and Scan Window with the same value is not recommended. The suggested ratio of Scan Window to Scan Interval is 3:4.
- In BLE, if a device is acting as Central, the scan window (in set\_scan\_params and create\_connection commands) must be less than the existing Connection Interval. The suggested ratio of Scan Window to Connection Interval is 2:3.
- In BLE mode, if scanning and advertising are in progress on the SiWx91x module and it subsequently gets connected and moves to the central role, scanning stops else if it moves to the peripheral role, advertising stops. To further establish a connection to another peripheral device or to a central device, the application should give a command for starting advertising and scanning again.

**Co-Existence**

- For concurrent Wi-Fi + BLE, and while a Wi-Fi connection is active, we recommend setting the ratio of the BLE scan window to BLE scan interval to 1:3 or 1:4.
- Wi-Fi + BLE Advertising
  - All standard advertising intervals are supported. As Wi-Fi throughput is increased, a slight difference in on-air advertisements compared to configured intervals may be observed.
  - BLE advertising is skipped if the advertising interval collides with Wi-Fi activity.
- Wi-Fi + BLE scanning
  - All standard scan intervals are supported. For better scan results, we recommend setting the ratio of the BLE scan window to BLE scan interval to 1:3 or 1:4.
  - BLE scanning will be stopped for intervals that collide with Wi-Fi activity.
- Wi-Fi + BLE Central/Peripheral Connections
  - All standard connection intervals are supported.
  - For a stable connection, use optimal connection intervals and max supervision timeout in the presence of Wi-Fi activity.
- Wi-Fi + BLE Central/Peripheral Data Transfer
  - To achieve higher throughput for both Wi-Fi and BLE, use medium connection intervals, such as 45 to 80 ms with maximum supervision timeout.
  - Ensure Wi-Fi activity consumes lower intervals.

**Known Issues**

**Network Stack**

- Sometimes during SSL Handshake, ECC curve parameters generated are wrong, resulting in connection failure with BBD2 error. However, this recovers in the next attempt.
- Recommended MQTT Publish payload is 1 kBytes.
- Randomize the client port if using rapid connect/disconnect of the MQTT session on the same client port with the power save.
- Secure SSL Renegotiation not supported in Embedded Networking Stack.

**Wi-Fi**

- Device with active TWT will not go to sleep when the buffer is full.
- There are performance and IOP issues with MU MIMO.
- WPA3 connection takes 2.5 seconds.
- Issue observed with WPA2 Enterprise Connectivity using Microsoft RADIUS Server.
- EAP connection with certificates of 4096-bit key length is not supported.
- Low Wi-Fi+BLE throughput
- Data stall and disconnection with TCP Tx data transfer when TA power save is enabled
- TCP/UDP TX/RX Data stall observed in CoEx scenarios
- HTTPS Continuous download fails with TA Power save
- Low-performance metrics.
- Data stall when WLAN TCP data transfer, BLE scanning, BLE advertising, and BLE notification are enabled

**BLE**

- BLE Range is less with A0/B0 dual flash Radio boards when compared to A0/B0 common flash Radio boards.

**System**

- None

**MCU**

- Refer the respective Radio board user guides for specific pinout details. Examples are targetted to a specific version mentioned in the respective readme.
- when using SL DMA, UDMA1 is not working as expected
- Few peripherals like WDT when configured with RO clock is not working as expected. No impact on the feature but the clocks are not accurate.

**Co-Existence**

- sl_wifi_init throws insufficient memory(0x2C) error, when low_power_mode feature is enabled in CoEx application with "TA_352K_M4SS_320K" Memory configuration.


**Limitations and Unsupported Features**

**Wi-Fi/Network Stack**

- TLS 1.3 Server is not supported
- In AP mode, IPv6 Router Advertisements are not supported. Although STA connected to the APUT can transfer IPv6 data to the peers by using SLAAC for address configuration.
- When sl\_wifi\_enable\_target\_wakeup\_time() API is used, observed occasional MQTT disconnections with longer TWT intervals (>30secs) with embedded MQTT + TWT.
- AMSDU TX is not supported.
- Fragmentation is not supported.
- AMSDUs within AMPDU is not supported.
- Currently, the module does not support Radio Measurement Requests feature of CCX V2
- 802.11k is not supported
- Short GI is not supported
- 40 MHz bandwidth for 2.4 GHz band is not supported.
- 802.11J channel 14 is not supported.
- MQTT versions 3 and 4 are supported.
- Maximum of 3 SSL connections are supported in Wi-Fi alone mode.
- In SSL ECC Curve ID supported is 23. SSL handshake with 3rd party clients depends on the SSL ECC Curve ID.
- LP mode is not supported.
- Fine Tuning 802.11ax Spectral mask in Progress
- Fine Tuning 11b mask in Ch11 in progress
- In iTWT mode, downlink data traffic should be limited. Disconnections may be observed if AP fails to send all the buffered data in the next TWT Service Period.
- Number of MBSSIDs processed is limited by the beacon length that can be processed by the stack (which is limited to 1024 bytes). Beacons greater than 1024 Bytes in length will not be processed.
- In A0 SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations
- Timeout value should be a minimum 1 second for socket select and socket receive calls. Timeout value less than 1 second is not currently supported.
- M4 OTA update on dual flash will work for same flash sizes only (internal and External).
- CoEx + EAP Security in 352K/320k is not feasible. This issue is observed due to a lack of memory in the 352k/320k Memory Configuration. It is supported with other EXT\_FEAT\_416K\_M4SS\_256K and EXT\_FEAT\_480K\_M4SS\_192K memory configurations.
- UL MUMIMO is not supported.
- The embedded HTTP server is not supported.
- Baremetal is not supported

**BLE**

- For BLE, if the connection is established with a small connection interval (less than 15 ms), simultaneous roles (i.e., Central + Scanning and Peripheral + Advertising) are not supported.
- BLE maximum two concurrent connections are supported, which can be either a connection to two peripheral devices, to one central and one peripheral device or two central devices.
- BLE Slave latency value is valid up to 32 only.
- BLE TX/RX throughput is less when tested with EFM as compared to EFR
- Maximum supported AE data length is 200 bytes.
- Supports only two ADV\_EXT sets.
- Supports only two BLE connections( 1 Central and 1 Peripheral) with AE.
- Advertising Extension feature is not supported in Coexistence.

**MCU**

- ULP Peripherals examples configurations are for RAM-based execution, as flash is powered off in ULP Mode
- On 4338a board, two I2C instances(I2C1 and I2C2) are using same GPIOs ,so support is not there for using two I2C instances simultaneously
- I2C Fast and High speed mode not supported
- when using GSPI and SSI, manual chip select option not supported

**Simplicity Studio and Commander**

- Default GDB debug configuration is not supported for SoC projects, work around details provided in "Getting-Started-with-SiWx917"
- Observing flash download failures(ERROR 108) for a few image sizes
- While creating project through Simplicity Studio, "copy contents" option not supported.
- Simplicity commander does not support options under "Debug Lock tools" .

**Terminology**

|**Term**|**Description**|
| :-: | :-: |
|**New Features**|These items are new to this release|
|**Changes/Issues Fixed**|Changes made to existing features found in previous software releases.|
||Enhancements to existing product flow and feature set.|
||Bug fixes done in the Release|
|**Deprecated Items**|Features or functions or APIs that are removed from the distributed release to align with the software roadmap|
|**Known Issues**|Features or functions that do not work as planned at the time of release. Workarounds may be offered to meet short-term development goals, but longer-term solutions will be added in future software releases|
|**Limitations/Recommendations**|Describes the limitations on product usage and recommendations for optimal use cases|

**Note**

- NA

<br>


**WiSeConnect3\_SDK\_3.1.0-rc2 Release Notes**

This SDK package supports SoC Mode and NCP Mode for SiWx917:

- In SoC Mode: Customer Applications can run on Cortex M4. Wireless, network, and security stacks run on the Wireless subsystem.
- In NCP mode: Wireless, network, and security stacks run on the Wireless subsystem. Customer applications run on the external host MCU.
- Silicon Labs' SiWx917 includes an ultra-low power Wi-Fi 6 plus Bluetooth Low Energy (BLE) 5.1 wireless subsystem and an integrated micro-controller application subsystem.

Note: Use Simplicity Studio version SV5.7.0.1 onwards

**SoC Highlights**

- **Operating Modes** : Wi-Fi STA (802.11ax, 802.11n), Wi-Fi 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + BLE
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n, 802.11ax, BLE 5.1
- **Multiple Ultra Low Power Modes** : Support Ultra low power Wi-Fi Standby associated current in Wi-Fi 4 mode, Ultra low power Wi-Fi Standby associated current in Wi-Fi 6 mode leveraging TWT, Always on Cloud connected power, BLE connected power, and, deep sleep ULP mode
- **MCU examples** :  GPIO, I2C, Calendar,  SPI, SSI, SIO, UDMA, UART/USART, WDT, Timers, Config Timers, ULP (Ultra Low Power) Timers, Sleeptimer, IOSTREAM, NVM3, MEMLCD, SDIO, PWM, ADC, EFUSE, I2S, PSRAM
- **Wi-Fi** : 2.4GHz Wi-Fi Support - WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and reduces latency
- **Cloud** : Amazon Cloud Connectivity Support, Amazon FreeRTOS
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack, BLE Stack, and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, DNS client
- **IDE** : Simplicity Studio with Windows 10(64-bit), Linux, Mac OS
- **TA/M4 Firmware Update Tool** : Simplicity Commander
- **Hardware kits to evaluate SoC Mode** :
  - Si-MB4002A Main board
  - SiWx917 Radio boards

|**RadioBoard Type**|**SiWx917A0 with Board Version**|**SiWx917B0 with Board Version**|
| :-: | :-: | :-: |
|Common flash|Si917-BRD4325A(1.0 /1.1 /1.2)|-|
|Common flash|-|Si917-BRD4338A(2.0)|
|Dual flash|Si917-BRD4325B(1.0 /1.1 /1.2)|-|
|External PSRAM|-|Si917-BRD4340A(2.0)|

**NCP Highlights**

- **Host Interface** : SPI
- **Operating Modes** : Wi-Fi STA (802.11ax, 802.11n), Wi-Fi 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + BLE
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n, 802.11ax, BLE 5.1
- **Multiple Ultra Low Power Modes** : Support Ultra low power Wi-Fi Standby associated current in Wi-Fi 4 mode, Ultra low power Wi-Fi Standby associated current in Wi-Fi 6 mode leveraging TWT, Always on Cloud connected power, BLE connected power, and, deep sleep ULP mode.
- **Wi-Fi** : 2.4GHz Wi-Fi Support, WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and reduces latency
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack , BLE Stack and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, DNS Client.
- **IDE** : Simplicity Studio with Windows 10(64-bit)
- **Hardware kits to evaluate NCP Mode**
  - Si917 B0 Single Band Radio Board (BRD4338A)
  - Wireless Pro kit Mainboard BRD4002A Rev A06
  - EFR32xG21 2.4 GHz 20 dBm Radio Board (BRD4180B Rev A02)

**Release Details**

|**Item**|**Details**|
| :-: | :-: |
|Release date|26th Sep, 2023|
|SDK Version|3\.1.0-rc2|
|Firmware Version|1711\.2.9.0.0.21|
|Package Name|WiSeConnect3\_SDK\_3.1.0|
|Supported RTOS|FreeRTOS|
|Operating Modes Supported|Wi-Fi STA, Wi-Fi AP, Wi-Fi STA+BLE, Wi-Fi STA+AP|
|Build Quality|Pre-certification|

**Updating to this Release**

- SiWx917 release consists of two components
  - Wireless Firmware - SiWx917 Firmware Binaries
  - Wiseconnect3 Library - Wiseconnect3 SDK Library runs on the external host in NCP mode and internal Cortex M4 in SoC Mode.
- This release is meant only for use with designs based on SiWx917 Silicon
- The firmware to load in your design are available in the following format:
  - SiWG917-A.2.9.0.0.x.rps - A0 Full-featured firmware binary
  - SiWG917-B.2.9.0.0.x.rps - B0 Full-featured firmware binary

**Features Supported**

**MCU**

- ADC Single Channel, ADC Static Mode, Analog Comparator, Blinky, Bod, CTS, DAC FIFO, DAC Static, GPIO, I2C, I2S, NVM3, OPAMP, PSRAM, PWM, QEI, RTC, SDIO Slave, SPI Master and Slave, UART, UDMA, USART, WDT, USART Master and Slave
- UC Supported Peripherals - GPIO, I2C, Calendar,  SPI, SSI, SIO, UDMA, UART/USART, WDT, Timers , Config Timers, ULP (Ultra Low Power) Timers, SDIO, PWM, ADC, EFUSE, I2S, PSRAM, Sleeptimer, IOSTREAM, MEMLCD.
- ULP (Ultra Low Power) Peripherals - ulp\_gpio, ulp\_adc ulp\_i2c, ulp\_i2s, ulp\_ir\_decoder, ulp\_spi, ulp\_timer, ulp\_uart, ulp\_udma

**Wi-Fi**

- WPA2/WPA3 Personal, WPS and WPA2-EAP Support for Station Mode
- TCP/IP stack with IPv4, IPv6, TCP, UDP, TLS, HTTP/HTTPS, DHCPv4, DHCPv6, MQTT Client, DNS Client, SNTP client.
- Support for SSL client versions TLSV1.0, TLSV1.2, TLSV1.3 and SSL server versions TLSV1.0 and TLSV1.2
- Wi-Fi STA (802.11n/802.11ax) + 802.11n AP Support
- HE (802.11ax) and Individual TWT Feature Support
- Multiple BSSID feature support as an STA
- Secure OTA support on B0 radio boards.
- Support for LWIP network stack
- Support for AWS MQTT library
- Support for BSD and IoT sockets application programming interface(API)

**Bluetooth Low Energy**

- BLE central & peripheral connections are supported.
- Ultra-low power save is supported in Test Mode to support Tx/Rx performance testing

**Power Save**

- The power save profiles supported are Max PSP, enhanced MAX PSP, and 802.11ax TWT.

**Crypto Support**

- AES, SHA, AES-CCM, HMAC and TRNG FW Crypto API support added.
- PSA enabled Mbed TLS support added
  - NVM support is added for key storage
  - Symmetric key storage support added for Volatile and transparent key.
  - TRNG, AES, SHA, and AES-CCM hardware crypto engine is integrated with PSA crypto.

**Changes and Fixes**

**MCU**

- SI91X bugs covered: SI91X-14081

**Wi-Fi**

- Fixed the join request structure
- Update Readme for TWT_TCP_CLIENT example
- Added crypto examples - ECDH, PSA GCM, PSA HMAC

**BLE**

- Fixed high power numbers issue in BLE PER application with Tx and Rx in SoC mode.

**System**

- None

**Recommendations**

**System**

- The current revision of SiWx917 A0 has:
  - RAM memory of 704k bytes which can be shared between TA and M4 processors in NCP/SoC mode. The following memory configuration modes are supported.
    - EXT\_FEAT\_704K\_M4SS\_0K- This mode configures TA with 704k and M4 with 0K bytes of memory which is applicable only in the case of NCP mode
  - The below configurations are applicable in SoC mode and can be configured based on the application requirement By Default EXT\_FEAT\_384K\_M4SS\_320K configuration will be selected in SoC mode
    - EXT\_FEAT\_512K\_M4SS\_192K - This mode configures TA with 512k and M4 with 192K bytes of memory
    - EXT\_FEAT\_448K\_M4SS\_256K - This mode configures TA with 448k and M4 with 256K bytes of memory
    - EXT\_FEAT\_384K\_M4SS\_320K - This mode configures TA with 384k and M4 with 320K bytes of memory
  - The currently supported memory configuration for NCP mode is 704K\_M4SS\_0K.
  - SoC mode should not use 704k\_M4SS\_0k Memory configuration.
  - In SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations.
- The current revision of SiWx917 B0 has:
  - RAM memory of 672k bytes which can be shared between TA and M4 processors in NCP/SoC mode. The following memory configuration modes are supported.
    - EXT\_FEAT\_672K\_M4SS\_0K- This mode configures TA with 672k and M4 with 0K bytes of memory which is applicable only in the case of NCP mode
  - The below configurations are applicable in SoC mode and can be configured based on the application requirement By Default EXT\_FEAT\_352K\_M4SS\_320K configuration will be selected in SoC mode
    - EXT\_FEAT\_480K\_M4SS\_192K - This mode configures TA with 480k and M4 with 192K bytes of memory
    - EXT\_FEAT\_416K\_M4SS\_256K - This mode configures TA with 416k and M4 with 256K bytes of memory
    - EXT\_FEAT\_352K\_M4SS\_320K - This mode configures TA with 352k and M4 with 320K bytes of memory
  - The currently supported memory configuration for NCP mode is 672K\_M4SS\_0K.
  - SoC mode should not use 672k\_M4SS\_0k Memory configuration.
  - In SoC mode, M4 power save will work with any memory configuration.
- Set the recommended Power Save Profile (PSP) type to Enhanced Max PSP.

**IDE**

- Download the latest Simplicity Studio (SV5.7.0.1)
- Refer to the latest version of the SoC/NCP "Getting-Started-with-SiWx917" guide for more details

**Wi-Fi**

- It is recommended to enable bit 16 of the 'Extended TCP IP Feature' bit map in the opermode command for all Wi-Fi Socket Operations from the host to ensure graceful handling during asynchronous closures from the peer.
- Aggregation (bit 2 of feature\_bit\_map) is recommended to be enabled in opermode. This enables sw to aggregate multiple packets to achieve better throughput
- TCP retransmission count value is recommended to be 30 or higher so that the TCP does not disconnect while the rejoin happens.
- To restart the module, the application needs to call sl\_wifi\_deinit() followed by sl\_wifi\_init().
- Register 'Join Fail Callback' function every time when join is called, as in the rejoin failure path the callback is deregistered. If not done, this might result in a scan not functioning on rejoin failure.
- User can enable SL\_SI91X\_EXT\_TCP\_IP\_SSL\_16K\_RECORD in 'Extended TCP IP Feature'bit map in opermode, if HTTPS download is failing after receiving HTTP headers..
- iTWT setup is recommended after IP assignment/TCP connection/application connection.
- When using sl\_wifi\_enable\_target\_wakeup\_time API, increase TCP / ARP Timeouts at the remote side depending upon the configured TWT interval configured.
- In case of TWT+coex, when using sl\_wifi\_enable\_target\_wakeup\_time API, use TWT wake duration <= 16 ms and TWT wake interval >= 1 sec. If wake duration > 16 ms or TWT wake interval < 1sec, there might be performance issues.
- For iTWT GTK Interval Should be kept max possible value or zero. If GTK interval is not configurable, recommended TWT interval (in case of sl\_wifi\_enable\_target\_wakeup\_time API)
- Disable Power Save for High Throughput Applications.
- The application needs to ensure that it sets RTC with the correct timestamp when the feature is enabled before establishing the SSL connection.
- Timeout value should be minimum 1 second for socket select and socket receive calls. Timeout value of less than 1 second is not currently supported.
- When sl\_wifi\_enable\_target\_wakeup\_time API is used, configuring TWT Wake interval beyond 1 min might lead to disconnections from the AP. Recommended to use TWT wakeup interval of less than or equal to 1 min.
- MQTT keep alive interval should be either 0 or a value greater than 35 seconds.
- When using sl\_wifi\_enable\_target\_wakeup\_time API, it is recommended to set missed\_beacon\_count of sl\_wifi\_set\_advanced\_client\_configuration API greater than 2 times of the configured TWT Interval.
- Secure OTA: Keys need to be programmed before validating Secure OTA

**BLE**

- In BLE, recommended range of Connection Interval in
  - Power Save (BLE Only) - 100 ms to 1.28 s.
- In BLE, during Connection, the configuration of Scan Interval and Scan Window with the same value is not recommended. The suggested ratio of Scan Window to Scan Interval is 3:4.
- In BLE, if a device is acting as Central, the scan window (in set\_scan\_params and create\_connection commands) must be less than the existing Connection Interval. The suggested ratio of Scan Window to Connection Interval is 2:3.
- In BLE mode, if scanning and advertising are in progress on the SiWx91x module and it subsequently gets connected and moves to the central role, scanning stops else if it moves to the peripheral role, advertising stops. To further establish a connection to another peripheral device or to a central device, the application should give a command for starting advertising and scanning again.

**Co-Existence**

- For concurrent Wi-Fi + BLE, and while a Wi-Fi connection is active, we recommend setting the ratio of the BLE scan window to BLE scan interval to 1:3 or 1:4.
- Wi-Fi + BLE Advertising
  - All standard advertising intervals are supported. As Wi-Fi throughput is increased, a slight difference in on-air advertisements compared to configured intervals may be observed.
  - BLE advertising is skipped if the advertising interval collides with Wi-Fi activity.
- Wi-Fi + BLE scanning
  - All standard scan intervals are supported. For better scan results, we recommend setting the ratio of the BLE scan window to BLE scan interval to 1:3 or 1:4.
  - BLE scanning will be stopped for intervals that collide with Wi-Fi activity.
- Wi-Fi + BLE Central/Peripheral Connections
  - All standard connection intervals are supported.
  - For a stable connection, use optimal connection intervals and max supervision timeout in the presence of Wi-Fi activity.
- Wi-Fi + BLE Central/Peripheral Data Transfer
  - To achieve higher throughput for both Wi-Fi and BLE, use medium connection intervals, such as 45 to 80 ms with maximum supervision timeout.
  - Ensure Wi-Fi activity consumes lower intervals.

**Known Issues**

**Network Stack**

- Sometimes during SSL Handshake, ECC curve parameters generated are wrong, resulting in connection failure with BBD2 error. However, this recovers in the next attempt.
- Recommended MQTT Publish payload is 1 kBytes.
- Randomize the client port if using rapid connect/disconnect of the MQTT session on the same client port with the power save.
- Secure SSL Renegotiation not supported in Embedded Networking Stack.

**Wi-Fi**

- Device with active TWT will not go to sleep when the buffer is full.
- There are performance and IOP issues with MU MIMO.
- WPA3 connection takes 2.5 seconds.
- Issue observed with WPA2 Enterprise Connectivity using Microsoft RADIUS Server.
- EAP connection with certificates of 4096-bit key length is not supported.
- Low Wi-Fi+BLE throughput
- Data stall and disconnection with TCP Tx data transfer when TA power save is enabled
- TCP/UDP TX/RX Data stall observed in CoEx scenarios
- HTTPS Continuous download fails with TA Power save
- Low-performance metrics.
- Data stall when WLAN TCP data transfer, BLE scanning, BLE advertising, and BLE notification are enabled

**BLE**

- BLE Range is less with A0/B0 dual flash Radio boards when compared to A0/B0 common flash Radio boards.

**System**

- None

**MCU**

- Refer the respective Radio board user guides for specific pinout details. Examples are targetted to a specific version mentioned in the respective readme.
- when using SL DMA, UDMA1 is not working as expected
- Few peripherals like WDT when configured with RO clock is not working as expected. No impact on the feature but the clocks are not accurate.

**Co-Existence**

- sl_wifi_init throws insufficient memory(0x2C) error, when low_power_mode feature is enabled in CoEx application with "TA_352K_M4SS_320K" Memory configuration.


**Limitations and Unsupported Features**

**Wi-Fi/Network Stack**

- TLS 1.3 Server is not supported
- In AP mode, IPv6 Router Advertisements are not supported. Although STA connected to the APUT can transfer IPv6 data to the peers by using SLAAC for address configuration.
- When sl\_wifi\_enable\_target\_wakeup\_time() API is used, observed occasional MQTT disconnections with longer TWT intervals (>30secs) with embedded MQTT + TWT.
- AMSDU TX is not supported.
- Fragmentation is not supported.
- AMSDUs within AMPDU is not supported.
- Currently, the module does not support Radio Measurement Requests feature of CCX V2
- 802.11k is not supported
- Short GI is not supported
- 40 MHz bandwidth for 2.4 GHz band is not supported.
- 802.11J channel 14 is not supported.
- MQTT versions 3 and 4 are supported.
- Maximum of 3 SSL connections are supported in Wi-Fi alone mode.
- In SSL ECC Curve ID supported is 23. SSL handshake with 3rd party clients depends on the SSL ECC Curve ID.
- LP mode is not supported.
- Fine Tuning 802.11ax Spectral mask in Progress
- Fine Tuning 11b mask in Ch11 in progress
- In iTWT mode, downlink data traffic should be limited. Disconnections may be observed if AP fails to send all the buffered data in the next TWT Service Period.
- Number of MBSSIDs processed is limited by the beacon length that can be processed by the stack (which is limited to 1024 bytes). Beacons greater than 1024 Bytes in length will not be processed.
- In A0 SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations
- Timeout value should be a minimum 1 second for socket select and socket receive calls. Timeout value less than 1 second is not currently supported.
- M4 OTA update on dual flash will work for same flash sizes only (internal and External).
- CoEx + EAP Security in 352K/320k is not feasible. This issue is observed due to a lack of memory in the 352k/320k Memory Configuration. It is supported with other EXT\_FEAT\_416K\_M4SS\_256K and EXT\_FEAT\_480K\_M4SS\_192K memory configurations.
- UL MUMIMO is not supported.
- The embedded HTTP server is not supported.
- Baremetal is not supported

**BLE**

- For BLE, if the connection is established with a small connection interval (less than 15 ms), simultaneous roles (i.e., Central + Scanning and Peripheral + Advertising) are not supported.
- BLE maximum two concurrent connections are supported, which can be either a connection to two peripheral devices, to one central and one peripheral device or two central devices.
- BLE Slave latency value is valid up to 32 only.
- BLE TX/RX throughput is less when tested with EFM as compared to EFR
- Maximum supported AE data length is 200 bytes.
- Supports only two ADV\_EXT sets.
- Supports only two BLE connections( 1 Central and 1 Peripheral) with AE.
- Advertising Extension feature is not supported in Coexistence.

**MCU**

- ULP Peripherals examples configurations are for RAM-based execution, as flash is powered off in ULP Mode
- On 4338a board, two I2C instances(I2C1 and I2C2) are using same GPIOs ,so support is not there for using two I2C instances simultaneously
- I2C Fast and High speed mode not supported
- when using GSPI and SSI, manual chip select option not supported

**Simplicity Studio and Commander**

- Default GDB debug configuration is not supported for SoC projects, work around details provided in "Getting-Started-with-SiWx917"
- Observing flash download failures(ERROR 108) for a few image sizes
- While creating project through Simplicity Studio, "copy contents" option not supported.
- Simplicity commander does not support options under "Debug Lock tools" .

**Terminology**

|**Term**|**Description**|
| :-: | :-: |
|**New Features**|These items are new to this release|
|**Changes/Issues Fixed**|Changes made to existing features found in previous software releases.|
||Enhancements to existing product flow and feature set.|
||Bug fixes done in the Release|
|**Deprecated Items**|Features or functions or APIs that are removed from the distributed release to align with the software roadmap|
|**Known Issues**|Features or functions that do not work as planned at the time of release. Workarounds may be offered to meet short-term development goals, but longer-term solutions will be added in future software releases|
|**Limitations/Recommendations**|Describes the limitations on product usage and recommendations for optimal use cases|

**Note**

- NA

<br>

**WiSeConnect3\_SDK\_3.1.0-rc1 Release Notes**

This SDK package supports SoC Mode and NCP Mode for SiWx917:

- In SoC Mode: Customer Applications can run on Cortex M4. Wireless, network, and security stacks run on the Wireless subsystem.
- In NCP mode: Wireless, network, and security stacks run on the Wireless subsystem. Customer applications run on the external host MCU.
- Silicon Labs' SiWx917 includes an ultra-low power Wi-Fi 6 plus Bluetooth Low Energy (BLE) 5.1 wireless subsystem and an integrated micro-controller application subsystem.

Note: Use Simplicity Studio version SV5.7.0.1 onwards

**SoC Highlights**

- **Operating Modes** : Wi-Fi STA (802.11ax, 802.11n), Wi-Fi 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + BLE
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n, 802.11ax, BLE 5.1
- **Multiple Ultra Low Power Modes** : Support Ultra low power Wi-Fi Standby associated current in Wi-Fi 4 mode, Ultra low power Wi-Fi Standby associated current in Wi-Fi 6 mode leveraging TWT, Always on Cloud connected power, BLE connected power, and, deep sleep ULP mode
- **MCU examples** :  GPIO, I2C, Calendar,  SPI, SSI, SIO, UDMA, UART/USART, WDT, Timers, Config Timers, ULP (Ultra Low Power) Timers, Sleeptimer, IOSTREAM, NVM3, MEMLCD, SDIO, PWM, ADC, EFUSE, I2S, PSRAM
- **Wi-Fi** : 2.4GHz Wi-Fi Support - WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and reduces latency
- **Cloud** : Amazon Cloud Connectivity Support, Amazon FreeRTOS
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack, BLE Stack, and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, DNS client
- **IDE** : Simplicity Studio with Windows 10(64-bit), Linux, Mac OS
- **TA/M4 Firmware Update Tool** : Simplicity Commander
- **Hardware kits to evaluate SoC Mode** :
  - Si-MB4002A Main board
  - SiWx917 Radio boards

|**RadioBoard Type**|**SiWx917A0 with Board Version**|**SiWx917B0 with Board Version**|
| :-: | :-: | :-: |
|Common flash|Si917-BRD4325A(1.0 /1.1 /1.2)|-|
|Common flash|-|Si917-BRD4338A(2.0)|
|Dual flash|Si917-BRD4325B(1.0 /1.1 /1.2)|-|
|External PSRAM|-|Si917-BRD4340A(2.0)|

**NCP Highlights**

- **Host Interface** : SPI
- **Operating Modes** : Wi-Fi STA (802.11ax, 802.11n), Wi-Fi 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + BLE
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n, 802.11ax, BLE 5.1
- **Multiple Ultra Low Power Modes** : Support Ultra low power Wi-Fi Standby associated current in Wi-Fi 4 mode, Ultra low power Wi-Fi Standby associated current in Wi-Fi 6 mode leveraging TWT, Always on Cloud connected power, BLE connected power, and, deep sleep ULP mode.
- **Wi-Fi** : 2.4GHz Wi-Fi Support, WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and reduces latency
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack , BLE Stack and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, DNS Client.
- **IDE** : Simplicity Studio with Windows 10(64-bit)
- **Hardware kits to evaluate NCP Mode**
  - Si917 B0 Single Band Radio Board (BRD4338A)
  - Wireless Pro kit Mainboard BRD4002A Rev A06
  - EFR32xG21 2.4 GHz 20 dBm Radio Board (BRD4180B Rev A02)

**Release Details**

|**Item**|**Details**|
| :-: | :-: |
|Release date|22th Sep, 2023|
|SDK Version|3\.1.0-rc1|
|Firmware Version|1711\.2.9.0.0.21|
|Package Name|WiSeConnect3\_SDK\_3.1.0|
|Supported RTOS|FreeRTOS|
|Operating Modes Supported|Wi-Fi STA, Wi-Fi AP, Wi-Fi STA+BLE, Wi-Fi STA+AP|
|Build Quality|Pre-certification|

**Updating to this Release**

- SiWx917 release consists of two components
  - Wireless Firmware - SiWx917 Firmware Binaries
  - Wiseconnect3 Library - Wiseconnect3 SDK Library runs on the external host in NCP mode and internal Cortex M4 in SoC Mode.
- This release is meant only for use with designs based on SiWx917 Silicon
- The firmware to load in your design are available in the following format:
  - SiWG917-A.2.9.0.0.x.rps - A0 Full-featured firmware binary
  - SiWG917-B.2.9.0.0.x.rps - B0 Full-featured firmware binary

**Features Supported**

**MCU**

- ADC Single Channel, ADC Static Mode, Analog Comparator, Blinky, Bod, CTS, DAC FIFO, DAC Static, GPIO, I2C, I2S, NVM3, OPAMP, PSRAM, PWM, QEI, RTC, SDIO Slave, SPI Master and Slave, UART, UDMA, USART, WDT, USART Master and Slave
- UC Supported Peripherals - GPIO, I2C, Calendar,  SPI, SSI, SIO, UDMA, UART/USART, WDT, Timers , Config Timers, ULP (Ultra Low Power) Timers, SDIO, PWM, ADC, EFUSE, I2S, PSRAM, Sleeptimer, IOSTREAM, MEMLCD.
- ULP (Ultra Low Power) Peripherals - ulp\_gpio, ulp\_adc ulp\_i2c, ulp\_i2s, ulp\_ir\_decoder, ulp\_spi, ulp\_timer, ulp\_uart, ulp\_udma

**Wi-Fi**

- WPA2/WPA3 Personal, WPS and WPA2-EAP Support for Station Mode
- TCP/IP stack with IPv4, IPv6, TCP, UDP, TLS, HTTP/HTTPS, DHCPv4, DHCPv6, MQTT Client, DNS Client, SNTP client.
- Support for SSL client versions TLSV1.0, TLSV1.2, TLSV1.3 and SSL server versions TLSV1.0 and TLSV1.2
- Wi-Fi STA (802.11n/802.11ax) + 802.11n AP Support
- HE (802.11ax) and Individual TWT Feature Support
- Multiple BSSID feature support as an STA
- Secure OTA support on B0 radio boards.
- Support for LWIP network stack
- Support for AWS MQTT library
- Support for BSD and IoT sockets application programming interface(API)

**Bluetooth Low Energy**

- BLE central & peripheral connections are supported.
- Ultra-low power save is supported in Test Mode to support Tx/Rx performance testing

**Power Save**

- The power save profiles supported are Max PSP, enhanced MAX PSP, and 802.11ax TWT.

**Crypto Support**

- AES, SHA, AES-CCM, HMAC and TRNG FW Crypto API support added.
- PSA enabled Mbed TLS support added
  - NVM support is added for key storage
  - Symmetric key storage support added for Volatile and transparent key.
  - TRNG, AES, SHA, and AES-CCM hardware crypto engine is integrated with PSA crypto.

**Changes and Fixes**

**MCU**

- SI91X bugs covered: SI91X-13974, SI91X-13963, SI91X-13960, SI91X-13931, SI91X-13711, SI91X-13678, SI91X-13677,SI91X-13676, 
                      SI91X-13611, SI91X-13555, SI91X-13554, SI91X-13969, SI91X-13912, SI91X-13855, SI91X-13709, SI91X-13706

**Wi-Fi**


- Added set device region for transmit_test opermode
- print_sl_ipv6_address updated
- Updated TCP Periodic wake up with M4 Sleep wake up
- Added thread safe support for malloc and free functions
- Update Readme for user_gain_table and wlan_rf_test
- Added SNI option for async sockets
- Fixed Soc Reset with M4 security enabled
- Added support for AP STOP feature
- Readme Updates - SI91X-13793, SI91X-13868, SI91X-13769, SI91X-13874, WIFISDK-724 
- Added iostream support in calibration example for letting users enter calib commands via VCOM port
- Fixed Firmware Update getting failed after sending two packets
- Added WPA3 and listen interval getter/setter method
- Added NCP Support for AWS MQTT, tcp_client, twt_tcp_client
- Added crypto examples - hmac, PSA SHA, si91x_psa_asymmetric_key_storage, si91x_psa_symmetric_key_storage, si91x_psa_aes 
- Added new example - aws_device_shadow_logging_stats
- SI91X bugs covered: SI91X-13939, SI91X-13921, SI91X-13184, SI91X-13852, SI91X-13988, SI91X-13884, SI91X-13980,
                      SI91X-13486, SI91X-14004, SI91X-13983, SI91X-13979, SI91X-13406, SI91X-14001, SI91X-13967

**BLE**

- Added new examples -  ble_ae_central, gatt_test, ble_ae_peripheral
- Fixed high power numbers issue in BLE PER application with Tx and Rx in SoC mode.

**System**

- None

**Recommendations**

**System**

- The current revision of SiWx917 A0 has:
  - RAM memory of 704k bytes which can be shared between TA and M4 processors in NCP/SoC mode. The following memory configuration modes are supported.
    - EXT\_FEAT\_704K\_M4SS\_0K- This mode configures TA with 704k and M4 with 0K bytes of memory which is applicable only in the case of NCP mode
  - The below configurations are applicable in SoC mode and can be configured based on the application requirement By Default EXT\_FEAT\_384K\_M4SS\_320K configuration will be selected in SoC mode
    - EXT\_FEAT\_512K\_M4SS\_192K - This mode configures TA with 512k and M4 with 192K bytes of memory
    - EXT\_FEAT\_448K\_M4SS\_256K - This mode configures TA with 448k and M4 with 256K bytes of memory
    - EXT\_FEAT\_384K\_M4SS\_320K - This mode configures TA with 384k and M4 with 320K bytes of memory
  - The currently supported memory configuration for NCP mode is 704K\_M4SS\_0K.
  - SoC mode should not use 704k\_M4SS\_0k Memory configuration.
  - In SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations.
- The current revision of SiWx917 B0 has:
  - RAM memory of 672k bytes which can be shared between TA and M4 processors in NCP/SoC mode. The following memory configuration modes are supported.
    - EXT\_FEAT\_672K\_M4SS\_0K- This mode configures TA with 672k and M4 with 0K bytes of memory which is applicable only in the case of NCP mode
  - The below configurations are applicable in SoC mode and can be configured based on the application requirement By Default EXT\_FEAT\_352K\_M4SS\_320K configuration will be selected in SoC mode
    - EXT\_FEAT\_480K\_M4SS\_192K - This mode configures TA with 480k and M4 with 192K bytes of memory
    - EXT\_FEAT\_416K\_M4SS\_256K - This mode configures TA with 416k and M4 with 256K bytes of memory
    - EXT\_FEAT\_352K\_M4SS\_320K - This mode configures TA with 352k and M4 with 320K bytes of memory
  - The currently supported memory configuration for NCP mode is 672K\_M4SS\_0K.
  - SoC mode should not use 672k\_M4SS\_0k Memory configuration.
  - In SoC mode, M4 power save will work with any memory configuration.
- Set the recommended Power Save Profile (PSP) type to Enhanced Max PSP.

**IDE**

- Download the latest Simplicity Studio (SV5.7.0.1)
- Refer to the latest version of the SoC/NCP "Getting-Started-with-SiWx917" guide for more details

**Wi-Fi**

- It is recommended to enable bit 16 of the 'Extended TCP IP Feature' bit map in the opermode command for all Wi-Fi Socket Operations from the host to ensure graceful handling during asynchronous closures from the peer.
- Aggregation (bit 2 of feature\_bit\_map) is recommended to be enabled in opermode. This enables sw to aggregate multiple packets to achieve better throughput
- TCP retransmission count value is recommended to be 30 or higher so that the TCP does not disconnect while the rejoin happens.
- To restart the module, the application needs to call sl\_wifi\_deinit() followed by sl\_wifi\_init().
- Register 'Join Fail Callback' function every time when join is called, as in the rejoin failure path the callback is deregistered. If not done, this might result in a scan not functioning on rejoin failure.
- User can enable SL\_SI91X\_EXT\_TCP\_IP\_SSL\_16K\_RECORD in 'Extended TCP IP Feature'bit map in opermode, if HTTPS download is failing after receiving HTTP headers..
- iTWT setup is recommended after IP assignment/TCP connection/application connection.
- When using sl\_wifi\_enable\_target\_wakeup\_time API, increase TCP / ARP Timeouts at the remote side depending upon the configured TWT interval configured.
- In case of TWT+coex, when using sl\_wifi\_enable\_target\_wakeup\_time API, use TWT wake duration <= 16 ms and TWT wake interval >= 1 sec. If wake duration > 16 ms or TWT wake interval < 1sec, there might be performance issues.
- For iTWT GTK Interval Should be kept max possible value or zero. If GTK interval is not configurable, recommended TWT interval (in case of sl\_wifi\_enable\_target\_wakeup\_time API)
- Disable Power Save for High Throughput Applications.
- The application needs to ensure that it sets RTC with the correct timestamp when the feature is enabled before establishing the SSL connection.
- Timeout value should be minimum 1 second for socket select and socket receive calls. Timeout value of less than 1 second is not currently supported.
- When sl\_wifi\_enable\_target\_wakeup\_time API is used, configuring TWT Wake interval beyond 1 min might lead to disconnections from the AP. Recommended to use TWT wakeup interval of less than or equal to 1 min.
- MQTT keep alive interval should be either 0 or a value greater than 35 seconds.
- When using sl\_wifi\_enable\_target\_wakeup\_time API, it is recommended to set missed\_beacon\_count of sl\_wifi\_set\_advanced\_client\_configuration API greater than 2 times of the configured TWT Interval.
- Secure OTA: Keys need to be programmed before validating Secure OTA

**BLE**

- In BLE, recommended range of Connection Interval in
  - Power Save (BLE Only) - 100 ms to 1.28 s.
- In BLE, during Connection, the configuration of Scan Interval and Scan Window with the same value is not recommended. The suggested ratio of Scan Window to Scan Interval is 3:4.
- In BLE, if a device is acting as Central, the scan window (in set\_scan\_params and create\_connection commands) must be less than the existing Connection Interval. The suggested ratio of Scan Window to Connection Interval is 2:3.
- In BLE mode, if scanning and advertising are in progress on the SiWx91x module and it subsequently gets connected and moves to the central role, scanning stops else if it moves to the peripheral role, advertising stops. To further establish a connection to another peripheral device or to a central device, the application should give a command for starting advertising and scanning again.

**Co-Existence**

- For concurrent Wi-Fi + BLE, and while a Wi-Fi connection is active, we recommend setting the ratio of the BLE scan window to BLE scan interval to 1:3 or 1:4.
- Wi-Fi + BLE Advertising
  - All standard advertising intervals are supported. As Wi-Fi throughput is increased, a slight difference in on-air advertisements compared to configured intervals may be observed.
  - BLE advertising is skipped if the advertising interval collides with Wi-Fi activity.
- Wi-Fi + BLE scanning
  - All standard scan intervals are supported. For better scan results, we recommend setting the ratio of the BLE scan window to BLE scan interval to 1:3 or 1:4.
  - BLE scanning will be stopped for intervals that collide with Wi-Fi activity.
- Wi-Fi + BLE Central/Peripheral Connections
  - All standard connection intervals are supported.
  - For a stable connection, use optimal connection intervals and max supervision timeout in the presence of Wi-Fi activity.
- Wi-Fi + BLE Central/Peripheral Data Transfer
  - To achieve higher throughput for both Wi-Fi and BLE, use medium connection intervals, such as 45 to 80 ms with maximum supervision timeout.
  - Ensure Wi-Fi activity consumes lower intervals.

**Known Issues**

**Network Stack**

- Sometimes during SSL Handshake, ECC curve parameters generated are wrong, resulting in connection failure with BBD2 error. However, this recovers in the next attempt.
- Recommended MQTT Publish payload is 1 kBytes.
- Randomize the client port if using rapid connect/disconnect of the MQTT session on the same client port with the power save.
- Secure SSL Renegotiation not supported in Embedded Networking Stack.

**Wi-Fi**

- Device with active TWT will not go to sleep when the buffer is full.
- There are performance and IOP issues with MU MIMO.
- WPA3 connection takes 2.5 seconds.
- Issue observed with WPA2 Enterprise Connectivity using Microsoft RADIUS Server.
- EAP connection with certificates of 4096-bit key length is not supported.
- Low Wi-Fi+BLE throughput
- Data stall and disconnection with TCP Tx data transfer when TA power save is enabled
- TCP/UDP TX/RX Data stall observed in CoEx scenarios
- HTTPS Continuous download fails with TA Power save
- Low-performance metrics.
- Data stall when WLAN TCP data transfer, BLE scanning, BLE advertising, and BLE notification are enabled

**BLE**

- BLE Range is less with A0/B0 dual flash Radio boards when compared to A0/B0 common flash Radio boards.

**System**

- None

**MCU**

- Refer the respective Radio board user guides for specific pinout details. Examples are targetted to a specific version mentioned in the respective readme.
- when using SL DMA, UDMA1 is not working as expected
- Few peripherals like WDT when configured with RO clock is not working as expected. No impact on the feature but the clocks are not accurate.

**Co-Existence**

- sl_wifi_init throws insufficient memory(0x2C) error, when low_power_mode feature is enabled in CoEx application with "TA_352K_M4SS_320K" Memory configuration.


**Limitations and Unsupported Features**

**Wi-Fi/Network Stack**

- TLS 1.3 Server is not supported
- In AP mode, IPv6 Router Advertisements are not supported. Although STA connected to the APUT can transfer IPv6 data to the peers by using SLAAC for address configuration.
- When sl\_wifi\_enable\_target\_wakeup\_time() API is used, observed occasional MQTT disconnections with longer TWT intervals (>30secs) with embedded MQTT + TWT.
- AMSDU TX is not supported.
- Fragmentation is not supported.
- AMSDUs within AMPDU is not supported.
- Currently, the module does not support Radio Measurement Requests feature of CCX V2
- 802.11k is not supported
- Short GI is not supported
- 40 MHz bandwidth for 2.4 GHz band is not supported.
- 802.11J channel 14 is not supported.
- MQTT versions 3 and 4 are supported.
- Maximum of 3 SSL connections are supported in Wi-Fi alone mode.
- In SSL ECC Curve ID supported is 23. SSL handshake with 3rd party clients depends on the SSL ECC Curve ID.
- LP mode is not supported.
- Fine Tuning 802.11ax Spectral mask in Progress
- Fine Tuning 11b mask in Ch11 in progress
- In iTWT mode, downlink data traffic should be limited. Disconnections may be observed if AP fails to send all the buffered data in the next TWT Service Period.
- Number of MBSSIDs processed is limited by the beacon length that can be processed by the stack (which is limited to 1024 bytes). Beacons greater than 1024 Bytes in length will not be processed.
- In A0 SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations
- Timeout value should be a minimum 1 second for socket select and socket receive calls. Timeout value less than 1 second is not currently supported.
- M4 OTA update on dual flash will work for same flash sizes only (internal and External).
- CoEx + EAP Security in 352K/320k is not feasible. This issue is observed due to a lack of memory in the 352k/320k Memory Configuration. It is supported with other EXT\_FEAT\_416K\_M4SS\_256K and EXT\_FEAT\_480K\_M4SS\_192K memory configurations.
- UL MUMIMO is not supported.
- The embedded HTTP server is not supported.
- Baremetal is not supported

**BLE**

- For BLE, if the connection is established with a small connection interval (less than 15 ms), simultaneous roles (i.e., Central + Scanning and Peripheral + Advertising) are not supported.
- BLE maximum two concurrent connections are supported, which can be either a connection to two peripheral devices, to one central and one peripheral device or two central devices.
- BLE Slave latency value is valid up to 32 only.
- BLE TX/RX throughput is less when tested with EFM as compared to EFR
- Maximum supported AE data length is 200 bytes.
- Supports only two ADV\_EXT sets.
- Supports only two BLE connections( 1 Central and 1 Peripheral) with AE.
- Advertising Extension feature is not supported in Coexistence.

**MCU**

- ULP Peripherals examples configurations are for RAM-based execution, as flash is powered off in ULP Mode
- On 4338a board, two I2C instances(I2C1 and I2C2) are using same GPIOs ,so support is not there for using two I2C instances simultaneously
- I2C Fast and High speed mode not supported
- when using GSPI and SSI, manual chip select option not supported

**Simplicity Studio and Commander**

- Default GDB debug configuration is not supported for SoC projects, work around details provided in "Getting-Started-with-SiWx917"
- Observing flash download failures(ERROR 108) for a few image sizes
- While creating project through Simplicity Studio, "copy contents" option not supported.
- Simplicity commander does not support options under "Debug Lock tools" .

**Terminology**

|**Term**|**Description**|
| :-: | :-: |
|**New Features**|These items are new to this release|
|**Changes/Issues Fixed**|Changes made to existing features found in previous software releases.|
||Enhancements to existing product flow and feature set.|
||Bug fixes done in the Release|
|**Deprecated Items**|Features or functions or APIs that are removed from the distributed release to align with the software roadmap|
|**Known Issues**|Features or functions that do not work as planned at the time of release. Workarounds may be offered to meet short-term development goals, but longer-term solutions will be added in future software releases|
|**Limitations/Recommendations**|Describes the limitations on product usage and recommendations for optimal use cases|

**Note**

- NA

<br>

**WiSeConnect3\_SDK\_3.1.0-ifc1 Release Notes**

This SDK package supports SoC Mode and NCP Mode for SiWx917:

- In SoC Mode: Customer Applications can run on Cortex M4. Wireless, network, and security stacks run on the Wireless subsystem.
- In NCP mode: Wireless, network, and security stacks run on the Wireless subsystem. Customer applications run on the external host MCU.
- Silicon Labs' SiWx917 includes an ultra-low power Wi-Fi 6 plus Bluetooth Low Energy (BLE) 5.1 wireless subsystem and an integrated micro-controller application subsystem.

Note: Use Simplicity Studio version SV5.7.0.1 onwards

**SoC Highlights**

- **Operating Modes** : Wi-Fi STA (802.11ax, 802.11n), Wi-Fi 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + BLE
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n, 802.11ax, BLE 5.1
- **Multiple Ultra Low Power Modes** : Support Ultra low power Wi-Fi Standby associated current in Wi-Fi 4 mode, Ultra low power Wi-Fi Standby associated current in Wi-Fi 6 mode leveraging TWT, Always on Cloud connected power, BLE connected power, and, deep sleep ULP mode
- **MCU examples** :  GPIO, I2C, Calendar,  SPI, SSI, SIO, UDMA, UART/USART, WDT, Timers, Config Timers, ULP (Ultra Low Power) Timers, Sleeptimer, IOSTREAM, NVM3, MEMLCD, SDIO, PWM, ADC, EFUSE, I2S, PSRAM
- **Wi-Fi** : 2.4GHz Wi-Fi Support - WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and reduces latency
- **Cloud** : Amazon Cloud Connectivity Support, Amazon FreeRTOS
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack, BLE Stack, and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, DNS client
- **IDE** : Simplicity Studio with Windows 10(64-bit), Linux, Mac OS
- **TA/M4 Firmware Update Tool** : Simplicity Commander
- **Hardware kits to evaluate SoC Mode** :
  - Si-MB4002A Main board
  - SiWx917 Radio boards

|**RadioBoard Type**|**SiWx917A0 with Board Version**|**SiWx917B0 with Board Version**|
| :-: | :-: | :-: |
|Common flash|Si917-BRD4325A(1.0 /1.1 /1.2)|-|
|Common flash|-|Si917-BRD4338A(2.0)|
|Dual flash|Si917-BRD4325B(1.0 /1.1 /1.2)|-|
|External PSRAM|-|Si917-BRD4340A(2.0)|

**NCP Highlights**

- **Host Interface** : SPI
- **Operating Modes** : Wi-Fi STA (802.11ax, 802.11n), Wi-Fi 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + BLE
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n, 802.11ax, BLE 5.1
- **Multiple Ultra Low Power Modes** : Support Ultra low power Wi-Fi Standby associated current in Wi-Fi 4 mode, Ultra low power Wi-Fi Standby associated current in Wi-Fi 6 mode leveraging TWT, Always on Cloud connected power, BLE connected power, and, deep sleep ULP mode.
- **Wi-Fi** : 2.4GHz Wi-Fi Support, WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and reduces latency
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack , BLE Stack and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, DNS Client.
- **IDE** : Simplicity Studio with Windows 10(64-bit)
- **Hardware kits to evaluate NCP Mode**
  - Si917 B0 Single Band Radio Board (BRD4338A)
  - Wireless Pro kit Mainboard BRD4002A Rev A06
  - EFR32xG21 2.4 GHz 20 dBm Radio Board (BRD4180B Rev A02)

**Release Details**

|**Item**|**Details**|
| :-: | :-: |
|Release date|11th Sep, 2023|
|SDK Version|3\.1.0-ifc1|
|Firmware Version|1711\.2.9.0.0.20|
|Package Name|WiSeConnect3\_SDK\_3.1.0|
|Supported RTOS|FreeRTOS|
|Operating Modes Supported|Wi-Fi STA, Wi-Fi AP, Wi-Fi STA+BLE, Wi-Fi STA+AP|
|Build Quality|Pre-certification|

**Updating to this Release**

- SiWx917 release consists of two components
  - Wireless Firmware - SiWx917 Firmware Binaries
  - Wiseconnect3 Library - Wiseconnect3 SDK Library runs on the external host in NCP mode and internal Cortex M4 in SoC Mode.
- This release is meant only for use with designs based on SiWx917 Silicon
- The firmware to load in your design are available in the following format:
  - SiWG917-A.2.9.0.0.x.rps - A0 Full-featured firmware binary
  - SiWG917-B.2.9.0.0.x.rps - B0 Full-featured firmware binary

**Features Supported**

**MCU**

- ADC Single Channel, ADC Static Mode, Analog Comparator, Blinky, Bod, CTS, DAC FIFO, DAC Static, GPIO, I2C, I2S, NVM3, OPAMP, PSRAM, PWM, QEI, RTC, SDIO Slave, SPI Master and Slave, UART, UDMA, USART, WDT, USART Master and Slave
- UC Supported Peripherals - GPIO, I2C, Calendar,  SPI, SSI, SIO, UDMA, UART/USART, WDT, Timers , Config Timers, ULP (Ultra Low Power) Timers, SDIO, PWM, ADC, EFUSE, I2S, PSRAM, Sleeptimer, IOSTREAM, MEMLCD.
- ULP (Ultra Low Power) Peripherals - ulp\_gpio, ulp\_adc ulp\_i2c, ulp\_i2s, ulp\_ir\_decoder, ulp\_spi, ulp\_timer, ulp\_uart, ulp\_udma

**Wi-Fi**

- WPA2/WPA3 Personal, WPS and WPA2-EAP Support for Station Mode
- TCP/IP stack with IPv4, IPv6, TCP, UDP, TLS, HTTP/HTTPS, DHCPv4, DHCPv6, MQTT Client, DNS Client, SNTP client.
- Support for SSL client versions TLSV1.0, TLSV1.2, TLSV1.3 and SSL server versions TLSV1.0 and TLSV1.2
- Wi-Fi STA (802.11n/802.11ax) + 802.11n AP Support
- HE (802.11ax) and Individual TWT Feature Support
- Multiple BSSID feature support as an STA
- Secure OTA support on B0 radio boards.
- Support for LWIP network stack
- Support for AWS MQTT library
- Support for BSD and IoT sockets application programming interface(API)

**Bluetooth Low Energy**

- BLE central & peripheral connections are supported.
- Ultra-low power save is supported in Test Mode to support Tx/Rx performance testing

**Power Save**

- The power save profiles supported are Max PSP, enhanced MAX PSP, and 802.11ax TWT.

**Crypto Support**

- Added support for AES, SHA, TRNG, and WRAP APIs.
- PSA enabled Mbed TLS support added
  - NVM support is added for key storage
  - Symmetric key storage support added for Volatile and transparent key.
  - TRNG crypto engine is integrated with PSA crypto.

**Changes and Fixes**

**Wi-Fi**

- Matter requirements - WIFISDK-868, WIFISDK-876, WIFISDK-882
- Polling for TX_PKT_TRANSFER_DONE_INTERRUPT interrupt from TA after send command
- RTC timer get and set APIs
- Adding PSRAM board support for applications
- Cleanup frame type when sync response is received
- Add ta and m4 powersave for lwip tcp client example
- Updated socket config API and wlan_throughput example
- Added new example - twt_use_case_demo
- SI91X bugs covered: SI91X-13855, SI91X-13709, RSCDEV-21660

**BLE**

- Added support for wifi_throughput_ble_dual_role example
- Added new example -  immediate_alert_client

**System**

- None

**Recommendations**

**System**

- The current revision of SiWx917 A0 has:
  - RAM memory of 704k bytes which can be shared between TA and M4 processors in NCP/SoC mode. The following memory configuration modes are supported.
    - EXT\_FEAT\_704K\_M4SS\_0K- This mode configures TA with 704k and M4 with 0K bytes of memory which is applicable only in the case of NCP mode
  - The below configurations are applicable in SoC mode and can be configured based on the application requirement By Default EXT\_FEAT\_384K\_M4SS\_320K configuration will be selected in SoC mode
    - EXT\_FEAT\_512K\_M4SS\_192K - This mode configures TA with 512k and M4 with 192K bytes of memory
    - EXT\_FEAT\_448K\_M4SS\_256K - This mode configures TA with 448k and M4 with 256K bytes of memory
    - EXT\_FEAT\_384K\_M4SS\_320K - This mode configures TA with 384k and M4 with 320K bytes of memory
  - The currently supported memory configuration for NCP mode is 704K\_M4SS\_0K.
  - SoC mode should not use 704k\_M4SS\_0k Memory configuration.
  - In SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations.
- The current revision of SiWx917 B0 has:
  - RAM memory of 672k bytes which can be shared between TA and M4 processors in NCP/SoC mode. The following memory configuration modes are supported.
    - EXT\_FEAT\_672K\_M4SS\_0K- This mode configures TA with 672k and M4 with 0K bytes of memory which is applicable only in the case of NCP mode
  - The below configurations are applicable in SoC mode and can be configured based on the application requirement By Default EXT\_FEAT\_352K\_M4SS\_320K configuration will be selected in SoC mode
    - EXT\_FEAT\_480K\_M4SS\_192K - This mode configures TA with 480k and M4 with 192K bytes of memory
    - EXT\_FEAT\_416K\_M4SS\_256K - This mode configures TA with 416k and M4 with 256K bytes of memory
    - EXT\_FEAT\_352K\_M4SS\_320K - This mode configures TA with 352k and M4 with 320K bytes of memory
  - The currently supported memory configuration for NCP mode is 672K\_M4SS\_0K.
  - SoC mode should not use 672k\_M4SS\_0k Memory configuration.
  - In SoC mode, M4 power save will work with any memory configuration.
- Set the recommended Power Save Profile (PSP) type to Enhanced Max PSP.

**IDE**

- Download the latest Simplicity Studio (SV5.7.0.1)
- Refer to the latest version of the SoC/NCP "Getting-Started-with-SiWx917" guide for more details

**Wi-Fi**

- It is recommended to enable bit 16 of the 'Extended TCP IP Feature' bit map in the opermode command for all Wi-Fi Socket Operations from the host to ensure graceful handling during asynchronous closures from the peer.
- Aggregation (bit 2 of feature\_bit\_map) is recommended to be enabled in opermode. This enables sw to aggregate multiple packets to achieve better throughput
- TCP retransmission count value is recommended to be 30 or higher so that the TCP does not disconnect while the rejoin happens.
- To restart the module, the application needs to call sl\_wifi\_deinit() followed by sl\_wifi\_init().
- Register 'Join Fail Callback' function every time when join is called, as in the rejoin failure path the callback is deregistered. If not done, this might result in a scan not functioning on rejoin failure.
- User can enable SL\_SI91X\_EXT\_TCP\_IP\_SSL\_16K\_RECORD in 'Extended TCP IP Feature'bit map in opermode, if HTTPS download is failing after receiving HTTP headers..
- iTWT setup is recommended after IP assignment/TCP connection/application connection.
- When using sl\_wifi\_enable\_target\_wakeup\_time API, increase TCP / ARP Timeouts at the remote side depending upon the configured TWT interval configured.
- In case of TWT+coex, when using sl\_wifi\_enable\_target\_wakeup\_time API, use TWT wake duration <= 16 ms and TWT wake interval >= 1 sec. If wake duration > 16 ms or TWT wake interval < 1sec, there might be performance issues.
- For iTWT GTK Interval Should be kept max possible value or zero. If GTK interval is not configurable, recommended TWT interval (in case of sl\_wifi\_enable\_target\_wakeup\_time API)
- Disable Power Save for High Throughput Applications.
- The application needs to ensure that it sets RTC with the correct timestamp when the feature is enabled before establishing the SSL connection.
- Timeout value should be minimum 1 second for socket select and socket receive calls. Timeout value of less than 1 second is not currently supported.
- When sl\_wifi\_enable\_target\_wakeup\_time API is used, configuring TWT Wake interval beyond 1 min might lead to disconnections from the AP. Recommended to use TWT wakeup interval of less than or equal to 1 min.
- MQTT keep alive interval should be either 0 or a value greater than 35 seconds.
- When using sl\_wifi\_enable\_target\_wakeup\_time API, it is recommended to set missed\_beacon\_count of sl\_wifi\_set\_advanced\_client\_configuration API greater than 2 times of the configured TWT Interval.
- Secure OTA: Keys need to be programmed before validating Secure OTA

**BLE**

- In BLE, recommended range of Connection Interval in
  - Power Save (BLE Only) - 100 ms to 1.28 s.
- In BLE, during Connection, the configuration of Scan Interval and Scan Window with the same value is not recommended. The suggested ratio of Scan Window to Scan Interval is 3:4.
- In BLE, if a device is acting as Central, the scan window (in set\_scan\_params and create\_connection commands) must be less than the existing Connection Interval. The suggested ratio of Scan Window to Connection Interval is 2:3.
- In BLE mode, if scanning and advertising are in progress on the SiWx91x module and it subsequently gets connected and moves to the central role, scanning stops else if it moves to the peripheral role, advertising stops. To further establish a connection to another peripheral device or to a central device, the application should give a command for starting advertising and scanning again.

**Co-Existence**

- For concurrent Wi-Fi + BLE, and while a Wi-Fi connection is active, we recommend setting the ratio of the BLE scan window to BLE scan interval to 1:3 or 1:4.
- Wi-Fi + BLE Advertising
  - All standard advertising intervals are supported. As Wi-Fi throughput is increased, a slight difference in on-air advertisements compared to configured intervals may be observed.
  - BLE advertising is skipped if the advertising interval collides with Wi-Fi activity.
- Wi-Fi + BLE scanning
  - All standard scan intervals are supported. For better scan results, we recommend setting the ratio of the BLE scan window to BLE scan interval to 1:3 or 1:4.
  - BLE scanning will be stopped for intervals that collide with Wi-Fi activity.
- Wi-Fi + BLE Central/Peripheral Connections
  - All standard connection intervals are supported.
  - For a stable connection, use optimal connection intervals and max supervision timeout in the presence of Wi-Fi activity.
- Wi-Fi + BLE Central/Peripheral Data Transfer
  - To achieve higher throughput for both Wi-Fi and BLE, use medium connection intervals, such as 45 to 80 ms with maximum supervision timeout.
  - Ensure Wi-Fi activity consumes lower intervals.

**Known Issues**

**Network Stack**

- Sometimes during SSL Handshake, ECC curve parameters generated are wrong, resulting in connection failure with BBD2 error. However, this recovers in the next attempt.
- Recommended MQTT Publish payload is 1 kBytes.
- Randomize the client port if using rapid connect/disconnect of the MQTT session on the same client port with the power save.
- Secure SSL Renegotiation not supported in Embedded Networking Stack.

**Wi-Fi**

- Device with active TWT will not go to sleep when the buffer is full.
- There are performance and IOP issues with MU MIMO.
- WPA3 connection takes 2.5 seconds.
- Issue observed with WPA2 Enterprise Connectivity using Microsoft RADIUS Server.
- EAP connection with certificates of 4096-bit key length is not supported.
- Low Wi-Fi+BLE throughput
- Data stall and disconnection with TCP Tx data transfer when TA power save is enabled
- TCP/UDP TX/RX Data stall observed in CoEx scenarios
- HTTPS Continuous download fails with TA Power save
- Low-performance metrics.
- Data stall when WLAN TCP data transfer, BLE scanning, BLE advertising, and BLE notification are enabled
- Combined secured OTA (M4 + TA) failures.
- TA secured OTA fails 1/10 times

**BLE**

- BLE Range is less with A0/B0 dual flash Radio boards when compared to A0/B0 common flash Radio boards.
- BLE applications hang after disconnection due to Disable Power save API failure
- Observing data stall with TCP Tx/Rx when connecting BLE With wifi\_throughput\_ble\_dual\_role application.

**System**

- None

**MCU**

- Refer the respective Radio board user guides for specific pinout details. Examples are targetted to a specific version mentioned in the respective readme.
- SSI bitrate above 10 Mbps is not working as expected.
- when using SL DMA, UDMA1 is not working as expected
- SIO-SPI few channels are not working as expected. (working of MOSI & MISO channel 4 and above is inconsistent)
- Few peripherals like WDT when configured with RO clock is not working as expected. No impact on the feature but the clocks are not accurate.

**Limitations and Unsupported Features**

**Wi-Fi/Network Stack**

- TLS 1.3 Server is not supported
- In AP mode, IPv6 Router Advertisements are not supported. Although STA connected to the APUT can transfer IPv6 data to the peers by using SLAAC for address configuration.
- When sl\_wifi\_enable\_target\_wakeup\_time() API is used, observed occasional MQTT disconnections with longer TWT intervals (>30secs) with embedded MQTT + TWT.
- AMSDU TX is not supported.
- Fragmentation is not supported.
- AMSDUs within AMPDU is not supported.
- Currently, the module does not support Radio Measurement Requests feature of CCX V2
- 802.11k is not supported
- Short GI is not supported
- 40 MHz bandwidth for 2.4 GHz band is not supported.
- 802.11J channel 14 is not supported.
- MQTT versions 3 and 4 are supported.
- Maximum of 3 SSL connections are supported in Wi-Fi alone mode.
- In SSL ECC Curve ID supported is 23. SSL handshake with 3rd party clients depends on the SSL ECC Curve ID.
- LP mode is not supported.
- Fine Tuning 802.11ax Spectral mask in Progress
- Fine Tuning 11b mask in Ch11 in progress
- In iTWT mode, downlink data traffic should be limited. Disconnections may be observed if AP fails to send all the buffered data in the next TWT Service Period.
- Number of MBSSIDs processed is limited by the beacon length that can be processed by the stack (which is limited to 1024 bytes). Beacons greater than 1024 Bytes in length will not be processed.
- In A0 SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations
- Timeout value should be a minimum 1 second for socket select and socket receive calls. Timeout value less than 1 second is not currently supported.
- M4 OTA update on dual flash will work for same flash sizes only (internal and External).
- CoEx + EAP Security in 352K/320k is not feasible. This issue is observed due to a lack of memory in the 352k/320k Memory Configuration. It is supported with other EXT\_FEAT\_416K\_M4SS\_256K and EXT\_FEAT\_480K\_M4SS\_192K memory configurations.
- UL MUMIMO is not supported.
- The embedded HTTP server is not supported.
- SNI is not supported
- Baremetal is not supported

**BLE**

- For BLE, if the connection is established with a small connection interval (less than 15 ms), simultaneous roles (i.e., Central + Scanning and Peripheral + Advertising) are not supported.
- BLE maximum two concurrent connections are supported, which can be either a connection to two peripheral devices, to one central and one peripheral device or two central devices.
- BLE Slave latency value is valid up to 32 only.
- BLE TX/RX throughput is less when tested with EFM as compared to EFR
- Maximum supported AE data length is 200 bytes.
- Supports only two ADV\_EXT sets.
- Supports only two BLE connections( 1 Central and 1 Peripheral) with AE.
- Filtering policy is not supported for Periodic advertising.

**MCU**

- ULP Peripherals examples configurations are for RAM-based execution, as flash is powered off in ULP Mode
- On 4338a board, two I2C instances(I2C1 and I2C2) are using same GPIOs ,so support is not there for using two I2C instances simultaneously
- I2C Fast and High speed mode not supported
- when using GSPI and SSI, manual chip select option not supported

**Simplicity Studio and Commander**

- Default GDB debug configuration is not supported for SoC projects, work around details provided in "Getting-Started-with-SiWx917"
- Observing flash download failures(ERROR 108) for a few image sizes
- While creating project through Simplicity Studio, "copy contents" option not supported.
- Simplicity commander does not support options under "Debug Lock tools" .

**Terminology**

|**Term**|**Description**|
| :-: | :-: |
|**New Features**|These items are new to this release|
|**Changes/Issues Fixed**|Changes made to existing features found in previous software releases.|
||Enhancements to existing product flow and feature set.|
||Bug fixes done in the Release|
|**Deprecated Items**|Features or functions or APIs that are removed from the distributed release to align with the software roadmap|
|**Known Issues**|Features or functions that do not work as planned at the time of release. Workarounds may be offered to meet short-term development goals, but longer-term solutions will be added in future software releases|
|**Limitations/Recommendations**|Describes the limitations on product usage and recommendations for optimal use cases|

**Note**

- NA

<br>

**WiSeConnect3\_SDK\_3.1.0-1 Release Notes**

This SDK package supports SoC Mode and NCP Mode for A0 and B0:

- In SoC Mode: Customer Applications can run on Cortex M4. Wireless, network, and security stacks run on the Wireless subsystem.
- In NCP mode: Wireless, network, and security stacks run on the Wireless subsystem. Customer applications run on the external host MCU.
- Silicon Labs' SiWx917 includes an ultra-low power Wi-Fi 6 plus Bluetooth Low Energy (BLE) 5.1 wireless subsystem and an integrated micro-controller application subsystem.

Note: Use Simplicity Studio version SV5.7.0.1 onwards

**SoC Highlights**

- **Operating Modes** : Wi-Fi STA (802.11ax, 802.11n), Wi-Fi 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + BLE
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n, 802.11ax, BLE 5.1
- **Multiple Ultra Low Power Modes** : Support Ultra low power Wi-Fi Standby associated current in Wi-Fi 4 mode, Ultra low power Wi-Fi Standby associated current in Wi-Fi 6 mode leveraging TWT, Always on Cloud connected power, BLE connected power, and, deep sleep ULP mode
- **MCU examples** :  GPIO, I2C, Calendar,  SPI, SSI, SIO, UDMA, UART/USART, WDT, Timers, Config Timers, ULP (Ultra Low Power) Timers, Sleeptimer, IOSTREAM, NVM3, MEMLCD, SDIO,    PWM, ADC, EFUSE, I2S, PSRAM
- **Wi-Fi** : 2.4GHz Wi-Fi Support - WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and reduces latency
- **Cloud** : Amazon Cloud Connectivity Support, Amazon FreeRTOS
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack, BLE Stack, and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, DNS client
- **IDE** : Simplicity Studio with Windows 10(64-bit), Linux, Mac OS
- **TA/M4 Firmware Update Tool** : Simplicity Commander
- **Hardware kits to evaluate SoC Mode** :
  - Si-MB4002A Main board
  - SiWx917 Radio boards

|**RadioBoard Type**|**SiWx917A0 with Board Version**|**SiWx917B0 with Board Version**|
| :-: | :-: | :-: |
|Common flash|Si917-BRD4325A(1.0 /1.1 /1.2)|-|
|Common flash|-|Si917-BRD4338A(2.0)|
|Dual flash|Si917-BRD4325B(1.0 /1.1 /1.2)|-|
|External PSRAM|-|Si917-BRD4340A(2.0)|

**NCP Highlights**

- **Host Interface** : SPI
- **Operating Modes** : Wi-Fi STA (802.11ax, 802.11n), Wi-Fi 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + 802.11n AP, Wi-Fi STA (802.11ax, 802.11n) + BLE
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n, 802.11ax, BLE 5.1
- **Multiple Ultra Low Power Modes** : Support Ultra low power Wi-Fi Standby associated current in Wi-Fi 4 mode, Ultra low power Wi-Fi Standby associated current in Wi-Fi 6 mode leveraging TWT, Always on Cloud connected power, BLE connected power, and, deep sleep ULP mode.
- **Wi-Fi** : 2.4GHz Wi-Fi Support, WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and reduces latency
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack , BLE Stack and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, DNS Client.
- **IDE** : Simplicity Studio with Windows 10(64-bit)
- **Hardware kits to evaluate NCP Mode**
  - Si917 B0 Single Band Radio Board (BRD4338A)
  - Wireless Pro kit Mainboard BRD4002A Rev A06
  - EFR32xG21 2.4 GHz 20 dBm Radio Board (BRD4180B Rev A02)

**Release Details**

|**Item**|**Details**|
| :-: | :-: |
|Release date|Sep 1st, 2023|
|SDK Version|3\.1.0-1|
|Firmware Version|1711\.2.9.0.0.20|
|Package Name|WiSeConnect3\_SDK\_3.1.0|
|Supported RTOS|FreeRTOS|
|Operating Modes Supported|Wi-Fi STA, Wi-Fi AP, Wi-Fi STA+BLE, Wi-Fi STA+AP|
|Build Quality|Pre-certification|

**Updating to this Release**

- SiWx917 release consists of two components
  - Wireless Firmware - SiWx917 Firmware Binaries
  - Wiseconnect3 Library - Wiseconnect3 SDK Library runs on the external host in NCP mode and internal Cortex M4 in SoC Mode.
- This release is meant only for use with designs based on SiWx917 Silicon
- The firmware to load in your design are available in the following format:
  - SiWG917-A.2.9.0.0.x.rps - A0 Full-featured firmware binary
  - SiWG917-B.2.9.0.0.x.rps - B0 Full-featured firmware binary

**Features Supported**

**MCU**

- ADC Single Channel, ADC Static Mode, Analog Comparator, Blinky, Bod, CTS, DAC FIFO, DAC Static, GPIO, I2C, I2S, NVM3, OPAMP, PSRAM, PWM, QEI, RTC, SDIO Slave, SPI Master and Slave, UART, UDMA, USART, WDT, USART Master and Slave
- UC Supported Peripherals - GPIO, I2C, Calendar,  SPI, SSI, SIO, UDMA, UART/USART, WDT, Timers , Config Timers, ULP (Ultra Low Power) Timers, SDIO, PWM, ADC, EFUSE, I2S, PSRAM, Sleeptimer, IOSTREAM, MEMLCD.
- ULP (Ultra Low Power) Peripherals - ulp\_gpio, ulp\_adc ulp\_i2c, ulp\_i2s, ulp\_ir\_decoder, ulp\_spi, ulp\_timer, ulp\_uart, ulp\_udma

**Wi-Fi**

- WPA2/WPA3 Personal, WPS and WPA2-EAP Support for Station Mode
- TCP/IP stack with IPv4, IPv6, TCP, UDP, TLS, HTTP/HTTPS, DHCPv4, DHCPv6, MQTT Client, DNS Client, SNTP client.
- Support for SSL client versions TLSV1.0, TLSV1.2, TLSV1.3 and SSL server versions TLSV1.0 and TLSV1.2
- Wi-Fi STA (802.11n/802.11ax) + 802.11n AP Support
- HE (802.11ax) and Individual TWT Feature Support
- Multiple BSSID feature support as an STA
- Secure OTA support on B0 radio boards.
- Support for LWIP network stack
- Support for AWS MQTT library
- Support for BSD and IoT sockets application programming interface(API)

**Bluetooth Low Energy**

- BLE central & peripheral connections are supported.
- Ultra-low power save is supported in Test Mode to support Tx/Rx performance testing

**Power Save**

- The power save profiles supported are Max PSP, enhanced MAX PSP, and 802.11ax TWT.

**Crypto Support**

- AES, SHA and TRNG Crypto API support added
- PSA enabled Mbed TLS support added
  - NVM support is added for key storage
  - Symmetric key storage support added for Volatile and transparent key.
  - TRNG crypto engine is integrated with PSA crypto.

**Changes and Fixes**

**Wi-Fi**

- Add support for Efuse read API
- Add support for User gain tables
- Add support for Calibration SW APIs
- Add support for M4 soft reset
- Updated all readme files with unified Project Environment
- Add SOC support for tcp_tx_on_periodic_wakeup example
- Added support for wlan_throughput_psram application
- Add async notification support and example usage in sntp example
- Add support for sl_wifi_target_wake_time_auto_selection() API
- Updated embedded_mqtt_client_twt and twt_tcp_client examples with M4 powersave
- Addition of twt_use_case_remote_app example
- SI91X bugs covered: SI91X-13628, SI91X-13406, SI91X-13738, SI91X-13859, SI91X-13769, SI91X-13793, SI91X-13521, SI91X-13689, SI91X-13659, SI91X-13726

**BLE**

- Add SOC and NCP support for ble_testmodes example
- Addition of gatt_long_read example
- Renaming of whitelist to acceptlist in all BLE examples
- Added studio support and logging stats feature for wifi_station_ble_provisioning_aws_logging_stats example
- Addition of wifi_station_ble_throughput_app
- Added support for test agent application for ble commands

**System**

- None

**Recommendations**

**System**

- The current revision of SiWx917 A0 has:
  - RAM memory of 704k bytes which can be shared between TA and M4 processors in NCP/SoC mode. The following memory configuration modes are supported.
    - EXT\_FEAT\_704K\_M4SS\_0K- This mode configures TA with 704k and M4 with 0K bytes of memory which is applicable only in the case of NCP mode
  - The below configurations are applicable in SoC mode and can be configured based on the application requirement By Default EXT\_FEAT\_384K\_M4SS\_320K configuration will be selected in SoC mode
    - EXT\_FEAT\_512K\_M4SS\_192K - This mode configures TA with 512k and M4 with 192K bytes of memory
    - EXT\_FEAT\_448K\_M4SS\_256K - This mode configures TA with 448k and M4 with 256K bytes of memory
    - EXT\_FEAT\_384K\_M4SS\_320K - This mode configures TA with 384k and M4 with 320K bytes of memory
  - The currently supported memory configuration for NCP mode is 704K\_M4SS\_0K.
  - SoC mode should not use 704k\_M4SS\_0k Memory configuration.
  - In SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations.
- The current revision of SiWx917 B0 has:
  - RAM memory of 672k bytes which can be shared between TA and M4 processors in NCP/SoC mode. The following memory configuration modes are supported.
    - EXT\_FEAT\_672K\_M4SS\_0K- This mode configures TA with 672k and M4 with 0K bytes of memory which is applicable only in the case of NCP mode
  - The below configurations are applicable in SoC mode and can be configured based on the application requirement By Default EXT\_FEAT\_352K\_M4SS\_320K configuration will be selected in SoC mode
    - EXT\_FEAT\_480K\_M4SS\_192K - This mode configures TA with 480k and M4 with 192K bytes of memory
    - EXT\_FEAT\_416K\_M4SS\_256K - This mode configures TA with 416k and M4 with 256K bytes of memory
    - EXT\_FEAT\_352K\_M4SS\_320K - This mode configures TA with 352k and M4 with 320K bytes of memory
  - The currently supported memory configuration for NCP mode is 672K\_M4SS\_0K.
  - SoC mode should not use 672k\_M4SS\_0k Memory configuration.
  - In SoC mode, M4 power save will work with any memory configuration.
- Set the recommended Power Save Profile (PSP) type to Enhanced Max PSP.

**IDE**

- Download the latest Simplicity Studio (SV5.7.0.1)
- Refer to the latest version of the SoC/NCP "Getting-Started-with-SiWx917" guide for more details

**Wi-Fi**

- It is recommended to enable bit 16 of the 'Extended TCP IP Feature' bit map in the opermode command for all Wi-Fi Socket Operations from the host to ensure graceful handling during asynchronous closures from the peer.
- Aggregation (bit 2 of feature\_bit\_map) is recommended to be enabled in opermode. This enables sw to aggregate multiple packets to achieve better throughput
- TCP retransmission count value is recommended to be 30 or higher so that the TCP does not disconnect while the rejoin happens.
- To restart the module, the application needs to call sl\_wifi\_deinit() followed by sl\_wifi\_init().
- Register 'Join Fail Callback' function every time when join is called, as in the rejoin failure path the callback is deregistered. If not done, this might result in a scan not functioning on rejoin failure.
- User can enable SL\_SI91X\_EXT\_TCP\_IP\_SSL\_16K\_RECORD in 'Extended TCP IP Feature'bit map in opermode, if HTTPS download is failing after receiving HTTP headers..
- iTWT setup is recommended after IP assignment/TCP connection/application connection.
- When using sl\_wifi\_enable\_target\_wakeup\_time API, increase TCP / ARP Timeouts at the remote side depending upon the configured TWT interval configured.
- In case of TWT+coex, when using sl\_wifi\_enable\_target\_wakeup\_time API, use TWT wake duration <= 16 ms and TWT wake interval >= 1 sec. If wake duration > 16 ms or TWT wake interval < 1sec, there might be performance issues.
- For iTWT GTK Interval Should be kept max possible value or zero. If GTK interval is not configurable, recommended TWT interval (in case of sl\_wifi\_enable\_target\_wakeup\_time API)
- Disable Power Save for High Throughput Applications.
- The application needs to ensure that it sets RTC with the correct timestamp when the feature is enabled before establishing the SSL connection.
- Timeout value should be minimum 1 second for socket select and socket receive calls. Timeout value of less than 1 second is not currently supported.
- When sl\_wifi\_enable\_target\_wakeup\_time API is used, configuring TWT Wake interval beyond 1 min might lead to disconnections from the AP. Recommended to use TWT wakeup interval of less than or equal to 1 min.
- MQTT keep alive interval should be either 0 or a value greater than 35 seconds.
- When using sl\_wifi\_enable\_target\_wakeup\_time API, it is recommended to set missed\_beacon\_count of sl\_wifi\_set\_advanced\_client\_configuration API greater than 2 times of the configured TWT Interval.
- Secure OTA: Keys need to be programmed before validating Secure OTA

**BLE**

- In BLE, recommended range of Connection Interval in
  - Power Save (BLE Only) - 100 ms to 1.28 s.
- In BLE, during Connection, the configuration of Scan Interval and Scan Window with the same value is not recommended. The suggested ratio of Scan Window to Scan Interval is 3:4.
- In BLE, if a device is acting as Central, the scan window (in set\_scan\_params and create\_connection commands) must be less than the existing Connection Interval. The suggested ratio of Scan Window to Connection Interval is 2:3.
- In BLE mode, if scanning and advertising are in progress on the SiWx91x module and it subsequently gets connected and moves to the central role, scanning stops else if it moves to the peripheral role, advertising stops. To further establish a connection to another peripheral device or to a central device, the application should give a command for starting advertising and scanning again.

**Co-Existence**

- For concurrent Wi-Fi + BLE, and while a Wi-Fi connection is active, we recommend setting the ratio of the BLE scan window to BLE scan interval to 1:3 or 1:4.
- Wi-Fi + BLE Advertising
  - All standard advertising intervals are supported. As Wi-Fi throughput is increased, a slight difference in on-air advertisements compared to configured intervals may be observed.
  - BLE advertising is skipped if the advertising interval collides with Wi-Fi activity.
- Wi-Fi + BLE scanning
  - All standard scan intervals are supported. For better scan results, we recommend setting the ratio of the BLE scan window to BLE scan interval to 1:3 or 1:4.
  - BLE scanning will be stopped for intervals that collide with Wi-Fi activity.
- Wi-Fi + BLE Central/Peripheral Connections
  - All standard connection intervals are supported.
  - For a stable connection, use optimal connection intervals and max supervision timeout in the presence of Wi-Fi activity.
- Wi-Fi + BLE Central/Peripheral Data Transfer
  - To achieve higher throughput for both Wi-Fi and BLE, use medium connection intervals, such as 45 to 80 ms with maximum supervision timeout.
  - Ensure Wi-Fi activity consumes lower intervals.

**Known Issues**

**Network Stack**

- Sometimes during SSL Handshake, ECC curve parameters generated are wrong, resulting in connection failure with BBD2 error. However, this recovers in the next attempt.
- Recommended MQTT Publish payload is 1 kBytes.
- Randomize the client port if using rapid connect/disconnect of the MQTT session on the same client port with the power save.
- Secure SSL Renegotiation not supported in Embedded Networking Stack.

**Wi-Fi**

- Device with active TWT will not go to sleep when the buffer is full.
- There are performance and IOP issues with MU MIMO.
- WPA3 connection takes 2.5 seconds.
- Issue observed with WPA2 Enterprise Connectivity using Microsoft RADIUS Server.
- EAP connection with certificates of 4096-bit key length is not supported.
- Low Wi-Fi+BLE throughput
- Data stall and disconnection with TCP Tx data transfer when TA power save is enabled
- TCP/UDP TX/RX Data stall observed in CoEx scenarios
- HTTPS Continuous download fails with TA Power save
- Low-performance metrics.
- Data stall when WLAN TCP data transfer, BLE scanning, BLE advertising, and BLE notification are enabled
- Combined secured OTA (M4 + TA) failures.
- TA secured OTA fails 1/10 times

**BLE**

- BLE Range is less with A0/B0 dual flash Radio boards when compared to A0/B0 common flash Radio boards.
- BLE applications hang after disconnection due to Disable Power save API failure
- Observing data stall with TCP Tx/Rx when connecting BLE With wifi\_throughput\_ble\_dual\_role application.

**System**

- None

**MCU**

- Refer the respective Radio board user guides for specific pinout details. Examples are targetted to a specific version mentioned in the respective readme.
- SSI bitrate above 10 Mbps is not working as expected.
- when using SL DMA, UDMA1 is not working as expected
- SIO-SPI few channels are not working as expected. (working of MOSI & MISO channel 4 and above is inconsistent)
- Few peripherals like WDT when configured with RO clock is not working as expected. No impact on the feature but the clocks are not accurate.

**Limitations and Unsupported Features**

**Wi-Fi/Network Stack**

- TLS 1.3 Server is not supported
- In AP mode, IPv6 Router Advertisements are not supported. Although STA connected to the APUT can transfer IPv6 data to the peers by using SLAAC for address configuration.
- When sl\_wifi\_enable\_target\_wakeup\_time() API is used, observed occasional MQTT disconnections with longer TWT intervals (>30secs) with embedded MQTT + TWT.
- AMSDU TX is not supported.
- Fragmentation is not supported.
- AMSDUs within AMPDU is not supported.
- Currently, the module does not support Radio Measurement Requests feature of CCX V2
- 802.11k is not supported
- Short GI is not supported
- 40 MHz bandwidth for 2.4 GHz band is not supported.
- 802.11J channel 14 is not supported.
- MQTT versions 3 and 4 are supported.
- Maximum of 3 SSL connections are supported in Wi-Fi alone mode.
- In SSL ECC Curve ID supported is 23. SSL handshake with 3rd party clients depends on the SSL ECC Curve ID.
- LP mode is not supported.
- Fine Tuning 802.11ax Spectral mask in Progress
- Fine Tuning 11b mask in Ch11 in progress
- In iTWT mode, downlink data traffic should be limited. Disconnections may be observed if AP fails to send all the buffered data in the next TWT Service Period.
- Number of MBSSIDs processed is limited by the beacon length that can be processed by the stack (which is limited to 1024 bytes). Beacons greater than 1024 Bytes in length will not be processed.
- In A0 SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations
- Timeout value should be a minimum 1 second for socket select and socket receive calls. Timeout value less than 1 second is not currently supported.
- M4 OTA update on dual flash will work for same flash sizes only (internal and External).
- CoEx + EAP Security in 352K/320k is not feasible. This issue is observed due to a lack of memory in the 352k/320k Memory Configuration. It is supported with other EXT\_FEAT\_416K\_M4SS\_256K and EXT\_FEAT\_480K\_M4SS\_192K memory configurations.
- UL MUMIMO is not supported.
- The embedded HTTP server is not supported.
- SNI is not supported
- Baremetal is not supported

**BLE**

- For BLE, if the connection is established with a small connection interval (less than 15 ms), simultaneous roles (i.e., Central + Scanning and Peripheral + Advertising) are not supported.
- BLE maximum two concurrent connections are supported, which can be either a connection to two peripheral devices, to one central and one peripheral device or two central devices.
- BLE Slave latency value is valid up to 32 only.
- BLE TX/RX throughput is less when tested with EFM as compared to EFR
- Maximum supported AE data length is 200 bytes.
- Supports only two ADV\_EXT sets.
- Supports only two BLE connections( 1 Central and 1 Peripheral) with AE.
- Filtering policy is not supported for Periodic advertising.

**MCU**

- ULP Peripherals examples configurations are for RAM-based execution, as flash is powered off in ULP Mode
- On 4338a board, two I2C instances(I2C1 and I2C2) are using same GPIOs ,so support is not there for using two I2C instances simultaneously
- I2C Fast and High speed mode not supported
- when using GSPI and SSI, manual chip select option not supported

**Simplicity Studio and Commander**

- Default GDB debug configuration is not supported for SoC projects, work around details provided in "Getting-Started-with-SiWx917"
- Observing flash download failures(ERROR 108) for a few image sizes
- While creating project through Simplicity Studio, "copy contents" option not supported.
- Simplicity commander does not support options under "Debug Lock tools" .

**Terminology**

|**Term**|**Description**|
| :-: | :-: |
|**New Features**|These items are new to this release|
|**Changes/Issues Fixed**|Changes made to existing features found in previous software releases.|
||Enhancements to existing product flow and feature set.|
||Bug fixes done in the Release|
|**Deprecated Items**|Features or functions or APIs that are removed from the distributed release to align with the software roadmap|
|**Known Issues**|Features or functions that do not work as planned at the time of release. Workarounds may be offered to meet short-term development goals, but longer-term solutions will be added in future software releases|
|**Limitations/Recommendations**|Describes the limitations on product usage and recommendations for optimal use cases|

**Note**

- NA

<br>

# WiSeConnect3_SDK_3.0.13 Release Notes

This SDK package supports SoC and NCP Mode

- In SoC Mode: Customer Applications can run on Cortex M4. Wireless stacks and Networking stacks run on the Wireless subsystem.
- In NCP Mode: Customer Applications can run on third party host. Wireless stacks and Networking stacks run on the Wireless subsystem.
- Silicon Labs' SiWx917 includes an ultra-low power Wi-Fi 6 plus Bluetooth Low Energy (BLE) 5.1 wireless subsystem and an integrated micro-controller application subsystem.
- Support for Phase 1 platform DX peripherals is added.

> Note: Release supports only Simplicity Studio 5.5 & above versions

## Highlights

- **Operating Modes** : Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx),
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n , 802.11ax, BLE 5.1
- **MCU Peripherals** : ADC Static Mode, Analog Comparator, Bod, CTS, DAC FIFO, DAC Static, OPAMP, GPIO, I2C, I2S, PWM, RTC, QEI, SPI, UART, USART, UDMA, WDT, MEMLCD
  : ULP (Ultra Low Power) Peripherals - ulp_gpio, ulp_i2c, ulp_i2s, ulp_ir_decoder, ulp_spi, ulp_timer, ulp_uart, ulp_udma
  : UART and I2C Deepsleep Wakeup Without RAM Retention
- **Multiple Ultra Low Power Modes** : Wi-Fi 6 TWT (Target Wake Time) - for improved network efficiency and device battery life
- **Wi-Fi** : 2.4GHz Wi-Fi Support - WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and latency
- **Cloud** : Amazon Cloud Connectivity Support, Amazon FreeRTOS
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack, BLE Stack and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, SNTP Client
- **IDE** : Simplicity Studio with Windows 10(64-bit)
- **TA/M4 Firmware Update Tool** : Simplicity Commander
- **Hardware kits to evaluate SoC Mode** : Si917-BRD4325B (Dual flash Radio board), Si917-BRD4325A, Si917-BRD4325G (Common Flash Radio board), Si917-BRD4338A (Common Flash Radio Board V2.0)

## Release Details

| Item                      | Details                                                        |
| ------------------------- | -------------------------------------------------------------- |
| Release date              | August 14th, 2023                                              |
| API Version               | 3.0.13(Build 1)                                                |
| Firmware Version          | 2.9.0.0.19                                                     |
| Package Name              | WiSeConnect3_SDK_3.0.13                                        |
| Supported RTOS            | FreeRTOS                                                       |
| Operating Modes Supported | Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx) |

## Updating to this Release

This release consists of Wireless Library - The Library runs on internal Cortex M4 in SoC Mode and third party host in NCP mode, supports 52 SoC and 13 NCP sample examples.

## Features and Bug Fixes

- Added NCP support for ble_per, aws_device_shadow, wlan_throughput, firmware update, wlan_tls_client
- Fixed customer issue in embedded MQTT
- SQA Bugs - SI91X-13682, SI91X-13742, SI91X-13727, SI91X-13406, SI91X-13736, SI91X-13743, SI91X-13749

## Known Issues

- Refer the respective Radio board user guides for specific pinout details. Example readme's dont include all board variant GPIO details.
- SSI bitrate above 10 Mbps is not working as expected.
- When using SL DMA, UDMA1 is not working as expected
- SIO-SPI few channels are not working as expected. (working of MOSI & - MISO channel 4 and above is inconsistent)
  - Few peripherals like WDT when configured with RO clock is not working as expected. No impact on the feature but the clocks are not accurate.
- DUT is getting hanged while continuously publishing data in embedded mqtt application during power save mode
- BLE notification and Continuous BG scan are not working as expected
- Ongoing efforts to update the readme file are in progress
- Matter issue - SI91X-13524
- BLE long range of 4-5m for BRD4325B A02 board

### SoC

- The "Browser File Viewer" plugin has issues. It can't render the last image included in the markdown files and observed issues accessing some hyperlinks
- In SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations

### Network Stack

### Wi-Fi

- WPA3 connection takes 2.5 sec more than WPA2 connection
- Issue observed with WPA2 Enterprise Connectivity using Microsoft RADIUS Server.

### BLE

- For BLE, dual role scenario issues might occur when connecting as central if the advertising is also going out for the peripheral role. Central connections can be made after the peripheral connections are established and advertising is stopped.
- LMP timeout BLE disconnection observed with the latest Realme mobile handsets.

## Limitations and Unsupported Features

### Wi-Fi/Network Stack

#### Limitations

- Throughput not at par with WiSeConnect 2 in the present release
- Maximum of 3 SSL connections are supported in WiFi alone mode.
- TWT is not verified in Coex mode.
- BGscan is not verified with TWT Feature.
- SIO currently supports SPI and UART.
- Peripherals currently uses UDMA CMSIS driver.

#### Not supported

- DTIM skip feature in power save.
- NCP Support(SDIO, UART, Linux, 3rd party hosts)
- 917 Specific features(degugging utilities)
- Calibration SW APIs
- Keep Alive Functionality
- SNI
- DNS Clients
- APIs for Crypto Hardware(ECDH, DH)
- Stats APIs
- Multi-threading support for relevant APIs
- SoC Support (Hosted mode): support for switching between LWIP & internal stack in SS
- IPV6 Support (for network application protocols)
- Console application for customers
- Protocols Offload mode: HTTP Server(917 specific), DHCPv6 Server, SNMP, Socket reads up to 64k, POP3, DTLS, mDNS, Web Socket
- Power save support (Message based)
- Baremetal support (for EFR)
- PTA Coexistence with other wireless
- SL Net Hosted mode (SoftAP over LWIP)
- Asynchronous API's(SSL)
- I2C Fast and High speed mode not supported
- When using GSPI and SSI, manual chip select option not supported

### BLE

- For BLE, if the connection is established with a small connection interval (less than 15 ms), simultaneous roles (i.e., Central + Scanning and Peripheral + Advertising) are not supported.
- BLE maximum two concurrent connections are supported, which can be either a connection to two peripheral devices, to one central and one peripheral device or two central devices.
- BLE Slave latency value is valid up to 32 only.

## Terminology

| Term                            | Description                                                                                                                                                                                                    |
| ------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **New Features**                | These items are new to this release                                                                                                                                                                            |
| **Changes/Issues Fixed**        | Changes made to existing features found in previous software releases.                                                                                                                                         |
|                                 | Enhancements to existing product flow and feature set.                                                                                                                                                         |
|                                 | Bug fixes done in the Release                                                                                                                                                                                  |
| **Deprecated Items**            | Features or functions or APIs that are removed from the distributed release to align with the software roadmap                                                                                                 |
| **Known Issues**                | Features or functions that do not work as planned at the time of release. Workarounds may be offered to meet short-term development goals, but longer-term solutions will be added in future software releases |
| **Limitations/Recommendations** | Describes the limitations on product usage and recommendations for optimal use cases                                                                                                                           |

<br />

## Notes

This release supports 917 Common Flash (A0 - BRD4325A, B0 - BRD4325G and B0 - BRD4338A(V 2.0)) and Dual Flash (A0 - BRD4325B).

# WiSeConnect3_SDK_3.0.12 Release Notes

This SDK package supports SoC Mode

- In SoC Mode: Customer Applications can run on Cortex M4. Wireless stacks and Networking stacks run on the Wireless subsystem.
- Silicon Labs' SiWx917 includes an ultra-low power Wi-Fi 6 plus Bluetooth Low Energy (BLE) 5.1 wireless subsystem and an integrated micro-controller application subsystem.
- Support for Phase 1 platform DX peripherals is added.

> Note: Release supports only Simplicity Studio 5.5 & above versions

## SoC Highlights

- **Operating Modes** : Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx),
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n , 802.11ax, BLE 5.1
- **MCU Peripherals** : ADC Static Mode, Analog Comparator, Bod, CTS, DAC FIFO, DAC Static, OPAMP, GPIO, I2C, I2S, PWM, RTC, QEI, SPI, UART, USART, UDMA, WDT, MEMLCD
  : ULP (Ultra Low Power) Peripherals - ulp_gpio, ulp_i2c, ulp_i2s, ulp_ir_decoder, ulp_spi, ulp_timer, ulp_uart, ulp_udma
  : UART and I2C Deepsleep Wakeup Without RAM Retention
- **Multiple Ultra Low Power Modes** : Wi-Fi 6 TWT (Target Wake Time) - for improved network efficiency and device battery life
- **Wi-Fi** : 2.4GHz Wi-Fi Support - WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and latency
- **Cloud** : Amazon Cloud Connectivity Support, Amazon FreeRTOS
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack, BLE Stack and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, SNTP Client
- **IDE** : Simplicity Studio with Windows 10(64-bit)
- **TA/M4 Firmware Update Tool** : Simplicity Commander
- **Hardware kits to evaluate SoC Mode** : Si917-BRD4325B (Dual flash Radio board), Si917-BRD4325A, Si917-BRD4325G (Common Flash Radio board), Si917-BRD4338A (Common Flash Radio Board V2.0)

## Release Details

| Item                      | Details                                                        |
| ------------------------- | -------------------------------------------------------------- |
| Release date              | August 4th, 2023                                               |
| API Version               | 3.0.12(Build 1)                                                |
| Firmware Version          | 2.9.0.0.17                                                     |
| Package Name              | WiSeConnect3_SDK_3.0.12                                        |
| Supported RTOS            | FreeRTOS                                                       |
| Operating Modes Supported | Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx) |

## Updating to this Release

This release consists of Wireless Library - The Library runs on internal Cortex M4 in SoC Mode and supports 52 sample examples.

## Features and Bug Fixes

- Added NCP support for access_point, concurrent_mode, aws_mqtt, powersave_standby_associated, select_app, station_ping, lwip_tcp_client, sntp
- Update documentation for SL_SI91X_EXT_FEAT_XTAL_CLK_ENABLE
- Added Macro SL_SI91X_EXT_FEAT_XTAL_CLK based on A0 or B0 board
- SQA Bugs - SI91X-13595, SI91X-13626, SI91X-13621, SI91X-13650, SI91X-13346, SI91X-13584, SI91X-13627, SI91X-13606,
             SI91X-13635, SI91X-13683, SI91X-13684 ,SI91X-13527, SI91X-13696, SI91X-13690, SI91X-13408, SI91X-13679,
- Platform SQA Bugs - SI91X-13644, SI91X-13556, SI91X-13542, SI91X-13460
- Added Frontend switch selection in SRM

## Known Issues

- Refer the respective Radio board user guides for specific pinout details. Example readme's dont include all board variant GPIO details.
- SSI bitrate above 10 Mbps is not working as expected.
- When using SL DMA, UDMA1 is not working as expected
- SIO-SPI few channels are not working as expected. (working of MOSI & - MISO channel 4 and above is inconsistent)
  - Few peripherals like WDT when configured with RO clock is not working as expected. No impact on the feature but the clocks are not accurate.
- DUT is getting hanged while continuously publishing data in embedded mqtt application during power save mode
- BLE notification and Continuous BG scan are not working as expected
- Ongoing efforts to update the readme file are in progress
- Matter issue - SI91X-13524
- BLE long range of 4-5m for BRD4325B A02 board

### SoC

- The "Browser File Viewer" plugin has issues. It can't render the last image included in the markdown files and observed issues accessing some hyperlinks
- In SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations

### Network Stack

### Wi-Fi

- WPA3 connection takes 2.5 sec more than WPA2 connection
- Issue observed with WPA2 Enterprise Connectivity using Microsoft RADIUS Server.

### BLE

- For BLE, dual role scenario issues might occur when connecting as central if the advertising is also going out for the peripheral role. Central connections can be made after the peripheral connections are established and advertising is stopped.
- LMP timeout BLE disconnection observed with the latest Realme mobile handsets.

## Limitations and Unsupported Features

### Wi-Fi/Network Stack

#### Limitations

- Throughput not at par with WiSeConnect 2 in the present release
- Maximum of 3 SSL connections are supported in WiFi alone mode.
- TWT is not verified in Coex mode.
- BGscan is not verified with TWT Feature.
- SIO currently supports SPI and UART.
- Peripherals currently uses UDMA CMSIS driver.

#### Not supported

- DTIM skip feature in power save.
- NCP Support(SDIO, UART,Linux, 3rd party hosts)
- 917 Specific features(degugging utilities)
- Calibration SW APIs
- Keep Alive Functionality
- SNI
- DNS Clients
- APIs for Crypto Hardware(ECDH, DH, SHA, AES)
- Stats APIs
- Multi-threading support for relevant APIs
- SoC Support (Hosted mode): support for switching between LWIP & internal stack in SS
- IPV6 Support (for network application protocols)
- Console application for customers
- Protocols Offload mode: HTTP Server(917 specific), DHCPv6 Server, SNMP, Socket reads up to 64k, POP3, DTLS, mDNS, Web Socket
- Power save support (Message based)
- Baremetal support (for EFR)
- PTA Coexistence with other wireless
- SL Net Hosted mode (SoftAP over LWIP)
- Asynchronous API's(SSL)
- I2C Fast and High speed mode not supported
- When using GSPI and SSI, manual chip select option not supported

### BLE

- For BLE, if the connection is established with a small connection interval (less than 15 ms), simultaneous roles (i.e., Central + Scanning and Peripheral + Advertising) are not supported.
- BLE maximum two concurrent connections are supported, which can be either a connection to two peripheral devices, to one central and one peripheral device or two central devices.
- BLE Slave latency value is valid up to 32 only.

## Terminology

| Term                            | Description                                                                                                                                                                                                    |
| ------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **New Features**                | These items are new to this release                                                                                                                                                                            |
| **Changes/Issues Fixed**        | Changes made to existing features found in previous software releases.                                                                                                                                         |
|                                 | Enhancements to existing product flow and feature set.                                                                                                                                                         |
|                                 | Bug fixes done in the Release                                                                                                                                                                                  |
| **Deprecated Items**            | Features or functions or APIs that are removed from the distributed release to align with the software roadmap                                                                                                 |
| **Known Issues**                | Features or functions that do not work as planned at the time of release. Workarounds may be offered to meet short-term development goals, but longer-term solutions will be added in future software releases |
| **Limitations/Recommendations** | Describes the limitations on product usage and recommendations for optimal use cases                                                                                                                           |

<br />

## Notes

This release supports 917 Common Flash (A0 - BRD4325A, B0 - BRD4325G and B0 - BRD4338A(V 2.0)) and Dual Flash (A0 - BRD4325B).

# WiSeConnect3_SDK_3.0.11 Release Notes

This SDK package supports SoC Mode

- In SoC Mode: Customer Applications can run on Cortex M4. Wireless stacks and Networking stacks run on the Wireless subsystem.
- Silicon Labs' SiWx917 includes an ultra-low power Wi-Fi 6 plus Bluetooth Low Energy (BLE) 5.1 wireless subsystem and an integrated micro-controller application subsystem.
- Support for Phase 1 platform DX peripherals is added.

> Note: Release supports only Simplicity Studio 5.5 & above versions

## SoC Highlights

- **Operating Modes** : Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx),
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n , 802.11ax, BLE 5.1
- **MCU Peripherals** : ADC Static Mode, Analog Comparator, Bod, CTS, DAC FIFO, DAC Static, OPAMP, GPIO, I2C, I2S, PWM, RTC, QEI, SPI, UART, USART, UDMA, WDT, MEMLCD
  : ULP (Ultra Low Power) Peripherals - ulp_gpio, ulp_i2c, ulp_i2s, ulp_ir_decoder, ulp_spi, ulp_timer, ulp_uart, ulp_udma
  : UART and I2C Deepsleep Wakeup Without RAM Retention
- **Multiple Ultra Low Power Modes** : Wi-Fi 6 TWT (Target Wake Time) - for improved network efficiency and device battery life
- **Wi-Fi** : 2.4GHz Wi-Fi Support - WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and latency
- **Cloud** : Amazon Cloud Connectivity Support, Amazon FreeRTOS
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack, BLE Stack and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, SNTP Client
- **IDE** : Simplicity Studio with Windows 10(64-bit)
- **TA/M4 Firmware Update Tool** : Simplicity Commander
- **Hardware kits to evaluate SoC Mode** : Si917-BRD4325B (Dual flash Radio board), Si917-BRD4325A, Si917-BRD4325G (Common Flash Radio board), Si917-BRD4338A (Common Flash Radio Board V2.0)

## Release Details

| Item                      | Details                                                        |
| ------------------------- | -------------------------------------------------------------- |
| Release date              | July 26th, 2023                                                |
| API Version               | 3.0.11(Build 1)                                                |
| Firmware Version          | 2.9.0.0.16                                                     |
| Package Name              | WiSeConnect3_SDK_3.0.11                                        |
| Supported RTOS            | FreeRTOS                                                       |
| Operating Modes Supported | Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx) |

## Updating to this Release

This release consists of Wireless Library - The Library runs on internal Cortex M4 in SoC Mode and supports 52 sample examples.

## Features and Bug Fixes

- Added support for Asynchronous Sockets
- Removes _DEFAULT_ from sl_net_interface_t enum and its instances
- Replace convert_string_to_sl_ipv4_address-API with sl_net_inet_addr in coex examples
- Added support for SNTP documentation
- Added new examples - proximity_profile and TCP/UDP bidirectional data transfer
- Updated NVM3 documentation
- Platform SQA Bugs: - SI91X-13445, SI91X-13446, SI91X-13562, SI91X-13556, SI91X-13534, SI91X-13492, SI91X-13450, SI91X-13460, SI91X-13593, SI91X-13542
- Addressed Matter issue - WIFISDK-752, WIFISDK-753, WIFISDK-706
- Fixed SAPI timeout error issue in ble_throughput application
- Updated example applications readme  

## Known Issues

- The current chipset support for all the DX peripherals is A0 and B0(V1.2). B0(V2.0) support shall be provided in subsequent releases.
- I2C High Speed mode is not working as expected.
- DUT is getting hanged while continuously publishing data in embedded mqtt application during power save mode
- BLE notification and Continuous BG scan are not working as expected
- Ongoing efforts to update the readme file are in progress
- Matter issue - SI91X-13524
- BLE long range of 4-5m for BRD4325B A02 board

### SoC

- The "Browser File Viewer" plugin has issues. It can't render the last image included in the markdown files and observed issues accessing some hyperlinks
- In SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations

### Network Stack

### Wi-Fi

- WPA3 connection takes 2.5 sec more than WPA2 connection
- Issue observed with WPA2 Enterprise Connectivity using Microsoft RADIUS Server.

### BLE

- For BLE, dual role scenario issues might occur when connecting as central if the advertising is also going out for the peripheral role. Central connections can be made after the peripheral connections are established and advertising is stopped.
- LMP timeout BLE disconnection observed with the latest Realme mobile handsets.

## Limitations and Unsupported Features

### Wi-Fi/Network Stack

#### Limitations

- Throughput not at par with WiSeConnect 2 in the present release
- Maximum of 3 SSL connections are supported in WiFi alone mode.
- TWT is not verified in Coex mode.
- BGscan is not verified with TWT Feature.
- SIO currently supports SPI and UART.
- Peripherals currently uses UDMA CMSIS driver.

#### Not supported

- DTIM skip feature in power save.
- NCP Support(SDIO, UART,Linux, 3rd party hosts)
- 917 Specific features(degugging utilities)
- Calibration SW APIs
- Keep Alive Functionality
- SNI
- DNS Clients
- APIs for Crypto Hardware(ECDH, DH, SHA, AES)
- Stats APIs
- Multi-threading support for relevant APIs
- SoC Support (Hosted mode): support for switching between LWIP & internal stack in SS
- IPV6 Support (for network application protocols)
- Console application for customers
- Protocols Offload mode: HTTP Server(917 specific), DHCPv6 Server, SNMP, Socket reads up to 64k, POP3, DTLS, mDNS, Web Socket
- Power save support (Message based)
- Baremetal support (for EFR)
- PTA Coexistence with other wireless
- SL Net Hosted mode (SoftAP over LWIP)
- Asynchronous API's(SSL)

### BLE

- For BLE, if the connection is established with a small connection interval (less than 15 ms), simultaneous roles (i.e., Central + Scanning and Peripheral + Advertising) are not supported.
- BLE maximum two concurrent connections are supported, which can be either a connection to two peripheral devices, to one central and one peripheral device or two central devices.
- BLE Slave latency value is valid up to 32 only.

## Terminology

| Term                            | Description                                                                                                                                                                                                    |
| ------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **New Features**                | These items are new to this release                                                                                                                                                                            |
| **Changes/Issues Fixed**        | Changes made to existing features found in previous software releases.                                                                                                                                         |
|                                 | Enhancements to existing product flow and feature set.                                                                                                                                                         |
|                                 | Bug fixes done in the Release                                                                                                                                                                                  |
| **Deprecated Items**            | Features or functions or APIs that are removed from the distributed release to align with the software roadmap                                                                                                 |
| **Known Issues**                | Features or functions that do not work as planned at the time of release. Workarounds may be offered to meet short-term development goals, but longer-term solutions will be added in future software releases |
| **Limitations/Recommendations** | Describes the limitations on product usage and recommendations for optimal use cases                                                                                                                           |

<br />

## Notes

This release supports 917 Common Flash (A0 - BRD4325A, B0 - BRD4325G and B0 - BRD4338A(V 2.0)) and Dual Flash (A0 - BRD4325B).

# WiSeConnect3_SDK_3.0.10 Release Notes

This SDK package supports SoC Mode

- In SoC Mode: Customer Applications can run on Cortex M4. Wireless stacks and Networking stacks run on the Wireless subsystem.
- Silicon Labs' SiWx917 includes an ultra-low power Wi-Fi 6 plus Bluetooth Low Energy (BLE) 5.1 wireless subsystem and an integrated micro-controller application subsystem.
- Support for Phase 1 platform DX peripherals is added.
  > Note: To run the application please install the GSDK patch following below instructions:
  >
  > - Install GSDK version 4.3.0.
  > - Open your terminal application.
  > - Go to your GSDK path and enter the following command.
      git apply --ignore-whitespace --ignore-space-change "extension/wiseconnect3/utilities/gsdk_service_patch/gsdk_service.patch"

> Note: The git apply command needs to be run to apply a GSDK patch not available with the current WiSeConnect 3 release.
>
> - Now you should be able to build and run Dx sample applications.

> Note: Release supports only Simplicity Studio 5.5 & above versions

## SoC Highlights

- **Operating Modes** : Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx),
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n , 802.11ax, BLE 5.1
- **MCU Peripherals** : ADC Static Mode, Analog Comparator, Blinky, Bod, CTS, DAC FIFO, DAC Static, OPAMP, GPIO, I2C, I2S, PWM, RTC, QEI, SPI, UART, USART, UDMA, WDT, Combined Peripheral App, MEMLCD
  : ULP (Ultra Low Power) Peripherals - ulp_gpio, ulp_i2c, ulp_i2s, ulp_ir_decoder, ulp_spi, ulp_timer, ulp_uart, ulp_udma
  : UART and I2C Deepsleep Wakeup Without RAM Retention
- **Multiple Ultra Low Power Modes** : Wi-Fi 6 TWT (Target Wake Time) - for improved network efficiency and device battery life
- **Wi-Fi** : 2.4GHz Wi-Fi Support - WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and latency
- **Cloud** : Amazon Cloud Connectivity Support, Amazon FreeRTOS
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack, BLE Stack and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, SNTP Client
- **IDE** : Simplicity Studio with Windows 10(64-bit)
- **TA/M4 Firmware Update Tool** : Simplicity Commander
- **Hardware kits to evaluate SoC Mode** : Si917-BRD4325B (Dual flash Radio board), Si917-BRD4325A, Si917-BRD4325G (Common Flash Radio board), Si917-BRD4338A (Common Flash Radio Board V2.0)

## Release Details

| Item                      | Details                                                        |
| ------------------------- | -------------------------------------------------------------- |
| Release date              | July 21th, 2023                                                |
| API Version               | 3.0.10(Build 1)                                                |
| Firmware Version          | 2.9.0.0.15                                                     |
| Package Name              | WiSeConnect3_SDK_3.0.10                                        |
| Supported RTOS            | FreeRTOS                                                       |
| Operating Modes Supported | Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx) |

## Updating to this Release

This release consists of Wireless Library - The Library runs on internal Cortex M4 in SoC Mode and supports 50 sample examples.

## Features and Bug Fixes

- Disable default RAM Execution for Common Flash boards and optimise Linker file
- Added MEMLCD Support for 917 and MEMLCD Sample App ( compatible only with Si917-BRD4338A )
- Added IOSTREM support on GSDK 4.3.1
- Added RSI_PS_SkipXtalWaitTime under common_flash_en macro
- Added M4 powersave in TWT tcp and AWS_MQTT client examples
- Added new BLE examples - health_thermometer, glucose, blood_pressure, battery_service
- Added new command line interface application(cli_demo)
- Updated with proper error codes that describes the reason for a failure
- Platform SQA Bug: SI91X-13422
- SDK SQA Bugs - SI91X-13535, SI91X-13549
- Addressed Matter issue - WIFISDK-754, WIFISDK-756, WIFISDK-757
- Updated example applications readme  

## Known Issues

- The current chipset support for all the DX peripherals is A0 and B0(V1.2). B0(V2.0) support shall be provided in subsequent releases.
- I2C High Speed mode is not working as expected.
- SSI bitrate above 10 Msps is not working as expected.
- DUT is getting hanged while continuously publishing data in embedded mqtt application during power save mode
- BLE notification and Continuous BG scan are not working as expected
- Ongoing efforts to update the readme file are in progress
- Matter issues - WIFISDK-752, WIFISDK-753, SI91X-13524
- BLE long range of 4-5m for BRD4325B A02 board

### SoC

- The "Browser File Viewer" plugin has issues. It can't render the last image included in the markdown files and observed issues accessing some hyperlinks
- In SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations

### Network Stack

### Wi-Fi

- WPA3 connection takes 2.5 sec more than WPA2 connection
- Issue observed with WPA2 Enterprise Connectivity using Microsoft RADIUS Server.

### BLE

- For BLE, dual role scenario issues might occur when connecting as central if the advertising is also going out for the peripheral role. Central connections can be made after the peripheral connections are established and advertising is stopped.
- LMP timeout BLE disconnection observed with the latest Realme mobile handsets.

## Limitations and Unsupported Features

### Wi-Fi/Network Stack

#### Limitations

- Throughput not at par with WiSeConnect 2 in the present release
- Maximum of 3 SSL connections are supported in WiFi alone mode.
- TWT is not verified in Coex mode.
- BGscan is not verified with TWT Feature.
- SIO currently supports SPI and UART.
- Peripherals currently uses UDMA CMSIS driver.

#### Not supported

- DTIM skip feature in power save.
- NCP Support(SDIO, UART,Linux, 3rd party hosts)
- 917 Specific features(degugging utilities)
- Calibration SW APIs
- Keep Alive Functionality
- SNI
- DNS Clients
- APIs for Crypto Hardware(ECDH, DH, SHA, AES)
- Stats APIs
- Multi-threading support for relevant APIs
- SoC Support (Hosted mode): support for switching between LWIP & internal stack in SS
- IPV6 Support (for network application protocols)
- Console application for customers
- Protocols Offload mode: HTTP Server(917 specific), DHCPv6 Server, SNMP, Socket reads up to 64k, POP3, DTLS, mDNS, Web Socket
- Power save support (Message based)
- Baremetal support (for EFR)
- PTA Coexistence with other wireless
- SL Net Hosted mode (SoftAP over LWIP)
- Asynchronous API's(TCP,UDP,SSL)

### BLE

- For BLE, if the connection is established with a small connection interval (less than 15 ms), simultaneous roles (i.e., Central + Scanning and Peripheral + Advertising) are not supported.
- BLE maximum two concurrent connections are supported, which can be either a connection to two peripheral devices, to one central and one peripheral device or two central devices.
- BLE Slave latency value is valid up to 32 only.

## Terminology

| Term                            | Description                                                                                                                                                                                                    |
| ------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **New Features**                | These items are new to this release                                                                                                                                                                            |
| **Changes/Issues Fixed**        | Changes made to existing features found in previous software releases.                                                                                                                                         |
|                                 | Enhancements to existing product flow and feature set.                                                                                                                                                         |
|                                 | Bug fixes done in the Release                                                                                                                                                                                  |
| **Deprecated Items**            | Features or functions or APIs that are removed from the distributed release to align with the software roadmap                                                                                                 |
| **Known Issues**                | Features or functions that do not work as planned at the time of release. Workarounds may be offered to meet short-term development goals, but longer-term solutions will be added in future software releases |
| **Limitations/Recommendations** | Describes the limitations on product usage and recommendations for optimal use cases                                                                                                                           |

<br />

## Notes

This release supports 917 Common Flash (A0 - BRD4325A, B0 - BRD4325G and B0 - BRD4338A(V 2.0)) and Dual Flash (A0 - BRD4325B).

# WiSeConnect3_SDK_3.0.9 Release Notes

This SDK package supports SoC Mode

- In SoC Mode: Customer Applications can run on Cortex M4. Wireless stacks and Networking stacks run on the Wireless subsystem.
- Silicon Labs' SiWx917 includes an ultra-low power Wi-Fi 6 plus Bluetooth Low Energy (BLE) 5.1 wireless subsystem and an integrated micro-controller application subsystem.
- Support for Phase 1 platform DX peripherals is added.
  > Note: To run the application please install the GSDK patch following below instructions:
  >
  > - Install GSDK version 4.3.0.
  > - Open your terminal application.
  > - Go to your GSDK path and enter the following command.
      git apply --ignore-whitespace --ignore-space-change "extension/wiseconnect3/utilities/gsdk_service_patch/gsdk_service.patch"

> Note: The git apply command needs to be run to apply a GSDK patch not available with the current WiSeConnect 3 release.
>
> - Now you should be able to build and run Dx sample applications.

> Note: Release supports only Simplicity Studio 5.5 & above versions

## SoC Highlights

- **Operating Modes** : Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx),
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n , 802.11ax, BLE 5.1
- **MCU Peripherals** : ADC Static Mode, Analog Comparator, Blinky, Bod, CTS, DAC FIFO, DAC Static, OPAMP, GPIO, I2C, I2S, PWM, RTC, QEI, SPI, UART, USART, UDMA, WDT, Combined Peripheral App
  : ULP (Ultra Low Power) Peripherals - ulp_gpio, ulp_i2c, ulp_i2s, ulp_ir_decoder, ulp_spi, ulp_timer, ulp_uart, ulp_udma
  : UART and I2C Deepsleep Wakeup Without RAM Retention
- **Multiple Ultra Low Power Modes** : Wi-Fi 6 TWT (Target Wake Time) - for improved network efficiency and device battery life
- **Wi-Fi** : 2.4GHz Wi-Fi Support - WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and latency
- **Cloud** : Amazon Cloud Connectivity Support, Amazon FreeRTOS
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack, BLE Stack and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, SNTP Client
- **IDE** : Simplicity Studio with Windows 10(64-bit)
- **TA/M4 Firmware Update Tool** : Simplicity Commander
- **Hardware kits to evaluate SoC Mode** : Si917-BRD4325B (Dual flash Radio board), Si917-BRD4325A, Si917-BRD4325G (Common Flash Radio board), Si917-BRD4338A (Common Flash Radio Board V2.0)

## Release Details

| Item                      | Details                                                        |
| ------------------------- | -------------------------------------------------------------- |
| Release date              | July 10th, 2023                                                 |
| API Version               | 3.0.9(Build 1)                                                 |
| Firmware Version          | 2.9.0.0.8                                                      |
| Package Name              | WiSeConnect3_SDK_3.0.9                                         |
| Supported RTOS            | FreeRTOS                                                       |
| Operating Modes Supported | Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx) |

## Updating to this Release

This release consists of Wireless Library - The Library runs on internal Cortex M4 in SoC Mode and supports 45 sample examples.

## Features and Bug Fixes

- Added B0(V1.2) chipset support for platform examples.
- Addressed Matter issues
- SL DEINIT issue Resolved
- Implemented station_ping_v6 example

## Known Issues

- The current chipset support for all the DX peripherals is A0 and B0(V1.2). B0(V2.0) support shall be provided in subsequent releases.
- I2C High Speed mode is not working as expected.
- SSI bitrate above 10 Msps is not working as expected.
- Powersave Deepsleep issue with Common Flash B0 Board.
- DUT is getting hanged while continuously publishing data in embedded mqtt application during power save mode
- BLE notification and Continuous BG scan are not working as expected
- Ongoing efforts to update the readme file are in progress

### SoC

- The "Browser File Viewer" plugin has issues. It can't render the last image included in the markdown files and observed issues accessing some hyperlinks
- In SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations

### Network Stack

### Wi-Fi

- WPA3 connection takes 2.5 sec more than WPA2 connection
- Issue observed with WPA2 Enterprise Connectivity using Microsoft RADIUS Server.

### BLE

- For BLE, dual role scenario issues might occur when connecting as central if the advertising is also going out for the peripheral role. Central connections can be made after the peripheral connections are established and advertising is stopped.
- LMP timeout BLE disconnection observed with the latest Realme mobile handsets.

## Limitations and Unsupported Features

### Wi-Fi/Network Stack

#### Limitations

- Throughput not at par with WiSeConnect 2 in the present release
- Maximum of 3 SSL connections are supported in WiFi alone mode.
- TWT is not verified in Coex mode.
- BGscan is not verified with TWT Feature.
- SIO currently supports SPI and UART.
- Peripherals currently uses UDMA CMSIS driver.

#### Not supported

- DTIM skip feature in power save.
- NCP Support(SDIO, UART,Linux, 3rd party hosts)
- 917 Specific features(degugging utilities)
- Calibration SW APIs
- Keep Alive Functionality
- SNI
- DNS Clients
- Asynchronous API's(TCP,UDP,SSL),
- APIs for Crypto Hardware(ECDH, DH, SHA, AES)
- Stats APIs
- Multi-threading support for relevant APIs
- SoC Support (Hosted mode): support for switching between LWIP & internal stack in SS
- IPV6 Support (for network application protocols)
- Console application for customers
- Protocols Offload mode: HTTP Server(917 specific), DHCPv6 Server, SNMP, Socket reads up to 64k, POP3, DTLS, mDNS, Web Socket
- Power save support (Message based)
- Baremetal support (for EFR)
- PTA Coexistence with other wireless
- SL Net Hosted mode (SoftAP over LWIP)

### BLE

- For BLE, if the connection is established with a small connection interval (less than 15 ms), simultaneous roles (i.e., Central + Scanning and Peripheral + Advertising) are not supported.
- BLE maximum two concurrent connections are supported, which can be either a connection to two peripheral devices, to one central and one peripheral device or two central devices.
- BLE Slave latency value is valid up to 32 only.

## Terminology

| Term                            | Description                                                                                                                                                                                                    |
| ------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **New Features**                | These items are new to this release                                                                                                                                                                            |
| **Changes/Issues Fixed**        | Changes made to existing features found in previous software releases.                                                                                                                                         |
|                                 | Enhancements to existing product flow and feature set.                                                                                                                                                         |
|                                 | Bug fixes done in the Release                                                                                                                                                                                  |
| **Deprecated Items**            | Features or functions or APIs that are removed from the distributed release to align with the software roadmap                                                                                                 |
| **Known Issues**                | Features or functions that do not work as planned at the time of release. Workarounds may be offered to meet short-term development goals, but longer-term solutions will be added in future software releases |
| **Limitations/Recommendations** | Describes the limitations on product usage and recommendations for optimal use cases                                                                                                                           |

<br />

## Notes

This release supports 917 Common Flash (A0 - BRD4325A, B0 - BRD4325G and B0 - BRD4338A(V 2.0)) and Dual Flash (A0 - BRD4325B).

# WiSeConnect3_SDK_3.0.7 Release Notes

This SDK package supports SoC Mode

- In SoC Mode: Customer Applications can run on Cortex M4. Wireless stacks and Networking stacks run on the Wireless subsystem.
- Silicon Labs' SiWx917 includes an ultra-low power Wi-Fi 6 plus Bluetooth Low Energy (BLE) 5.1 wireless subsystem and an integrated micro-controller application subsystem.
- Support for Phase 1 platform DX peripherals is added.
  > Note: To run the application please download the GSDK from below link and follow the instructions:
  >
  > - Download GSDK from <https://artifactory.silabs.net/artifactory/platswhyd-docker-development/gecko-sdk-dx-v2.zip>
  > - Open latest simplicity studio and add new GSDK which is downloaded from above step.
  > - Now add wiseconnect3 release package as extension to that gsdk.
  > - Now you should be able to build and run Dx sample applications.

> Note: Release supports only Simplicity Studio 5.5 & above versions

## SoC Highlights

- **Operating Modes** : Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx),
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n , 802.11ax, BLE 5.1
- **MCU Peripherals** : ADC Static Mode, Analog Comparator, Blinky, Bod, CTS, DAC FIFO, DAC Static, OPAMP, GPIO, I2C, I2S, PWM, RTC, QEI, SPI, UART, USART, UDMA, WDT, Combined Peripheral App
  : ULP (Ultra Low Power) Peripherals - ulp_gpio, ulp_i2c, ulp_i2s, ulp_ir_decoder, ulp_spi, ulp_timer, ulp_uart, ulp_udma
  : UART and I2C Deepsleep Wakeup Without RAM Retention
- **Multiple Ultra Low Power Modes** : Wi-Fi 6 TWT (Target Wake Time) - for improved network efficiency and device battery life
- **Wi-Fi** : 2.4GHz Wi-Fi Support - WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and latency
- **Cloud** : Amazon Cloud Connectivity Support, Amazon FreeRTOS
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack, BLE Stack and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, SNTP Client
- **IDE** : Simplicity Studio with Windows 10(64-bit)
- **TA/M4 Firmware Update Tool** : Simplicity Commander
- **Hardware kits to evaluate SoC Mode** : Si917-BRD4325B (Dual flash Radio board), Si917-BRD4325A, Si917-BRD4325G (Common Flash Radio board), Si917-BRD4338A (Common Flash Radio Board V2.0)

## Release Details

| Item                      | Details                                                        |
| ------------------------- | -------------------------------------------------------------- |
| Release date              | June 26th, 2023                                                |
| API Version               | 3.0.7(Build 1)                                                 |
| Firmware Version          | 2.9.0.0.6                                                      |
| Package Name              | WiSeConnect3_SDK_3.0.7                                         |
| Supported RTOS            | FreeRTOS                                                       |
| Operating Modes Supported | Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx) |

## Updating to this Release

This release consists of Wireless Library - The Library runs on internal Cortex M4 in SoC Mode and supports 45 sample examples.

## Features and Bug Fixes

- Phase-1 peripheral support for Platform Dx added to this release
- Supported DX Peripherals: Calender, ULP Timer, GSPI, SSI, GPIO, I2C, Watchdog Timer, DMA, USART, Config Timer, SIO
- Supported Services: Sleeptimer, IOStream, NVM3

## Known Issues

- The current chipset support for all the DX peripherals is A0, subsequent releases will add support to additional boards.
- Chipset support for services - Sleeptimer: B0, NVM3: A0,B0, IOStream: A0(brd4325a)
- wifi_deinit is not working as expected

### SoC

- The "Browser File Viewer" plugin has issues. It can't render the last image included in the markdown files and observed issues accessing some hyperlinks
- In SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations

### Network Stack

### Wi-Fi

- WPA3 connection takes 2.5 sec more than WPA2 connection
- Issue observed with WPA2 Enterprise Connectivity using Microsoft RADIUS Server.

### BLE

- For BLE, dual role scenario issues might occur when connecting as central if the advertising is also going out for the peripheral role. Central connections can be made after the peripheral connections are established and advertising is stopped.
- LMP timeout BLE disconnection observed with the latest Realme mobile handsets.

## Limitations and Unsupported Features

### Wi-Fi/Network Stack

- Maximum of 3 SSL connections are supported in WiFi alone mode.
- TWT is not verified in Coex mode.
- BGscan is not verified with TWT Feature.
- No support for DTIM skip feature in power save.

### BLE

- For BLE, if the connection is established with a small connection interval (less than 15 ms), simultaneous roles (i.e., Central + Scanning and Peripheral + Advertising) are not supported.
- BLE maximum two concurrent connections are supported, which can be either a connection to two peripheral devices, to one central and one peripheral device or two central devices.
- BLE Slave latency value is valid up to 32 only.

## Terminology

| Term                            | Description                                                                                                                                                                                                    |
| ------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **New Features**                | These items are new to this release                                                                                                                                                                            |
| **Changes/Issues Fixed**        | Changes made to existing features found in previous software releases.                                                                                                                                         |
|                                 | Enhancements to existing product flow and feature set.                                                                                                                                                         |
|                                 | Bug fixes done in the Release                                                                                                                                                                                  |
| **Deprecated Items**            | Features or functions or APIs that are removed from the distributed release to align with the software roadmap                                                                                                 |
| **Known Issues**                | Features or functions that do not work as planned at the time of release. Workarounds may be offered to meet short-term development goals, but longer-term solutions will be added in future software releases |
| **Limitations/Recommendations** | Describes the limitations on product usage and recommendations for optimal use cases                                                                                                                           |

<br />

## Notes

This release supports 917 Common Flash (A0 - BRD4325A, B0 - BRD4325G and B0 - BRD4338A(V 2.0)) and Dual Flash (A0 - BRD4325B).

# WiSeConnect3_SDK_3.0.6 Release Notes

This SDK package supports SoC Mode

- In SoC Mode: Customer Applications can run on Cortex M4. Wireless stacks and Networking stacks run on the Wireless subsystem.
- Silicon Labs' SiWx917 includes an ultra-low power Wi-Fi 6 plus Bluetooth Low Energy (BLE) 5.1 wireless subsystem and an integrated micro-controller application subsystem.

> Note: Release supports only Simplicity Studio 5.5 & above versions

## SoC Highlights

- **Operating Modes** : Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx),
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n , 802.11ax, BLE 5.1
- **MCU Peripherals** : ADC Static Mode, Analog Comparator, Blinky, Bod, CTS, DAC FIFO, DAC Static, OPAMP, GPIO, I2C, I2S, PWM, RTC, QEI, SPI, UART, USART, UDMA, WDT, Combined Peripheral App
  : ULP (Ultra Low Power) Peripherals - ulp_gpio, ulp_i2c, ulp_i2s, ulp_ir_decoder, ulp_spi, ulp_timer, ulp_uart, ulp_udma
  : UART and I2C Deepsleep Wakeup Without RAM Retention
- **Multiple Ultra Low Power Modes** : Wi-Fi 6 TWT (Target Wake Time) - for improved network efficiency and device battery life
- **Wi-Fi** : 2.4GHz Wi-Fi Support - WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and latency
- **Cloud** : Amazon Cloud Connectivity Support, Amazon FreeRTOS
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack, BLE Stack and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, SNTP Client
- **IDE** : Simplicity Studio with Windows 10(64-bit)
- **TA/M4 Firmware Update Tool** : Simplicity Commander
- **Hardware kits to evaluate SoC Mode** : Si917-BRD4325B (Dual flash Radio board), Si917-BRD4325A, Si917-BRD4325G (Common Flash Radio board), Si917-BRD4338A (Common Flash Radio Board V2.0)

## Release Details

| Item                      | Details                                                        |
| ------------------------- | -------------------------------------------------------------- |
| Release date              | June 16th, 2023                                                |
| API Version               | 3.0.6(Build 1)                                                 |
| Firmware Version          | 2.9.0.0.4                                                      |
| Package Name              | WiSeConnect3_SDK_3.0.6                                         |
| Supported RTOS            | FreeRTOS                                                       |
| Operating Modes Supported | Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx) |

## Updating to this Release

This release consists of Wireless Library - The Library runs on internal Cortex M4 in SoC Mode and supports 45 sample examples.

## Features and Bug Fixes

- Added support for sl wifi get pairwise master key
- Updated socket functionality to work with ipv6
- Implemented examples - access_point_v6, wlan_throughput_v6, wifi_station_ble_provisioning_aws_logging_stats,
  wlan_throughput_ble_dual_role, wlan_https_ble_dual_role, Standby associated with TCP Client with TCP Packet every 55sec

## Known Issues

- Dx enhanced Platform APIs Phase -1 Integrated with SDK and NVM3 credential manager dual flash SoC - Update examples with sl_net_set_credential()

### SoC

- The "Browser File Viewer" plugin has issues. It can't render the last image included in the markdown files and observed issues accessing some hyperlinks
- In SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations

### Network Stack

### Wi-Fi

- WPA3 connection takes 2.5 sec more than WPA2 connection
- Issue observed with WPA2 Enterprise Connectivity using Microsoft RADIUS Server.

### BLE

- For BLE, dual role scenario issues might occur when connecting as central if the advertising is also going out for the peripheral role. Central connections can be made after the peripheral connections are established and advertising is stopped.
- LMP timeout BLE disconnection observed with the latest Realme mobile handsets.

## Limitations and Unsupported Features

### Wi-Fi/Network Stack

- Maximum of 3 SSL connections are supported in WiFi alone mode.
- TWT is not verified in Coex mode.
- BGscan is not verified with TWT Feature.
- No support for DTIM skip feature in power save.

### BLE

- For BLE, if the connection is established with a small connection interval (less than 15 ms), simultaneous roles (i.e., Central + Scanning and Peripheral + Advertising) are not supported.
- BLE maximum two concurrent connections are supported, which can be either a connection to two peripheral devices, to one central and one peripheral device or two central devices.
- BLE Slave latency value is valid up to 32 only.

## Terminology

| Term                            | Description                                                                                                                                                                                                    |
| ------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **New Features**                | These items are new to this release                                                                                                                                                                            |
| **Changes/Issues Fixed**        | Changes made to existing features found in previous software releases.                                                                                                                                         |
|                                 | Enhancements to existing product flow and feature set.                                                                                                                                                         |
|                                 | Bug fixes done in the Release                                                                                                                                                                                  |
| **Deprecated Items**            | Features or functions or APIs that are removed from the distributed release to align with the software roadmap                                                                                                 |
| **Known Issues**                | Features or functions that do not work as planned at the time of release. Workarounds may be offered to meet short-term development goals, but longer-term solutions will be added in future software releases |
| **Limitations/Recommendations** | Describes the limitations on product usage and recommendations for optimal use cases                                                                                                                           |

<br />

## Notes

This release supports 917 Common Flash (A0 - BRD4325A, B0 - BRD4325G and B0 - BRD4338A(V 2.0)) and Dual Flash (A0 - BRD4325B).

# WiSeConnect3_SDK_3.0.5 Release Notes

This SDK package supports SoC Mode

- In SoC Mode: Customer Applications can run on Cortex M4. Wireless stacks and Networking stacks run on the Wireless subsystem.
- Silicon Labs' SiWx917 includes an ultra-low power Wi-Fi 6 plus Bluetooth Low Energy (BLE) 5.1 wireless subsystem and an integrated micro-controller application subsystem.

> Note: Release supports only Simplicity Studio 5.5 & above versions

## SoC Highlights

- **Operating Modes** : Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx),
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n , 802.11ax, BLE 5.1
- **MCU Peripherals** : ADC Static Mode, Analog Comparator, Blinky, Bod, CTS, DAC FIFO, DAC Static, OPAMP, GPIO, I2C, I2S, PWM, RTC, QEI, SPI, UART, USART, UDMA, WDT, Combined Peripheral App
  : ULP (Ultra Low Power) Peripherals - ulp_gpio, ulp_i2c, ulp_i2s, ulp_ir_decoder, ulp_spi, ulp_timer, ulp_uart, ulp_udma
  : UART and I2C Deepsleep Wakeup Without RAM Retention
- **Multiple Ultra Low Power Modes** : Wi-Fi 6 TWT (Target Wake Time) - for improved network efficiency and device battery life
- **Wi-Fi** : 2.4GHz Wi-Fi Support - WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and latency
- **Cloud** : Amazon Cloud Connectivity Support, Amazon FreeRTOS
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack, BLE Stack and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, SNTP Client
- **IDE** : Simplicity Studio with Windows 10(64-bit)
- **TA/M4 Firmware Update Tool** : Simplicity Commander
- **Hardware kits to evaluate SoC Mode** : Si917-BRD4325B (Dual flash Radio board), Si917-BRD4325A and Si917-BRD4325G (Common Flash Radio board)

## Release Details

| Item                      | Details                                                        |
| ------------------------- | -------------------------------------------------------------- |
| Release date              | June 7th, 2023                                                 |
| API Version               | 3.0.5(Build 1)                                                 |
| Firmware Version          | 2.9.0.0.3                                                      |
| Package Name              | WiSeConnect3_SDK_3.0.5                                         |
| Supported RTOS            | FreeRTOS                                                       |
| Operating Modes Supported | Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx) |

## Updating to this Release

This release consists of Wireless Library - The Library runs on internal Cortex M4 in SoC Mode and supports 43 sample examples.

## Features and Bug Fixes

- Added Support for RSI_FAST_PSP
- Fixed issue with IPMU offset address values for Common Flash B0 Board i.e. BRD4325G
- Updated httpclient to support ssl 1.2 and 1.3
- Added support to configure rejoin parameters
- Added support for EAP-FAST and EAP-PEAP
- fix the issue in power_save_deep_sleep-example on common flash board
- Handling multiple successful events in case of TWT.
- Update BLE and WLAN examples to Latest Firware version 2.9.0.0.3
- Implemented examples - OTAF client, three ssl concurrent client sockets and BLE multiconnection gatt test

## Known Issues

- Dx enhanced Platform APIs Phase -1 Integrated with SDK and NVM3 credential manager dual flash SoC - Update examples with sl_net_set_credential()
- IPv6 support not working for Sockets
- wlan_station_ble_provisioning_AWS_logging_stats - functionality not working as expected

### SoC

- The "Browser File Viewer" plugin has issues. It can't render the last image included in the markdown files and observed issues accessing some hyperlinks
- In SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations

### Network Stack

### Wi-Fi

- WPA3 connection takes 2.5 sec more than WPA2 connection
- Issue observed with WPA2 Enterprise Connectivity using Microsoft RADIUS Server.

### BLE

- For BLE, dual role scenario issues might occur when connecting as central if the advertising is also going out for the peripheral role. Central connections can be made after the peripheral connections are established and advertising is stopped.
- LMP timeout BLE disconnection observed with the latest Realme mobile handsets.

## Limitations and Unsupported Features

### Wi-Fi/Network Stack

- Maximum of 3 SSL connections are supported in WiFi alone mode.
- TWT is not verified in Coex mode.
- BGscan is not verified with TWT Feature.
- No support for DTIM skip feature in power save.

### BLE

- For BLE, if the connection is established with a small connection interval (less than 15 ms), simultaneous roles (i.e., Central + Scanning and Peripheral + Advertising) are not supported.
- BLE maximum two concurrent connections are supported, which can be either a connection to two peripheral devices, to one central and one peripheral device or two central devices.
- BLE Slave latency value is valid up to 32 only.

## Terminology

| Term                            | Description                                                                                                                                                                                                    |
| ------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **New Features**                | These items are new to this release                                                                                                                                                                            |
| **Changes/Issues Fixed**        | Changes made to existing features found in previous software releases.                                                                                                                                         |
|                                 | Enhancements to existing product flow and feature set.                                                                                                                                                         |
|                                 | Bug fixes done in the Release                                                                                                                                                                                  |
| **Deprecated Items**            | Features or functions or APIs that are removed from the distributed release to align with the software roadmap                                                                                                 |
| **Known Issues**                | Features or functions that do not work as planned at the time of release. Workarounds may be offered to meet short-term development goals, but longer-term solutions will be added in future software releases |
| **Limitations/Recommendations** | Describes the limitations on product usage and recommendations for optimal use cases                                                                                                                           |

<br />

## Notes

This release supports 917 Common Flash (A0 - BRD4325A and B0 - BRD4325G) and Dual Flash (A0 - BRD4325B).

# WiSeConnect3_SDK_3.0.4 Release Notes

This SDK package supports SoC Mode

- In SoC Mode: Customer Applications can run on Cortex M4. Wireless stacks and Networking stacks run on the Wireless subsystem.
- Silicon Labs' SiWx917 includes an ultra-low power Wi-Fi 6 plus Bluetooth Low Energy (BLE) 5.1 wireless subsystem and an integrated micro-controller application subsystem.

> Note: Release supports only Simplicity Studio 5.5 & above versions

## SoC Highlights

- **Operating Modes** : Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx),
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n , 802.11ax, BLE 5.1
- **MCU Peripherals** : ADC Static Mode, Analog Comparator, Blinky, Bod, CTS, DAC FIFO, DAC Static, OPAMP, GPIO, I2C, I2S, PWM, RTC, QEI, SPI, UART, USART, UDMA, WDT, Combined Peripheral App
  : ULP (Ultra Low Power) Peripherals - ulp_gpio, ulp_i2c, ulp_i2s, ulp_ir_decoder, ulp_spi, ulp_timer, ulp_uart, ulp_udma
  : UART and I2C Deepsleep Wakeup Without RAM Retention
- **Multiple Ultra Low Power Modes** : Wi-Fi 6 TWT (Target Wake Time) - for improved network efficiency and device battery life
- **Wi-Fi** : 2.4GHz Wi-Fi Support - WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and latency
- **Cloud** : Amazon Cloud Connectivity Support, Amazon FreeRTOS
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack, BLE Stack and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client, SNTP Client
- **IDE** : Simplicity Studio with Windows 10(64-bit)
- **TA/M4 Firmware Update Tool** : Simplicity Commander
- **Hardware kits to evaluate SoC Mode** : Si917-BRD4325B (Dual flash Radio board), Si917-BRD4325A and Si917-BRD4325G (Common Flash Radio board)

## Release Details

| Item                      | Details                                                        |
| ------------------------- | -------------------------------------------------------------- |
| Release date              | MAY 29th, 2023                                                 |
| API Version               | 3.0.4(Build 1)                                                 |
| Firmware Version          | 2.9.0.0.2                                                      |
| Package Name              | WiSeConnect3_SDK_3.0.4                                         |
| Supported RTOS            | FreeRTOS                                                       |
| Operating Modes Supported | Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx) |

## Updating to this Release

This release consists of Wireless Library - The Library runs on internal Cortex M4 in SoC Mode and supports 40 sample examples.

## Features and Bug Fixes

- Added LWIP Support
- Added Support for Common Flash B0 Board i.e. BRD4325G
- Fixed certificate configuration issue in AWS MQTT example
- Updated Linker file.
- Update sl_wifi_connect with configurable for okc
- API Documentation enhancement
- Print IPv6 Address
- Fixed SNTP client build issues in SS
- Update BLE and WLAN examples to Latest Firware version 2.9.0.0.2
- Implemented examples - tcp_client, udp_client, ssl_client, select_app

## Known Issues

- Dx enhanced Platform APIs Phase -1 Integrated with SDK and NVM3 credential manager dual flash SoC - Update examples with sl_net_set_credential()
- 917 Specific features: OTAF
- IPv6 support not working for Sockets
- wlan_station_ble_provisioning_AWS_logging_stats - functionality not working as expected
- TWT response handling
- Minor changes need to be ported for 2.9.0.2 and later FW releases
- power_save_deep_sleep example is not working as expected (M4 and TA)

### SoC

- The "Browser File Viewer" plugin has issues. It can't render the last image included in the markdown files and observed issues accessing some hyperlinks
- In SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations

### Network Stack

### Wi-Fi

- WPA3 connection takes 2.5 sec more than WPA2 connection
- Issue observed with WPA2 Enterprise Connectivity using Microsoft RADIUS Server.

### BLE

- For BLE, dual role scenario issues might occur when connecting as central if the advertising is also going out for the peripheral role. Central connections can be made after the peripheral connections are established and advertising is stopped.
- LMP timeout BLE disconnection observed with the latest Realme mobile handsets.
- BLE Powersave + RTOS is not supported in SoC Mode.

## Limitations and Unsupported Features

### Wi-Fi/Network Stack

- Maximum of 3 SSL connections are supported in WiFi alone mode.
- TWT is not verified in Coex mode.
- BGscan is not verified with TWT Feature.
- No support for DTIM skip feature in power save.

### BLE

- For BLE, if the connection is established with a small connection interval (less than 15 ms), simultaneous roles (i.e., Central + Scanning and Peripheral + Advertising) are not supported.
- BLE maximum two concurrent connections are supported, which can be either a connection to two peripheral devices, to one central and one peripheral device or two central devices.
- BLE Slave latency value is valid up to 32 only.

### SoC

- RTOS support is not available for MCU peripheral drivers. Application-level RTOS support exists.

## Terminology

| Term                            | Description                                                                                                                                                                                                    |
| ------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **New Features**                | These items are new to this release                                                                                                                                                                            |
| **Changes/Issues Fixed**        | Changes made to existing features found in previous software releases.                                                                                                                                         |
|                                 | Enhancements to existing product flow and feature set.                                                                                                                                                         |
|                                 | Bug fixes done in the Release                                                                                                                                                                                  |
| **Deprecated Items**            | Features or functions or APIs that are removed from the distributed release to align with the software roadmap                                                                                                 |
| **Known Issues**                | Features or functions that do not work as planned at the time of release. Workarounds may be offered to meet short-term development goals, but longer-term solutions will be added in future software releases |
| **Limitations/Recommendations** | Describes the limitations on product usage and recommendations for optimal use cases                                                                                                                           |

<br />

## Notes

This release supports 917 Common Flash (A0 and B0) and Dual Flash (A0).

# WiSeConnect3_SDK_3.0.3 Release Notes

This SDK package supports SoC Mode

- In SoC Mode: Customer Applications can run on Cortex M4. Wireless stacks and Networking stacks run on the Wireless subsystem.
- Silicon Labs' SiWx917 includes an ultra-low power Wi-Fi 6 plus Bluetooth Low Energy (BLE) 5.1 wireless subsystem and an integrated micro-controller application subsystem.

> Note: Release supports only Simplicity Studio 5.5 & above versions

## SoC Highlights

- **Operating Modes** : Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx),
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n , 802.11ax, BLE 5.1
- **MCU Peripherals** : ADC Static Mode, Analog Comparator, Blinky, Bod, CTS, DAC FIFO, DAC Static, OPAMP, GPIO, I2C, I2S, PWM, RTC, QEI, SPI, UART, USART, UDMA, WDT, Combined Peripheral App
  : ULP (Ultra Low Power) Peripherals - ulp_gpio, ulp_i2c, ulp_i2s, ulp_ir_decoder, ulp_spi, ulp_timer, ulp_uart, ulp_udma
  : UART and I2C Deepsleep Wakeup Without RAM Retention
- **Multiple Ultra Low Power Modes** : Wi-Fi 6 TWT (Target Wake Time) - for improved network efficiency and device battery life
- **Wi-Fi** : 2.4GHz Wi-Fi Support - WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and latency
- **Cloud** : Amazon Cloud Connectivity Support, Amazon FreeRTOS
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack, BLE Stack and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client
- **IDE** : Simplicity Studio with Windows 10(64-bit)
- **TA/M4 Firmware Update Tool** : Simplicity Commander
- **Hardware kits to evaluate SoC Mode** : Si917-BRD4325B (Dual flash Radio board)

## Release Details

| Item                      | Details                                                        |
| ------------------------- | -------------------------------------------------------------- |
| Release date              | MAY 22nd, 2023                                                 |
| API Version               | 3.0.3(Build 1)                                                 |
| Firmware Version          | 1711.1.0.2.0.2                                                 |
| Package Name              | WiSeConnect3_SDK_3.0.3                                         |
| Supported RTOS            | FreeRTOS                                                       |
| Operating Modes Supported | Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx) |

## Updating to this Release

This release consists of Wireless Library - The Library runs on internal Cortex M4 in SoC Mode and supports 33 sample examples.

## Features and Bug Fixes

- Added SNTP client Application
- Handling DHCP of AP
- Update BLE and WLAN examples to Latest Firware version 1.0.2.0.2
- Update TWT Config Error handling
- Update http_client example to support Certificate Index
- Update RSI_WLAN_REQ_11AX_PARAMS to be updated with configurable guard interval
- Update RSI_WLAN_RSP_JOIN handling to support concurrent mode usecase
- API Documentation enhancement
- Implemented SNTP Client APIs
- Added support for printing floating point in Simplicity Studio IDE.
- APPS Team Feedback (Difficulty in making initial configurations using the new Wi-Fi SDK)
- Update Linker file for Common flash for TLS Issue

## Known Issues

### SoC

- The "Browser File Viewer" plugin has issues. It can't render the last image included in the markdown files and observed issues accessing some hyperlinks
- In SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations

### Network Stack

### Wi-Fi

- WPA3 connection takes 2.5 sec more than WPA2 connection
- Issue observed with WPA2 Enterprise Connectivity using Microsoft RADIUS Server.
- power_save_deep_sleep example is not working

### BLE

- For BLE, dual role scenario issues might occur when connecting as central if the advertising is also going out for the peripheral role. Central connections can be made after the peripheral connections are established and advertising is stopped.
- LMP timeout BLE disconnection observed with the latest Realme mobile handsets.
- BLE Powersave + RTOS is not supported in SoC Mode.

## Limitations and Unsupported Features

### Wi-Fi/Network Stack

- Maximum of 3 SSL connections are supported in WiFi alone mode.
- TWT is not verified in Coex mode.
- BGscan is not verified with TWT Feature.
- No support for DTIM skip feature in power save.

### BLE

- For BLE, if the connection is established with a small connection interval (less than 15 ms), simultaneous roles (i.e., Central + Scanning and Peripheral + Advertising) are not supported.
- BLE maximum two concurrent connections are supported, which can be either a connection to two peripheral devices, to one central and one peripheral device or two central devices.
- BLE Slave latency value is valid up to 32 only.

### SoC

- RTOS support is not available for MCU peripheral drivers. Application-level RTOS support exists.

## Terminology

| Term                            | Description                                                                                                                                                                                                    |
| ------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **New Features**                | These items are new to this release                                                                                                                                                                            |
| **Changes/Issues Fixed**        | Changes made to existing features found in previous software releases.                                                                                                                                         |
|                                 | Enhancements to existing product flow and feature set.                                                                                                                                                         |
|                                 | Bug fixes done in the Release                                                                                                                                                                                  |
| **Deprecated Items**            | Features or functions or APIs that are removed from the distributed release to align with the software roadmap                                                                                                 |
| **Known Issues**                | Features or functions that do not work as planned at the time of release. Workarounds may be offered to meet short-term development goals, but longer-term solutions will be added in future software releases |
| **Limitations/Recommendations** | Describes the limitations on product usage and recommendations for optimal use cases                                                                                                                           |

<br />

## Notes

This release supports 917 A0(Common flash & Dual flash).

# WiSeConnect3_SDK_3.0.2 Release Notes

This SDK package supports SoC Mode

- In SoC Mode: Customer Applications can run on Cortex M4. Wireless stacks and Networking stacks run on the Wireless subsystem.
- Silicon Labs' SiWx917 includes an ultra-low power Wi-Fi 6 plus Bluetooth Low Energy (BLE) 5.1 wireless subsystem and an integrated micro-controller application subsystem.

> Note: Release supports only Simplicity Studio 5.5 & above versions

## SoC Highlights

- **Operating Modes** : Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx),
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n , 802.11ax, BLE 5.1
- **MCU Peripherals** : ADC Static Mode, Analog Comparator, Blinky, Bod, CTS, DAC FIFO, DAC Static, OPAMP, GPIO, I2C, I2S, PWM, RTC, QEI, SPI, UART, USART, UDMA, WDT, Combined Peripheral App
  : ULP (Ultra Low Power) Peripherals - ulp_gpio, ulp_i2c, ulp_i2s, ulp_ir_decoder, ulp_spi, ulp_timer, ulp_uart, ulp_udma
  : UART and I2C Deepsleep Wakeup Without RAM Retention
- **Multiple Ultra Low Power Modes** : Wi-Fi 6 TWT (Target Wake Time) - for improved network efficiency and device battery life
- **Wi-Fi** : 2.4GHz Wi-Fi Support - WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and latency
- **Cloud** : Amazon Cloud Connectivity Support, Amazon FreeRTOS
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack, BLE Stack and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client
- **IDE** : Simplicity Studio with Windows 10(64-bit)
- **TA/M4 Firmware Update Tool** : Simplicity Commander
- **Hardware kits to evaluate SoC Mode** : Si917-BRD4325B (Dual flash Radio board)

## Release Details

| Item                      | Details                                                        |
| ------------------------- | -------------------------------------------------------------- |
| Release date              | MAY 2nd, 2023                                                  |
| API Version               | 3.0.2(Build 1)                                                 |
| Firmware Version          | 1711.1.0.0.0.29                                                |
| Package Name              | WiSeConnect3_SDK_3.0.2                                         |
| Supported RTOS            | FreeRTOS                                                       |
| Operating Modes Supported | Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx) |

## Updating to this Release

This release consists of Wireless Library - The Library runs on internal Cortex M4 in SoC Mode and supports 27 sample examples.

## Features and Bug Fixes

- Added Two Applications
  TLS client
  BLE throughput
- Enhancement of example readme files
- Added migration guide, Getting Started Guide​
- Updated API documentation
- Added UTF support for SL_WIFI APIs, SL_NET APIs, etc ..
- Added M4 Powersave APIs and updated M4 Powersave changes in powersave_standby_associated application.
- Added Support for following APIs/Frame
  RSI_WLAN_REQ_GAIN_TABLE,
  RSI_WLAN_REQ_IPCONFV6,
  RSI_COMMON_REQ_SOFT_RESET
  RSI_COMMON_REQ_ASSERT
- Added .bat utility for common flash

## Known Issues

### SoC

- No support for floating point print in Simplicity Studio IDE.
- The "Browser File Viewer" plugin has issues. It can't render the last image included in the markdown files and observed issues accessing some hyperlinks
- In SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations

### Network Stack

### Wi-Fi

- WPA3 connection takes 2.5 sec more than WPA2 connection
- Issue observed with WPA2 Enterprise Connectivity using Microsoft RADIUS Server.

### BLE

- For BLE, dual role scenario issues might occur when connecting as central if the advertising is also going out for the peripheral role. Central connections can be made after the peripheral connections are established and advertising is stopped.
- LMP timeout BLE disconnection observed with the latest Realme mobile handsets.
- BLE Powersave + RTOS is not supported in SoC Mode.

## Limitations and Unsupported Features

### Wi-Fi/Network Stack

- Maximum of 3 SSL connections are supported in WiFi alone mode.
- TWT is not verified in Coex mode.
- BGscan is not verified with TWT Feature.
- No support for DTIM skip feature in power save.

### BLE

- For BLE, if the connection is established with a small connection interval (less than 15 ms), simultaneous roles (i.e., Central + Scanning and Peripheral + Advertising) are not supported.
- BLE maximum two concurrent connections are supported, which can be either a connection to two peripheral devices, to one central and one peripheral device or two central devices.
- BLE Slave latency value is valid up to 32 only.

### SoC

- RTOS support is not available for MCU peripheral drivers. Application-level RTOS support exists.

## Terminology

| Term                            | Description                                                                                                                                                                                                    |
| ------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **New Features**                | These items are new to this release                                                                                                                                                                            |
| **Changes/Issues Fixed**        | Changes made to existing features found in previous software releases.                                                                                                                                         |
|                                 | Enhancements to existing product flow and feature set.                                                                                                                                                         |
|                                 | Bug fixes done in the Release                                                                                                                                                                                  |
| **Deprecated Items**            | Features or functions or APIs that are removed from the distributed release to align with the software roadmap                                                                                                 |
| **Known Issues**                | Features or functions that do not work as planned at the time of release. Workarounds may be offered to meet short-term development goals, but longer-term solutions will be added in future software releases |
| **Limitations/Recommendations** | Describes the limitations on product usage and recommendations for optimal use cases                                                                                                                           |

<br />

## Notes

# WiSeConnect3_SDK_IR_1.0.1 Release Notes

This SDK package supports SoC Mode

- In SoC Mode: Customer Applications can run on Cortex M4. Wireless stacks and Networking stacks run on the Wireless subsystem.
- Silicon Labs' SiWx917 includes an ultra-low power Wi-Fi 6 plus Bluetooth Low Energy (BLE) 5.1 wireless subsystem and an integrated micro-controller application subsystem.

> Note: Release supports only Simplicity Studio 5.5 & above versions

## SoC Highlights

- **Operating Modes** : Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx),
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n , 802.11ax, BLE 5.1
- **MCU Peripherals** : ADC Static Mode, Analog Comparator, Blinky, Bod, CTS, DAC FIFO, DAC Static, OPAMP, GPIO, I2C, I2S, PWM, RTC, QEI, SPI, UART, USART, UDMA, WDT, Combined Peripheral App
  : ULP (Ultra Low Power) Peripherals - ulp_gpio, ulp_i2c, ulp_i2s, ulp_ir_decoder, ulp_spi, ulp_timer, ulp_uart, ulp_udma
  : UART and I2C Deepsleep Wakeup Without RAM Retention
- **Multiple Ultra Low Power Modes** : Wi-Fi 6 TWT (Target Wake Time) - for improved network efficiency and device battery life
- **Wi-Fi** : 2.4GHz Wi-Fi Support - WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and latency
- **Cloud** : Amazon Cloud Connectivity Support, Amazon FreeRTOS
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack, BLE Stack and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client
- **IDE** : Simplicity Studio with Windows 10(64-bit)
- **TA/M4 Firmware Update Tool** : Simplicity Commander
- **Hardware kits to evaluate SoC Mode** : Si917-BRD4325B (Dual flash Radio board)

## Release Details

| Item                      | Details                                                        |
| ------------------------- | -------------------------------------------------------------- |
| Release date              | April 17th, 2023                                               |
| API Version               | 1.0.1(Build 1)                                                 |
| Firmware Version          | 1711.1.0.0.0.29                                                |
| Package Name              | WiSeConnect3_SDK_IR_1.0.1                                      |
| Supported RTOS            | FreeRTOS                                                       |
| Operating Modes Supported | Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx) |

## Updating to this Release

This release consists of Wireless Library - The Library runs on internal Cortex M4 in SoC Mode and supports 27 sample examples.

## Features and Bug Fixes

- Implemented TLS APIs.
- Added Four Applications(wlan_station_ble_provisioning_aws, wlan_station_ble_provisioning, aws_device_shadow, wifi6_mqtt_twt)
- Enhancement of example readme files.
- Added additional host error codes.
- Zero build Warnings.
- Documentation support for sl_wifi_device.h.​
- MQTT Bug Fix (MQTT event handler isn't receiving failure event).
- Added support to switch M4 frequency for throughput and wifi6-mimo examples.
- Prepared repo for SDK.

## Known Issues

### SoC

- No support for floating point print in Simplicity Studio IDE.
- The "Browser File Viewer" plugin has issues. It can't render the last image included in the markdown files and observed issues accessing some hyperlinks
- In SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations

### Network Stack

- IPv6 support is not available in this release.

### Wi-Fi

- WPA3 connection takes 2.5 sec more than WPA2 connection
- Issue observed with WPA2 Enterprise Connectivity using Microsoft RADIUS Server.

### BLE

- For BLE, dual role scenario issues might occur when connecting as central if the advertising is also going out for the peripheral role. Central connections can be made after the peripheral connections are established and advertising is stopped.
- LMP timeout BLE disconnection observed with the latest Realme mobile handsets.
- BLE Powersave + RTOS is not supported in SoC Mode.

## Limitations and Unsupported Features

### Wi-Fi/Network Stack

- Maximum of 3 SSL connections are supported in WiFi alone mode.
- TWT is not verified in Coex mode.
- BGscan is not verified with TWT Feature.
- No support for DTIM skip feature in power save.

### BLE

- For BLE, if the connection is established with a small connection interval (less than 15 ms), simultaneous roles (i.e., Central + Scanning and Peripheral + Advertising) are not supported.
- BLE maximum two concurrent connections are supported, which can be either a connection to two peripheral devices, to one central and one peripheral device or two central devices.
- BLE Slave latency value is valid up to 32 only.

### SoC

- RTOS support is not available for MCU peripheral drivers. Application-level RTOS support exists.

## Terminology

| Term                            | Description                                                                                                                                                                                                    |
| ------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **New Features**                | These items are new to this release                                                                                                                                                                            |
| **Changes/Issues Fixed**        | Changes made to existing features found in previous software releases.                                                                                                                                         |
|                                 | Enhancements to existing product flow and feature set.                                                                                                                                                         |
|                                 | Bug fixes done in the Release                                                                                                                                                                                  |
| **Deprecated Items**            | Features or functions or APIs that are removed from the distributed release to align with the software roadmap                                                                                                 |
| **Known Issues**                | Features or functions that do not work as planned at the time of release. Workarounds may be offered to meet short-term development goals, but longer-term solutions will be added in future software releases |
| **Limitations/Recommendations** | Describes the limitations on product usage and recommendations for optimal use cases                                                                                                                           |

<br />

## Notes

# WiSeConnect3_SDK_IR_1.0.0 Release Notes

This SDK package supports SoC Mode

- In SoC Mode: Customer Applications can run on Cortex M4. Wireless stacks and Networking stacks run on the Wireless subsystem.
- Silicon Labs' SiWx917 includes an ultra-low power Wi-Fi 6 plus Bluetooth Low Energy (BLE) 5.1 wireless subsystem and an integrated micro-controller application subsystem.

> Note: Release supports only Simplicity Studio 5.5 & above versions

## SoC Highlights

- **Operating Modes** : Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE(CoEx),
- **Wireless Protocols** : IEEE 802.11b, 802.11g, 802.11n , 802.11ax, BLE 5.1
- **MCU Peripherals** : ADC Static Mode, Analog Comparator, Blinky, Bod, CTS, DAC FIFO, DAC Static, OPAMP, GPIO, I2C, I2S, PWM, RTC, QEI, SPI, UART, USART, UDMA, WDT, Combined Peripheral App
  : ULP (Ultra Low Power) Peripherals - ulp_gpio, ulp_i2c, ulp_i2s, ulp_ir_decoder, ulp_spi, ulp_timer, ulp_uart, ulp_udma
  : UART and I2C Deepsleep Wakeup Without RAM Retention
- **Multiple Ultra Low Power Modes** : Wi-Fi 6 TWT (Target Wake Time) - for improved network efficiency and device battery life
- **Wi-Fi** : 2.4GHz Wi-Fi Support - WPA2/WPA3 Personal, Wi-Fi 6 OFDMA/MU-MIMO Support that enhances network capacity and latency
- **Cloud** : Amazon Cloud Connectivity Support, Amazon FreeRTOS
- **BLE** : BLE 5.1, BLE dual role (Central and Peripheral Support)
- **Integrated Stacks and Profiles** : Wi-Fi Stack, BLE Stack and Profiles, TCP/IP stack with TLS 1.3, HTTP/HTTPS, DHCP, MQTT Client
- **IDE** : Simplicity Studio with Windows 10(64-bit)
- **TA/M4 Firmware Update Tool** : Simplicity Commander
- **Hardware kits to evaluate SoC Mode** : Si917-BRD4325B (Dual flash Radio board)

## Release Details

| Item                      | Details                                                  |
| ------------------------- | -------------------------------------------------------- |
| Release date              | April 3rd, 2023                                          |
| API Version               | 1.0.0(Build 1)                                           |
| Firmware Version          | 1711.1.0.0.0.26                                          |
| Package Name              | WiSeConnect3_SDK_IR_1.0.0                                |
| Supported RTOS            | FreeRTOS                                                 |
| Operating Modes Supported | Wi-Fi STA, Wi-Fi AP, Concurrent(AP + STA), Wi-Fi STA+BLE |

## Updating to this Release

This release consists of Wireless Library - The Library runs on internal Cortex M4 in SoC Mode and supports 23 sample examples.

## Features

- Platform agnostic Wifi, Network APIs.
- FreeRTOS support
- Multi-threaded application development support
- AWS MQTT library support
- BSD and IOT socket application programming interface (API)
- WPA2/WPA3 Personal Support for Station Mode and Enterprise security Support for station Mode.
- Network Application protocol support for
  Offloaded mode(TCP/IP internal stack) with HTTP/HTTPS, DHCP, MQTT Client, DNS Client.
- TA Power save support and Max PSP, Fast PSP, 11ax TWT profiles are supported
- 11ax and TWT support
- Bluetooth Low Energy(BLE) central & peripheral connections are supported
- Wireless firmware upgradation.

## Known Issues

### SoC

- No support for floating point print in Simplicity Studio IDE.
- The "Browser File Viewer" plugin has issues. It can't render the last image included in the markdown files and observed issues accessing some hyperlinks
- In SoC mode, M4 power save will work with 384k TA and 320 M4 memory configuration only. It is not supported for "448K TA and 256k M4" and "512k TA and 192k M4" memory configurations

### Network Stack

- IPv6 support is not available in this release.

### Wi-Fi

- WPA3 connection takes 2.5 sec more than WPA2 connection
- Issue observed with WPA2 Enterprise Connectivity using Microsoft RADIUS Server.

### BLE

- For BLE, dual role scenario issues might occur when connecting as central if the advertising is also going out for the peripheral role. Central connections can be made after the peripheral connections are established and advertising is stopped.
- LMP timeout BLE disconnection observed with the latest Realme mobile handsets.
- BLE Powersave + RTOS is not supported in SoC Mode.

## Limitations and Unsupported Features

### Wi-Fi/Network Stack

- Maximum of 3 SSL connections are supported in WiFi alone mode.
- TWT is not verified in Coex mode.
- BGscan is not verified with TWT Feature.
- No support for DTIM skip feature in power save.

### BLE

- For BLE, if the connection is established with a small connection interval (less than 15 ms), simultaneous roles (i.e., Central + Scanning and Peripheral + Advertising) are not supported.
- BLE maximum two concurrent connections are supported, which can be either a connection to two peripheral devices, to one central and one peripheral device or two central devices.
- BLE Slave latency value is valid up to 32 only.

### SoC

- RTOS support is not available for MCU peripheral drivers. Application-level RTOS support exists.

## Terminology

| Term                            | Description                                                                                                                                                                                                    |
| ------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **New Features**                | These items are new to this release                                                                                                                                                                            |
| **Changes/Issues Fixed**        | Changes made to existing features found in previous software releases.                                                                                                                                         |
|                                 | Enhancements to existing product flow and feature set.                                                                                                                                                         |
|                                 | Bug fixes done in the Release                                                                                                                                                                                  |
| **Deprecated Items**            | Features or functions or APIs that are removed from the distributed release to align with the software roadmap                                                                                                 |
| **Known Issues**                | Features or functions that do not work as planned at the time of release. Workarounds may be offered to meet short-term development goals, but longer-term solutions will be added in future software releases |
| **Limitations/Recommendations** | Describes the limitations on product usage and recommendations for optimal use cases                                                                                                                           |

<br />

## Notes
