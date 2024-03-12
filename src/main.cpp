#include <ETH.h>
#include <WiFi.h>

/*
 * ETH_CLOCK_GPIO0_IN   - default: external clock from crystal oscillator
 * ETH_CLOCK_GPIO0_OUT  - 50MHz clock from internal APLL output on GPIO0 - possibly an inverter is needed for LAN8720
 * ETH_CLOCK_GPIO16_OUT - 50MHz clock from internal APLL output on GPIO16 - possibly an inverter is needed for LAN8720
 * ETH_CLOCK_GPIO17_OUT - 50MHz clock from internal APLL inverted output on GPIO17 - tested with LAN8720
 */
#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT

// Pin# of the enable signal for the external crystal oscillator (-1 to disable for internal APLL source)
#define ETH_POWER_PIN 16

// Type of the Ethernet PHY (LAN8720 or TLK110)
#define ETH_TYPE ETH_PHY_LAN8720

// I²C-address of Ethernet PHY (0 or 1 for LAN8720, 31 for TLK110)
#define ETH_ADDR 1

// Pin# of the I²C clock signal for the Ethernet PHY
#define ETH_MDC_PIN 23

// Pin# of the I²C IO signal for the Ethernet PHY
#define ETH_MDIO_PIN 18

// MAC address of Device 1
uint8_t mac[] = {0xDE, 0xAD, 0xBE, 0xEE, 0xFE, 0xEE}; // use any MAC

// Select the IP address for Device 1
IPAddress localIP(192, 168, 1, 1); // IP address of Device 1

// Select the subnet mask for Device 1
IPAddress subnet(255, 255, 255, 0); // Subnet mask for Device 1

// Select the port number for communication
uint16_t port = 23; // telnet use port 23

const size_t ETH_bufferSize = 64;
uint8_t ETH_buffer[ETH_bufferSize] = {0};
uint8_t totalBufSize = 0;

WiFiServer server;
void setup()
{
    Serial.begin(115200);

    // Initialize Ethernet and set the MAC address
    ETH.begin(ETH_ADDR, ETH_POWER_PIN, ETH_MDC_PIN, ETH_MDIO_PIN, ETH_TYPE, ETH_CLK_MODE);
    ETH.macAddress(mac);

    // Set the local IP address, subnet mask, and start Ethernet connection
    ETH.config(localIP, IPAddress(), subnet);

    // Start the TCP server
    server.begin(port);
    Serial.print("TCP server started at ");
    Serial.print(localIP);
    Serial.print(":");
    Serial.println(port);
}

void loop()
{
    // Check if there is a connected client waiting to be serviced by the server
    if (server.hasClient())
    {
        WiFiClient client = server.available();
        // New client connected
        Serial.println("Client available");

        while (client.connected())
        {
            // Check if there is data available from the client
            if (client.available())
            {
                // Read the data from the client
                char c = client.read();
                Serial.println(c);
                if (c == '\n')
                {
                    break;
                }
            }
            delay(10);
        }
        Serial.println("");
        // Client disconnected
        Serial.println("Client disconnected");
    }
}