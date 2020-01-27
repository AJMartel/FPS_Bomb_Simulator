[comment]: # (Start Markdown Notes)
# 3DFabXYZ.com FPS Bomb Simulator v1.X
## MEGA2560 BASIC Model:
- Sketch uses 37338 bytes (14.7%) of program storage space. Maximum is 253952 bytes.
- Global variables use 1235 bytes (15.1%) of dynamic memory, leaving 6957 bytes for local variables. Maximum is 8192 bytes.

### Language Menu
Configurable up to 5 Languages
 - "English"
 - "French"
 - "Spanish"
 - "Portugues"
 - "German"

  **Note: Only English characters are printed on LCD using 2004 Charater display**

### PnP upgradable addon modules:
1. **Cutwire Module** (4 wires)
   - Not available in Domination and EscapeRoom modes.
   - Cutwire module will be disabled if any wires are not connected before the bomb is armed.
   - Plug in 4 wires (Red to Black connector), if wires are not connected the Cut wire option will not function.
        - 1 wire is randomly selected each game to "Disarm the bomb".
        - 1 wire is randomly selected each game to "Explode the bomb".
        - 1 wire is randomly selected each game to "Speedup the bomb timer".
        - 1 wire is randomly selected each game to "Slowdown the bomb timer".
        - If all wires are cut at the same time the bomb will explode.
2. **Relay Module** (4 ports)
   - the first 3 sockets can be used to power 3 externally attached lights, mirroring the RGB LED indicator
   - the 4th can be used to power a plug in device for the "Bang" when the bomb explodes (example: smoke machine)
3. **Servo Key Box** enables Escape Room game mode
4. **Sound with YX5300** (Currently in Development) will use hardwareserial1 on ATMega2560
5. **Laser Tag IR Module** (Currently in Hardware Development) uses the "MilesTag II Data Protocol"
6. **Wireless modules**
   * Future Development
     * Additional game modes to be developed
     * using hardwareserial2 on ATMega2560
       - Wireless Master
       - Wireless Numbered Slave (Multiple slaves possible)
       - Add 2 new game modes
         - Area Domination
         - Capture the Flag
7. **sw420 Module** shock/vibration sensor.
8. **Accelerometer**
   * Future Development
     * possibly the MPU6050 i2c module to replace the sw420 Module

### Currently 5 Game modes for FPS (Airsoft/LaserTag/Nerf/Paintball)
  - **Search and Destroy**
  - **Sabotage**
  - **Armed!**
  - **Domination**
  - **Conquered**

### and 1 Game mode for Escape Rooms
  - **Escape Room**

##    Search and Destroy
    In this mode the device acts as a bomb.
    When the "button" mode is used:
      i   The Red button Arms the bomb.
      ii  The Green button Disarms the bomb.
    When the "Passcode" mode is used:
      i   The time for Passcode entry has a programable time limit.
      ii  "A" is used to initialize the passcode entry to Arm the bomb.
      iii "D" is used to initialize the passcode entry to Disarm the bomb.
      iv  You can set the length of the passcode to a value between 04 and 16 digits
      v   The "Passcode hint" system is available.
    Common for both "passcode" and "button" modes:
      a.  The bomb can be armed and defused only once.
      b.  The bomb has to be defended by the GREEN team for the duration of the Game Time.
      c.  The attacking RED team's objective is to arm the bomb and once it is armed, they must prevent the GREEN team from defusing it, until it detonates.
    There are three ways to finish the game.
      1.  The Game time expires and the RED team was unsuccessful in placing and arming the bomb; the GREEN team wins.
      2.  The RED team was successful in placing and arming the bomb, but unable to prevent the GREEN team from disarming it; The GREEN team wins.
      3.  The RED team was successful in placing and arming the bomb, the GREEN team fails to disarm it and the bomb detonates; The RED team wins.


##    Sabotage
    In this mode the device acts as a bomb.
    When the "button" mode is used:
      i   The Red button Arms the bomb.
      ii  The Green button Disarms the bomb.
    When the "Passcode" mode is used:
      i   "A" is used to initialize the passcode entry to Arm the bomb.
      ii  "D" is used to initialize the passcode entry to Disarm the bomb.
      iii You can set the length of the passcode to a value between 04 and 16 digits
      iv  The "Passcode hint" system is available.
    Common for both "passcode" and "button" modes:
      a.  The bomb can be armed and defused as many times as the game time allows.
      b.  The bomb has to be defended by the GREEN team during Game Time.
      c.  The attacking RED team's objective is to arm the bomb and once armed must prevent the GREEN team from defusing it, until it detonates.
    There are two ways to finish the game.
      1.  The Game time expires and the RED team was unsuccessful in placing and arming the bomb; the GREEN team wins.
      2.  The RED team was successful in placing and arming the bomb, the GREEN team fails to disarm it and the bomb detonates; The RED team wins.

##    Armed!
    In this mode the device acts as a planted bomb.
    When the "button" mode is used:
      i   The Green button Disarms bomb.
    When the "Passcode" mode is used:
      i   The time for Passcode entry has a programable time limit.
      ii  "D" is used to initialize the passcode entry to Disarm the bomb.
      iii You ca set the length of the passcode to a value between 04 and 16 digits
      iv  The "Passcode hint" system is available.
    Common for both "passcode" and "button" modes:
      a.  The bomb starts armed with the countdown to detonation already triggered.
    There are two ways to finish the game.
      1.  The bomb time expires and the GREEN team was unsuccessful in disarming the bomb, and the bomb detonates; The RED team wins.
      2.  The GREEN team succeeds in disarming the bomb; The GREEN team wins.

##    Escape Room:
    In this mode the device acts as a planted bomb and key safe.
    Only the "Passcode" mode is available:
      i   The time for Passcode entry has a programable time limit.
      ii  "D" is used to initialize the passcode entry to Disarm the bomb.
      iii You ca set the length of the passcode to a value between 04 and 16 digits
      iv  "hint" system is unavailable.
      v   "cutwire" module is unavailable.
    In this mode:
      a.  The bomb starts armed with the countdown to detonation already triggered.
    There are two ways to finish the game.
      1.  The bomb time expires and the GREEN team was unsuccessful in disarming the bomb, and the bomb detonates; Game Over.
      2.  The GREEN team succeeds in disarming the bomb; The Key Box Opens.

##    Domination
    In this mode the device acts as a base.
    The Red button Captures the zone for the RED Team.
    The Red button Neutralizes a GREEN zone.
    The Green button Captures the zone for the GREEN Team.
    The Green button Neutralizes a RED zone.
      a.  When the game starts, the base is a Neutral (BLUE) Zone.
      b.  The objective for both (GREEN and RED) teams is to capture the base.
      c.  Once the base is captured, the controlling team's time is displayed on screen.
      d.  While the base is neutral no time is accumulated for either Red or Green teams.
      e.  Game can be configured to Neutralize the Zone after a set time => forces teams to patrol the zone to keep control.
      f.  When auto neutralize zone is enabled teams can recapture the zone to reset the auto neutralize time.
    The only way to win is:
      1.  The team with the highest total time in control of the base wins.

##    Conquered
    In this mode the device acts as a base.
    The goal is to be in control of the base with a total Captured time equal to a specified time.
    The Red button Captures the zone for the RED Team.
    The Red button Neutralizes a GREEN zone.
    The Green button Captures the zone for the GREEN Team.
    The Green button Neutralizes a RED zone.
      a.  When the game starts, the base is a Neutral (BLUE) Zone.
      b.  The objective for both (GREEN and RED) teams is to capture the base.
      c.  Once the base is captured, the controlling team's time is displayed on screen.
      d.  While the base is neutral no time is decreased for either Red or Green teams.
      e.  Game can be configured to Neutralize the Zone after a set time => forces teams to patrol the zone to keep control.
      f.  When auto neutralize zone is enabled teams can recapture the zone to reset the auto neutralize time.
    The only way to win is:
      1.  The team that has a total time in control of the base equal to the specified time wins.

####    To test
- [ ] DTMF (Telephone Keypad Sound) funtion requires Shield version 1.2+

Domination game mode
- [x] Reset Auto-Neutralize timer from last captured button press
- [ ] Red/Green buttons Blink when in control of zone (requires hardware v1.2+, Hardware v1.1 is always on)
- [ ] Winning Team's Button lights up at end of game (requires hardware v1.2+, Hardware v1.1 is always on)

Sound with YX5300 => use hardwareserial for ATMEGA2650
- [ ] Currently only available under "settings => test sound"
- [ ] Set Volume Level integrated into settings menu

Cutwire Module
- [ ] RandomWireGen optimized code, now sets the following variables
     - [x] wireDisarm
     - [x] wireExplode
     - [x] wireFaster => "timeMultiplier = 2" variable to increase game clock  to double the speed
     - [ ] wireSlower => "timeMultiplier = 1" variable to set game clock speed to the original speed
- [ ] use 2 variables to change game timer speed
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
- [ ] Created hardware changes [Driving IR from Arduino pin](https://www.analysir.com/blog/2014/10/03/driving-infrared-led-directly-arduino-pin/)

### To Do

  **Program space is limited use ATmega2650 to add the rest of the options:**

  - [x] Add Game mode "Conquered" Domination type game, game ends when counter reaches zero
  - [ ] Add difficulty must press a button to activate arm/disarm button?? Reqires hardware modification.
  - [ ] 12864 Graphic LCD Module
    - [ ] Support non-English characters
  - [ ] Sound Module
    - [x] Create function
    - [ ] Integrate into game modes.
    - [ ] Create sound files for different languages
  - [ ] Accelerometer MPU6050 i2c module to replace sw420 vibration sensor
  - [ ] Wireless LoRa modules, "E32 915T20D" => up to 3km, "E32 915T30D" => up to 8km
    - [ ] Wireless Master
    - [ ] Wireless Numbered Slave
      - [ ] Multi Slave to Master
   - [ ] Add 2 game modes for wireless play:
    - [ ] Area Domination
    - [ ] Capture the Flag
  - [ ] Add GPS?? to enable finding the device
  - [ ] Make a youtube video to demonstrate this project
  - [ ] Come up with a cooler name for this than "FPS Bomb Simulator"
  - [ ] Add settings for each Game Mode that are accessible at boot time

### BUGs
- [ ] Green LED always on juring game play
  -[x] Use alternate pins (on Timer 5)
- [ ] Static sound on **loudTone** pin

### Notes
- [Air Open Soft](http://www.soft-r.fr/index.php?p=accueil)
- [Arduino stackexchange.com](https://arduino.stackexchange.com/questions/14647/how-can-i-detect-a-disconnected-pin)
- [Electronics stackexchange.com](https://electronics.stackexchange.com/questions/83133/arduino-digitalread-reading-wrong)

### What's left on the project (as of 2020/01/22):
- [ ] Finish writing and upload the source code (currently v1.76)
  - [ ] See BUGs for current issues
- [ ] ReDesign and print circuit board then sent to China for fabrication
  - [ ] Required to use all available functionality of the device (version 1.2)
- [x] Build the actual device using PCB
  - [x] Currently working BETA Model PCB version 1.1
  - [ ] Build with new PCB version 1.2
- [ ] Install and calibrate system
  - [ ] See BUGs for current issues
- [ ] Write and publish instructables page

[comment]: # (End Markdown Notes)
