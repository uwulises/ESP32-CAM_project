
#include "esp_cam_inia.h"
#include "TMP_102_inia.h"
void setup() {
  // put your setup code here, to run once:
  // Disable brownout detector
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  // Start Serial Monitor
  Serial.begin(115200);


  // Initialize the camera
  Serial.print("Initializing the camera module...");
  configESPCamera();
  Serial.println("Camera OK!");
  // initialize EEPROM with predefined size
  EEPROM.begin(EEPROM_SIZE);

}

void loop() {

  //Init TMP102 I2C
  I2C_TMP102();
  //Temperature lecture
  temp_stamp();

  delay(100);

  Serial.print("Initializing the MicroSD card module... ");
  initMicroSDCard();
  pictureCount = EEPROM.read(0) + 1;

  // Path where new picture will be saved in SD Card
  String path = "/image" + String(pictureCount) + "_" + String(temp_without_dot) + ".jpg";
  Serial.printf("Picture file name: %s\n", path.c_str());

  // Take and Save Photo
  takeNewPhoto(path);
  // Update EEPROM picture number counter
  EEPROM.write(0, pictureCount);
  EEPROM.commit();

  //esp_deep_sleep_start();
  esp_deep_sleep(60000000);

}
