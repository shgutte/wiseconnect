# PSA ECDH for SI91X

## Introduction 
- This application contains an example code to demonstrate the PSA ECDH functionality
- This application uses hardware accelerators for key generation and shared secret computation using P256 and P192 ecc curve
- This application uses mbedtls fallback for key generation and shared secret computation for all other ecc curves
- TRNG generation is done using hardware accelerator

## Setting Up 
 - To use this application following Hardware, Software and the Project Setup is required

### Hardware Requirements	
  - Windows PC 
  - Silicon Labs [Si917 Evaluation Kit WSTK + BRD4325A]
 
![Figure: Introduction](resources/readme/image508a.png)

### Software Requirements
  - Si91x SDK
  - Embedded Development Environment
    - For Silicon Labs Si91x, use the latest version of Simplicity Studio (refer **"Download and Install Simplicity Studio"** section in **getting-started-with-siwx917-soc** guide at **release_package/docs/index.html**)
 
## Project Setup
- **Silicon Labs Si91x** refer **"Download SDKs"**, **"Add SDK to Simplicity Studio"**, **"Connect SiWx917"**, **"Open Example Project in Simplicity Studio"** section in **getting-started-with-siwx917-soc** guide at **release_package/docs/index.html** to work with Si91x and Simplicity Studio

## Build 
- Compile the application in Simplicity Studio using build icon 

![Figure: Build run and Debug](resources/readme/image508c.png)

## Device Programming
- To program the device ,refer **"Burn M4 Binary"** section in **getting-started-with-siwx917-soc** guide at **release_package/docs/index.html** to work with Si91x and Simplicity Studio

## Executing the Application
-  Default ecc curve is SEP256R1. 
-  Default key size is 256
-  To change the ecc curve and key size change the corresponding macro in app_process_action(). File - app_process.c

## Key Storage

The following key storages are supported in this example:

* Volatile plain key in RAM

## Expected Results 
- The shared secret generated at the client and server side should match. 
 
## Resources

[AN1311: Integrating Crypto Functionality Using PSA Crypto Compared to Mbed TLS Guide](https://www.silabs.com/documents/public/application-notes/an1311-mbedtls-psa-crypto-porting-guide.pdf)
