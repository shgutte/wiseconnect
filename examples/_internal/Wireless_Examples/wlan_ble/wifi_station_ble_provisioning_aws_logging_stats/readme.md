## WLAN Station BLE Provisioning with AWS cloud example

**Protocol Overview**

MQTT is a publish-subscribe based "light weight" messaging protocol for using on top of the TCP/IP protocol. The MQTT connection itself is always between one client and the broker, no client is connected to another client directly.

**MQTT client**

A MQTT client is any device from a micro controller to isa full fledged server, that has a MQTT library running and is connecting to an MQTT broker over any kind of network. MQTT Clients can share the information on a particular topic using MQTT protocol. MQTT clients connect to the MQTT broker using TCP connection and can subscribe and publish on any desired topic. The other clients which are subscribed for that topic will receive the published messages.

**MQTT Broker**

The publish-subscribe messaging pattern requires a message broker. The broker is primarily responsible for receiving all messages, filtering them, deciding like who is interested in it and then sending the message to all subscribed clients.

It also holds the session of all persisted clients including subscriptions and missed messages. Another responsibility of the broker is the authentication and authorization of clients.

**Overview**

This application explains how to get the WLAN connection functionality using BLE provisioning.

In this application,

- Silicon Labs Module starts advertising and with BLE Provisioning the Access Point details are fetched

- Silicon Labs device is configured as a WiFi station and connects to an Access Point.

**Sequence of Events**

**WLAN Task**

This Application explains user how to:

    • Create Silabs device in Station mode

    • Connect Silabs station to the remote Access point

**BLE Task**

This Application explains user how to:

    • Configure Silabs device in advertise mode