#ifndef PRM_H
#define	PRM_H

#include <arduino.h>
#include "nxfont32.h"

#define ST7789

// Lamp emulation
#define lampX 160  // Lamp position X
#define lampY 140  // Lamp position Y
#define lampD 50  // Spot size(diameter)
#define depth_LE_effect 7.5 // if 0, without Lamp emulation

//#define Digtal_Freq_OFF

/*----------------------------------------------------------
   Dial design
-----------------------------------------------------------*/
#define MAINDIAL_IS_OUTSIDE //Comment out this definition and Sub dial is outsaide

//#define REV_DIAL
//#define REV_ENCODER

//#define MAIN_UNIT_kHz


#define MODE0 // MODE0, MODE1, MODE2


// Dial Number Size ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Font size of numbers
#define font_sizex_main 0.75
#define font_sizey_main 0.70
#define font_sizex_sub  0.90
#define font_sizey_sub  0.70


// Frequency per scale of 1 main dial -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define  freq_tick_main 10000  // Frequency per tick of Main dial: 10000(10kHz) or 100000(100kHz)
#define  freq_tick_sub  1000  // Frequency per tick of Sub  dial: 1000(1kHz) or 10000(10kHz)



// Dial display position-----------------------------------------------------------------------------------------
//Position of dial display
#define center_offset  0
#define top_position  65
#define top_margin    20


// Dial radius ----
#define dial_radius 260.0  // Dial radius (if 10000, Linear scale)


// Spacing between main and subdials---------------------------------------------------------------------------------------
#define dial_space  60.0  // Space bitween Main and Sub dial


// Tick ​​interval----------------------------------
#define tick_pitch_main  10.0  // Tick pitch of main dial
#define tick_pitch_sub   12.0  // Tick pitch of sub dial


// Scale thickness----
#define tw_main1   3.0  // Tick width of main(1)
#define tw_main5   4.0  // Tick width of main(5)
#define tw_main10  4.5  // Tick width of main(10)
#define tw_sub1    3.0  // Tick width of sub(1)
#define tw_sub5    4.0  // Tick width of sub(5)
#define tw_sub10   4.5  // Tick width of sub(10)


// Tick ​​length--------------------------------
#define tl_main1    5.0  // Tick length of main(1)
#define tl_main5   14.0  // Tick length of main(5)
#define tl_main10  18.0  // Tick length of main(10)
#define tl_sub1     5.0  // Tick length of sub(1)
#define tl_sub5    14.0  // Tick length of sub(5)
#define tl_sub10   18.0  // Tick length of sub(10)


// Space between scales and numbers---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define TNCL_main  22.0  // Space bitween Number and Tick (Main dial)
#define TNCL_sub   22.0  // Space bitween Number and Tick (Sub dial)


// Guideline width, length---------------
#define DP_width   1.0  // Needle width
#define DP_len   200.0  // Needle length


#define TickMainCol TFT_CYAN
#define TickSubCol  TFT_GREEN
#define NumMainCol  TFT_WHITE
#define NumSubCol   TFT_GOLD // TFT_ORANGE
#define PointerCol  TFT_RED
#define BGCol       TFT_BLACK // 0x80FF80U
#define DialBGCol   BGCol

#define TFT_BLACK2  0x0020  // opaque black



#include <LovyanGFX.hpp>
class LGFX : public lgfx::LGFX_Device
{
  lgfx::Panel_ST7789  _panel_instance;
  lgfx::Bus_SPI         _bus_instance;

public:
  LGFX(void)
  {
    { // // Configuring the SPI bus
      auto cfg = _bus_instance.config();    // Gets the structure for bus configuration.
      cfg.spi_host = VSPI_HOST;     // Select the SPI to use ESP32-S2,C3: SPI2_HOST or SPI3_HOST / ESP32: VSPI_HOST or HSPI_HOST
      // * Due to the ESP-IDF version upgrade, descriptions of VSPI_HOST and HSPI_HOST will be deprecated, so if an error occurs, use SPI2_HOST and SPI3_HOST instead.
      cfg.spi_mode = 0;             // Set SPI communication mode (0 to 3)
      cfg.freq_write = 27000000;    // SPI clock at transmission (rounded to 80MHz, 80MHz divided by an integer)
      cfg.freq_read  = 16000000;    // SPI clock when receiving
      cfg.spi_3wire  = false;        // Set true if receiving is performed using the MOSI pin.
      cfg.use_lock   = true;        // Set to true if transaction lock is used
      cfg.dma_channel = SPI_DMA_CH_AUTO; // Set the DMA channel to use (0=DMA not used / 1=1ch / 2=ch / SPI_DMA_CH_AUTO=automatically set)
      // * Due to the ESP-IDF version upgrade, SPI_DMA_CH_AUTO (automatic setting) is now recommended for DMA channels. 1ch and 2ch specification is deprecated.
      cfg.pin_sclk = 18;            // Set SCLK pin number for SPI
      cfg.pin_mosi = 23;            // Set the MOSI pin number for SPI
      cfg.pin_miso = -1;            // Set the MISO pin number for SPI (-1 = disable)
      cfg.pin_dc   = 2;            // Set the D/C pin number for SPI (-1 = disable)
      _bus_instance.config(cfg);    // The setting value is reflected on the bus.
      _panel_instance.setBus(&_bus_instance);      // Place the bus on the panel.
    }

    { // Sets the display panel control.
      auto cfg = _panel_instance.config();    // Gets the structure for display panel settings.
      cfg.pin_cs           =    5;  // Pin number to which CS is connected (-1 = disable)
      cfg.pin_rst          =    15;  // Pin number to which RST is connected (-1 = disable)
      cfg.pin_busy         =    -1;  // Pin number to which BUSY is connected (-1 = disable)

      // *The following settings have a general initial value set for each panel, so please comment out any unknown items and try it out.

      cfg.panel_width      =   240;  // Actual displayable width
      cfg.panel_height     =   320;  // The actual height that can be displayed
      cfg.offset_x         =     0;  // X-direction offset amount of panel
      cfg.offset_y         =     0;  // Panel Y-direction offset amount
      cfg.offset_rotation  =     1;  // Offset of the value in the direction of rotation: 0~7 (4~7 inverts up and down)
      cfg.dummy_read_pixel =     8;  // Number of bits in dummy read before pixel read
      cfg.dummy_read_bits  =     1;  // Number of bits in dummy read before reading data other than pixels
      cfg.readable         = false;  // Set to true if data read is possible
      cfg.invert           =  true;  // Set to true if the panel light and darkness are reversed
      cfg.rgb_order        = false;  // Set to true if the red and blue panels are swapped
      cfg.dlen_16bit       = false;  // For panels that send data lengths in 16-bit parallel or SPI, set to true, false: 8-bit
      cfg.bus_shared       = false;  // If the bus is shared with the SD card, set to true (bus control is performed using drawJpgFile, etc.)

      // Please set the following only if the display is shifted by a driver with variable pixel counts, such as ST7735 or ILI9163.
      // cfg.memory_width = 128; // Maximum width supported by driver IC
      // cfg.memory_height = 160; // Maximum height supported by driver IC

      _panel_instance.config(cfg);
    }   
    setPanel(&_panel_instance); // Set the panel you want to use.
  }
};

#endif