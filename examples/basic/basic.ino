#include "seeed_line_chart.h" //include the library

TFT_eSPI tft;

#define MAX_SIZE 30 // maximum size of data
doubles data;       // Initilising a doubles type to store data
int brightness;

void setup()
{
    pinMode(A0, INPUT);
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(TFT_WHITE);
}

void loop()
{
    brightness = analogRead(A0);

    if (data.size() > MAX_SIZE) // keep the old line chart front
    {
        data.pop(); // this is used to remove the first read variable
    }

    data.push(brightness); // read variables and store in data

    // Settings for the line graph title
    auto header = text(0, 0)
                      .value("Light Sensor Readings")
                      .align(center)
                      .valign(vcenter)
                      .width(tft.width())
                      .thickness(2);

    header.height(header.font_height(&tft) * 2);
    header.draw(&tft); // Header height is the twice the height of the font

    // Settings for the line graph
    auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
    content
        .height(tft.height() - header.height() * 1.5) // actual height of the line chart
        .width(tft.width() - content.x() * 2)         // actual width of the line chart
        .based_on(0.0)                                // Starting point of y-axis, must be a float
        .show_circle(false)                           // drawing a cirle at each point, default is on.
        .value(data)                                  // passing through the data to line graph
        .max_size(MAX_SIZE)
        .color(TFT_RED)                               // Setting the color for the line
        .backgroud(TFT_WHITE)                         // Setting the color for the backgroud
        .draw(&tft);
    
    delay(200);
}
