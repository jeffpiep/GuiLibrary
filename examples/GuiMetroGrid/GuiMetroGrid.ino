/***************************************************
  Example showing a list of elements, some enabled, some disabled some touch enabled

  NOTE: screeen rotation is set to 270 degrees. Don't worry, the touchscreen will map
  correctly.

  Uses Adafruit TFT library for the example:
  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

/** NOT FOR USE WITH THE TOUCH SHIELD, ONLY FOR THE BREAKOUT! **/

#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>
#include <Adafruit_ILI9341.h>
#include "TouchScreen.h"
#include "GuiLibrary.h"

// These are the four touchscreen analog pins
#define YP A0  // must be an analog pin, use "An" notation!
#define XM A1  // must be an analog pin, use "An" notation!
#define YM 6   // can be a digital pin
#define XP 5   // can be a digital pin


// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940


// The display uses hardware SPI, plus #9 & #10
#define TFT_CS 4
#define TFT_DC 5
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Setup the gui model
// needs reference to the tft and the touchscreen
Gui gui(&tft, &ts, 0, 0, tft.height(), tft.width());

// some global references to the menu panels
GuiGrid* panelMenu;
GuiGrid* panelSettings;

// This will be called when the button is pressed or released
uint8_t callbackFunction_home(void *a, GuiElement *element, uint8_t event) {
  if (event == GUI_EVENT_RELEASE) {
    Serial.println("Pressed Back");
    panelSettings->visible(false);
    panelMenu->visible(true);
  }
  return 1; // tell the gui engine we are going to be moving away and not to redraw
}

// This will be called when the button is pressed or released
uint8_t callbackFunction_settings(void *a, GuiElement *element, uint8_t event) {
  if (event == GUI_EVENT_RELEASE) {
    Serial.println("Pressed Settings");
    Serial.print("x "); Serial.print(element->absoluteX());
    Serial.print(" y "); Serial.print(element->absoluteY());
    Serial.print(" p "); Serial.print(element->padding);
    Serial.print(" w "); Serial.print(element->width);
    Serial.print(" h "); Serial.println(element->height);
    panelMenu->visible(false);
    panelSettings->visible(true);
  }
  return 1; // tell the gui engine we are going to be moving away and not to redraw
}

uint8_t callbackFunction_menu1(void *a, GuiElement *element, uint8_t event) {
  if (event == GUI_EVENT_RELEASE) {
    Serial.println("Pressed menu 1");
  }
  return 0;
}

void buildPanelMenu() {
  // build a 4x4 grid of elements
  panelMenu = new GuiGrid(0, 0, 320, 240, 4, 4);
  panelMenu->padding = 0;
  panelMenu->margin = 0;
  
  GuiButton *button = new GuiButton(0, 0, 0, 0, "Settings");
  button->backgroundColour = GuiUtils::getColour(119, 185, 0); // purple
  // hook up the callback function defined above to the button so we can track clicks
  button->connectCallback(callbackFunction_settings);
  button->borderWidth = 0;

  GuiButton *button1 = new GuiButton(0, 0, 0, 0, "Menu 1");
  button1->backgroundColour = GuiUtils::getColour(99, 47, 0); // brown
  button1->connectCallback(callbackFunction_menu1);
  button1->borderWidth = 0;

  
  GuiButton *button2 = new GuiButton(0, 0, 0, 0, "Menu 2");
  button2->backgroundColour = GuiUtils::getColour(70,23,180); // blue
//  button2->connectCallback(callbackFunction);
  button2->borderWidth = 0;

  
  GuiButton *button3 = new GuiButton(0, 0, 0, 0, "Small");
  button3->backgroundColour = GuiUtils::getColour(255, 152, 29);
//  button3->connectCallback(callbackFunction);
  button3->borderWidth = 0;

  GuiButton *button4 = new GuiButton(0, 0, 0, 0, "Tiles");
  button4->backgroundColour = GuiUtils::getColour(255, 118, 188);
//  button3->connectCallback(callbackFunction);
  button4->borderWidth = 0;
  

  GuiButton *button5 = new GuiButton(0, 0, 0, 0, "Rock");
  button5->backgroundColour = GuiUtils::getColour(193, 0, 79);
//  button3->connectCallback(callbackFunction);
  button5->borderWidth = 0;

  GuiButton *button6 = new GuiButton(0, 0, 0, 0, "Exit");
  button6->backgroundColour = GuiUtils::getColour(86, 197, 255);
//  button3->connectCallback(callbackFunction);
  button6->borderWidth = 0;

  // add the elements into the grid. Each element it set to the grid by row and column
  // element, col, row, column span, row span
  panelMenu->addElement(button, 0, 0, 2, 2);
  panelMenu->addElement(button1, 2, 0, 2, 2);
  panelMenu->addElement(button2, 0, 2, 2, 2);
  panelMenu->addElement(button3, 2, 2, 1, 1);
  panelMenu->addElement(button4, 3, 2, 1, 1);
  panelMenu->addElement(button5, 2, 3, 1, 1);
  panelMenu->addElement(button6, 3, 3, 1, 1);
  
  // finally add the widgt to the page
  gui.addChild(panelMenu);
}

void buildPanelSettings() {
  // build a new panel and make it the same size as the screen
  // this panel will be hidden
  panelSettings = new GuiGrid(0, 0, 320, 240, 2, 2);
  panelSettings->padding = 0;
  panelSettings->margin = 0;
  
  GuiLabel *label = new GuiLabel(0, 0, 0, 0, "System Status: Mauve");

  GuiButton *button1 = new GuiButton(0, 0, 0, 0, "<- Home");
  button1->backgroundColour = GuiUtils::getColour(70,23,180); // blue
  button1->connectCallback(callbackFunction_home);
  button1->borderWidth = 0;

  panelSettings->addElement(label, 0, 0, 2, 1);
  panelSettings->addElement(button1, 0, 1, 1, 1);

  panelSettings->visible(false);
  
  // finally add the widget to the page
  gui.addChild(panelSettings);
}

void setup(void) {
 // while (!Serial);     // used for leonardo debugging

  Serial.begin(115200);
  delay(1000);
  Serial.println(F("Gui Widgets test!"));
  
  tft.begin();
  // in multiples of 90 only (duh)
  gui.setRotation(270);
    
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

