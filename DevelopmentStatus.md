[comment]: # (Start Markdown Notes)
# 3DFabXYZ.com FPS Bomb Simulator v1.X
## MEGA2560 BASIC Model:
- Sketch uses 40128 bytes (15%) of program storage space. Maximum is 253952 bytes.
- Global variables use 1243 bytes (15%) of dynamic memory, leaving 6949 bytes for local variables. Maximum is 8192 bytes.

### Language Menu
Configurable up to 5 Languages
 - "English"
 - "French"
 - "Spanish"
 - "Portugues"
 - "German"

  **Note: Only English characters are printed on LCD using 2004 Charater display**

### PnP upgradable addon modules:
**All modules are auto-detected when the bomb is powered on**
**Addon modules afect available options for game play**
1. **Cutwire Module** (4 wires)
   - Not available in Domination and EscapeRoom modes.
   - Cutwire module will be disabled if any wires are not connected before the bomb is armed.
     - Plug in 4 wires (Red to Black connector), if wires are not connected the Cut wire option will not function.
        - 1 wire is randomly selected each game to "Disarm the bomb".
        - 1 wire is randomly selected each game to "Explode the bomb".
        - 1 wire is randomly selected each game to "Speedup the bomb timer".
        - 1 wire is randomly selected each game to "Nothing".
        - If all wires are cut at the same time the bomb will explode.
2. **Relay Module** (4 ports)
   - the first 3 sockets can be used to power 3 externally attached lights, mirroring the RGB LED indicator
   - the 4th can be used to power a plug in device for the "Bang" when the bomb explodes (example: smoke machine)
3. **Servo Key Box** enables Escape Room game mode
**Remaining devices are in development (current or Future)**
4. **Sound with YX5300** (Currently in Development) will use hardwareserial1 on ATMega2560
5. **Laser Tag IR Module** (Currently in Hardware Development) uses the "MilesTag II Data Protocol"
6. **Wireless modules**
   * Future Development
     * Additional game modes to be developed
     * using hardwareserial2 on ATMega2560
       - Wireless Master
       - Wireless Numbered Slave (Multiple slaves possible)
       - Add 4 new game modes
         - Area Domination
         - Area Conquered
         - Capture the Flag
         - Pandemic (Virus transport)
7. **sw420 Module** shock/vibration sensor. (Currently implimented in code but not recomending public release)
8. **Accelerometer**
   * Future Development
     * possibly the MPU6050 i2c module to replace the sw420 Module

### Currently 5 Game modes for FPS (Airsoft/Paintball/LaserTag)
  - **Search and Destroy**
  - **Sabotage**
  - **Armed!**
  - **Domination**
  - **Conquered**

### and 1 Game mode for Escape Rooms
  - **Escape Room**

##    Search and Destroy
#### In this game mode the device acts as a bomb.
1. When the "button" mode is used:
      1.   The Red button Arms the bomb.
      2.  The Green button Disarms the bomb.
2. When the "Passcode" mode is used:
      1.   The time for Passcode entry has a programable time limit.
      2.  "A" is used to initialize the passcode entry to Arm the bomb.
      3. "D" is used to initialize the passcode entry to Disarm the bomb.
      4.  You can set the length of the passcode to a value between 04 and 16 digits
      5.   The "Passcode hint" system is available.
3. Common for both "passcode" and "button" modes:
      1.  The bomb can be armed and defused only once.
      2.  The bomb has to be defended by the GREEN team for the duration of the Game Time.
      3.  The attacking RED team's objective is to arm the bomb and once it is armed, they must prevent the GREEN team from defusing it, until it detonates.
4. There are three ways to finish the game.
      1.  The Game time expires and the RED team was unsuccessful in placing and arming the bomb; the GREEN team wins.
      2.  The RED team was successful in placing and arming the bomb, but unable to prevent the GREEN team from disarming it; The GREEN team wins.
      3.  The RED team was successful in placing and arming the bomb, the GREEN team fails to disarm it and the bomb detonates; The RED team wins.


##    Sabotage
#### In this game mode the device acts as a bomb.
1. When the "button" mode is used:
      1.   The Red button Arms the bomb.
      2.  The Green button Disarms the bomb.
2. When the "Passcode" mode is used:
      1.   "A" is used to initialize the passcode entry to Arm the bomb.
      2.  "D" is used to initialize the passcode entry to Disarm the bomb.
      3. You can set the length of the passcode to a value between 04 and 16 digits
      4.  The "Passcode hint" system is available.
3. Common for both "passcode" and "button" modes:
      1.  The bomb can be armed and defused as many times as the game time allows.
      2.  The bomb has to be defended by the GREEN team during Game Time.
      3.  The attacking RED team's objective is to arm the bomb and once armed must prevent the GREEN team from defusing it, until it detonates.
4. There are two ways to finish the game.
      1.  The Game time expires and the RED team was unsuccessful in placing and arming the bomb; the GREEN team wins.
      2.  The RED team was successful in placing and arming the bomb, the GREEN team fails to disarm it and the bomb detonates; The RED team wins.

##    Armed!
#### In this game mode the device acts as a planted bomb.
1. When the "button" mode is used:
      1.   The Green button Disarms bomb.
2. When the "Passcode" mode is used:
      1.   The time for Passcode entry has a programable time limit.
      2.  "D" is used to initialize the passcode entry to Disarm the bomb.
      3. You ca set the length of the passcode to a value between 04 and 16 digits
      4.  The "Passcode hint" system is available.
3. Common for both "passcode" and "button" modes:
      1.  The bomb starts armed with the countdown to detonation already triggered.
4. There are two ways to finish the game.
      1.  The bomb time expires and the GREEN team was unsuccessful in disarming the bomb, and the bomb detonates; The RED team wins.
      2.  The GREEN team succeeds in disarming the bomb; The GREEN team wins.

##    Escape Room:
#### In this game mode the device acts as a planted bomb and key safe.
1. Only the "Passcode" mode is available:
      1.   The time for Passcode entry has a programable time limit.
      2.  "D" is used to initialize the passcode entry to Disarm the bomb.
      3. You ca set the length of the passcode to a value between 04 and 16 digits
      4.  "hint" system is unavailable.
      5.   "cutwire" module is unavailable.
2. In this mode:
      1.  The bomb starts armed with the countdown to detonation already triggered.
3. There are two ways to finish the game.
      1.  The bomb time expires and the GREEN team was unsuccessful in disarming the bomb, and the bomb detonates; Game Over.
      2.  The GREEN team succeeds in disarming the bomb; The Key Box Opens.

##    Domination
#### In this game mode the device acts as a base.
1. Only the "button" mode is available
   1. The Red button Captures the zone for the RED Team.
   2. The Red button Neutralizes a GREEN zone.
   3. The Green button Captures the zone for the GREEN Team.
   1. The Green button Neutralizes a RED zone.
2. This is a time limited game.
   1.  When the game starts, the base is a Neutral (BLUE) Zone.
   2.  The objective for both (GREEN and RED) teams is to capture the base.
   3.  Once the base is captured, the controlling team's time is displayed on screen.
   4.  While the base is neutral no time is accumulated for either Red or Green teams.
   5.  Game can be configured to Neutralize the Zone after a set time => forces teams to patrol the zone to keep control.
   1.  When auto neutralize zone is enabled teams can recapture the zone to reset the auto neutralize time.
3. The only way to win is:
   1.  The team with the highest total time in control of the base wins.

##    Conquered
#### In this game mode the device acts as a base.
1. Only the "button" mode is available.
    1. The goal is to be in control of the base with a total Captured time equal to a specified time.
    2. The Red button Captures the zone for the RED Team.
    3. The Red button Neutralizes a GREEN zone.
    4. The Green button Captures the zone for the GREEN Team.
    5. The Green button Neutralizes a RED zone.
2. This is a time limited game.
    1.  When the game starts, the base is a Neutral (BLUE) Zone.
    2.  The objective for both (GREEN and RED) teams is to capture the base.
    3.  Once the base is captured, the controlling team's time is displayed on screen.
    4.  While the base is neutral no time is decreased for either Red or Green teams.
    5.  Game can be configured to Neutralize the Zone after a set time => forces teams to patrol the zone to keep control.
    6.  When auto neutralize zone is enabled teams can recapture the zone to reset the auto neutralize time.
3. The only way to win is:
    1.  The team that has a total time in control of the base equal to the specified time wins.

####    To test
- [ ] Quick Game Menus

- [ ] DTMF (Telephone Keypad Sound) funtion requires Shield version 1.2+

Domination game mode
- [x] Reset Auto-Neutralize timer from last captured button press
- [ ] Red/Green buttons Blink when in control of zone (requires hardware v1.2+, Hardware v1.1 is always on)
- [ ] Winning Team's Button lights up at end of game (requires hardware v1.2+, Hardware v1.1 is always on)

Sound with YX5300 => use hardwareSerial for ATMEGA2650
- [ ] Currently only available under "settings => test sound"
- [ ] Set Volume Level integrated into settings menu

Cutwire Module
- [x] RandomWireGen optimized code, now sets the following variables
     - [x] wireDisarm
     - [x] wireExplode
     - [x] wireFaster => "timeMultiplier = 2" variable to increase game clock  to double the speed
     - [x] wireSlower => "Nothing"
- [x] use variable to change game timer speed
  - ``` "currentMillis = ((millis() - startMillis) * timeMultiplier );" ```

Added pins to control the Button LEDs
- [ ] Requires FPS-Bomb-Mega-Shield-v1.2+ shield changed to reflect changes

Board ID
- [x] Variables and Function created **shieldVersion** Value

Escape Room game mode
- [x] Added servo for Escape Room gamemode (Servo will unlock a box holding a key, Used for "Escape Rooms")
- [x] replaced display names
  - ```"Green team" ==> "Captives"```
  - ```"Red team" ==> "Jailers"```

LaserTag Module (http://www.lasertagparts.com/mtformat-2.htm)
- [x] Code created for IR pulse (Explode Player), integrated menu code to enable option

### To Do

  **Due to Program space using ATmega2650 to add the remaining options:**

  - [x] Add settings for each Game Mode that are accessible at boot time
    - [ ] Test each quick game
  - [ ] MP3 Sound Module
    - [x] Create function
    - [ ] Integrate into game modes.
    - [ ] Create sound files for different languages

  **FPS Bomb Simulator Board v1.2+**
  - Add **Servo Key Box** for Escape Room game mode
  - LaserTag Module
    - [ ] Create hardware changes [Driving IR from Arduino pin](https://www.analysir.com/blog/2014/10/03/driving-infrared-led-directly-arduino-pin/)
  - [ ] Create 2nd separate board for Pro edition
    - [ ] Move Wireless Module to 2nd separate board
      - [ ] Wireless LoRa modules, "E32 915T20D" => up to 3km, "E32 915T30D" => up to 8km
	    - [ ] Wireless Master
	    - [ ] Wireless Numbered Slave
	      - [ ] Multi Slave to Master
	    - [ ] Add 3 game modes for wireless play:
	      - [ ] Area Domination
          - [ ] Capture the Flag
          - [ ] Epidemic
    - [ ] Move SPI GLCD Module to 2nd separate board
      - [ ] 12864 Graphic LCD Module
      - [ ] Support for non-English characters
  - [ ] Add difficulty must press a button to activate arm/disarm button?? Reqires major hardware modifications.
  - [ ] Accelerometer MPU6050 i2c module to replace sw420 vibration sensor
  - [ ] Add GPS?? to enable finding the device

### BUGs
- [x] Green LED always on juring game play, changed pins fixed issue
- [ ] Static sound on **tonePin2** pin
- [ ] Change VibrationSensor Pin

### Notes
- [Air Open Soft](http://www.soft-r.fr/index.php?p=accueil)
- [Arduino stackexchange.com](https://arduino.stackexchange.com/questions/14647/how-can-i-detect-a-disconnected-pin)
- [Electronics stackexchange.com](https://electronics.stackexchange.com/questions/83133/arduino-digitalread-reading-wrong)

- https://github.com/AJMartel/Evc_pt2257
- http://www.coldtears-electronics.com/images/PT2257-1.jpg
```text
                 |----._.----|
     10uF+    1 -| Lin   Rin |- 8    +10uF
     10uF+    2 -| Lout Rout |- 7    +10uF
     GND      3 -| Gnd    V+ |- 6    .1uF +47uF 5VDC
     SDA      4 -| SDA   SCL |- 5    SCL
                 |-----------|
```
- Control LCD backlight
- https://e-radionica.com/en/blog/hum-digital-potentiometer-10k/
- MCP4018 I2C 10KOhm 128 steps


### What\'s left on the project (as of 2020/02/24):
- [ ] Finish writing and upload the source code (currently v1.92)
- [ ] ReDesign and print circuit board then sent to China for fabrication
  - [ ] Required to use all available functionality of the device (version 1.2)
- [x] Build the actual device using PCB
  - [x] Currently working with PCB version 1.1
  - [ ] Build with new PCB version 1.2
- [ ] Install and calibrate system
  - [ ] See BUGs for current issues
- [ ] Come up with a cooler name for this than "FPS Bomb Simulator"
- [ ] Write and publish instructables page
- [ ] Make a youtube video to demonstrate this project


[comment]: # (End Markdown Notes)
