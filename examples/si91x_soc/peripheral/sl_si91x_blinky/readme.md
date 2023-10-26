# BLINKY

## Introduction 
- This application contains an example code to demonstrate the GPIO/LED toggle functionality

## Setting Up 
 - To use this application following Hardware, Software and the Project Setup is required

### Hardware Requirements	
  - Windows PC 
  - Silicon Labs [SiWx917 Radio Board]

![Figure: Introduction](resources/readme/image700a.png)

### Software Requirements
  - Si91x SDK
  - Embedded Development Environment
    - For Silicon Labs Si91x, use the latest version of Simplicity Studio (refer **"Download and Install Simplicity Studio"** section in **getting-started-with-siwx917-soc** guide at **release_package/docs/index.html**)
 
## Project Setup
- **Silicon Labs Si91x** refer **"Download SDKs"**, **"Add SDK to Simplicity Studio"**, **"Connect SiWx917"**, **"Open Example Project in Simplicity Studio"** section in **getting-started-with-siwx917-soc** guide at **release_package/docs/index.html** to work with Si91x and Simplicity Studio

## Loading Application on Simplicity Studio

1. With the product BRD4338A selected, navigate to the example projects by clicking on Example Projects & Demos
   in Simplicity Studio and create blinky example application as shown below.

![Figure: Selecting Example project](resources/readme/image700b.png)

## Configuration and Steps for Execution

- By default, LED0 should blink on WSTK/WPK base board. To use LED1, initial step is to install LED1 instance. Further, the LED1 instance can then be changed in blinky.c file.
- By default, the toggle delay is 500 ms. The delay should have a minimum value of 31.25 ms. Ideally, there is no maximum value limit for the delay. Configure the following parameter in blinky.c file to change the delay.
```C
#define TOOGLE_DELAY_MS 500//  configured for 500 ms delay
```   

## Build 
- Compile the application in Simplicity Studio using build icon 

![Figure: Introduction](resources/readme/image700c.png)

## Device Programming
- To program the device ,refer **"Burn M4 Binary"** section in **getting-started-with-siwx917-soc** guide at **release_package/docs/index.html** to work with Si91x and Simplicity Studio

## Executing the Application
- Sets the board state of LED to on and off for configured blink rate and then device goes to sleep 
 **Note!** LED OFF ,LED ON ,device sleep will be a continous process 

## Expected Results 
- LED0/LED1 should blink on WSTK/WPK base board.
 