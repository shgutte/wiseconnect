# Battery Service

## 1. Purpose / Scope

This application demonstrates how to configure Battery Service GATT server with Battery service along with notification characteristic UUID.

## 2. Prerequisites / Setup Requirements

Before running the application, the user will need the following things to setup.

## 2.1 Hardware Requirements

- Windows PC
- **SoC Mode**:
  - Silicon Labs [BRD4325A, BRD4325B, BRD4325C, BRD4325G, BRD4338A](https://www.silabs.com/)
- **NCP Mode**:
  - Silicon Labs [BRD4180B](https://www.silabs.com/) **AND**
  - Host MCU Eval Kit. This example has been tested with:
    - Silicon Labs [WSTK + EFR32MG21](https://www.silabs.com/development-tools/wireless/efr32xg21-bluetooth-starter-kit)

### 2.2 Software Requirements

- Embedded Development Environment

  - For Silicon Labs EFx32, use the latest version of [Simplicity Studio](https://www.silabs.com/developers/simplicity-studio)- Download and install the Silicon Labs [EFR Connect App](https://www.silabs.com/developers/efr-connect-mobile-app) in the android smart phones for testing BLE applications. Users can also use their choice of BLE apps available in Android/iOS smart phones.

### 2.3 Setup Diagram

#### SoC Mode

![Figure: Setup Diagram SoC Mode for Battery Service Example](resources/readme/batteryservicesoc.png)
  
#### NCP Mode  

![Figure: Setup Diagram NCP Mode for Battery Service Example](resources/readme/batteryservicencp.png)

Follow the [Getting Started with Wiseconnect3 SDK](https://docs.silabs.com/wiseconnect/latest/wiseconnect-getting-started/) guide to set up the hardware connections and Simplicity Studio IDE.

## 3 Project Environment

- Ensure the SiWx91x loaded with the latest firmware following the [Upgrade Si91x firmware](https://docs.silabs.com/wiseconnect/latest/wiseconnect-getting-started/getting-started-with-soc-mode#upgrade-si-wx91x-connectivity-firmware)

### 3.1 Creating the Project

#### 3.1.1 SoC Mode

- In the Simplicity Studio IDE, the SiWx91x SoC board will be detected under **Debug Adapters** pane as shown below.

  ![Soc Board detection](resources/readme/soc_board_detection.png)

- Studio should detect your board. Your board will be shown here. Click on the board detected and go to **EXAMPLE PROJECTS & DEMOS** section.  

- Filter for Bluetooth examples from the Gecko SDK added. For this, check the *Bluetooth* checkbox under **Wireless Technology** and select *BLE - Dual Role* application.

   ![project_selection](resources/readme/create_project1.png)

- Click 'Create'. The "New Project Wizard" window appears. Click 'Finish'

  ![creation_final](resources/readme/create_project2.png)

#### 3.1.2 NCP Mode

- In the Simplicity Studio IDE, the EFR32 board will be detected under **Debug Adapters** pane as shown below.

   ![](resources/readme/efr32.png)

- Ensure the latest Gecko SDK along with the WiSeConnect 3 extension is added to Simplicity Studio.

- Go to the 'EXAMPLE PROJECT & DEMOS' tab and select *BLE - Dual Role* application.

- Click 'Create'. The "New Project Wizard" window appears. Click 'Finish'.

  ![](resources/readme/create_project2.png)

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

`RSI_BLE_BATTERY_SERVICE_UUID` refers to the attribute value of the newly created service.

         #define RSI_BLE_BATTERY_SERVICE_UUID                      0x180F

`RSI RSI_BLE_BATTERY_LEVEL_UUID` refers to the attribute type of the first attribute under this above primary service.

         #define RSI RSI_BLE_BATTERY_LEVEL_UUID                        0x2A19

`RSI_BLE_MAX_DATA_LEN` refers to the Maximum length of the attribute data.
open ble_config.h file to modify this this parameter.

         #define RSI_BLE_MAX_DATA_LEN                              1

`BLE_BATTERY_SERVICE` refers name of the Silicon Labs device to appear during scanning by remote devices.

         #define RSI_LOCAL_DEVICE_NAME                             "BATTERY_SERVICE"

`GATT_ROLE` refers the role of the Silicon Labs module to be selected.
If user configure `SERVER`, Silicon Labs module will act as GATT SERVER, means will add battery service profile.
If user configure `CLIENT`, Silicon Labs module will act as GATT CLIENT, means will connect to remote GATT server and get services.

         #define GATT_ROLE                                         "SERVER"

If user configure CLIENT role following macros should be configured.
`RSI_BLE_DEV_ADDR_TYPE` refers address type of the remote device to connect.

         #define RSI_BLE_DEV_ADDR_TYPE                             LE_PUBLIC_ADDRESS

Valid configurations are

         LE_RANDOM_ADDRESS
         LE_PUBLIC_ADDRESS

**Note:**
Depends on the remote device, address type will be changed.

`RSI_BLE_DEV_ADDR` refers address of the remote device to connect.
         #define RSI_BLE_DEV_ADDR                                  "00:1A:7D:DA:71:13"

`RSI_REMOTE_DEVICE_NAME` refers the name of remote device to which Silicon Labs device has to connect

         #define RSI_REMOTE_DEVICE_NAME                            "REDPINE_DEV"

**Note:**
Silicon Labs module can connect to remote device by referring either `RSI_BLE_DEV_ADDR` or `RSI_REMOTE_DEVICE_NAME` of the remote device.

Following Characteristic Presentation Format fields

         #define RSI_BLE_UINT8_FORMAT                              0x04
         #define RSI_BLE_EXPONENT                                  0x00
         #define RSI_BLE_PERCENTAGE_UNITS_UUID                     0x27AD
         #define RSI_BLE_NAME_SPACE                                0x01
         #define RSI_BLE_DESCRIPTION                               0x010B

**4.1.2** Following are the non configurable macros related to client characteristic configuration.

         #define RSI_BLE_NOTIFY_VALUE                              0x01 
         #define RSI_BLE_INDICATE_VALUE                            0x02

Following are the non-configurable macros in the application.

`RSI_BLE_CHAR_SERV_UUID` refers to the attribute type of the characteristics to be added in a service.

         #define RSI_BLE_CHAR_SERV_UUID                            0x2803

`RSI_BLE_CLIENT_CHAR_UUID` refers to the attribute type of the client characteristics descriptor to be added in a service.

         #define RSI_BLE_CLIENT_CHAR_UUID                          0x2902

`RSI_BLE_CHAR_PRESENTATION_FORMATE_UUID` refers to the attribute type of the characteristic presentation format descriptor to be added in a service.

         #define RSI_BLE_CHAR_PRESENTATION_FORMATE_UUID            0x2904

Following are the Macros for the GATT properties

         #define  RSI_BLE_ATT_PROPERTY_READ                         0x02
         #define  RSI_BLE_ATT_PROPERTY_WRITE                        0x08
         #define  RSI_BLE_ATT_PROPERTY_NOTIFY                       0x10

`BT_GLOBAL_BUFF_LEN` refers Number of bytes required by the application and the driver

         #define BT_GLOBAL_BUFF_LEN                                15000

2. Open ble_config.h file and update/modify following macros,

         #define RSI_FEATURE_BIT_MAP                               (FEAT_ULP_GPIO_BASED_HANDSHAKE |FEATT_DEV_TO_HOST_ULP_GPIO_1)
         #define RSI_TCP_IP_BYPASS                                 RSI_DISABLE 
         #define RSI_TCP_IP_FEATURE_BIT_MAP                        TCP_IP_FEAT_DHCPV4_CLIENT 
         #define RSI_CUSTOM_FEATURE_BIT_MAP                        FEAT_CUSTOM_FEAT_EXTENTION_VALID
         #define RSI_EXT_CUSTOM_FEATURE_BIT_MAP                    (EXT_FEAT_LOW_POWER_MODE | EXT_FEAT_XTAL_CLK_ENABLE | EXT_FEAT_384K_MODE)

         #define RSI_BLE_PWR_INX                                   30 
         #define RSI_BLE_PWR_SAVE_OPTIONS                          BLE_DISABLE_DUTY_CYCLING 

**Note:**
 ble_config.h file is already set with desired configuration in respective example folders user need not change for each example.

## 5. Build and Test the Application

- Follow the below steps for the successful execution of the application.

### 5.1 Build the Application

- Follow the below steps for the successful execution of the application.

#### SoC Mode

- Once the project is created, click on the build icon (hammer) to build the project (or) right click on project and click on Build Project.

   ![build_project](resources/readme/build_example.png)

- Successful build output will show as below.

#### NCP Mode

   ![build_project](resources/readme/build_example.png)

- Successful build output will show as below.

### 5.2 Loading the Application Image

1. Click on Tools and Simplicity Commander as shown below.

   ![](resources/readme/load_image1.png)

2. Load the firmware image

- Select the board.
- Browse the application image (.hex) and click on Flash button.

   ![](resources/readme/load_image2.png)

### 5.3 Common Steps

**5.3.1** Server role

1. After the program gets executed, Silicon Labs module will be in Advertising state.
2. Open a nRFConnect App and do the scan.
3. In the App, Silicon Labs module will appear with the name configured in the macro RSI_BLE_APP_SIMPLE_CHAT (Ex: "BLE_BATTERY_SERVICE") or sometimes observed as Silicon Labs device as internal name "SimpleBLEPeripheral".
4. Initiate connection from the App.
5. After successful connection, nRFConnect displays the supported services of Silicon Labs module.
6. Select the attribute service which is added RSI_BLE_BATTERY_SERVICE_UUID
(Ex: 0x180F).
7. Enable Notify for the characteristic RSI_BLE_BATTERY_LEVEL_UUID
(Ex: 0x2A19). So that GATT server Notifies when value updated in that particular attribute.
8. Silicon Labs module send the Battery Service battery level data to the attribute RSI_BLE_BATTERY_LEVEL_UUID (Ex: 0x2A19) of the remote device and will Notifies the GATT client (remote device).
9. RSI_BLE_CHAR_PRESENTATION_FORMATE_UUID will describe the value by its fields as shown in fig.
10. Please refer the given below image for Notify operation from remote device GATT client.

![Client Characteristic Configuration and Characteristic Presentation Format](resources/readme/image2.png)

**5.3.2** Client role

1. Advertise a LE device which supports Battery Service.
2. After the program gets executed, Silicon Labs module will connect to that remote device based on given BD address or name
3. After successful connection Silicon Labs module will read the services from the remote GATT server.
4. If remote device support notify property Silicon Labs module will enable notify, and ready to receive notifications from remote device.
5. Whenever GATT server changes value and notifies that Silicon Labs module will receive that value.
