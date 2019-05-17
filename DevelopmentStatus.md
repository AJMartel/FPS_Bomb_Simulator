 NANO BASIC Model:
  Sketch to big to compile
 UNO BASIC Model:  ***NANO with UNO BootLoader***
  Sketch uses 31006 bytes (96%) of program storage space. Maximum is 32256 bytes.
  Global variables use 829 bytes (40%) of dynamic memory, leaving 1219 bytes for local variables. Maximum is 2048 bytes.
 MEGA/MEGA2560 PRO Model:
  Sketch uses 32614 bytes (12%) of program storage space. Maximum is 253952 bytes.
  Global variables use 1171 bytes (14%) of dynamic memory, leaving 7021 bytes for local variables. Maximum is 8192 bytes.

  *** 3DFabXYZ.com FPS BOMB SIMULATOR ***       
   
  Configurable 5 Languages = "English", "French", "Spanish", "Portugues", and "German" 
  **Note: Only English characters are printed on LCD**

  PnP upgradable addon modules:  
    i    Cutwire Module (4 wires)
           - Not available in Domination mode.
           - Cutwire module will be disabled if any wires are not connected before the bomb is armed.
           - Plug in 4 wires (Red to Black connector), if wires are not connected the Cut wire option will not function.
           - 1 wire is randomly selected each game to "Disarm the bomb".
           - 1 wire is randomly selected each game to "Explode the bomb".
		       - 1 wire is randomly selected each game to "Speedup the bomb timer".  "timeMultiplier = 2"
           - 1 wire is randomly selected each game to "Slowdown the bomb timer". "timeMultiplier = 0.5"
           - If all wires are cut at the same time the bomb will explode.
    ii   Relay Module (4 ports)
           - the first 3 sockets can be used to power 3 attached lights to be seen from afar, mirroring the RGB LED indicator
           - the 4th can be used to power a plug in device for the "Bang" when the bomb explodes (example: smoke machine)
    iii  sw420 Module (Currently Development has been Halted, the code execution Slowed down the System) shock/vibration sensor. 
    iv   Accelerometer  (Future Development)  MPU6050?? to replace sw420 for mega
    v    Sound with YX5300  (Currently in Development) will use hardwareserial1 on ATMega2560
    vi   Wireless modules  (Future Development)  (Function to be developed) will use hardwareserial2 on ATMega2560
    vii    - Wireless Master
           - Wireless Numbered Slave (Multiple slaves possible)
		   - Add 2 new game modes
		     *Area Domination
		     *Capture the Flag
  
  4 Game modes for FPS = "Search and Destroy", "Sabotage", "Domination", "Armed!"
  
Search and Destroy:
  In this mode the device acts as a bomb.
  When the "button" mode is used:
    i   The Red button Arms the bomb.
    ii  The Green button Disarms the bomb.
  When the "Passcode" mode is used:
    i   The time for Passcode entry has a programable time limit.
    ii  "A" is used to initialize the passcode entry to Arm the bomb.
    iii "D" is used to initialize the passcode entry to Disarm the bomb.
  Common for both "passcode" and "button" modes:
    a.  The bomb can be armed and defused only once.
    b.  The bomb has to be defended by the GREEN team for the duration of the Game Time.
    c.  The attacking RED team's objective is to arm the bomb and once it is armed, they must prevent the GREEN team from defusing it, until it detonates.
  There are three ways to finish the game.
    1.  The Game time expires and the RED team was unsuccessful in placing and arming the bomb; the GREEN team wins.
    2.  The RED team was successful in placing and arming the bomb, but unable to prevent the GREEN team from disarming it; The GREEN team wins.
    3.  The RED team was successful in placing and arming the bomb, the GREEN team fails to disarm it and the bomb detonates; The RED team wins.

Sabotage:
  In this mode the device acts as a bomb.
  When the "button" mode is used:
    i   The Red button Arms the bomb.
    ii  The Green button Disarms the bomb.
  When the "Passcode" mode is used:
    i   "A" is used to initialize the passcode entry to Arm the bomb.
    ii  "D" is used to initialize the passcode entry to Disarm the bomb.
  Common for both "passcode" and "button" modes:
    a.  The bomb can be armed and defused as many times as the game time allows.
    b.  The bomb has to be defended by the GREEN team during Game Time.
    c.  The attacking RED team's objective is to arm the bomb and once armed must prevent the GREEN team from defusing it, until it detonates.
  There are two ways to finish the game.
    1.  The Game time expires and the RED team was unsuccessful in placing and arming the bomb; the GREEN team wins.
    2.  The RED team was successful in placing and arming the bomb, the GREEN team fails to disarm it and the bomb detonates; The RED team wins.

Domination:
  In this mode the device acts as a base.
  The Red button Captures the zone for the RED Team.
  The Red button Neutralizes a GREEN zone.
  The Green button Captures the zone for the GREEN Team.
  The Green button Neutralizes a RED zone.
    a.  When the game starts, the base is a Neutral (BLUE) Zone.
    b.  The objective for both (GREEN and RED) teams is to capture the base.
    c.  Once the base is captured, the controlling team's time is displayed on screen.
    d.  While the base is neutral no time is accumulated for either Red or Green teams.
  The only way to win is:
    1.  The team with the highest total time in control of the base wins.

Armed!:
  In this mode the device acts as a planted bomb.
  When the "button" mode is used:
    i   The Green button Disarms bomb.
  When the "Passcode" mode is used:
    i   The time for Passcode entry has a programable time limit.
    ii  "D" is used to initialize the passcode entry to Disarm the bomb.
  Common for both "passcode" and "button" modes:
    a.  The bomb starts armed with the countdown to detonation already triggered.
  There are two ways to finish the game.
    1.  The bomb time expires and the GREEN team was unsuccessful in disarming the bomb, and the bomb detonates; The RED team wins.
    2.  The GREEN team succeeds in disarming the bomb; The GREEN team wins.

 To test: 
   1.23
   Disarm/Neutralize => Reverse onscreen progress bar direction "drawNegPercent();"
   Piezo changes tempo as bomb is about to explode
     - Once per second before 1 minute
     - Piezo tempo Speeds up at the 1 munute mark
     - Piezo tempo Speeds up again at 10 secondes to explosion
     - Changed sound when bomb explodes.
   Sound with YX5300 => use hardwareserial for ATMEGA2650	  
     - Currently only available under "settings => test sound" 	
   RandomWireGen optimized code, now sets the following variables
     -wireDisarm	  
     -wireExplode	  
     -wireFaster => Added "timeMultiplier = 2" variable to increase game clock speed	  -+- Might have to invert these
     -wireSlower => Added "timeMultiplier = 0.5" variable to decrease game clock speed  -+
   Cutwire Module use 2 variables to change game timer speed "printTime(minutes, (aTime * timeMultiplier));" (maybe modify iTime?)
   Added pins to control the Button LEDs (FPS-Bomb-Mega-Shield-v1.1 shield changed to reflect changes)
   Board ID - Variables and Function created **"shieldVersion" Value
     - Display Firmware and Shield versions under Settings

 
 To Do: 
  Program space is limited use ATmega2650 to add the rest of the options:
	Domination game mode
	  - [ ]  Red/Green buttons Blink when in control of zone (requires hardware v1.1)
	  - [ ]  Winning Team's Button lights up at end of game (currently RGB LED lights up)
	  - [ ]  Display TOTAL TIME in control of the zone
	  - [ ]  Neutralize the Zone after a set time => forces teams to patrol the zone
    Sound Module
	  - [ ]  Integrate into game modes.
	  - [ ]  Set Volume Level [use setTempTime() as starting point for code]
    Accelerometer MPU6050?? to replace sw420 vibration sensor
    Wireless LoRa modules, "E32 915T20D" => up to 3km, "E32 915T30D" => up to 8km
      - [ ]  WirelessMaster
      - [ ]  WirelessNumberedSlave
		*Multi Slave to Master
        **with wireless modules add 2 game modes: 
          - [ ]  "Area Domination", and 
          - [ ]  "Capture the Flag"


What's left on the project (as of 17/05/2019):
- [ ] Finish writing and upload the source code (currently v1.23)
- [x] Design and print circuit board (sent to China for fabrication)
- [ ] Build the actual device using PCB
- [ ] Install and calibrate system
- [ ] Write and publish instructables page
- [ ] Make README.md prettier by turning it into a gh-page
