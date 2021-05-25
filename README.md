# ebook-reader-for-m5stack-core-2
eBook Reader for the M5Stack Core 2 


Smallest eBook reader? This is a port of the <a href="https://github.com/jackbrennan-creator/minimalist-ebook-reader">Minimalist eBook Reader for InkPlate 6</a> to the <a href="https://docs.m5stack.com/en/core/core2">M5Stack Core 2</a>. 
The overall structure of this system is the same as that of the InkPlate 6 system. The details are described here and are not repeated in this document. In particular details of eBook file formatting remain the same.

![eBook Reader](https://github.com/jackbrennan-creator/minimalist-ebook-reader/blob/main/screen.JPG)

As the original system only used a small subset of the functions from the InkPlate library, the strategy used for this port was to build a class to implement that subset on top of the M5Stack Core 2 library. This class is called “ink_plate”. The fact that the InkPlate is an eInk device, i.e. has a persistent display, and the Core 2 has an LCD display, is not a problem. For an eInk screen, graphics are defined first and then the display is updated all in one go. For a TFT display, the final update operation is null as graphics appear on the screen as they are defined. The InkPlate has three touch contacts that are not part of the display and these were used to interact with the eBook reader. The Core 2 has three built-in touch areas that are part of the display and these were used for the same purpose.

Substituting the new class for the InkPlate library class allowed the original source to compile with no other changes. Some subsequent adjustments were made to font sizes and positioning to allow for the smaller display size. In addition, the Core 2 library provides “gesture” support and this was used to map “swipe” gestures onto the three navigation buttons. Left and right swipes cause page turning to the next page or previous page. Up or down swipes are equivalent to tapping the menu button. The original software did not require any changes to accommodate this. 

The only other problem was using the SdFat library in conjunction with the Core 2 library. The InkPlate design relied on using the SdFat library so that eBook files can be named with the full titles of the books they contain. This requires FAT32 formatting to allow long file names. The Core 2 library provides SD card support that is not comparable with this requirement. Unfortunately both the SdFat library and the Core 2 library define a type called "FILE" and this creates a name conflict. To solve this, a modified copy of the SdFat library was embedded in the system with all references to the identifier "FILE" globally replaced with "simple_file". A corresponding modification to the original eBook reader source then allowed the system to compile and operate correctly using an SD card originally setup for the InkPlate system.

The only other change made to the original system was to specifically exclude any non-ASCII characters from being sent to the display. The InkPlate library seems to handle this correctly, i.e. non-ASCII characters are ignored, whereas the corresponding Core 2 functions cause the system to reboot after a “core panic”. 

There is no separate documentation for this system, the PDF document for the original InkPlate system covers all the main details. 

This system was build using Arduino IDE 1.8.13 under macOS Sierra, running on a 2010 Macbook Pro.

The M5Stack Core 2 library from https://github.com/ropg/M5Core2 was version 0.0.3.

https://carinasagittarius.co.uk/
