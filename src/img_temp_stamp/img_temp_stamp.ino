
#include "esp_cam_inia.h"
#include "TMP_102_inia.h"
void setup() {
  // put your setup code here, to run once:
  // Disable brownout detector
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  // Start Serial Monitor
  Serial.begin(115200);

  //Init TMP102 I2C
  I2C_TMP102();
  // Initialize the camera
  Serial.print("Initializing the camera module...");
  configESPCamera();
  Serial.println("Camera OK!");
  delay(2000);
  // Initialize the MicroSD
  Serial.print("Initializing the MicroSD card module... ");
  initMicroSDCard();
   // initialize EEPROM with predefined size
  EEPROM.begin(EEPROM_SIZE);
    
}

void loop() {
 
  pictureCount = EEPROM.read(0) + 1;

  //Temperature lecture
  temp_stamp();
  
  // Path where new picture will be saved in SD Card
  String path = "/image" + String(pictureCount) + ".jpg";
  Serial.printf("Picture file name: %s\n", path.c_str());

  // Take and Save Photo
  takeNewPhoto(path);

  // Update EEPROM picture number counter
  EEPROM.write(0, pictureCount);
  EEPROM.commit();

  // Bind Wakeup to GPIO13 going LOW
  //esp_sleep_enable_ext0_wakeup(GPIO_NUM_13, 0);
  
  

  Serial.println("Entering sleep mode");
  delay(1000);

  // Enter deep sleep mode
  esp_deep_sleep_start();
}
