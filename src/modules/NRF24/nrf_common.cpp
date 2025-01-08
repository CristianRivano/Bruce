#include "nrf_common.h"
#include "../../core/mykeyboard.h"

RF24 NRFradio(NRF24_CE_PIN, NRF24_SS_PIN);
SPIClass* NRFSPI;

void nrf_info() {
  tft.fillScreen(bruceConfig.bgColor);
  tft.setTextSize(FM);
  tft.setTextColor(TFT_RED, bruceConfig.bgColor);
  tft.drawCentreString("_Descargo de responsabilidad_",tftWidth/2,10,1);
  tft.setTextColor(TFT_WHITE, bruceConfig.bgColor);
  tft.setTextSize(FP);
  tft.setCursor(15,33);
  tft.println("Estas funciones fueron creadas para ser utilizadas en un entorno controlado únicamente para ESTUDIO..");
  tft.println("\nNO uses estas funciones para dañar a personas o empresas, ¡puedes ir a la cárcel!");
  tft.setTextColor(bruceConfig.priColor, bruceConfig.bgColor);
  tft.println("\Este dispositivo es MUY sensible al ruido, por lo que los cables largos o que pasan cerca de la línea VCC pueden hacer que las cosas salgan mal..");
  delay(1000);
  while(!checkAnyKeyPress());
}

bool nrf_start() {
#if defined(USE_NRF24_VIA_SPI)
  pinMode(NRF24_SS_PIN, OUTPUT);
  digitalWrite(NRF24_SS_PIN, HIGH);
  pinMode(NRF24_CE_PIN, OUTPUT);
  digitalWrite(NRF24_CE_PIN, LOW);
  
  #if CC1101_MOSI_PIN==TFT_MOSI // (T_EMBED), CORE2 and others
    NRFSPI = &tft.getSPIinstance();
    NRFSPI->begin(NRF24_SCK_PIN,NRF24_MISO_PIN,NRF24_MOSI_PIN);    
  #elif CC1101_MOSI_PIN==SDCARD_MOSI
    NRFSPI = &sdcardSPI;
    NRFSPI->begin(NRF24_SCK_PIN,NRF24_MISO_PIN,NRF24_MOSI_PIN);
  #elif defined(SMOOCHIEE_BOARD)
    NRFSPI = &CC_NRF_SPI;
    NRFSPI->begin(NRF24_SCK_PIN,NRF24_MISO_PIN,NRF24_MOSI_PIN);
  #else 
    NRFSPI = &SPI;
    NRFSPI->begin(NRF24_SCK_PIN,NRF24_MISO_PIN,NRF24_MOSI_PIN);
  #endif

  if(NRFradio.begin(NRFSPI,rf24_gpio_pin_t(NRF24_CE_PIN),rf24_gpio_pin_t(NRF24_SS_PIN)))
  {
    return true;
  }
  else
  return false;



#else // NRF24 not set in platfrmio.ini
  return false;
#endif
}