# Glucose

## 1. Purpose / Scope

This application demonstrates how to configure GATT server in BLE peripheral mode and GATT client in BLE central mode .
Glucose Service GATT server configures with Glucose service with notification characteristic UUID. 

## 2. Prerequisites / Setup Requirements

Before running the application, the user will need the following things to setup.

### 2.1 Hardware Requirements

- Windows PC.
- SiWx91x Wi-Fi Evaluation Kit. The SiWx91x supports multiple operating modes. See [Operating Modes]() for details.
- **SoC Mode**:
      - Silicon Labs [BRD4325A, BRD4325B, BRD4325C, BRD4325G, BRD4338A](https://www.silabs.com/)
- **NCP Mode**:
      - Silicon Labs [BRD4180B](https://www.silabs.com/); **AND**
      - Host MCU Eval Kit. This example has been tested with:
      - Silicon Labs [WSTK + EFR32MG21](https://www.silabs.com/development-tools/wireless/efr32xg21-bluetooth-starter-kit)
- BLE peripheral device

#### SoC Mode

![Figure: Setup Diagram SoC Mode for Glucose Example](resources/readme/glucosesoc.png)
  
#### NCP Mode

![Figure: Setup Diagram NCP Mode for Glucose Example](resources/readme/glucosencp.png) 

Follow the [Getting Started with Wiseconnect3 SDK](https://docs.silabs.com/wiseconnect/latest/wiseconnect-getting-started/) guide to set up the hardware connections and Simplicity Studio IDE.

### 2.2 Software Requirements

- [WiSeConnect SDK](https://github.com/SiliconLabs/wiseconnect-wifi-bt-sdk/)

- Embedded Development Environment

      - For STM32, use licensed [Keil IDE](https://www.keil.com/demo/eval/arm.htm)

      - For Silicon Labs EFx32, use the latest version of [Simplicity Studio](https://www.silabs.com/developers/simplicity-studio)

- Download and install the Silicon Labs [EFR Connect App](https://www.silabs.com/developers/efr-connect-mobile-app) in the android smart phones for testing BLE applications. Users can also use their choice of BLE apps available in Android/iOS smart phones.

## 3. Project Environment

### 3.1 Project Creation

#### 3.1.1 SoC Mode

1. Ensure the SiWx91x setup is connected to your PC.

- In the Simplicity Studio IDE, the SiWx91x SoC board will be detected under **Debug Adapters** pane as shown below.

   ![Soc Board detection](resources/readme/socboarddetection111.png)

- Studio should detect your board. Your board will be shown here. Click on the board detected and go to **EXAMPLE PROJECTS & DEMOS** section.  

- Filter for Bluetooth examples from the Gecko SDK added. For this, check the *Bluetooth* checkbox under **Wireless Technology** and select *BLE - Glucose* application.

   ![project_selection](resources/readme/create_project1.png)

- Click 'Create'. The "New Project Wizard" window appears. Click 'Finish'

  ![creation_final](resources/readme/create_project2.png)

#### 3.1.2 NCP Mode

1. Ensure the EFx32 and SiWx91x setup is connected to your PC.

- In the Simplicity Studio IDE, the EFR32 board will be detected under **Debug Adapters** pane as shown below.

   ![EFR32 Board detection](resources/readme/efr32.png)

- Ensure the latest Gecko SDK along with the WiSeConnect 3 extension is added to Simplicity Studio.

- Go to the 'EXAMPLE PROJECT & DEMOS' tab and select *BLE - Glucose* application.

- Click 'Create'. The "New Project Wizard" window appears. Click 'Finish'.

  ![creation_final](resources/readme/create_project2.png)
  
### 3.2 Setup for Application Prints

#### 3.2.1 SoC Mode

  You can use either of the below USB to UART converters for application prints.

1. Setup using USB to UART converter board.

   - Connect Tx (Pin-6) to P27 on WSTK
   - Connect GND (Pin 8 or 10) to GND on WSTK

      **![FTDI_prints](resources/readme/usb_to_uart_1.png)**

2. Setup using USB to UART converter cable.

   - Connect RX (Pin 5) of TTL convertor to P27 on WSTK
   - Connect GND (Pin1) of TTL convertor to GND on WSTK

      **![FTDI_prints](resources/readme/usb_to_uart_2.png)**

**Tera Term setup - for NCP and SoC modes**

1. Open the Tera Term tool.

   - For SoC mode, choose the serial port to which USB to UART converter is connected and click on **OK**.

   **![UART - SoC](resources/readme/port_selection_soc.png)**

   - For NCP mode, choose the J-Link port and click on **OK**.

   **![J-link - NCP](resources/readme/port_selection.png)**

2. Navigate to the Setup → Serial port and update the baud rate to **115200** and click on **OK**.

  **![Serial port](resources/readme/serial_port_setup.png)**

  **![Baud rate](resources/readme/serial_port.png)**

## 4. Application Configuration Parameters

The application can be configured to suit your requirements and development environment. Read through the following sections and make any changes needed.

**4.1** Open `app.c` file

**4.1.1** User must update the below parameters

`RSI_BLE_GLUCOSE_SERVICE_UUID` refers to the attribute value of the newly created service.

         #define RSI_BLE_GLUCOSE_SERVICE_UUID                     0x1808

`RSI_BLE_GLUCOSE_MEASUREMENT_UUID` refers to the attribute type of the first attribute under this above primary service.

`RSI_BLE_GLUCOSE_MEASUREMENT_CONTEXT_UUID` refers to the attribute type of the second attribute under this above primary service.

`RSI_BLE_GLUCOSE_FEATURE_UUID` refers to the attribute type of the third attribute under this above primary service.

`RSI_BLE_RECORD_ACCESS_CONTROL_POINT_UUID` refers to the attribute type of the fourth attribute under this above primary service.

         #define  RSI_BLE_GLUCOSE_MEASUREMENT_UUID                 0x2A18
         #define  RSI_BLE_GLUCOSE_MEASUREMENT_CONTEXT_UUID         0x2A34
         #define  RSI_BLE_GLUCOSE_FEATURE_UUID                     0x2A51
         #define  RSI_BLE_RECORD_ACCESS_CONTROL_POINT_UUID         0x2A52

`RSI_BLE_APP_GLUCOSE` refers name of the Silicon Labs device to appear during scanning by remote devices.

         #define RSI_BLE_APP_GLUCOSE                              "GLS"

`GATT_ROLE` refers the role of the Silicon Labs module to be selected.
If user configure `SERVER`, Silicon Labs module will act as GATT SERVER, means will add Glucose service profile.
If user configure `CLIENT`, Silicon Labs module will act as GATT CLIENT, means will connect to remote GATT server and get services.

         #define GATT_ROLE                                         SERVER

If user configure CLIENT role following macros should be configured.
`RSI_BLE_DEV_ADDR_TYPE` refers address type of the remote device to connect.

         #define RSI_BLE_DEV_ADDR_TYPE                             LE_PUBLIC_ADDRESS

Valid configurations are

         LE_RANDOM_ADDRESS
         LE_PUBLIC_ADDRESS

`RSI_BLE_DEV_ADDR` refers address of the remote device to connect.

         #define RSI_BLE_DEV_ADDR                                  "00:1A:7D:DA:71:13" 

`RSI_REMOTE_DEVICE_NAME` refers the name of remote device to which Silicon Labs device has to connect

         #define RSI_REMOTE_DEVICE_NAME                           "BLE_REMOTE_GLS_DEV"

**Note:**
User can configure either RSI_BLE_DEV_ADDR or RSI_REMOTE_DEVICE_NAME of the remote device.

Following are the non configurable macros related to attribute properties.

         #define  RSI_BLE_ATT_PROPERTY_READ                        0x02
         #define  RSI_BLE_ATT_PROPERTY_WRITE                       0x08
         #define  RSI_BLE_ATT_PROPERTY_WRITE_WITHOUT_RESP          0x04
         #define  RSI_BLE_ATT_PROPERTY_NOTIFY                      0x10
         #define  RSI_BLE_ATT_PROPERTY_INDICATE                    0x20

**4.1.2** Following are the non-configurable macros in the application.

`RSI_BLE_CHAR_SERV_UUID` refers to the attribute type of the characteristics to be added in a service.
`RSI_BLE_CLIENT_CHAR_UUID` refers to the attribute type of the client characteristics descriptor to be added in a service.

         #define RSI_BLE_CHAR_SERV_UUID                            0x2803
         #define RSI_BLE_CLIENT_CHAR_UUID                          0x2902

`BT_GLOBAL_BUFF_LEN` refers Number of bytes required by the application and the driver
         #define BT_GLOBAL_BUFF_LEN                                15000

**4.2** Open ble_config.h file and update/modify following macros,

         #define RSI_BLE_PWR_INX                                  30 
         #define RSI_BLE_PWR_SAVE_OPTIONS                         BLE_DISABLE_DUTY_CYCLING 

**Note:** `ble_config.h` files are already set with desired configuration in respective example folders user need not change for each example.

## 5. Build and Test the Application

- Follow the below steps for the successful execution of the application.

### 5.1 Build the Application

#### SoC Mode

- Once the project is created, click on the build icon (hammer) to build the project (or) right click on project and click on Build Project.

   ![build_project](resources/readme/build_example.png)

#### NCP Mode

   ![build_project](resources/readme/build_example.png)

### 5.2 Loading the Application Image

1. Click on Tools and Simplicity Commander as shown below.

   ![](resources/readme/load_image1.png)

2. Load the firmware image
   - Select the board.
   - Browse the application image (.hex) and click on Flash button.

   ![](resources/readme/load_image2.png)

### 5.3 Common Steps

**Server role**

1. After the program gets executed, Silicon Labs module will be in Advertising state.
2. Open a nRFConnect App and do the scan.
3. In the App, Silicon Labs module will appear with the name configured in the macro `RSI_BLE_APP_GLUCOSE` (Ex: "GLS") or sometimes observed as Silicon Labs device as internal name "SimpleBLEPeripheral" (See Figure 2)
4. Initiate connection from the App.
5. After successful connection, nRFConnect displays the supported services of Silicon Labs module.
6. Select the attribute service which is added `RSI_BLE_GLUCOSE_SERVICE_UUID` (Ex: 0x1808).
7. Enable Notify for the characteristic `RSI_BLE_GLUCOSE_MEASUREMENT_UUID` (Ex: 0x2A18). So that GATT server Notifies when value updated in that particular attribute.
8. Silicon Labs module send the Battery Service battery level data to the attribute `RSI_BLE_GLUCOSE_MEASUREMENT_UUID` (Ex: 0x2A18) of the remote device and will Notifies the GATT client (remote device).
9. `RSI_BLE_GLUCOSE_FEATURE_UUID` will describe the value by its fields as shown in fig.

![Scanning for GLS device & connecting to it](resources/readme/image41.png)

![GLS and its characteristic discovery](resources/readme/image42.png)

![Client Characteristic Configuration (Indication disable)](resources/readme/image43.png)

![Glucose measurement value (Indication enable)](resources/readme/image44.png)

![Get records using control point characteristic](resources/readme/image45.png)

![](resources/readme/output_1.png)
