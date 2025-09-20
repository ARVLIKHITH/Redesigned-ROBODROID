# Redesigned-ROBODROID
# Robodroid — Fire Fighting Robot (First Semester Prototype)  

## Story and Background  
During my first semester at RVCE University, I was enrolled in a 13th Year Certification Course, where I was tasked with designing, prototyping, and presenting a working system.  

While exploring ideas, I came across a [YouTube video demonstration](https://www.youtube.com/watch?v=v19kwZ4ReT0) of a fire-fighting robot. The concept inspired me, and instead of directly replicating it, I decided to experiment with the design, add my own modifications, and build a working version.  

This became Robodroid, my very first robotics prototype.  

- I was responsible for the electronics design, sensor integration, circuit connections, and prototype assembly.  
- My friend, Arnav Bajaj, contributed by developing the Arduino code that handled sensor logic, motor control, and GSM communication.  
- Together, we successfully created a working system capable of detecting fire, sending alerts, and extinguishing flames.  

This project introduced me to embedded systems and robotics, and taught me valuable lessons in power regulation, sensor calibration, and the importance of collaboration.  
<p align="center">
  <img width="500" alt="Robodroid Prototype" src="https://github.com/user-attachments/assets/7fbf0b86-b15a-4936-8327-9096da136ad4" />
</p>

## System Overview  

### Sensors  
- Flame Sensors — used to detect the presence of fire in front of the robot.  
- MQ2 Gas Sensor — detects gases such as propane, methane, and smoke, as well as lighter fumes, within a range of 200–10,000 ppm.  

### Actuators and Components  
- Water Pump — controlled via a relay, used to spray water onto the flame.  
- Servo Motor (180°) — mounted at the front, sweeping the nozzle between 50° and 110° to cover the area of the fire.  
- DC Motors (chassis movement) — allowed the robot to approach the detected fire.  
- SIM800L GSM Module — sent SMS alerts and made phone calls when fire or gas was detected.  

### Controller and Power  
- Arduino UNO — main microcontroller for handling sensors, actuators, and communication.  
- Power Supply — 18650 Li-ion batteries.  
- LM2596 Voltage Regulator — reduced the voltage to ensure the SIM800L module operated safely at around 4.3 V.  

---

## Working Principle  

1. Detection  
   - Flame sensor detects the presence of fire.  
   - MQ2 gas sensor identifies gas or smoke.  

2. Communication  
   - On gas detection, the Arduino sends AT commands to the SIM800L module.  
   - The module sends an SMS and makes a phone call to notify the user.  

3. Action  
   - When fire is detected, the Arduino drives the DC motors to move the robot closer to the fire.  
   - The relay activates the water pump, which sprays water through the nozzle.  
   - The servo motor sweeps the nozzle across an arc to maximize coverage and extinguish the fire.  

---

## Contributors  
- Likhith Anand — Electronics design, circuit integration, prototype assembly, power regulation, and documentation.  
- Arnav Bajaj — Arduino programming (sensor logic, motor control, and SIM800L communication).  

---

## Prototype Media  
- [Slides (PPT)](./Fire%20Fighting%20Robot%20Car.pptx)  
- [Arduino Code](./1Fire_Fighting_Bot-1.text)  
- [Inspiration video](https://www.youtube.com/watch?v=v19kwZ4ReT0)  

---

## Problems Faced (First Semester)  
- Power Issues: The SIM800L module malfunctioned when supplied with more than 5 V. This was resolved using an LM2596 step-down regulator.  
- GSM Reliability: SMS sending and call functions sometimes failed due to unstable AT command handling. Debugging and delays were added for stability.  
- Water Pump Current Draw: The initial current surge from the pump caused the Arduino to reset. This was fixed by isolating the pump on a separate relay-controlled supply.  
- Servo Jitter: The servo motor experienced jittering during idle. Grounding improvements and stable PWM control resolved the issue.  
- Navigation Tuning: Achieving accurate approach towards the flame required fine adjustments of flame sensor logic.  

---

## Lessons Learned  
- Proper voltage regulation is critical when using GSM modules like SIM800L.  
- Separating power supplies for high-current actuators and the microcontroller ensures system stability.  
- Sensor calibration significantly improves detection accuracy and reduces false triggers.  
- Teamwork between electronics design and coding is essential in building reliable prototypes.  

---

## References and Inspiration  
- Original Inspiration: [YouTube – Fire Fighting Robot Project](https://www.youtube.com/watch?v=v19kwZ4ReT0).  
- Circuit Diagram Credit: Belongs to the YouTube creator (not my own work).  
- Hardware Guides: Datasheets for MQ2 sensor, SIM800L module, and servo motor.  
- Documentation: Self-prepared presentation and prototype description.  

> Note: This project was inspired by publicly available tutorials, but the modifications (SIM800L integration, regulator design, electronics assembly) and the prototype build were my own work, completed in collaboration with Arnav Bajaj.  

---

In the second semester, this design was improved further to address the limitations of the first prototype. The upgraded version is documented in Part 2.  
