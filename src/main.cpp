#include "config.h"
#include "data/data.h"
#include "button/button.h"
#include "sensor/sensor.h"
#include "display/display.h"
#include "menu/menu.h"

unsigned long lastCalculationTime = 0;

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting booting sequence...");

    // Modüllerin başlatılması
    DataClass::getInstance().begin();
    ButtonClass::getInstance().begin();
    SensorClass::getInstance().begin();
    DisplayClass::getInstance().begin();
    MenuClass::getInstance().begin();

    lastCalculationTime = millis();
}

void loop()
{
    // Debug modunda fake veri üretimi
    if (debug)
    {
        SensorClass::getInstance().fakeTrigger();
    }

    // Hız ve Mesafe Hesaplama Periyodu
    if (millis() - lastCalculationTime >= waitUntil)
    {
        SensorClass::getInstance().calculate();
        lastCalculationTime = millis();
    }

    // EEPROM Güncellemesi (Modül içeride akıllı kontrol yapıyor)
    DataClass::getInstance().writeAll();

    // Menü olayları, buton kontrolü ve ekran dinamik çizimleri
    MenuClass::getInstance().update();

    delay(150);
}