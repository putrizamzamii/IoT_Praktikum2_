#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <DHT.h>

#define SCREEN_WIDTH 128 // OLED width, in pixels
#define SCREEN_HEIGHT 64 // OLED height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// DHT22 setup
#define DHTPIN 15      // Pin where DHT22 is connected
#define DHTTYPE DHT22  // DHT 22 (AM2302)
DHT dht(DHTPIN, DHTTYPE);

// LDR setup
#define LDR_PIN 12     // Analog pin for LDR (AO pin)

void setup() {
  // Initialize the serial monitor
  Serial.begin(115200);

  // Initialize the DHT22 sensor
  dht.begin();

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Clear the display buffer
  display.clearDisplay();
  
  // Set text size and color
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  // Read temperature and humidity from DHT22
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read light intensity from LDR
  int lightValue = analogRead(LDR_PIN);
  
  // Convert LDR value to a percentage (optional, for display)
  float lightPercentage = map(lightValue, 0, 4095, 0, 100);

  // Check if any reading failed, and exit early (to try again).
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Print the values to the serial monitor (optional)
  Serial.print(F("Temperature: "));
  Serial.print(temperature);
  Serial.print(F(" °C  Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Light Intensity: "));
  Serial.print(lightPercentage);
  Serial.println(F("%"));

  // Display the values on OLED
  display.clearDisplay();  // Clear the display buffer

  display.setCursor(0, 0); // Set the cursor to (0,0)
  display.print(F("Temp: "));
  display.print(temperature);
  display.println(F(" C"));

  display.print(F("Humidity: "));
  display.print(humidity);
  display.println(F(" %"));

  display.print(F("Light: "));
  display.print(lightPercentage);
  display.println(F(" %"));

  display.display();  // Send the buffer to the display

  delay(2000);  // Wait for 2 seconds before the next reading
}
