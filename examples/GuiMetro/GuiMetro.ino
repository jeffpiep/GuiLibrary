/***************************************************
  Example showing a list of elements, some enabled, some disabled some touch enabled

  NOTE: screeen rotation is set to 270 degrees. Don't worry, the touchscreen will map
  correctly.

  Uses Adafruit TFT library for the example:
  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

/** NOT FOR USE WITH THE TOUCH SHIELD, ONLY FOR THE BREAKOUT! **/
//
// SPFD5408 libraries for Adafruit
#include <SPFD5408_Adafruit_GFX.h>
#include <SPFD5408_Adafruit_TFTLCD.h>
#include <SPFD5408_TouchScreen.h>
#include <GuiLibrary.h>

// These are the four touchscreen analog pins
#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin


// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 200
#define TS_MINY 120
#define TS_MAXX 905
#define TS_MAXY 830


// The display uses hardware SPI, plus #9 & #10

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Setup the gui model
// needs reference to the tft and the touchscreen
Gui gui(&tft, &ts, 0, 0, tft.height(), tft.width());

// some global references to the menu panels
GuiPanel* panelMenu;
GuiPanel* panelSettings;

#define TILE_HEIGHT  116
#define TILE_WIDTH   156
#define TILE_COLUMN1 160

// This will be called when the button is pressed or released
uint8_t callbackFunction_home(void *a, GuiElement *element, uint8_t event) {
  if (event == GUI_EVENT_RELEASE) {
    Serial.println("Pressed Back");
    panelSettings->visible(false);
    panelMenu->visible(true);
  }
  return 0;
}

// This will be called when the button is pressed or released
uint8_t callbackFunction_settings(void *a, GuiElement *element, uint8_t event) {
  if (event == GUI_EVENT_RELEASE) {
    Serial.println("Pressed Settings");
    panelMenu->visible(false);
    panelSettings->visible(true);
  }
  return 0;
}

uint8_t callbackFunction_menu1(void *a, GuiElement *element, uint8_t event) {
  if (event == GUI_EVENT_RELEASE) {
    Serial.println("Pressed menu 1");
  }
  return 0;
}

void buildPanelMenu() {
  // build a 4 tile of elements
  panelMenu = new GuiPanel(0, 0, 320, 240);
  panelMenu->padding = 0;
  panelMenu->margin = 0;
  
  GuiButton *button = new GuiButton(0, 0, TILE_WIDTH, TILE_HEIGHT, "Settings");
  button->backgroundColour = GuiUtils::getColour(119, 185, 0); // purple
  // hook up the callback function defined above to the button so we can track clicks
  button->connectCallback(callbackFunction_settings);
  button->borderWidth = 0;

  GuiButton *button1 = new GuiButton(TILE_COLUMN1, 0, TILE_WIDTH, TILE_HEIGHT, "Menu 1");
  button1->backgroundColour = GuiUtils::getColour(99, 47, 0); // brown
  button1->connectCallback(callbackFunction_menu1);
  button1->borderWidth = 0;

  
  GuiButton *button2 = new GuiButton(0, TILE_HEIGHT + 4, TILE_WIDTH, TILE_HEIGHT, "Menu 2");
  button2->backgroundColour = GuiUtils::getColour(70,23,180); // blue
//  button2->connectCallback(callbackFunction);
  button2->borderWidth = 0;

  
  GuiButton *button3 = new GuiButton(TILE_COLUMN1, TILE_HEIGHT + 4, (TILE_WIDTH / 2) - 2, (TILE_HEIGHT / 2) - 2, "Exit");
  button3->backgroundColour = GuiUtils::getColour(0, 193, 63); // green
//  button3->connectCallback(callbackFunction);
  button3->borderWidth = 0;

  GuiButton *button4 = new GuiButton(TILE_COLUMN1 + (TILE_WIDTH / 2) + 2, TILE_HEIGHT + 4, (TILE_WIDTH / 2) - 2, (TILE_HEIGHT / 2) - 2, "Exit");
  button4->backgroundColour = GuiUtils::getColour(0, 193, 63); // green
//  button3->connectCallback(callbackFunction);
  button4->borderWidth = 0;
  

  GuiButton *button5 = new GuiButton(TILE_COLUMN1, TILE_HEIGHT + (TILE_HEIGHT / 2) + 6, (TILE_WIDTH / 2) - 2, (TILE_HEIGHT / 2) - 2, "Exit");
  button5->backgroundColour = GuiUtils::getColour(0, 193, 63); // green
//  button3->connectCallback(callbackFunction);
  button5->borderWidth = 0;

  GuiButton *button6 = new GuiButton(TILE_COLUMN1 + (TILE_WIDTH / 2) + 2, TILE_HEIGHT + (TILE_HEIGHT / 2) + 6, (TILE_WIDTH / 2) - 2, (TILE_HEIGHT / 2) - 2, "Exit");
  button6->backgroundColour = GuiUtils::getColour(0, 193, 63); // green
//  button3->connectCallback(callbackFunction);
  button6->borderWidth = 0;


  panelMenu->addChild(button);
  panelMenu->addChild(button1);
  panelMenu->addChild(button2);
  panelMenu->addChild(button3);
  panelMenu->addChild(button4);
  panelMenu->addChild(button5);
  panelMenu->addChild(button6);
  
  // finally add the widgt to the page
  gui.addChild(panelMenu);
}

void buildPanelSettings() {
  // build a new panel and make it the same size as the screen
  // this panel will be hidden
  panelSettings = new GuiPanel(0, 0, 320, 240);
  panelSettings->padding = 0;
  panelSettings->margin = 0;
  
  GuiLabel *label = new GuiLabel(0, 0, TILE_WIDTH, TILE_HEIGHT, "System Status: Mauve");

  GuiButton *button1 = new GuiButton(0, TILE_HEIGHT + 4, TILE_WIDTH, TILE_HEIGHT, "<- Home");
  button1->backgroundColour = GuiUtils::getColour(70,23,180); // blue
  button1->connectCallback(callbackFunction_home);
  button1->borderWidth = 0;

  panelSettings->addChild(label);
  panelSettings->addChild(button1);

  panelSettings->visible(false);
  
  // finally add the widget to the page
  gui.addChild(panelSettings);
}

void setup(void) {
 // while (!Serial);     // used for leonardo debugging

  Serial.begin(9600);
  //delay(1000);
  Serial.println(F("Gui Widgets test!"));
  tft.reset();
  
  tft.begin(0x9341);
  // in multiples of 90 only (duh)
  gui.setRotation(90);
    
  buildPanelMenu();
  buildPanelSettings();

  gui.draw();

  return;  
}


void loop()
{
  // this has to be called to keep the system up to date
  gui.update();

  return;
}